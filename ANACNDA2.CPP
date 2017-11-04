#include<conio.h>
#include<iostream.h>
#include<stdio.h>
#include<stdlib.h>
#include<bios.h>
//#define SPEED 6000000

int len;
long int SPEED = 6000000;
int maze;

struct player
{
 char name[16];
 int score;
};

int getkey(void)
 {
  int key,lo,hi;
  key=bioskey(0);
  lo=key & 0x00FF;
  hi=(key & 0xFF00)>>8;
  return((lo==0)?hi+256:lo);
 }

void start_graphic();
void function(int len0,int x,int y,int xt,int yt,int xf, int yf,
	      int px[],int py[],long int speed,char a[],char status,
	      player);
int isamong(char c,char ch[],int n);
int isamong1(int c,int c1,int ch[],int ch1[],int n);
void showmaze();
int mazehit(int x,int y);
void waitfor(long int k);
void wait();

void hline()
{
for(int i=0;i<80;i++)
printf("Ä");
return;
}
/********************************************************************/

//////////////////////// MAIN STARTS ///////////////////////////////
void main()
{
char a[500],s='O',name[80],status; //s=skin
int px[500],py[500],len0,xt,yt,xf,yf,i,j,r,rx,ry,x,y; //xt=xtemporary  xf=xfood
int  top=3,bottom=24,left=1,right=79;    //r = range of food //x,y of tail
int  move,current,ans;
FILE *fil;
player curr;

maze=0;
long int speed;
speed=SPEED;

start_graphic();

clrscr();
for(i=0;i<80;i++) name[i]=' ';
cout<<"NOTE:\n\nThe Anaconda is not beautiful... but then... It is not meant to be either...!!!";
cout<<"\n\n\nEnter Your Name ( 15 characters max. ) : ";
scanf(" %[^\n]",name);
for(i=0;i<15;i++) curr.name[i]=name[i];
 curr.name[15]='\0';

_setcursortype(_NOCURSOR);


newgame:
clrscr();
curr.score=0;
randomize();

//***************** create and display initial anaconda ****************
len0=10;  // initial length
len=len0;
for( i=0;i<len;i++)
 { a[i]=s; px[i]=i+5; py[i]=14;}

for( i=0;i<len;i++)
 { gotoxy(px[i],py[i]);       cout<<a[i]; }
 r=4;   rx=74; ry=19;
xf=random(rx)+r;
yf=random(ry)+r;
gotoxy(xf,yf); cout<<s;

if(maze) showmaze();
//************************** start game *******************************
 again:
 move=getkey();
 //if(!isamong(move,allowedmoves,4)) goto again;

//NOTE : BIOS codes for arrowkeys : l,r,u,d : 331,333,328,336
//       For others, see tcalc example ( header file )

do {
    switch (move)
     {
      case 333:

       if(current==331) {move=current; break;} //backward not allowed
       speed=SPEED/2;
       current=333;
       do{
	 x=px[0]; y=py[0];
	 status='3';// status is  nothing imp, to be used for debugging
	 xt=px[len-1]; yt=py[len-1];        // [len-1] represents "head"
	 if(!maze)
	  { if(xt==right)  xt-=(right-left);}  // to allow " aar paar " through
	  xt++;			     // screen
	  if(isamong1(xt,yt,px,py,len) )    // self collision
	   {
	    gotoxy(1,1); cout<<"G A M E   O V E R ! ! ! ";
	    goto end;
	   }
	  if(maze)
	   {
	    if(mazehit(xt,yt))
	     {
	      gotoxy(1,1); cout<<"G A M E   O V E R  ! ! !";
	      getch();
	      goto end;
	     }
	   }

	  function(len0,x,y,xt,yt,xf,yf,px,py,speed,a,status,curr);
			     // function shows current frame

	  if(xt==xf && yt==yf)              // check and eat food
	  {
	   a[len]='O'; px[len]=xt; py[len]=yt; len++;
	   xf=random(rx)+r;
	   yf=random(ry)+r;                // show new food
	   gotoxy(xf,yf); cout<<'O';
	  }
	 }while(!kbhit());   // run anaconda till key press
	  move=getkey();      // retrieve the key pressed
	 break;
       //----------------------------------------------------------
       case 331:

	if(current==333) {move=current; break;}
	speed=SPEED/2;
	current=331;
	do
	 {
	 x=px[0]; y=py[0];
	 status='1';
	 xt=px[len-1]; yt=py[len-1];
	 if(!maze)
	 { if(xt==left) xt+=(right-left); }
	  xt--;
	  if(isamong1(xt,yt,px,py,len) )
	   {
	    gotoxy(1,1); cout<<"G A M E   O V E R ! ! ! ";
	    goto end;
	   }
	  if(maze)
	   { if(mazehit(xt,yt))
	     {
	      gotoxy(1,1); cout<<"G A M E   O V E R ! ! ! ";
	      getch();
	      goto end;
	     }
	   }

	  function(len0,x,y,xt,yt,xf,yf,px,py,speed,a,status,curr);
	  if(xt==xf && yt==yf)
	  {
	   a[len]='O'; px[len]=xt; py[len]=yt; len++;
	   xf=random(rx)+r;
	   yf=random(ry)+r;
	   gotoxy(xf,yf); cout<<'O';
	  }
	 }while(!kbhit());
	  move=getkey();
	 break;
       //------------------------------------------------------------
       case 336:

	if(current==328) {move=current; break;}
	speed=SPEED;
	current=336;
	 do
	 {
	 x=px[0]; y=py[0];
	 status='2';
	 xt=px[len-1]; yt=py[len-1];
	 if(!maze)
	 { if(yt==bottom) yt-=(bottom-top); }
	 yt++;
	  if(isamong1(xt,yt,px,py,len) )
	   {
	    gotoxy(1,1); cout<<"G A M E   O V E R ! ! ! ";
	    goto end;
	   }
	  if(maze)
	   { if(mazehit(xt,yt))
	     {
	      gotoxy(1,1); cout<<"G A M E   O V E R ! ! ! ";
	      getch();
	      goto end;
	     }
	   }

	  function(len0,x,y,xt,yt,xf,yf,px,py,speed,a,status,curr);
	  if(xt==xf && yt==yf)
	  {
	   a[len]='O'; px[len]=xt; py[len]=yt; len++;
	   xf=random(rx)+r;
	   yf=random(ry)+r;
	   gotoxy(xf,yf); cout<<'O';
	  }
	 }while(!kbhit());
	  move=getkey();
	 break;
       //----------------------------------------------------------
       case 328:

	if(current==336) {move=current; break;}
	speed=SPEED;
	current=328;
	do
	 {
	 x=px[0]; y=py[0];
	 status='5';
	 xt=px[len-1]; yt=py[len-1];
	 if(!maze)
	  { if(yt==top) yt+=(bottom-top); }
	  yt--;
	  if(isamong1(xt,yt,px,py,len) )
	   {
	    gotoxy(1,1); cout<<"G A M E   O V E R ! ! ! ";
	    goto end;
	   }
	  if(maze)
	   { if(mazehit(xt,yt))
	     {
	      gotoxy(1,1); cout<<"G A M E   O V E R ! ! ! ";
	      getch();
	      goto end;
	     }
	   }

	  function(len0,x,y,xt,yt,xf,yf,px,py,speed,a,status,curr);
	  if(xt==xf && yt==yf)
	  {
	   a[len]='O'; px[len]=xt; py[len]=yt; len++;
	   xf=random(rx)+r;
	   yf=random(ry)+r;
	   gotoxy(xf,yf); cout<<'O';
	  }
	 }while(!kbhit());
	  move=getkey();
	 break;
       //---------------------------------------------------------------
       case 27:

	clrscr();
	cout<<"Game Aborted !!!                            Press esc to exit";
	cout<<"\nYour score : "<<(len-len0)*10;
	goto end;

       default :       // for invalid key presses
	move=current;
	break;
       }
       status='0';
   }while(1);
//*********************** exit options **************************
end:
_setcursortype(_NORMALCURSOR);
getch();
clrscr();
cout<<"Press ENTER   : NEW GAME"
    <<"\n          esc : To EXIT"
    <<"\n\n\n\n\n\nNOTE 	ANACONDA ETIQUETTE 	:- \n\n Do NOT move Anaconda \"right\" EVERYTIME you 'start' a new game"
    <<"\nIf he gets fed up of starting with \"right\" move everytime, he will signal "
    <<"\nGameover at the very start"
    <<"\n\nIn such a case 'start' your game with some other move,like \"up\" , \"down\" etc.";

ans=getkey();
if(ans==27) { textcolor(WHITE); clrscr(); }
else goto newgame;
}
/////////////////////////// MAIN ENDS //////////////////////////////////////

