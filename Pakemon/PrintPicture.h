#include <DxLib.h>
#define SMALLWIDTH  7	// 小さい画像の横幅
#define SMALLHEIGHT 7	// 小さい画像の高さ
#define BIGWIDTH 14		//大きい画像の横幅
#define BIGHEIGHT 14	//大きい画像の高さ


class PrintPicture{
private:
	int spritNo[10];
	int spritString[26];
	PrintPicture();
public: 
	static PrintPicture* instance(){
		static PrintPicture printPicture;
		return &printPicture;
	}
	void NumDraw(int num,int argx,int argy);
	void StringDraw(char String[],int x,int y);
};
