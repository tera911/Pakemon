#include "ResultWindow.h"
#include "ParentWindow.h"
#include <DxLib.h>
#include "KeyBoardTools.h"
#include "PrintPicture.h"

//�R���X�g���N�^
ResultWindow::ResultWindow(){
	ZeroMemory(key, sizeof(int) * 256);
	frame = 0;
	score = -1;
	length = 0;
	select = RETRY;
	select_num = 0;
	LoadDivGraph("Nyan_s.png", 6, 6, 1, 32, 20, Nyan);
}

//�A�b�v�f�[�^�@�e����Ăяo�����֐�
//��ʑJ�ڎ��͂��̊֐����parent->moveTo(ParentWindow::STAT);���Ăяo��
void ResultWindow::update(ParentWindow* parent){
	if(frame > 10){
		KeyBoardTools::GetHitKeyStateAll_2(key);
	}
	if(frame < 60){
		frame++;
	}

	//�L�[����
	if(key[KEY_INPUT_UP] == 1){
			select_num--;
	}
	if(key[KEY_INPUT_DOWN] == 1){
			select_num++;
	}

	//�I��������
	if(select_num < 0){
		select_num = 1;
	}else if(select_num > 1){
		select_num = 0;
	}
	select = static_cast<TRY>(select_num);
	if(key[KEY_INPUT_SPACE] == 1 || key[KEY_INPUT_RETURN] == 1){
		switch(select){
			case RETRY:
				//���X�^�[�g
				parent->moveTo(ParentWindow::PLAY);
			break;
			case TITLE:
				//TITLE
				parent->moveTo(ParentWindow::TITLE);
			break;
		}
	}
	//�X�R�A�v�Z
	if(score == -1){
		score = parent->getScore() + (parent->getRemainingTime() * 100);
		score = score + (parent->isGoal() ? 1000 : 0);	//�S�[���Ȃ�+1000P
		for(int i = score; i > 0; i = i / 10){
			length++;
		}
	}
	render();//�`��
}

//�`��p����
void ResultWindow::render(){
	PrintPicture::instance()->StringDraw("PLAYSCORE",270,100,3);
	PrintPicture::instance()->NumDraw(score, (800 + 28 * (10 - length)) / 2, 170,3);

	PrintPicture::instance()->StringDraw("RETRY",370,400,2);
	PrintPicture::instance()->StringDraw("TITLE",370,440,2);
	switch(select){
			//���̏ꏊ
		case RETRY:
			DrawGraph(320, 400, Nyan[3], true);
		break;
		case TITLE:
			DrawGraph(320, 440, Nyan[3], true);
		break;
		}
}

//�f�X�g���N�^ ���낢��J���������肷��
ResultWindow::~ResultWindow(){
	//�񂧂ق��J���J�������H�H�@��߂��[�A�킽���������ق��J���J���������ЂႤ����

}