CC=g++
BD=../build
CXX_FLAGS=-c -std=c++17 #-g -Wall -Werror -Wextra -Wfloat-equal -Warray-bounds 
LCOVFLAGS=-fprofile-arcs -ftest-coverage
GTESTFLAGS=-lgtest

ifeq ($(shell uname -s), Linux)
	GTESTFLAGS+= -lpthread -lrt
endif
#              Файлы для основного проекта
PROJECT_FILES_SOURCES= main_debug.cpp DataS21Student.cpp Btree.cpp
PROJECT_FILES_SOURCES_DEBUG= main_debug.cpp Model/DataS21Student.cpp Model/BTree/Btree.cpp
PROJECT_FILES_OBJECTS=$(addprefix $(BD)/,$(PROJECT_FILES_SOURCES:.cpp=.o))

all: clean start

./$(BD)/%.o:%.cpp
	$(CC) $(CXX_FLAGS) $< -o $@

./$(BD)/%.o:*/%.cpp
	$(CC) $(CXX_FLAGS) $< -o $@
 
./$(BD)/%.o: */*/%.cpp
	$(CC) $(CXX_FLAGS) $< -o $@

./$(BD)/%.o: */*/*/%.cpp
	$(CC) $(CXX_FLAGS) $< -o $@

start:$(PROJECT_FILES_OBJECTS)
	$(CC) -g  $^ -o $(BD)/$@ 
	./$(BD)/$@

debug:$(PROJECT_FILES_SOURCES_DEBUG)
	$(CC) -g  $^ -o $(BD)/$@ 

tests: clean test_exe
	./$(BD)/test

test_exe:$(TESTS_FILES_OBJECTS)
	$(CC) -g  $^ -o $(BD)/test   $(GTESTFLAGS)

clean:
	rm -rf $(BD)/*.*
	rm -rf $(BD)/*