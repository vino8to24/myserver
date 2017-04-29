.SUFFIXES: .c .o
CC = gcc
SRCS = client.c
OBJS = $(SRCS:.c=.o)
EXEC = client

all: start clean
start:$(OBJS)	
	@$(CC) -o $(EXEC) $(OBJS)

.c.o:
	@$(CC) -Wall -g -o $@ -c $<

.PHONY:clean
clean:
	@rm -f *.o core
