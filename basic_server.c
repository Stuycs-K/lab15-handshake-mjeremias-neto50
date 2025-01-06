#include "pipe_networking.h"

int main(int argc, char const *argv[]){
  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );
}
