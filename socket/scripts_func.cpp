#include "scripts_func.h"

bool Readn(const int sockfd, char *buffer, const size_t n){
    int _left, n_read, idx;
    _left = n;
    idx = 0;

    while(_left > 0){
        if( (n_read = recv(sockfd, buffer + idx, _left, 0)) <= 0) return false;

        idx = n_read;
        _left -= n_read;
    }
    return true;
}

bool Writen(const int sockfd, const char *buffer, const size_t n){
    int _left, idx, n_write;
    _left = n;
    idx = 0;

    while(_left > 0){
        if((n_write = send(sockfd, buffer + idx, _left, 0)) <= 0) return false;
        idx = n_write;
        _left -= n_write;
    }
    return true;
}

bool TcpRead(const int sockfd, char *buffer, int *ibuflen, const int itimeout){
    if (sockfd == -1) return false;

    if (itimeout > 0){
        fd_set tmpfd;

        FD_ZERO(&tmpfd);
        FD_SET(sockfd,&tmpfd);

        struct timeval timeout;
        timeout.tv_sec = itimeout; timeout.tv_usec = 0;

        int i;
        if ( (i = select(sockfd+1, &tmpfd, 0, 0, &timeout)) <= 0 ) return false;
    }

    (*ibuflen) = 0;
    if(Readn(sockfd, (char *)ibuflen, 4) == false) return false;

    (*ibuflen) = ntohl(*ibuflen);

    if(Readn(sockfd, buffer, (*ibuflen)) == false) return false;

    return true;
}

bool TcpWrite(const int sockfd, const char *buffer,const int ibuflen){
    if(sockfd == -1) return false;

    fd_set tmpfd;

    FD_ZERO(&tmpfd);
    FD_SET(sockfd, &tmpfd);

    struct timeval timeout;
    timeout.tv_sec = 5; timeout.tv_usec = 0;

    if(select(sockfd + 1, 0, &tmpfd, 0, &timeout) <= 0) return false;

    int _len = 0;

    if(ibuflen == 0){
        _len = strlen(buffer);
    }else{
        _len = ibuflen;
    }

    int _len_n = htonl(_len);

    char str_buffer[_len + 4];
    memset(str_buffer, 0, sizeof(str_buffer));
    memcpy(str_buffer, &_len_n, 4);
    memcpy(str_buffer + 4, &buffer, _len);

    if(Writen(sockfd, str_buffer, _len + 4) == false) return false;

    return true;
}

TcpServer::TcpServer(){
    m_listenfd = -1;
    m_connfd = -1;
    m_socklen = 0;
    m_btimeout = false;
}

bool TcpServer::initServer(const unsigned int port){
    if(m_listenfd > 0){
        close(m_listenfd);
        m_listenfd = -1;
    }

    m_listenfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&m_servaddr, 0, sizeof(m_servaddr));
    m_servaddr.sin_family = AF_INET;
    m_servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_servaddr.sin_port = htons(port);

    if(bind(m_listenfd, (struct sockaddr *)&m_servaddr, sizeof(m_servaddr)) != 0){
        closeListen();
        return false;
    }

    if(listen(m_listenfd, 5) != 0){
        closeListen();
        return false;
    }

    m_socklen = sizeof(struct sockaddr_in);
    return true;
}

bool TcpServer::tcpAccept(){
    if(m_listenfd == -1) return false;

    if(m_connfd = accept(m_listenfd, (struct sockaddr *)&m_clientaddr, (socklen_t *)&m_socklen) < 0){
        return false;
    }
    return true;
}

char *TcpServer::getIp(){
    return(inet_ntoa(m_clientaddr.sin_addr));
}

bool TcpServer::tcpRead(char *buffer, const int itimeout){
    if(m_connfd == -1) return false;

    fd_set tmpfd;

    FD_ZERO(&tmpfd);
    FD_SET(m_connfd, &tmpfd);

    struct timeval timeout;
    timeout.tv_sec = itimeout, timeout.tv_usec = 0;

    m_btimeout = false;
    int tmpi;
    if((tmpi = select(m_connfd + 1, &tmpfd, 0, 0, &timeout)) <= 0){
        if(tmpi == 0) m_btimeout = true;
        return false;
    }

    m_bufflen = 0;

    return TcpRead(m_connfd, buffer, &m_bufflen);
}

bool TcpServer::tcpWrite(const char *buffer, const int ibufflen){
    if(m_connfd == -1) return false;

    fd_set tmpfd;

    FD_ZERO(&tmpfd);
    FD_SET(m_connfd, &tmpfd);

    struct timeval timeout;
    timeout.tv_sec = 5, timeout.tv_usec = 0;

    m_btimeout = false;
    int tmpi;
    if((tmpi = select(m_connfd + 1, &tmpfd, 0, 0, &timeout)) <= 0){
        if(tmpi == 0) m_btimeout = true;
        return false;
    }

    int len = ibufflen == 0 ? strlen(buffer) : ibufflen;

    return TcpWrite(m_connfd, buffer, len);
}

void TcpServer::closeListen(){
    if(m_listenfd > 0){
        close(m_listenfd);
        m_listenfd = -1;
    }
}

void TcpServer::closeClient(){
    if(m_connfd > 0){
        close(m_connfd);
        m_connfd = -1;
    }
}

int main(int argc, char **argv){


    return 0;
}

