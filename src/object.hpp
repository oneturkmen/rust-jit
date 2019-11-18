#ifndef OBJECT_H
#define OBJECT_H

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

        enum Type {
            NUMBER,
            STRING,
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

        int m_value;
};


class String : public Object {
    public:
        String(std::string s) {
            m_value = s;
        }

        std::string value() {
            return m_value;
        }

        std::string m_value;
};

#endif
