#include <DxLib.h>
#define WIDTH  7	// 数字グラフィック横幅
#define HEIGHT 7	// 数字グラフィック高さ

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