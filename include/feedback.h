#ifndef __FEEDBACK_H__
#define __FEEDBACK_H__
#define OPT_TYPE_CRC		1
#define OPT_TYPE_REJECT		2
#define OPT_TYPE_SN_NOT_VALID	3
#define OPT_TYPE_SN		4
#define OPT_TYPE_CLOCK		5	// not used
#define OPT_TYPE_JITTER		6	// not used
#define OPT_TYPE_LOSS		7
#define ACKTYPE_ACK		0
#define ACKTYPE_NACK		1
#define ACKTYPE_STATIC_NACK	2
#define NO_CRC			0
#define WITH_CRC		1
#define	false			0
#define	true			1
typedef int bool;
struct sd_feedback
{
	int feedback_type;
	char feedback[30];
	int size;
};
// PUBLIC:
//int f_feedback(int acktype, int mode, int sn, struct sd_feedback * f);
bool f_feedback1(int sn, struct sd_feedback * f);
void f_feedback2(int acktype, int mode, int sn, struct sd_feedback * f);
bool f_add_option(struct sd_feedback * feedback, int opt_type, char * data);
char * f_wrap_feedback(struct sd_feedback * f, int cid, int largecidUsed, int with_crc, int * final_size);
// PRIVATE:
bool f_append_cid(struct sd_feedback * f, int cid, int largecidUsed);
#endif
