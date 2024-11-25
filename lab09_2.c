#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int counter = 0;
pthread_mutex_t counter_lock;
pthread_cond_t is_one;
pthread_cond_t is_two;
pthread_cond_t is_three;


void * routine_even(void * arg)
{
    // event: counter is zero (happens first)      
    pthread_mutex_lock(&counter_lock);
    if (counter == 0) {
        printf("zero\n");
        counter += 1;
	pthread_cond_signal(&is_one);
	pthread_mutex_unlock(&counter_lock);
    }
    // event: counter is two
    pthread_mutex_lock(&counter_lock);
    while (counter != 2) {
	    pthread_cond_wait(&is_two, &counter_lock);
    }
    
    printf("two\n");
    counter += 1;
    pthread_cond_signal(&is_three);
    pthread_mutex_unlock(&counter_lock);
    
    return NULL;
}


void * routine_odd(void * arg)
{
    // event: counter is one
    pthread_mutex_lock(&counter_lock);
    while(counter != 1) {
	    pthread_cond_wait(&is_one, &counter_lock);
    }

    printf("one\n");
    counter += 1;
    pthread_cond_signal(&is_two);
    pthread_mutex_unlock(&counter_lock);
   
    // event: counter is three
    pthread_mutex_lock(&counter_lock);
    while (counter != 3) {
	    pthread_cond_wait(&is_three, &counter_lock);
    }
    printf("three\n");
    pthread_mutex_unlock(&counter_lock);
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
