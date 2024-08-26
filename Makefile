CXX = clang++
INCLUDES = -Iincludes/ -I/usr/local/include
CXXFLAGS = -std=c++20

# Google Test libraries
GTEST_LIBS = -lgtest -lgtest_main -pthread
LDFLAGS = -L/usr/local/lib

# Default target
.DEFAULT_GOAL := exec

exec: bin/exec
tests: bin/tests
reset: bin/reset

SOURCE_FILES = ./src/main.cc ./src/database.cc ./src/table.cc ./src/row.cc ./src/column.cc ./src/cell.cc
TEST_FILES = tests/database_tests.cc tests/table_tests.cc tests/cell_tests.cc

bin/exec: ./includes/models.hpp $(SOURCE_FILES)
	$(CXX) $(INCLUDES) $(CXXFLAGS) ./src/main.cc ./src/database.cc ./src/table.cc ./src/row.cc ./src/column.cc ./src/cell.cc -o bin/exec

bin/tests: ./includes/models.hpp $(TEST_FILES) $(SOURCE_FILES)
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(LDFLAGS) $(TEST_FILES) ./src/database.cc ./src/table.cc ./src/row.cc ./src/column.cc ./src/cell.cc -o bin/tests $(GTEST_LIBS)

bin/reset:
	./data/reset_data.sh

.PHONY: clean exec tests

clean:
	rm -fr bin/*