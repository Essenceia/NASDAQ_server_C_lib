#ifndef FEED_HPP
#define FEED_HPP

#include "history.hpp"

/* Data feed class
 * Reads the content of the nasdaq dump file, 
 * get's a number of itch messages and creates the
 * next mold packet. 
 * Adds the itch messages in the next packet to the
 * history.
 */
class feed{
	public:
		feed(const char* path);	
		~feed();
		/* generate the next moldudp64 packet containing
 		 * `cnt` itch messages */ 
		void gen_nxt_pkt(
			uint16_t cnt);	
		/* get flattened packet */
		uint8_t *get_nxt_pkt(
			size_t *len);
	private:
		FILE* fptr;
		hst h;
		moldudp64_s *pkt;
};

#endif // FEED_HPP
