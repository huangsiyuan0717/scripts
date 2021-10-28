#include <iostream>
#include <sys/socket.h>

//从socket中读取数据，即recv()数据
//但是可能出现网络缓冲满了等异常问题，导致数据一次不能完全读取完
//利用一个循环读取完整长度字节的数据
//@sockfd: 已建立的的socket连接
//@buffer： 接受数据缓冲区的地址
//@n: 本次接收的字节数
//返回值： 成功接受n个字节的返回true， 连接异常返回false；
bool Readn(const int sockfd, char *buffer, const size_t n);

//向socket中写数据，即send()数据
//但是可能出现网络缓冲满了等异常问题，导致数据一次不能完全发送完
//利用一个循环发送完整长度字节的数据
//@sockfd: 已建立的的socket连接
//@buffer： 接受数据缓冲区的地址
//@n: 本次接收的字节数
//返回值： 成功发送n个字节的返回true， 连接异常返回false；
bool Writen(const int sockfd, const char *buffer, const size_t n);

bool TcpRead(const int sockfd, char *buffer, int *ibuflen, const int itimeout=0);

bool TcpWrite(const int sockfd, const char *buffer,int *ibuflen,const int itimeout=0);





