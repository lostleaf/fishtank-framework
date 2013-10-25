#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <ctime>
#include <cstring>
#include <windows.h>
#include "fish.h"
#include "player.h"
#include "st01.h"
#include "st02.h"
#include "st04.h"
#include "st05.h"
#include "st06.h"
#include "st08.h"
#include "st10.h"
#include "st11.h"
#include "st12.h"
#include "st14.h"
#include "st15.h"
#include "st16.h"
#include "st17.h"
#include "st19.h"
#include "st20.h"
#include "st21.h"
#include "st22.h"
#include "st23.h"
#include "st24.h"
#include "st25.h"
#include "st26.h"
#include "st27.h"
#include "st28.h"
#include "st29.h"
#include "st30.h"
#include "st31.h"
#include "st32.h"
#include "st34.h"
#include "st35.h"
#include "st36.h"
#include "st39.h"
#include "st40.h"
#include "st41.h"
#include "st42.h"
#include "st43.h"
#include "st07.h"
#include "fishsk.h"
#include "czp.h"

using namespace std;

fish *yu[MAX_PLAYER+3],*now;
const int ROUND=500;
int ran[MAX_PLAYER+3];
int rankround[11];

class watcher:public fish{
    void init(){}
    void play(){}
    void revive(int &x,int &y){}
};

class cnx_env{
    public:
    bool inRange(int _x,int _y){
        if(_x<1||_x>N)return 0;
        if(_y<1||_y>M)return 0;
        return 1;
    }
    void getrand(fish *r,int &x,int &y){
        for(;;){
            x=rand()%N+1;
            y=rand()%M+1;
            if(r->cnx_map[x][y]==EMPTY)return;
        }
    }

    void fresh(fish *r){
        for(int i=1;i<=N;++i)
            for(int j=1;j<=M;++j)
                if(r->cnx_map[i][j]==FOOD)
                    r->cnx_map[i][j]=EMPTY;
        for(int i=1;i<=MAX_FOOD;++i){
            int x,y;
            getrand(r,x,y);
            r->cnx_map[x][y]=FOOD;
        }
    }

    struct cmp{
        bool operator () (fish *x,fish *y){
            if(x->cnx_Speed[x->cnx_ID]!=y->cnx_Speed[y->cnx_ID])return x->cnx_Speed[x->cnx_ID]>y->cnx_Speed[y->cnx_ID];
            if(yu[0]->cnx_HP[x->cnx_ID]*yu[0]->cnx_maxHP[y->cnx_ID]!=yu[0]->cnx_maxHP[x->cnx_ID]*yu[0]->cnx_HP[y->cnx_ID])
                return yu[0]->cnx_HP[x->cnx_ID]*yu[0]->cnx_maxHP[y->cnx_ID]>yu[0]->cnx_maxHP[x->cnx_ID]*yu[0]->cnx_HP[y->cnx_ID];
            if(x->cnx_Score+x->cnx_Exp[x->cnx_ID]!=y->cnx_Score+y->cnx_Exp[y->cnx_ID])
                return x->cnx_Score+x->cnx_Exp[x->cnx_ID]<y->cnx_Score+y->cnx_Exp[y->cnx_ID];
            return x->cnx_ID<y->cnx_ID;
        }
    };

    struct cmp2{
        bool operator () (fish *x,fish *y){
            return x->cnx_Score+x->cnx_Exp[x->cnx_ID]>y->cnx_Score+y->cnx_Exp[y->cnx_ID];
        }
    };

    void init(int n){
        yu[0]->cnx_Player=n;
        for(int i=1;i<=N;++i)
            for(int j=1;j<=M;++j)
                yu[0]->cnx_map[i][j]=EMPTY;
        for(int i=1;i<=n;++i)ran[i]=i;
        for(int i=1;i<=n;++i){
            int x=rand()%n+1;
            swap(ran[x],ran[i]);
        }
        for(int i=1;i<=n;++i)
            yu[0]->cnx_pos[ran[i]]=i;
        yu[1]=new st02();yu[1]->cnx_ID=ran[1];
        yu[2]=new st04();yu[2]->cnx_ID=ran[2];
        yu[3]=new st05();yu[3]->cnx_ID=ran[3];
        yu[4]=new st06();yu[4]->cnx_ID=ran[4];
        yu[5]=new st08();yu[5]->cnx_ID=ran[5];
        yu[6]=new st10();yu[6]->cnx_ID=ran[6];
        yu[7]=new st11();yu[7]->cnx_ID=ran[7];
        yu[8]=new st12();yu[8]->cnx_ID=ran[8];
        yu[9]=new st14();yu[9]->cnx_ID=ran[9];
        yu[10]=new st15();yu[10]->cnx_ID=ran[10];
        yu[11]=new st16();yu[11]->cnx_ID=ran[11];
        yu[12]=new st17();yu[12]->cnx_ID=ran[12];
        yu[13]=new st19();yu[13]->cnx_ID=ran[13];
        yu[14]=new st20();yu[14]->cnx_ID=ran[14];
        yu[15]=new st21();yu[15]->cnx_ID=ran[15];
        yu[16]=new st22();yu[16]->cnx_ID=ran[16];
        yu[17]=new st23();yu[17]->cnx_ID=ran[17];
        yu[18]=new st26();yu[18]->cnx_ID=ran[18];
        yu[19]=new st27();yu[19]->cnx_ID=ran[19];
        yu[20]=new st28();yu[20]->cnx_ID=ran[20];
        yu[21]=new st29();yu[21]->cnx_ID=ran[21];
        yu[22]=new st30();yu[22]->cnx_ID=ran[22];
        yu[23]=new st31();yu[23]->cnx_ID=ran[23];
        yu[24]=new st32();yu[24]->cnx_ID=ran[24];
        yu[25]=new st34();yu[25]->cnx_ID=ran[25];
        yu[26]=new st35();yu[26]->cnx_ID=ran[26];
        yu[27]=new st36();yu[27]->cnx_ID=ran[27];
        yu[28]=new st39();yu[28]->cnx_ID=ran[28];
        yu[29]=new st25();yu[29]->cnx_ID=ran[29];
        yu[30]=new st01();yu[30]->cnx_ID=ran[30];
        yu[31]=new st40();yu[31]->cnx_ID=ran[31];
        yu[32]=new st41();yu[32]->cnx_ID=ran[32];
        yu[33]=new st42();yu[33]->cnx_ID=ran[33];
        yu[34]=new st43();yu[34]->cnx_ID=ran[34];
        yu[35]=new st24();yu[35]->cnx_ID=ran[35];
        yu[36]=new st07();yu[36]->cnx_ID=ran[36];
        yu[37]=new fishsk();yu[37]->cnx_ID=ran[37];
        yu[38]=new fishczp();yu[38]->cnx_ID=ran[38];
        for(int i=1;i<=n;++i){
            yu[0]->cnx_Speed[i]=0;
            yu[0]->cnx_Attack[i]=0;
            yu[0]->cnx_HP[i]=0;
            yu[0]->cnx_maxHP[i]=0;
            yu[0]->cnx_Exp[i]=0;
        }
        for(int i=1;i<=n;++i){
            yu[i]->cnx_Point=10;
            yu[0]->cnx_Level[yu[i]->cnx_ID]=1;
            yu[i]->cnx_Score=0;
            int x,y;
            getrand(yu[0],x,y);
            yu[i]->cnx_p_x=x;
            yu[i]->cnx_p_y=y;
            yu[0]->cnx_map[x][y]=yu[i]->cnx_ID;
            yu[i]->cnx_haveAttack=yu[i]->cnx_haveMove=1;
        }
        for(int i=1;i<=n;++i)
            yu[i]->init();
    }

