#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ae/libae.h"

char neterr[ANET_ERR_LEN];

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

    ::close(clientfd);
}

int main()
{
    char srvddr[] = "0.0.0.0";
    int port = 9999;

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