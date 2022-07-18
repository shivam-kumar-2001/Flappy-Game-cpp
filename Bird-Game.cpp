#include<iostream>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <time.h>
#include<direct.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define MENU_WIDTH 20
#define GAP_SIZE 7
#define PIPE_DIF 45

using namespace std;



HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int pipePos[3];
int gapPos[3];
int pipeFlag[3];
char bird[2][6] = { '/','-','-','o','\\',' ',
                    '|','_','_','_',' ','>' };
int birdPos = 6;
int score = 0;

void gotoXY(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size)
{
    if(size == 0)
        size = 20;

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console,&lpCursor);
}

void drawBorder(){

    for(int i=0; i<SCREEN_WIDTH; i++){
        gotoXY(i,0); cout<<"±";
        gotoXY(i,SCREEN_HEIGHT); cout<<"±";
    }

    for(int i=0; i<SCREEN_HEIGHT; i++){
        gotoXY(0,i); cout<<"±";
        gotoXY(SCREEN_WIDTH,i); cout<<"±";
    }
    for(int i=0; i<SCREEN_HEIGHT; i++){
        gotoXY(WIN_WIDTH,i); cout<<"±";
    }
}
void genPipe(int ind){
    gapPos[ind] = 3 + rand()%14;
}
void drawPipe(int ind){
    if( pipeFlag[ind] == true ){
        for(int i=0; i<gapPos[ind]; i++){
            gotoXY(WIN_WIDTH-pipePos[ind],i+1); cout<<"***";
        }
        for(int i=gapPos[ind]+GAP_SIZE; i<SCREEN_HEIGHT-1; i++){
            gotoXY(WIN_WIDTH-pipePos[ind],i+1); cout<<"***";
        }
    }
}
void erasePipe(int ind){
    if( pipeFlag[ind] == true ){
        for(int i=0; i<gapPos[ind]; i++){
            gotoXY(WIN_WIDTH-pipePos[ind],i+1); cout<<"   ";
        }
        for(int i=gapPos[ind]+GAP_SIZE; i<SCREEN_HEIGHT-1; i++){
            gotoXY(WIN_WIDTH-pipePos[ind],i+1); cout<<"   ";
        }
    }
}

void drawBird(){
    for(int i=0; i<2; i++){
        for(int j=0; j<6; j++){
            gotoXY(j+2,i+birdPos); cout<<bird[i][j];
        }
    }
}
void eraseBird(){
    for(int i=0; i<2; i++){
        for(int j=0; j<6; j++){
            gotoXY(j+2,i+birdPos); cout<<" ";
        }
    }
}

int collision(){
    if( pipePos[0] >= 61  ){
        if( birdPos<gapPos[0] || birdPos >gapPos[0]+GAP_SIZE ){
//          cout<< " HIT ";
//          getch();
            return 1;
        }
    }
    return 0;
}
void debug(){
//  gotoXY(SCREEN_WIDTH + 3, 4); cout<<"Pipe Pos: "<<pipePos[0];

}
void gameOver(){
    system("cls");
    cout<<endl;
    cout<<"\t\t--------------------------"<<endl;
    cout<<"\t\t-------- Game Over -------"<<endl;
    cout<<"\t\t--------------------------"<<endl<<endl;
    cout<<"\t\tPress any key to go back to menu.";
    getch();
}
void updateScore(){
    gotoXY(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
}

void instructions(){

    system("cls");
    cout<<"Instructions";
    cout<<"\n----------------";
    cout<<"\n Press spaceBar to make bird fly";
    cout<<"\n\nPress any key to go back to menu";
    getch();
}

void play(){

    birdPos = 6;
    score = 0;
    pipeFlag[0] = 1;
    pipeFlag[1] = 0;
    pipePos[0] = pipePos[1] = 4;

    system("cls");
    drawBorder();
    genPipe(0);
    updateScore();

    gotoXY(WIN_WIDTH + 5, 2);cout<<"FLAPPY BIRD";
    gotoXY(WIN_WIDTH + 6, 4);cout<<"----------";
    gotoXY(WIN_WIDTH + 6, 6);cout<<"----------";
    gotoXY(WIN_WIDTH + 7, 12);cout<<"Control ";
    gotoXY(WIN_WIDTH + 7, 13);cout<<"-------- ";
    gotoXY(WIN_WIDTH + 2, 14);cout<<" SpaceBar = jump";

    gotoXY(10, 5);cout<<"Press any key to start";
    getch();
    gotoXY(10, 5);cout<<"                      ";

    while(1){
        /* kbhit function is used to determine if a key has been pressed or not.
                        To use kbhit function in your program you should include the header file “conio. h”.
                        If a key has been pressed then it returns a non zero value otherwise returns zero. */

        if(kbhit()){
            char ch = getch();
            if(ch==32){
                if( birdPos > 3 )
                    birdPos-=3;
            }
            if(ch==27){
                break;
            }
        }

        drawBird();
        drawPipe(0);
        drawPipe(1);
        debug();
        if( collision() == 1 ){
            gameOver();
            return;
        }
        Sleep(100);
        eraseBird();
        erasePipe(0);
        erasePipe(1);
        birdPos += 1;

        if( birdPos > SCREEN_HEIGHT - 2 ){
            gameOver();
            return;
        }

        if( pipeFlag[0] == 1 )
            pipePos[0] += 2;

        if( pipeFlag[1] == 1 )
            pipePos[1] += 2;

        if( pipePos[0] >= 40 && pipePos[0] < 42 ){
            pipeFlag[1] = 1;
            pipePos[1] = 4;
            genPipe(1);
        }
        if( pipePos[0] > 68 ){
            score++;
            updateScore();
            pipeFlag[1] = 0;
            pipePos[0] = pipePos[1];
            gapPos[0] = gapPos[1];
        }

    }

}

int main()
{
    setcursor(0,0);
    srand( (unsigned)time(NULL));

//  play();

    do{
        system("cls");

     gotoXY(5,2);cout<<" -- -- ";       cout<<" |    ";           cout<<"       /\\     ";          cout<<"  ____     "; cout<<"  ____     ";        cout<<"\\    |"<<endl;
     gotoXY(5,3);cout<<"|      ";       cout<<" |    ";           cout<<"      /  \\    ";          cout<<"|     |    "; cout<<"|     |    ";        cout<<" \\   |"<<endl;
     gotoXY(5,4);cout<<"|      ";       cout<<" |    ";           cout<<"     /____\\   ";          cout<<"|_____|    "; cout<<"|_____|    ";        cout<<"  \\  |"<<endl;
     gotoXY(5,5);cout<<" -- -- ";       cout<<" |    ";           cout<<"    /      \\  ";          cout<<"|          "; cout<<"|           ";       cout<<"  \\ |"<<endl;
     gotoXY(5,6);cout<<"|      ";       cout<<" |    ";           cout<<"   /        \\ ";          cout<<"|          "; cout<<"|           ";       cout<<"    |"<<endl;
     gotoXY(5,7);cout<<"|      ";       cout<<" |_____";          cout<<" /          \\";           cout<<"|          "; cout<<"|           ";       cout<<"    |"<<"  G A M E"<<endl;


        gotoXY(12,9); cout<<"1. Start Game";
        gotoXY(12,10); cout<<"2. Instructions";
        gotoXY(12,11); cout<<"3. Quit";
        gotoXY(10,13); cout<<"Select option: ";
        char op = getche();

        if( op=='1') play();
        else if( op=='2') instructions();
        else if( op=='3') exit(0);

    }while(1);

    return 0;
}
