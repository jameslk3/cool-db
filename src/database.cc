#include "models.hpp"

#include <stdexcept>
#include <fstream>
#include <filesystem>


// ----------------------- CONSTRUCTOR ---------------------- //
Database::Database(const std::string& path) {
	// If a directory in the same path as already exists, create the database in that directory
	if (std::filesystem::exists(std::filesystem::path(path))) {
		this->path = path;
	} else {
		// Create the database directory
		std::filesystem::create_directory(std::filesystem::path(path));
		this->path = path;
	}
}

// ----------------------- METHODS ---------------------- //
void Database::add_table(Table& table) const {
	// Check if the table already exists
	if (std::filesystem::exists(std::filesystem::path(this->path + "/" + table.get_name()  + ".txt"))) {
		throw std::invalid_argument("Table already exists");
	}

	// Create the table file
	std::ofstream ofs{this->path + "/" + table.get_name() + ".txt"};
	if (!ofs.is_open()) {
		throw std::runtime_error("File could not be opened");
	}

	// Write the table name
	ofs << table.get_name() << std::endl;
	// Write the number of rows
	ofs << table.get_num_rows() << std::endl;
	// Write the number of columns
	ofs << table.get_num_cols() << std::endl;
	// Write the columns
	for (const auto& column : table.get_columns()) {
		ofs << column << ", ";
	}
	ofs << std::endl;
	// Write the rows
	for (const auto& row : table.get_rows()) {
		ofs << row << std::endl;
	}
}