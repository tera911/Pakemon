#ifndef __NYANCAT_
#define __NYANCAT_

#include "GameMap.h"
#include <DxLib.h>
#include <iostream>
#include <time.h>
class GameMap;

class Nyancat{
private:
	int handle[6];
	float nyan_x;
	float nyan_y;
	float top;
	float left;
	float right;
	bool fall;	//���R����
	float GA;	//�������x
	int sound[5];
	int voice;
	bool ground;
	GameMap* map;
	
public:
	Nyancat();
	void render();
	void jump();
	void moveDown();
	void moveLeft();
	void moveRight();
	void grabity();

	//���R�����J�n
	void onFall();
	//���R�����I��
	void offFall();
	//�ڒn����ON
	void onground();
	//�ڒn����OFF
	void offground();

	//���W�C��
	// 0 = ��A 1 = �E�A 2 = ���A 3 = ��
	void revisePosition(int direction, int value);
	//�j����������X���W���擾
	float getNyanX();
	//�j����������Y���W���擾
	float getNyanY();

};
#endif