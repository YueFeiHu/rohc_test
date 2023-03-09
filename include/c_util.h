#ifndef _C_UTIL_H
#define _C_UTIL_H

#include "rohc.h"

// W-LSB: Window based Least Significant Bits encoding

struct sc_window {
	int sn;
	int time;
	int value;
	boolean used;
};

struct sc_wlsb {
 	int windowWidth;
 	struct sc_window *window; // windowWidth number of sc_window..

	int oldest;	// points to the oldest entry in the window
	int next;	// keeps track of the current position in the window

 	int bits;
 	int p;
};


// Create new window..
struct sc_wlsb *c_create_wlsb(int bits, int windowWidth, int p);

// Print window content
void print_wlsb_stats(struct sc_wlsb * s);

// Add value to window with the given sequence number and timestamp
void c_add_wlsb(struct sc_wlsb *, int sn, int time, int value);

// Get minimum number of bits necessary (k) of value needed for 
// decompressor to decode correctly
int c_get_k_wlsb(struct sc_wlsb *, int value);

// Acknowledge (remove older values) from window based on the sequence number
void c_ack_sn_wlsb(struct sc_wlsb *, int sn);

// Acknowledge (remove odler values) from window based on the timestamp
void c_ack_time_wlsb(struct sc_wlsb *, int time);

// Unallocate all memory used in the WLSB structure
void c_destroy_wlsb(struct sc_wlsb *);

// Calculate the sum of the values in window (used for a statistics window)
int c_sum_wlsb(struct sc_wlsb *);

// Calculate the mean-value in window (used for a statistics window)
int c_mean_wlsb(struct sc_wlsb *);

void c_print_wlsb(struct sc_wlsb *);

// SDVL: Self Described Variable Length  encoding

// returns number of bytes needed to represent value
int c_bytesSdvl(int value);

// returns false if value is to big (value>2^29)
boolean c_encodeSdvl(unsigned char *dest, int value);

// returns add-cid value
unsigned char c_add_cid(int cid);

/* Function that sets the cid_values it will set the cids proper in the
pointer dest, the function takes a pointer called first_position where you get the position
to place your first byte, the second byte can be placed in the value that this function returns.
*/
int code_cid_values(struct sc_context *context,unsigned char *dest,int max_size,int *first_position);

// CRC

#define CRC_TYPE_3 1
#define CRC_TYPE_7 2
#define CRC_TYPE_8 3



unsigned int crc_calculate(int type, unsigned char *, int length);
int crc_get_polynom(int type);
void crc_init_table(unsigned char *table, unsigned char polynum);

#endif
