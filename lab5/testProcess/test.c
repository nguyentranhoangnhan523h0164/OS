#include <stdio.h>
#include <pthread.h>

void* thr1(void* arg) {
  printf("this is thread %d\n", *((int*)arg));
  sleep(2);
}

int main(int argc, char* argv[]) {
  int i;
  int num = atoi(argv[1]);
  pthread_t tid[num];

  for (i = 0; i < num; i++) {
    pthread_create(&tid[i], NULL, thr1, (void*)&tid[i]);
  }

  sleep(3);

  return 0;
}
