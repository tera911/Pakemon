/**
�f���؂�͎̂コ�I�a��J���͖����I
�S���т��E�C�̐n�I
�L���A�\�[�h�I
*/
#include "Nyancat.h"
#include "GameMap.h"
#include <DxLib.h>
#include <time.h>
#include "PrintPicture.h"
#include "ParentWindow.h"

#define SAFE_DELETE(x)	{\
	delete (x);\
	(x) = 0;\
}

Nyancat::Nyancat(){
		//Nyan�̕`��
		LoadDivGraph("item/Nyan_s.png", 6, 6, 1, 32, 20, handle);

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
		nowMap = new GameMap();
	
		//���y�̃��[�h
		sound[0]	=	LoadSoundMem( "nyanVoice\\nyan01.wav" ) ;
		sound[1]	=	LoadSoundMem( "nyanVoice\\nyan02.wav" ) ;
		sound[2]	=	LoadSoundMem( "nyanVoice\\nyan03.wav" ) ;
		sound[3]	=	LoadSoundMem( "nyanVoice\\nyan04.wav" ) ;
		sound[4]	=	LoadSoundMem( "nyanVoice\\nyan05.wav" ) ;
		sound[5]	=	LoadSoundMem( "nyanVoice\\nyan06.wav" ) ;
//		printPic=new PrintPicture();
		score = 0;
		leftflag = false;
		goalFlag = false;
		deadFlag = false;
		frame=0;
	}
	void Nyancat::update(ParentWindow* parent){
		if(goalFlag){
			parent->registScore(score, 150 - frame / 60, true);
			parent->moveTo(ParentWindow::RESULT);
		}
		if(deadFlag){
			parent->registScore(score, 0, false);
			parent->moveTo(ParentWindow::RESULT);
		}
		frame++;
		if(frame >= 9000){
			parent->moveTo(ParentWindow::RESULT);
		}
		GetHitKeyStateAll(key);
		if(key[KEY_INPUT_C] == 1){
			jump();
		}
		if(key[KEY_INPUT_LEFT] == 1){
			moveLeft();
		}
		if(key[KEY_INPUT_RIGHT] == 1){
			moveRight();
		}
		render();
	}
	void Nyancat::render(){
		if(nowMap == NULL){
			return;
		}
		nowMap->render();
		nowMap->checkMapHit(this);
		if(left){
			DrawTurnGraph((int)nyan_x, (int)nyan_y,handle[3],true);
		}
		else
		{
			DrawGraph((int)nyan_x, (int)nyan_y, handle[3], true);
		}
		
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
	
#ifdef __DEBUG_
		//y���W�ʒu����
		DrawFormatString(500, 100, 0, "nyan_y = %f", nyan_y);
#endif
		//�X�R�A�\��
		PrintPicture::instance()->StringDraw("SCORE",150,25,2);
		PrintPicture::instance()->NumDraw(score,300, 25, 2);
		//���L�����̃|�[�g�ԍ��\��
		if(nyan_port != 0){
			if(nyan_port==443){
				PrintPicture::instance()->NumDraw(nyan_port, (int)(nyan_x + 20.0f),(int)(nyan_y - 10.0f),1);
			}else{
				PrintPicture::instance()->NumDraw(nyan_port, (int)(nyan_x + 15.0f),(int)(nyan_y - 10.0f),1);
				}
			}
		PrintPicture::instance()->StringDraw("TIME",600,0,2);
		PrintPicture::instance()->NumDraw(150 - frame / 60 ,700,0,2);
	}
	void Nyancat::jump(){
		if(!fall){
		//	top = 15.0f;
			for(int i=0;i<20;i++){
			top+=1;
			}
			//printfDx("%d",voice);
			voice=GetRand(6);
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
		leftflag=true;
	}
	void Nyancat::moveRight(){
		right = 3;
		leftflag=false;
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
	//�S�[��
	void Nyancat::goal(){
		goalFlag = true;
	}
	void Nyancat::dead(){
		deadFlag = true;
	}
	//���R�����J�n
	void Nyancat::onFall(){
		fall = true;
	}
	//���R�����I��
	void Nyancat::offFall(){
		fall = false;
	}
	bool Nyancat::isMoveNyan(){
		return (fall);
	}

	//���W�C��
	// 0 = ��A 1 = �E�A 2 = ���A 3 = ��
	void Nyancat::revisePosition(int direction, float value){
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
	//�Z�O�����g�ړ��p
	//�j�����L���b�g�̈ʒu������ɂ���
	void Nyancat::flyday(){
		nyan_x = 100;
		nyan_y = 0;
	}
	Nyancat::~Nyancat(){
		SAFE_DELETE(nowMap);
	}