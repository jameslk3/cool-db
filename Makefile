CXX=clang++
CXXFLAGS=-std=c++20

exec: bin/exec
tests: bin/tests

bin/exec: src/main.cc
	$(CXX) $(CXXFLAGS) src/main.cc -o bin/exec

bin/tests: src/tests.cpp
	$(CXX) $(CXXFLAGS) src/tests.cc -o bin/tests

.DEFUALT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/*