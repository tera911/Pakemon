#define WIN32
#define WPCAP
#define HAVE_REMOTE

#pragma comment(lib, "Packet.lib")
#pragma comment(lib, "wpcap.lib")
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <pcap.h>
#include <WinSock2.h>
#include "packet/PacketICMP.h"
#include "packet/Map.h"
#include "loadPacket.h"

#define LINE_LEN 16
#define PACKET_FILE "icmpPacket.pcap"

using namespace std;

class PacketCapcure{
private:
	struct ip_header icmpPacket[1020];
public:
	int addPacket(ip_header * packet){
		static int i = 0;
		if(i < 1000){
			memcpy(&icmpPacket[i],packet,sizeof(ip_header));
			i++;
			return 0;
		}else{
			return -1;
		}
	}
	ip_header* getPacket(){
		return icmpPacket;
	}
};

void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
int convertEndian(void *input, size_t s);

PacketCapcure packet;

int mai1n(int argc, char **argv) {
    
    pcap_t *fp;
    char errbuf[PCAP_ERRBUF_SIZE];


   /* if(argc != 2){

        printf("usage: %s filename", PACKET_FILE);
        return -1;

    }*/
    
    /* Open a capture file */
    if ( (fp = pcap_open_offline(PACKET_FILE, errbuf) ) == NULL)
    {
        fprintf(stderr,"\nError opening dump file\n");
        return -1;
    }
    
    // read and dispatch packets until EOF is reached
    pcap_loop(fp, 0, packet_handler, NULL);

	Map map;
	map.buildMap(packet.getPacket(), 1000);
	map.showMap();
    return 0;
}

/*int getMap(char map[46][18]){
	pcap_t * fp;
	char errbuf[PCAP_ERRBUF_SIZE];
	if((fp = pcap_open_offline(PACKET_FILE, errbuf)) = NULL){
		return 0;
	}

	pcap_loop(fp, 0, packet_handler, NULL);
	
	Map packetMap;
	packetMap.buildMap(packet.getPacket(), 1000);

	for(int y = 0; y < 18; y++){
		for(int x = 0; x < 46; x++){
			map[x][y] = packetMap.map[x][y];
		}
	}
	//map = (char**)malloc(46*18);
//	memcpy(map, packetMap.map, 46*18);

	return 1;
}

*/
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
/*
int convertEndian(void *input, size_t s){
    // エンディアン変換をおこなう関数
    // stdlib.hをインクルードしてください。
    // 【引数】: void *input...エンディアン変換対象へのポインタ
    // 【引数】: size_t    s...変換対象のバイト数

    int i;   // カウンタ
    char *temp;   // 変換時に用いる一時的配列

    if((temp = (char *)calloc( s, sizeof(char))) == NULL){
        return 0;   // 領域確保できず（失敗）
    }

    for(i=0; i<s; i++){   // inputデータをtempに一時保管
        temp[i] = ((char *)input)[i];
    }

    for(i=1; i<=s; i++){   // tempデータを逆方向にしてinputへ代入
        ((char *)input)[i-1] = temp[s-i];
    }

    free(temp);   // 確保した領域を解放

    return 1;   // 正常終了
}
*/