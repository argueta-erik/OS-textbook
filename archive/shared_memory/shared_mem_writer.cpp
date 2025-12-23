/**
 * This program illustrates the basics of shared memory,
 * 	using the newer POSIX API calls
 * This program allocates a piece of memory, and writes
 * the string that user entered at the command line into
 * the memory location.
 */


#include <sys/mman.h>		// shm_open / etc
#include <unistd.h>			// ftruncate
#include <sys/stat.h>		// Mode constants
#include <fcntl.h>			// O_* constants
#include <cstring>

#include <iostream>
#include <string>


using std::cin, std::cout, std::cerr, std::endl;
using std::string;


int main(int argc, char** argv)
{
	const char * SHARE_KEY = "/MySuperCoolDemoBro";		// Arbitrary
	const size_t SHARE_SIZE = 1024;						// In bytes
	const size_t SHARE_MODE = 0600;						// Linux perms; octal
	
	// Check the command line parameters
	if ( argc < 2 ) {
		cerr << "Usage: " << argv[0] << "<string to write>" << endl;
		exit(-1);
	}
	
	/* Since we will be allocating only MEMORY_SIZE bytes of 
 	 * shared memory, our string cannot exceed that size
 	 */
	if ( strlen( argv[1] ) > SHARE_SIZE ) {
		cerr << "Your string is too big (should be <= " << SHARE_SIZE << " characters)" << endl;
		exit(-1);
	}
	
	/* Allocate a segment with key SHARE_KEY, of size MEMORY_SIZE bytes.
	 * Make it readable, writable, and executable.
 	 */
	int segment_id = shm_open(
		SHARE_KEY,
		O_CREAT | O_RDWR | O_TRUNC | O_EXCL,
		SHARE_MODE
	);
	
	// Failed to allocate shared memory
	if ( segment_id < 0 ) {
		perror("shm_open has failed: ");
		exit(-1);
	}
	perror("zOMG Yey! ===> ");
	
	// Set shared memory size
	int truncate_result = ftruncate(segment_id, SHARE_SIZE);
	if ( truncate_result < 0 ) {
		perror("ftruncate has failed: ");
		exit(-1);
	}
	
	// Get a pointer to the shared memory
	char* shared_memory = static_cast<char*> (
		mmap(
			NULL,			// Let OS specify where to allocate in system RAM
			SHARE_SIZE,		// Size of share
			PROT_WRITE,		// Desired memory protection (usually PROT_READ or PROT_WRITE)
			MAP_SHARED,		// Flags
			segment_id,		// Shared memory segment ID (handle)
			0				// Offset the pointer against the actual shared memory by this amount
		)
	);
	
	// Error checks
	//if(((void*)shared_memory) < 0) {
	if ( shared_memory < static_cast<void*> (0) ) {
		perror("mmap has failed: ");
		exit(-1);
	}
	
	// Write a string to the shared memory
	snprintf(shared_memory, strlen(argv[1])+1, "%s", argv[1]);
	cout << "Specified string has been written to shared memory!" << endl;
	cout << "Note: You should be able to find and 'cat' the segment in /dev/shm without even using the reader!" << endl;
	
	// Wait for the user to enter anything, before deallocating the shared memory segment
	cout << "Type anything and hit enter to continue > ";
	string dummy;
	cin >> dummy;
	shm_unlink(SHARE_KEY);
	
	return 0;
}
