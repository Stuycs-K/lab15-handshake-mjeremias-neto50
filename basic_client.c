#include "pipe_networking.h"

int main(int argc, char const *argv[]) {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );
  int running = 0;
  while(running != -1){
    char buffer[100];
    running = read(from_server, buffer, 100);
    printf("%s\n", buffer);
  }
  return 0;
}
