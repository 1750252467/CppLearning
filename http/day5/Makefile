

# File Name Makefile
# Author 泷fengyoukai
# Github https://github.com/1750252467
# Created Time 2022-09-27 22:41
SRCS:=$(wildcard *.cc)
OBJS:=$(patsubst %.cc, %, ${SRCS})

OUT: ${OBJS}

%: %.cc
	g++ $^ -o $@ -lworkflow
.PHONY: clean rebuild OUT

clean:
	${RM} ${OBJS}
rebuild: clean OUT
