#include "models.hpp"

#include <iostream>

int main() {
		Table table("/workspaces/cool-db/data/seed/sample_table_1.txt");
		std::cout << table;
}