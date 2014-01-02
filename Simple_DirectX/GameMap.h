#ifndef GAME_MAP
#define GAME_MAP
#include "headall.h"

class GameMap{
private:
	char map[46][18];
	LPDIRECT3DTEXTURE9 block_brick;
	LPDIRECT3DTEXTURE9 block_hatena;
	LPDIRECT3DTEXTURE9 block_normal;
	LPDIRECT3DTEXTURE9 block_packet;
	LPDIRECT3DTEXTURE9 block_ware;

public:
	static const int MAP_WIDTH = 46;
	static const int MAP_HEIGHT = 18;
	GameMap(LPDIRECT3DDEVICE9 g_pd3dDev);
	void render(LPDIRECT3DDEVICE9 g_pd3dDev);
	void render_block(LPDIRECT3DDEVICE9 g_pd3dDev, int block_type, int x, int y);

};

#endif