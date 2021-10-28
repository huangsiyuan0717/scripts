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

bool TcpRead(const int sockfd, char *buffer, int *ibuflen, const int itimeout = 0){
    if (sockfd == -1) return false;

    if (itimeout > 0){
        fd_set tmpfd;

        FD_ZERO(&tmpfd);
        FD_SET(sockfd,&tmpfd);

        struct timeval timeout;
        timeout.tv_sec = itimeout; timeout.tv_usec = 0;

        int i;
        if ( (i = select(sockfd+1,&tmpfd,0,0,&timeout)) <= 0 ) return false;
    }

    (*ibuflen) = 0;
    if(Readn(sockfd, (char *)ibuflen, 4) == false) return false;

    (*ibuflen) = ntohl(*ibuflen);

    if(Readn(sockfd, buffer, (*ibuflen)) == false) return false;

    return true;
}


int main(int argc, char **argv){
    return 0;
}

