

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <mqueue.h>

#include <iostream>
#include <cstring>
#include <string>

#include "MyMessage.hpp"


using std::cout, std::cerr, std::cin, std::endl;
using std::string;


int main()
{
	//
	//string queue_name = "My SuperCool Queue, OH JOY";
	string queue_name = "/MySuperCoolQueueOHJOY";
	size_t queue_perms_mode = 0600;
	
	//	Note: mq_maxmsg must be less than the value currently set in `sysctl fs.mqueue.msg_max`
	mq_attr queue_attributes;
	queue_attributes.mq_flags = O_NONBLOCK;					// Q flags
	queue_attributes.mq_maxmsg = 10;						// # of messages we can queue, at most
	queue_attributes.mq_msgsize = sizeof(MyMessage);		// Size of each message
	queue_attributes.mq_curmsgs = 0;						// Ignored by open
	
	// mqd_t mq_open(const char *name, int oflag);
	// mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);
	mqd_t qid = mq_open(
		queue_name.c_str(),		// Name of queue
		O_CREAT | O_RDWR,		// O Flags
		queue_perms_mode,		// Linux file permissions mode for the queue
		&queue_attributes		// The specified attribute (above)
	);
	
	cout << "QID is: " << qid << endl;
	
	if ( qid < 0 ) {
		perror(string("Failed to open message queue (" + queue_name + ")").c_str());
		exit(1);
	}
	
	MyMessage message;
	message.a = 387632;
	message.b = 38723.12733;
	strcpy(message.c, "Hello, this is a message from the sender!");
	int send_result = mq_send(
		qid,													// Message Queue ID
		reinterpret_cast<char *>(&message), sizeof(MyMessage), 	// Pointer to message data (recasting to pass a struct!) and size
		0														// Message priority (higher is higher priority)
	);
	if ( send_result < 0 ) {
		perror("Failed to send message");
		exit(2);
	}
	
	cout << "Sleeping before removing queue" << endl;
	sleep(60);
	
	int unlink_result = mq_unlink(queue_name.c_str());
	if ( unlink_result < 0 ) {
		perror(string("Failed to remove the message queue (" + queue_name + "), for some reason").c_str());
	}
	
	return 0;
}







