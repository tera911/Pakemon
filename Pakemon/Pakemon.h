#include <DxLib.h>
#include "Fps.h"
#include <stdlib.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Packet.lib")
#pragma comment(lib, "wpcap.lib")
#pragma comment(lib, "ws2_32.lib")

#define SCREEN_WIDTH	(800)	//�X�N���[���̉���
#define SCREEN_HEIGHT	(600)	//�X�N���[���̏c��
#define CHIP_SIZE		(32)	//��̃`�b�v�̃T�C�Y
#define MAP_WIDTH		(46)
#define	MAP_HEIGHT		(18)

int WINAPI Game(  );