#include "GameMap.h"
#include "headall.h"
#include <stdio.h>


// 頂点フォーマット
#define	FVF_TLVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1)

typedef struct _tlvertex{	// 上記頂点フォーマットに合わせた構造体を定義
	float x,y,z;
	float rhw;
	D3DCOLOR diffuse;
	D3DCOLOR specular;
	float tu,tv;
}TLVERTEX;

GameMap::GameMap(LPDIRECT3DDEVICE9 g_pd3dDev){
	::AllocConsole();
	freopen("CON", "r", stdin);
	freopen("CON", "w", stdout);
	int x,y;
	for(x = 0; x < 46; x++){
		for(y = 0; y < 18; y++){
			if( y < 18 && y > 15){
				map[x][y] = 1;
			//	printf("map[%d][%d] = %d\n", i, j, map[i][j]);
			}else{
				map[x][y] = 0;
			}
			
		}
	}
	D3DXCreateTextureFromFileA(g_pd3dDev, "block/brick.png", &block_brick);
	D3DXCreateTextureFromFileA(g_pd3dDev, "block/hatena.png", &block_hatena);
	D3DXCreateTextureFromFileA(g_pd3dDev, "block/normal.png", &block_normal);
	D3DXCreateTextureFromFileA(g_pd3dDev, "block/packet.png", &block_packet);
	D3DXCreateTextureFromFileA(g_pd3dDev, "block/ware.png", &block_ware);
}

void GameMap::render(LPDIRECT3DDEVICE9 g_pd3dDev){
	int i, j;
	for(i = 0; i < 46; i++){
		for(j = 0; j < 18; j++){
			render_block(g_pd3dDev, map[i][j], i, j);		
		}
	}
}

void GameMap::render_block(LPDIRECT3DDEVICE9 g_pd3dDev, int block_type, int x, int y){
	if(block_type == 0){
		return;
	}
	int block_x, block_y;
	block_x =  x * 32;
	block_y  = y * 32;
	TLVERTEX vertex[4];
	g_pd3dDev->SetFVF(FVF_TLVERTEX);
	switch(block_type){
		case 1:
			g_pd3dDev->SetTexture(0, block_brick);
		break;
		case 2:
			g_pd3dDev->SetTexture(0, block_ware);
		break;
		case 3:
			g_pd3dDev->SetTexture(0, block_hatena);
		break;
		case 4:
			g_pd3dDev->SetTexture(0, block_packet);
		break;
	}
	
	vertex[0].rhw = vertex[1].rhw = vertex[2].rhw = vertex[3].rhw = 1.0f;
	vertex[0].diffuse = D3DCOLOR_RGBA(255,255,255,255); //各頂点（左上）の色
	vertex[1].diffuse = D3DCOLOR_RGBA(255,255,255,255); //各頂点（右上）の色
	vertex[2].diffuse = D3DCOLOR_RGBA(255,255,255,255); 
	vertex[3].diffuse = D3DCOLOR_RGBA(255,255,255,255); 
	vertex[0].specular = vertex[1].specular = vertex[2].specular = vertex[3].specular = D3DCOLOR_XRGB(0,0,0); //Specular スポットライト
	
	vertex[0].x = 0.0f  + block_x;		vertex[0].y = 0.0f  + block_y;	vertex[0].z = 0.0f;		// １頂点のスクリーン座標
	vertex[1].x = 32.0f + block_x;		vertex[1].y = 0.0f  + block_y;	vertex[1].z = 0.0f;		// ２頂点のスクリーン座標
	vertex[2].x = 0.0f  + block_x;		vertex[2].y = 32.0f + block_y;	vertex[2].z = 0.0f;		// ３頂点のスクリーン座標
	vertex[3].x = 32.0f + block_x;		vertex[3].y = 32.0f + block_y;	vertex[3].z = 0.0f;

	vertex[0].tu = 0.0f;		vertex[0].tv = 0.0f;
	vertex[1].tu = 1.0f;		vertex[1].tv = 0.0f;
	vertex[2].tu = 0.0f;		vertex[2].tv = 1.0f;
	vertex[3].tu = 1.0f;		vertex[3].tv = 1.0f;

	g_pd3dDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(TLVERTEX));
}