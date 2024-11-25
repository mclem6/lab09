#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int counter = 0;


void * routine_even(void * arg)
{
    // event: counter is zero (happens first)
    if (counter == 0) {
        printf("zero\n");
        counter += 1;
    }
    // event: counter is two
    if (counter == 2) {
        printf("two\n");
        counter += 1;
    }
    return NULL;
}


void * routine_odd(void * arg)
{
    // event: counter is one
    if (counter == 1) {
        printf("one\n");
        counter += 1;
    }
    // event: counter is three
    if (counter == 3) {
        printf("three\n");
    }
    return NULL;
}


int main(void)
{
    pthread_t even, odd;

    pthread_create(&even, NULL, routine_even, NULL);
    pthread_create(&odd, NULL, routine_odd, NULL);

    pthread_join(even, NULL);
    pthread_join(odd, NULL);

    printf("Finished\n");

    return 0;
}
