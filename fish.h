#pragma once

const int N=40;//��ͼ�����귶Χ1-N
const int M=40;//��ͼ�����귶Χ1-M
const int MAX_PLAYER=40;//������������ID��1-MAX_PLAYER
const int MAX_FOOD=50;//ˢ��ʳ������
const int MAX_ROUND=500;
const int FOOD_ROUND=5;//ˢ��ʳ��غ���
const int EMPTY=0;//����Ϊ��
const int FOOD=-1;//ʳ��
const int LEVEL_POINT=3;//�����ܻ�õĵ���

class env;

class fish{
private:
    bool cnx_haveMove,cnx_haveAttack;
    int cnx_ID,cnx_Point,cnx_p_x,cnx_p_y,cnx_Score;
    static int cnx_Player;
    static int cnx_map[N+3][M+3];
    static int cnx_Speed[MAX_PLAYER+3];
    static int cnx_Attack[MAX_PLAYER+3];
    static int cnx_HP[MAX_PLAYER+3];
    static int cnx_maxHP[MAX_PLAYER+3];
    static int cnx_Exp[MAX_PLAYER+3];
    static int cnx_Level[MAX_PLAYER+3];
    static int cnx_Death[2][MAX_PLAYER+3];
    static int cnx_pos[MAX_PLAYER+3];
    //void setID(int);//����ID��ֻ�ɱ�����һ��
public:
    friend class cnx_env;
    bool move(int,int);//�ƶ���ĳ��λ��
    bool attack(int,int);//����ĳ��λ��
    int getPoint();//���ص�ǰ���ʣ�����
    int getLevel();//���ص�ǰ��ҵȼ�
    int getExp();//���ص�ǰ��Ҿ���
    int getX();//���ص�ǰ��Һ�����
    int getY();//���ص�ǰ���������
    int getHP();//���ص�ǰ�������ֵ
    int getMaxHP();//���ص�ǰ�����������
    int getAtt();//���ص�ǰ��ҹ�����
    int getSp();//���ص�ǰ����ٶ�
    int getID();//��ȡ���ID
    int getTotalPlayer();
    int askWhat(int,int);//���ص�ͼĳ��λ�����ݣ����ID��FOOD��EMPTY��
    int askHP(int);//ѯ��ĳ�����ID��ǰѪ��
    bool increaseHealth();//����health����1
    bool increaseStrength();//����Strength����1
    bool increaseSpeed();//����Speed����1

    virtual void init()=0;//��ʼ��������ÿһ�����¿�ʼ������
    virtual void play()=0;//�ж�������ÿ�غ��ж�������
    virtual void revive(int&,int&)=0;//����ʱ���ã���������ѡ�񸴻�λ�ã������Ϸ��������
};

//�������������躯�������������豣֤����ÿ��������������ɵ���

//��Ҫʹ��ȫ�ֱ���!!!
