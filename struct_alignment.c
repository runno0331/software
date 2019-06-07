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

  int id;
  char tag;
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
  printf("&s         %p\n",&s);               //128
  printf("&s.id      %p\n",&s.id);            //4
  printf("&s.name    %p\n",&s.name);          //100
  printf("&s.age     %p\n",&s.age);           //8
  printf("&s.height  %p\n",&s.height);        //8
  printf("&s.weight  %p\n",&s.weight);        //8
  printf("sizeof student1:%lu\n",sizeof(s1));
  printf("sizeof tag: %lu,id: %lu, name: %lu, age: %lu, height: %lu, weight: %lu\n",sizeof(s1.tag),sizeof(s1.id),sizeof(s1.name),sizeof(s1.age),sizeof(s1.height),sizeof(s1.weight));
  printf("&s1         %p\n",&s1);             //136
  printf("&s1.id      %p\n",&s1.id);          //4
  printf("&s1.name    %p\n",&s1.name);        //100
  printf("&s1.age     %p\n",&s1.age);         //8
  printf("&s1.height  %p\n",&s1.height);      //8
  printf("&s1.weight  %p\n",&s1.weight);      //8
  printf("&s1.tag     %p\n",&s1.tag);         //8
  printf("sizeof student2:%lu\n",sizeof(s2));
  printf("sizeof tag: %lu,id: %lu, name: %lu, age: %lu, height: %lu, weight: %lu\n",sizeof(s2.tag),sizeof(s2.id),sizeof(s2.name),sizeof(s2.age),sizeof(s2.height),sizeof(s2.weight));
  printf("&s2         %p\n",&s2);             //128
  printf("&s2.tag     %p\n",&s2.tag);         //4
  printf("&s2.id      %p\n",&s2.id);          //4
  printf("&s2.name    %p\n",&s2.name);        //100
  printf("&s2.age     %p\n",&s2.age);         //4
  printf("&s2.height  %p\n",&s2.height);      //8
  printf("&s2.weight  %p\n",&s2.weight);      //8
  /* 各構造体の中身のポインタを表示するプログラムを書く */
  /* printf で %p フォーマットを指定する*/
  return 0;
}
/*
student、student1、student2のサイズはそれぞれ128,136,128である。
id,name,height,weightはいずれの場合においても変わらない。
一方それ以外のものについて、本来のバイト数とは違ってあらわされている。
これは、double型、および構造体の先頭アドレスが8の倍数になるように
またint型においては先頭ドレスが4の倍数になるようにアライメントが
起きているためと考えられる。そのため、studentにおいてはid、name、age
までで本来108バイトであり、double型のためにageが4バイトアライメントされ
8バイトとなる。student1では、ageまでで本来108バイトでstudentと
同様の理由で8バイトとなっている。また、tagが本来1バイトのところ
構造体の先頭が8の倍数となるためのアライメントで8バイト分となっている。
student2ではtagにおけるアライメントで4バイトとなっていることを除き、
上の規則をアライメントなしで見たすため、本来のバイト数になっている。
*/
