#include<conio.h>  
#include<graphics.h>
#include<stdio.h>
#include<time.h>
#include<mmsystem.h>
#include"resource.h"
#include<stdlib.h>
#pragma comment(lib,"winmm.lib")
constexpr auto BLOCK_SIZE = 20;//每个各自大小;
constexpr auto HEIGHT = 30;//高度为30;
constexpr auto WIDTH = 40;//宽度为40;
int Blocks[30][40] = { 0 };//初始化数组
int direction = 0;//方向
int max=3;//最大长度，初始为3
int score = 0;
//全局变量
void startup()//初始化
{
    initgraph((HEIGHT+5) * BLOCK_SIZE, WIDTH * BLOCK_SIZE);//30*40图形
    Blocks[20][20] = 1;//组头部
    for (int i = 1; i <= max; i++)
    {
        Blocks[20][20 - i] = i + 1;//形成连续
    }
}
void food()//刷新食物
{
    int a,b;
    a = rand() % 30;
    b = rand() % 40;
    Blocks[a][b] = -1;//食物标记
}
void start()//上色
{
    for (int m = 0; m < HEIGHT; m++) //遍历数组
    {
        for (int n = 0; n < WIDTH; n++) 
        {
            if (Blocks[m][n] != 0 && Blocks[m][n] != -1)//选择构造出的组a
            {
                //依据数值确定颜色
                setfillcolor(RGB(0, 255, 0));
            }
            else if (Blocks[m][n] != 0)
                setfillcolor(RGB(255, 0, 0));//红色果实
            else
                setfillcolor(RGB(0, 0, 0));//黑色背景
            //上色大小
                fillrectangle(m * BLOCK_SIZE, n * BLOCK_SIZE, (m+1)* BLOCK_SIZE, (n + 1) * BLOCK_SIZE);
        }
    }
    FlushBatchDraw();
}
void movesnake() //移动蛇身
{
    int m, n, b1, b2, p1, p2,c;
    p1 = 0, p2 = 0, b1 = 0, b2 = 0,c=0;
    for ( m = 0; m < HEIGHT; m++) //遍历数组
    {
        for ( n = 0; n < WIDTH; n++)
        {
            if (Blocks[m][n] != 0 && Blocks[m][n] != -1)
            {
                Blocks[m][n]++;
            }
            else if (Blocks[m][n] == -1)
            {
                c++;//记录果实个数
            }
        }
    }
    for ( m = 0; m < HEIGHT; m++) //遍历数组
    {
        for ( n = 0; n < WIDTH; n++)
        {
            b1 = (n + 1) % 40;//下
            b2= (n +39) % 40; //上
            p1 = (m + 1) % 30;//右
            p2 = (m +29) % 30;//左
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
            if (Blocks[m][n] > max)//超出长度大小
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
        printf("分数是score");
    }
}
void statics() //没有按键时刷新屏幕
{
    static int frame = 1;
    frame++;
    if (frame == 10-(score/120)) //十次后刷新屏幕
    {
        movesnake();
        frame = 1;
    }
}
void dynamic()//有输入时刷新屏幕 
{
    if (_kbhit())
    {
        char val= _getch();
        if ( 's'==val&&direction!=2)//当不向上且输入向下指令时
            direction = 1, movesnake();
        else if ('w' == val&&direction!=1 && direction != 0)//当不向下且发出向上指令时
            direction = 2, movesnake();
        else if ('d' == val && direction != 4)//当不向左且发出向右指令时
            direction = 3, movesnake();
        else if ('a' == val&&direction!=3)//当不向右且发出向左指令时
            direction = 4, movesnake();
    }
}
int main() 
{
    startup();
    food();//初始画面
    PlaySound(L"2.WAV", NULL, SND_FILENAME | SND_ASYNC|SND_LOOP);//音乐播放，循环，且为背景音
    while (1) 
    {
        start();//上色
        statics();//没有输入时
        dynamic();//有输入时
    }
    return 0;
}