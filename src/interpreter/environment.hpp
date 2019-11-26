#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <iostream>
#include <unordered_map>

#include "object.hpp"

struct Value {
    bool _mutable;
    bool _mutably_borrowed = false;
    bool _borrowed = false;
    Object* value;
};

struct Ref {
    bool _mutable;
    std::string to;
};

class Environment {
    public:
        Environment() { /*enclosing = nullptr;*/ }

        void define(std::string name, Value value);
        void assign(std::string name, Object* value); // cannot assign to non-existent vars

        Object* lookup(std::string name);
        
        // For pointers
        void reference(std::string from, std::string to, bool _mutable);
        Object* dereference(std::string alias);


    private:
        // The surrounding (outer) scope so we can find
        // variable outside this environment.
        // Environment* enclosing;


        // Keep track of values in the scope
        std::unordered_map<std::string, Value> env;

        // Points to map
        std::unordered_map<std::string, Ref> pointer;
};

#endif
