#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>
int main()
{
    const char * s1 = "fill";
    const char * s2 = "available";
    const char * s3 = "mutex";
    int loop = 6;

    sem_unlink(s1);
    sem_unlink(s2);
    sem_unlink(s3);

    int tbl = shm_open("table", O_CREAT | O_RDWR, 0666);
    
    ftruncate(tbl,sizeof(int));
    
    int * table = mmap(0,sizeof(int), O_RDWR, MAP_SHARED, tbl, 0);
    
    sem_t* fill = sem_open(s1, O_CREAT | O_RDWR,0666,0);
    if(fill == SEM_FAILED){
      printf("fill failed");
    }

    sem_t* avail = sem_open(s2, O_CREAT | O_RDWR, 0666, 2);
    if(avail == SEM_FAILED){
      printf("avail failed");
    }

    sem_t* mutex = sem_open(s3,O_CREAT | O_RDWR,0666,1);
    if(mutex == SEM_FAILED){
      printf("mutex");
    }

  

    printf("\nProducer ready to create %d items.\n", loop-1);

        for(int i = 1; i < loop; ++i){
        sem_wait(avail);

        int ms=rand() % 2+i;
        sleep(ms);
        sem_wait(mutex);
        ++(* table);
        /*printf("Table items: %d",* table);*/
        sem_post(mutex);
        printf("Item produced, there are now %d item(s) in the table.\n",* table);
        sem_post(fill);
    }
    
    sem_close(fill);
    sem_close(avail);
    sem_close(mutex);
    sem_unlink(s1);
    sem_unlink(s2);
    sem_unlink(s3);
    munmap(table, sizeof(int));
    close(tbl);
    shm_unlink("table");
    printf("Producer cleaned up!\n");
    return 0;
}
