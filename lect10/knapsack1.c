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

//標準入力としてバイナリファイル名、ナップザックの容量を取る
int main (int argc, char**argv)
{
  /* 引数処理: ユーザ入力が正しくない場合は使い方を標準エラーに表示して終了 */
  if (argc != 3){
    fprintf(stderr, "usage: %s <name of binary file (char*)> <max capacity (double)>\n",argv[0]);
    exit(1);
  }

  //itemsの初期化
  FILE *fp;
  char *s = argv[1];
  if((fp = fopen(s,"rb")) == NULL){
    fprintf(stderr,"cannot open file %s.\n",s);
    exit(1);
  }

  int n;
  fread(&n,sizeof(int),1,fp);
  Itemset *items = (Itemset*)malloc(sizeof(Itemset));
  items->number = n;

  items->value = (double*)malloc(sizeof(double)*n);
  items->weight = (double*)malloc(sizeof(double)*n);

  for (int i = 0 ; i < n ; i++){
    fread(&items->value[i],sizeof(double),1,fp);
    fread(&items->weight[i],sizeof(double),1,fp);
  }
  fclose(fp);

  const int W = atof(argv[2]);

  printf("max capacity: W = %.f, # of items: %d\n",W, n);

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