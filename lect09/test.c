if (strcmp(s, "copy") == 0){
    int x0, y0, x, y;             //copying rectangle left top & h & w
    x0 = 0; y0 = 0; x = 0; y = 0; // initialize 
    char *b[4];
    for (int i = 0 ; i < 4; i++){
      b[i] = strtok(NULL, " ");
      if (b[i] == NULL){
	      printf("the number of point is not enough.\n");
	      return 1;
      }
    }
    x0 = atoi(b[0]);
    y0 = atoi(b[1]);
    x = atoi(b[2]);
    y = atoi(b[3]);
    copy(c, x0, y0, x, y);
    return 0;
}

if (strcmp(s, "paste") == 0){
    int x0, y0;             //pasting rectangle to left top
    x0 = 0; y0 = 0          // initialize 
    char *b[2];
    for (int i = 0 ; i < 2; i++){
      b[i] = strtok(NULL, " ");
      if (b[i] == NULL){
	      printf("the number of point is not enough.\n");
	      return 1;
      }
    }
    x0 = atoi(b[0]);
    y0 = atoi(b[1]);
    paste(c, x0, y0);
    return 0;
}

void copy(Canvas *c,const int x0, const int y0, const int x, const int y)
{
    free(c->copy[0]);
    free(c->copy);
    c->copy = (char**)malloc(sizeof(char *) * x);
    for(int i = 0; i < x; i++){
        c->copy[i] = (char *)malloc(sizeof(char) * y);
    }
    memset(copy[0], NULL, x*y);

    const int width = c->width;
    const int height = c->height;
    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            if ((x0+i >= 0) && (x0+i < width) && (y0+j >= 0) && (y0+j < height)){
                c->copy[i][j] = c->canvas[x0+i][y0+j];
            }
        }
    }
    
}

void paste(Canvas c, const int x0, const int y0)
{
    const int n = sizeof(copy)
    for (int i = 0; i < n/sizeof(copy[0]); i++){
        for (int j = 0; j < sizeof(copy[0]); j++){
            if ((x0+i >= 0) && (x0+i < width) && (y0+j >= 0) && (y0+j < height)){
                if (copy[i][j] != NULL){
                    c->canvas[x0+i][y0+j] = c->copy[i][j];
                }
            }
        }
    }
}