#include "server.hpp"
extern "C"{
#include "inc/defs.h"
}
int main(){
	uint8_t dst_mac[6] = DEFAULT_DST_MAC;
	uint8_t src_mac[6] = DEFAULT_SRC_MAC;
	ser s("/home/pitchu/rtl/hft/tb/12302019.NASDAQ_ITCH50",
		dst_mac,
		src_mac,
		//(uint8_t*)DEFAULT_SRC_MAC,
		DEFAULT_SRC_IP ,
		DEFAULT_DST_IP ,
		DEFAULT_SRC_PORT,
		DEFAULT_DST_PORT,
		false);
	size_t l;
	uint8_t *p = s.get_nxt_feed_pkt(&l, true);
	return 0;
}
