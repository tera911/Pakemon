#include "OptionWindow.h"
#include "ParentWindow.h"
#include <DxLib.h>
#include "KeyBoardTools.h"

//����̓R���X�g���N�^�ŃQ�\
//�ϐ��̏������Ȃǎg���܂��ŃQ�\
OptionWindow::OptionWindow(){
	ZeroMemory(key, sizeof(int) * 256);
	frame = 0;
}

//�e�N���X�i�X�[�p�N���X�j����Ăяo�����֐��ŃQ�\
//�\������鏈���� 1/60�b�Ŏ��s����܂��ŃQ�\
//��ʑJ�ڂȂǂ���ۂ�parentWindow�ɑ΂���moveTo�����s���܂��ŃQ�\
//ex. parent->moveTo(ParentWindow::TITLE);		//�^�C�g���Ɉړ����邶��ȃC�J
void OptionWindow::update(ParentWindow* parent){
	if(frame > 10){
		KeyBoardTools::GetHitKeyStateAll_2(key);
	}

	if(key[KEY_INPUT_SPACE] == 1){
		parent->moveTo(ParentWindow::TITLE);
	}
	if(frame < 60){
		frame++;
	}
	render();
}

//�`��p�N���X����ȃC�J
//�����ɕ`��Ȃǂ̏����������ŃQ�\
void OptionWindow::render(){
	DrawString(200, 200, "MIKAN OPTION", GetColor(255,255,255));
}

//�f�X�g���N�^����ȃC�J�H
OptionWindow::~OptionWindow(){

}