#include "msgcomm.h"

int main()
{
	struct msg_s rcv;

	memset(rcv.text, 0, sizeof(rcv.text));

	struct msg_s ret;

	// msgtype of server -> client is S2C: `456`
	ret.msgtype = S2C;
	// initiate ret
	char retmsg[] = "Server have received the msg.";
	strcpy(ret.text, retmsg);
	ret.length = strlen(ret.text);

	// id of msg queue
	int qid;

	qid = msgget(MSGKEY, IPC_CREAT | 0666);

	char output[] = "test_out.txt";
	FILE *out = fopen(output, "w");

	// create msg fail
	if(qid == -1)
	{
		printf("create message queue fail.\n");
		return 2;
	}

	// listening 
	while(1)
	{

		// msgtpye from client is C2S: `123`
		msgrcv(qid, &rcv, sizeof(rcv.text), C2S, MSG_NOERROR);
		
		printf("[Server] Server has received a message from the message queue.\n"); /* process: %d.\n", rcv.pid);*/
		printf("[Server] The length is: %d.\n", rcv.length);
		
		printf("[Server] Text will be written is: %s.\n", rcv.text);
		
		fwrite(rcv.text, sizeof(char), rcv.length, out);
		
		// tell client the msg have been received
		msgsnd(qid, &ret, sizeof(ret.text), 0);
		
		// nothing more will be sended
		if(rcv.length < BUFFER_SIZE - sizeof(long))
			break;
		// clear the rcv.text
		memset(rcv.text, 0, sizeof(rcv.text));
	}
	
	fclose(out);
	
	return 0;
}	
