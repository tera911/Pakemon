#include "Nyancat.h"

#define SAFE_DELETE(x)	{\
	delete (x);\
	(x) = 0;\
}

Nyancat::Nyancat(){
		//Nyan�̕`��
		LoadDivGraph("Nyan_s.png", 6, 6, 1, 32, 20, handle);

		//�f�t�H���g�̍��W
		nyan_x = 200;
		nyan_y = 0;

		//1�t���[�����Ƃ̈ړ���
		top = 0;
		left = 0;
		right = 0;

		//�|�[�g�ԍ�
		nyan_port = 0;

				fall = true;
		GA = 0;

		//�}�b�v�̏�����
		map1 = new GameMap();
		map2 = 0;
		map3 = 0;
		map4 = 0;
		map5 = 0;
		nowMap = 0;

		nowMap = map1;

		//���y�̃��[�h
		sound[0]	=	LoadSoundMem( "nyanVoice\\nyan01.wav" ) ;
		sound[1]	=	LoadSoundMem( "nyanVoice\\nyan02.wav" ) ;
		sound[2]	=	LoadSoundMem( "nyanVoice\\nyan03.wav" ) ;
		sound[3]	=	LoadSoundMem( "nyanVoice\\nyan04.wav" ) ;
		sound[4]	=	LoadSoundMem( "nyanVoice\\nyan05.wav" ) ;
		sound[5]	=	LoadSoundMem( "nyanVoice\\nyan06.wav" ) ;
//		printPic=new PrintPicture();
		score = 0;
		
	}

	void Nyancat::render(){
		if(nowMap == NULL){
			return;
		}
		nowMap->render();
		nowMap->checkMapHit(this);
		DrawGraph(nyan_x, nyan_y, handle[3], true);
		nyan_x -= left;
		nyan_x += right;
		nyan_y -= top;
		
		grabity();
		//nyan_y += map->checkMapHit1(nyan_x, nyan_y, 0, GA);
		nyan_y += GA;
		if(left > 0){
			left -= 0.5;
		}
		if(right > 0){
			right -= 0.5;
		}
		if(top > 0){
			onFall();
			top -= 1.0f;
		}else{
			top = 0;
		}
		//y���W�ʒu����
		DrawFormatString(500, 100, 0, "nyan_y = %f", nyan_y);
		//�X�R�A�\��
		//DrawFormatString(100, 50, GetColor(255,255,255), "SCORE : %d", score);
		PrintPicture::instance()->NumDraw(score,100,50);
		//���L�����̃|�[�g�ԍ��\��
		if(nyan_port != 0){
		DrawFormatString(nyan_x + 5, nyan_y - 15, GetColor(255,255,255), "%d", nyan_port);
		}
	}
	void Nyancat::jump(){
		if(!fall){
		//	top = 15.0f;
			for(int i=0;i<20;i++){
			top+=1;
			}
			srand((unsigned) time(NULL));
			voice=rand();
			voice%=5;

			/*printfDx("%d",voice);
			voice=GetRand(6);*/
			if(CheckSoundMem(sound[voice])==0){ 
				PlaySoundMem(sound[voice],DX_PLAYTYPE_BACK);
				
			}
		}
		
	}
	void Nyancat::moveDown(){
		nyan_y +=1;
	}
	void Nyancat::moveLeft(){
		left = 3;
	}
	void Nyancat::moveRight(){
		right = 3;
	}
	void Nyancat::grabity(){
		if(fall){
			GA  = 4.9f;
		}else{
			GA = 0 ;
		}
		
	}
	void Nyancat::reset(){
		SAFE_DELETE(nowMap);
		nowMap = new GameMap();
		//�f�t�H���g�̍��W
		nyan_x = 200;
		nyan_y = 0;

		//1�t���[�����Ƃ̈ړ���
		top = 0;
		left = 0;
		right = 0;

		//�|�[�g�ԍ�
		nyan_port = 0;

				fall = true;
		GA = 0;
		score = 0;
	}
	//���R�����J�n
	void Nyancat::onFall(){
		fall = true;
	}
	//���R�����I��
	void Nyancat::offFall(){
		fall = false;
	}
	//�ڒn����ON
	void Nyancat::onground(){
		ground=true;
	}
	//�ڒn����OFF
	void Nyancat::offground(){
		ground=false;
	}
	bool Nyancat::isMoveNyan(){
		return (fall);
	}

	//���W�C��
	// 0 = ��A 1 = �E�A 2 = ���A 3 = ��
	void Nyancat::revisePosition(int direction, int value){
		char test[40];
		wsprintf(test, "%d\n",value);
		OutputDebugString(test);
		switch(direction){
		case 0:
			nyan_y = nyan_y + value;
		break;
		case 1:
			nyan_x = nyan_x + value;
		break;
		case 2:
			nyan_y = nyan_y - value;
		break;
		case 3:
			nyan_x = nyan_x - value;
		break;
		}
	}
	//�j����������X���W���擾
	float Nyancat::getNyanX(){
		return nyan_x;
	}
	//�j����������Y���W���擾
	float Nyancat::getNyanY(){
		return nyan_y;
	}

	//�X�R�A�����Z����
	void Nyancat::sumScore(int value){
		score = score + value;
	}

	//���L�����̃|�[�g�ԍ���ύX
	void Nyancat::changePortNumber(int port){
		nyan_port = port;
	}