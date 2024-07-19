#include "models.hpp"

#include <fstream>

void Database::add_table(Table &table) const {
	std::string table_path = DB_PATH + "/" + table.get_name() + ".tbl";
	std::ofstream table_file(table_path);
	
	// Logic to write the table to the file
	// TODO

	table_file.close();
}

void Database::remove_table(std::string table_name) const {
	std::string table_path = DB_PATH + "/" + table_name + ".tbl";

	// Check if the file exists before removing it
	if (std::ifstream(table_path)) {
		std::remove(table_path.c_str());
	}
	
	throw std::invalid_argument("Table does not exist");
}