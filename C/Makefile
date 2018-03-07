CFLAGS += -std=c99 -g -Wall
run: test
	./test

clean: 
	rm test *.o linkedlist/*.o binarytree/*.o

test: linkedlist/list.o binarytree/bintree.o test.o
	gcc -o $@ $^ $(CFLAGS)
