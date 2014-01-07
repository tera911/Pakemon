#include "GameMap.h"
#include "Nyancat.h"

int GameMap::checkMapHit(Nyancat* nyan){
		float nyan_x = nyan->getNyanX();
		float nyan_y = nyan->getNyanY();
		int tb[2], bb[2], cb[2],lb[2], rb[2];		//��A���A�����A���A�E�u���b�N [x,y] 

		cb[0] = round(nyan_x / 32.0f);	//���L������X���W
		cb[1] = round(nyan_y / 32.0f);	//���L������Y���W
		
		tb[0] = cb[0];		//���L�����̏�u���b�N�̍��W
		tb[1] = cb[1] -1;	//���L�����̏�u���b�N�̍��W
		
		bb[0] = cb[0];		//���L�����̏�u���b�N�̍��W
		bb[1] = cb[1] +1;	//���L�����̏�u���b�N�̍��W

		//�܂��͏ォ��
		if(map[tb[0]][tb[1]] == 'A' || map[tb[0]][tb[1]] == 'S' || map[tb[0]][tb[1]] == 'I'){
		//	nyan->revisePosition(0, nyan_y - tb[1] * 32);
		}
		

		//���ɑ���u���b�N���������ꍇ
		if(map[bb[0]][bb[1]] == 'A' || map[bb[0]][bb[1]] == 'S' || map[bb[0]][bb[1]] == 'I'){
			nyan->offFall();
			nyan->onground();
			
		}else{
			nyan->onFall();
			nyan->offground();
		}

		int block_x = (nyan_x / 32) + 1;
		int block_y = (nyan_y / 32) + 1;
		DrawBox(cb[0] * 32, cb[1] * 32, (cb[0] * 32) + 32,(cb[1] * 32) +  32, GetColor(255,0,0), true);
		if(map[cb[0]][cb[1]] != 0){
			DrawString(500, 100, "�ڐG", GetColor(255,255,255));
		}
		return 0;
	}