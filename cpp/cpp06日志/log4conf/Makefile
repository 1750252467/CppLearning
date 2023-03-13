SRCS:=$(wildcard *.cpp)
OBJECTS:=$(patsubst %.cpp, %.o, $(SRCS))
CC:=g++
LIBS:=
SERVER:= Test

$(SERVER):$(OBJECTS)
	$(CC) $^ -o $@ $(LIBS) -g -llog4cpp -lpthread

%.o:%.cpp
	$(CC) -c $^ -o $@ $(LIBS) -g -llog4cpp -lpthread
print:
	echo $(OBJECTS)
clean:
	rm -rf $(OBJECTS) $(SERVER)
