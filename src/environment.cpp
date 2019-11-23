#include "environment.hpp"

void Environment::define(std::string name, Object* value) {
    if (name.empty() || value == nullptr) {
        std::cout << "ERROR: name or value cannot be empty! name = "
                  << name << "\n";
        return;
    }

    env[name] = value;

    return;
}

Object* Environment::lookup(std::string name) {
    if (name.empty()) {
        std::cout << "ERROR: Name cannot be empty!\n";
        throw;
    }
    
    try {
        return env[name];
    } catch (std::out_of_range) {
        // TODO: Gotta ask outer scope as well

        return nullptr;
    }
}
