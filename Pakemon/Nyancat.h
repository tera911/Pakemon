#ifndef __NYANCAT_
#define __NYANCAT_
#include <DxLib.h>


class Nyancat{
private:
	int handle[6];
	float nyan_x;
	float nyan_y;
	float top;
	float left;
	float right;
	bool jump;
	float GA;
	
public:
	Nyancat(){
		LoadDivGraph("Nyan_s.png", 6, 6, 1, 32, 32, handle);
		nyan_x = 200;
		nyan_y = 0;
		top = 0;
		left = 0;
		right = 0;
		jump = false;
		
	}

	void render(){
		DrawGraph(nyan_x, nyan_y, handle[3], true);
		nyan_x -= left;
		nyan_x += right;
		nyan_y -= top;
		grabity();
		nyan_y -= GA ;
		
		if(left > 0){
			left -= 0.5;
		}
		if(right > 0){
			right -= 0.5;
		}
		if(top > 0){
			top -= 20.0f;
		}
	}
	void moveUp(){
		top += 20.0f;
	}
	void moveDown(){
		nyan_y +=7;
	}
	void moveLeft(){
		left = 5;
	}
	void moveRight(){
		right = 5;
	}
	void grabity(){
		GA-=0.5
			;
		if( nyan_y > 500 )
		{
			nyan_y = 500 ;
			GA = 0 ;
		}

		
		
	}

};
#endif