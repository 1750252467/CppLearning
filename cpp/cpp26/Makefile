SRCS:=$(wildcard *.cc)
OBJECTS:=$(patsubst %.cc, %.o, $(SRCS))
CC:=g++
LIBS:=
SERVER:= Test

$(SERVER):$(OBJECTS)
	$(CC) $^ -o $@ $(LIBS) -g -pthread

%.o:%.cc
	$(CC) -c $^ -o $@ $(LIBS) -g -pthread
print:
	echo $(OBJECTS)
clean:
	rm -rf $(OBJECTS) $(SERVER)
