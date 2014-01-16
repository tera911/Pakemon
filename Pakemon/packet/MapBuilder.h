#ifndef DANMAKU_MAP
#define DANMAKU_MAP
#include "packet.h"

#define MAP_WIDTH (35)
#define MAP_HEIGHT (18)

class PacketICMP;

class MapBuilder{
private:
	int rand(struct ip_address, int mod, int seed);
	int randblock(struct ip_address, int seed);	
public:
	int map[MAP_WIDTH * 6 + 10][MAP_HEIGHT];
	enum BLOCK {AIR = 0 ,ASHIBA = 0x2 ,SHOGAI = 0x4 ,ITEM = 0x8, ITEM_NORMAL = 0x10 ,SWITCH = 0x20, ROUTER = 0x40 , 
				COIN_FTP = 0x80, COIN_SSH = 0x100, COIN_SMTP = 0x200, COIN_DNS = 0x400, COIN_HTTP = 0x800, COIN_HTTPS = 0x1000, COIN_ALL = 0x1F80, 
				ROUTER_FLAG = 0x2008, SWITCH_FLAG = 0x4008,BLOCK_FW = 0x8000, ALL_HIT_BLOCK = 0x1E};
	MapBuilder();
	void buildMap(ip_header* ih, int size);
	int getMap(int distmap[][MAP_HEIGHT], const char filter[]);
	void showMap();
	~MapBuilder();
};

#endif