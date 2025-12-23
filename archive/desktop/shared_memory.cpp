#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/mman.h>

#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */


/*
 * Exit Codes:
|0|Success|
|1|General failure, of some sort|
|2|No mode (send/receive) was specified|
|3|Bad mode; A mode other than send/receive was specified|
|4|No message; The user failed to provide a message in send mode|
|5|Message too long; The user provided a message that exceeded the
	 shared memory size|
|6|The sender was unable to create a shared memory segment|
|7|The receiver was unable to open the shared memory segment|
 */


/**
 * memory segment: `/HeyProfessorPThisIsCool`
 * EXCLUSIVE mode, permissionsse to `0600`
 * Shared memory segment should be 1024 bytes long
 * Sending mode max strings is `1023`

 * sender sleep 5 seconds and must exit

*/

void checklist(int numArgs);
int shareCommand(char** arg);

//void openMem(char* PATH, const size_t SHARE_M);
// shm_open(const char* name, int oflag, mode_t);


int main(int argc, char** argv)
{
	// CONST
	const size_t SHARE_MODE = 0600;
	const char* SHARE_PATH = "/HeyProfessorPThisIsCool";
	const size_t BUF_SIZE = 1024;
	const size_t SEND_SIZE = 1023;

	int commandReceived;
	checklist(argc);
	commandReceived = shareCommand(argv);

	if (commandReceived == 1) {} //function to send
	else if(commandReceived == 2) {} //function to receive
	else { fprintf(stderr, "General failure, of some sort"); exit(1); }

	return 0;
}

void checklist(int numArgs) {
	// Checks if an argument for send/receive was written
	if (numArgs < 2) {
		fprintf(stderr, "No mode (send/receive) was specified");
		//std::cerr << "Usage: " << argArray[0] << "<string to write>" << std::endl;
		exit(1);
	}
}

int shareCommand(char** arg) {
	std::string command = static_cast<std::string>(arg[1]);
	if (command == "send") { return 1; }
	if (command == "receive") { return 2; }
	else {
		fprintf(stderr, "Bad mode; A mode other than send/receive was specified.");
		exit(3);
	}
}



/*
void openMem(char* PATH, const size_t SHARE_M) {
	int oMem = shm_open(path, O_CREAT | O_EXCL | O_RDWR, SHARE_M);
	if (oMem == -1) { perror("Failed to shm_openn"); exit(6); }
	else { std::cout << "shm_open success!" << std::endl; }
}
*/
