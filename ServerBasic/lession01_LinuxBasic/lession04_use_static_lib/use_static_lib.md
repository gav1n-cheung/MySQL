```
.
├── app
├── include
│   └── head.h
├── lib
│   └── libcal.a
├── main.c
└── src
    ├── add.c
    ├── div.c
    ├── mult.c
    └── sub.c
```
文件结构如上所示，使用ar进行静态库的创建，将头文件放入include中，但在main.c中include是相对路径，则需要在编译时添加-I参数指明寻找头文件的路径，需要注意的是如果是在上面的路径进行.o文件的创建，则会因为找不到头文件报错，因此要加上参数-I指明头文件的路径
```
# 在library/lib文件夹下执行
gcc -c ../src/add.c ../src/add.c ../src/mult.c ../src/sub.c -I ../include
# 然后在该文件夹下生成静态库
ar rcs libcalc.a 
# 删除.o文件
rm *.o
# 在library文件夹下执行
gcc main.c -o app -I ./include 
```
然后我们引用静态库，使用-l参数
```
gcc main.c -o app -I ./include -l calc
```
但是也会报错找不到函数，则需要指明静态库的路径，使用-L表明该路径即可
```
gcc main.c -o app -I ./include -l calc -L ./lib
```
生成app文件直接执行即可