#ifndef __NYANCAT_
#define __NYANCAT_
#include "Child.h"


class GameMap;
class ParentWindow;
class PrintPicture;

class Nyancat : public Child{
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

	int sound[5];
	int voice;		
	
	GameMap* nowMap;
	int score;
	PrintPicture* printPic;
	bool leftflag;
	char key[256];
	bool goalFlag;
	bool deadFlag;
	int frame;
	int BGM;
public:
	Nyancat(ParentWindow* parent, int packetType);
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
	//自由落下開始
	void onFall();
	//自由落下終了
	void offFall();
	//プレイヤーが動いているならtrue
	bool isMoveNyan();

	//座標修正
	// 0 = 上、 1 = 右、 2 = 下、 3 = 左
	void revisePosition(int direction, float value);
	//ニャンがいるX座標を取得
	float getNyanX();
	//ニャンがいるY座標を取得
	float getNyanY();

	void sumScore(int value);
	void changePortNumber(int port);
	int	 getPortNumber();
	//ニャンキャットの位置を左上にする
	void flyday();
};
#endif