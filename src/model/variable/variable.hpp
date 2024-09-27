#ifndef __VARIABLE_HPP__
#define __VARIABLE_HPP__

#include <optional>
#include <stdexcept>
#include <string>

#include "../definitions.hpp"

using namespace std;

namespace Model {

    namespace Variable {

        class Variable {
            private:
                Id id;
                string name;
                DataType data_type;

            protected:
                optional<double> minimum = nullopt;
                optional<double> maximum = nullopt;

                Variable(Id id, string name, DataType data_type): id(id), name(name), data_type(data_type) {}

            public:
                virtual ~Variable() = default;

                Id getId() const { return id; }

                string getName() const { return name; }

                DataType getDataType() const { return data_type; }

                optional<double> getMinimum() const { return minimum; }

                optional<double> getMaximum() const { return maximum; }
        };

        class Double: public Variable {
            public:
                Double(Id id, string name, optional<double> minimum, optional<double> maximum): Variable(id, name, DataType::DOUBLE) {
                    if (minimum.has_value() && maximum.has_value()) {
                        if (minimum.value() > maximum.value()) {
                            throw invalid_argument("Minimum value must be less than or equal to maximum value!");
                        }
                    }

                    this->minimum = minimum;
                    this->maximum = maximum;
                }
        };

        class Integer: public Variable {
            public:
                Integer(Id id, string name, optional<double> minimum, optional<double> maximum): Variable(id, name, DataType::INTEGER) {
                    if (minimum.has_value() && maximum.has_value()) {
                        if (minimum.value() > maximum.value()) {
                            throw invalid_argument("Minimum value must be less than or equal to maximum value!");
                        }
                    }

                    this->minimum = minimum;
                    this->maximum = maximum;
                }
        };

        class Binary: public Variable {
            public:
                Binary(Id id, string name): Variable(id, name, DataType::BINARY) {}
        };

    }  // namespace Variable

}  // namespace Model

#endif  // __VARIABLE_HPP__
