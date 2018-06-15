SRC_FILES=main.c products.c

all: main

main: $(SRC_FILES)
	gcc -Wall -Wextra -pedantic -g -std=c99 -o $@ $(SRC_FILES)

clean:
	rm -f main

run: main
	# Running our main function from file main.c
	./main
