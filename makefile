OPTS=-fno-pie -no-pie -fno-builtin -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Werror -std=c17 -Wpedantic -O0 -g


all: lab09_1 lab09_2

lab09_2: lab09_2.o
	gcc $^ -o $@ $(OPTS)

lab09_2.o: lab09_2.c
	gcc $< -c -o $@ $(OPTS)

lab09_1: lab09_1.o
	gcc $^ -o $@ $(OPTS)

lab09_1.o: lab09_1.c
	gcc $< -c -o $@ $(OPTS)

clean:
	rm -f *.o lab09_1 lab09_2
