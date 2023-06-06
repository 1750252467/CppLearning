server:main.o Hash.o Crypt.o Token.o
	g++ $^ -o $@  -fno-rtti -lSimpleAmqpClient -lalibabacloud-oss-cpp-sdk -lcurl -lpthread -lwfrest -lworkflow -lssl -lcrypto -lcrypt
main.o:main.cc
	g++ -c $^ -o $@ -g
test.o:test.cc
	g++ -c $^ -o $@ -g
Hash.o:Hash.cc
	g++ -c $^ -o $@ -g
Crypt.o:Crypt.cc
	g++ -c $^ -o $@ -g
Token.o:Token.cc
	g++ -c $^ -o $@ -g
test:test.o Hash.o Crypt.o Token.o
	g++ $^ -o $@ -lwfrest -lworkflow -lssl -lcrypto -lcrypt
oss:oss.cc
	g++ $^ -o $@ -fno-rtti -lalibabacloud-oss-cpp-sdk -lcurl -lcrypto -lpthread 
mqconsumer:mqconsumer.cc
	g++ $^ -o $@ -fno-rtti -lSimpleAmqpClient -lalibabacloud-oss-cpp-sdk -lcurl -lpthread -lwfrest -lworkflow -lssl -lcrypto -lcrypt
clean:
	rm -f main.o Hash.o test.o server test