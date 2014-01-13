#include "TitleWindow.h"
#include "ParentWindow.h"
#include <DxLib.h>
#include "KeyBoardTools.h"

	//�R���X�g���N�^
	TitleWindow::TitleWindow(){
		ZeroMemory(key, sizeof(int)	*	256);
		arrow_y = 200;
		select = START;
		select_num = 0;
		//�摜�ǂݍ���
		LoadDivGraph("Nyan_s.png", 6, 6, 1, 32, 20, Nyan);
		TitleLogo	=	LoadGraph("title/title_logo_oic.png");
		LoadDivGraph("title/title_nyancatrun_oic.png",6,6,1,320,320,NyanTitle);
		team = LoadGraph("oic2c.class_oic.png");
		frame = 0;
		untitti=0;
	}

	//�J��Ԃ����s�����
	void TitleWindow::update(ParentWindow* parent){
		//��ʐ؂�ւ��ɂ��ď�<
		//�L�[����
		if(frame > 10){
			KeyBoardTools::GetHitKeyStateAll_2(key);
		}
		if(key[KEY_INPUT_UP] == 1){
			select_num--;
		}
		if(key[KEY_INPUT_DOWN] == 1){
			select_num++;
		}
		
		//Enter, Space�������ꂽ��m��
		if(key[KEY_INPUT_SPACE] == 1 || key[KEY_INPUT_RETURN] == 1){
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
		
		if(frame < 48){
			frame++;
		}else{
			frame = 12;
		}
		//�`��
		render();
	}
	//�`��p
	void TitleWindow::render(){
		if(frame % 6 == 0){
			untitti++;
			if(untitti > 5){
				untitti = 0;
			}
		}
		
		//printfDx("%d",frame);
		
		DrawGraph(126, 60, TitleLogo, true);	//���S
		DrawGraph(240, 80, NyanTitle[untitti], true);	//�ɂ�񂫂����
		DrawGraph(40,540,team,true);
		PrintPicture::instance()->StringDraw("START",	358,450,2);
        PrintPicture::instance()->StringDraw("OPTION",	358,480,2);
		PrintPicture::instance()->StringDraw("EXIT",	358,510,2);
		switch(select){
			//���̏ꏊ
		case START:
			DrawGraph(300, 445, Nyan[3], true);
		break;
		case OPTION:
			DrawGraph(300, 475, Nyan[3], true);
		break;
		case EXIT:
			DrawGraph(300, 505, Nyan[3], true);
		break;
		}
	}

int TitleWindow::GetHitKeyStateAll_2(int KeyStateBuf[]){
    char GetHitKeyStateAll_Key[256];
    GetHitKeyStateAll( GetHitKeyStateAll_Key );
    for(int i=0;i<256;i++){
            if(GetHitKeyStateAll_Key[i]==1) KeyStateBuf[i]++;
            else                            KeyStateBuf[i]=0;
    }
    return 0;
}

	//�f�X�g���N�^
	TitleWindow::~TitleWindow(){

	}
