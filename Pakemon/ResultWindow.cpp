    //////////////////////////////////////////////////////
   //////										  ///////
  //////	����ҁ@�݂��r���̃h�[�x���}����	 ///////
 //////											///////
//////////////////////////////////////////////////////
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
	remainingTime = 0;
	goal = false;
	select = RETRY;
	select_num = 0;
	LoadDivGraph("item/Nyan_s.png", 6, 6, 1, 32, 20, Nyan);
	staffs=LoadGraph("item/staffs_oic.png");
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
				parent->moveTo(ParentWindow::OPTION);
			break;
			case TITLE:
				//TITLE
				parent->moveTo(ParentWindow::TITLE);
			break;
		}
	}
	//�X�R�A�v�Z
	if(score == -1){
		goal = parent->isGoal();
		remainingTime = parent->getRemainingTime();
		score = parent->getScore() + (remainingTime * 100);
		score = score + (goal ? 1000 : 0);	//�S�[���Ȃ�+1000P
		for(int i = score; i > 0; i = i / 10){
			length++;
		}
	}
	render();//�`��
}

//�`��p����
void ResultWindow::render(){
	PrintPicture *print = PrintPicture::instance();
	print->StringDraw("PLAYSCORE",270,100,3);
	print->NumDraw(score, (800 + 28 * (10 - length)) / 2, 170,3);
	print->StringDraw("REMAINING TIME",300, 280, 2);
	print->NumDraw(remainingTime, 530, 280, 2);
	DrawGraph(500,400,staffs,true);
	if(!goal){
		PrintPicture::instance()->StringDraw("NYAN IS DEAD!!", 400, 300, 2);
	}
	print->StringDraw("RETRY?",370,400,2);
	print->StringDraw("TITLE",370,440,2);
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