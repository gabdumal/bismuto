#ifndef __VARIABLE_HPP__
#define __VARIABLE_HPP__

#include <optional>
#include <stdexcept>
#include <string>

#include "../data_type.hpp"

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

                long getId() const { return id; }

                string getName() const { return name; }

                DataType getDataType() const { return data_type; }
        };

        class Double: public Variable {
            private:
                optional<double> minimum;
                optional<double> maximum;

            public:
                Double(long id, string name, optional<double> minimum, optional<double> maximum): Variable(id, name, DataType::DOUBLE) {
                    if (minimum.has_value() && maximum.has_value()) {
                        if (minimum.value() > maximum.value()) {
                            throw invalid_argument("Minimum value must be less than or equal to maximum value!");
                        }
                    }

                    this->minimum = minimum;
                    this->maximum = maximum;
                }

                optional<double> getMinimum() const { return minimum; }

                optional<double> getMaximum() const { return maximum; }
        };

        class Integer: public Variable {
            private:
                optional<double> minimum;
                optional<double> maximum;

            public:
                Integer(long id, string name, optional<double> minimum, optional<double> maximum): Variable(id, name, DataType::INTEGER) {
                    if (minimum.has_value() && maximum.has_value()) {
                        if (minimum.value() > maximum.value()) {
                            throw invalid_argument("Minimum value must be less than or equal to maximum value!");
                        }
                    }

                    this->minimum = minimum;
                    this->maximum = maximum;
                }

                optional<double> getMinimum() const { return minimum; }

                optional<double> getMaximum() const { return maximum; }
        };

        class Binary: public Variable {
            public:
                Binary(long id, string name): Variable(id, name, DataType::BINARY) {}
        };

    }  // namespace Variable

}  // namespace Model

#endif  // __VARIABLE_HPP__
