#include "TitleWindow.h"
#include "ParentWindow.h"
#include <DxLib.h>

	//�R���X�g���N�^
	TitleWindow::TitleWindow(){
		ZeroMemory(key, 256);
		arrow_y = 200;
		select = START;
		select_num = 0;
		//�摜�ǂݍ���

	}

	//�J��Ԃ����s�����
	void TitleWindow::update(ParentWindow* parent){
		//��ʐ؂�ւ��ɂ��ď�<

		//�L�[����
		GetHitKeyStateAll(key);
		if(key[KEY_INPUT_UP] ==1){
			select_num++;
		}else if(key[KEY_INPUT_DOWN] ==1){
			select_num--;
		}else if(key[KEY_INPUT_SPACE] == 1 || key[KEY_INPUT_RETURN] == 1){
			switch(select){
				case START:
					//�X�^�[�g
					parent->moveTo(ParentWindow::PLAY);
				break;
				case OPTION:
					//�I�v�V����
					parent->moveTo(ParentWindow::OPTION);
				break;
				case EXIT:
					//������
					parent->moveTo(ParentWindow::EXIT);
				break;
			}
		}
		if(select_num < 0){
			select_num = 2;
		}else if(select_num > 2){
			select_num = 0;
		}
		select = static_cast<STAT>(select_num);

		//Enter, Space�������ꂽ��m��
		
		
		//�`��
		render();
	}
	//�`��p
	void TitleWindow::render(){
		DrawString(200,200,"�݂���",GetColor(255,255,255));
        DrawString( 330 , 420 , "START" , GetColor(255,255,255) );
        DrawString( 330 , 440 , "OPTION" , GetColor(255,255,255) );
        DrawString( 330 , 460 , "EXIT"   , GetColor(255,255,255) );
		switch(select){
			//���̏ꏊ
		case START:
			DrawString( 300 , 420   , "��"    , GetColor(255,255,255) );
		break;
		case OPTION:
			DrawString( 300 , 440   , "��"    , GetColor(255,255,255) );
		break;
		case EXIT:
			DrawString( 300 , 460   , "��"    , GetColor(255,255,255) );
		break;
		}
	}

	//�f�X�g���N�^
	TitleWindow::~TitleWindow(){

	}
