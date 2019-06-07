int main(int argc, const char * argv[]) {
  int i;
  for(i=0; i<argc; i++){
    printf("%s\n",argv[i]);
  }
  return 0;
}

11432677160

str_toupper()で返されるのが配列の先頭のアドレスであるため、printf()で配列全体を出力できないため。
str_toupper()でchar *dstと宣言し、mallocで動的メモリの確保行うと正しい出力が得られる。

128

1111
10000000
10001110010001
1111110000001111011
1011001111010010010

11122021112
205355
1144208
1a72a8
3b4028
b34d7
fffff

9
7
9