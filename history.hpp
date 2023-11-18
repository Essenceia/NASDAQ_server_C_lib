#ifndef HISTORY_H
#define HISTORY_H 

/* Copyright (c) 2023, Julia Desmazes. All rights reserved.
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial
 * 4.0 International License.
 *
 * This code is provided "as is" without any express or implied warranties. */

#include <map>
#include <array>
#include <stdint.h>
#include "moldudp64.h"

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
/* session id array: can't use uint8_t[10] as key
 * as there are no compare methodes */
typedef std::array<uint8_t, 10> sid_t;
/* message map */
typedef std::map<uint64_t,moldudp64_msg_s*> mmap_t; 
/* history map */
typedef std::map<sid_t, mmap_t> hmap_t;

class hst {
	public:
		/* Constructor */
		hst();
		~hst();
		/* add an itch message to the history */
		void add_itch_msg(
			const sid_t sid, 
			const uint64_t seq, 
			const moldudp64_msg_s* msg);
		/* get itch message by sid and seq */
		moldudp64_msg_s* get_itch_msg(
			const sid_t sid,
			const uint64_t seq);
		/* delete history by session id */
		void forget_session(const sid_t sid);
	private:
		hmap_t hmap;
};

#endif // HISTORY_H
