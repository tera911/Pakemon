#include "packet/MapBuilder.h"
#include "GameMap.h"
#include "Nyancat.h"
#include <math.h>
#include <DxLib.h>
#include "PrintPicture.h"

#include <list>

using namespace std;
#define __DEBUG__	//�f�o�b�O���̂�
#define GRAVITY (12) //�d�ʋ�

struct Point{
	int x0;	//����
	int y0;
	int x1;	//�E��
	int y1;
	int x2;	//�E��
	int y2;
	int x3;	//����
	int y3;
};
GameMap::GameMap(){
		segment = -1;
		screen_x = 1;
		move_screen = 0;
		screen_center_x = 12.0f * 32;
		block_brick		= LoadGraph("./block/brick.png", true);
		block_hatena	= LoadGraph("./block/hatena.png", true);
		block_normal	= LoadGraph("./block/normal.png", true);
		block_packet	= LoadGraph("./block/packet.png", true);
		block_ware		= LoadGraph("./block/ware.png", true);
		block_router	= LoadGraph("./block/router.png", true);
		block_switch	= LoadGraph("./block/switch.png", true);
		block_fire32	= LoadGraph("./block/fire_32.png", true);
		block_fire64	= LoadGraph("./block/fire_64.png", true);
		MapBuilder builder;
		builder.getMap(map);
	}