    static DWORD WINAPI Thread_fish(LPVOID pM){
        try{
            now->play();
        }
        catch(...){
            printf("%d crashed\n",now->cnx_ID);
        }
    }

    void work(int n){
        init(n);

        yu[0]->cnx_Death[0][0]=yu[0]->cnx_Death[1][0]=0;
        for(int cas=1;cas<=ROUND;++cas){
            printf("Round %d:\n",cas);
            if(cas%FOOD_ROUND==1)fresh(yu[0]);
            for(int i=1;i<=yu[0]->cnx_Death[1][0];++i){
                int _id=yu[0]->cnx_Death[1][i];
                for(int l=1;l<=n;++l)
                    if(yu[l]->cnx_ID==_id){
                        int x,y;
                        yu[l]->revive(x,y);
                        if(!inRange(x,y)||yu[0]->cnx_map[x][y]!=EMPTY)getrand(yu[0],x,y);
                        yu[l]->cnx_p_x=x;
                        yu[l]->cnx_p_y=y;
                        yu[0]->cnx_map[x][y]=_id;
                        yu[l]->cnx_HP[yu[l]->cnx_ID]=max(yu[0]->cnx_maxHP[_id]/10,1);
                        break;
                    }
            }

            for(int i=0;i<=yu[0]->cnx_Death[0][0];++i)
                yu[0]->cnx_Death[1][i]=yu[0]->cnx_Death[0][i];
            yu[0]->cnx_Death[0][0]=0;

            sort(yu+1,yu+n+1,cmp());

            for(int i=1;i<=n;++i)
                if(yu[0]->cnx_HP[yu[i]->cnx_ID]>0){
                    yu[i]->cnx_haveAttack=yu[i]->cnx_haveMove=0;
                    //printf("%d\n",yu[0]->cnx_pos[yu[i]->cnx_ID]);
                    /*now=yu[i];
                    HANDLE pro=CreateThread(NULL,0,Thread_fish,NULL,0,NULL);
                    if(WaitForSingleObject(pro,2000)==WAIT_TIMEOUT)
                        printf("%d Time out\n",yu[0]->cnx_pos[yu[i]->cnx_ID]);
                    */
                    yu[i]->play();
                }
            if(cas==rankround[1]||cas==rankround[2]||cas==rankround[3]||cas==500){
                sort(yu+1,yu+n+1,cmp2());
                printf("No      Name    Level    HP      maxHP    Att     Sp      Exp     Bonus\n");
                for(int i=1;i<=n;++i)
                    printf("%4d    %4d    %4d     %4d    %4d     %4d    %4d    %4d    %4d\n",i,yu[0]->cnx_pos[yu[i]->cnx_ID],yu[0]->cnx_Level[yu[i]->cnx_ID],yu[0]->cnx_HP[yu[i]->cnx_ID],yu[0]->cnx_maxHP[yu[i]->cnx_ID],yu[0]->cnx_Attack[yu[i]->cnx_ID],yu[0]->cnx_Speed[yu[i]->cnx_ID],yu[0]->cnx_Exp[yu[i]->cnx_ID],yu[i]->cnx_Score);
            }
        }
    }
};

int main(){
    char outfile[11];
    srand(unsigned(time(0)));
    rankround[1]=rand()%(ROUND-50)+51;
    rankround[2]=rand()%(ROUND-50)+51;
    rankround[3]=rand()%(ROUND-50)+51;
    /*
    for(int tmp=11;tmp<=12;++tmp){
        sprintf(outfile,"%d.out",tmp);
        freopen(outfile,"w",stdout);*/
        cnx_env cnx;
        yu[0]=new watcher();
        cnx.work(38);/*
        printf("\a");
    }*/
    //system("shutdown -s -f -t 0");
    return 0;
}
