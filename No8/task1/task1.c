#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int count;
pthread_mutex_t count_lock;

void *my_thread(void *arg)
{
    int i = 0;

    for (i = 0; i < 500000000; i++) {
        pthread_mutex_lock(&count_lock);
        count++;
        pthread_mutex_unlock(&count_lock);
    }

    return NULL;
}

int main()
{
    pthread_t thread1;
    pthread_t thread2;

    // Initialize semaphore
    pthread_mutex_init(&count_lock, NULL); // Initialize semaphore to 1

    // Create threads
    pthread_create(&thread1, NULL, my_thread, NULL);
    pthread_create(&thread2, NULL, my_thread, NULL);

    // Join threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy semaphore
    pthread_mutex_destroy(&count_lock);

    printf("count = %d\n", count);

    return 0;
}
