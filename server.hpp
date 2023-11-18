#ifndef SERVER_HPP
#define SERVER_HPP
#include "feed.hpp"
extern "C"{
#include "inc/eth.h"
}
/* Server class */
class ser{
	public:
		ser(
			const char* dump_path,
			const uint8_t dst_mac[6],
			const uint8_t src_mac[6],
			const uint32_t src_ip,
			const uint32_t dst_ip,
			const uint16_t src_port,
			const uint16_t dst_port,
			const bool vtag
		);
		~ser();
		/* get next itch data feed packet */
		uint8_t* get_nxt_feed_pkt(const size_t *len, bool dump);
	
	private:
		feed *f;
		eth_packet_s *eth;		
};

#endif // SERVER_HPP
