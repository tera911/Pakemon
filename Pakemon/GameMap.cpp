#include "GameMap.h"
#include "Nyancat.h"

int GameMap::checkMapHit(Nyancat* nyan){
		float nyan_x = nyan->getNyanX();
		float nyan_y = nyan->getNyanY();
		int tb[2], bb[2], cb[2],lb[2], rb[2];		//��A���A�����A���A�E�u���b�N [x,y] 

		//�u���b�N�ɂ߂荞�ނ̂�h��
		cb[0] = round(nyan_x / 32.0f);	//���L������X���W
		cb[1] = round(nyan_y / 32.0f);	//���L������Y���W

		tb[0] = cb[0];		//���L�����̏�u���b�N��x���W
		tb[1] = cb[1] -1;	//���L�����̏�u���b�N��y���W
		
		bb[0] = cb[0];		//���L�����̏�u���b�N��x���W
		bb[1] = cb[1] +1;	//���L�����̏�u���b�N��y���W

		lb[0] = cb[0] -1;	//���L�����̍��u���b�N��x���W
		lb[1] = cb[1];		//���L�����̍��u���b�N��y���W

		rb[0] = cb[0] + 1;	//���L�����̍��u���b�N��x���W
		rb[1] = cb[1];		//���L�����̍��u���b�N��y���W

		DrawFormatString(600,70, GetColor(0,0,0), "x = %d",cb[0]);
		DrawFormatString(600,90, GetColor(0,0,0), "y = %d",cb[1]);
		
		//�L�����N�^�[���}�b�v�u���b�N�����яo���ꍇ

		//��ɔ�яo�Ă邩
		if(cb[1] * 32 > nyan_y){
			if(map[tb[0]][tb[1]] == 'A' || map[tb[0]][tb[1]] == 'S' || map[tb[0]][tb[1]] == 'I'){
				nyan->revisePosition(2, nyan_y - cb[1] * 32);	//�ʒu�C��
			}
		}
		//�������ɔ�яo���ꍇ
		if(cb[1] * 32 + 11 < nyan_y){	//�{���� cb[1] * 32 + 32 < nyan_y + 32�����Ǎ������̂��� ;�L�����N�^�̃T�C�Y��20�̂��� + 12
			if(map[bb[0]][bb[1]] == 'A' || map[bb[0]][bb[1]] == 'S' || map[bb[0]][bb[1]] == 'I'){
				nyan->revisePosition(0, (cb[1] * 32 + 12) - nyan_y);	//�ʒu�C��
				nyan->offFall();
				nyan->onground();
			}else{
				nyan->onFall();
				nyan->offground();
			}
		}
		//���ɔ�яo��
		if(cb[0] * 32 > nyan_x){
			if(map[lb[0]][lb[1]] == 'A' || map[lb[0]][lb[1]] == 'S' || map[lb[0]][lb[1]] == 'I'){
				nyan->revisePosition(1, cb[0] * 32 - nyan_x);	//�ʒu�C��
			}
		}
		//�E�ɔ�яo��
		if(cb[0] * 32 < nyan_x){
			if(map[rb[0]][rb[1]] == 'A' || map[rb[0]][rb[1]] == 'S' || map[rb[0]][rb[1]] == 'I'){
				nyan->revisePosition(3, nyan_x - cb[0] * 32);	//�ʒu�C��
			}
		}
		//���L�������u���b�N�ɂ߂荞�񂾏ꍇ�@
		if(map[cb[0]][cb[1]] == 'A' || map[cb[0]][cb[1]] == 'S' || map[cb[0]][cb[1]] == 'I'){
			float block_pos[2];
			block_pos[0] = cb[0] * 32 + 16;	//�u���b�N�̒��S���W x
			block_pos[1] = cb[1] * 32 + 16;	//�u���b�N�̒��S���W y
		
			if(block_pos[1] > nyan_y){
				nyan->revisePosition(0, block_pos[1] - nyan_y);
			}else if(block_pos[1] < nyan_y){
				nyan->revisePosition(2, nyan_y - block_pos[1]);
			}else if(block_pos[0] > nyan_x){
				nyan->revisePosition(3, block_pos[0] - nyan_x);
			}else if(block_pos[0] < nyan_x){
				nyan->revisePosition(1, nyan_x - block_pos[0]);
			}
		}

		//���L�������p�P�b�g���擾�����ꍇ
		if(map[cb[0]][cb[1]] == 'C'){
			map[cb[0]][cb[1]] = 0;	//�p�P�b�g������
		}
		

		int block_x = (nyan_x / 32) + 1;
		int block_y = (nyan_y / 32) + 1;
		DrawBox(cb[0] * 32, cb[1] * 32, (cb[0] * 32) + 32,(cb[1] * 32) +  32, GetColor(255,0,0), true);
		if(map[cb[0]][cb[1]] != 0){
			DrawString(500, 100, "�ڐG", GetColor(255,255,255));
		}
		return 0;
	}
int GameMap::checkMapHit1(float nyan_x, float nyan_y, int direction, float value){
		int tb[2], bb[2], cb[2],lb[2], rb[2];		//��A���A�����A���A�E�u���b�N [x,y] 
		cb[0] = round(nyan_x / 32.0f);	//���L������X���W
		cb[1] = round(nyan_y / 32.0f);	//���L������Y���W
		
		tb[0] = cb[0];		//���L�����̏�u���b�N�̍��W
		tb[1] = cb[1] -1;	//���L�����̏�u���b�N�̍��W
		
		bb[0] = cb[0];		//���L�����̏�u���b�N�̍��W
		bb[1] = cb[1] +1;	//���L�����̏�u���b�N�̍��W

		switch(direction){
		case 0:
			//��
			if(map[tb[0]][tb[1]] == 'A' || map[tb[0]][tb[1]] == 'S' || map[tb[0]][tb[1]] == 'I'){
					int next_value = nyan_y - cb[1] * 32;
					if(next_value > value){
						return next_value;
					}else{
						return value;
					}
				}
		break;
		}
		return value;
	}