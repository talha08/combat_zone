#include <graphics.h>
#include <conio.h>
#include<cstdio>

typedef struct{
    char name[6];
    int score;
} highscore;

typedef struct{;
    int xl, xr, yt, yb;a
} coor;

highscore scores[3];
int input, pts;
coor icon;

void main_menu();
void levelmenu();
int getinput();
void showscores();
void sethighscores();
bool level1();
bool level2();
bool level3();
bool level4();
void scoring(int n);
void logo();
bool ptszero();
//void p_life(int life);

main()
{
    initwindow(800, 600);
    FILE *fpt;
    fpt = fopen("highscore.txt", "r");
    for(int i=0; i<3; i++) fscanf(fpt, " %s %d", &scores[i].name, &scores[i].score);
    fclose(fpt);
    logo();
    main_menu();
}

void logo()
{
    coor name1;
    char filename[80];
    PlaySound(TEXT("intro.wav"), NULL, SND_ASYNC);
    for(int i=1; i<=123; i++)
    {
        sprintf(filename, "logo\\game logo%05d.jpg", i);
        readimagefile(filename, 0, 0, 800, 600);
        delay(50);
    }
    delay(200);
     for(name1.xl=390, name1.xr=410, name1.yt=150, name1.yb=450; name1.xl>=90; name1.xl-=30, name1.xr+=30)
    {
         readimagefile("name1.jpg", name1.xl, name1.yt, name1.xr, name1.yb);
         delay(100);
    }
    delay(200);
}

void main_menu()
{
    do
    {
        icon.xl= 200, icon.yt=180, icon.xr=270, icon.yb=250;
        readimagefile("game menu.jpg", 0, 0, 800, 600);
        readimagefile("play.jpg",300, 180, 500, 250);
        readimagefile("highscore.jpg", 300, 260, 500, 330);
        readimagefile("help.jpg", 300, 340, 500, 410);
        readimagefile("about.jpg", 300, 420, 500, 490);
        readimagefile("exit.jpg",300, 500,  500, 570);
        readimagefile("icon.jpg",icon.xl, icon.yt, icon.xr, icon.yb);
        input = getinput();
        switch(input)
        {
            case 1:
                levelmenu();
                break;
            case 2:
                showscores();
                input=0;
                break;
            case 3:
                readimagefile("instruction.jpg", 0, 0, 800, 600);
                input =0;
                getch();
                break;
            case 4:
                readimagefile("about us.jpg", 0, 0, 800, 600);
                input=0;
                getch();
                break;
            case 5:
                cleardevice();
                exit(0);
        }
    }while(1);
}

void levelmenu()
{
    bool flag, st=0;
    icon.xl=200 , icon.yt=180, icon.xr=270, icon.yb=250;
    readimagefile("game_menu.jpg", 0, 0, 800, 600);
    readimagefile("level1.jpg", 300, 180, 500, 250);
    readimagefile("level2.jpg", 300, 260, 500, 330);
    readimagefile("level3.jpg", 300, 340, 500, 410);
    readimagefile("level4.jpg", 300, 420, 500, 490);
    readimagefile("back.jpg", 300, 500, 500, 570);
    readimagefile("icon.jpg", icon.xl, icon.yt, icon.xr, icon.yb);
    input = getinput();
    switch(input)
    {
        case 1:
            if(st == 0) pts=180, st++;
            flag = level1();
            if(!flag) break;
        case 2:
            if(st == 0) pts=180, st++;
            flag = level2();
            if(!flag) break;
        case 3:
            if(st == 0) pts=180, st++;
            flag = level3();
            if(!flag) break;
        case 4:
            if(st == 0) pts=180, st++;
            flag = level4();
            if(!flag)break;
            sethighscores();
            showscores();
            break;
        case 5:
            return;
    }
}

int getinput()
{
    int in;
    while(1)
    {
        if(kbhit()) in = getch();
        if(in == 32)
        {
            PlaySound(TEXT("select.wav"), NULL, SND_ASYNC);
            switch(icon.yt)
            {
            case 180:
                return 1;
            case 260:
                return 2;
            case 340:
                return 3;
            case 420:
                return 4;
            case 500:
                return 5;
            }
        }
        else if(in == 80)
        {
            PlaySound(TEXT("aaa.wav"), NULL, SND_ASYNC);
            if(icon.yt == 500) continue;
                readimagefile("background.jpg",icon.xl,icon.yt,icon.xr,icon.yb);
                icon.yb+=80;
                icon.yt+=80;
                readimagefile("icon.jpg", icon.xl,icon.yt,icon.xr,icon.yb);
                in=0;
                continue;
        }
        else if(in == 72)
        {
            PlaySound(TEXT("aaa.wav"), NULL, SND_ASYNC);
            if(icon.yt == 180) continue;
                readimagefile("background.jpg",icon.xl,icon.yt,icon.xr,icon.yb);
                icon.yb-=80;
                icon.yt-=80;
                readimagefile("icon.jpg", icon.xl,icon.yt,icon.xr,icon.yb);
                in=0;
                continue;
        }
        else if(in == 77);
        else if(in == 75);
        in=0;

    }
}

void showscores()
{
    readimagefile("highscore12.jpg", 0, 0, 800, 600);
    int clr[3]={9, 3, 14};

    for(int i=0, y=260; i<3; i++, y +=100)
    {
        setcolor(clr[i]);
        settextstyle(8, HORIZ_DIR, 3);
        outtextxy(310, y, scores[i].name);
        int num = scores[i].score;
         char str[3];
    for(int i=0; i<3; i++) str[3] = '\0';
        for(int j=0; j<3; j++, num /= 10) str[3-j-1] = num%10 + '0';
        str[3] = '\0';
        outtextxy(600, y, str);
    }
    getch();
    FILE *fpt;
    fpt = fopen("highscore.txt", "w");
    for(int i=0; i<3; i++) fprintf(fpt, "%s %d\n", scores[i].name, scores[i].score);
    fclose(fpt);
}

void sethighscores()
{
    for(int i=0; i<3; i++)
        if(pts> scores[i].score)
        {
            readimagefile("highscore14.jpg", 0, 0, 800, 600);
            setcolor(9);
            settextstyle(8, HORIZ_DIR, 3);
            outtextxy(280, 200, "ENTER YOUR NAME");
            for(int j=0; (scores[i].name[j]=getch()) != '\n' && j<6; j++) outtextxy(280, 250, scores[i].name);
            scores[i].score = pts;
            break;
        }
}

void scoring(int n)
{
    pts += n;
    setcolor(14);
    settextstyle(8, HORIZ_DIR, 1);
    outtextxy(700, 0, "SCORE:");
    int num=pts;
    char str[3];
    for(int i=0; i<3; i++, num /= 10) str[3-i-1] = num%10 + '0';
    str[3] = '\0';
    outtextxy(765, 0, str);
}

bool ptszero()
{
    if(pts==0) return 1;
    return 0;
}

/*void p_life(int life)
{
   readimagefile("heart.jpg", 0, 0, 20, 20);
    setcolor(7);
    settextstyle(5, HORIZ_DIR, 1);
    char str[1];
    str[0] = life + '0';
    str[1] = '\0';
    outtextxy(25, 0, str);
}*/
