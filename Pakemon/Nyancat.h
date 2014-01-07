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
	bool fall;	//自由落下
	float GA;	//落下速度
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

	//自由落下開始
	void onFall();
	//自由落下終了
	void offFall();
	//接地判定ON
	void onground();
	//接地判定OFF
	void offground();

	//座標修正
	// 0 = 上、 1 = 右、 2 = 下、 3 = 左
	void revisePosition(int direction, int value);
	//ニャンがいるX座標を取得
	float getNyanX();
	//ニャンがいるY座標を取得
	float getNyanY();

};
#endif