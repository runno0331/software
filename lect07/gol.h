/*
  セルの初期化: グリッドの高さ・幅と、状態を表す2次元配列を入力とし2次元配列の状態を初期化する。初期化係数は関数内で適宜定める。現状はdefault.dat と同じ
 */
void init_cells(const int height, const int width, int cell[height][width]);

/*
 ファイルによるセルの初期化: 生きているセルの座標が記述されたファイルをもとに2次元配列の状態を初期化する
 */
void init_cells_byfile(FILE* fp, const int height, const int width, int cell[height][width]);

/*
 グリッドの描画: 世代情報とグリッドの配列等を受け取り、ファイルポインタに該当する出力にグリッドを描画する
 */
void print_cells(FILE *fp, int gen, const int height, const int width, int cell[height][width]);

/*
 着目するセルの周辺の生きたセルをカウントする関数
 */
int count_adjacent_cells(int i, int j, const int height, const int width, int cell[height][width]);

/*
 ライフゲームのルールに基づいて2次元配列の状態を更新する
 */
void update_cells(const int height, const int width, int cell[height][width]);
