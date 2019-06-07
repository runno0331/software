#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// array for history recording
const int bufsize = 1000;

struct history
{
  char *command;
  struct history *next;
};
typedef struct history History;

// Structure for canvas
typedef struct
{
  int width;
  int height;
  char **canvas;
  char pen;
} Canvas;

int history_size(History *h);
int interpret_command(const char *command, Canvas *c, History *h);
History *push_history(History *h, const char *command);
History *undo(History *h, Canvas *c);

Canvas *init_canvas(int width,int height, char pen)
{
  Canvas *new = (Canvas *)malloc(sizeof(Canvas));
  new->width = width;
  new->height = height;
  new->canvas = (char **)malloc(width * sizeof(char *));

  char *tmp = (char *)malloc(width*height*sizeof(char));
  memset(tmp, ' ', width*height*sizeof(char));
  for (int i = 0 ; i < width ; i++){
    new->canvas[i] = tmp + i * height;
  }

  new->pen = pen;
  return new;
}

void reset_canvas(Canvas *c)
{
  const int width = c->width;
  const int height = c->height;
  memset(c->canvas[0], ' ', width*height*sizeof(char));
}

void print_canvas(FILE *fp, Canvas *c)
{
  const int height = c->height;
  const int width = c->width;
  char **canvas = c->canvas;
  
  // 上の壁
  fprintf(fp,"+");
  for (int x = 0 ; x < width ; x++)
    fprintf(fp, "-");
  fprintf(fp, "+\n");

  // 外壁と内側
  for (int y = 0 ; y < height ; y++) {
    fprintf(fp,"|");
    for (int x = 0 ; x < width; x++){
      const char c = canvas[x][y];
      fputc(c, fp);
    }
    fprintf(fp,"|\n");
  }
  
  // 下の壁
  fprintf(fp, "+");
  for (int x = 0 ; x < width ; x++)
    fprintf(fp, "-");
  fprintf(fp, "+\n");
  fflush(fp);
}

void free_canvas(Canvas *c)
{
  free(c->canvas[0]); //  for 2-D array free
  free(c->canvas);
  free(c);
}

void rewind_screen(FILE *fp,unsigned int line)
{
  fprintf(fp,"\033[%dA",line);
}

void clear_command(FILE *fp)
{
  fprintf(fp,"\033[2K");
}
void clear_screen(FILE *fp)
{
  fprintf(fp, "\033[2J");
}

int max(const int a, const int b)
{
  return (a > b) ? a : b;
}

void draw_line(Canvas *c, const int x0, const int y0, const int x1, const int y1)
{
  const int width = c->width;
  const int height = c->height;
  char pen = c->pen;
  
  const int n = max(abs(x1 - x0), abs(y1 - y0));
  c->canvas[x0][y0] = pen;
  for (int i = 1; i <= n; i++) {
    const int x = x0 + i * (x1 - x0) / n;
    const int y = y0 + i * (y1 - y0) / n;
    if ( (x >= 0) && (x<width) && (y >= 0) && (y < height))
      c->canvas[x][y] = pen;
  }
}

void draw_rectangle(Canvas *c, const int x0, const int y0, const int x, const int y)
{
  const int width = c->width;
  const int height = c->height;
  char pen = c->pen;
  for(int i = 0; i <= x; i++){
    if ( (x0+i >= 0) && (x0+i < width) && (y0 >= 0) && (y0 < height)){
      c->canvas[x0+i][y0] = pen;
    }
    if ( (x0+i >= 0) && (x0+i < width) && (y0+y >= 0) && (y0+y < height)){
      c->canvas[x0+i][y0+y] = pen;
    }
  }
  for(int i = 0; i <= y; i++){
    if ( (x0 >= 0) && (x0 < width) && (y0+i >= 0) && (y0+i < height))
      c->canvas[x0][y0+i] = pen;
    if ( (x0+x >= 0) && (x0+x < width) && (y0+i >= 0) && (y0+i < height))
      c->canvas[x0+x][y0+i] = pen;
  }
}

void draw_circle(Canvas *c, const int x0, const int y0, const int r)
{
    const int width = c->width;
    const int height = c->height;
    char pen = c->pen;
    for (int i = -r; i <= r; i++){
      for (int j = -r; j <= r; j++){
        if(round(sqrt(i*i)) == round(sqrt(r*r - j*j)) || round(sqrt(j*j)) == round(sqrt(r*r - i*i))){
          if ((x0+i >= 0) && (x0+i < width) && (y0+j >= 0) && (y0+j < height))
            c->canvas[x0+i][y0+j] = pen;
        }
      }
    }
}

void save_history(const char *filename, History *h)
{
  const char *default_history_file = "history.txt";
  if (filename == NULL)
    filename = default_history_file;
  
  FILE *fp;
  if ((fp = fopen(filename, "w")) == NULL) {
    fprintf(stderr, "error: cannot open %s.\n", filename);
    return;
  }
  
  for (History *p = h; p != NULL; p = p->next) {
    fprintf(fp, "%s", p->command);
  }

  printf("saved as \"%s\"\n", filename);

  fclose(fp);
}

