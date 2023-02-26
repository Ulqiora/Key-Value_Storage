CC=g++
BD=../build
GCOV_REPORT_FOLDER=$(BD)
CXX_FLAGS=-c -std=c++17 -Wall -Werror -Wextra -Wfloat-equal -Warray-bounds -Wshadow -pedantic
LCOVFLAGS=-fprofile-arcs -ftest-coverage
GTESTFLAGS=-lgtest

ifeq ($(shell uname -s), Linux)
	GTESTFLAGS+= -lpthread -lrt
endif

all: clean start

./$(BD)/%.o:%.cc
	$(CC) $(CXX_FLAGS) $< -o $@

./$(BD)/%.o:*/%.cc
	$(CC) $(CXX_FLAGS) $< -o $@
 
./$(BD)/%.o: */*/%.cc
	$(CC) $(CXX_FLAGS) $< -o $@

./$(BD)/%.o: */*/*/%.cc
	$(CC) $(CXX_FLAGS) $< -o $@

#				Libraries
BTREE_SOURCES=$(shell find $(PWD)/Project/Model/BTree $(PWD)/Project/Model $(PWD)/Project/Model/ThreadsDel -maxdepth 1 -iname '*.cc')
BTREE_FILENAMES=$(shell basename -a $(BTREE_SOURCES))
BTREE_OBJECTS=$(addprefix $(BD)/,$(BTREE_FILENAMES:.cc=.o))

SELF_BALANCING_BINARY_SEARCH_TREE_SOURCES=$(shell find $(PWD)/Project/Model/SelfBalancingBinarySearchTree $(PWD)/Project/Model $(PWD)/Project/Model/ThreadsDel -maxdepth 1 -iname '*.cc')
SELF_BALANCING_BINARY_SEARCH_TREE_FILENAMES=$(shell basename -a $(SELF_BALANCING_BINARY_SEARCH_TREE_SOURCES))
SELF_BALANCING_BINARY_SEARCH_TREE_OBJECTS=$(addprefix $(BD)/,$(SELF_BALANCING_BINARY_SEARCH_TREE_FILENAMES:.cc=.o))

HASH_TABLE_SOURCES=$(shell find $(PWD)/Project/Model $(PWD)/Project/Model/HashTable $(PWD)/Project/Model/ThreadsDel -maxdepth 1 -iname '*.cc')
HASH_TABLE_FILENAMES=$(shell basename -a $(HASH_TABLE_SOURCES))
HASH_TABLE_OBJECTS=$(addprefix $(BD)/,$(HASH_TABLE_FILENAMES:.cc=.o))

#              Файлы для основного проекта
PROJECT_FILES_SOURCES=$(shell find $(PWD)/Project  -iname '*.cc')
PROJECT_FILES_FILENAMES=$(shell basename -a $(PROJECT_FILES_SOURCES))
PROJECT_FILES_OBJECTS=$(addprefix $(BD)/,$(PROJECT_FILES_FILENAMES:.cc=.o))

TESTS_FILES_SOURCES=$(shell find $(PWD)/Tests $(PWD)/Project/Model -iname '*.cc')
TESTS_FILES_FILENAMES=$(shell basename -a $(TESTS_FILES_SOURCES))
TESTS_FILES_OBJECTS=$(addprefix $(BD)/,$(TESTS_FILES_FILENAMES:.cc=.o))

./$(BD)/btree.a:$(BTREE_OBJECTS)
	ar rcs $(BD)/$@ $^
./$(BD)/sbbst.a:$(SELF_BALANCING_BINARY_SEARCH_TREE_OBJECTS)
	ar rcs $(BD)/$@ $^
./$(BD)/hash_table.a:$(HASH_TABLE_OBJECTS)
	ar rcs $(BD)/$@ $^

tests:$(TESTS_FILES_OBJECTS)
	$(CC) -g  $^ -o $(BD)/$@ $(GTESTFLAGS)

run: tests
	./$(BD)/tests

start:$(PROJECT_FILES_OBJECTS) ./$(BD)/btree.a ./$(BD)/sbbst.a ./$(BD)/hash_table.a
	$(CC) -g  $^ -o $(BD)/$@ 
	./$(BD)/$@

gcov_report: clean
	g++ --coverage $(TESTS_FILES_SOURCES) -o test -lgtest -std=c++17
	./test
	lcov -t "test" --no-external -o test.info -c -d ./
	genhtml -o report test.info
	open ./report/index.html

check: clean tests
	 cp -f ../materials/linters/.clang-format .clang-format
	clang-format -i $(PROJECT_FILES_SOURCES)
	 clang-format -n $(PROJECT_FILES_SOURCES)
	 cppcheck --language=c++ --enable=all --suppressions-list=suppresionlist.cfg $(PROJECT_FILES_SOURCES)
	 rm -rf .clang-format
	 CK_FORK=no leaks --atExit -- ./../build/tests

clean:
	rm -rf $(BD)/*
	rm -rf $(BD)/*.*
	rm -rf run test *.a *.o
	rm -rf *.gcda *.gcno *.info
	rm -rf ./report
	rm -rf Tests/Examples/out.txt
