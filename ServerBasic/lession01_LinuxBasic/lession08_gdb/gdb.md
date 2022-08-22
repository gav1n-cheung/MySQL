# GDB调试
## 准备工作
通常，为了调试而编译时，我们关掉编译器的优化选项`-o`，并打开调试选项`-g`。另外，`-Wall`在尽量不影响程序行为的情况下选项打开所有warning，也可以发现许多问题，避免一些不必要的BUG
```
gcc -g -Wall program.c -o program
```
`-g` 选项的作用是在可执行文件中加入源代码的信息，比如可执行文件中第几条机
器指令对应源代码的第几行，但并不是把整个源文件嵌入到可执行文件中，所以在调
试时必须保证 gdb 能找到源文件。
## 相关方法
```
❯ gcc test.c -o test -g
❯ gcc test.c -o test1
❯ ll -h test test1
-rwxr-xr-x 1 cheung cheung 18K Jun 28 09:27 test
-rwxr-xr-x 1 cheung cheung 17K Jun 28 09:27 test1
# 是否加入-g参数对最后的可执行文件的大小是有影响的
❯ gdb test 
(gdb) set args 10 20 # 设定调试参数
(gdb) show args      # 显示设定的参数
Argument list to give program being debugged when it is started is "10 20".
(gdb) q              # 退出
(gdb) l/list         # 查看当前文件并加上行号
(gdb) l/list 20      # 从指定行开始查看当前文件
(gdb) l/list main    # 从指定的函数开始查看当前文件
```

