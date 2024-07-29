#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int count;
sem_t count_sem;

void *my_thread(void *arg)
{
    int i = 0;

    for (i = 0; i < 500000000; i++) {
        sem_wait(&count_sem);
        count++;
        sem_post(&count_sem);
    }

    return NULL;
}

int main()
{
    pthread_t thread1;
    pthread_t thread2;

    // Initialize semaphore
    sem_init(&count_sem, 0, 1); // Initialize semaphore to 1

    // Create threads
    pthread_create(&thread1, NULL, my_thread, NULL);
    pthread_create(&thread2, NULL, my_thread, NULL);

    // Join threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy semaphore
    sem_destroy(&count_sem);

    printf("count = %d\n", count);

    return 0;
}
