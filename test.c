#include "server.hpp"
#include <cstring>
extern "C"{
#include "inc/defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
}
int main(){
	/* init random number genreator */
	srand(time(NULL));
	uint8_t src_ip_lite[4] = {4,125,74,233};
	uint32_t src_ip;
	memcpy(&src_ip, &src_ip_lite, 4);
	uint16_t src_port = 31004;
	uint16_t dst_port = 31504;
	uint8_t dst_mac[6] = DEFAULT_DST_MAC;
	uint8_t src_mac[6] = DEFAULT_SRC_MAC;
	ser s("/home/pitchu/rtl/hft/tb/12302019.NASDAQ_ITCH50",
		dst_mac,
		src_mac,
		src_ip,
		DEFAULT_DST_IP ,
		src_port,
		dst_port,
		false);
	size_t l;
	for(int i=0; i<50000; i++){
		uint8_t *p = s.get_nxt_feed_pkt(&l, true);
		free(p);
	}
	return 0;
}
