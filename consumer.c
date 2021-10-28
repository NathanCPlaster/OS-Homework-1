#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<fcntl.h>
#include <sys/shm.h>
#include<sys/stat.h>
#include <sys/mman.h>
#include <pthread.h>
#include <semaphore.h>


int main(){
    const char * s1 = "fill";
    const char * s2 = "available";
    const char * s3 = "mutex";

    int tbl = shm_open("table", O_RDWR, 0666);
    int * table = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, tbl, 0);
    
    int loop = 6;

    sem_t * fill = sem_open(s1, O_CREAT | O_RDWR, 0666, 0);
    if(fill == SEM_FAILED)
      printf("fill");
    sem_t * avail = sem_open(s2, O_CREAT | O_RDWR, 0666, 2);
    if(avail == SEM_FAILED)
      printf("avail");
    sem_t * mutex = sem_open(s3, O_CREAT | O_RDWR, 0666, 1);
    if(mutex == SEM_FAILED)
      printf("mutex");

    /*printf("\nConsumer ready to receive %d items.\n", loop);*/

    for(int i=1; i<loop; ++i){
        sem_wait(fill);

        int ms = rand() % 3+i;
        sleep(ms);

        sem_wait(mutex);
        --( * table);
        sem_post(mutex);

        printf("Item consumed, %d remaining.\n",* table);

        sem_post(avail);
        sem_post(fill);

    }
    sem_close(fill);
    sem_close(avail);
    sem_close(mutex);
    sem_unlink(s1);
    sem_unlink(s2);
    sem_unlink(s3);

    munmap(table,sizeof(int));
    shm_unlink("table");
    printf("Consumer went home!\n");
    return 0;

}
