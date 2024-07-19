#include <gtest/gtest.h>
#include "models.hpp"

#include <iostream>

class TableTests : public ::testing::Test {
protected:
	Table* table;

	void SetUp() override {
		std::vector<std::pair<ColumnType, std::string>> columns = {
			{ColumnType::INT, "int_col"},
			{ColumnType::DOUBLE, "double_col"},
			{ColumnType::STRING, "string_col"},
		};
		std::string name = "test_table";
		table = new Table(name, std::vector<std::pair<ColumnType, std::string>>(columns));
	}

	void TearDown() override {
		delete table;
	}
};

TEST_F(TableTests, TestTableConstructor) {
	EXPECT_EQ(table->get_name(), "test_table");
	EXPECT_EQ(table->get_num_rows(), 0);
	EXPECT_EQ(table->get_num_cols(), 3);
	EXPECT_EQ(table->get_columns()[0].type, ColumnType::INT);
	EXPECT_EQ(table->get_columns()[0].name, "int_col");
	EXPECT_EQ(table->get_columns()[1].type, ColumnType::DOUBLE);
	EXPECT_EQ(table->get_columns()[1].name, "double_col");
	EXPECT_EQ(table->get_columns()[2].type, ColumnType::STRING);
	EXPECT_EQ(table->get_columns()[2].name, "string_col");
}

TEST_F(TableTests, TestAddRow) {
	std::vector<Cell> cells = {
		Cell(1),
		Cell(2.0),
		Cell("test"),
	};
	table->add_row(cells);
	EXPECT_EQ(table->get_num_rows(), 1);
	EXPECT_EQ(std::get<int>(table->get_rows()[0].get_cells()[0].value), 1);
	EXPECT_EQ(std::get<double>(table->get_rows()[0].get_cells()[1].value), 2.0);
	EXPECT_EQ(std::get<std::string>(table->get_rows()[0].get_cells()[2].value), "test");

	// Test adding a row with invalid types
	std::vector<Cell> invalid_cells = {
		Cell(1),
		Cell("test"),
		Cell(2.0),
	};
	EXPECT_THROW(table->add_row(invalid_cells), std::invalid_argument);
}