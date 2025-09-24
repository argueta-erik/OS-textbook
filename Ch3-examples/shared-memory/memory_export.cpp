#include <sys/mman.h>		// shm_open/etc
#include <unistd.h>		// ftruncate
#include <sys/stat.h>		// Mode constants
#include <fcntl.h>		// O_* constants
#include <cstring>

#include <iostream>

using std::cout, std::cerr, std::endl;

int main(int argc, char** argv) {
	const char * SHARE_KEY = "/MySuperCoolDemoBro";		// Arbitrary
	const size_t SHARE_SIZE = 1024;				// in bytes
	const size_t SHARE_MODE = 0600;				// Linux perms; octal

	/*
	 * Grab the segment identified by SHARE_KEY, of size MEMORY_SIZE bytes
	*/
	int segment_id = shm_open(
		SHARE_KEY,
		O_RDWR,
		SHARE_MODE
}
