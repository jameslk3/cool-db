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

	//Creating Columns
	std::vector<Column> cols;
	for (unsigned int i = 0; i < this->num_cols; ++i) {
		ColumnType type;
		std::string name;
		try {
			//Retrieving the ColumnType
			std::string type_as_str;
			ifs >> type_as_str;
			type_as_str = type_as_str.substr(1, type_as_str.size() - 2);
			if (type_as_str == "STRING") {
				type = ColumnType::STRING;
			} else if (type_as_str == "INT") {
				type = ColumnType::INT;
			} else if (type_as_str == "DOUBLE") {
				type = ColumnType::DOUBLE;
			} else {
				throw std::runtime_error("");
			}
			
			//Retrieving name of the column
			ifs >> name;
			name = name.substr(0, name.size() - 2);

			//Create the column, add it to vector
			Column col(type, name);
			cols.push_back(col);

		} catch (std::exception) {
			throw std::runtime_error("Creating columns failed");
		}
	}
	this->columns = cols; //assigning cols to columns

	//Create cells, put them into rows
	std::vector<Row> rows_vector;
	for (unsigned int i = 0; i < num_rows; ++i) {
		std::vector<Cell> cell_vector;
		for (unsigned int j = 0; j < num_cols; ++j) {
			try {
				//Read in input as string
				std::string input;
				ifs >> input;
				//Continues reading in input until a comma is reached
				while (input.substr(input.size() - 1, std::string::npos) != ",") {
					std::string input_continued;
					ifs >> input_continued;
					input += " " + input_continued;
				}
				//Convert input to integer or double (or don't convert) depending on ColumnType
				//Then create cell and add cell to cell vector
				if (this->columns.at(j).type == ColumnType::INT) {
					int input_read = std::stoi(input);
					Cell cell(input_read);
					cell_vector.push_back(cell);
				} else if (this->columns.at(j).type == ColumnType::DOUBLE) {
					double input_read = std::stod(input);
					Cell cell(input_read);
					cell_vector.push_back(cell);
				} else {
					Cell cell(input.substr(0, input.size() - 1));
					cell_vector.push_back(cell);
				}
			} catch (std::exception) {
				throw std::runtime_error("error creating cell");
			}
		}
		//Create row using cell_vector, add row to rows_vector
		Row row(cell_vector);
		rows_vector.push_back(row);
	}
	this->rows = rows_vector; //assign rows the value of rows_vector
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
std::ostream& operator<<(std::ostream& os, const Table& table) {
	// Check if table has been created (has columns)
	if (table.get_num_cols() == 0) {
			throw std::runtime_error("Table has no columns");
	}

	// Start of file
	os << table.name << std::endl;
	os << table.num_rows << std::endl;
	os << table.num_cols << std::endl;

	// Print column types and names, in that order, separated by commas
	for (unsigned int i = 0; i < table.num_cols; ++i) {
		// Use the overloaded operator<< for Column
		os << table.columns.at(i);
		
		os << ", ";
	}

	// Print newline
	os << std::endl;

	// Check if table has rows
	if (table.num_rows == 0) {
			return os;
	}

	// Print row values
	for (unsigned int i = 0; i < table.num_rows; ++i) {
		// Use the overloaded operator<< for Row
		os << table.rows.at(i);
		os << std::endl;
	}

	return os;
}

bool operator==(const Table& lhs, const Table& rhs) {
	// Check if the tables have the same number of rows and columns
	if (lhs.get_num_rows() != rhs.get_num_rows() || lhs.get_num_cols() != rhs.get_num_cols()) {
		return false;
	}

	// Check if the tables have the same name
	if (lhs.get_name() != rhs.get_name()) {
		return false;
	}

	// Check if the tables have the same columns
	for (unsigned int i = 0; i < lhs.get_num_cols(); ++i) {
		if (lhs.get_columns().at(i).type != rhs.get_columns().at(i).type || lhs.get_columns().at(i).name != rhs.get_columns().at(i).name) {
			return false;
		}
	}

	// Check if the tables have the same rows
	for (unsigned int i = 0; i < lhs.get_num_rows(); ++i) {
		for (unsigned int j = 0; j < lhs.get_num_cols(); ++j) {
			if (lhs.get_rows().at(i).get_cells().at(j).value != rhs.get_rows().at(i).get_cells().at(j).value) {
				return false;
			}
		}
	}

	return true;
}