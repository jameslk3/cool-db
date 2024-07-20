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

	// Printer
	friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
	
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
	std::vector<Cell> get_cells() const { return cells; }
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

	// Custom constructor to initialize the type and name
	Column(ColumnType type, const std::string& name) : type(type), name(name) {}

	// Printer
	friend std::ostream& operator<<(std::ostream& os, const Column& column);
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
	Table(const std::string& name, const std::vector<std::pair<ColumnType, std::string>>& columns);

	// Function to add a row to the table
	void add_row(const std::vector<Cell>& cells);

	bool validate_cell(const Cell& cell, ColumnType type);

	bool validate_row(const std::vector<Cell>& cells);

	// Getters
	std::string get_name() const { return name; }
	unsigned int get_num_rows() const { return num_rows; }
	unsigned int get_num_cols() const { return num_cols; }
	std::vector<Column> get_columns() const { return columns; }
	std::vector<Row> get_rows() const { return rows; }

	// Friend function to overload the << operator for the Table class
	friend std::ostream& operator<<(std::ostream& os, const Table& table);
};

/*
------------------- Database ------------------- //
This class serves as a manager for the database, or a layer of abstraction on top of the file system.
*/
class Database {
private:

	std::string DB_PATH = "/workspaces/cool-db/data/live";

public:

	void add_table(Table &table) const;
	void remove_table(std::string table_name) const;

};

#endif