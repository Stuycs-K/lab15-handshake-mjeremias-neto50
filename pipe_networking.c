#include "pipe_networking.h"

#define READ 0
#define WRITE 1

//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  int from_client = 0;
  mkfifo(WKP, 666);
  from_client = open(WKP, O_RDONLY);
  remove(WKP);
  return from_client;
}

/*=========================
  server_handshake
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
  int send;
  int recv;
  //1-4
  int from_client = server_setup();
  //5
  char buffer[100];
  read(from_client, buffer, 100);
  //6
  *to_client = open(buffer, O_WRONLY);
  //7
  char *buffer2 = buffer + 1;
  send = atoi(buffer2);
  snprintf(buffer, 100, "%d", send);
  write(*to_client, buffer, 100);
  //9
  read(from_client, buffer, 100);
  recv = atoi(buffer);
  if((recv+=2 )==send){
  }
  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int send;
  int recv;
  //3
  int from_server;
  int pid = (int)getpid();
  send = pid;
  char buffer[100];
  snprintf(buffer, 100, "/%d", send);
  mkfifo(buffer, 0666);
  *to_server = open(WKP, O_WRONLY);
  write(*to_server, buffer, 100);
  from_server = open(buffer, O_RDONLY);
  remove(buffer);
  recv = atoi(buffer);
  if(recv == (send ++)){
  }
  snprintf(buffer, 100, "%d", recv+1);
  write(*to_server, buffer, 100);
  return from_server;
}


/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  int send;
  int recv;
  int to_client  = 0;
  char buffer[100];
  read(from_client, buffer, 100);
  //6
  to_client = open(buffer, O_WRONLY);
  //7
  char *buffer2 = buffer + 1;
  send = atoi(buffer2);
  snprintf(buffer, 100, "%d", send);
  write(to_client, buffer, 100);
  //9
  read(from_client, buffer, 100);
  recv = atoi(buffer);
  if((recv+=2 )==send){
  }
  return from_client;
}
