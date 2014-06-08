#include <stdio.h>
#include <stdlib.h>

#define N 16
#define MGREEN "\e[32m"
#define RCOLOR "\033[0m"

int counter=1;

typedef struct hnode* horse;
typedef struct hnode {
    int x;
    int y;
    int score;
    horse next;
} hnode;

hnode* create_horse();
void destroy_horse(horse knight);
int insert_jump(horse knight, int x, int y, int score);

void init_board(int board[N][N]);
void print_board(int board[N][N]);

void load(horse knight,int board[N][N]);
int valid_move(int x, int y, int board[N][N]);
void move(horse knight, int board[N][N]);
int min_warnscore(int x, int y, int board[N][N], int* movetox, int* movetoy);
int warnscore(int x, int y, int board[N][N]);
int end();

void clear_screen();

int main(){
    horse knight=create_horse();
    int board[N][N];
    init_board(board);
    load(knight, board);
    move(knight, board);
    print_board(board);
    destroy_horse(knight);
    return 0;
}

//Function to choose the first position on the board
void load(horse knight,int board[N][N]){
    int x=8;
    int y=8;
    int scorefirst;
    board[x][y]= counter;
    scorefirst=warnscore(x, y, board);
    insert_jump(knight, x, y, scorefirst);
}

//Horse Fuctions
hnode* create_horse(){
    hnode* aux;
    aux =malloc(sizeof(hnode));
    if(aux!=NULL){
        aux->next=NULL;
        return aux;
    }
    printf("ERROR! Returning NULL\n");
    return NULL;
}

void destroy_horse(horse knight){
    horse aux;
    while(knight->next!=NULL){
        aux=knight->next;
        free(knight);
        knight=aux;
    }
    free(knight);
}

int insert_jump(horse knight, int x, int y, int score){
    hnode* aux;
    aux=malloc(sizeof(hnode));
    if(aux!=NULL){
        aux->x=x;
        aux->y=y;
        aux->score=score;
        aux->next=knight->next;
        knight->next=aux;
        return 0;
    }
    printf("ERROR! Returning 1\n");
    return 1;
}

//Board Funcions
void init_board(int board[N][N]){
    int i;
    int k;
    for(i=0;i<N;i++){
        for(k=0;k<N;k++){
            board[i][k]=-1;
        }
    }
}

void print_board(int board[N][N]){
    int i;
    int k;
    clear_screen();
    for(i=0;i<N;i++){
        for(k=0;k<N;k++){
            if(board[i][k]!=-1){
                printf(MGREEN "%4d " RCOLOR, board[i][k]);
            } else {
                printf("%4d ", board[i][k]);
            }
        }
        printf("\n");
    }
}

//General Functions
int valid_move(int x, int y, int board[N][N]){
    if(x<0 || x>=N || y<0 || y>=N){
        return 1;
    } else if(board[x][y]!=-1){
        return 1;
    }
    return 0;
}

void move(horse knight, int board[N][N]){
    horse aux=knight->next;
    int min;
    int x;
    int y;
    min=min_warnscore(aux->x, aux->y, board, &x, &y);
    counter++;
    board[x][y]=counter;
    insert_jump(knight, x, y, min);
    if(end()==1){
        move(knight, board);
    }
}

int min_warnscore(int x, int y, int board[N][N], int* movetox, int* movetoy){
    int posx[8]={-2, -2, -1, -1, 1, 1, 2, 2};
    int posy[8]={-1, 1, -2, 2, -2, 2, -1, 1};
    int movex;
    int movey;
    int min=8;
    int score;
    int i;
    for(i=0; i<N;i++){
        movex= x+posx[i];
        movey= y+posy[i];
        if(valid_move(movex, movey, board)==0){
            score=warnscore(movex, movey, board);
            if(score<min){
                *movetox=movex;
                *movetoy=movey;
                min=score;
            }
        }
    }
    return min;
}

int warnscore(int x, int y, int board[N][N]){
    int posx[8]={-2, -2, -1, -1, 1, 1, 2, 2};
    int posy[8]={-1, 1, -2, 2, -2, 2, -1, 1};
    int movex;
    int movey;
    int i;
    int score= 0;
    for (i=0;i<8;i++){
        movex= x+posx[i];
        movey= y+posy[i];
        if(valid_move(movex, movey, board)==0){
            score++;
        }
    }
    return score;
}

int end(){
    if(counter==N*N){
        return 0;
    }
    return 1;
}

//System Functions
void clear_screen(){
    system("clear");
}