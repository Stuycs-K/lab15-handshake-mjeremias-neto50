#include "pipe_networking.h"

static void sighandler(int signo);

int main(int argc, char const *argv[]){
  while(1){
    signal(SIGINT, sighandler);
    int to_client;
    int from_client;
    from_client = server_setup();
    pid_t f = fork();
    if (f == 0) {
      to_client = server_connect(int from_client);
      while(running != -1){
        signal(SIGINT, sighandler);
        signal(SIGPIPE, SIG_IGN);
        srand(time(NULL));
        int r = rand()%100;
        char buffer[100];
        snprintf(buffer, 100, "%d", r);
        running = write(to_client, buffer, 100);
        sleep(1);
      }
      close(to_client);
      close(from_client);
      exit(0);
    }
  }
  return 0;
}
static void sighandler(int signo) {
    if ( signo == 2 ){
      remove(WKP);
      exit(0);
    }
  }
