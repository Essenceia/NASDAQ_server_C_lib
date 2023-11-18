#include "history.hpp"
#include <cassert>
#include <cstdlib>
#include <cstring>

/* default constructor */
hst::hst(){
	/* init history ... nothing to do */
}

/* default destructor */
hst::~hst(){
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

void hst::add_itch_msg(
			const sid_t sid, 
			const uint64_t seq, 
			const moldudp64_msg_s* msg
){
	assert(msg);
	moldudp64_msg_s *cpy;
	cpy = (moldudp64_msg_s*)malloc(sizeof(moldudp64_msg_s));
	cpy->data = (uint8_t*) malloc(msg->len);
	cpy->len = msg->len;
	memcpy(cpy->data, msg->data, msg->len);
	this->hmap[sid][seq] = cpy; 
}


moldudp64_msg_s* hst::get_itch_msg(
			const sid_t sid,
			const uint64_t seq
){
	moldudp64_msg_s* ret = NULL;
	hmap_t::iterator i;
	i = this->hmap.find(sid);
	if(i!=this->hmap.find(sid)){
		mmap_t::iterator j;
		j = i->second.find(seq);
		if(j!= i->second.end()){
			ret = j->second;
		}
	}
	return ret;
}

void hst::forget_session(
	const sid_t sid
){
	this->hmap[sid].clear();	
}
	
