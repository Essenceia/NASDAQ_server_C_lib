/* Copyright (c) 2023, Julia Desmazes. All rights reserved.
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial
 * 4.0 International License.
 *
 * This code is provided "as is" without any express or implied warranties. */

#include "server.hpp"
#include <cassert>
extern "C"{
#include "inc/dump.h"
}
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
	size_t *len, 
	bool dump
){
	uint16_t msg_cnt =  (uint16_t)rand() % 15 + 1;
	/* generate a new mold packet with 10 message */
	this->f->gen_nxt_pkt(msg_cnt);
	size_t l;
	uint8_t *app = this->f->get_nxt_pkt(&l);
	assert(app);

	/* add mold to udp packet and package into
 	 * a mac packet */
	update_eth_packet_data(this->eth, app, l);
	#ifdef DEBUG
	print_eth_packet(this->eth);
	#endif

	/* flatten packet */
	uint8_t *flat; 
	flat = write_eth_packet(this->eth, len);
	assert(flat);

	/* dump to wireshark compatible format */
	if (dump){
		dump_eth_packet(flat, *len, false);	
	}

	return flat;
}

