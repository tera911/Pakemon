#ifndef DANMAKU_MAP
#define DANMAKU_MAP
#include "packet.h"

class Map{
private:
	int rand(struct ip_address, int mod);
	int randblock(struct ip_address);
	enum BLOCK {AIR,ASHIBA = 'A' ,SHOGAI = 'S',ITEM = 'I',COIN = 'C' ,SWITCH = 'W',ROUTER = 'R'};	
public:
	char map[46][18];
	Map(){
		for(int i = 0; i < 46; i++){
			for(int k = 0; k < 18; k++){
				map[i][k] = 0;
			}
		}
	}
	void buildMap(ip_header* ih, int size);
//	char** getMap();
	void showMap();
};

#endif