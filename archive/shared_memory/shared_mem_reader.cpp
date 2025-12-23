/**
 * This program illustrates the basics of shared memory,
 * 	using the newer POSIX API calls
 * This program allocates a piece of memory, and writes
 * the string that user entered at the command line into
 * the memory location.
 */


#include <sys/mman.h>		// shm_open / etc
//#include <unistd.h>			// ftruncate
//#include <sys/stat.h>		// Mode constants
#include <fcntl.h>			// O_* constants
//#include <cstring>

#include <iostream>


using std::cout, std::cerr, std::endl;


int main(int argc, char** argv)
{
	const char * SHARE_KEY = "/MySuperCoolDemoBro";		// Arbitrary
	const size_t SHARE_SIZE = 1024;						// In bytes
	const size_t SHARE_MODE = 0600;						// Linux perms; octal
	
	/*
	 * Grab the segment identified by SHARE_KEY, of size MEMORY_SIZE bytes
 	 */
	int segment_id = shm_open(
		SHARE_KEY,
		O_RDWR,
		SHARE_MODE
	);
	
	// Failed to allocate shared memory
	if ( segment_id < 0 ) {
		perror("shm_open has failed: ");
		exit(-1);
	}
	
	/* Get a pointer to the shared memory  */ 
	char* shared_memory = static_cast<char*> (
		mmap(
			NULL,			// Let OS specify where to allocate in system RAM
			SHARE_SIZE,		// Size of share
			PROT_READ,		// Desired memory protection (usually PROT_READ or PROT_WRITE)
			MAP_SHARED,		// Flags
			segment_id,		// Shared memory segment ID (handle)
			0				// Offset the pointer against the actual shared memory by this amount
		)
	);
	
	/*  Error checks */
	//if(((void*)shared_memory) < 0) {
	if ( shared_memory < static_cast<void*> (0) ) {
		perror("mmap has failed: ");
		exit(-1);
	}
	
	/* Read the string from shared memory */
	//snprintf(shared_memory, strlen(argv[1])+1, "%s", argv[1]);
	cout << "Received the following string: " << endl << "> ";
	cout << shared_memory << endl;
	
	return 0;
}
