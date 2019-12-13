//msgcomm.h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#define BUFFER_SIZE 1024
#define MSGKEY 1234
#define C2S 123
#define S2C 456

struct msg_s {
	long msgtype;
	int length;
	char text[BUFFER_SIZE];
};