```
# 这里gcc不能识别c++的函数，因此使用g++
❯ g++ bubble.cpp main.cpp select.cpp -o main -g
❯ gdb main
# 默认查看的是main所在的cpp的文件
(gdb) l
    1       #include <iostream>
    2       #include "sort.h"
    3
    4       using namespace std;
    5
    6       int main() {
    7
    8           int array[] = {12, 27, 55, 22, 67};
(gdb) l bubble.cpp:1
# 从第1行开始查看bubble.cpp   
    1       #include "sort.h"
    2       #include <iostream>
    3
    4       using namespace std;
    5
    6       void bubbleSort(int *array, int len) {
(gdb) l select.cpp:selectSort
# 也可以查看指定文件的函数，和前面的查看本文件区别不大
    1       #include "sort.h"
    2       #include <iostream>
    3
    4       using namespace std;
    5
    6       void selectSort(int *array, int len) {
(gdb) list main.cpp:1
    1       #include <iostream>
    2       #include "sort.h"
    3
    4       using namespace std;
    5
    6       int main() {
    7
    8           int array[] = {12, 27, 55, 22, 67};
    9           int len = sizeof(array) / sizeof(int);
    10
(gdb) show list
    Number of source lines gdb will list by default is 10.
(gdb) show listsize
    Number of source lines gdb will list by default is 10.
(gdb) set listsize 20
(gdb) list main.cpp:1
    1       #include <iostream>
    2       #include "sort.h"
    3
    4       using namespace std;
    5
    6       int main() {
    7
    8           int array[] = {12, 27, 55, 22, 67};
    9           int len = sizeof(array) / sizeof(int);
    10
(gdb) show list
    Number of source lines gdb will list by default is 10.
(gdb) show listsize
    Number of source lines gdb will list by default is 10.
(gdb) set listsize 20
    # 修改显示的行数
(gdb) l
    11          bubbleSort(array, len);
    12          
    13          // 遍历
    14          cout << "冒泡排序之后的数组: ";
    15          for(int i = 0; i < len; i++) {
    16              cout << array[i] << " ";
    17          }
    18          cout << endl;
    19          cout << "===================================" << endl;
    20
    21          int array1[] = {25, 47, 36, 80, 11};
(gdb) show list
    Number of source lines gdb will list by default is 20.
```
## 设置断点
```
# 在当前文件中打断点，可以使用break/b 行号/函数名的方式
(gdb) break 9
Breakpoint 2 at 0x12e8: file main.cpp, line 9.
# 使用i/info b查看当前已有的断点信息
(gdb) info b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x00000000000012c5 in main() at main.cpp:8
2       breakpoint     keep y   0x00000000000012e8 in main() at main.cpp:9
(gdb) break main
Note: breakpoint 1 also set at pc 0x12c5.
Breakpoint 3 at 0x12c5: file main.cpp, line 8.
(gdb) info b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x00000000000012c5 in main() at main.cpp:8
2       breakpoint     keep y   0x00000000000012e8 in main() at main.cpp:9
3       breakpoint     keep y   0x00000000000012c5 in main() at main.cpp:8
# 使用文件名:行号/函数名来打其他文件的断点
(gdb) break bubble.cpp:11
Breakpoint 4 at 0x11e3: file bubble.cpp, line 11.
(gdb) info b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x00000000000012c5 in main() at main.cpp:8
2       breakpoint     keep y   0x00000000000012e8 in main() at main.cpp:9
3       breakpoint     keep y   0x00000000000012c5 in main() at main.cpp:8
4       breakpoint     keep y   0x00000000000011e3 in bubbleSort(int*, int) at bubble.cpp:11
(gdb) break bubble.cpp:bubbleSort
Breakpoint 5 at 0x1180: file bubble.cpp, line 8.
(gdb) info b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x00000000000012c5 in main() at main.cpp:8
2       breakpoint     keep y   0x00000000000012e8 in main() at main.cpp:9
3       breakpoint     keep y   0x00000000000012c5 in main() at main.cpp:8
4       breakpoint     keep y   0x00000000000011e3 in bubbleSort(int*, int) at bubble.cpp:11
5       breakpoint     keep y   0x0000000000001180 in bubbleSort(int*, int) at bubble.cpp:8
# 删除断点，使用delete/d 断点编号即可
(gdb) delete 1
(gdb) info b
Num     Type           Disp Enb Address            What
2       breakpoint     keep y   0x00000000000012e8 in main() at main.cpp:9
3       breakpoint     keep y   0x00000000000012c5 in main() at main.cpp:8
4       breakpoint     keep y   0x00000000000011e3 in bubbleSort(int*, int) at bubble.cpp:11
5       breakpoint     keep y   0x0000000000001180 in bubbleSort(int*, int) at bubble.cpp:8
# 使断点失效，使用disable 断点编号
(gdb) disable 5
(gdb) i b
Num     Type           Disp Enb Address            What
4       breakpoint     keep y   0x00000000000011e3 in bubbleSort(int*, int) at bubble.cpp:11
5       breakpoint     keep n   0x0000000000001180 in bubbleSort(int*, int) at bubble.cpp:8
# 使断点生效，使用enable 断点编号
(gdb) enable 5
(gdb) i b
Num     Type           Disp Enb Address            What
4       breakpoint     keep y   0x00000000000011e3 in bubbleSort(int*, int) at bubble.cpp:11
5       breakpoint     keep y   0x0000000000001180 in bubbleSort(int*, int) at bubble.cpp:8
# 设置条件断点，使用b/break 行号 条件
(gdb) break 16 if i=3
Breakpoint 7 at 0x1322: file main.cpp, line 16.
(gdb) i b
Num     Type           Disp Enb Address            What
7       breakpoint     keep y   0x0000000000001322 in main() at main.cpp:16
        stop only if i=3
```
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
(gdb) i b
No breakpoints or watchpoints.
(gdb) start
Temporary breakpoint 1 at 0x12c5: file main.cpp, line 8.
Starting program: /home/cheung/program/server/server_lession/lession08_gdb/main 

