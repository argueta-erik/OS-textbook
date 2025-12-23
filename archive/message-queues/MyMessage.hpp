#ifndef DEMO_MESSAGE_QUEUES_PERALTA_MYMESSAGE_H
#define DEMO_MESSAGE_QUEUES_PERALTA_MYMESSAGE_H


// Using `__attribute__((__packed__))` causes structs to be packed rather than padded,
// which ensures they are compatible with our message queue

// Note that surrounding the struct with a push/pop might be needed instead, in pure C
// Example:
// #pragma pack(push, 1)	// Set packing to 1 byte (no padding)
// #pragma pack(pop)		// Restore default packing alignment


struct __attribute__((__packed__)) MyMessage
{
	int a;
	double b;
	
	char c[1024];
};

#endif
