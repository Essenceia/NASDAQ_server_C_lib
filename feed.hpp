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
		/* get next moldudp64 packet containing
 		 * `cnt` itch messages */ 
		moldudp64_s* get_next_packet(
			uint16_t cnt);	
	private:
		FILE* fptr;
		hst h;
		moldudp64_s *pkt;
};
