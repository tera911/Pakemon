#ifndef DANMAKU_MAP
#define DANMAKU_MAP
#include "packet.h"
#include <pcap.h>
#include "PacketICMP.h"



class MapBuilder{
private:
	int rand(struct ip_address, int mod);
	int randblock(struct ip_address);	
public:
	int map[46][18];
	enum BLOCK {AIR = 0 ,ASHIBA = 0x2 ,SHOGAI = 0x4 ,ITEM = 0x8, ITEM_NORMAL = 0x10 ,SWITCH = 0x20, ROUTER = 0x40 , COIN = 0x80};	
	MapBuilder(){
		for(int i = 0; i < 46; i++){
			for(int k = 0; k < 18; k++){
				map[i][k] = 0;
			}
		}
	}
	void buildMap(ip_header* ih, int size);
	int getMap(int map[46][18]);
	void showMap();
};

#endif