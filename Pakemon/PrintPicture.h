#include <DxLib.h>
#define WIDTH  7	// �����O���t�B�b�N����
#define HEIGHT 7	// �����O���t�B�b�N����

class PrintPicture{
private:
	int spritPicture[10];
	static PrintPicture *instance;
	PrintPicture();
public: 
	static PrintPicture* instance(){
		static PrintPicture printPicture;
		return &printPicture;
	}
	void NumDraw(int num,int argx,int argy);
};