Temporary breakpoint 1, main () at main.cpp:8
8           int array[] = {12, 27, 55, 22, 67};
(gdb) l
3
4       using namespace std;
5
6       int main() {
7
8           int array[] = {12, 27, 55, 22, 67};
9           int len = sizeof(array) / sizeof(int);
10
11          bubbleSort(array, len);
12          
(gdb) c
Continuing.
冒泡排序之后的数组: 12 22 27 55 67 
===================================
选择排序之后的数组: 11 25 36 47 80 
[Inferior 1 (process 186853) exited normally]
(gdb) run
Starting program: /home/cheung/program/server/server_lession/lession08_gdb/main 
冒泡排序之后的数组: 12 22 27 55 67 
===================================
选择排序之后的数组: 11 25 36 47 80 
[Inferior 1 (process 186963) exited normally]
(gdb) b 8
Breakpoint 2 at 0x5555555552c5: file main.cpp, line 8.
(gdb) b bubble.cpp:bubbleSort
Breakpoint 3 at 0x555555555180: file bubble.cpp, line 8.
(gdb) b 16
Breakpoint 4 at 0x555555555322: file main.cpp, line 16.
(gdb) i b
Num     Type           Disp Enb Address            What
2       breakpoint     keep y   0x00005555555552c5 in main() at main.cpp:8
3       breakpoint     keep y   0x0000555555555180 in bubbleSort(int*, int) at bubble.cpp:8
4       breakpoint     keep y   0x0000555555555322 in main() at main.cpp:16
# 此时程序就停在了第八行断点处，而这行程序没有被执行
(gdb) run
Starting program: /home/cheung/program/server/server_lession/lession08_gdb/main 

Breakpoint 2, main () at main.cpp:8
8           int array[] = {12, 27, 55, 22, 67};
(gdb) c
Continuing.

Breakpoint 3, bubbleSort (array=0x7fffffffdf00, len=5) at bubble.cpp:8
8           for (int i = 0; i < len - 1; i++) {
(gdb) list bubble.cpp:bubbleSort
1       #include "sort.h"
2       #include <iostream>
3
4       using namespace std;
5
6       void bubbleSort(int *array, int len) {
7
8           for (int i = 0; i < len - 1; i++) {
9                       for (int j = 0; j < len - 1 - i; j++) {
10                              if (array[j] > array[j + 1]) {
(gdb) next
9                       for (int j = 0; j < len - 1 - i; j++) {
(gdb) step
10                              if (array[j] > array[j + 1]) {
(gdb) c
Continuing.

Breakpoint 4, main () at main.cpp:16
16              cout << array[i] << " ";
(gdb) i b
Num     Type           Disp Enb Address            What
2       breakpoint     keep y   0x00005555555552c5 in main() at main.cpp:8
        breakpoint already hit 1 time
3       breakpoint     keep y   0x0000555555555180 in bubbleSort(int*, int) at bubble.cpp:8
        breakpoint already hit 1 time
4       breakpoint     keep y   0x0000555555555322 in main() at main.cpp:16
        breakpoint already hit 1 time

(gdb) step
15          for(int i = 0; i < len; i++) {
(gdb) step

Breakpoint 4, main () at main.cpp:16
16              cout << array[i] << " ";
(gdb) c
Continuing.

Breakpoint 4, main () at main.cpp:16
16              cout << array[i] << " ";
(gdb) print i
$1 = 2
(gdb) c
Continuing.

Breakpoint 4, main () at main.cpp:16
16              cout << array[i] << " ";
(gdb) print i
$2 = 3
# 使用until不能跳出有断点的循环，首先要使断点失效或删除断点
(gdb) i b
Num     Type           Disp Enb Address            What
2       breakpoint     keep y   0x00005555555552c5 in main() at main.cpp:8
        breakpoint already hit 1 time
3       breakpoint     keep y   0x0000555555555180 in bubbleSort(int*, int) at bubble.cpp:8
        breakpoint already hit 1 time
4       breakpoint     keep y   0x0000555555555322 in main() at main.cpp:16
        breakpoint already hit 5 times
(gdb) del 4
(gdb) until
15          for(int i = 0; i < len; i++) {
(gdb) s
18          cout << endl;

(gdb) d 3
(gdb) i b
Num     Type           Disp Enb Address            What
2       breakpoint     keep y   0x00005555555552c5 in main() at main.cpp:8
        breakpoint already hit 1 time
(gdb) run 
(gdb) n
9           int len = sizeof(array) / sizeof(int);
(gdb) n
11          bubbleSort(array, len);
# 这里next没有进入函数直接执行完毕了
(gdb) n
14          cout << "冒泡排序之后的数组: ";

(gdb) run
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/cheung/program/server/server_lession/lession08_gdb/main 

Breakpoint 2, main () at main.cpp:8
8           int array[] = {12, 27, 55, 22, 67};
(gdb) s
9           int len = sizeof(array) / sizeof(int);
(gdb) s
11          bubbleSort(array, len);
# step会进入函数内部执行
(gdb) s
bubbleSort (array=0x7fffffffdf00, len=5) at bubble.cpp:8
8           for (int i = 0; i < len - 1; i++) {
# 使用finish跳出函数体
(gdb) finish
Run till exit from #0  bubbleSort (array=0x7fffffffdf00, len=5) at bubble.cpp:8
main () at main.cpp:14
14          cout << "冒泡排序之后的数组: ";
```

```
❯ gdb test
GNU gdb (Debian 10.1-1.7) 10.1.90.20210103-git
Copyright (C) 2021 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
--Type <RET> for more, q to quit, c to continue without paging--
Type "apropos word" to search for commands related to "word"...
Reading symbols from test...
(gdb) b 18
Breakpoint 1 at 0x11d5: file test.c, line 18.
(gdb) i b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x00000000000011d5 in main at test.c:18
(gdb) b 21
Breakpoint 2 at 0x11f9: file test.c, line 21.
(gdb) d 2
(gdb) b 21 if i=3
Breakpoint 3 at 0x11f9: file test.c, line 21.
(gdb) i b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x00000000000011d5 in main at test.c:18
3       breakpoint     keep y   0x00000000000011f9 in main at test.c:21
        stop only if i=3
(gdb) run
Starting program: /home/cheung/program/server/server_lession/lession08_gdb/test 
argc = 1
a = 10, b = 30

Breakpoint 1, main (argc=1, argv=0x7fffffffe018) at test.c:18
18          printf("a + b = %d\n", a + b);
(gdb) print a
$1 = 10
(gdb) print b
$2 = 30
(gdb) n
a + b = 40
20          for(int i = 0; i < a; ++i) {

# 使用display设置自动变量
(gdb) display a
1: a = 10
(gdb) display b
2: b = 30
(gdb) n

Breakpoint 3, main (argc=1, argv=0x7fffffffe018) at test.c:21
21              printf("i = %d\n", i);
1: a = 10
2: b = 30
(gdb) n
i = 3
23              int res = test(i);
1: a = 10
2: b = 30
# 查看设置的自动变量
(gdb) i display
Auto-display expressions now in effect:
Num Enb Expression
1:   y  a
2:   y  b
# 使用undisplay删除自动变量
(gdb) undisplay 1
(gdb) i display
Auto-display expressions now in effect:
Num Enb Expression
2:   y  b
(gdb) n
24              printf("res value: %d\n", res);
2: b = 30

(gdb) run
Starting program: /home/cheung/program/server/server_lession/lession08_gdb/test 
argc = 1
a = 10, b = 30
a + b = 40

Breakpoint 1, main (argc=1, argv=0x7fffffffe018) at test.c:21
21              printf("i = %d\n", i);
# 使用set var 设置变量值
(gdb) set var i = 9
(gdb) print i
$1 = 9
(gdb) n
i = 9
23              int res = test(i);
(gdb) n
24              printf("res value: %d\n", res);
```