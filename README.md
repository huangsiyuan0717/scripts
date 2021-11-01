# scripts
自己写了一些封装常用的函数脚本

## ros相关

## socket/TCP
1. socket的函数封装，封装成了一个TcpServer/TcpClient类，包括初始化、bind、listen、accept、send、recv等步骤（针对解决了TCP分包粘包问题解决，添加了数据报长度，添加了超时机制）
