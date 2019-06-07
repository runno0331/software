/*
草とそれを食べる草食動物からなる。草は自然に十字方向に増えていく。一方、草食動物は
草を食べて一定の確率で増殖する。また草食動物は寿命で消滅もしくは突然死で消滅する。
草が増える割合に対して、あまり動物のほうが増えない。寿命が短いとあまり広がらない。
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define LIFE 2 //寿命
#define NEW_LIFE 80 //草食動物が生まれる確率
#define DEATH 10 //突然死の確率

void my_print_cells(int gen,const int height,const int width,int cell[height][width]);
int my_count_adjacent_cells(int i,int j,const int height,const int width,int copy[height][width]);
void my_update_cells(const int height,const int width,int cell[height][width]);
void grow_grass(int h,int w,const int height,const int width,int copy[height][width],int cell[height][width]);
void eat_grass(int h,int w,const int height,const int width,int copy[height][width],int cell[height][width]);

int main(){
    int gen,i,j;
    const int height = 40;
    const int width = 70;
    int cell[height][width];
    
    srand((unsigned)time(NULL));
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            cell[i][j] = 0;
            if(rand()%100 < 3){
                cell[i][j] += 10;//草
            }else if(rand()%100 < NEW_LIFE-60){
                cell[i][j] += LIFE;//草食動物
            }
        }
    }

    my_print_cells(0, height, width, cell); // 表示し、休止する

    /* 世代を進める*/
    for(gen = 1;; gen++) {
        my_update_cells(height, width, cell); // セルを更新
        my_print_cells(gen, height, width, cell);  // 表示し、休止する
    }

    return 0;
}

//cellの出力
void my_print_cells(int gen,const int height,const int width,int cell[height][width]){
    int i,j,g=0,h=0,c=0;
    double grate,hrate,crate; 
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            if(cell[i][j] == 10){
                g++;
            }else if(cell[i][j] > 0){
                h++;
            }
        }
    }
    grate = (double)g/((double)height*(double)width);
    hrate = (double)h/((double)height*(double)width);
    printf("generation = %d rate of grass = %lf rate of herb = %lf\n",gen,grate,hrate);
    for(i=-1;i<height+1;i++){
        for(j=-1;j<width+1;j++){
            if(i == -1 && j == -1){
                printf("+");
            }else if(i == -1 && j == width){
                printf("+");
            }else if(i == height && j == -1){
                printf("+");
            }else if(i == height && j == width){
                printf("+");
            }else if(i == -1 || i == height){
                printf("-");
            }else if(j == -1 || j == width){
                printf("|");
            }else{
                if(cell[i][j]==10){
                    printf("\x1b[32m");
                    printf("w");//草
                    printf("\x1b[39m");
                }else if(cell[i][j] > 0){
                    printf("@");//草食動物
                }else if(cell[i][j] == 0){
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    sleep(1);
}

//更新
void my_update_cells(const int height,const int width,int cell[height][width]){
    int i,j,n,m;
    int copy[height][width];
    
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            copy[i][j] = cell[i][j];
        }
    }
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            if(copy[i][j]==10){//草の場合
                grow_grass(i,j-1,height,width,copy,cell);
                grow_grass(i,j+1,height,width,copy,cell);
                grow_grass(i-1,j,height,width,copy,cell);
                grow_grass(i+1,j,height,width,copy,cell);
            }else if(copy[i][j]>0){//草食動物の場合
                if(rand()%100 < DEATH){
                    cell[i][j] = 0;
                    break;
                }
                for(n=-1;n<=1;n++){
                    for(m=-1;m<=1;m++){
                        if((i+n)!=i && (j+m)!=j){
                            eat_grass(i+n,j+m,height,width,copy,cell);
                        }
                    }
                }
            }
        }
    }
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            if(copy[i][j]>0 && copy[i][j]<=LIFE && cell[i][j]>0){
                cell[i][j]--;
            }
        }
    }
}

//草を生やす
void grow_grass(int h,int w,const int height,const int width,int copy[height][width],int cell[height][width]){
    if(h>=0 && w>=0 && h<height && w<width && cell[h][w]==0 && copy[h][w]==0){
        cell[h][w] = 10;
    }else if(h == -1 && w == -1 && cell[height-1][width-1]==0 && copy[height-1][width-1]==0){
        cell[height-1][width-1] = 10;
    }else if(h == -1 && w == width && cell[height-1][0]==0 && copy[height-1][0] == 0){
        cell[height-1][0] = 10;
    }else if(h == height && w == -1 && cell[0][width-1]==0 && copy[0][width-1] == 0){
        cell[0][width-1] = 10;
    }else if(h == height && w == width && cell[0][0]==0 && copy[0][0] == 0){
        cell[0][0] = 10;
    }else if(h == -1 && cell[height-1][w]==0 && copy[height-1][w]==0){
        cell[height-1][w] = 10;
    }else if(h == height && cell[0][w]==0 && copy[0][w]==0){
        cell[0][w] = 10;
    }else if(w == -1 && cell[h][width-1]==0 && copy[h][width-1]==0){
        cell[h][width-1] = 10;
    }else if(w == width && cell[h][0]==0 && copy[h][0] == 0){
        cell[h][0] = 10;
    }
}

//草を食べて増殖、増えないこともある
void eat_grass(int h,int w,const int height,const int width,int copy[height][width],int cell[height][width]){
    if(h>=0 && w>=0 && h<height && w<width && copy[h][w]==10){
        if(rand()%100 < NEW_LIFE){
            cell[h][w] = LIFE;
        }else{
            cell[h][w] = 0;
        }
    }else if(h == -1 && w == -1 && copy[height-1][width-1]==10){
        if(rand()%100 < NEW_LIFE){
            cell[height-1][width-1] = LIFE;
        }else{
            cell[height-1][width-1] = 0;
        }
    }else if(h == -1 && w == width && copy[height-1][0]==10){
        if(rand()%100 < NEW_LIFE){
            cell[height-1][0] = LIFE;
        }else{
            cell[height-1][0] = 0;
        }
    }else if(h == height && w == -1 && copy[0][width-1]==10){
        if(rand()%100 < NEW_LIFE){
            cell[0][width-1] = LIFE;
        }else{
            cell[0][width-1] = 0;
        }
    }else if(h == height && w == width && copy[0][0]==10){
        if(rand()%100 < NEW_LIFE){
            cell[0][0] = LIFE;
        }else{
            cell[0][0] = 0;
        }
    }else if(h == -1 && copy[0][w]==10){
        if(rand()%100 < NEW_LIFE){
            cell[height-1][w] = LIFE;
        }else{
            cell[height-1][w] = 0;
        }
    }else if(h == height && copy[0][w]==10){
        if(rand()%100 < NEW_LIFE){
            cell[0][w] = LIFE;
        }else{
            cell[0][w] = 0;
        }
    }else if(w == -1 && copy[h][width-1]==10){
        if(rand()%100 < NEW_LIFE){
            cell[h][width-1] = LIFE;
        }else{
            cell[h][width-1] = 0;
        }
    }else if(w == width && copy[h][0]==10){
        if(rand()%100 < NEW_LIFE){
            cell[h][0] = LIFE;
        }else{
            cell[h][0] = 0;
        }
    }
}

