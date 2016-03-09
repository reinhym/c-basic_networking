all: client server
	

client: client.c client.h
	gcc client.c -o client -lpthread

server: server.c server.h
	gcc server.c -o server -lpthread

.PHONY: clean
clean:
	rm server client -f