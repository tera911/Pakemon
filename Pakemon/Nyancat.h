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
	bool fall;	//���R����
	float GA;	//�������x
	int sound[5];
	int voice;
	bool ground;
	
	
public:
	Nyancat(){
		LoadDivGraph("Nyan_s.png", 6, 6, 1, 32, 32, handle);
		nyan_x = 200;
		nyan_y = 0;
		top = 0;
		left = 0;
		right = 0;
		fall = true;
		GA = 0;
		
		
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
		nyan_y += GA ;
		
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
	void jump(){
		onFall();
		srand((unsigned) time(NULL));
		voice=rand();
		voice%=5;
		if(ground){
		top += 40.0f;
		}
		if(CheckSoundMem(sound[voice])==0) {
		PlaySoundMem(sound[voice],DX_PLAYTYPE_BACK);
		}
	}
	void moveDown(){
		nyan_y +=7;
	}
	void moveLeft(){
		left = 3;
	}
	void moveRight(){
		right = 3;
	}
	void grabity(){
		if(fall){
			GA  = 6.0f;
		}else{
			GA = 0 ;
		}
		
	}

	//���R�����J�n
	void onFall(){
		fall = true;
	}
	//���R�����I��
	void offFall(){
		fall = false;
	}
	//�ڒn����ON
	void onground(){
		ground=true;
	}
	//�ڒn����OFF
	void offground(){
		ground=false;
	}
	
	//�j����������X���W���擾
	float getNyanX(){
		return nyan_x;
	}
	//�j����������Y���W���擾
	float getNyanY(){
		return nyan_y;
	}

};
#endif