void load_file(Canvas *c, const char *filename, History *h)
{
  const char *default_history_file = "history.txt";
  char buf[bufsize];
  int r;

  if (filename == NULL)
    filename = default_history_file;
  
  FILE *fp;
  if ((fp = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "error: cannot open %s.\n", filename);
    return;
  }

  reset_canvas(c); //initialize

  while (fgets(buf, bufsize, fp) != NULL){
      r = interpret_command(buf, c, h);
  }

  fclose(fp);
}

// Interpret and execute a command
//   return value:
//     0, normal commands such as "line"
//     1, unknown or special commands (not recorded in history[])
//     2, quit
int interpret_command(const char *command, Canvas *c, History *h)
{
  char buf[bufsize];
  strcpy(buf, command);
  buf[strlen(buf) - 1] = 0; // remove the newline character at the end

  const char *s = strtok(buf, " ");

  // The first token corresponds to command
  if (strcmp(s, "line") == 0) {
    int x0, y0, x1, y1;
    x0 = 0; y0 = 0; x1 = 0; y1 = 0; // initialize
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
    x1 = atoi(b[2]);
    y1 = atoi(b[3]);
    
    draw_line(c,x0, y0, x1, y1);
    
    return 0;
  }

  // drawing rectangle
  if (strcmp(s, "rectangle") == 0) {
    int x0, y0, x, y;             //left top & h & w
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
    draw_rectangle(c, x0, y0, x-1, y-1); //長さ１の辺を点とした
    return 0;
  }

  // drawing circle
  if (strcmp(s, "circle") == 0) {
    int x0, y0, r;                // center & radius
    x0 = 0; y0 = 0; r = 0;
    char *b[3];
    for (int i = 0 ; i < 3; i++){
      b[i] = strtok(NULL, " ");
      if (b[i] == NULL){
	      printf("the number of point is not enough.\n");
	      return 1;
      }
    }
    x0 = atoi(b[0]);
    y0 = atoi(b[1]);
    r = atoi(b[2]);
    draw_circle(c, x0, y0, r-1); 
    return 0;
  } 

  if (strcmp(s, "save") == 0) {
    s = strtok(NULL, " ");
    save_history(s, h);
    return 1;
  }

  if (strcmp(s, "load") == 0) {
    s = strtok(NULL, " ");
    load_file(c, s, h);
    return 0;
  }

  if (strcmp(s, "undo") == 0) {
    reset_canvas(c);
    h = undo(h,c);
    if (h == NULL){
      return 3;
    }
    return 1;
  }

  if (strcmp(s, "quit") == 0) {
    return 2;
  }

  printf("error: unknown command.\n");

  return 1;
}

int history_size(History *h)
{
  int hsize = 0;
  History *p;
  for (p = h; p != NULL; p = p->next)
    hsize++;
  return hsize;
}

History *push_history(History *h, const char *command)
{
  History *new = (History*)malloc(sizeof(History));
  new->command = (char*)malloc(strlen(command)+1);
  new->next = (History*)malloc(sizeof(History));
  strcpy(new->command, command);
  new->next = NULL;
  
  if (h == NULL) return new;
  
  History *current = h;
  while (current->next != NULL){
    current = current->next;
  }
  current->next = new;
  return h;
}

History *undo(History *h, Canvas *c)
{
  if (h == NULL){
    printf("No history\n");
    return NULL;
  }

  History *p = h;
  History *q = h->next;

  if (q == NULL){
    free(p->command);
    free(p);
    return NULL;
  }

  while(q->next != NULL){
    interpret_command(p->command, c, NULL);
    p = q;
    q = p->next;
  }

  interpret_command(p->command, c, NULL);
  free(q->command);
  free(q);
  p->next = NULL;

  return h;
}

int main()
{
  const int width = 70;
  const int height = 40;
  char pen = '*';
  
  FILE *fp;
  char buf[bufsize];
  fp = stdout;
  Canvas *c = init_canvas(width,height, pen);
  History *h;

  h = NULL;
  
  int hsize = 0;  // history size
  while (1) {
    hsize = history_size(h);
    printf("%d > ", hsize);
    if(fgets(buf, bufsize, stdin) == NULL) break;
    if(strlen(buf) == 1) continue;
    const int r = interpret_command(buf, c, h);
    if (r == 2) break;
    if (r == 0) {
      h = push_history(h, buf);
    }
    if (r == 3) h = NULL;
    print_canvas(fp, c);
    rewind_screen(fp, height+3); // rewind the screen to command input
    clear_command(fp); // clear the previous command
  }

  clear_screen(fp);
  free_canvas(c);
  fclose(fp);

  return 0;
}
