#ifndef __VALUE_HPP__
#define __VALUE_HPP__

#include <stdexcept>
#include <type_traits>
using namespace std;

namespace Model {

    enum class DataType { DOUBLE, INTEGER, BINARY };

    namespace Value {

        template<typename T>
        class Value {
            private:
                T value;
                DataType data_type;

            public:
                Value(T value): value(value) {
                    if constexpr (is_same_v<T, double>) {
                        this->data_type = DataType::DOUBLE;
                    } else if constexpr (is_same_v<T, int>) {
                        this->data_type = DataType::INTEGER;
                    } else if constexpr (is_same_v<T, bool>) {
                        this->data_type = DataType::BINARY;
                    }

                    throw invalid_argument("Invalid data type! Valid values are double, int, and bool.");
                }

                DataType getDataType() const { return this->data_type; }

                T getValue() const { return this->value; }
        };

        using Double = Value<double>;
        using Integer = Value<int>;
        using Boolean = Value<bool>;

    }  // namespace Value

}  // namespace Model

#endif  // __VALUE_HPP__
