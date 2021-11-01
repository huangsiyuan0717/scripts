#pragma once

#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


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
bool TcpRead(const int sockfd, char *buffer, int *ibuflen, const int itimeout = 0);

//TCP传输的时候可能出现分包和沾包的情况，解决的方法是传输数据的时候带上数据长度
//这个函数约定的是在数据前带上长度，然后转换成字节序列传输
//@sockfd: 已建立的socket连接
//@buffer: 待发送数据的缓冲区地址
//@ibuflen: 本次成功接受数据的字节数，如果发送的是ascii字符串，ibuflen取0，如果是二进制流数据，ibuflen为二进制数据块的大小
// 返回值：true-成功；false-失败，如果失败，表示socket连接已不可用。
bool TcpWrite(const int sockfd, const char *buffer, const int *ibuflen = 0);

//socket通信的服务端
class TcpServer{
private:
    int m_socklen;                  //结构体sockaddr_in的大小
    struct sockaddr_in m_clientaddr;    // 客户端的地址信息
    struct sockaddr_in m_servaddr;    // 服务店的地址信息

public:
    int m_listenfd;        //服务端监听的socket
    int m_connfd;          //客户端连接上来的socket
    int m_btimeout;        //调用Read和Write方法时，失败的原因是否是超时： true-超时  false-未超时
    int m_bufflen;          //调用Read后接受到的报文大小，单位：字节

    TcpServer();

    //服务端初始化： port-监听的端口
    bool initServer(const unsigned int port);

    //阻塞等待客户端的连接请求
    //返回true-有新的客户端连接   false-失败，accept被中断，如果accept被中断则可以重新accept
    bool tcpAccept();

    //获取客户端ip地址，返回字符串型"192.168.1.10"这种
    char *getIp();

    // 接收客户端发送过来的数据。
    // buffer：接收数据缓冲区的地址，数据的长度存放在m_buflen成员变量中。
    // itimeout：等待数据的超时时间，单位：秒，缺省值是0-无限等待。
    // 返回值：true-成功；false-失败，失败有两种情况：1）等待超时，成员变量m_btimeout的值被设置为true；2）socket连接已不可用。
    bool tcpRead(char *buffer, const int itimeout);

    // 向客户端发送数据。
    // buffer：待发送数据缓冲区的地址。
    // ibuflen：待发送数据的大小，单位：字节，缺省值为0，如果发送的是ascii字符串，ibuflen取0，如果是二进制流数据，ibuflen为二进制数据块的大小。
    // 返回值：true-成功；false-失败，如果失败，表示socket连接已不可用。
    bool tcpWrite(const char *buffer, const int ibufflen = 0);

    // 关闭监听的socket，即m_listenfd，常用于多进程服务程序的子进程代码中。
    void closeListen();

    // 关闭客户端的socket，即m_connfd，常用于多进程服务程序的父进程代码中。
    void closeClient();

    ~TcpServer();  // 析构函数自动关闭socket，释放资源。

};


class TcpClient{

};


