# C Chat
A peer to peer messaging program made with sockets in C  
cChat also functions as a minimal telnet clone, allowing you to easily attempt tcp connections
## Prerequisites
1. The current program is made for unix based operating systems (if you are on windows you can use it using Windows Subsystem for Linux(WSL))
2. git to clone the repo
3. A c compiler and make to build the binary - only compilation with gcc has been tested
## Set-up
Clone the repo with `git clone https://github.com/sidesbutgithub/cChat.git`, cd into the project dir with `cd cChat` and run `make all` to build the output files and final binary `cChat`
## Usage
The program uses command line args to specify functionality
```
./cChat <host> <port>
```
- if no args are provided, the program starts a server listening on yor ip address and the default port `9034` for all connections and will display
```
listening on <your ip>
```
- if `<host>` and `<port>` are provided, the program will attempt a tcp connection to a socket at `<host>` and `<port>`  
- if the connection is successful, the chat session will begin  
- else, the program opens a listening socket listening on your ip and default port `9034` for connections exclusively from `<host>` and `<port>`  
only when a connection from `<host>` and `<port>` is accepted will the chat session begin
## Chatting
Once chatting has begun, the program polls the connected socket for incoming messages and stdin for your outgoing messages
