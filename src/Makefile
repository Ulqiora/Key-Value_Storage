CC=g++
BD=../build
CXX_FLAGS=-c -std=c++17 #-g -Wall -Werror -Wextra -Wfloat-equal -Warray-bounds 
LCOVFLAGS=-fprofile-arcs -ftest-coverage
GTESTFLAGS=-lgtest

ifeq ($(shell uname -s), Linux)
	GTESTFLAGS+= -lpthread -lrt
endif
#              Файлы для основного проекта
PROJECT_FILES_SOURCES= main_debug.cpp DataS21Student.cpp
PROJECT_FILES_OBJECTS=$(addprefix $(BD)/,$(PROJECT_FILES_SOURCES:.cpp=.o))

all: clean debug

./$(BD)/%.o:%.cpp
	$(CC) $(CXX_FLAGS) $< -o $@

./$(BD)/%.o:*/%.cpp
	$(CC) $(CXX_FLAGS) $< -o $@
 
./$(BD)/%.o: */*/%.cpp
	$(CC) $(CXX_FLAGS) $< -o $@

./$(BD)/%.o: */*/*/%.cpp
	$(CC) $(CXX_FLAGS) $< -o $@

debug:$(PROJECT_FILES_OBJECTS)
	$(CC) -g  $^ -o $(BD)/$@ 
	./$(BD)/$@
tests: clean test_exe
	./$(BD)/test

test_exe:$(TESTS_FILES_OBJECTS)
	$(CC) -g  $^ -o $(BD)/test   $(GTESTFLAGS)

clean:
	rm -rf $(BD)/*.*
	rm -rf $(BD)/*