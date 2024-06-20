CC		= gcc
CFLAGS	= -std=c17
TARGET	= ELFMaker
SRCS	= main.c
OBJS	= $(SRCS:.c=.o)

all: test

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

test: $(TARGET)
	$(TARGET)
	ld hello1.o hello2.o -o hello
	./hello

clean:
	$(RM) $(TARGET) $(OBJS) hello1.o hello2.o

.PHONY:	test clean
