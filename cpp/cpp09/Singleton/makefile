SRCS:=$(wildcard *.cc)              
OBJS:=$(patsubst %.cc, %, ${SRCS})
                                                           
OUT: ${OBJS}                       
         
%: %.cc                          
	g++ $^ -o $@                      
                                   
.PHONY: clean rebuild OUT        
clean:                             
	${RM} ${OBJS}           
rebuild: clean OUT           
                   
