SRCS:=$(wildcard *.cc)
OBJECTS:=$(patsubst %.cc, %.o, $(SRCS))
CC:=g++
LIBS:=
SERVER:= Test

$(SERVER):$(OBJECTS)
	$(CC) $^ -o $@ $(LIBS) -g 

%.o:%.cpp
	$(CC) -c $^ -o $@ $(LIBS) -g 
print:
	echo $(OBJECTS)
clean:
	rm -rf $(OBJECTS) $(SERVER)
