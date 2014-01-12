#include "ResultWindow.h"
#include "ParentWindow.h"
#include <DxLib.h>
#include "KeyBoardTools.h"

//�R���X�g���N�^
ResultWindow::ResultWindow(){
	ZeroMemory(key, sizeof(int) * 256);
	frame = 0;
}

//�A�b�v�f�[�^�@�e����Ăяo�����֐�
//��ʑJ�ڎ��͂��̊֐����parent->moveTo(ParentWindow::STAT);���Ăяo��
void ResultWindow::update(ParentWindow* parent){
	if(frame > 10){
		KeyBoardTools::GetHitKeyStateAll_2(key);
	}

	if(key[KEY_INPUT_SPACE] == 1){
		parent->moveTo(ParentWindow::TITLE);
	}
	if(frame < 60){
		frame++;
	}
	render();//�`��
}

//�`��p����
void ResultWindow::render(){
	DrawString(200, 200, "MIKAN RESULT", GetColor(255,255,255));
}

//�f�X�g���N�^ ���낢��J���������肷��
ResultWindow::~ResultWindow(){
	//�񂧂ق��J���J�������H�H�@��߂��[�A�킽���������ق��J���J���������ЂႤ����

}