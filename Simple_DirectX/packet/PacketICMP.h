#include "packet.h"

class PacketICMP{
private:
	ip_header icmp[1000];
public:
	int addPacket(ip_header * packet){
		static int i = 0;
		if(i < 100){
			memcpy(&icmp[i],packet,sizeof(ip_header));
			i++;
			return 0;
		}else{
			return -1;
		}
	}
	ip_header getPacket(int i){
		return icmp[i];
	}
}