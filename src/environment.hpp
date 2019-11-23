#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <iostream>
#include <unordered_map>

#include "object.hpp"

class Environment {
    public:
        Environment() { /*enclosing = nullptr;*/ }

        void define(std::string name, Object* value);
        Object* lookup(std::string name);

    private:
        // The surrounding (outer) scope so we can find
        // variable outside this environment.
        // Environment* enclosing;


        // Keep track of values in the scope
        std::unordered_map<std::string, Object*> env;
};

#endif
