#include "db.hpp"
#include "table.hpp"

#include <fstream>

DB::DB()
{
}

DB::~DB()
{
}

void DB::add_table(Table &table) const
{
	std::string table_path = DB_PATH + "/" + table.get_name() + ".tbl";
	std::ofstream table_file(table_path);
	table_file << table;
	table_file.close();
}

