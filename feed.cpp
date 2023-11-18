#include "feed.hpp"
#include <iostream>
#include <stdio.h>
#include <cassert>

extern "C"{
#include "inc/file.h"
}

feed::feed(const char* path){
	assert(path);
	/* init mold packet */
	this->pkt = moldudp64_alloc();
 
	/* open file */
	this->fptr = fopen(path,"r");
	if (!this->fptr)
		std::cerr <<  "ERROR: Unable to open file "<<path << std::endl; 
	assert(this->fptr);
}

feed::~feed(){
	fclose(this->fptr);
}

moldudp64_s* feed::get_next_packet(
			uint16_t cnt
){
	/* clear packet */
	moldudp64_clear(this->pkt);

	for(uint16_t i=0; i<cnt; i++){
		/* read mold messages */
		/* Read an itch message. */
		uint8_t buff[ITCH_MSG_MAX_LEN + 1];		
		size_t msg_len = get_next_bin_msg(this->fptr, buff, ITCH_MSG_MAX_LEN);
		if (msg_len ==  0) {
			std::cerr << "No new message to read" << std::endl;
			break;
		}
		assert(msg_len <= ITCH_MSG_MAX_LEN);
		
		/* Copy the read message at the end of the mold struct. */
		moldudp64_add_msg(pkt, buff, msg_len);
	}
	return this->pkt;
}

