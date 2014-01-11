#ifndef __NYANCAT_
#define __NYANCAT_
#include "Child.h"


class GameMap;
class ParentWindow;
class PrintPicture;

class Nyancat : public Child{
private:
	int handle[6];
	float nyan_x;	//�v���C���̍��W x
	float nyan_y;	//�v���C���̍��W y
	float top;		//���t���[���ł̈ړ��� ��
	float left;		//���t���[���ł̈ړ��� ��
	float right;	//���t���[���ł̈ړ��� �E
	int nyan_port;	//�|�[�g�ԍ�

	bool fall;		//���R����
	float GA;		//�������x
	bool ground;

	int sound[5];
	int voice;		
	
	GameMap* nowMap;
	int score;
	PrintPicture* printPic;
	bool leftflag;
	char key[256];
	bool goalFlag;
	bool deadFlag;
public:
	Nyancat();
	~Nyancat();
	void update(ParentWindow*);
	void render();
	void jump();
	void moveDown();
	void moveLeft();
	void moveRight();
	void grabity();

	//DEBUG
	void reset();
	void goal();
	void dead();
	//���R�����J�n
	void onFall();
	//���R�����I��
	void offFall();
	//�ڒn����ON
	void onground();
	//�ڒn����OFF
	void offground();
	//�v���C���[�������Ă���Ȃ�true
	bool isMoveNyan();

	//���W�C��
	// 0 = ��A 1 = �E�A 2 = ���A 3 = ��
	void revisePosition(int direction, int value);
	//�j����������X���W���擾
	float getNyanX();
	//�j����������Y���W���擾
	float getNyanY();

	void sumScore(int value);
	void changePortNumber(int port);
};
#endif