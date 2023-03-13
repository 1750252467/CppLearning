SRCS:=$(wildcard *.c)              
OBJS:=$(patsubst %.c, %, ${SRCS})
                                                           
OUT: ${OBJS}                       
         
%: %.c                           
	gcc $^ -o $@ -lpthread 
                                   
.PHONY: clean rebuild OUT        
clean:                             
	${RM} ${OBJS}           
rebuild: clean OUT            
                   
