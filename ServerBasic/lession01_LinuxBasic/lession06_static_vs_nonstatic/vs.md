# 静态库和动态库的对比
静态库和动态库区别来自链接阶段如何处理，连接成可执行程序。分别称为静态链接方式和动态链接方式。
## 使用的原则
* 
## 静态库的优缺点
* 优点：
```
静态库被打包到应用程序中加载速度快
发布程序无需提供静态库，移植方便
```
* 缺点：
```
消耗系统资源，浪费内存
更新、部署、发布麻烦
```
## 动态库的优缺点
* 优点：
```
可以实现进程间资源共享(共享库)
更新、部署、发布简单
可以控制何时加载动态库
```
* 缺点：
```
加载速度比静态库慢
发布程序时需要提供依赖的动态库
```