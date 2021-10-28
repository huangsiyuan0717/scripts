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


int main(int argc, char **argv){
    std::cout << 1 << std::endl;
    return 0;
}

