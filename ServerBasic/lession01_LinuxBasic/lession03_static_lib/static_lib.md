# 静态库
## 命名规则
```
linux:libxxx.a  
    lib : 前缀(固定)  
    xxx : 库的名称，自定义  
    .a  : 后缀(固定)  
windows : libxxx.lib  
```
## 静态库的制作  
 gcc 获得.o 文件
 将.o文件打包，使用ar工具(archive)
```
ar rcs libxxx.a xxx.o xxx.o
r - 将文件插入备存文件中
c - 建立备存文件
s - 索引
```
