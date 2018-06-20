#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

struct thr_args{
    size_t size;//100000001
    size_t thr_num;
    size_t thr_id;
    size_t count;
};
void *run(void* args){
    size_t size=((struct thr_args*)args)->size;
    size_t thr_num=((struct thr_args*)args)->thr_num;
    size_t thr_id=((struct thr_args*)args)->thr_id;
    size_t* count=&(((struct thr_args*)args)->count);//////// count value 
    long star=size/thr_num * thr_id;
    long end;
    if(thr_id == thr_num-1)// if it is last thread 
        end = size;
    else
        end = size/thr_num*(thr_id+1); // if it is not last thread 
    if (star%2==0)
        star++;
    for (int i = star; i < end; i+=2) {/// is ? simple ?
        int is_simple = 1;
        for (long j = 3; j < sqrt(i)+1; j+=2) {
            if(i%j==0) {
                is_simple = 0;
                break;
            }
        }
        if(is_simple)
            (*count)++;
    }
    pthread_exit(NULL);
}

long long current_timestamp() {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}
int main(int argc, char **argv) {
    int thr_num =atoi(argv[1]);///////////////////////////////////1
    const size_t size = atoi(argv[2]);//////////////////////10000000
    size_t count = 0;
    struct timeval t;/// thime 
    size_t start = current_timestamp();/// thime start.
    struct thr_args *thr_arg = malloc(sizeof(struct thr_args)*thr_num);
    pthread_t threads[thr_num];
    for (int i = 0; i < thr_num; ++i) {
        thr_arg[i].size=size;
        thr_arg[i].thr_num=thr_num;
        thr_arg[i].thr_id=i;
        thr_arg[i].count=0;
        pthread_create(&threads[i],NULL,run,&thr_arg[i]);
    }
    for (int j = 0; j < thr_num; ++j) {
        pthread_join(threads[j],NULL);
        count+=thr_arg[j].count;
    }
    size_t end = current_timestamp();
    printf("Count = %d Time = %d milliseconds\n",count,end-start);
    return 0;
}
