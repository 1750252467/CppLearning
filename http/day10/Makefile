# File Name Makefile
# Author 泷fengyoukai
# Github https://github.com/1750252467
# Created Time 2022-10-06 21:29

server:main.o Hash.o
	g++ $^ -o $@ -lwfrest -lworkflow -lssl -lcrypto 
main.o:main.cc
	g++ -c $^ -o $@ -g
test.o:test.cc
	g++ -c $^ -o $@ -g
Hash.o:Hash.cc
	g++ -c $^ -o $@ -g
test:test.o Hash.o
	g++ $^ -o $@ -lwfrest -lworkflow -lssl -lcrypto
clean:
	rm -f main.o Hash.o test.o server test
