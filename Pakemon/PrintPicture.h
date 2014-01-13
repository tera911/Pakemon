#include <DxLib.h>


class PrintPicture{
private:
	int SmallSpritNo[10];
	int MediumSpritNo[10];
	int LargeSpritNo[10];
	
	int SmallSpritString[27];
	int MediumSpritString[27];
	int LargeSpritString[27];
	PrintPicture();
public: 
	static PrintPicture* instance(){
		static PrintPicture printPicture;
		return &printPicture;
	}

	/*void SmallNumDraw(int num,int argx,int argy);
	void MediumNumDraw(int num,int argx,int argy);
	void LargeNumDraw(int num,int argx,int argy);
	void SmallStringDraw(char String[],int x,int y);
	void MediumStringDraw(char String[],int x,int y);*/

	void NumDraw(int num,int argx,int argy,int size);
	void StringDraw(char String[],int x,int y,int size);

};
