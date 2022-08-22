# Makefile

## 什么是Makefile
一个工程中的源文件不计其数，其按类型、功能、模块分别放在若干个目录中，
Makefile 文件定义了一系列的规则来指定哪些文件需要先编译，哪些文件需要后编
译，哪些文件需要重新编译，甚至于进行更复杂的功能操作，因为 Makefile 文件就
像一个 Shell 脚本一样，也可以执行操作系统的命令。  
◼ Makefile 带来的好处就是“自动化编译” ，一旦写好，只需要一个 make 命令，整
个工程完全自动编译，极大的提高了软件开发的效率。 make 是一个命令工具，是一个
解释 Makefile 文件中指令的命令工具，一般来说，大多数的 IDE 都有这个命令，
比如 Delphi 的 make， Visual C++ 的 nmake， Linux 下 GNU 的 make。
## makefile文件规则
* 文件命名  
makefile 或 Makefile
* Makefile规则  
* *  一个Makefile文件中可以有一个或多个规则
```
目标 ...: 依赖...
    命令(Shell命令)
    ...
```
* * 目标: 最终要生成的文件(伪目标除外)
* * 依赖：生成目标所需要的文件或是目标
* * 命令：通过执行命令对依赖操作生成目标(命令前必须使用Tab缩进)
* Makefile中的其他规则一般都是为第一条规则服务的
```
app:add.c div.c mult.c div.c main.c
	gcc sub.c div.c mult.c add.c main.c -o app
```
## makefile工作原理
命令在执行之前，需要先检查规则中的依赖是否存在  
 如果存在，执行命令  
 如果不存在，向下检查其它的规则，检查有没有一个规则是用来生成这个依赖的,
如果找到了，则执行该规则中的命令  
◼ 检测更新，在执行规则中的命令时，会比较目标和依赖文件的时间  
 如果依赖的时间比目标的时间晚，需要重新生成目标  
 如果依赖的时间比目标的时间早，目标不需要更新，对应规则中的命令不需要被
执行
```
app:add.o div.o mult.o div.o main.o sub.o
	gcc sub.o div.o mult.o add.o main.o -o app

sub.o:sub.c
	gcc -c sub.c -o sub.o
add.o:add.c
	gcc -c add.c -o add.o
mult.o:mult.c
	gcc -c mult.c -o mult.o
div.o:div.c
	gcc -c div.c -o div.o
main.o:main.c
	gcc -c main.c -o main.o
```

```
# 如果直接执行make，则会检查时间跳过make过程
❯ make
make: 'app' is up to date.
# 如果修改了main.c，在执行make,则会检测到main.c的时间比main.o时间晚,则会执行发生了修改的部分，因此比第一种makefile的效率更高，虽然写起来更麻烦一点
❯ make
gcc -c main.c -o main.o
gcc sub.o div.o mult.o add.o main.o -o app
```
## 变量
```
* 自定义变量  
    变量名=变量值 var=hello
* 预定义变量
    AR:归档维护程序的名称，默认值为ar
    CC:C编译器的名称，默认值为cc
    CXX:C++编译器的名称，默认值为g++
    $@:目标的完整名称
    $<:第一个依赖文件的名称
    $^:所有依赖文件
* 获取变量的值
    $(变量名)
```
```
app:main.c a.c b.c
    gcc -c main.c a.c b.c
# 用变量来写makefile
app:mian.c a.c b.c
    $(CC) -c $^ -o $@
```
```
# 定义变量
src=add.o div.o mult.o div.o main.o sub.o
target=app
$(target):$(src)
	$(CC) $^ -o $@

sub.o:sub.c
	gcc -c sub.c -o sub.o
add.o:add.c
	gcc -c add.c -o add.o
mult.o:mult.c
	gcc -c mult.c -o mult.o
div.o:div.c
	gcc -c div.c -o div.o
main.o:main.c
	gcc -c main.c -o main.o
```
## 模式匹配
```
%.o:%.c
    - %:通配符，匹配一个字符串
    - 两个%匹配的是同一个字符串
%.o:%.c
    gcc -c $< -o $@

sub.o:sub.c
	gcc -c sub.c -o sub.o
add.o:add.c
	gcc -c add.c -o add.o
mult.o:mult.c
	gcc -c mult.c -o mult.o
div.o:div.c
	gcc -c div.c -o div.o
main.o:main.c
	gcc -c main.c -o main.o
```
```
# 定义变量
src=add.o div.o mult.o div.o main.o sub.o
target=app
$(target):$(src)
	$(CC) $^ -o $@
## 由于上面的依赖是缺失的，因此makefile向下找依赖，则会自动匹配%，然后通过$<拿到第一项依赖（这里只有一项），然后通过$@拿到目标，这两者的文件名是相同的。
%.o:%.c
	$(CC) -c $< -o $@
```
## 函数
```
$(wildcard PATTERN...)
 功能：获取指定目录下指定类型的文件列表
 参数： PATTERN 指的是某个或多个目录下的对应的某种类型的文件，如果有多
个目录，一般使用空格间隔
 返回：得到的若干个文件的文件列表，文件名之间使用空格间隔
 示例：
$(wildcard *.c ./sub/*.c)
返回值格式: a.c b.c c.c d.c e.c f.c

 $(patsubst <pattern>,<replacement>,<text>)
 功能：查找<text>中的单词(单词以“空格”、“Tab”或“回车”“换行”分隔)是否符合
模式<pattern>，如果匹配的话，则以<replacement>替换。
 <pattern>可以包括通配符`%`，表示任意长度的字串。如果<replacement>
中也包含`%`，那么， <replacement>中的这个`%`将是<pattern>中的那个%
所代表的字串。 (可以用`\`来转义，以`\%`来表示真实含义的`%`字符)
 返回：函数返回被替换过后的字符串
 示例：
$(patsubst %.c, %.o, x.c bar.c)
返回值格式: x.o bar.o
```
```
src=$(wildcard ./*.c)
objs=$(patsubst %.c,%.o,$(src))
target=app
$(target):$(objs)
	$(CC) $^ -o $@
%.o:%.c
	$(CC) -c $< -o $@
#生成伪目标，避免与外部文件对比
.PHONY:clean
clean:
	rm $(objs) -f
```
