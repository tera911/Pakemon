#include "PrintPicture.h"

PrintPicture::PrintPicture() {
		LoadDivGraph( "font_number01_oic.png" , 10 , 10 , 1 , SMALLWIDTH , SMALLHEIGHT , spritNo ) ;
		LoadDivGraph( "font_alphabet02_oic.png" , 26 , 26 , 1 , BIGWIDTH , BIGHEIGHT , spritString ) ;
	}

// 数値をグラフィック表示する関数
  void  PrintPicture::NumDraw( int Num ,int argx,int argy )
{

	int i , Length , x = argx,y=argy ;

	// Numが十進数で何桁になるか調べる
	Length = 0 ;
	for( i = 10 ; Num >= i ; i *= 10 ) Length ++ ;

		
	for( i = 0 ; i <= Length ; i ++ )
	{
		
		DrawGraph( x , y , spritNo[ Num % 10 ], TRUE ) ;

		// 描画Ｘ座標を移動
		x -= SMALLWIDTH ;

		// １番下の桁が描画し終わったので一桁下げる
		Num /= 10 ;
	}
}
  void PrintPicture::StringDraw(char String[],int x,int y){
	int i,Length;
	for(Length=0;String[Length];Length++);
	 for(i= 0;i<Length;i++){
	 if('A'<=String[i]&&String[i]<='Z'){
   DrawGraph( i*BIGWIDTH + x , y , spritString[String[i]-'A' ], TRUE ) ;
		}
	 }
  }