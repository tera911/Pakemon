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
	float nyan_x;	//プレイヤの座標 x
	float nyan_y;	//プレイヤの座標 y
	float top;		//次フレームでの移動量 上
	float left;		//次フレームでの移動量 左
	float right;	//次フレームでの移動量 右
	int nyan_port;	//ポート番号

	bool fall;		//自由落下
	float GA;		//落下速度
	bool ground;

	int sound[5];
	int voice;		
	
	GameMap* nowMap;
	GameMap* map1;	//プレイするMapのポインタ
	GameMap* map2;	//プレイするMapのポインタ
	GameMap* map3;	//プレイするMapのポインタ
	GameMap* map4;	//プレイするMapのポインタ
	GameMap* map5;	//プレイするMapのポインタ

	int score;
	
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
	//プレイヤーが動いているならtrue
	bool isMoveNyan();

	//座標修正
	// 0 = 上、 1 = 右、 2 = 下、 3 = 左
	void revisePosition(int direction, int value);
	//ニャンがいるX座標を取得
	float getNyanX();
	//ニャンがいるY座標を取得
	float getNyanY();

	void sumScore(int value);
	void changePortNumber(int port);
};
#endif