all: main.c config.h mapping.h
	gcc main.c config.h mapping.h -o mapping

run: all
	./mapping
