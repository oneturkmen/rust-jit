#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <string>

/**
 * Wrappers around primitive types
 * that hold type information and
 * values.
 *
 * Reference: @rpshukla/napkin
 **/


class Object {
    public:
        virtual std::string value() = 0;
        virtual void print() = 0;

        enum Type {
            NUMBER,
            STRING,
            REFERENCE,
        };

        Type type;
};


class Number : public Object {
    public:
        Number(int value) // TODO: extend to double
            : m_value{value} {
                type = NUMBER;
            }

        std::string value() {
            return std::to_string(m_value);
        }

        void print() {
            // Display thyself.
            std::cout << m_value << "\n";
        }

        int m_value;
};


class String : public Object {
    public:
        String(std::string value)
            : m_value{value} {
            type = STRING;
        }

        std::string value() {
            return m_value;
        }

        void print() {
            std::cout << "\"" << m_value << "\"\n";
        }

        std::string m_value;
};

/**
 * Wrapper class for declaration statement
 * or assignment expression for referencing other
 * variable.
 */
class Reference : public Object {
    public:
        Reference(std::string obj_name, bool is_mutable)
            : to{obj_name}, _mutable{is_mutable} {
            type = REFERENCE;    
        }

        std::string value() {
            // none
            return "";
        }

        void print() {
            // none
        }

        bool _mutable;
        std::string to;
};

#endif