void function (int len0,int x,int y,int xt,int yt,int xf, int yf,
	       int px[],int py[],long int speed,char a[],char status,
	       player cur)
{
  FILE *fil;
  player tp;
  //
  if( (fil=fopen("topscore.doc","r") )==NULL )
  {
   fil=fopen("topscore.doc","w");
   fprintf(fil,"Amit Bhola\n%d",100);
   fclose(fil);
  }
  else fclose(fil);

   fil=fopen("topscore.doc","r");
   fscanf(fil," %[^\n]",&tp.name);
   fscanf(fil,"%d",&tp.score);
   fclose(fil);
   //
	 for(int j=1;j<len;j++)
	  { px[j-1]=px[j]; py[j-1]=py[j]; }
	 px[len-1]=xt; py[len-1]=yt;
	 waitfor(speed);

	 gotoxy(x,y); cout<<" ";
  textcolor(LIGHTGREEN);
  for(int i=0;i<len;i++)
	  { gotoxy(px[i],py[i]);       cprintf("%c",a[i]); }
   textcolor(LIGHTRED);
	 gotoxy(xf,yf); cprintf("O");
   textcolor(LIGHTCYAN);
	 gotoxy(1,1);
	 cur.score=(len-len0)*10;
	 if(cur.score>=tp.score) tp=cur;
	 cprintf("A N A C O N D A                   Top Score : %15s : %d        ",tp.name,tp.score);
	 printf("\n");
	 cprintf("Press esc to EXIT                 Player    : %15s : %d        ",cur.name,cur.score);
   fil=fopen("topscore.doc","w");
   fprintf(fil,"%s\n%d",tp.name,tp.score);
   fclose(fil);
   return;
}
//***********************************************************
void showmaze()
 {
  int i;
  textcolor(BROWN);

   for(i=1;i<=79;i++) { gotoxy(i,3);   cprintf("Û"); }
   for(i=1;i<=79;i++) { gotoxy(i,24);   cprintf("Û"); }
   for(i=3;i<=24;i++) { gotoxy(1,i);   cprintf("Û"); }
   for(i=3;i<=24;i++) { gotoxy(79,i);   cprintf("Û"); }
  return;
 }
