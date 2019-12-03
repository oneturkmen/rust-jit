#include "environment.hpp"

void Environment::define(std::string name, Value value) {
    if (name.empty()) {
        std::cout << "ERROR: name or value cannot be empty! name = "
                  << name << "\n";
        return;
    }

    auto found = env.find(name);

    if (found != env.end()) {
        std::cout << "ERROR: Cannot re-define a variable!" << std::endl;
        return;
    }

    env[name] = value;

    return;
}

void Environment::assign(std::string name, Object* object) {
    if (name.empty() || object == nullptr) {
        std::cout << "ERROR: name or value cannot be empty! name = "
                  << name << "\n";
        return;
    }

    auto found = env.find(name);

    // std::cout << "Hello" << object->value() << std::endl;
    if (found == env.end()) {
        std::cout << "ERROR: Cannot assign to non-existent variable!\n";
        return;
    }

    // Retrieve current object and re-assign.
    bool is_mutable = env[name]._mutable;
    bool is_borrowed = env[name]._borrowed;
    Object* target  = env[name].value;

    if (!is_mutable) {
        std::cout << "ERROR: Variable `"
            << name
            << "` is immutable, cannot re-assign!\n";
        return;
    }
    if (object->type != target->type) {
        std::cout << "ERROR: L-value and R-value types are different!\n";
        return;
    }
    if (is_borrowed) {
        std::cout << "ERROR: Variable `"
            << name
            << "` is borrowed, cannot re-assign!\n";
        return;
    }

    env[name].value = object;

    return;
}

Object* Environment::lookup(std::string name) {
    if (name.empty()) {
        std::cout << "ERROR: Name cannot be empty!\n";
        throw;
    }

    try {
        if (env.find(name) == env.end()) {
            throw std::out_of_range("Entry not found");
        }

        return env[name].value;
    } catch (std::out_of_range) {
        // TODO: Gotta ask outer scope as well

        if (pointer.find(name) == pointer.end()) {
            std::cout << "ERROR: Variable `" + name + "`is not defined\n";
        }

        return nullptr;
    }
}

void Environment::reference(std::string from, std::string to, bool _mutable = false) {
    // std::cout << "Inside reference()\n";
    // Validate that target exists
    auto found = env.find(to);

    if (found == env.end()) {
        std::cout << "ERROR: Cannot reference non-existent variable!\n";
        return;
    }

    // Validate that:
    // 1. If target is already borrowed, then only immutably.
    // 2. If target is not borrowed, then can be any (mutable and immutable) borrow.
    if (found->second._mutably_borrowed) {
        std::cout << "ERROR: Cannot borrow `"
            << to
            << "` because it is already borrowed as mutable\n";
        return;
    }
    else if (found->second._borrowed && _mutable) {
        std::cout << "ERROR: Cannot borrow `"
            << to
            << "` as mutable because it is already borrowed as immutable\n";
        return;
    }

    // Add in the pointer map
    pointer[from] = {
        _mutable,
        to,
    };

    // Can either borrow mutably or immutably
    if (_mutable) {
        env[to]._borrowed = true;
        env[to]._mutably_borrowed = true;
    }
    else {
        env[to]._borrowed = true;
    }
}

Object* Environment::dereference(std::string alias) {
    // Validate that reference exists
    auto found = pointer.find(alias);

    if (found == pointer.end()) {
        std::cout << "ERROR: Cannot dereference non-existent alias!\n";
        return nullptr;
    }

    Ref ref = pointer[alias];

    // May be a reference to reference to reference ...
    while (pointer.find(ref.to) != pointer.end()) {
        ref = pointer[ref.to];
    }

    // std::cout << "TARGET == " << ref.to << "\n";
    return env[ref.to].value;
}
