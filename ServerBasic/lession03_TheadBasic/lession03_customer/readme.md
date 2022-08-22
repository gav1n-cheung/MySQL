# 生产者消费者模型
## 条件变量
```
◼ 条件变量的类型 pthread_cond_t
◼ int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
◼ int pthread_cond_destroy(pthread_cond_t *cond);
◼ int pthread_cond_wait(pthread_cond_t *restrict cond,pthread_mutex_t *restrict mutex);
◼ int pthread_cond_timedwait(pthread_cond_t *restrict cond,pthread_mutex_t *restrict mutex, const struct timespec *restrict abstime);
◼ int pthread_cond_signal(pthread_cond_t *cond);
◼ int pthread_cond_broadcast(pthread_cond_t *cond);
```
## 信号量
```
◼ 信号量的类型 sem_t
◼ int sem_init(sem_t *sem, int pshared, unsigned int value);
◼ int sem_destroy(sem_t *sem);
◼ int sem_wait(sem_t *sem);
◼ int sem_trywait(sem_t *sem);
◼ int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);
◼ int sem_post(sem_t *sem);
◼ int sem_getvalue(sem_t *sem, int *sval);
```