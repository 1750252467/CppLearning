SRCS:=$(wildcard *.c)            
OBJS:=$(patsubst %.c, %.o, ${SRCS})
OUT:=main
                                 
OUT: ${OBJS}
	gcc ${OBJS} -o ${OUT}                          
%.o: %.c            
	gcc -c $^                 
                                 
.PHONY: clean rebuild print       
clean:                          
	${RM} ${OBJS} ${OUT}               
	rebuild: clean main
print:
	each ${SRCS}
	each ${OBJS}
