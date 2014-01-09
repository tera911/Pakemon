#include <DxLib.h>
#define WIDTH  7	// 数字グラフィック横幅
#define HEIGHT 7	// 数字グラフィック高さ

class PrintPicure{
private:
	int spritPicture[8];


public:
	PrintPicure();
	void NumDraw(int num);
}