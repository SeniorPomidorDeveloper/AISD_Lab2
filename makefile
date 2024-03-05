COMPILLER = gcc

PATH_LIBS = ./libs

PATH_STACK_LIB_FILES = CyclicStack

NAME_VECTOR_FILE = CyclicStack_vector.c
NAME_LIST_FILE = CyclicStack_list.c

NAME_OBJECT_FILE = CyclicStack

NAME_RUN_FILE = run

all: compile_vector

compile_vector: make_vector compile_main compile

compile_list: make_list compile_main compile

compile_vector_dynamic: install make_vector_dynamic compile_main compile_dynamic install

compile_list_dynamic: install make_list_dynamic compile_main compile_dynamic install

compile:
	$(COMPILLER) *.o -L./ -l:$(NAME_OBJECT_FILE).a -o $(NAME_RUN_FILE)
	rm ./$(NAME_OBJECT_FILE).a
	rm ./*.o

make_vector:
	make -f $(PATH_LIBS)/$(PATH_STACK_LIB_FILES)/makefile creat_vector ARG=$(PATH_LIBS)/$(PATH_STACK_LIB_FILES)/

make_list:
	make -f $(PATH_LIBS)/$(PATH_STACK_LIB_FILES)/makefile creat_list ARG=$(PATH_LIBS)/$(PATH_STACK_LIB_FILES)/

compile_dynamic:
	$(COMPILLER) *.o -L./ -l:$(NAME_OBJECT_FILE).so -o $(NAME_RUN_FILE) -ldl
	rm ./*.o

make_vector_dynamic:
	make -f $(PATH_LIBS)/$(PATH_STACK_LIB_FILES)/makefile creat_vector_dynamic ARG=$(PATH_LIBS)/$(PATH_STACK_LIB_FILES)/

make_list_dynamic:
	make -f $(PATH_LIBS)/$(PATH_STACK_LIB_FILES)/makefile creat_list_dynamic ARG=$(PATH_LIBS)/$(PATH_STACK_LIB_FILES)/

install:
	export LD_LIBRARY_PATH=.:LD_LIBRARY_PATH

compile_main:
	$(COMPILLER) -c main.c
	$(COMPILLER) -c game.c
	$(COMPILLER) -c ./libs/gets.c
	$(COMPILLER) -c ./libs/compares.c
