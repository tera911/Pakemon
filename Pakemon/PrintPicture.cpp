#include "PrintPicture.h"


PrintPicture::PrintPicture(){
	
	LoadDivGraph( "testfonts.png" , 10 , 10 , 1 , WIDTH , HEIGHT , spritPicture ) ;
}

// 数値をグラフィック表示する関数

  void  PrintPicture::NumDraw( int Num ,int argx,int argy )
{

	int i , BeamWidth , x = argx,y=argy ;

	// Numが十進数で何桁になるか調べる
	BeamWidth = 0 ;
	for( i = 10 ; Num >= i ; i *= 10 ) BeamWidth ++ ;

		
	for( i = 0 ; i <= BeamWidth ; i ++ )
	{
		
		DrawGraph( x , y , spritPicture[ Num % 10 ], TRUE ) ;

		// 描画Ｘ座標を移動
		x -= WIDTH ;

		// １番下の桁が描画し終わったので一桁下げる
		Num /= 10 ;
	}
}
