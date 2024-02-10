FILE = search

build: $(FILE).c
	gcc -Wall -g $(FILE).c -o $(FILE) -lm

.PHONY: db

db:
	gdb -tui $(FILE)

run:
	./$(FILE)