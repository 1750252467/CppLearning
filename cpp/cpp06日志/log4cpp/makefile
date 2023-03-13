SRCS:=$(wildcard *.cc)              
OBJS:=$(patsubst %.cc, %, ${SRCS})
                                                           
OUT: ${OBJS}                       
         
%: %.cc                          
	g++ $^ -o $@ -llog4cpp -lpthread                    
                                   
.PHONY: clean rebuild OUT        
clean:                             
	${RM} ${OBJS}           
rebuild: clean OUT           
                   
