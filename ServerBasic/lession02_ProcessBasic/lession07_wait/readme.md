# wait
```
◼ 在每个进程退出的时候，内核释放该进程所有的资源、包括打开的文件、占用的内
存等。但是仍然为其保留一定的信息，这些信息主要主要指进程控制块PCB的信息
（包括进程号、退出状态、运行时间等）。
◼ 父进程可以通过调用wait或waitpid得到它的退出状态同时彻底清除掉这个进程。
◼ wait() 和 waitpid() 函数的功能一样，区别在于， wait() 函数会阻塞，
waitpid() 可以设置不阻塞， waitpid() 还可以指定等待哪个子进程结束。
◼ 注意：一次wait或waitpid调用只能清理一个子进程，清理多个子进程应使用循环。

◼ WIFEXITED(status) 非0，进程正常退出
◼ WEXITSTATUS(status) 如果上宏为真，获取进程退出的状态（exit的参数）
◼ WIFSIGNALED(status) 非0，进程异常终止
◼ WTERMSIG(status) 如果上宏为真，获取使进程终止的信号编号
◼ WIFSTOPPED(status) 非0，进程处于暂停状态
◼ WSTOPSIG(status) 如果上宏为真，获取使进程暂停的信号的编号
◼ WIFCONTINUED(status) 非0，进程暂停后已经继续运行
```