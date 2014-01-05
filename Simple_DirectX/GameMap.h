#ifndef GAME_MAP
#define GAME_MAP
#include "headall.h"

class GameMap{
private:
	float screen_x;
	LPDIRECT3DTEXTURE9 block_brick;
	LPDIRECT3DTEXTURE9 block_hatena;
	LPDIRECT3DTEXTURE9 block_normal;
	LPDIRECT3DTEXTURE9 block_packet;
	LPDIRECT3DTEXTURE9 block_ware;
	typedef struct _tlvertex{	// 上記頂点フォーマットに合わせた構造体を定義
		float x,y,z;
		float rhw;
		D3DCOLOR diffuse;
		D3DCOLOR specular;
		float tu,tv;
	}TLVERTEX;
	TLVERTEX vertex[4];

public:
	char map[46][18];
	static const int MAP_WIDTH = 46;
	static const int MAP_HEIGHT = 18;
	GameMap(LPDIRECT3DDEVICE9 g_pd3dDev);
	void render(LPDIRECT3DDEVICE9 g_pd3dDev);
	void render_block(LPDIRECT3DDEVICE9 g_pd3dDev, int block_type, int x, int y);
	void screenScroll_x(int value);
};

#endif