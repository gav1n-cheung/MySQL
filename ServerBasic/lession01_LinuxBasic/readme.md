# 牛客网Linux高并发服务器开发
## Linux系统编程入门
### GCC
```
gcc ***.c -o name //生成name名称的可执行文件
-E 预编译生成.i文件
-S 编译生成.s汇编文件
-C 汇编生成.o机器码文件
-o 生成可执行文件
```
### 制作和使用静态库
```
gcc -c **.c //生成.o文件
ar rcs libxx.a **.o //将.o文件生成名为libxx.a的静态库文件，该静态库文件的名称为xx
# 如果找不到头文件，使用-I 指定头文件目录
gcc main.c -o app -I ./include -l calc -L ./lib 
# 使用-l指定静态库名称，使用-L指定静态库所在目录
```
### 制作和使用动态库
```
gcc -c -fpic *.c
gcc -shared *.o -o libcalc.so -I ./include
gcc main.cpp -o app -I ./include -l calc -L ./lib
#可以在终端内临时设置环境变量
export LD_LIBRARY_PATH = $LD_LIBRARY_PATH:your_path
#或者在~/.bashrc 或者~/.zshrc中添加该行
export LD_LIBRARY_PATH = $LD_LIBRARY_PATH:your_path
source ~/.bashrc
```
### 静态库和动态库的区别
![静态库和动态库的优缺点]()
### makefile
![如何读和写makefile]()
### GDB调试
```
# 在gcc中加入参数-g以进行GDB调试,加入-Wall参数尽量打开warning
gcc test.c -o test -g -Wall
# gdb中设定参数
>(gdb) set args 10 20
# 显示设定的参数
>(gdb) show args
# l/list (filename:)11 可以根据行号和方法名来查看指定的文件

# 在指定的行号处设断点
>(gdb) break (filename:)9
# 显示已有的断点
>(gdb) info b 
# 在指定的方法名处设置断点
>(gdb) break (filename:)main
# 使用delete 断点编号 来删除指定的断点
>(gdb) delete 1
# 使用disable/enable使断点失效/生效
>(gdb) disable 1
# 使用break 行号 if var = ? 来设定条件断点
>(gdb) break 16 if i=3

◼ 运行GDB程序  
start（程序停在第一行）  
run（遇到断点才停）  
◼ 继续运行，到下一个断点停  
c/continue  
◼ 向下执行一行代码（不会进入函数体）  
n/next  
◼ 变量操作  
p/print 变量名（打印变量值）  
ptype 变量名（打印变量类型）  
◼ 向下单步调试（遇到函数进入函数体）  
s/step  
finish（跳出函数体）  
◼ 自动变量操作  
display 变量名（自动打印指定变量的值）  
i/info display  
undisplay 编号  
◼ 其它操作  
set var 变量名=变量值 （循环中用的较多）  
until （跳出循环）  
```
### 文件IO
```
标准C库和Linux系统IO的关系：调用和被调用的关系
```
### 虚拟地址空间
```
每个进程都有自己的PCB,通过CPU来与物理内存映射
```
### 文件描述符
```
文件描述符是一个数组，大小默认为1024，前三个位置被默认占用了(0=标准输入,1=标准输出,2=标准错误,表征当前终端的信息)，新打开的文件会选择没被占用的最小的位置来保存文件标识符。被占用的文件描述符在释放后才可以被重新使用。
```
### Linux系统IO函数
```
open 打开一个文件并分配文件标识符，通过O_CREAT可以创建新文件并设定其权限(需要与掩码做按位与操作)
read
write 通过buf来进行写操作，参数包括(文件标识符，buf，size)
lseek 对文件指针进行偏移操作，可以获取文件长度，扩展文件长度等(需要写入才能生效)
stat/lstat 获取文件属性
```
### 自己写一个ls l命令
[这里]()查看代码
### 控制文件属性
```
access 与输入的宏对比得到是否有该权限
chmod 修改文件的权限(八进制修改)
chown 修改文件所有者
truncate 修改文件的长度至指定的尺寸
```
### 控制目录属性
```
chdir 修改进程的工作目录
getcwd 获取当前的工作目录
mkdir 创建一个文件夹并指定权限(与掩码进行按位与)
rename 修改oldpath至oldpath名称
```
### 遍历整个目录
```
opendir 打开目录
readdir 读取目录内容,返回一个struct,内有读到的文件信息，可以通过宏来找到特定类型的文件和目录
close 关闭目录
```
[这里]()查看代码
### dup和dup2控制文件描述符
```
dup 复制一个文件描述符到一个新的文件描述符，当然会占用一个新的文件描述符，我们也可以通过新的文件描述符来修改复制的文件描述符指向的文件，并且close一次即可关闭所有指向该文件的文件描述符(实验通过,再通过旧的文件描述符进行write操作是不合法的--write: Bad file descriptor)
```
```
dup2 重定向文件描述符,被重定向的文件描述符原来指向的文件将被自动关闭,返回一个这个被重定向的文件描述符,这是与上面的复制情况不同,这两个文件描述符是独立的,如果关闭其中一个不会影响另外一个文件描述符对文件的操作(实验通过,关闭其中一个文件描述符,但是另外一个文件描述符进行write操作是合法的)
```
### fcntl
```
fcntl可以实现复制文件描述符、或者指定的文件描述符文件状态flag、可以设置部分可选项的文件描述符文件状态flag(如O_APPEND,O_NONBLOCK)
```