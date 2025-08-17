CFLAGS = -Wall -Werror

all: cchat

cchat: main.o socktoip.o server.o getListener.o client.o getRemote.o peerToPeer.o
	gcc ${CFLAGS} src/main.o src/utils/socktoip.o src/server/server.o src/server/getListener.o src/client/client.o src/peerToPeer/peerToPeer.o src/client/getRemote.o -o cchat

main.o: src/main.c
	gcc ${CFLAGS} -c src/main.c -o src/main.o

socktoip.o: src/utils/socktoip.c
	gcc ${CFLAGS} -c src/utils/socktoip.c -o src/utils/socktoip.o

server.o: src/server/server.c
	gcc ${CFLAGS} -c src/server/server.c -o src/server/server.o

getListener.o: src/server/getListener.c
	gcc ${CFLAGS} -c src/server/getListener.c -o src/server/getListener.o

client.o: src/client/client.c
	gcc ${CFLAGS} -c src/client/client.c -o src/client/client.o

getRemote.o: src/client/getRemote.c
	gcc ${CFLAGS} -c src/client/getRemote.c -o src/client/getRemote.o

peerToPeer.o: src/peerToPeer/peerToPeer.c
	gcc ${CFLAGS} -c src/peerToPeer/peerToPeer.c -o src/peerToPeer/peerToPeer.o