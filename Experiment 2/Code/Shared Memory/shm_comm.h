// shm_comm.h

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SHM_KEY 1234
#define SHM_SIZE 1024
#define SEMKEY1 2345
#define SEMKEY2 3456
#define SEMKEY3 4567

// create a new semaphore
int createsig(key_t key, int num)
{
        int semid = 0;
        union semun{
                int var;
                struct semid_ds *buf;
                ushort *array;
        } arg;

        // create a semaphore
        if ( (semid = semget(key, 1, IPC_CREAT | 0666)) == -1)

        {
                perror("semget error !");
                return -1;
        }

        arg.var = num;

        // use arg to set the value of the semaphore
        if (semctl(semid, 0, SETVAL, arg) == -1)
        {
                perror("semctl error !");
                return -1;
        }

        return semid;
}

// operate on a certain semaphore
void op_sem(int semid, int op)
{
        struct sembuf buf;
        buf.sem_num = 0;
        buf.sem_op = op;
        buf.sem_flg = 0;

        if(semop(semid, &buf, 1) == -1)
        {
                perror("semop error !");
        }
}

/*
 *  P operator
 *  enter the restricted area
 */
void P(int semid)
{
        op_sem(semid, -1);
}

/*
 * V operator
 * leave the restricted area
 */
void V(int semid)
{
        op_sem(semid, 1);
}