void GameMap::render(){
	int size = (int)floor(screen_x);
	for(int x = size; x < SCREEN_WIDTH + size +1; x++){
		for(int y = 0; y < MAP_HEIGHT; y++){
			if(map[x][y] & COIN_ALL && map[x][y] & ASHIBA){
				render_fw(map[x][y], x, y);
				break;
			}else{
				render_block(map[x][y], x, y);
			}
		}
	}
//	Animation();
	//screenScroll_x(0.015f);
	segment = (int)screen_x / MAP_WIDTH;
	PrintPicture *pp = PrintPicture::instance();
	pp->NumDraw(172,31,25,1);
	pp->StringDraw(".",39,27,1); 
	pp->NumDraw(16,50, 25,1);
	pp->StringDraw(".",60,27,1); 
	pp->NumDraw(0 ,66, 25,1);
	pp->StringDraw(".",76,27,1);
	int didit=Digit(32*segment);
	switch (didit)
		{
		case 1:
			pp->NumDraw( 32 * segment,83, 25,1);
			pp->StringDraw("/" ,94, 25,1);
			pp->NumDraw(28,109,25,1);
			break;
		case 2:
			pp->NumDraw( 32 * segment,90, 25,1);
			pp->StringDraw("/" ,101, 25,1);
			pp->NumDraw(28,116,25,1);
			break;
		case 3:	
			pp->NumDraw( 32 * segment,97, 25,1);
			pp->StringDraw("/" ,108, 25,1);
			pp->NumDraw(28,123,25,1);
			break;
	}
	/*pp->NumDraw(172,30,25,2);
	pp->StringDraw(".",47,27,2); 
	pp->NumDraw(16,68, 25,2);
	pp->StringDraw(".",84,27,2);
	pp->NumDraw(0 ,95, 25,2);
	pp->StringDraw(".",110,27,2);
	pp->NumDraw( 32 * segment,118, 25,2);
	pp->StringDraw("/" ,130, 25,2);
	pp->NumDraw(28,163,25,2);*/
	
}
void GameMap::render_fw(int block_type, int x, int y){
	BLOCK block = static_cast<BLOCK>(block_type & ASHIBA);
	for(int fy = y; fy < MAP_HEIGHT; fy++){
		render_block(map[x][fy], x, fy);		//�u���b�N�\��
		if(x % 2 == 0){							//���\���p����
			if(map[x][fy] != 0){
				fy % 4 == 0 ? render_block(BLOCK_FIRE, x, fy) : "" ;
			}
		}else{									//���\���p����
			if(map[x][fy] != 0){
				fy % 3 == 0 ? render_block(BLOCK_FIRE, x, fy) : "" ;
			}
		}
	}
	if(map[x - 1][10] == block_type){
		int block_x =  (int)floor((x - screen_x) * 32);
		int block_y  = y * 32;
		PrintPicture::instance()->StringDraw("PORT", block_x - 30, 15 * 32, 2);	//�|�[�g�\��
		switch(block_type & COIN_ALL){
			case COIN_FTP:
				PrintPicture::instance()->NumDraw(21, block_x, 13 * 32 + 16, 3);
				break;
			case COIN_SSH:
				PrintPicture::instance()->NumDraw(22, block_x, 13 * 32 + 16, 3);
				break;
			case COIN_SMTP:
				PrintPicture::instance()->NumDraw(25, block_x, 13 * 32 + 16, 3);
				break;
			case COIN_DNS:
				PrintPicture::instance()->NumDraw(53, block_x, 13 * 32 + 16, 3);
				break;
			case COIN_HTTP:
				PrintPicture::instance()->NumDraw(80, block_x, 13 * 32 + 16, 3);
				break;
			case COIN_HTTPS:
				PrintPicture::instance()->NumDraw(443, block_x, 13 * 32 + 16, 3);
				break;
		}
	}
}
void GameMap::render_block(int block_type, int x, int y){
	if(block_type == 0){
		//return;
	}
	int block_x, block_y;
	block_x =  (int)floor((x - screen_x) * 32);
	block_y  = y * 32;
	switch(block_type & 0x1FFF){	//AND���Z��ROUTER��SWITCH������
		case ASHIBA:
			DrawGraph(block_x, block_y, block_brick, true);
		break;
		case SHOGAI:
			DrawGraph(block_x, block_y, block_ware, true);
		break;
		case ITEM:
			DrawGraph(block_x, block_y, block_hatena, true);
		break;
		case SWITCH: 
			//DrawModiGraph(block_x, block_y, block_x + 32, block_y, block_x + 32, block_y + 32, block_x, block_y + 32, block_switch, true); 
			DrawGraph(block_x, block_y + 10, block_switch,true);
		break;
		case ROUTER:
			//DrawModiGraph(block_x, block_y, block_x + 32, block_y, block_x + 32, block_y + 32, block_x, block_y + 32, block_router, true); 
			DrawGraph(block_x, block_y + 5, block_router,true);
		break;
		case COIN_FTP:
			DrawGraph(block_x, block_y, block_packet, true);
			PrintPicture::instance()->NumDraw(21,block_x+13,block_y+15,1);
			
		break;
		case COIN_SSH:
			DrawGraph(block_x, block_y, block_packet, true);
			PrintPicture::instance()->NumDraw(22,block_x+13,block_y+15,1);
			
		break;
		case COIN_SMTP:
			DrawGraph(block_x, block_y, block_packet, true);
			PrintPicture::instance()->NumDraw(25,block_x+13,block_y+15,1);
			
		break;
		case COIN_DNS:
			DrawGraph(block_x, block_y, block_packet, true);
			PrintPicture::instance()->NumDraw(53,block_x+13,block_y+15,1);
		break;
		case COIN_HTTP:
			DrawGraph(block_x, block_y, block_packet, true);
			PrintPicture::instance()->NumDraw(80,block_x+13,block_y+15,1);
		break;
		case COIN_HTTPS:
			DrawGraph(block_x, block_y, block_packet, true);
			PrintPicture::instance()->NumDraw(443,block_x+17,block_y+15,1);
		break;
		case ITEM_NORMAL:
			DrawGraph(block_x, block_y, block_normal, true);
		break;
		default:
#ifdef __DEBUG_
			DrawString(block_x + 16, block_y + 16, "1", GetColor(255,255,255));
			DrawFormatString(100, 90, GetColor(255,255,255), "screen_x = %f",screen_x);
#endif
		break;
	}
	if(block_type & BLOCK_FW){
		DrawGraph(block_x, block_y, block_brick, true);
	}
	if(block_type == BLOCK_FIRE){
		DrawGraph(block_x, block_y, block_fire32, true);
	}
}

