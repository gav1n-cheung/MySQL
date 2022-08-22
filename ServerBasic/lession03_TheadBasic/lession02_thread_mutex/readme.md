# 线程同步
## 基本
```
◼ 线程的主要优势在于，能够通过全局变量来共享信息。不过，这种便捷的共享是有代价
的：必须确保多个线程不会同时修改同一变量，或者某一线程不会读取正在由其他线程
修改的变量。
◼ 临界区是指访问某一共享资源的代码片段，并且这段代码的执行应为原子操作(不可分割，不可中断)，也就是
同时访问同一共享资源的其他线程不应终端该片段的执行。
◼ 线程同步：即当有一个线程在对内存进行操作时，其他线程都不可以对这个内存地址进
行操作，直到该线程完成操作，其他线程才能对该内存地址进行操作，而其他线程则处
于等待状态。
```
## 互斥量/互斥锁
```
◼ 为避免线程更新共享变量时出现问题，可以使用互斥量（mutex 是 mutual exclusion
的缩写）来确保同时仅有一个线程可以访问某项共享资源。可以使用互斥量来保证对任意共
享资源的原子访问。
◼ 互斥量有两种状态：已锁定（locked）和未锁定（unlocked）。任何时候，至多只有一
个线程可以锁定该互斥量。试图对已经锁定的某一互斥量再次加锁，将可能阻塞线程或者报
错失败，具体取决于加锁时使用的方法。
◼ 一旦线程锁定互斥量，随即成为该互斥量的所有者，只有所有者才能给互斥量解锁。一般情
况下，对每一共享资源（可能由多个相关变量组成）会使用不同的互斥量，每一线程在访问
同一资源时将采用如下协议：
⚫ 针对共享资源锁定互斥量
⚫ 访问共享资源
⚫ 对互斥量解锁
```
![互斥量](%E4%BA%92%E6%96%A5.png)
### 相关函数
```
◼ 互斥量的类型 pthread_mutex_t
◼ int pthread_mutex_init(pthread_mutex_t *restrict mutex,const pthread_mutexattr_t *restrict attr);
◼ int pthread_mutex_destroy(pthread_mutex_t *mutex);
◼ int pthread_mutex_lock(pthread_mutex_t *mutex);
◼ int pthread_mutex_trylock(pthread_mutex_t *mutex);
◼ int pthread_mutex_unlock(pthread_mutex_t *mutex);
```
## 死锁
![死锁](%E6%AD%BB%E9%94%81.png)
## 读写锁
```
◼ 当有一个线程已经持有互斥锁时，互斥锁将所有试图进入临界区的线程都阻塞住。但是考
虑一种情形，当前持有互斥锁的线程只是要读访问共享资源，而同时有其它几个线程也想
读取这个共享资源，但是由于互斥锁的排它性，所有其它线程都无法获取锁，也就无法读
访问共享资源了，但是实际上多个线程同时读访问共享资源并不会导致问题。
◼ 在对数据的读写操作中，更多的是读操作，写操作较少，例如对数据库数据的读写应用。
为了满足当前能够允许多个读出，但只允许一个写入的需求，线程提供了读写锁来实现。
◼ 读写锁的特点：
 如果有其它线程读数据，则允许其它线程执行读操作，但不允许写操作。
 如果有其它线程写数据，则其它线程都不允许读、写操作。
 写是独占的，写的优先级高。
```
### 相关函数
```
◼ 读写锁的类型 pthread_rwlock_t
◼ int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock,const pthread_rwlockattr_t *restrict attr);
◼ int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
◼ int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
◼ int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
◼ int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
◼ int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
◼ int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
```
## 生产者消费者模型
![生产者消费者模型](%E7%94%9F%E4%BA%A7%E8%80%85%E6%B6%88%E8%B4%B9%E8%80%85%E6%A8%A1%E5%9E%8B.png)  
生产者可以有多个，消费者可以有多个。如果商品为空，则需要阻塞消费者，并通知生产者来生产商品。如果商品已满容器，则需要阻塞生产者并通知消费者消费商品。  
同时多个线程间需要保证数据安全，进行线程同步。
