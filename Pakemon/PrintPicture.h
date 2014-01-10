#include <DxLib.h>
#define WIDTH  7	// 数字グラフィック横幅
#define HEIGHT 7	// 数字グラフィック高さ

class PrintPicture{
private:
	static int spritPicture[10];



public: 
	PrintPicture();
	 static void NumDraw(int num,int argx,int argy);
};