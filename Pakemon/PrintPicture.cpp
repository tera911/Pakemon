#include "PrintPicture.h"

PrintPicture::PrintPicture() {
		LoadDivGraph( "font_number01_oic.png" , 10 , 10 , 1 , SMALLWIDTH , SMALLHEIGHT , spritNo ) ;
		LoadDivGraph( "font_alphabet02_oic.png" , 26 , 26 , 1 , BIGWIDTH , BIGHEIGHT , spritString ) ;
	}

// ���l���O���t�B�b�N�\������֐�
  void  PrintPicture::NumDraw( int Num ,int argx,int argy )
{

	int i , Length , x = argx,y=argy ;

	// Num���\�i���ŉ����ɂȂ邩���ׂ�
	Length = 0 ;
	for( i = 10 ; Num >= i ; i *= 10 ) Length ++ ;

		
	for( i = 0 ; i <= Length ; i ++ )
	{
		
		DrawGraph( x , y , spritNo[ Num % 10 ], TRUE ) ;

		// �`��w���W���ړ�
		x -= SMALLWIDTH ;

		// �P�ԉ��̌����`�悵�I������̂ňꌅ������
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