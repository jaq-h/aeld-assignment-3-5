#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>   

#ifdef DEBUG
  #define DEBUG_LOG(msg, ...) fprintf(stderr, "threading: " msg "\n", ##__VA_ARGS__)
#else
  #define DEBUG_LOG(msg, ...) ((void)0)
#endif

#define ERROR_LOG(msg, ...) do { \
    fprintf(stderr, "threading ERROR [%s:%d tid=%lx]: " msg "\n", \
            __FILE__, __LINE__, (unsigned long)pthread_self(), ##__VA_ARGS__); \
} while(0)

void* threadfunc(void* thread_param)
{
    if(thread_param == NULL){
	    ERROR_LOG("thread param is NULL");
	    return thread_param;
    }
	
    struct thread_data* thr_args = (struct thread_data *) thread_param;
    nanosleep(&(struct timespec){ .tv_sec = thr_args->wait_to_obtain_ms / 1000, .tv_nsec = (thr_args->wait_to_obtain_ms % 1000) * 1000000L }, NULL);
    if(pthread_mutex_lock(thr_args->mutex) !=0){
	    ERROR_LOG("Lock Failed");
    	    thr_args->thread_complete_success = false;
    }
     nanosleep(&(struct timespec){ .tv_sec = thr_args->wait_to_release_ms / 1000, .tv_nsec = (thr_args->wait_to_release_ms % 1000) * 1000000L }, NULL);
    if(pthread_mutex_unlock(thr_args->mutex) != 0){
	    ERROR_LOG("Unlock Failed");
	    thr_args->thread_complete_success = false;
    }
    else{
	    thr_args->thread_complete_success = true;
    }

    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
	struct thread_data *thr_data = malloc(sizeof *thr_data);

	 if (!thr_data) {
		 ERROR_LOG("malloc failed");
      		 return false;
   	 }

     	thr_data->mutex = mutex;
	thr_data->wait_to_obtain_ms = wait_to_obtain_ms;
	thr_data->wait_to_release_ms = wait_to_release_ms;
	int t = pthread_create(thread, NULL, &threadfunc, thr_data);

	if(t != 0){
		ERROR_LOG("pthread_create failed: %d (%s)",t, strerror(t));
		free(thr_data);
		return false;
	}

	DEBUG_LOG("New Thread tid: %0lx,%0lx", *(uint64_t *) thread, (uint64_t) thr_data->mutex);
	return true;

}

