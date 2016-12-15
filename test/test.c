#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <error.h>
#include <errno.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 30

int main(int argc, char *argv[])
{
        int s[2];
        s[0] = strtol(argv[1], NULL, 10);
        s[1] = strtol(argv[2], NULL, 10);
        printf("argv[1]: %s\n", argv[1]);
        printf("argv[2]: %s\n", argv[2]);

        printf("test sockpair: s[0]: %d, s[1]: %d.\n", s[0], s[1]);
        close(s[0]);

        int r = -1;
        char *buf = (char *)calloc(1, BUF_SIZE);
        while (r == -1) {
		r = read(s[1], buf, BUF_SIZE);
                printf("pid %d read from socket error: %s\n",
                       getpid(), strerror(errno));
        }

        printf("pid %d read string in same process: %s\n", getpid(), buf);
        printf("test successed, %d\n", getpid());
}
