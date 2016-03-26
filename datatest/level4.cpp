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

bool level4()
{
    char bname[25];
    coor player, enemy[3], pshot[25], enshot[3];
    int plife=3, enlife[3]={7,7, 7};
    int fb =0, input, bo=0;
    player.xl= 20, player.yt=200, player.xr=100, player.yb=300;
    enemy[0].xl=550, enemy[0].yt=50, enemy[0].xr=630, enemy[0].yb=150;
    enemy[1].xl=550, enemy[1].yt=400, enemy[1].xr=630, enemy[1].yb=500;
    enemy[2].xl=650, enemy[2].yt=200, enemy[2].xr=730, enemy[2].yb=300;
    readimagefile("background.jpg", 0, 0, 800, 600);
    readimagefile("player.jpg", player.xl, player.yt, player.xr, player.yb);
    readimagefile("enemy3.jpg", enemy[0].xl, enemy[0].yt, enemy[0].xr, enemy[0].yb);
    readimagefile("enemy4.jpg", enemy[1].xl, enemy[1].yt, enemy[1].xr, enemy[1].yb);
    while(1)
    {
       scoring(0);
     //  p_life(plife);
        for(int i=0; i<3; i++)
        {
            char name[30];
           if(enshot[i].xl<=0 || fb==i)
            {
                fb++;
                enshot[i].xl = enemy[i].xl - 30;
                enshot[i].xr = enemy[i].xl;
                enshot[i].yb = enemy[i].yb - 45;
                enshot[i].yt = enemy[i].yt + 45;
                readimagefile("background.jpg", 0, 0, 800, 600);
                sprintf(name, "enbullet%d.jpg", i);
                readimagefile(name, enshot[i].xl, enshot[i].yt, enshot[i].xr, enshot[i].yb);
            }
            enemy[i].yb += 4, enemy[i].yt += 4 ;
            if(enshot[i].xl > 0)
            {
                enshot[i].xl-= 5, enshot[i].xr -=5;
                sprintf(name, "enbullet%d.jpg", i);
                readimagefile(name, enshot[i].xl, enshot[i].yt, enshot[i].xr, enshot[i].yb);
            }
            if(enemy[i].yb> 600)
            {
                enemy[i].yt =0, enemy[i].yb = 100;
                readimagefile("background.jpg", 0, 0, 800, 600);
            }
            sprintf(name, "enemy%d.jpg", i+2);
            readimagefile(name, enemy[i].xl, enemy[i].yt, enemy[i].xr, enemy[i].yb);
        }
        if(kbhit())
        {
            input = getch();
            if(input == 32)
            {
                scoring(-5);
                readimagefile("background.jpg", 0, 0, 800, 600);
                PlaySound(TEXT("shoot.wav"), NULL, SND_ASYNC);
                for(int k=0; k<2; k++)
            {
                pshot[bo].xl = player.xr;
                pshot[bo].xr = player.xr + 30;
                if(k==0)
                {
                    pshot[bo].yb = player.yb - 40;
                    pshot[bo].yt = player.yt + 50;
                    sprintf(bname, "pbullet%d.jpg", bo);
                readimagefile(bname, pshot[bo].xl, pshot[bo].yt, pshot[bo].xr, pshot[bo].yb);
                bo++;
                }
               /* if(k==1)
               {
                    pshot[bo].yb = player.yb - 50;
                    pshot[bo].yt = player.yt + 40;
                    sprintf(bname, "pbullet%d.jpg", bo);
                readimagefile(bname, pshot[bo].xl, pshot[bo].yt, pshot[bo].xr, pshot[bo].yb);
                bo++;
                }*/

            }
            input =0;
            }
            else if(input == 72)
            {
            if(player.yt>= 0) player.yb-=5, player.yt-=5;
            input =0;
            }
            else if(input == 80)
            {
            if(player.yb <= 600) player.yb+=5, player.yt+=5;
            input =0;
            }
            else if(input == 75)
            {
            if(player.xl >=0) player.xl-=5, player.xr-=5;
            input =0;
            }
            else if(input == 77)
            {
            if(player.xr<=800) player.xl+=5, player.xr+=5;
            input =0;
            }
  /*           else if(input == 13)
            {
                system("pause");
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
                pshot[i].xl +=6, pshot[i].xr +=6;
                sprintf(bname, "pbullet%d.jpg", i);
                readimagefile(bname, pshot[i].xl, pshot[i].yt, pshot[i].xr, pshot[i].yb);
            }
            if(pshot[i].xr >= 800)
            {
                pshot[i].xl =-1, pshot[i].xr = -1, pshot[i].yb =-1, pshot[i].yt =-1;
                readimagefile("background.jpg", 0, 0, 800, 600);
            }
        }
        for(int j=0; j<3; j++)
        {
            if((enshot[j].yt>= player.yt && enshot[j].yb <= player.yb) && (enshot[j].xl>=player.xl && enshot[j].xl <player.xr))
            {
                PlaySound(TEXT("explosion.wav"), NULL, SND_ASYNC);
                readimagefile("Explosion.jpg" , player.xl, player.yt, player.xr , player.yb );
                delay(200);
                readimagefile("background.jpg", 0, 0, 800, 600);
                readimagefile("player.jpg", player.xl, player.yt, player.xr, player.yb);
                enshot[j].xl = 0, plife--;
            }
            if(((player.xl>=enemy[j].xl && player.xl<=enemy[j].xr) || (player.xr>=enemy[j].xl && player.xr<=enemy[j].xr)) &&
                 ((player.yt>=enemy[j].yt && player.yb<=enemy[j].yt) || (player.yb>=enemy[j].yb && player.yt<=enemy[j].yb))) plife=0, enlife[j] =0;
             for(int i=0; i<bo; i++) if((pshot[i].yt>= enemy[j].yt && pshot[i].yb<= enemy[j].yb) && (pshot[i].xl>= enemy[j].xl && pshot[i].xr<= enemy[j].xr))
            {
                PlaySound(TEXT("explosion.wav"), NULL, SND_ASYNC);
                readimagefile("Explosion.jpg" , enemy[j].xl , enemy[j].yt , enemy[j].xr , enemy[j].yb );
                delay(200);
                pshot[i].xl =-1, pshot[i].xr = -1, pshot[i].yb =-1, pshot[i].yt =-1, enlife[j]--;
                if(enlife[j]>0)
                {
                    char name[30];
                    sprintf(name, "enemy%d.jpg", j+2);
                    readimagefile(name, enemy[j].xl, enemy[j].yt, enemy[j].xr, enemy[j].yb);
                }
                scoring(20);
                readimagefile("background.jpg", 0, 0, 800, 600);
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
         if(enlife[0] ==0 && enlife[1] == 0)
        {
            PlaySound(TEXT("win.wav"), NULL, SND_ASYNC);
            readimagefile("win.jpg", 0, 0, 800, 600);
            cleardevice();
            return 1;
        }
    }
}

