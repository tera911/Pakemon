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
	}
	void moveUp(){
		jump = true;
	}
	void moveDown(){
		nyan_y = nyan_y +  7;
	}
	void moveLeft(){
		nyan_x = nyan_x -  5;
	}
	void moveRight(){
		nyan_x = nyan_x +  5;
	}
	void grabity(){
		if(jump){
			nyan_y -= 40.0f;
			jump=false;
		}else if(nyan_y < 450){
			nyan_y += 5.5f;
		}
	}
private:
	int handle[6];
	float nyan_x;
	float nyan_y;
	bool jump;
	
};
#endif