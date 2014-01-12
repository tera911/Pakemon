
#include "MapBuilder.h"
#include "PacketICMP.h"
#include <pcap.h>

#define LINE_LEN 16
#define PACKET_FILE "icmpPacket.pcap"

#define MAP_WIDTH (35)
#define MAP_HEIGHT (18)

PacketICMP packet;

int MapBuilder::rand(struct ip_address ip, int mod, int seed = 0){
	int ip1 = (int)ip.byte1 * ip.byte2;
	int ip2 = (int)ip.byte3 * ip.byte4;
	int ret;
	switch(seed){
	case 0:	ret = (ip1 + ip2); break;
	case 1:	ret = (ip1 - ip2); break;
	case 2:	ret = (ip1 * ip2); break;
	case 3:	ret = (ip1 ^ ip2); break;
	case 4:	ret = (ip1 | ip2); break;
	case 5:	ret = (ip1 & ip2); break;
	default:ret = (ip1 + ip2); break;
	}



	ret = ret < 0 ? -ret : ret;//負の数なら正になおす
	return ret % mod;
	//return ((ip.byte1 * ip.byte2) + (ip.byte3 * ip.byte4)) % mod;
	//return (((int)ip.byte1 * ip.byte2) | ((int)ip.byt e3 + ip.byte4)) % mod;
}
int MapBuilder::randblock(struct ip_address ip, int seed = 0){
/*
	0 = 空気
	1 = 足場
	2 = １段目の障害物
	3 = アイテムブロック
	4 = コイン
	5 = SWITCH
	6 = ROUTER
	*/

	static char normal_map[100] =	
	{11,11,11,11,11,11,11,11,11,11,11,11, //足場 49/100
	 12,12,12,12,12,12,12, //
	 13,13,13,13,13,13,13, //
	 14,14,14,14,14,14,14, //
	 15,15,15,15,15,15,15, //
	 16,16,16,16,16,16,16, //
	 17,17,17,17,17,17,17, //足場
     3,3,3,3,		//コイン 24/100 = 6/25
	 4,4,4,4,
	 6,6,6,6,
	 7,7,7,7,
	 9,9,9,9,
	 10,10,10,10,	 //コイン
	 8,8,8,8,8,//はてなブロック 5/100 = 1/20
	 8,8,8,8,8,8,8,8,8,8,//障害物 
	 5,5,5,5,5,//障害物２段目
	 10,10
	};

	
	int i = rand(ip,100, seed);
	return normal_map[i];
}

void MapBuilder::buildMap(ip_header* ih, int size){
	for(int seed = 0; seed < 6; seed++){
		for(int i = 0; i < MAP_WIDTH; i++){
			int x = i + MAP_WIDTH * seed;	//x座標
			for(int k = 0; k < 10; k++){
				char blockpos[18] = {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
				ip_address ip = ih->daddr;	
				int pos = randblock(ip, seed);
				if(map[x][pos] != 0){
					break;
				}
				if(blockpos[pos] == 0){
					map[x][pos] = BLOCK_NONE;
				}else{
					int random = 0;
					switch(pos){
					case 3:
					case 4:
					case 6:
					case 7:
					case 9:
					case 10:
						random = rand(ip,13, seed);	// 0~4コイン  5スイッチ 6ルーター
												//確率的に　コイン５個に対してルーターとスイッチが１個出る
						switch(random % 6){
						case 0:
							map[x][pos] = COIN_FTP;
						break;
						case 1:
							map[x][pos] = COIN_SSH;
						break;
						case 2:
							map[x][pos] = COIN_SMTP;
						break;
						case 3:
							map[x][pos] = COIN_DNS;
						break;
						case 4:
							map[x][pos] = COIN_HTTP;
						break;
						case 5:
							map[x][pos] = COIN_HTTPS;
						break;
						}
					break;
					case 5:
					case 8:
						if(rand(ip,5, seed) == 0){
							map[x][pos] = ITEM;
							int itemtype = rand(ip, 10);
							if(itemtype == 0){
								map[x][pos] = SWITCH_FLAG;
							}else if(itemtype == 1){
								map[x][pos] = SWITCH_FLAG;
							}else if(itemtype == 2){
								map[x][pos] = ROUTER_FLAG;
							}else{
								map[x][pos] = ITEM;
							}
						}else{
							map[x][pos] = SHOGAI;
						}
						break;
					case 11:
					case 12:
					case 13:
					case 14:
					case 15:
					case 16:
					case 17:
						map[x][pos] = ASHIBA;
						break;
					}
				}

				if(i * k -1 > size){
					break;
				}
				ih++;
			}
		}
	}
}
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data){
	ip_header *ih;
	tcp_header *th;
	u_int ip_len;
	u_short sport,dport;
	ih = (ip_header *)(pkt_data + 14);
	
	ip_len = (ih->ver_ihl & 0xf) * 4;
	th = (tcp_header *)((u_char *)ih + ip_len);


	packet.addPacket(ih);//パケットを保存

	/*sport = ntohs( th->sport);
	dport = ntohs( th->dport);

	 printf("%d.%d.%d.%d.%d -> %d.%d.%d.%d.%d\n",
        ih->saddr.byte1,
        ih->saddr.byte2,
        ih->saddr.byte3,
        ih->saddr.byte4,
        sport,
        ih->daddr.byte1,
        ih->daddr.byte2,
        ih->daddr.byte3,
        ih->daddr.byte4,
        dport);*/
}


int MapBuilder::getMap(int distmap[][MAP_HEIGHT]){
	pcap_t * fp;
	char errbuf[PCAP_ERRBUF_SIZE];

	if((fp = pcap_open_offline(PACKET_FILE, errbuf)) == NULL){
		return 0;
	}

	pcap_loop(fp, 0, packet_handler, NULL);
	
	
	buildMap(packet.getPacket(), 1000);

	for(int y = 0; y < MAP_HEIGHT; y++){
		for(int x = 0; x < MAP_WIDTH * 6 + 10; x++){
			distmap[x][y] = map[x][y];
		}
	}

	return 1;
}
