#ifndef MODELS_HPP
#define MODELS_HPP

#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <memory>

// Types that a cell can hold, should match the types in the enum class ColumnType
using CellValue = std::variant<int, double, std::string>;

/*
------------------- Cell ------------------- //
This struct represents a cell in a table. It holds a value that can be one of the types in the CellValue variant.
*/
struct Cell {
	CellValue value;

	// Custom constructor to initialize the value
	Cell(const CellValue& value) : value(value) {}
	
};

/*
------------------- Row ------------------- //
This struct represents a row in a table. It holds a vector of shared pointers to cells.
*/
struct Row {
	std::vector<Cell> cells;

	// Custom constructor to fill the cells vector
	Row(const std::vector<Cell>& cells) {
		for (const auto& cell : cells) {
			this->cells.push_back(cell);
		}
	}

	// Getter
	std::vector<Cell> get_cells() const {
		return cells;
	}
};

/*
------------------- Column ------------------- //
This struct represents a column in a table. All it really does is hold the type and name of a column.
*/
enum class ColumnType {
		INT,
		DOUBLE,
		STRING
};
struct Column {
	ColumnType 	type;
	std::string name;
};

/*
------------------- Table ------------------- //
This class represents a table in the database. It will become a file on disk. It will handle type checking and most of the data manipulation.
*/
class Table {
private:

	std::string name;
	std::vector<Column> columns;
	std::vector<Row> rows;
	unsigned int num_rows;
	unsigned int num_cols;

public:

	// Custom constructor with name and columns where columns holds data type and column name, respectively
	Table(const std::string& name, const std::vector<std::pair<ColumnType, std::string>>& columns) {
		this->name = name;
		this->num_rows = 0;
		this->num_cols = columns.size();
		for (const auto& column : columns) {
				this->columns.push_back({ column.first, column.second });
		}
	}

	// Function to add a row to the table
	void add_row(const std::vector<Cell>& cells) {
		// Validate the row
		if (!validate_row(cells)) {
			throw std::invalid_argument("Row does not match the types of the columns");
		}
		
		// If cells are valid, construct a new row and add it to the table
		rows.push_back(Row(cells));
		num_rows++;
	}

	bool validate_cell(const Cell& cell, ColumnType type) {
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

	bool validate_row(const std::vector<Cell>& cells) {
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

	// Getters
	std::string get_name() const {
		return name;
	}
	unsigned int get_num_rows() const {
		return num_rows;
	}
	unsigned int get_num_cols() const {
		return num_cols;
	}
	std::vector<Column> get_columns() const {
		return columns;
	}
	std::vector<Row> get_rows() const {
		return rows;
	}
};

/*
------------------- Database ------------------- //
This class serves as a manager for the database, or a layer of abstraction on top of the file system.
*/
class Database {
public:
private:
};

#endif