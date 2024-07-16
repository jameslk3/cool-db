#include "table.hpp"

#include <stdexcept>

std::ostream& operator<<(std::ostream& os, const Table& table) {
    // error checking
    if (table.num_rows_ == 0 || table.num_cols_ == 0) {
        throw std::runtime_error("no table yet");
    }

    //printing out table
    for (unsigned int i = 0; i < table.num_rows_; ++i) {
        for (unsigned int j = 0; j < table.num_cols_; ++j) {
            if (j != 0) {
                os << ",";
            }
            os << table.rows_.at(i)[j];
        }
        os << std::endl;
    }
    return os;

}