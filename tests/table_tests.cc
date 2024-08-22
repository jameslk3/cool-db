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
		table = new Table(name, columns);
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
	TableEditor editor(*table);
	std::vector<Cell> cells = {
		Cell(1),
		Cell(2.0),
		Cell("test"),
	};
	editor.add_row(cells);
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
	EXPECT_THROW(editor.add_row(invalid_cells), std::invalid_argument);
}

TEST_F(TableTests, TestPrintTable) {
	TableEditor editor(*table);
	std::vector<Cell> cells = {
		Cell(1),
		Cell(2.6969),
		Cell("test"),
	};
	editor.add_row(cells);
	std::cout << *table << std::endl;
}

TEST_F(TableTests, TestTableConstructorCompatability) {
	std::vector<std::pair<ColumnType, std::string>> columns = {
		{ColumnType::STRING, "animals"},
		{ColumnType::STRING, "action"},
		{ColumnType::DOUBLE, "number"},
	};
	Table entered_table = Table("sample_table_1", columns);
	TableEditor editor(entered_table);

	std::vector<Cell> row_1 = {
		Cell("chickens"),
		Cell("run away"),
		Cell(3.14),
	};
	editor.add_row(row_1);

	std::vector<Cell> row_2 = {
		Cell("turtles"),
		Cell("waddle closer"),
		Cell(3.16),
	};
	editor.add_row(row_2);

	Table table_from_file = Table("/workspaces/cool-db/data/seed/sample_table_1.txt");
	EXPECT_TRUE(entered_table == table_from_file);
}

TEST_F(TableTests, TestEditExisting) {
	Database db("/workspaces/cool-db/data/live");
	TableEditor* editor =  new TableEditor(db, "sample_table_1");
	std::vector<Cell> row = {
		Cell("cats"),
		Cell("jump"),
		Cell(2.71),
	};
	editor->add_row(row);
	EXPECT_EQ(editor->get_table().get_num_rows(), 3);
	EXPECT_EQ(std::get<std::string>(editor->get_table().get_rows()[2].get_cells()[0].value), "cats");
	EXPECT_EQ(std::get<std::string>(editor->get_table().get_rows()[2].get_cells()[1].value), "jump");
	EXPECT_EQ(std::get<double>(editor->get_table().get_rows()[2].get_cells()[2].value), 2.71);

	delete editor;

	EXPECT_THROW({ TableEditor editor(db, "non_existent_table"); }, std::runtime_error);
}