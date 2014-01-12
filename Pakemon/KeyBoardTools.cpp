#include "KeyBoardTools.h"
#include <DxLib.h>

int KeyBoardTools::GetHitKeyStateAll_2(int KeyStateBuf[]){
	char GetHitKeyStateAll_Key[256];
    GetHitKeyStateAll( GetHitKeyStateAll_Key );
    for(int i=0;i<256;i++){
            if(GetHitKeyStateAll_Key[i]==1) KeyStateBuf[i]++;
            else                            KeyStateBuf[i]=0;
    }
    return 0;
}