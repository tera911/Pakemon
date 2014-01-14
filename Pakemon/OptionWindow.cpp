#include "OptionWindow.h"
#include "ParentWindow.h"
#include <DxLib.h>
#include "KeyBoardTools.h"
#include "PrintPicture.h"

//����̓R���X�g���N�^�ŃQ�\
//�ϐ��̏������Ȃǎg���܂��ŃQ�\
OptionWindow::OptionWindow(){
	ZeroMemory(key, sizeof(int) * 256);
	frame = 0;
	select=ICMP;
	select_num = 0;
	LoadDivGraph("item/Nyan_s.png", 6, 6, 1, 32, 20, Nyan);
	LoadDivGraph("item/title_nyancatrun_oic.png",6,6,1,320,320,NyanBig);
	i=0;
}

//�e�N���X�i�X�[�p�N���X�j����Ăяo�����֐��ŃQ�\
//�\������鏈���� 1/60�b�Ŏ��s����܂��ŃQ�\
//��ʑJ�ڂȂǂ���ۂ�parentWindow�ɑ΂���moveTo�����s���܂��ŃQ�\
//ex. parent->moveTo(ParentWindow::TITLE);		//�^�C�g���Ɉړ����邶��ȃC�J
void OptionWindow::update(ParentWindow* parent){
	if(frame > 10){
		KeyBoardTools::GetHitKeyStateAll_2(key);
	}

	if(key[KEY_INPUT_UP] == 1){
			select_num--;
	}
	if(key[KEY_INPUT_DOWN] == 1){
			select_num++;
	}
	if(select_num < 0){
		select_num = 2;
	}else if(select_num > 2){
		select_num = 0;
	}
	select = static_cast<packet>(select_num);
	if(key[KEY_INPUT_SPACE] == 1 || key[KEY_INPUT_RETURN] == 1){
		switch(select){
			case ICMP:
				//ICMP��I�񂾍ۂ̏���
			break;
			case HTTP:
				//HTTP��I�񂾍ۂ̏���
				break;
			case TITLE:
				//TITLE
				parent->moveTo(ParentWindow::TITLE);
			break;
		}
	}
	if(frame < 48){
			frame++;
		}else{
			frame = 12;
		}
	render();
}

//�`��p�N���X����ȃC�J
//�����ɕ`��Ȃǂ̏����������ŃQ�\
void OptionWindow::render(){
	if(frame % 6 == 0){
			i++;
			if(i > 5){
				i = 0;
			}
		}
	PrintPicture *print = PrintPicture::instance();
	DrawGraph(240, 80, NyanBig[i], true);
	print->StringDraw("SELECT USE PACKET",180,150,3);
	print->StringDraw("ICMP",	358,450,2);
    print->StringDraw("HTTP",	358,480,2);
	print->StringDraw("TITLE",	358,530,2);
	/*print->StringDraw("?./!",	0,0,1);
	print->StringDraw("?./!",	0,50,2);
	print->StringDraw("?./!",	0,100,3);*/
	switch(select){
			//���̏ꏊ
		case ICMP:
			DrawGraph(300, 450, Nyan[3], true);
		break;
		case HTTP:
			DrawGraph(300, 480, Nyan[3], true);
		break;
		case TITLE:
			DrawGraph(300,530,Nyan[3],true);
			break;
		}

}

//�f�X�g���N�^����ȃC�J�H
OptionWindow::~OptionWindow(){

}