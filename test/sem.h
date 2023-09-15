#include "types.h"
#include "user.h"
#include "spinlock.h"

struct semaphore {
  int count;
  struct spinlock lock;
};

void sem_init(struct semaphore *sem, int count) {
  initlock(&sem->lock, "semaphore");
  sem->count = count;
}

void P(struct semaphore *sem) {
  acquire(&sem->lock);

  while (sem->count == 0) {
    release(&sem->lock);
    yield();
    acquire(&sem->lock);
  }

  sem->count--;
  release(&sem->lock);
}

void V(struct semaphore *sem) {
  acquire(&sem->lock);

  sem->count++;
  release(&sem->lock);
}

