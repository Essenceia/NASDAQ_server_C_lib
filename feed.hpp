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
	private:
		FILE* fptr;
		hst h;
};
