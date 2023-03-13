SRCS:=$(wildcard *.c)
OBJECTS:=$(patsubst %.c, %, $(SRCS))
CC:=gcc
LIBS:=

all:$(OBJECTS)

%:%.c
	$(CC) $^ -o $@ $(LIBS) -g
print:
	echo $(OBJECTS)
clean:
	rm -rf $(OBJECTS)
