.SUFFIXES: .c .o
CC = gcc
SRCS = server.c
OBJS = $(SRCS:.c=.o)
EXEC = server

all:start clean
start:$(OBJS)
	@$(CC) -o $(EXEC) $(OBJS)

.c.o:
	@$(CC) -Wall -g -o $@ -c $<

.PHONY:clean
clean:
	@rm -f *.o core
