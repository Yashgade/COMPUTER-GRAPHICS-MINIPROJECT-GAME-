/*CG MINI_PROJECT: MINI_GAME*/
#include<iostream>
#include<stdio.h>
#include<conio.h>
#include"BresenhemLine.h"
#include"BresenhemCircle.h"
#include<graphics.h>
using namespace std;

int y[]={150,120,90,60,30};                                     // HEIGHT ARRAY FOR THE TARGET
int x[]={54,80,148,216,284,352,420,488,556};                    // X-COORDINATES OF THE TARGET
int orbRadius=10;                                               //RADIUS OF THE TARGET
void aircraft1(int[],int);
void orb(int);

void start()
{
    int gd=DETECT,gm,ch,i=0,j=1,k=1,cnt=1,mov,speed=25,ht1=410,ht2=440,flag=0,points=0;
	char resp;
	int x1[]={310,275,290,300,310,320,330,340,350,365,330};         //X-COORDINATES OF THE AIRCRAFT
	int x_check[]={1,2,3,4,5,4,3,2,1} ;
	initgraph(&gd,&gm,NULL);

    Breline(0,0,getmaxx(),0,k);                                     //BACKGROUND FOR THE SETUP
    Breline(0,0,0,getmaxy(),k);
    Breline(0,getmaxy(),getmaxx(),getmaxy(),k);
    Breline(getmaxx(),0,getmaxx(),getmaxy(),k);

    setfillstyle(1,k);
    floodfill(320,240,k);

    setcolor(k);

    orb(10);                                                            //ORB ARE CREATED WITH SPECIFIED COLOUR THROUGH orb() FUNCTION

    do
    {
        mov=tolower(getche());                                          //USER ENTERS ONE OUT OF THREE MOVES
        if(mov=='d' || mov=='D')                                       //TO MOVE RIGHT
        {
            aircraft1(x1,getcolor());
            for(int i=0;i<11;i++)
                x1[i]=x1[i]+speed;
            aircraft1(x1,12);
        }
        else if(mov=='a' || mov=='A')                                   //TO MOVE LEFT
        {
            aircraft1(x1,getcolor());
            for(int i=0;i<11;i++)
                x1[i]=x1[i]-speed;
            aircraft1(x1,12);
        }
        else if(mov=='w' || mov=='W')                                   //TO SHOOT
        {
            while(ht1>10)                                               //CREATES SHOOTING EFFECT
            {
                Breline(x1[0],ht1,x1[0],ht2,11);
                Breline(x1[10],ht1,x1[10],ht2,11);
                Breline(x1[0],ht1,x1[0],ht2,getcolor());
                Breline(x1[10],ht1,x1[10],ht2,getcolor());
                ht1-=10;
                ht2-=10;
                delay(0.8);
                for(int i=0;i<9;i++)                                    //LOOP TO CHECK IF ANY OF THE ORBS IS HIT
                    if((x[i]-10<=x1[0] && x1[0]<=x[i]+10) || (x[i]-10<=x1[10] && x1[10]<=x[i]+10))
                        if((ht1<=y[abs(4-i)]+10) ||(ht2<=y[abs(4-i)]+10) )
                            if(x_check[i]>0)
                            {
                                Brecircle(x[i],(x_check[i]*30),orbRadius,getcolor());
                                setfillstyle(1,getcolor());
                                floodfill(x[i],(x_check[i]*30),getcolor());
                                x_check[i]=x_check[i]-1;
                                points++;
                                flag=1;
                                break;
                            }
                if(flag==1)                                            //CHECKS IF ORB IS HIT
                    break;
                }
                ht1=410;ht2=440;
                flag=0;
        }
        i=i+10;

        if(points==25)                                                //IF ALL ORBS ARE HIT
        {
            setcolor(14);
            outtextxy(280,240,"THE ENEMY HAS BEEN DEFEATED");
            outtextxy(280,260,"YOU WIN");
            outtextxy(280,300,"POINTS : 25");
            delay(200);
            break;
        }
    }while(x1[1]>0 && x1[9]<getmaxx());                             //CHECKS IF AIRCRAFT IS WITHIN THE BOUNDS
    if(points<25)
    {
        setcolor(14);
        outtextxy(280,240,"OUT OF BOUNDS!");
        outtextxy(280,260,"GAME OVER");
    }
    outtextxy(280,360,"Click on the aircraft and press any key");
    getch();
    closegraph();
}

int main()
{
	int gd=DETECT,gm,ch;
	char resp;
	do
    {
        initgraph(&gd,&gm,NULL);
        setbkcolor(5);
        setcolor(14);
        outtextxy(280,0,"MENU");                            //MENU
        outtextxy(280,60,"1.START");
        outtextxy(280,100,"2.EXIT");
        outtextxy(100,420,"d: To move right");
        outtextxy(100,460,"a: To move left");
        outtextxy(100,380,"w: To shoot");
        outtextxy(260,460,"Make sure you have selected the user window");
        cin>>ch;
        if(ch==1)
        {
            closegraph();
            start();
        }

    }while(ch!=2);
    closegraph();
	cout<<"\nOUT OF PROGRAM"<<endl;
	return 0;
}

void orb(int orbColor)                                  //TO CREATE ORB-PATTERN WITH A GIVEN COLOUR
{
        int inc=0,iterate;
        for(int i=0;i<5;i++)
        {
            inc++;iterate=i;
            for(int j=0;j<i+inc;j++)
            {
                Brecircle(x[4-iterate],y[i],orbRadius,orbColor);
                setfillstyle(1,orbColor);
                floodfill(x[4-iterate],y[i],orbColor);
                iterate--;
            }
        }
}

void aircraft1(int x[],int c)                          //TO CREATE AIRCRAFT WITH A GIVEN COLOUR
{
            Breline(x[5],420,x[4],430,c);             //TRIANGLE
            Breline(x[5],420,x[6],430,c);
            Breline(x[4],430,x[6],430,c);
            setfillstyle(1,c);
            floodfill(x[5],425,c);

            Breline(x[2],430,x[8],430,c);           //UPPER TRAPEZOID
            Breline(x[2],430,x[1],445,c);
            Breline(x[8],430,x[9],445,c);
            Breline(x[1],445,x[9],445,c);
            setfillstyle(1,c);
            floodfill(x[5],437,c);

            Breline(x[4],445,x[6],445,c);           //RECTANGLE
            Breline(x[4],445,x[4],460,c);
            Breline(x[4],460,x[6],460,c);
            Breline(x[6],445,x[6],460,c);
            setfillstyle(1,c);
            floodfill(x[5],453,c);

            Breline(x[4],460,x[6],460,c);           //LOWER TRAPEZOID
            Breline(x[4],460,x[3],470,c);
            Breline(x[3],470,x[7],470,c);
            Breline(x[6],460,x[7],470,c);
            setfillstyle(1,c);
            floodfill(x[5],465,c);
}
