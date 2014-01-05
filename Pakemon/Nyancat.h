#ifndef __NYANCAT_
#define __NYANCAT_
#include <DxLib.h>
#include <iostream>
#include <time.h>


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
	int sound[5];
	int voice;
	
	
public:
	Nyancat(){
		LoadDivGraph("Nyan_s.png", 6, 6, 1, 32, 32, handle);
		nyan_x = 200;
		nyan_y = 0;
		top = 0;
		left = 0;
		right = 0;
		jump = false;
		
		sound[0]=LoadSoundMem( "nyanVoice\\nyan01.wav" ) ;
		sound[1]=LoadSoundMem( "nyanVoice\\nyan02.wav" ) ;
		sound[2]=LoadSoundMem( "nyanVoice\\nyan03.wav" ) ;
		sound[3]=LoadSoundMem( "nyanVoice\\nyan04.wav" ) ;
		sound[4]=LoadSoundMem( "nyanVoice\\nyan05.wav" ) ;
		sound[5]=LoadSoundMem( "nyanVoice\\nyan06.wav" ) ;

		
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
		srand((unsigned) time(NULL));
		voice=rand();
		voice%=5;
		top += 20.0f;
		if(CheckSoundMem(sound[voice])==0) 
		PlaySoundMem(sound[voice],DX_PLAYTYPE_BACK);
		 
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