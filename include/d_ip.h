#ifndef _D_IP_H
#define _D_IP_H

#include "rohc.h"
#include "decomp.h"
#include "d_util.h"

struct s_iponly_change
{
	int rnd;
	int nbo;
	struct iphdr ip;
};

struct s_iponly_profile_data
{
	struct s_iponly_change * last1;
	struct s_iponly_change * last2;
	struct s_iponly_change * active1;
	struct s_iponly_change * active2;

	struct sd_lsb_decode sn;
	struct sd_ip_id_decode ip_id1;
	struct sd_ip_id_decode ip_id2;

	// multiple ip-header if multiple_ip=1
	int multiple_ip;
//	struct type_timestamp	sn;
//	struct type_ipid	ipid;
	int package_type;

	int counter;
	int last_packet_time; //the time of the last crc-approved packet
	int current_packet_time; //the time of the current packet without crc-test yet
	int inter_arrival_time; //a average inter-packet time of the last few packets,
};

struct s_profile * iponly_profile_create(void);

#endif
