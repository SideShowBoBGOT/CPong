#include<conio.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<Windows.h>
#include <process.h>


const int WIDTH = 31;
const int HEIGHT = 20;
enum Direction
{
    UpRight = 0,
    DownRight = 1,
    UpLeft = 2,
    DownLeft = 3,
};
struct Player {
    int headX;
    int headY;
    int score;
};
struct Ball {
    int ballX;
    int ballY;
    int direction;
};
void DrawDungeon(int width, int height, struct Player *p1, struct Player *p2, struct Ball *b);
void Input(struct Player *p1, struct Player *p2);
void LogicPlayer(struct Player* p1, struct Player* p2);
void LogicBall(struct Player* p1, struct Player* p2, struct Ball* b);
void MoveBall(struct Ball* b);
int main()
{
    time_t t;
    srand((unsigned)time(&t));

    struct Player p1;
    p1.headX = 2;
    p1.headY = HEIGHT/2-1;
    struct Player p2;
    p2.headX = WIDTH-4;
    p2.headY = HEIGHT/2-1;
    struct Ball b;
    b.ballX = WIDTH / 2;
    b.ballY = HEIGHT / 2;
    b.direction = rand()%3;
    
    p1.score = 0;
    p2.score = 0;

    int gameIsLaunched=1;
    int addThreadIsOn = 1;
    _beginthread(MoveBall, NULL, (void*)&b);

    while(gameIsLaunched==1){
        Input(&p1, &p2);
        LogicPlayer(&p1, &p2);
        
        LogicBall(&p1, &p2, &b);
        DrawDungeon(30, 20, &p1, &p2, &b);
        
        system("cls");
    }
    
    _endthread();
    return 0;
}
void MoveBall(struct Ball* b) {
    while(1){
        if ((*b).direction == UpLeft) {
            (*b).ballX--;
            (*b).ballY--;
        }
        if ((*b).direction == UpRight) {
            (*b).ballX++;
            (*b).ballY--;
        }
        if ((*b).direction == DownLeft) {
            (*b).ballX--;
            (*b).ballY++;
        }
        if ((*b).direction == DownRight) {
            (*b).ballX++;
            (*b).ballY++;
        }
        Sleep(150);
    }
}
void LogicBall(struct Player *p1, struct Player *p2, struct Ball *b){
    time_t t;
    srand((unsigned)time(&t));
    if    (((*b).ballX == (*p1).headX + 1 && (*b).ballY == (*p1).headY)
        || ((*b).ballX == (*p1).headX + 1 && (*b).ballY == (*p1).headY + 1)
        || ((*b).ballX == (*p1).headX + 1 && (*b).ballY == (*p1).headY + 2)
        || ((*b).ballX == (*p1).headX && (*b).ballY == (*p1).headY - 1)
        || ((*b).ballX == (*p1).headX && (*b).ballY == (*p1).headY + 3)) {
        if ((*b).direction == UpLeft)
        {
            (*b).direction = rand() % 2;
        }
        if ((*b).direction == DownLeft)
        {
            (*b).direction = rand() % 2;
        }
    }
    if    (((*b).ballX == (*p2).headX - 1 && (*b).ballY == (*p2).headY)
        || ((*b).ballX == (*p2).headX - 1 && (*b).ballY == (*p2).headY + 1)
        || ((*b).ballX == (*p2).headX - 1 && (*b).ballY == (*p2).headY + 2)
        || ((*b).ballX == (*p2).headX && (*b).ballY == (*p2).headY - 1)
        || ((*b).ballX == (*p2).headX && (*b).ballY == (*p2).headY + 3)) {
        if ((*b).direction == UpRight)
        {
            (*b).direction = 2 + (rand()%2);
        }
        if ((*b).direction == DownRight) {
            (*b).direction = 2 + (rand() % 2);
        }
    }
    if ((*b).ballY == 1 && ((*b).direction == UpRight))
        (*b).direction = DownRight;
    if ((*b).ballY == 1 && ((*b).direction == UpLeft))
        (*b).direction = DownLeft;
    if ((*b).ballY == HEIGHT-2 && ((*b).direction == DownRight))
        (*b).direction = UpRight;
    if ((*b).ballY == HEIGHT-2 && ((*b).direction == DownLeft))
        (*b).direction = UpLeft;
        
    if ((*b).ballX == 1) {
        (*p2).score++;
        (*b).ballX = WIDTH / 2;
        (*b).ballY = HEIGHT / 2;
        (*b).direction = rand() % 3;
    }
    if ((*b).ballX == WIDTH - 1) {
        (*p1).score++;
        (*b).ballX = WIDTH / 2;
        (*b).ballY = HEIGHT / 2;
        (*b).direction = rand() % 3;
    }
    if ((*b).ballX<0 || (*b).ballY<0 || (*b).ballX>WIDTH || (*b).ballY>HEIGHT) {
        (*b).ballX = WIDTH / 2;
        (*b).ballY = HEIGHT / 2;
    }
}
void LogicPlayer(struct Player* p1, struct Player* p2) {
    
    if ((*p1).headY < 1) {
        (*p1).headY = 1;
    }
    if ((*p1).headY + 3 > HEIGHT - 1) {
        (*p1).headY = HEIGHT - 4;
    }
    if ((*p2).headY < 1) {
        (*p2).headY = 1;
    }
    if ((*p2).headY + 3 > HEIGHT - 1) {
        (*p2).headY = HEIGHT - 4;
    }

}
void Input(struct Player *p1, struct Player *p2) {
    if (_kbhit()) {
        char ch = _getch();
        switch (ch) {
        case 'w':
            (*p1).headY--;
            break;
        case 's':
            (*p1).headY++;
            break;
        case 'o':
            (*p2).headY--;
            break;
        case 'l':
            (*p2).headY++;
        }
    }
}
void DrawDungeon(int width, int height, struct Player *p1, struct Player *p2, struct Ball *b) {
    struct Player P1 = *p1;
    struct Player P2 = *p2;
    struct Ball B = *b;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width;j++) {
            
                if (i == 0||i==height-1) {

                    if (i == 0 && j == width - 1) {
                        printf("#\tX: %d\tY: %d\n", B.ballX, B.ballY);
                    }
                    else {
                        printf("%c", '#');
                        if (j == width - 1) {
                            printf("\n");
                        }
                    }
                }
            else {
                
                if (j == 0 || j == width - 1) {
                    printf("%c", '#');
                }
                else {

                    if ((i == P1.headY && j == P1.headX) || (i == P2.headY && j == P2.headX)
                        || (i == P1.headY + 1 && j == P1.headX) || (i == P2.headY + 1 && j == P2.headX)
                        || (i == P1.headY + 2 && j == P1.headX) || (i == P2.headY + 2 && j == P2.headX)
                        || (j == (width - 1) / 2 + 1)||(i==1&&j==14)||(i==1&&j==17)||(B.ballX==j&&B.ballY==i)) {
                        if (B.ballX == j && B.ballY == i) {
                            printf("@");
                            continue;
                        }
                        if ((j == (width - 1) / 2 + 1)) {
                            printf("|");
                        }
                        if ((i == P1.headY && j == P1.headX) || (i == P2.headY && j == P2.headX)
                            || (i == P1.headY + 1 && j == P1.headX) || (i == P2.headY + 1 && j == P2.headX)
                            || (i == P1.headY + 2 && j == P1.headX) || (i == P2.headY + 2 && j == P2.headX)) {
                            printf("$");
                        }
                        if (i == 1 && j == 14) {
                            printf("%d", P1.score);
                        }
                        if (i == 1 && j == 17) {
                            printf("%d", P2.score);
                        }
                    }
                    else{
                        
                        
                            printf(" ");
                    }
                    
                }
                if (j == width - 1) {
                    printf("\n");
                }
            }
        }
    }
}



