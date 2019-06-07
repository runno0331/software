/* 境界つきで、グリッドを表示するプログラム */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  int gen;
  const int height = 40;
  const int width = 70;
  int cell[height][width] = {0};

  /* 適当に何箇所か生きているセルを置く */
  
  cell[20][20] = 1;
  cell[20][21] = 1;
  cell[20][22] = 1;

  //上の壁
  FILE *fp = stdout; // 標準出力に出す
  fprintf(fp,"[calibration]\n"); // この場合 (fp = stdout), printfと同じ
  fprintf(fp,"+");
  for (int i = 0 ; i < width ; i++)
    fprintf(fp, "-");
  fprintf(fp, "+\n");
  
  /* 外壁と 内側のゲーム部分 */
  for (int i = 0; i < height; i++) {
    fprintf(fp,"|");
    for (int j = 0; j < width; j++) {
      const char c = (cell[i][j] == 1) ? '#' : ' ';
      fputc(c, fp);
    }
    fprintf(fp,"|\n");
  }

  // 下の壁
  fprintf(fp, "+");
  for (int i = 0 ; i < width ; i++)
    fprintf(fp, "-");
  fprintf(fp, "+\n");
  fflush(fp); // バッファされている文字列を出力する
  
  return 0;
}
