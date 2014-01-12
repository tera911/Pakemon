#include <DxLib.h>
#define SMALLWIDTH  7	// ¬‚³‚¢‰æ‘œ‚Ì‰¡•
#define SMALLHEIGHT 7	// ¬‚³‚¢‰æ‘œ‚Ì‚‚³
#define BIGWIDTH 14		//‘å‚«‚¢‰æ‘œ‚Ì‰¡•
#define BIGHEIGHT 14	//‘å‚«‚¢‰æ‘œ‚Ì‚‚³


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
