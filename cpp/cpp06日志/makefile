SRCS:=$(wildcard *.cpp)              
OBJS:=$(patsubst %.cpp, %, ${SRCS})
                                                           
OUT: ${OBJS}                       
         
%: %.cpp                          
	g++ $^ -o $@ -llog4cpp -lpthread                    
                                   
.PHONY: clean rebuild OUT        
clean:                             
	${RM} ${OBJS}           
rebuild: clean OUT           
                   
