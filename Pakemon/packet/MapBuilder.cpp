
#include "MapBuilder.h"
#include "PacketICMP.h"
#include <pcap.h>

#define LINE_LEN 16
#define PACKET_FILE "10m.pcap"

#define MAP_WIDTH (35)
#define MAP_HEIGHT (18)

PacketICMP packet;
MapBuilder::MapBuilder(){
	ZeroMemory(map, (MAP_WIDTH * 6 + 10) * MAP_HEIGHT * sizeof(int));
}
int MapBuilder::rand(struct ip_address ip, int mod, int seed = 0){
	int ip1 = (int)ip.byte1 * ip.byte2;
	int ip2 = (int)ip.byte3 * ip.byte4;
	int ret;
	switch(seed){
	case 0:	ret = (ip1 + ip2); break;
	case 1:	ret = (ip1 - ip2); break;
	case 2:	ret = (ip1 * ip2); break;
	case 3:	ret = (ip1 * ip2); break;
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
	{11,11,11,11,11,11,11,11,11,11,11,11,11,11,11, //15  //足場 42 + 15 = 57/100
	 12,12,12,12,12,12,12, //7
	 13,13,13,13,13,13,13, //7
	 14,14,14,14,14,14,14, //7
	 15,15,15,15,15,15,15, //7
	 16,16,16,16,16,16,16, //7
	 17,17,17,17,17,17,17, //7 //足場
	 4,4,4,4,		//コイン 20/100
	 6,6,6,6,
	 7,7,7,7,
	 9,9,9,9,
	 10,10,10,10,	 //コイン
	 8,8,8,8,8,//はてなブロック or 障害物 23/100
	 8,8,8,8,8,8,8,8,8,8,//障害物 
	 5,5,5,5,5,//障害物２段目
	 10,10,
	 0			//FW
	};

	
	int i = rand(ip,100, seed);
	return normal_map[i];
}

void MapBuilder::buildMap(ip_header* ih, int size){
	for(int seed = 0; seed < 6; seed++){
		bool fw = false;
		for(int i = 0; i < MAP_WIDTH; i++){
			int x = i + MAP_WIDTH * seed;	//x座標
			for(int k = 0; k < 10; k++){
				char blockpos[18] = {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
				ip_address ip = ih->daddr;	//送信先ＩＰアドレスを使用
				int pos = randblock(ip, seed);
				if(map[x][pos] != 0){
					break;
				}

				if(blockpos[pos] == 0){
					if(!fw && x > 30){	//FWがまだ生成されていない かつ　x座標が30以上なら
						/*  FW作成 
						FWが生成できるか近くにあるパケットファイルを検索する
						FW生成予定位置から6 x MAP_HEIGHTの間に
						コインがあった場合のみFWを生成する。
						コインはFWから遠い位置から検索される。見つかったらその時点で検索を終了しFWを生成する
キャーｯ　ふぁいあーうぉーるきちゃうっ＞＜ */
						bool fw_create = false;
						int	 acceptBlock;
						for(int y =  0; y < MAP_HEIGHT; y++){		
							for(int fx = x - 6; fx < x - 2; fx++){	
								if(map[fx][y] & COIN_ALL){
									acceptBlock = map[fx][y];
									fw_create = true;
									break;
								}
							}
							if(fw_create) break;
						}
						if(fw_create){
							for(int y = 0; y < MAP_HEIGHT; y++){
								for(int fx = x -2; fx < x; fx++){
									map[fx][y] = ASHIBA | acceptBlock | BLOCK_FW;
								}
							}
							fw = true;
						}
					}else{
						map[x][pos] = 0;
					}
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

int MapBuilder::getMap(int distmap[][MAP_HEIGHT], const char filter[]){
	pcap_t * handle;
	struct pcap_pkthdr *header;
	const u_char *pkt_data;
	char errbuf[PCAP_ERRBUF_SIZE];
	struct ip_header ip_headers[MAP_WIDTH * MAP_HEIGHT * 6 + 100];
	static int packetCount = 0;

	//フィルター処理
	bpf_program fp;
	char filter_exp[] = "icmp";

	if((handle = pcap_open_offline(PACKET_FILE, errbuf)) == NULL){
		return 0;
	}
	pcap_compile(handle, &fp, filter, 0, 0);
	pcap_setfilter(handle, &fp);
	
	//パケット進める
	int count = 0;
	while(count < packetCount){
		if(pcap_next_ex(handle, &header, &pkt_data) < 0){
			packetCount = 0;
			break;
		}
		count++;
	}

	struct ip_header *ip = ip_headers;
	//pcap_loop(fp, 0, packet_handler, NULL);
	for(int i = 0; i < MAP_WIDTH * MAP_HEIGHT * 6;i++){
		if(pcap_next_ex(handle, &header, &pkt_data)  > 0){
		//	(ip_header *)(pkt_data + 14);
			//memcpy((void*)(ip + i) ,(void*)(pkt_data+ 14), sizeof(ip_header));
			memcpy((void*)ip++, (void*)((ip_header*)(pkt_data + 14)), sizeof(ip_header));
			packetCount++;
		}else{
			break;
		}
	}

	buildMap(ip_headers, MAP_WIDTH * MAP_HEIGHT * 6);

	for(int y = 0; y < MAP_HEIGHT; y++){
		for(int x = 0; x < MAP_WIDTH * 6 + 10; x++){
			distmap[x][y] = map[x][y];
		}
	}
	pcap_close(handle);	//オープンしたパケットをクローズする
	return 1;
}

MapBuilder::~MapBuilder(){
}
