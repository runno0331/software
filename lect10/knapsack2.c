#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const int max_items = 1000;

typedef struct itemset
{
  int number;
  double *value;
  int *weight;
} Itemset;

Itemset *init_itemset(int number, int seed);

Itemset *load_itemset(char *filename);

void print_itemset(const Itemset *list);

void save_itemset(char *filename);

double max(double a, double b);

double dp_solve(const Itemset *list, int capacity);

int main (int argc, char**argv)
{
  /* 引数処理: ユーザ入力が正しくない場合は使い方を標準エラーに表示して終了 */
  if (argc != 3){
    fprintf(stderr, "usage: %s <the number of items (int)> <max capacity (double)>\n",argv[0]);
    exit(1);
  }

  const int n = atoi(argv[1]);
  assert( n <= max_items );
  
  const int W = atoi(argv[2]);
  
  printf("max capacity: W = %d, # of items: %d\n",W, n);

  // 乱数シードを1にして、初期化 (ここは変更可能)
  int seed = 1; 
  Itemset *items = init_itemset(n, seed);
  print_itemset(items);

  // ソルバーで解く
  double total = dp_solve(items, W);

  // 表示する
  printf("----\nbest solution:\n");
  printf("value: %4.1f\n",total);

  return 0;
}

// 構造体を初期化
Itemset *init_itemset(int number, int seed)
{
  Itemset *list = (Itemset*)malloc(sizeof(Itemset));
  list->number = number;

  list->value = (double*)malloc(sizeof(double)*number);
  list->weight = (int*)malloc(sizeof(double)*number);

  srand(seed);
  for (int i = 0 ; i < number ; i++){
    list->value[i] = 0.1 * (rand() % 20 + 1);
    list->weight[i] = rand() % 20 + 1;
  }
  
  return list;
}

// itemset の free関数
void free_itemset(Itemset *list)
{
  free(list->value);
  free(list->weight);
  free(list);
}

// 表示関数
void print_itemset(const Itemset *list)
{
  int n = list->number;
  for(int i = 0 ; i < n ; i++){
    printf("v[%d] = %4.1f, w[%d] = %d\n", i, list->value[i], i, list->weight[i]);
  }
  printf("----\n");
}

double max(double a, double b)
{
  return (a >= b) ? a : b;
}

// 動的計画法によるソルバー
double dp_solve(const Itemset *list, int capacity)
{
  int i, j;
  const int number = list->number;
  double **table = (double**)malloc(sizeof(double*)*(number+1));
  double *tmp = (double*)malloc(sizeof(double)*(number+1)*(capacity+1));
  for(i = 0; i < number+1; i++){
      table[i] = tmp + i * (capacity+1);
  }
  
  for(i = 0; i < number+1; i++){
    for(j = 0; j < capacity+1; j++){
      if(i == 0){        // 品物数が0の時
        table[i][j] = 0;
      }else if(j == 0){        // 重量制限が0のとき
        table[i][j] = 0;
      }else if(j - list->weight[i-1] < 0){ // (i-1)番目の品物をナップザックに入れる容量がないとき
        table[i][j] = table[i-1][j];
      }else{
        table[i][j] = max(table[i-1][j], table[i-1][j - list->weight[i-1]] + list->value[i-1]);
      }
    }
  }
  const double total = table[number][capacity];

  // メモリ解放
  free(table[0]);
  free(table);

  return total; 
}

/*
動的計画法においては表を作ってそれを埋めていくことで詰められる最大価値の
荷物を求める。表の一マスをうめる操作の計算量はO(1)であるから、表のマスを
すべて埋める計算量はナップザックの容量をW、品物数をnとするとO(nW)となる。
したがって動的計画法によりナップザック問題を解く作業の計算量もO(nW)となる。
今回用いた表の要素table[i][j]に入るのは、品物のうち0~i-1番目のものを使って
重量制限jのナップザックに詰めたときの最大価値をである。
*/