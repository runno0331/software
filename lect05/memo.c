int count(char matrix[SIZE][SIZE],int i,int j){
    int h,w,num = 0;
    for(h=i-1;h<=i+1;h++){
        for(w=j-1;w<=j+1;w++){
            if(h!=i && w!=j){
                if(h>=0 && w>=0 && h<SIZE && w<SIZE && matrix[h][w]=='*'){
                    num++;
                }else if(h == -1 && matrix[SIZE-1][w]=='*'){
                    num++;
                }else if(w == -1 && matrix[h][SIZE-1]=='*'){
                    num++;
                }else if(h == SIZE && matrix[0][w]=='*'){
                    num++;
                }else if(w == SIZE && matrix[h][0]=='*'){
                    num++;
                }
            }
        }
    }
    return num;
}
int count(char matrix[SIZE][SIZE],int i,int j){
    int h,w,num = 0;
    for(h=i-1;h<=i+1;h++){
        for(w=j-1;w<=j+1;w++){
            if(h!=i && w!=j){
                if(h == -1){
                    h = SIZE-1;
                }else if(h == SIZE){
                    h = 0;
                }
                if(w == -1){
                    w = SIZE-1; 
                }else if(w == SIZE){
                    w = 0;
                }
                if(matrix[h][w]=='*'){
                    num++;
                }
            }
        }
    }
    return num;
}

for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(rand()%100 < 13){
                matrix[i][j] = '*';
            }else{
                matrix[i][j] = ' ';
            }
        }
    }