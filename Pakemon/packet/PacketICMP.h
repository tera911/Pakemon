#ifndef __PACKET_ICMP_
#define __PACKET_ICMP_
#include "packet.h"

class PacketICMP{
private:
	struct ip_header icmp[1020];
public:
	int addPacket(ip_header * packet){
		static int i = 0;
		if(i < 1000){
			memcpy(&icmp[i],packet,sizeof(ip_header));
			i++;
			return 0;
		}else{
			return -1;
		}
	}
	ip_header* getPacket(){
		return &icmp[300];
	};
};
#endif