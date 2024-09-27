#ifndef __DEFINITIONS_HPP__
#define __DEFINITIONS_HPP__

using namespace std;

namespace Model {

    using Id = unsigned long;

    enum class DataType { DOUBLE,
                          INTEGER,
                          BINARY };

    using Coefficient = double;

}  // namespace Model

#endif  // __DEFINITIONS_HPP__
