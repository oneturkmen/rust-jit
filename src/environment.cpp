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

void Environment::assign(std::string name, Object* value) {
    if (name.empty() || value == nullptr) {
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
    // FIXME: this is ugly.
    bool current_mutable = env[name]._mutable;

    if (!current_mutable) {
        std::cout << "ERROR: Variable is immutable, cannot re-assign!\n";
        return;
    }

    env[name] = {
        current_mutable,
        value,
    };

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
