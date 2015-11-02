#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ae/libae.h"

#define MAX_BUFFER_SIZE 4096

void echo_service(aeEventLoop *ev, int fd, void *privdata, int mask)
{
    char buffer[MAX_BUFFER_SIZE];

    bool readMore = true;
    while (readMore)
    {
        int len = ::read(fd, buffer, MAX_BUFFER_SIZE);
        if (len < 0)
        {
            readMore = false;
            ::perror("read error 1: ");
            aeDeleteFileEvent(ev, fd, mask);
            ::close(fd);
        }
        else if (len == 0)  // closed
        {
            readMore = false;
            ::perror("read error 1: ");
            aeDeleteFileEvent(ev, fd, mask);
            ::close(fd);
        }
        else
        {
            printf("get data on [%d] : %s\n", fd, buffer);
            len = anetWrite(fd, buffer, len); // should check return value
            if (len < MAX_BUFFER_SIZE)
            {
                readMore = false;
            }
        }
    }
}

void accept_callback(aeEventLoop *ev, int fd, void *privdata, int mask)
{
    int port;
    char cip[128];
    char neterr[ANET_ERR_LEN];

    int clientfd = anetTcpAccept(neterr, fd, cip, sizeof(cip), &port);
    if (clientfd == AE_ERR)
    {
        return;
    }
    printf("accept one %d, on port [%d]\n", clientfd, port);

    anetEnableTcpNoDelay(neterr, clientfd);

    char *noparam = NULL;
    if (aeCreateFileEvent(ev, clientfd, AE_READABLE, echo_service, noparam) == AE_ERR)
    {
        ::close(clientfd);
        return;
    }
}

int main()
{
    char srvddr[] = "0.0.0.0";
    int port = 9999;

    char neterr[ANET_ERR_LEN];
    int listen_fd = anetTcpServer(neterr, port, srvddr, 1024);
    if (listen_fd < 0)
    {
        printf("anetTcpServer error : %s\n", neterr);
        perror("open listening socket");
        exit(0);
    }

    aeEventLoop *ev = aeCreateEventLoop(1024);
    printf("i/o multiplex : %s\n", aeGetApiName());

    aeCreateFileEvent(ev, listen_fd, AE_READABLE, accept_callback, &ev);

    printf("server is listening on [%s:%d]\n", srvddr, port);
    aeMain(ev);		// event loop

    printf("hello world\n");
}