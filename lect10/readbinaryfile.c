#include <stdio.h>
#include <stdlib.h>

int main()
{
  // バイナリファイルを出力してみる
  // テキストファイルに出力した場合と比較

  int size = 1000000;
  double *d1 = (double*)malloc(sizeof(double)*size); // とりあえず100万確保
  double *d2 = (double*)malloc(sizeof(double)*size);

  char *s = "data.txt";// ひとまずテキストでだしてみる
  FILE *fp;
  if((fp = fopen(s,"r")) == NULL){
    fprintf(stderr,"connot open file %s.\n",s);
    exit(1);
  }

  for(int i = 0 ; i < size ; i++)
    fscanf(fp,"%lf\n",&d1[i]);
  fclose(fp);

  char *s2 = "data.txt";// ひとまずテキストでだしてみる
  fp = fopen(s2,"rb");
  fread(d2,sizeof(double),size,fp);
  fclose(fp);
  

  for(int i = 0 ; i < size ; i++)
    printf("%f %f\n",d1[i],d2[i]);
}
