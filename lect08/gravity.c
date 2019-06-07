#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

/* 今回の設定を構造体で記述*/
struct condition
{
  int width; 
  int height;
  double G; // gravity constant
};
  
struct star
{
  double m;   // mass
  double x;   // position_x
  double y;   // position_y
  double vx;  // velocity_x
  double vy;  // velocity_y
};

struct star stars[] = {
  { 1.0, -10.0, 0.0, 0.0, 0.0},
  { 0.5,  10.0, 0.0, 0.2, 0.2} 
};

const int nstars = sizeof(stars) / sizeof(struct star);

void plot_stars(FILE *fp, const double t,struct condition cond)
{
  int width = cond.width;
  int height = cond.height;
  char space[width][height];
  
  memset(space, ' ', sizeof(space));
  for (int i = 0; i < nstars; i++) {
    const int x = width  / 2 + stars[i].x;
    const int y = height / 2;
    if (x < 0 || x >= width)  continue;
    if (y < 0 || y >= height) continue;
    char c = (stars[i].m >= 1.0)?'O':'o'; // 質量が大きい場合は表示を変える
    space[x][y] = c;
  }

  fprintf(fp, "----------\n");
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++)
      fputc(space[x][y], fp);
    fputc('\n', fp);
  }
  fflush(fp);

  printf("t = %5.1f", t);
  for (int i = 0; i < nstars; i++) 
    printf(", stars[%d].x = %7.2f, stars[%d].y = %7.2f", i, stars[i].x, i, stars[i].y);
  printf("\n");
}

void update_velocities(const double dt,struct condition cond)
{
  int i, j;
  for (i = 0; i < nstars; i++) {
    double ax = 0, ay = 0;
    for(j = 0;j < nstars; j++){
      if(i != j){
        ax += (stars[j].x-stars[i].x)*stars[j].m*cond.G/fabs(pow(stars[i].x-stars[j].x,3));
        ay += (stars[j].y-stars[i].y)*stars[j].m*cond.G/fabs(pow(stars[i].y-stars[j].y,3));
      }
    }
    /* 何も書いていないと初期値の初速になるのでここに更新ルールを記述  */

    stars[i].vx += ax * dt;
    stars[i].vy += ay * dt;
  }
}

void update_positions(const double dt)
{
  for (int i = 0; i < nstars; i++) {
    stars[i].x += stars[i].vx * dt;
    stars[i].y += stars[i].vy * dt;
  }
}

int main()
{
  const char *filename = "space.txt";
  FILE *fp;
  if ((fp = fopen(filename, "a")) == NULL) {
    fprintf(stderr, "error: cannot open %s.\n", filename);
    return 1;
  }

  const double dt = 1.0;
  const double stop_time = 400;

  struct condition cond;
  cond.height = 100;
  cond.width = 100;
  cond.G = 1.0;

  double t = 0.;
  for (int i = 0; t <= stop_time; i++) {
    t = i * dt;
    update_velocities(dt,cond);
    update_positions(dt);
    if (i % 10 == 0) {
      plot_stars(fp, t, cond);
      usleep(200 * 1000);
    }
  }

  fclose(fp);

  return 0;
}
