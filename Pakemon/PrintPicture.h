#include <DxLib.h>


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
