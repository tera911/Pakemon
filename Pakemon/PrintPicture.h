#include <DxLib.h>
#define SMALLWIDTH  7	// �������摜�̉���
#define SMALLHEIGHT 7	// �������摜�̍���
#define BIGWIDTH 14		//�傫���摜�̉���
#define BIGHEIGHT 14	//�傫���摜�̍���


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
