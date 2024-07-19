#include "table.hpp"

#include <stdexcept>

// ----------------------- CONSTRUCTORS ---------------------- //
Table::Table(std::string name, std::vector<std::tuple<std::type_index, std::string>> columns) {
    this->name = name;
    for (auto column : columns) {
        column_types.push_back(std::get<0>(column));
        column_names.push_back(std::get<1>(column));
    }
    this->num_rows = 0;
    this->num_cols = columns.size();
}

// -------------------------- METHODS ------------------------ //
std::string Table::get_name() const {
    return this->name;
}

void Table::add_row(Row row) {
    // Make sure row has the same number of columns as the table
    if (row.cells.size() != this->num_cols) {
        throw std::runtime_error("Row has incorrect number of columns");
    }
    
    // Make sure the types of the cells in the row match the types of the columns in the table


    this->rows.push_back(row);
    this->num_rows++;
}


// -------------------------- UTILS -------------------------- //
std::ostream& operator<<(std::ostream& os, const Table& table) {
    // Check if table has been created (has columns)
    if (table.num_cols == 0) {
        throw std::runtime_error("Table has no columns");
    }

    // Print column types and names, in that order, separated by commas
    for (unsigned int i = 0; i < table.num_cols; ++i) {
        if (i != 0) {
            os << ",";
        }
        os << table.column_types.at(i).name() << " " << table.column_names.at(i);
    }

    // Print newline
    os << std::endl;

    // Check if table has rows
    if (table.num_rows == 0) {
        return os;
    }

    // Print row values
    for (unsigned int i = 0; i < table.num_rows; ++i) {
        for (unsigned int j = 0; j < table.num_cols; ++j) {
            if (j != 0) {
                os << ",";
            }
            os << table.rows.at(i).get_cell<std::string>(j).get_value();
        }
        os << std::endl;
    }

    return os;
}