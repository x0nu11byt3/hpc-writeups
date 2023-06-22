#include "factorial.h"

long long factorial(long n){
    long long result = 1;
    for ( long long number = 2; number <= n; number++ )
        result *= number;
    return (result);
}

long long factorial_fork(long n){
     long long response = 1;
     pid_t pid = fork(); 
    
    if (pid == -1) {
        printf("\nCan't create child procees this fork");
        return -1;
    } else if (pid == 0) {
        for(long long number = 2; number <= n; number++){
            response *= number;
        }
    } else {
        wait(NULL); 
        return 0;
    }
    return response;
}

long long *factorial_forks(long n, long m) {
    long long factorial_a = 1;
    long long factorial_b = 1;
    static long long factorials[2];
    
    pid_t pid_a, pid_b;
    pid_a = fork();
    
    if ( pid_a < 0 ) 
        printf("\nFirst fork A doesn't work");
  
    if ( pid_a == 0 ) {
        for ( long long number = 2; number <= n; number++ )
            factorial_a *= number;
    
        factorials[0] = factorial_a; 
    } else {
        
        pid_b = fork();
  
        if ( pid_b < 0 ) 
             printf("\nSecond fork B doesn't work");
  
        if (pid_b == 0) {
           for ( long long number = 2; number <= m; number++ )
                factorial_b *= number; 
        
           factorials[1] = factorial_b;
        } else {
            wait(NULL);
            wait(NULL);
        }
    }
    return factorials;
}

void *factorial_thread(void *arg) {
    sleep(1);
    thread_data *tdata=(thread_data *)arg;
    long n = tdata->n;
    
    long long response = 1;
    for(long long number = 2; number <= n; number++)
        response *= number;

    tdata->response = response;
    pthread_exit(NULL);
}



int main(int argc, char *argv[]){
    // Firs exercice from exam second partial
    int amount_argv = argc - 1;
    for ( int i = 0; i < amount_argv; i++) {
        long long factorial = factorial_fork(atoll(argv[i+1]));
        printf("factorial[ %d ] from %d is %lld \n",i,atoll(argv[i+1]), factorial);
    }
    
    /*
    if( argc != 3 ){
        printf("Error!");
        exit(1);
    }
    
    long long *factorial;
    factorial = factorial_forks( atoll(argv[1]), atoll(argv[2]) );
    
    printf("[+] execute factorial -> first factorial %lld | second factorial is %lld \n", factorial[0], factorial[1] );
    
    */
    int amount_argv_ = argc - 1;
    pthread_t thread_id[amount_argv_];
    long long array_fact[2];
    for ( int i = 0; i < amount_argv_; i++ ) {
        thread_data tdata;
        tdata.n = atoll(argv[i+1]);
        pthread_create(&thread_id[i], NULL, factorial_thread, (void *)&tdata);
        pthread_join(thread_id[i], NULL);
        array_fact[i] = tdata.response;
        printf("[+] Thread :: factorial of %d is %d\n", tdata.n, tdata.response);
    }
    
    
    if ( array_fact[0] > array_fact[1] )
        printf("max factorial is %lld",array_fact[0]);
    else if ( array_fact[0] < array_fact[1] )
        printf("max factorial is %lld",array_fact[1]);
    else 
    
    
    
    
    exit(0);
}
