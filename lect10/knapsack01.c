#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const int max_items = 1000;

typedef struct itemset
{
  int number;
  double *value;
  double *weight;
} Itemset;

Itemset *init_itemset(int number, int seed);

Itemset *load_itemset(char *filename);

void print_itemset(const Itemset *list);

void save_itemset(char *filename);

double solve(const Itemset *list, double capacity, int *flags);

double search(int index, const Itemset *list, double capacity, int *flags, double sum_v, double sum_w);

int main (int argc, char**argv)
{
  /* 引数処理: ユーザ入力が正しくない場合は使い方を標準エラーに表示して終了 */
  if (argc != 3){
    fprintf(stderr, "usage: %s <the number of items (int)> <max capacity (double)>\n",argv[0]);
    exit(1);
  }

  const int n = atoi(argv[1]);
  assert( n <= max_items );
  
  const double W = atof(argv[2]);
  
  printf("max capacity: W = %.f, # of items: %d\n",W, n);

  // 乱数シードを1にして、初期化 (ここは変更可能)
  int seed = 1; 
  Itemset *items = init_itemset(n, seed);
  print_itemset(items);

  // 品物を入れたかどうかを記録するフラグ配列
  int *flags = (int*)calloc(n, sizeof(int));

  // ソルバーで解く
  double total = solve(items, W, flags);

  // 表示する
  printf("----\nbest solution:\n");
  printf("value: %4.1f\n",total);

  return 0;
}

// 構造体をポインタで確保するお作法を確認してみよう
Itemset *init_itemset(int number, int seed)
{
  Itemset *list = (Itemset*)malloc(sizeof(Itemset));
  list->number = number;

  list->value = (double*)malloc(sizeof(double)*number);
  list->weight = (double*)malloc(sizeof(double)*number);

  srand(seed);
  for (int i = 0 ; i < number ; i++){
    list->value[i] = 0.1 * (rand() % 200);
    list->weight[i] = 0.1 * (rand() % 200 + 1);
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
    printf("v[%d] = %4.1f, w[%d] = %4.1f\n", i, list->value[i], i, list->weight[i]);
  }
  printf("----\n");
}

// ソルバーは search を index = 0 で呼び出すだけ
double solve(const Itemset *list,  double capacity, int *flags)
{
  return search(0,list,capacity,flags, 0., 0.);
}

// 再帰的な探索関数
double search(int index, const Itemset *list, double capacity, int *flags, double sum_v, double sum_w)
{
  int max_index = list->number;
  assert(index >= 0 && sum_v >= 0 && sum_w >= 0);
  // 必ず再帰の停止条件を明記する (最初が望ましい)
  if (index == max_index){
    for (int i = 0 ; i < max_index ; i++){
      printf("%d", flags[i]);
    }
    printf(", total_value = %5.1f, total_weight = %5.1f\n", sum_v, sum_w);
    return sum_v;
  }

  // 以下は再帰の更新式: 現在のindex の品物を使う or 使わないで分岐し、index をインクリメントして再帰的にsearch() を実行する
  
  flags[index] = 0;
  const double v0 = search(index+1, list, capacity, flags, sum_v, sum_w);

  flags[index] = 1;
  double v1 = v0;
  if (sum_w + list->weight[index] <= capacity){
    v1 = search(index+1, list, capacity, flags, sum_v + list->value[index], sum_w + list->weight[index]);
  }

  // 使った場合の結果と使わなかった場合の結果を比較して返す
  return (v0 > v1) ? v0 : v1;
}
