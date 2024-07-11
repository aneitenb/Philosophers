NAME := philo
CC := cc
CFLAGS := -Wextra -Wall -Werror -pthread

HEADERS	= -I ./include

SRCS	= 	main.c \
			check_arg.c \
			error_handling.c 

OBJS	= ${SRCS:.c=.o}

all: ${NAME}

%.o: %.c
	@${CC} ${CFLAGS} -o $@ -c $< ${HEADERS}

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} ${HEADERS} -o ${NAME}
	@echo "\033[32;1mCompilation Succesful!\033[0m"

clean:
	@rm -rf ${OBJS}
	@echo "\033[32;1mCleaned files\033[0m"

fclean: clean
	@rm -rf ${NAME}
	@echo "\033[32;1mRemoved program!\033[0m"

re: clean all

.PHONY: all, clean, fclean, re