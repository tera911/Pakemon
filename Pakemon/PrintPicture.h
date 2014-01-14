#include <DxLib.h>


class PrintPicture{
private:
	int SmallSpritNo[10];
	int MediumSpritNo[10];
	int LargeSpritNo[10];
	
	int SmallSpritString[30];
	int MediumSpritString[30];
	int LargeSpritString[30];
	PrintPicture();
public: 
	static PrintPicture* instance(){
		static PrintPicture printPicture;
		return &printPicture;
	}

	

	void NumDraw(int num,int argx,int argy,int size);
	void StringDraw(char String[],int x,int y,int size);

};
