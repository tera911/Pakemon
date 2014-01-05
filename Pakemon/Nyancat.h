#ifndef __NYANCAT_
#define __NYANCAT_
#include <DxLib.h>


class Nyancat{
public:
	Nyancat(){
		LoadDivGraph("Nyan_s.png", 6, 6, 1, 32, 32, handle);
		nyan_x = 0;
		nyan_y = 0;
		jump = false;
		
	}

	void render(){
		DrawGraph(nyan_x, nyan_y, handle[3], true);
		grabity();
		nyan_y -= GA ;
	}
	void moveUp(){
		
		nyan_y -=10;
	}
	void moveDown(){
		nyan_y +=7;
	}
	void moveLeft(){
		nyan_x -=5;
	}
	void moveRight(){
		nyan_x +=5;
	}
	void grabity(){
		GA-=1;
		if( nyan_y > 500 )
		{
			nyan_y = 500 ;
			GA = 0 ;
		}

		
		
	}
private:
	int handle[6];
	float nyan_x;
	float nyan_y;
	bool jump;
	float GA;
	
};
#endif