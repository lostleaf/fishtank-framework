#include "fish.h"
#include <cstdio>
#include <algorithm>
using namespace std;

int fish::cnx_Player;
int fish::cnx_pos[MAX_PLAYER+3];
int fish::cnx_map[N+3][M+3];
int fish::cnx_Speed[MAX_PLAYER+3];
int fish::cnx_Attack[MAX_PLAYER+3];
int fish::cnx_HP[MAX_PLAYER+3];
int fish::cnx_maxHP[MAX_PLAYER+3];
int fish::cnx_Exp[MAX_PLAYER+3];
int fish::cnx_Level[MAX_PLAYER+3];
int fish::cnx_Death[2][MAX_PLAYER+3];

bool inRange(int _x,int _y){
	if(_x<1||_x>N)return 0;
	if(_y<1||_y>M)return 0;
	return 1;
}

bool fish::move(int _x,int _y){
	if(!inRange(_x,_y))return 0;
	if(cnx_HP[cnx_ID]<1)return 0;
	if(cnx_map[_x][_y]!=EMPTY)return 0;
	if(abs(cnx_p_x-_x)+abs(cnx_p_y-_y)>cnx_Speed[cnx_ID])return 0;
	if(cnx_haveMove||cnx_haveAttack)return 0;
	else cnx_haveMove=1;
	cnx_map[cnx_p_x][cnx_p_y]=0;
	cnx_map[_x][_y]=cnx_ID;
	cnx_p_x=_x;
	cnx_p_y=_y;
	return 1;
}

int calcExp(int _Level){
	return (1+_Level)*_Level/2-1;
}

bool fish::attack(int _x,int _y){
    if(!inRange(_x,_y))return 0;
	if(cnx_map[_x][_y]==EMPTY)return 0;
	if(abs(cnx_p_x-_x)+abs(cnx_p_y-_y)!=1)return 0;
	if(cnx_Attack[cnx_ID]<1)return 0;
	if(cnx_HP[cnx_ID]<1)return 0;
	if(cnx_haveAttack)return 0;
	else cnx_haveAttack=1;
	if(cnx_map[_x][_y]==FOOD){
		cnx_map[_x][_y]=EMPTY;
		cnx_Exp[cnx_ID]+=1;
		cnx_HP[cnx_ID]=min(cnx_maxHP[cnx_ID],cnx_HP[cnx_ID]+max(2,cnx_maxHP[cnx_ID]/10));
		printf("%d eats food\n",cnx_pos[cnx_ID]);
	}
	else{
		int _ID=cnx_map[_x][_y];
		cnx_HP[_ID]=max(0,cnx_HP[_ID]-cnx_Attack[cnx_ID]);
		if(cnx_HP[_ID]<1){
			cnx_Death[0][++cnx_Death[0][0]]=_ID;
			cnx_Exp[cnx_ID]+=max(cnx_Level[_ID]/2,1);
			cnx_map[_x][_y]=EMPTY;
            if(cnx_Level[_ID]>cnx_Level[cnx_ID])
                cnx_Score+=2*(cnx_Level[_ID]-cnx_Level[cnx_ID]);
            printf("%d kills %d\n",cnx_pos[cnx_ID],cnx_pos[_ID]);
		}
		else printf("%d attacks %d\n",cnx_pos[cnx_ID],cnx_pos[_ID]);
	}
	while(cnx_Exp[cnx_ID]>=calcExp(cnx_Level[cnx_ID]+1)){
        ++cnx_Level[cnx_ID];
        cnx_Point+=3;
    }
	return 1;
}

int fish::getPoint(){
	return cnx_Point;
}

int fish::getLevel(){
	return cnx_Level[cnx_ID];
}

int fish::getExp(){
	return cnx_Exp[cnx_ID];
}

int fish::getX(){
	return cnx_p_x;
}

int fish::getY(){
	return cnx_p_y;
}

int fish::getHP(){
	return cnx_HP[cnx_ID];
}

int fish::getMaxHP(){
	return cnx_maxHP[cnx_ID];
}

int fish::getAtt(){
	return cnx_Attack[cnx_ID];
}

int fish::getSp(){
	return cnx_Speed[cnx_ID];
}

int fish::getID(){
	return cnx_ID;
}

int fish::getTotalPlayer(){
    return cnx_Player;
}

int fish::askWhat(int _x,int _y){
	if(!inRange(_x,_y))return EMPTY;
	if(cnx_HP[cnx_ID]<1)return EMPTY;
	return cnx_map[_x][_y];
}

int fish::askHP(int _ID){
    if(1>_ID||_ID>MAX_PLAYER)return 0;
	return cnx_HP[_ID];
}

bool fish::increaseHealth(){
	if(cnx_Point){
		--cnx_Point;
		cnx_HP[cnx_ID]+=2;
		cnx_maxHP[cnx_ID]+=2;
		return true;
	}
	else return false;
}

bool fish::increaseStrength(){
	if(cnx_Point){
		--cnx_Point;
		++cnx_Attack[cnx_ID];
		return true;
	}
	else return false;
}

bool fish::increaseSpeed(){
	if(cnx_Point){
		--cnx_Point;
		++cnx_Speed[cnx_ID];
		return true;
	}
	else return false;
}
