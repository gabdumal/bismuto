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
                string name;

            protected:
                Variable(string name): name(name) {}

            public:
                virtual ~Variable() = default;
                virtual DataType getDataType() const = 0;

                string getName() const { return name; }
        };

        class Double: public Variable {
            private:
                DataType data_type;
                optional<Value::Double> minimum;
                optional<Value::Double> maximum;

            public:
                Double(string name, optional<Value::Double> minimum, optional<Value::Double> maximum)
                    : Variable(name), data_type(DataType::DOUBLE) {
                    if (minimum.has_value() && maximum.has_value()) {
                        if (minimum.value().getValue() > maximum.value().getValue()) {
                            throw invalid_argument("Minimum value must be less than or equal to maximum value");
                        }
                    }

                    this->minimum = minimum;
                    this->maximum = maximum;
                }

                DataType getDataType() const override { return data_type; }

                optional<Value::Double> getMinimum() const { return minimum; }

                optional<Value::Double> getMaximum() const { return maximum; }
        };

        class Integer: public Variable {
            private:
                DataType data_type;
                optional<Value::Double> minimum;
                optional<Value::Double> maximum;

            public:
                Integer(string name, optional<Value::Double> minimum, optional<Value::Double> maximum)
                    : Variable(name), data_type(DataType::INTEGER) {
                    if (minimum.has_value() && maximum.has_value()) {
                        if (minimum.value().getValue() > maximum.value().getValue()) {
                            throw invalid_argument("Minimum value must be less than or equal to maximum value");
                        }
                    }

                    this->minimum = minimum;
                    this->maximum = maximum;
                }

                DataType getDataType() const override { return data_type; }

                optional<Value::Double> getMinimum() const { return minimum; }

                optional<Value::Double> getMaximum() const { return maximum; }
        };

        class Boolean: public Variable {
            private:
                DataType data_type;

            public:
                Boolean(string name): Variable(name), data_type(DataType::BOOLEAN) {}

                DataType getDataType() const override { return data_type; }
        };
    }  // namespace Variable

}  // namespace Model

#endif  // __VARIABLE_HPP__
