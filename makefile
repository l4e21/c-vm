OUTPUT_FILE = src/main
SRC_FILES = src/*.c
CC = gcc

compile: src/*.c
	${CC} -o ${OUTPUT_FILE} ${SRC_FILES}
