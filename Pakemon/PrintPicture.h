#include <DxLib.h>
#define WIDTH  7	// �����O���t�B�b�N����
#define HEIGHT 7	// �����O���t�B�b�N����

class PrintPicture{
private:
	int spritPicture[10];
	PrintPicture() {
		LoadDivGraph( "testfonts.png" , 10 , 10 , 1 , WIDTH , HEIGHT , spritPicture ) ;
	}
public: 
	static PrintPicture* instance(){
		static PrintPicture printPicture;
		return &printPicture;
	}
	void NumDraw(int num,int argx,int argy);
};