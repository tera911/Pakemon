#include "PrintPicture.h"


PrintPicture::PrintPicture(){
	
	LoadDivGraph( "testfonts.png" , 10 , 10 , 1 , WIDTH , HEIGHT , spritPicture ) ;
}

// ���l���O���t�B�b�N�\������֐�

  void  PrintPicture::NumDraw( int Num ,int argx,int argy )
{

	int i , BeamWidth , x = argx,y=argy ;

	// Num���\�i���ŉ����ɂȂ邩���ׂ�
	BeamWidth = 0 ;
	for( i = 10 ; Num >= i ; i *= 10 ) BeamWidth ++ ;

		
	for( i = 0 ; i <= BeamWidth ; i ++ )
	{
		
		DrawGraph( x , y , spritPicture[ Num % 10 ], TRUE ) ;

		// �`��w���W���ړ�
		x -= WIDTH ;

		// �P�ԉ��̌����`�悵�I������̂ňꌅ������
		Num /= 10 ;
	}
}
