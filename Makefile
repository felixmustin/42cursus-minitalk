NAME = minitalk
CC = gcc
CCFLAG = -Wall -Wextra -Werror

SRC_CLIENT = client.c
SRC_SERVER = server.c
SRCS = utils.c

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJS = $(SRCS:.c=.o)

all: $(OBJ_SERVER) $(OBJ_CLIENT) $(OBJS)
	$(CC) $(OBJ_SERVER) $(OBJS) -o server
	$(CC) $(OBJ_CLIENT) $(OBJS) -o client

clean:
			rm -f $(OBJ_CLIENT) $(OBJ_SERVER) $(OBJS)

fclean:		clean
			rm -f client server

re:			fclean all

.PHONY: all, clean, fclean, re