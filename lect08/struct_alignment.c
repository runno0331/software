#include <stdio.h>

struct student
{
  int id;
  char name[100];
  int age;
  double height;
  double weight;
};

struct tagged_student1
{
  int id;
  char name[100];
  int age;
  double height;
  double weight;
  char tag;
};

struct tagged_student2
{
  char tag;
  int id;
  char name[100];
  int age;
  double height;
  double weight;
};

int main (int argc, char**argv)
{
  struct student a;
  struct student s;
  struct tagged_student1 s1;
  struct tagged_student2 s2;
  printf("&a         %p\n",&a);
  printf("sizeof student:%lu\n",sizeof(s));
  printf("sizeof id: %lu, name: %lu, age: %lu, height: %lu, weight: %lu\n",sizeof(s.id),sizeof(s.name),sizeof(s.age),sizeof(s.height),sizeof(s.weight));
  printf("&s         %p\n",&s);
  printf("&s.id      %p\n",&s.id);
  printf("&s.name    %p\n",&s.name);
  printf("&s.age     %p\n",&s.age);
  printf("&s.height  %p\n",&s.height);
  printf("&s.weight  %p\n",&s.weight);
  printf("sizeof student:%lu\n",sizeof(s1));
  printf("sizeof tag: %lu,id: %lu, name: %lu, age: %lu, height: %lu, weight: %lu\n",sizeof(s1.tag),sizeof(s1.id),sizeof(s1.name),sizeof(s1.age),sizeof(s1.height),sizeof(s1.weight));
  printf("&s1         %p\n",&s1);
  printf("&s1.id      %p\n",&s1.id);
  printf("&s1.name    %p\n",&s1.name);
  printf("&s1.age     %p\n",&s1.age);
  printf("&s1.height  %p\n",&s1.height);
  printf("&s1.weight  %p\n",&s1.weight);
  printf("&s1.tag     %p\n",&s1.tag);
  printf("sizeof student:%lu\n",sizeof(s));
  printf("sizeof tag: %lu,id: %lu, name: %lu, age: %lu, height: %lu, weight: %lu\n",sizeof(s2.tag),sizeof(s2.id),sizeof(s2.name),sizeof(s2.age),sizeof(s2.height),sizeof(s2.weight));
  printf("&s2         %p\n",&s2);
  printf("&s2.tag     %p\n",&s2.tag);
  printf("&s2.id      %p\n",&s2.id);
  printf("&s2.name    %p\n",&s2.name);
  printf("&s2.age     %p\n",&s2.age);
  printf("&s2.height  %p\n",&s2.height);
  printf("&s2.weight  %p\n",&s2.weight);
  /* 各構造体の中身のポインタを表示するプログラムを書く */
  /* printf で %p フォーマットを指定する*/
  return 0;
}
/*

*/
