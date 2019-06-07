#include <stdio.h>
#include <stdlib.h>
#include "gol.h"



int main(int argc, char **argv)
{
  int gen;
  FILE *fp = stdout;
  const int height = 40;
  const int width = 70;
  int cell[height][width] = {0};

  /* ファイルを引数にとるか、ない場合はデフォルトの初期値を使う */
  if ( argc > 2 ) {
    fprintf(stderr, "usage: %s [filename for init]\n",argv[0]);
    exit(EXIT_FAILURE);
  }
  else if (argc == 2) {
    FILE *lgfile;
    if ( (lgfile = fopen(argv[1],"r")) != NULL ) {
      init_cells_byfile(lgfile,height,width,cell); // ファイルによる初期化
    }
    else{
      fprintf(stderr,"cannot open file %s\n",argv[1]);
      exit(EXIT_FAILURE);
    }
    fclose(lgfile);
  }
  else{
    init_cells(height, width, cell); // デフォルトの初期値を使う
  }

  print_cells(fp, 0, height, width, cell); // 表示し、1秒休止する

  /* 世代を進める*/
  for (gen = 1;; gen++) {
    update_cells(height, width, cell); // セルを更新
    print_cells(fp, gen, height, width, cell);  // 表示し、1秒休止する
  }

  return 0;
}
