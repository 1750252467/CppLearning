SRCS:=$(wildcard *.cc)
EXES:=$(SRCS:%.cc=%)
all:$(EXES)
%:%.cc
	g++ $^ -o $@ -lworkflow
clean:
	$(RM) $(EXES)