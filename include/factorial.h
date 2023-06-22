
#ifndef _FACTORIAL_H
#define _FACTORIAL_H
  
#define __PROGRAM_NAME__ "factorial"
#define __PROGRAM_VERSION__ "1.0.0"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
    
long long factorial(long);
long long factorial_fork(long);
void *factorial_thread(void *arg);
long long *factorial_forks(long n, long m);

typedef struct thread_data {
    long n;
    long long response;
} thread_data;
    
#endif  /* !_FACTORIAL_H */
