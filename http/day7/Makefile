SRCS:=$(wildcard *.cc)
EXES:=$(SRCS:%.cc=%)
all:$(EXES)
%:%.cc
	g++ $^ -o $@ -lworkflow -g
clean:
	$(RM) $(EXES)