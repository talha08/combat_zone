#include<cstdio>
#include<graphics.h>
#include<conio.h>
#include<windows.h>

typedef struct{
    int xl, xr, yt, yb;
} coor;
void scoring(int n);
bool ptszero();
void showscores();
void sethighscores();
//void p_life(int life);

bool level1()
{
    char bname[25];
    coor player, enemy, pshot[25], enshot;
    int plife=3, enlife =4, bo=0, input;
    bool fb;
    player.xl= 20, player.yt=200, player.xr=100, player.yb=300;
    enemy.xl=650, enemy.yt=100, enemy.xr=720, enemy.yb=200;
    readimagefile("background.jpg", 0, 0, 800, 600);
    readimagefile("player.jpg", player.xl, player.yt, player.xr, player.yb);
    readimagefile("enemy1.jpg", enemy.xl, enemy.yt, enemy.xr, enemy.yb);
    while(1)
    {
       scoring(0);
      // p_life(plife);
        if(enshot.xl <=0 || fb==0)
        {
            if(fb ==0)fb++;
            enshot.xl = enemy.xl - 30;
            enshot.xr = enemy.xl;
            enshot.yb = enemy.yb - 45;
            enshot.yt = enemy.yt + 45;
            readimagefile("background.jpg", 0, 0, 800, 600);
            readimagefile("enbullet1.jpg", enshot.xl, enshot.yt, enshot.xr, enshot.yb);
        }
        enemy.yt+=2, enemy.yb+=2;
        if(enshot.xl > 0)
        {
            enshot.xl-= 4, enshot.xr -=4;
            readimagefile("enbullet1.jpg", enshot.xl, enshot.yt, enshot.xr, enshot.yb);
        }
        if(enemy.yb> 600)
        {
            enemy.yt =0, enemy.yb =100;
            readimagefile("background.jpg", 0, 0, 800, 600);
        }
            readimagefile("enemy1.jpg", enemy.xl, enemy.yt, enemy.xr, enemy.yb);
        if(kbhit())
        {
            input = getch();
            if(input == 32)
            {
            scoring(-5);
            pshot[bo].xl = player.xr;
            pshot[bo].xr = player.xr + 30;
            pshot[bo].yb = player.yb - 45;
            pshot[bo].yt = player.yt + 45;
            readimagefile("background.jpg", 0, 0, 800, 600);
            PlaySound(TEXT("shoot.wav"), NULL, SND_ASYNC);
            sprintf(bname, "pbullet%d.jpg", bo);
            readimagefile(bname, pshot[bo].xl, pshot[bo].yt, pshot[bo].xr, pshot[bo].yb);
            input =0, bo++;
            }
            else if(input == 72)
            {
            if(player.yt>= 0) player.yb-=4, player.yt-=4;
            input =0;
            }
            else if(input == 80)
            {
            if(player.yb <= 600) player.yb+=4, player.yt+=4;
            input =0;
            }
            else if(input == 75)
            {
            if(player.xl >=0) player.xl-=4, player.xr-=4;
            input =0;
            }
            else if(input == 77)
            {
            if(player.xr<=800) player.xl+=4, player.xr+=4;
            input =0;
            }
 /*           else if(input == 13)
            {
                system("pause.exe");
                setcolor(5);
                settextstyle(8, HORIZ_DIR, 3);
                outtextxy(300, 350, "Game Paused");
                outtextxy(270, 380, "Press Any Key To Continue");
                getch();
            }*/
        }
        readimagefile("player.jpg", player.xl, player.yt, player.xr, player.yb);
        for(int i=0; i<bo; i++)
        {
            if(pshot[i].xr>0 && pshot[i].xr<800)
            {
                pshot[i].xl +=4, pshot[i].xr +=4;
                sprintf(bname, "pbullet%d.jpg", i);
                readimagefile(bname, pshot[i].xl, pshot[i].yt, pshot[i].xr, pshot[i].yb);
            }
            if(pshot[i].xr >= 800)
            {
                pshot[i].xl =-1, pshot[i].xr = -1, pshot[i].yb =-1, pshot[i].yt =-1;
                readimagefile("background.jpg", 0, 0, 800, 600);
            }
        }
        if((enshot.yt>= player.yt && enshot.yb <= player.yb) && (enshot.xl>=player.xl && enshot.xl <player.xr))
        {
            PlaySound(TEXT("explosion.wav"), NULL, SND_ASYNC);
            readimagefile("Explosion.jpg" , player.xl , player.yt , player.xr , player.yb );
            delay(200);
            readimagefile("background.jpg", 0, 0, 800, 600);
            readimagefile("player.jpg", player.xl, player.yt, player.xr, player.yb);
            enshot.xl = 0, plife--;
        }
        if(((player.xl>=enemy.xl && player.xl<=enemy.xr) || (player.xr>=enemy.xl && player.xr<=enemy.xr)) &&
            ((player.yt>=enemy.yt && player.yb<=enemy.yt) || (player.yb>=enemy.yb && player.yt<=enemy.yb))) plife=0, enlife =0;
        for(int i=0; i<bo; i++)
        {
            if((pshot[i].yt>= enemy.yt && pshot[i].yb<= enemy.yb) && (pshot[i].xl>= enemy.xl && pshot[i].xr<= enemy.xr))
            {
                PlaySound(TEXT("explosion.wav"), NULL, SND_ASYNC);
                readimagefile("Explosion.jpg" , enemy.xl , enemy.yt , enemy.xr , enemy.yb );
                delay(200);
                pshot[i].xl =-1, pshot[i].xr = -1, pshot[i].yb =-1, pshot[i].yt =-1;
                readimagefile("background.jpg", 0, 0, 800, 600);
                readimagefile("enemy1.jpg", enemy.xl, enemy.yt, enemy.xr, enemy.yb);
                pshot[i].xl =-1, pshot[i].xr = -1, pshot[i].yb =-1, pshot[i].yt =-1, enlife--;
                scoring(20);
            }
        }
        if(plife ==0 || ptszero())
        {
            PlaySound(TEXT("over.wav"), NULL, SND_ASYNC);
            readimagefile("Game over.jpg", 0, 0, 800, 600);
            delay(2000);
            sethighscores();
            showscores();
            cleardevice();
            return 0;
        }
         if(enlife ==0)
        {
            PlaySound(TEXT("win.wav"), NULL, SND_ASYNC);
            readimagefile("win.jpg", 0, 0, 800, 600);
            delay(2000);
            cleardevice();
            return 1;
        }
    }
}
