#include <stdio.h>
#include <pthread.h>

void* thr1(void* arg) {
  int count;  // This variable is not used in the provided code.

  printf("this is thread %d\n", *((int*)arg));
  sleep(2);

  return NULL;
}

int main(int argc, char* argv[]) {
  int i;
  pthread_t tid[3]; // Array to store IDs of 3 threads
  int status; // Variable to store join status

  for (i = 0; i < 3; i++) {
    pthread_create(&tid[i], NULL, thr1, (void*)&tid[i]);  // Create 3 threads
  }

  for (i = 0; i < 3; i++) {
    if (pthread_join(tid[i], (void**) &status) > 0) {  // Wait for each thread
      printf("pthread_join for thread %d failure\n", (int)tid[i]);
      return 0;  // Exit if there's an error
    }
    printf("pthread_waited for %d OK, return code: %d\n", (int)tid[i], status);
    sleep(1);  // Main thread sleeps for 1 second after each join
  }

  sleep(1);  // Main thread sleeps for another 1 second before exiting
  return 0;  // Successful program termination
}
