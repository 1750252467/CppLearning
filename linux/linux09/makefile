SRCS:=$(wildcard *.c)              
OBJS:=$(patsubst %.c, %, ${SRCS})
                                                           
OUT: ${OBJS}                       
         
%.o: %.c                           
	gcc $^ -o $@                      
                                   
.PHONY: clean rebuild OUT        
clean:                             
	${RM} ${OBJS}           
rebuild: clean main            
                   
