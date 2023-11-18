#include "server.hpp"

ser::ser(
	const char* dump_path,
	const uint8_t dst_mac[6],
	const uint8_t src_mac[6],
	const uint32_t src_ip,
	const uint32_t dst_ip,
	const uint16_t src_port,
	const uint16_t dst_port,
	const bool vtag
){
	/* open feed */
	this->f = new feed(dump_path);
	/* create packet */
	this->eth = init_eth_packet(
		dst_mac,
		src_mac,
		src_ip,
		dst_ip,
		src_port,
		dst_port,
		vtag);	
}

ser::~ser(){
	free_eth_packet(this->eth);
	delete(this->f);
};

uint8_t* ser::get_nxt_feed_pkt(
	const size_t *len, 
	bool dump
){
	/* generate a new mold packet with 10 message */
	this->f->gen_nxt_pkt(10);
	size_t l;
	uint8_t *app = this->f->get_nxt_pkt(&l);
	
}

