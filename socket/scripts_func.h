#include <iostream>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

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

//TCP传输的时候可能出现分包和沾包的情况，解决的方法是传输数据的时候带上数据长度
//这个函数约定的是在数据前带上长度，然后转换成字节序列传输
//@sockfd: 已建立的socket连接
//@buffer: 接受数据的缓冲区地址
//@ibuflen: 本次成功接受数据的字节数 
//@itimeout: 接受等待超时的时间， 单位/s，缺省值0-无限等待
//返回值： true-成功  false-失败 两种情况：1）等待超时 2）socket连接断开
bool TcpRead(const int sockfd, char *buffer, int *ibuflen, const int itimeout);

//TCP传输的时候可能出现分包和沾包的情况，解决的方法是传输数据的时候带上数据长度
//这个函数约定的是在数据前带上长度，然后转换成字节序列传输
//@sockfd: 已建立的socket连接
//@buffer: 待发送数据的缓冲区地址
//@ibuflen: 本次成功接受数据的字节数，如果发送的是ascii字符串，ibuflen取0，如果是二进制流数据，ibuflen为二进制数据块的大小
//@itimeout: 接受等待超时的时间， 单位/s，缺省值0-无限等待
// 返回值：true-成功；false-失败，如果失败，表示socket连接已不可用。
bool TcpWrite(const int sockfd, const char *buffer,int *ibuflen,const int itimeout);





