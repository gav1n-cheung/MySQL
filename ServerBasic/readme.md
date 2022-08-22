# 牛客网高并发服务器

## Linux下C++开发基础

### GCC 
[笔记](https://github.com/gav1n-cheung/MySQL/blob/main/ServerBasic/lession01_LinuxBasic/lession02_gcc/gcc.md)  
> C++生成可执行文件,分别需要经过--预编译，编译，汇编，链接四个过程，与之对应的GCC流程为：
> > 预编译 -E 使用gcc -E xx.c 可以生成预编译文件 xx.i  
> > 编译  -S  使用gcc -S xx.i 可以将.i文件编译为汇编文件.s文件  
> > 汇编  -c  使用gcc -c xx.s 可以将.s文件编译为可执行的二进制文件.o  
> > 链接  -o  使用gcc -o xx.o 可以将.o文件编译为最终的可执行文件(无后缀，.c文件可以直接-o生成最后的文件)

``` bash
❯ vim test.c
❯ gcc test.c -E -o test.i
❯ ls
gcc.md  test.c  test.i
❯ gcc test.i -S -o test.s
❯ ls
gcc.md  test.c  test.i  test.s
❯ gcc test.s -c -o test.o
❯ ls
gcc.md  test.c  test.i  test.o  test.s
❯ gcc test.o -o test
❯ ls
gcc.md  test  test.c  test.i  test.o  test.s
❯ ./test
hello world!
```
### 静态库的制作
[笔记](https://github.com/gav1n-cheung/MySQL/blob/main/ServerBasic/lession01_LinuxBasic/lession03_static_lib/static_lib.md)  
> 静态库的命名规则如下:  
> linux:libxxx.a
> > lib:库前缀(固定)  
> > xxx:库名称(自定义)  
> > .a :库后缀(固定)
> 
> windows:libxxx.lib
```bash
静态库的制作：
ar rcs libxxx.a xxx.o xxx.o
    -r:将文件插入备存文件中
    -c:建立备存文件
    -s:索引文件
❯ gcc test.c -o test.o
❯ ls
gcc.md  test.c  test.o
❯ ar rcs libtest.a test.o
❯ ls
gcc.md  libtest.a  test.c  test.o
```
### 静态库的使用
[笔记](https://github.com/gav1n-cheung/MySQL/blob/main/ServerBasic/lession01_LinuxBasic/lession04_use_static_lib/use_static_lib.md)
```
❯ tree
.
├── add.c
├── div.c
├── mult.c
└── sub.c

❯ tree
.
├── add.c
├── add.o
├── div.c
├── div.o
├── mult.c
├── mult.o
├── sub.c
└── sub.o

❯ ar rcs libtest.a add.o div.o mult.o sub.o

❯ tree
.
├── add.c
├── add.o
├── div.c
├── div.o
├── libtest.a
├── mult.c
├── mult.o
├── sub.c
└── sub.o

❯ rm *.o
❯ tree
.
├── add.c
├── div.c
├── libtest.a
├── mult.c
└── sub.c

❯ gcc main.c -o app -L ./lib -l test -I ./include
    -o 生成文件
    -L 指明静态库文件路径
    -l 智能静态库文件名称(libxxx.a中的xxx)
    -I 指明头文件路径
❯ tree
.
├── app
├── include
│   └── head.h
├── lib
│   └── libtest.a
├── main.c
└── src
    ├── add.c
    ├── div.c
    ├── mult.c
    └── sub.c
```
### 制作动态库
[笔记](https://github.com/gav1n-cheung/MySQL/blob/main/ServerBasic/lession01_LinuxBasic/lession05_nonstatic_lib/nonstatic.md)
> 动态库的命名规则  
> libxxx.so  
> > lib:前缀(固定)  
> > xxx:库名称  
> > so: 库后缀(固定)  
> 
> windows:libxxx.dll  
```bash
#生成无关位置的.o文件
gcc -c fpic/-fPIC a.c b.c
#生成动态库
gcc -shared a.o b.o -o libtest.so
```
### 使用动态库
[笔记](https://github.com/gav1n-cheung/MySQL/blob/main/ServerBasic/lession01_LinuxBasic/lession05_nonstatic_lib/nonstatic.md)
```bash
#仍然报错，因为动态库的路径没有设置
❯ gcc main.c -o app -l test -L ./lib -I ./include 
#使用ldd命令查看执行文件的链接库信息
❯ ldd app 
    linux-vdso.so.1 (0x00007ffe80395000)
    libcalc.so => not found
    libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fcad191e000)
    /lib64/ld-linux-x86-64.so.2 (0x00007fcad1afd000)
#使用echo命令查看动态库的链接信息
❯ echo &LD_LIBRATY_PATH
#使用export临时指定动态链接库路径
❯ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/cheung/program/server/server_lession/lession05_nonstatic_lib/library/lib/
# 再次查看ldd app既可得到结果
❯ ldd app
    linux-vdso.so.1 (0x00007ffcaf3f1000)
    libcalc.so => /home/cheung/program/server/server_lessionlession05_nonstatic_lib/library/lib/libcalc.so (0x00007f3618d1c000)
    libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f3618b44000)
    /lib64/ld-linux-x86-64.so.2 (0x00007f3618d28000)
#在shell配置文件中加入该环境变量，用户级别的路径设置
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/cheung/program/server/server_lession/lession05_nonstatic_lib/library/lib/
#修改系统文件，实现系统级别的动态库路径设置
sudo vim /etc/profile   
#在文件末尾添加 
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/cheung/program/server/server_lession/lession05_nonstatic_lib/library/lib/
#即可
```