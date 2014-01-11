#include "DxLib.h"
#include "Pakemon.h"

int GetHitKeyStateAll_2(int KeyStateBuf[]){
        char GetHitKeyStateAll_Key[256];
        GetHitKeyStateAll( GetHitKeyStateAll_Key );
        for(int i=0;i<256;i++){
                if(GetHitKeyStateAll_Key[i]==1) KeyStateBuf[i]++;
                else                            KeyStateBuf[i]=0;
        }
        return 0;
}

void disp(int White,int y){
        DrawString( 300 , y   , "→"    , White );
        DrawString( 330 , 420 , "START" , White );
        DrawString( 330 , 440 , "OPTION" , White );
        DrawString( 330 , 460 , "EXIT"   , White );
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
				LPSTR lpCmdLine, int nCmdShow ){
	int White , y=420;  
	int Key[256];
	White=GetColor( 255 , 255 , 255 ) ; 
	SetGraphMode(800, 600, 32, 60);
	ChangeWindowMode(true);
	SetMainWindowText("Pakemon");
	SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面にする
	SetBackgroundColor(15,77,143);

	
	if( DxLib_Init() == -1 )	// ＤＸライブラリ初期化処理
	{
		 return -1;				// エラーが起きたら直ちに終了
	}
	while(ProcessMessage()==0 &&GetHitKeyStateAll_2(Key)==0 && ClearDrawScreen()==0&&Key[KEY_INPUT_ESCAPE]==0){
		disp(White,y);

			if( Key[KEY_INPUT_DOWN]==1 ||( Key[KEY_INPUT_DOWN]%5==0 && Key[KEY_INPUT_DOWN]>30)){
			 
            y+=20;   
			if(y==480){
			y=420;
			}
        }
			if( Key[KEY_INPUT_UP]==1 ||( Key[KEY_INPUT_UP]%5==0 && Key[KEY_INPUT_UP]>30)){
			
            y-=20;
			if(y==400){
			y=460;
			}	
        }
			switch (y){
			case 420:
				//If文でゲーム開始処理
				if(Key[KEY_INPUT_RETURN]){
				Game();
				}
				break;
			case 440:
				//If文でオプション開始処理
				break;
			case 460:
				//ゲーム終了処理
				if(Key[KEY_INPUT_RETURN]){
				return -1;
				}
				break;
			default:
				break;
			}

			ScreenFlip();//裏画面反映
			
	}
}

