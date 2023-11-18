
#include <map>
#include <stdint.h>

/* Order history class
 * Contains all the itch messages sent from the server
 * to the exchange.
 * Messages are stored in raw bin fomat and not in the
 * itch decoded structure to save on space and because
 * a minority of them will ever be re-read.
 * History is stored in a collection of maps. 
 * There is a map per mold session, and each item
 * in the map is accessed using the messages sequence number 
 * as the key.
 */
/* message map */
typedef std::map<uint64_t,uint8_t*> mmap_t; 
/* history map */
typedef std::map<uint8_t[10],mmap_t> hmap_t;

class History {
	public:
		/* Constructor */
		History();
		~History();
		/* add an itch message to the history */
		void add_itch_msg(
			const uint8_t sid[10], 
			const uint64_t seq, 
			const uint8_t* msg);
		/* delete history by session id */
		void forget_session(const uint8_t sid[10]);
	private:
		hmap_t hmap;
};