int GameMap::checkMapHit(Nyancat* nyan){
		float nyan_x = nyan->getNyanX();
		float nyan_y = nyan->getNyanY();
		int tb[2], bb[2], cb[2],lb[2], rb[2], rbb[2], lbb[2];		//��A���A�����A���A�E�u���b�N [x,y] �@�E�΂߉� ���΂߉�
		float fcb_32[2];
		//�u���b�N�ɂ߂荞�ނ̂�h��
		cb[0] = round((nyan_x + screen_x * 32) / 32);	//���L������X���W
		cb[1] = round((nyan_y) / 32);	//���L������Y���W

		fcb_32[0] = cb[0] * 32.0f;	//cb[0] * 32 �����O�Ɍv�Z�������
		fcb_32[1] = cb[1] * 32.0f;	//cb[0] * 32 �����O�Ɍv�Z�������

		tb[0] = cb[0];		//���L�����̏�u���b�N��x���W
		tb[1] = cb[1] -1;	//���L�����̏�u���b�N��y���W
		
		bb[0] = cb[0];		//���L�����̏�u���b�N��x���W
		bb[1] = cb[1] +1;	//���L�����̏�u���b�N��y���W

		lb[0] = cb[0] -1;	//���L�����̍��u���b�N��x���W
		lb[1] = cb[1];		//���L�����̍��u���b�N��y���W

		rb[0] = cb[0] + 1;	//���L�����̉E�u���b�N��x���W
		rb[1] = cb[1];		//���L�����̉E�u���b�N��y���W

		rbb[0] = rb[0];		//���L�����̉E�΂߉��u���b�Nx
		rbb[1] = bb[1];		//���L�����̉E�΂߉��u���b�Ny

		lbb[0] = lb[0];		//���L�����̍��΂߉��u���b�Nx
		lbb[1] = bb[1];		//���L�����̍��΂߉��u���b�Ny

		
#ifdef __DEBUG_
		DrawFormatString(600,70, GetColor(0,0,0), "x = %d",cb[0]);
		DrawFormatString(600,90, GetColor(0,0,0), "y = %d",cb[1]);
		DrawFormatString(600,120, GetColor(0,0,0), "segment = %d",segment);
#endif
		
		//�L�����N�^�[���}�b�v�u���b�N�����яo���ꍇ
		//���ɔ�яo��
		if(fcb_32[0] > (nyan_x + screen_x * 32)){
			if(map[lb[0]][lb[1]] & ALL_HIT_BLOCK){
				if(map[lb[0]][lb[1]] & COIN_ALL){
					if(clear_fw(nyan, lb[0], lb[1])){
						nyan->revisePosition(1, cb[0] * 32 - (nyan_x + screen_x * 32.0f));	//�ʒu�C��
					}
				}else{
					nyan->revisePosition(1, cb[0] * 32 - (nyan_x + screen_x * 32.0f));	//�ʒu�C��
				}
			}
		}
		//�E�ɔ�яo��
		if(fcb_32[0] < (nyan_x + screen_x * 32)){
			if(map[rb[0]][rb[1]] & ALL_HIT_BLOCK){
				if(map[rb[0]][rb[1]] & COIN_ALL){
					if(clear_fw(nyan, rb[0], rb[1])){
						nyan->revisePosition(3, (nyan_x + screen_x * 32.0f) - cb[0] * 32.0f);	//�ʒu�C��
					}
				}else{
					nyan->revisePosition(3, (nyan_x + screen_x * 32.0f) - cb[0] * 32.0f);	//�ʒu�C��
				}
			}
		}

		//��ɔ�яo�Ă邩
		if(fcb_32[1] > nyan_y){
			if(map[tb[0]][tb[1]] & ALL_HIT_BLOCK){
				nyan->revisePosition(2, cb[1] * 32 - nyan_y);	//�ʒu�C��
			}
			if(map[tb[0]][tb[1]] & ITEM){
				if(map[tb[0]][tb[1]] & (ROUTER_FLAG & ~ITEM)){
					map[tb[0]][tb[1]-1] = ROUTER;
				}else if(map[tb[0]][tb[1]] & (SWITCH_FLAG & ~ITEM)){
					map[tb[0]][tb[1]-1] = SWITCH;
				}
				map[tb[0]][tb[1]] = ITEM_NORMAL;
			}
		}
		//�������ɔ�яo���ꍇ
		if(fcb_32[1] + 11 < nyan_y){	//�{���� cb[1] * 32 + 32 < nyan_y + 32�����Ǎ������̂��� ;�L�����N�^�̃T�C�Y��20�̂��� + 12
			if(map[bb[0]][bb[1]] & ALL_HIT_BLOCK){
				nyan->revisePosition(0, nyan_y - (cb[1] * 32 + 12));	//�ʒu�C��
				nyan->offFall();
			}else{
				nyan->onFall();
			}
		}
		//���L�������u���b�N�ɂ߂荞�񂾏ꍇver2
		if(map[cb[0]][cb[1]] & ALL_HIT_BLOCK){
			//�v���C���̍��W
			struct Point nyanP	= {	(int)nyan_x,		(int)nyan_y, 
									(int)nyan_x + 32,	(int)nyan_y, 
									(int)nyan_x + 32,	(int)nyan_y + 12, 
									(int)nyan_x,		(int)nyan_y + 12, };
			//�u���b�N�̍��W
			struct Point block	= {	(cb[0] - (int)ceill(screen_x) + 1) * 32,				cb[1] * 32,
									(cb[0] - (int)ceill(screen_x) + 1) * 32 + 32,		cb[1] * 32, 
									(cb[0] - (int)ceill(screen_x) + 1) * 32 + 32,		cb[1] * 32 + 32, 
									(cb[0] - (int)ceill(screen_x) + 1) * 32,				cb[1] * 32 + 32};
			struct Point block_center = {	(cb[0] - (int)ceill(screen_x) + 1)  * 32 + 16, cb[1] * 32 + 16,
											(cb[0] - (int)ceill(screen_x) + 1)  * 32 + 16, cb[1] * 32 + 16,
											(cb[0] - (int)ceill(screen_x) + 1)  * 32 + 16, cb[1] * 32 + 16, 
											(cb[0] - (int)ceill(screen_x) + 1)  * 32 + 16, cb[1] * 32 + 16
										};

			//�扽�ی����U�蕪����
			//3,4
			if(nyanP.y3 >= block.y0 && nyanP.y3 < block_center.y0){
				nyan->revisePosition(0, (float)nyanP.y3 + GRAVITY - block.y0);	//��ɉ����グ��
			}
			//1,2
			if(nyanP.y0 <= block.y3 && nyanP.y0 + 12 > block_center.y0){
				nyan->revisePosition(2, (float)block.y3 - nyanP.y0);			//���ɉ����グ��
			}

			//FW�̏���
			if(map[cb[0]][cb[1]] & COIN_ALL){
				clear_fw(nyan, cb[0], cb[1]);
			}
		}

		//�A�C�e�����擾��������
		if(map[cb[0]][cb[1]] & DROPITEM){
			if(map[cb[0]][cb[1]] == SWITCH){
				switchAction(nyan);
				map[cb[0]][cb[1]] = 0;
			}else if(map[cb[0]][cb[1]] == ROUTER){
				nextSegment(nyan);
				map[cb[0]][cb[1]] = 0;
			}
		}

		//�X�N���[����ɉ�ʍ��ɓ���Ȃ��悤�ɂ���
		if(0 > nyan_x){
			nyan->revisePosition(1, 0 - nyan_x);
		}
		//�S�[���n�_�ɓ��B�������̏���
		if(cb[0] >= 208){
				//nyan->reset();
			nyan->goal();
		}

		//���L�������p�P�b�g���擾�����ꍇ
		if(map[cb[0]][cb[1]] & COIN_ALL && !(map[cb[0]][cb[1]] & ASHIBA)){
			nyan->sumScore(100);	//�X�R�A���Z

			//���L�����̃|�[�g�ԍ��ύX
			int block = map[cb[0]][cb[1]];
			if(block & COIN_FTP){
				nyan->changePortNumber(21);
			}else if(block & COIN_SSH){
				nyan->changePortNumber(22);
			}else if(block & COIN_SMTP){
				nyan->changePortNumber(25);
			}else if(block & COIN_DNS){
				nyan->changePortNumber(53);
			}else if(block & COIN_HTTP){
				nyan->changePortNumber(80);
			}else if(block & COIN_HTTPS){
				nyan->changePortNumber(443);
			}
			/*Effect * effect = (Effect*)malloc(sizeof(Effect));
			effect->blocktype = block;
			effect->nyan = nyan;
			effect->sx = nyan_x;
			effect->sy = nyan_y;
			effect->alpha = 255;
			addAnimation(effect);*/
			map[cb[0]][cb[1]] = 0;	//�p�P�b�g������
		}
		
		if(cb[1] > 18){
			nyan->dead();
#ifdef __DEBUG_
			nyan->offFall();
#endif
		}

		

		//�ɂ��L���b�g�̓����Ɖ�ʂ̃X�N���[����A��
		if(nyan_x > screen_center_x){
			float xdiff = nyan_x - screen_center_x;
			screenScroll_x(xdiff / 32.0f);
			if(xdiff > 0){
				if(screen_x < MAP_WIDTH * 6 - SCREEN_WIDTH){
					nyan->revisePosition(3, xdiff);	
				}
			}
		}
		
		//��ʃX�N���[���ɂ���
		if(move_screen > 0){
			move_screen = move_screen - 0.01f;
			if(move_screen < 0.01f){move_screen = 0.0f;}
			screen_x	= screen_x + move_screen;
		}
		
#ifdef __DEBUG_
		//DrawBox((int)(cb[0] - ceill(screen_x)) * 32, cb[1] * 32, (int)(cb[0] - ceill(screen_x)) *32 + 32, cb[1] * 32 + 32, GetColor(200,0,0),true);
		if(map[cb[0]][cb[1]] != 0){
			DrawString(500, 100, "�ڐG", GetColor(255,255,255));
		}
#endif
		return 0;
	}
