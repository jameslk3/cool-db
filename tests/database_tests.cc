#include <gtest/gtest.h>
#include "models.hpp"

#include <iostream>

class DatabaseTests : public ::testing::Test {
protected:
	Database* db;

	void SetUp() override {
		db = new Database("/workspaces/cool-db/data/live");
	}

	void TearDown() override {
		delete db;
	}
};

TEST_F(DatabaseTests, TestDatabaseConstructor) {
	EXPECT_EQ(db->get_path(), "/workspaces/cool-db/data/live");
}

TEST_F(DatabaseTests, TestAddTable) {
	Table table("/workspaces/cool-db/data/seed/sample_table_1.txt");
	table.set_name("created_table");
	db->add_table(table);
}