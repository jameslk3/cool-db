#include "models.hpp"

#include <stdexcept>
#include <fstream>

// ----------------------- CONSTRUCTOR ---------------------- //
Table::Table(const std::string& name, const std::vector<std::pair<ColumnType, std::string>>& columns) {
	this->name = name;
	this->num_rows = 0;
	this->num_cols = columns.size();
	for (const auto& column : columns) {
					this->columns.push_back(Column(column.first, column.second));
	}
}

//TODOs: See note at bottom
Table::Table(const std::string& file_path) {
	std::ifstream ifs{file_path};

	//Check if file is open
	if (!ifs.is_open()) {
		throw std::runtime_error("File could not be opened");
	}

	//Initializing table name
	std::string table_name;
	try {
		ifs >> table_name;
		this->name = table_name;
	} catch (std::exception) {
		throw std::runtime_error("problem with table name");
	}
	
	//Initializing number of rows
	unsigned int rows;
	try {
		ifs >> rows;
		this->num_rows = rows;
	} catch (std::exception) {
		throw std::runtime_error("problem initializing number of rows");
	}

	//Initializing number of columns
	unsigned int columns;
	try {
		ifs >> columns;
		this->num_cols = columns;
	} catch (std::exception) {
		throw std::runtime_error("problem initializing number of columns");
	}
	
	//TODO: Create Columns
	//TODO: Create cells, put them into rows

}

// -------------------------- METHODS ------------------------ //
void Table::add_row(const std::vector<Cell>& cells) {
	// Validate the row
	if (!validate_row(cells)) {
		throw std::invalid_argument("Row does not match the types of the columns");
	}
	
	// If cells are valid, construct a new row and add it to the table
	rows.push_back(Row(cells));
	num_rows++;
}

bool Table::validate_cell(const Cell& cell, ColumnType type) {
	switch (type) {
	case ColumnType::INT:
		return std::holds_alternative<int>(cell.value);
	case ColumnType::DOUBLE:
		return std::holds_alternative<double>(cell.value);
	case ColumnType::STRING:
		return std::holds_alternative<std::string>(cell.value);
	default:
		return false;
	}
}

bool Table::validate_row(const std::vector<Cell>& cells) {
	// Check if the types of the cells match the types of the columns
	if (cells.size() != num_cols) {
		return false;
	}

	// Check the types of the cells, they could hold any of the types in the CellValue variant, so we need to check if they match with ColumnType
	for (unsigned int i = 0; i < cells.size(); i++) {
		if (!validate_cell(cells[i], columns[i].type)) {
			return false;
		}
	}
	return true;
}


// -------------------------- UTILS -------------------------- //
//TODOs: see bottom
std::ostream& operator<<(std::ostream& os, const Table& table) {
	// Check if table has been created (has columns)
	if (table.get_num_cols() == 0) {
			throw std::runtime_error("Table has no columns");
	}

	// Print column types and names, in that order, separated by commas
	for (unsigned int i = 0; i < table.num_cols; ++i) {
			if (i != 0) {
					os << ",";
			}
		// Use the overloaded operator<< for Column
		os << table.columns.at(i);
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
				// Use the overloaded operator<< for Cell to visit the variant in type safe way
				os << table.rows.at(i).cells.at(j);
		}
		os << std::endl;
	}

	return os;

	//TODO: Change to fit new table format
}