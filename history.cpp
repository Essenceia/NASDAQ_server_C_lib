#include "history.hpp"
#include <cassert>
#include <cstdlib>

/* default constructor */
History::History(){
	/* init history ... nothing to do */
}

/* default destructor */
History::~History(){
	/* free memory allocated by maps
 	 * iterate over the map and free memory
 	 * used for itch messages */
	for(auto i = hmap.begin(); i != hmap.end(); i++){
		mmap_t inner = i->second;
		for(auto j = inner.begin(); j!= inner.end(); j++){
			assert(j->second);
			free(j->second);	
		}		
	} 
}
