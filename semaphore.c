#include <stdio.h>

/* 信号量结构 */ 
struct semaphore {
    int val;        /* 信号量值 */
    struct proc* list;   /* 等待进程队列 */ 
};

/* P操作 - 信号量获取 */
void P(struct semaphore *sem) 
{
    if (sem == NULL) {
        fprintf(stderr, "Semaphore pointer is NULL!\n");
        return;
    }
    
    while (1) { 
        if (sem->val > 0) {  
            sem->val--;   
            return;
        }
            
        /* 进入等待队列 */  
        sleep(sem->list);  
    }
}

/* V操作 - 信号量释放 */ 
void V(struct semaphore *sem)
{
    if (sem == NULL) {
        fprintf(stderr, "Semaphore pointer is NULL!\n");
        return; 
    }
    
    sem->list++;
    if (sem->list) {
        wakeup(sem->val); 
    }    
}

