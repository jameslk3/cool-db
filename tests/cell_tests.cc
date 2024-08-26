#include <gtest/gtest.h>
#include "models.hpp"

#include <fstream>

class CellTests : public ::testing::Test {
protected:
	Cell int_cell = Cell(1);
	Cell double_cell = Cell(2.0);
	Cell string_cell = Cell("test");

	// void SetUp() override {
	// 	Cell int_cell(1);
	// 	Cell double_cell(2.0);
	// 	Cell string_cell("test");
	// }

	// void TearDown() override {
	// 	delete int_cell;
	// 	delete double_cell;
	// 	delete string_cell;
	// }
};

TEST_F(CellTests, TestCellSerialization) {
	std::ofstream ofs{"/workspaces/cool-db/data/live/cell_test.txt"};
	int_cell.serialize(ofs);
	double_cell.serialize(ofs);
	string_cell.serialize(ofs);
	ofs.close();
}

TEST_F(CellTests, TestCellDeserialization) {
	std::ifstream ifs{"/workspaces/cool-db/data/live/cell_test.txt"};
	Cell int_cell_deserialized(CellValue(0));
	Cell double_cell_deserialized(CellValue(0));
	Cell string_cell_deserialized(CellValue(0));
	int_cell_deserialized.deserialize(ifs);
	double_cell_deserialized.deserialize(ifs);
	string_cell_deserialized.deserialize(ifs);
	ifs.close();

	EXPECT_EQ(std::get<int>(int_cell_deserialized.value), 1);
	EXPECT_EQ(std::get<double>(double_cell_deserialized.value), 2.0);
	EXPECT_EQ(std::get<std::string>(string_cell_deserialized.value), "test");
}