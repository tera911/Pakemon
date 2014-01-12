#include "PrintPicture.h"
#define SMALLWIDTH  7	//小さい画像の横幅
#define SMALLHEIGHT 7	//小さい画像の高さ
#define MEDIUMWIDTH 14	//中ぐらい画像の横幅
#define MEDIUMHEIGHT 14	//中ぐらい画像の高さ
#define LARGEWIDTH 28	//大きい画像の横幅
#define LARGEHEIGHT 28	//大きい画像の高さ
PrintPicture::PrintPicture() {
		LoadDivGraph( "font_number01_oic.png" , 10 , 10 , 1 , SMALLWIDTH , SMALLHEIGHT , SmallSpritNo );
		LoadDivGraph( "font_number02_oic.png" , 10 , 10 , 1 , MEDIUMWIDTH , MEDIUMHEIGHT , MediumSpritNo ) ;
		LoadDivGraph( "font_number03_oic.png" , 10 , 10 , 1 , LARGEWIDTH , LARGEHEIGHT , LargeSpritNo ) ;
		LoadDivGraph( "font_alphabet01_oic.png" , 26 , 26 , 1 , SMALLHEIGHT , SMALLHEIGHT , SmallSpritString );
		LoadDivGraph( "font_alphabet02_oic.png" , 26 , 26 , 1 , MEDIUMWIDTH , MEDIUMHEIGHT , MediumSpritString );
		LoadDivGraph( "font_alphabet03_oic.png" , 26 , 26 , 1 , LARGEWIDTH , LARGEHEIGHT , LargeSpritString );
	}

// 数値をグラフィック表示する関数
  void  PrintPicture::NumDraw( int Num ,int argx,int argy,int size )
{

	int i , Length , x = argx,y=argy ;
	Length = 0 ;
	switch (size)
	{
	case 1:
		for(i=10;Num>=i;i*=10)Length ++ ;	
			for(i=0;i<=Length;i++)
				{
					DrawGraph( x , y , SmallSpritNo[ Num % 10 ], TRUE ) ;
						x -= SMALLWIDTH ;
					Num /= 10 ;
				}
			break;
	case 2:
		for(i=10;Num>=i;i*=10)Length ++ ;	
			for(i=0;i<=Length;i++)
				{
					DrawGraph( x , y , MediumSpritNo[ Num % 10 ], TRUE ) ;
						x -= MEDIUMWIDTH ;
					Num /= 10 ;
				}
			break;
	case 3:
		for(i=10;Num>=i;i*=10)Length ++ ;	
			for(i=0;i<=Length;i++)
				{
					DrawGraph( x , y , LargeSpritNo[ Num % 10 ], TRUE ) ;
						x -= LARGEWIDTH ;
					Num /= 10 ;
				}
			break;
	}
	
}
  
  void PrintPicture::StringDraw(char String[],int x,int y,int size){
	int i,Length;
	switch (size)
	{
	case 1:
		for(Length=0;String[Length];Length++);
		for(i= 0;i<Length;i++){
		if('A'<=String[i]&&String[i]<='Z'){
			DrawGraph( i*SMALLWIDTH + x , y , SmallSpritString[String[i]-'A' ], TRUE ) ;
			}
		}
		break;
	case 2:
		for(Length=0;String[Length];Length++);
		for(i= 0;i<Length;i++){
		if('A'<=String[i]&&String[i]<='Z'){
			DrawGraph( i*MEDIUMWIDTH + x , y , MediumSpritString[String[i]-'A' ], TRUE ) ;
			}
		}
		break;
	case 3:
		for(Length=0;String[Length];Length++);
		for(i= 0;i<Length;i++){
		if('A'<=String[i]&&String[i]<='Z'){
			DrawGraph( i*LARGEWIDTH + x , y , LargeSpritString[String[i]-'A' ], TRUE ) ;
			}
		}
		break;
	}
	
  }