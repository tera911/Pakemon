#include "PrintPicture.h"


PrintPicure::PrintPicure(){
	LoadDivGraph( "testfonts.png" , 10 , 10 , 1 , WIDTH , HEIGHT , spritPicture ) ;
}

void PrintPicure::NumDraw( int Num )
{
	int i , BeamWidth , x ;

	// Num���\�i���ŉ����ɂȂ邩���ׂ�
	BeamWidth = 0 ;
	for( i = 10 ; Num >= i ; i *= 10 ) BeamWidth ++ ;

	// ��ʍ���ɃO���t�B�b�N�ŕ`��
	// x �͐����O���t�B�b�N��`����`�̍��[�̍��W�ł�
	x = BeamWidth * WIDTH ;	
	for( i = 0 ; i <= BeamWidth ; i ++ )
	{
		// �����̕`��(���ߐF����)
		// NumHandle �z��ɂ͗v�f�ԍ��O�ɂ́w�O�x�̃O���t�B�b�N���ʔԍ���
		// �P�ɂ́w�P�x�̃O���t�B�b�N���ʔԍ��������Ă���̂ŁA
		// DrawGraph( 0 , 0 , NumHandle[ 0 ] , TRUE ) ; �Ƃ����
		// �w�O�x�̃O���t�B�b�N��`��ł��邱�Ƃ����Y��Ȃ�
		DrawGraph( x , 0 , spritPicture[ Num % 10 ], TRUE ) ;

		// �`��w���W���ړ�
		x -= WIDTH ;

		// �P�ԉ��̌����`�悵�I������̂ňꌅ������
		Num /= 10 ;
	}
}