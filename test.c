#include "history.hpp"
#include "feed.hpp"

int main(){
	hst h;
	feed f("/home/pitchu/rtl/hft/tb/12302019.NASDAQ_ITCH50");
	moldudp64_s *m = f.get_next_packet(10);
	moldudp64_print(m);
	return 0;
}
