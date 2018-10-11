CC_FLAGS = -Wall -Wextra -g -std=c11

hvm: main.c
	${CC} $^ ${CC_FLAGS} -o $@
