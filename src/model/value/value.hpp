#ifndef __VALUE_HPP__
#define __VALUE_HPP__

namespace Model {

    enum class DataType { DOUBLE, INTEGER, BOOLEAN };

    namespace Value {

        class Value {
            public:
                virtual ~Value() = default;
                virtual DataType getDataType() const = 0;
        };

        class Double: public Value {
            private:
                DataType data_type;
                double value;

            public:
                Double(double value): data_type(DataType::DOUBLE), value(value) {}

                DataType getDataType() const override { return data_type; }

                double getValue() const { return value; }
        };

        class Integer: public Value {
            private:
                DataType data_type;
                int value;

            public:
                Integer(int value): data_type(DataType::INTEGER), value(value) {}

                DataType getDataType() const override { return data_type; }

                int getValue() const { return value; }
        };

        class Boolean: public Value {
            private:
                DataType data_type;
                bool value;

            public:
                Boolean(bool value): data_type(DataType::BOOLEAN), value(value) {}

                DataType getDataType() const override { return data_type; }

                bool getValue() const { return value; }
        };

    }  // namespace Value

}  // namespace Model

#endif  // __VALUE_HPP__
