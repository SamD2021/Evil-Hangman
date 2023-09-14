CC = gcc
CFLAGS = -Wall --std=c99 -g
OBJECTS = main.o my_string.o generic_vector.o associativearray.o
TOBJECTS = unit_test.o test_def.o

string_driver: $(OBJECTS)
	$(CC) $(CFLAGS) -o string_driver $(OBJECTS)
unit_test: my_string.o unit_test.o test_def.o
	$(CC) $(CFLAGS) -o unit_test unit_test.o test_def.o my_string.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
associativearray.o:associativearray.c associativearray.h status.h
	$(CC) $(CFLAGS) associativearray.c -o associativearray.o -c
my_string.o: my_string.h my_string.c status.h
	$(CC) $(CFLAGS) -c my_string.c
generic_vector.o: generic.h generic_vector.h generic_vector.c status.h
	$(CC) $(CFLAGS) -c generic_vector.c
clean:
	rm string_driver unit_test $(OBJECTS) $(TOBJECTS)

