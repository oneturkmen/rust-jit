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

    if (found == env.end()) {
        std::cout << "ERROR: Cannot assign to non-existent variable!\n";
        return;
    }

    // Retrieve current object and re-assign.
    bool is_mutable = env[name]._mutable;
    Object* target  = env[name].value;

    if (!is_mutable) {
        std::cout << "ERROR: Variable is immutable, cannot re-assign!\n";
        return;
    }
    if (object->type != target->type) {
        std::cout << "ERROR: L-value and R-value types are different!\n";
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
        return env[name].value;
    } catch (std::out_of_range) {
        // TODO: Gotta ask outer scope as well

        return nullptr;
    }
}
