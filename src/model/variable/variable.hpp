#ifndef __VARIABLE_HPP__
#define __VARIABLE_HPP__

#include <optional>
#include <stdexcept>
#include <string>

#include "../value/value.hpp"

using namespace std;

namespace Model {

    namespace Variable {

        class Variable {
            private:
                long id;
                string name;
                DataType data_type;

            protected:
                Variable(long id, string name, DataType data_type): id(id), name(name), data_type(data_type) {}

            public:
                virtual ~Variable() = default;

                string getName() const { return name; }

                DataType getDataType() const { return data_type; }
        };

        class Double: public Variable {
            private:
                optional<Value::Double> minimum;
                optional<Value::Double> maximum;

            public:
                Double(long id, string name, optional<Value::Double> minimum, optional<Value::Double> maximum)
                    : Variable(id, name, DataType::DOUBLE) {
                    if (minimum.has_value() && maximum.has_value()) {
                        if (minimum.value().getValue() > maximum.value().getValue()) {
                            throw invalid_argument("Minimum value must be less than or equal to maximum value!");
                        }
                    }

                    this->minimum = minimum;
                    this->maximum = maximum;
                }

                optional<Value::Double> getMinimum() const { return minimum; }

                optional<Value::Double> getMaximum() const { return maximum; }
        };

        class Integer: public Variable {
            private:
                optional<Value::Integer> minimum;
                optional<Value::Integer> maximum;

            public:
                Integer(long id, string name, optional<Value::Integer> minimum, optional<Value::Integer> maximum)
                    : Variable(id, name, DataType::INTEGER) {
                    if (minimum.has_value() && maximum.has_value()) {
                        if (minimum.value().getValue() > maximum.value().getValue()) {
                            throw invalid_argument("Minimum value must be less than or equal to maximum value!");
                        }
                    }

                    this->minimum = minimum;
                    this->maximum = maximum;
                }

                optional<Value::Integer> getMinimum() const { return minimum; }

                optional<Value::Integer> getMaximum() const { return maximum; }
        };

        class Binary: public Variable {
            public:
                Binary(long id, string name): Variable(id, name, DataType::BINARY) {}
        };

    }  // namespace Variable

}  // namespace Model

#endif  // __VARIABLE_HPP__
