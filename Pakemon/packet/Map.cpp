#include <iostream>
#include <iomanip>
#include "packet.h"
#include "Map.h"
using namespace std;

int Map::rand(struct ip_address ip, int mod){
	//return ((ip.byte1 * ip.byte2) + (ip.byte3 * ip.byte4)) % mod;
	return ((ip.byte1 * ip.byte2) | (ip.byte3 + ip.byte4)) % mod;
}
int Map::randblock(struct ip_address ip){
/*
	0 = ��C
	1 = ����
	2 = �P�i�ڂ̏�Q��
	3 = �A�C�e���u���b�N
	4 = �R�C��
	5 = SWITCH
	6 = ROUTER
	*/

	char normal_map[100] =	
	{11,11,11,11,11,11,11,11,11,11,11,11, //���� 49/100
	 12,12,12,12,12,12,12, //
	 13,13,13,13,13,13,13, //
	 14,14,14,14,14,14,14, //
	 15,15,15,15,15,15,15, //
	 16,16,16,16,16,16,16, //
	 17,17,17,17,17,17,17, //����
     3,3,3,3,		//�R�C��
	 4,4,4,4,
	 6,6,6,6,
	 7,7,7,7,
	 9,9,9,9,
	 10,10,10,10,	 //�R�C��
	 8,8,8,8,8,//�͂Ăȃu���b�N
	 8,8,8,8,8,8,8,8,8,8,//��Q��
	 5,5,5,5,5,//��Q���Q�i��
	 10,10
	};

	

	return normal_map[rand(ip,100)];
}

void Map::buildMap(ip_header* ih, int size){
	for(int i = 0;i < 46; i++){
		for(int k = 0; k < 10; k++){
			char blockpos[18] = {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
			ip_address ip = ih->daddr;	
			int pos = randblock(ip);
			if(map[i][pos] != 0){
				break;
			}
			if(blockpos[pos] == 0){
				map[i][pos] = 0;
			}else{
				int random = 0;
				switch(pos){
				case 3:
				case 4:
				case 6:
				case 7:
				case 9:
				case 10:
					random = rand(ip,15);	// 0~4�R�C��  5�X�C�b�` 6���[�^�[
											//�m���I�Ɂ@�R�C���T�ɑ΂��ă��[�^�[�ƃX�C�b�`���P�o��
					if(random < 13){
						map[i][pos] = COIN;
					}else{
						if((random % 2) == 0){
							map[i][pos] = SWITCH;
						}else{
							map[i][pos] = ROUTER;
						}
					}
					break;
				case 5:
				case 8:
					if(rand(ip,5) == 0){
						map[i][pos] = ITEM;
					}else{
						map[i][pos] = SHOGAI;
					}
					break;
				case 11:
				case 12:
				case 13:
				case 14:
				case 15:
				case 16:
				case 17:
					map[i][pos] = ASHIBA;
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
void Map::showMap(){
	for(int y = 0; y < 18; y++){
		for(int x = 0; x < 46; x++){
			cout << setw(1) << map[x][y];
		}
		cout << "|"<< endl;
	}
}