#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void my_print_cells(int gen,const int height,const int width,int cell[height][width]);
int my_count_adjacent_cells(int i,int j,const int height,const int width,int copy[height][width]);
void my_update_cells(const int height,const int width,int cell[height][width]);

int main(){
    int gen,i,j;
    const int height = 40;
    const int width = 70;
    int cell[height][width];
    
    srand((unsigned)time(NULL));
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            if(rand()%10 == 0){
                cell[i][j] = 1;
            }else{
                cell[i][j] = 0;
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
    int i,j,n=0;
    double rate; 
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            if(cell[i][j] == 1){
                n += 1;
            }
        }
    }
    rate = (double)n/((double)height*(double)width);
    printf("generation = %d rate of survival = %lf\n",gen,rate);
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
                if(cell[i][j] == 1){
                    printf("#");
                }else{
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    usleep(300000);
}

//生きているセルのカウント（端も考慮）
int my_count_adjacent_cells(int i,int j,const int height,const int width,int copy[height][width]){
    int h,w,num = 0;
    for(h=i-1;h<i+2;h++){
        for(w=j-1;w<j+2;w++){
            if(h!=i || w!=j){
                if(h>=0 && w>=0 && h<height && w<width && copy[h][w]==1){
                    num++;
                }else if(h == -1 && w == -1 && copy[height-1][width-1] == 1){
                    num++;
                }else if(h == -1 && w == width && copy[height-1][0] == 1){
                    num++;
                }else if(h == height && w == -1 && copy[0][width-1] == 1){
                    num++;
                }else if(h == height && w == width && copy[0][0] == 1){
                    num++;
                }else if(h == -1 && copy[height-1][w] == 1){
                    num++;
                }else if(h == height && copy[0][w] == 1){
                    num++;
                }else if(w == -1 && copy[h][width-1] == 1){
                    num++;
                }else if(w == width && copy[h][0] == 1){
                    num++;
                }
                    
            }
        }
    }
    return num;
}

//更新
void my_update_cells(const int height,const int width,int cell[height][width]){
    int i,j;
    int copy[height][width];
    
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            copy[i][j] = cell[i][j];
        }
    }
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            if(my_count_adjacent_cells(i,j,height,width,copy) <= 1){
                cell[i][j] = 0;
            }else if(my_count_adjacent_cells(i,j,height,width,copy) == 3){
                cell[i][j] = 1;
            }else if(my_count_adjacent_cells(i,j,height,width,copy) >= 4){
                cell[i][j] = 0;
            }
        }
    } 
}