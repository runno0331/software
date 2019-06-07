#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void my_init_cells_byfile(FILE*,const int height,const int width,int cell[height][width]);
void my_init_cells(const int height,const int width,int cell[height][width]);
void my_print_cells(FILE *fp,int gen,const int height,const int width,int cell[height][width]);
int my_count_adjacent_cells(int i,int j,const int height,const int width,int copy[height][width]);
void my_update_cells(const int height,const int width,int cell[height][width]);

int main(int argc,char **argv){
    int gen,i,j;
    FILE *fp = stdout;
    const int height = 40;
    const int width = 70;
    int cell[height][width];

    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            cell[i][j] = 0;            
        }
    }

    /* ファイルを引数にとるか、ない場合はデフォルトの初期値を使う */
    if(argc > 2) {
        fprintf(stderr, "usage: %s [filename for init]\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    else if(argc == 2) {
        FILE *lgfile;
        if((lgfile = fopen(argv[1],"r")) != NULL) {
            my_init_cells_byfile(lgfile,height,width,cell); // ファイルによる初期化
        }else{
            fprintf(stderr,"cannot open file %s\n",argv[1]);
            exit(EXIT_FAILURE);
        }
        fclose(lgfile);
    }else{
        my_init_cells(height, width, cell); // デフォルトの初期値を使う
    }
    my_print_cells(fp, 0, height, width, cell); // 表示し、1秒休止する

    /* 世代を進める*/
    for(gen = 1;; gen++) {
        my_update_cells(height, width, cell); // セルを更新
        my_print_cells(fp, gen, height, width, cell);  // 表示し、1秒休止する
    }

    return 0;
}

void my_init_cells_byfile(FILE* lgfile,const int height,const int width,int cell[height][width]){
    int x,y;
    while(fscanf(lgfile,"%d %d",&x,&y) != EOF){
        cell[x][y] = 1;
    }
}

//cellの初期化
void my_init_cells(const int height,const int width,int cell[height][width]){
    FILE *fp;
    int x,y;
    if((fp = fopen("default.dat","r")) == NULL){
        fprintf(stderr,"error: cannot open a file.\n");
    }else{
        while(fscanf(fp,"%d %d",&x,&y) != EOF){
            cell[x][y] = 1;
        }
    }
    fclose(fp);
}

//cellの出力
void my_print_cells(FILE *fp,int gen,const int height,const int width,int cell[height][width]){
    int i,j;
    printf("generation = %d\n",gen);
    for(i=0;i<height+2;i++){
        for(j=0;j<width+2;j++){
            if(i == 0 && j == 0){
                printf("+");
            }else if(i == 0 && j == width+1){
                printf("+");
            }else if(i == height+1 && j == 0){
                printf("+");
            }else if(i == height+1 && j == width+1){
                printf("+");
            }else if(i == 0 || i == height+1){
                printf("-");
            }else if(j == 0 || j == width+1){
                printf("|");
            }else{
                if(cell[i-1][j-1] == 1){
                    printf("#");
                }else{
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    fflush(fp);
    sleep(1);
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
                }else if(w == height && copy[h][0] == 1){
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