//***********************************************************
int isamong(char c,char ch[],int n)  // for invalid starting moves
{
  int i,t=0;
  for(i=0;i<n;i++)
   {
    if(ch[i]==c)
    {t=1; break;}
   }
   //cout<<t;
  return t;
}
//************************************************************
int isamong1(int c,int c1,int ch[],int ch1[],int n)
{                                   // for collision check
  int i,t=0;
  for(i=0;i<n;i++)
   {
    if(ch[i]==c && ch1[i]==c1)
    {t=1; break;}
   }

  return t;
}
//************************************************************
int mazehit(int xt,int yt)
{
 int mx[300],my[300];
 int i,j;
 j=0;
   for(i=1;i<=79;i++,j++)  { mx[j]=i; my[j]=3; }
   for(i=1;i<=79;i++,j++)  { mx[j]=i; my[j]=24; }
   for(i=3;i<=24;i++,j++)  { mx[j]=1; my[j]=i; }
   for(i=3;i<=24;i++,j++)  { mx[j]=79; my[j]=i; }

  return (isamong1(xt,yt,mx,my,j) );
 }
//************************************************************
void start_graphic()          // show starting graphics , messages
{
 char c;
 clrscr();
 cout<<"Loading...\n\n\n\n\n\n\n\n\n";
 cout<<"                   A   N   A   C   O   N   D   A";
 wait();
 cout<<"\n\n               If You Can't Breathe...";
 wait(); wait();
 cout<<"\n\n               How Will You Scream.....  ?";
 gotoxy(1,1);
 wait(); wait(); wait();
 clrscr();
 cout<<"\nANACONDA  is behind you..."
     <<"\n\n\nPlease press Alt+<enter> to maximise..( ITS IMPORTANT FOR GOOD GRAPHICS )\n";
     hline();
cout <<"\n\nPRESS ANY KEY : TO CONTINUE WITH DEFAULT SETTINGS..."
     <<"\n          'S' : to adjust settings"
     <<"\n\n( You can select speed levels and mazes with settings )\n\n";
     hline();
 c=getch();
 if (c=='s'||c=='S')
  {
   char l,m;

   again1:
   clrscr();
   cout<<"Select Level : \n"
       <<"\nEnter 1: Baby"
       <<"\n      2: Intermediate ( Default )"
       <<"\n      3: Challange"
       <<"\n      4: You need to have strong RELATIVITY CONCEPTS !"
       <<"\n\nEnter Your Choice : ";
   cin>>l;
   switch (l)
    {
     case '1':
       SPEED=15000000; break;
     case '2':
       SPEED=6000000; break;
     case '3':
       SPEED=3000000; break;
     case '4':
       SPEED=1000000; break;
     default:
       goto again1;
     }

    again2:
   clrscr();
   cout<<"Select Maze : \n"
       <<"\nEnter 1: Maze on"
       <<"\n      2: No Maze ( Default )"
       <<"\n\nEnter Your Choice : ";
   cin>>m;
   switch (m)
    {
     case '1':
       maze=1; break;
     case '2':
       maze=0; break;
     default:
       goto again2;
     }
    return;
  }
 else
 return ;
}

/*******************************************************************/
void waitfor(long int k)
{
for(long int i=0;i<k;i++) ;
}

/********************************************************************/
void wait()
{
for(long int i=0;i<99999999;i++) ;
}