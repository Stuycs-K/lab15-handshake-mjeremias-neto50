#include "pipe_networking.h"

static void sighandler(int signo);

int main(int argc, char const *argv[]){
  int to_client;
  int from_client;
  from_client = server_handshake( &to_client );
  int running = 0;
  while(running != -1){
    signal(SIGINT, sighandler);
    srand(time(NULL));
    int r = rand()%100;
    char buffer[100];
    snprintf(buffer, 100, "%d", r);
    running = write(to_client, buffer, 100);
    sleep(1);
  }

  return 0;
}
static void sighandler(int signo) {
    if ( signo == 2 ){
      remove(WKP);
      exit(0);
    }
  }
