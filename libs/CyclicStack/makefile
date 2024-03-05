COMPILLER = gcc

PATH_LIB_FILES = $(ARG)

NAME_VECTOR_FILE = CyclicStack_vector.c
NAME_LIST_FILE = CyclicStack_list.c

NAME_OBJECT_FILE = CyclicStack

all: creat_vector

make_object_file_vector:
	$(COMPILLER) -c $(PATH_LIB_FILES)$(NAME_VECTOR_FILE) -o $(NAME_OBJECT_FILE).o -fPIC

make_object_file_list:
	$(COMPILLER) -c $(PATH_LIB_FILES)$(NAME_LIST_FILE) -o $(NAME_OBJECT_FILE).o -fPIC

creat_vector: make_object_file_vector
	ar r $(NAME_OBJECT_FILE).a $(NAME_OBJECT_FILE).o
	rm $(NAME_OBJECT_FILE).o

creat_list: make_object_file_list
	ar r $(NAME_OBJECT_LIST_FILE).a $(NAME_OBJECT_FILE).o
	rm $(NAME_OBJECT_FILE).o

creat_vector_dynamic: make_object_file_vector
	$(COMPILLER) -shared -o $(NAME_OBJECT_FILE).so $(NAME_OBJECT_FILE).o
	rm $(NAME_OBJECT_FILE).o

creat_list_dynamic: make_object_file_list
	$(COMPILLER) -shared -o $(NAME_OBJECT_FILE).so $(NAME_OBJECT_FILE).o
	rm $(NAME_OBJECT_FILE).o