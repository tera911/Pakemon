#include "PrintPicture.h"


PrintPicure::PrintPicure(){
	LoadDivGraph( "testfonts.png" , 10 , 10 , 1 , WIDTH , HEIGHT , spritPicture ) ;
}

void PrintPicure::NumDraw( int Num )
{
	int i , BeamWidth , x ;

	// Numが十進数で何桁になるか調べる
	BeamWidth = 0 ;
	for( i = 10 ; Num >= i ; i *= 10 ) BeamWidth ++ ;

	// 画面左上にグラフィックで描画
	// x は数字グラフィックを描く矩形の左端の座標です
	x = BeamWidth * WIDTH ;	
	for( i = 0 ; i <= BeamWidth ; i ++ )
	{
		// 数字の描画(透過色あり)
		// NumHandle 配列には要素番号０には『０』のグラフィック識別番号が
		// １には『１』のグラフィック識別番号が入っているので、
		// DrawGraph( 0 , 0 , NumHandle[ 0 ] , TRUE ) ; とすれば
		// 『０』のグラフィックを描画できることをお忘れなく
		DrawGraph( x , 0 , spritPicture[ Num % 10 ], TRUE ) ;

		// 描画Ｘ座標を移動
		x -= WIDTH ;

		// １番下の桁が描画し終わったので一桁下げる
		Num /= 10 ;
	}
}