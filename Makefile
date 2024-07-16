CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -gdwarf-4 -fstandalone-debug -O0
EXTRA_CXX_FLAGS=-Wall -Wextra -Werror -pedantic -Wno-error=unused-parameter

exec: bin/exec
tests: bin/tests
reset data: bin/reset

bin/exec: ./includes/table.hpp src/main.cc
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(EXTRA_CXX_FLAGS) ./src/table.cc ./src/main.cc -o bin/exec

bin/tests: src/tests.cpp
	$(CXX) $(CXXFLAGS) src/tests.cc -o bin/tests

bin/reset:
	./workspaces/cool-db/data/reset_data.sh


.DEFUALT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/*