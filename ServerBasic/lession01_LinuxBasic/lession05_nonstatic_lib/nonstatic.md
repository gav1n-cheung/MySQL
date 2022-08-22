# 动态库的制作  
## 命名规则  
* linux: libxxx.so  
    lib: 前缀（固定）  
    xxx: 库的名字，自定义
    .so: 后缀（固定）  
    在linux下是一个可执行文件
* windows : libxxx.dll
## 动态库的制作
* gcc得到.o文件，得到和位置无关的代码
```
gcc -c -fpic/-fPIC a.c b.c
```
* gcc得到动态库
```
gcc -shared a.o b.o -o libcalc.so
```

## 动态库的使用
```
生成可执行文件
gcc main.cpp -o app -I ./include -l calc -L ./lib 
但是会仍然报错：./app: error while loading shared libraries: libcalc.so: cannot open shared object file: No such file or directory
即找不到动态库
```

### 通过修改LD_LIBRARY_PATH连接动态库
```
# ldd app查看链接库
❯ ldd app
        linux-vdso.so.1 (0x00007ffe80395000)
        libcalc.so => not found
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fcad191e000)
        /lib64/ld-linux-x86-64.so.2 (0x00007fcad1afd000)
# 使用echo查看系统库路径,得到空
echo &LD_LIBRATY_PATH
# 使用export修改路径，再次查看即可得到修改的路径
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/cheung/program/server/server_lession/lession05_nonstatic_lib/library/lib/
# 再次查看ldd app既可得到结果
❯ ldd app
        linux-vdso.so.1 (0x00007ffcaf3f1000)
        libcalc.so => /home/cheung/program/server/server_lession/lession05_nonstatic_lib/library/lib/libcalc.so (0x00007f3618d1c000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f3618b44000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f3618d28000)

此时执行可执行文件就可以运行了,但是该环境变量只是临时的
```
### 用户级别的环境变量配置
```
在shell配置文件中加入该环境变量即可
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/cheung/program/server/server_lession/lession05_nonstatic_lib/library/lib/
```
### 系统级别的环境变量设置
```
sudo vim /etc/profile   
在文件末尾添加 export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/cheung/program/server/server_lession/lession05_nonstatic_lib/library/lib/
即可
```