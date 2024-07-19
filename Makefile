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
reset data: bin/reset

bin/exec: ./includes/table.hpp src/main.cc
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(EXTRA_CXX_FLAGS) ./src/table.cc ./src/main.cc -o bin/exec

bin/tests: ./includes/models.hpp tests/table_tests.cc
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(LDFLAGS) tests/table_tests.cc -o bin/tests $(GTEST_LIBS)

bin/reset:
	./workspaces/cool-db/data/reset_data.sh

.PHONY: clean exec tests

clean:
	rm -fr bin/*