void GameMap::screenScroll_x(float value){
	if(screen_x < MAP_WIDTH * 6 - SCREEN_WIDTH){
		move_screen = value;
	}
}
//����x���W �E��x���W y���W
//������w�肷���FW������
int GameMap::clear_fw(Nyancat* nyan, int x, int y){
	bool accept = false;
	switch(map[x][0] & COIN_ALL){
			case COIN_FTP:
				if(nyan->getPortNumber() == 21) accept = true;
				break;
			case COIN_SSH:
				if(nyan->getPortNumber() == 22) accept = true;
				break;
			case COIN_SMTP:
				if(nyan->getPortNumber() == 25) accept = true;
				break;
			case COIN_DNS:
				if(nyan->getPortNumber() == 53) accept = true;
				break;
			case COIN_HTTP:
				if(nyan->getPortNumber() == 80) accept = true;
				break;
			case COIN_HTTPS:
				if(nyan->getPortNumber() == 443) accept = true;
				break;
	}
	if(accept){
		if(map[x][0] & BLOCK_FW){
			map[x][0] = map[x][0] ^ BLOCK_FW;
			nyan->sumScore(250);
		}
		map[x][y] = 0;
		nyan->onFall();
		return 0;
	}else{
		return -1;
	}
}
void GameMap::Animation(){
	list<struct Effect>::iterator it = effectList.begin();
	while(it != effectList.end()){
		it->sx = (it->nyan->getNyanX() - it->sx) * 0.7f;
		it->sy = (it->nyan->getNyanY() - it->sy) * 0.7f;
		it->alpha = it->alpha - 0.01f;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)it->alpha);
		render_block(it->blocktype, (int)it->sx, (int)it->sy);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		if(it->alpha < 25){
				it = effectList.erase(it);
		}
	}
}

void GameMap::addAnimation(Effect *effect){
	effectList.push_front(*effect);
}

void GameMap::nextSegment(Nyancat* nyan){
	if(segment < 5){
		screen_x = (float)(segment+ 1) * MAP_WIDTH;
		nyan->flyday();
		nyan->onFall();
	}
}
//�X�C�b�`���擾�����ꍇ
void GameMap::switchAction(Nyancat* nyan){
	int size = (int)floor(screen_x);
	for(int x = size; x < SCREEN_WIDTH + size; x++){
		for(int y = 0; y < MAP_HEIGHT; y++){
			if(map[x][y] & COIN_ALL && !(map[x][y] & ASHIBA)){	//�R�C�������ꂶ��Ȃ��ꍇ�̂�
				nyan->sumScore(80);
				map[x][y] = 0;
			}
		}
	}
}

int GameMap::Digit(int digit){
	int i;
	for(i=0;digit!=0;i++)
		digit/=10;
	if(i==0){
		return 1;}
	else
	{
		return i;
	}
}