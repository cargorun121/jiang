#include<conio.h>  
#include<graphics.h>
#include<stdio.h>
#include<time.h>
#include<mmsystem.h>
#include"resource.h"
#include<stdlib.h>
#pragma comment(lib,"winmm.lib")
constexpr auto BLOCK_SIZE = 20;//ÿ�����Դ�С;
constexpr auto HEIGHT = 30;//�߶�Ϊ30;
constexpr auto WIDTH = 40;//���Ϊ40;
int Blocks[30][40] = { 0 };//��ʼ������
int direction = 0;//����
int max=3;//��󳤶ȣ���ʼΪ3
int score = 0;
//ȫ�ֱ���
void startup()//��ʼ��
{
    initgraph((HEIGHT+5) * BLOCK_SIZE, WIDTH * BLOCK_SIZE);//30*40ͼ��
    Blocks[20][20] = 1;//��ͷ��
    for (int i = 1; i <= max; i++)
    {
        Blocks[20][20 - i] = i + 1;//�γ�����
    }
}
void food()//ˢ��ʳ��
{
    int a,b;
    a = rand() % 30;
    b = rand() % 40;
    Blocks[a][b] = -1;//ʳ����
}
void start()//��ɫ
{
    for (int m = 0; m < HEIGHT; m++) //��������
    {
        for (int n = 0; n < WIDTH; n++) 
        {
            if (Blocks[m][n] != 0 && Blocks[m][n] != -1)//ѡ���������a
            {
                //������ֵȷ����ɫ
                setfillcolor(RGB(0, 255, 0));
            }
            else if (Blocks[m][n] != 0)
                setfillcolor(RGB(255, 0, 0));//��ɫ��ʵ
            else
                setfillcolor(RGB(0, 0, 0));//��ɫ����
            //��ɫ��С
                fillrectangle(m * BLOCK_SIZE, n * BLOCK_SIZE, (m+1)* BLOCK_SIZE, (n + 1) * BLOCK_SIZE);
        }
    }
    FlushBatchDraw();
}
void movesnake() //�ƶ�����
{
    int m, n, b1, b2, p1, p2,c;
    p1 = 0, p2 = 0, b1 = 0, b2 = 0,c=0;
    for ( m = 0; m < HEIGHT; m++) //��������
    {
        for ( n = 0; n < WIDTH; n++)
        {
            if (Blocks[m][n] != 0 && Blocks[m][n] != -1)
            {
                Blocks[m][n]++;
            }
            else if (Blocks[m][n] == -1)
            {
                c++;//��¼��ʵ����
            }
        }
    }
    for ( m = 0; m < HEIGHT; m++) //��������
    {
        for ( n = 0; n < WIDTH; n++)
        {
            b1 = (n + 1) % 40;//��
            b2= (n +39) % 40; //��
            p1 = (m + 1) % 30;//��
            p2 = (m +29) % 30;//��
            if (Blocks[m][n] == 2)
            {
                if (direction==1)
                    Blocks[m][b1] = 1;
                else if (direction == 2)
                    Blocks[m][b2] = 1;
                else if (direction == 3)
                    Blocks[p1][n] = 1;
                else if (direction == 4)
                    Blocks[p2][n] = 1;
                else if(direction == 0)
                    Blocks[m][b1] = 1;
            }
            if (Blocks[m][n] > max)//�������ȴ�С
            {
                Blocks[m][n] = 0;
            }
        }
    }
    if (c == 0)
    {
        food();
        max++;
        score++;
        COORD pos;
        pos.X = 32;
        pos.Y = 32;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        printf("������score");
    }
}
void statics() //û�а���ʱˢ����Ļ
{
    static int frame = 1;
    frame++;
    if (frame == 10-(score/120)) //ʮ�κ�ˢ����Ļ
    {
        movesnake();
        frame = 1;
    }
}
void dynamic()//������ʱˢ����Ļ 
{
    if (_kbhit())
    {
        char val= _getch();
        if ( 's'==val&&direction!=2)//������������������ָ��ʱ
            direction = 1, movesnake();
        else if ('w' == val&&direction!=1 && direction != 0)//���������ҷ�������ָ��ʱ
            direction = 2, movesnake();
        else if ('d' == val && direction != 4)//���������ҷ�������ָ��ʱ
            direction = 3, movesnake();
        else if ('a' == val&&direction!=3)//���������ҷ�������ָ��ʱ
            direction = 4, movesnake();
    }
}
int main() 
{
    startup();
    food();//��ʼ����
    PlaySound(L"2.WAV", NULL, SND_FILENAME | SND_ASYNC|SND_LOOP);//���ֲ��ţ�ѭ������Ϊ������
    while (1) 
    {
        start();//��ɫ
        statics();//û������ʱ
        dynamic();//������ʱ
    }
    return 0;
}