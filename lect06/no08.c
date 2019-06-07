#include <stdio.h>
#include <string.h>

char affine_encode(char c, int a, int b)
{
    return 'a' + (a * (c - 'a') + b) % 26;
}


int main(void)
{
    char cipher_text[50] = {};

    // input
    int cipher_len = 0;
    char c;
    while ((c = (char)getchar()) != '\n') {
        cipher_text[cipher_len] = c;
        cipher_len++;
    }
    printf("input_string(len:%d): %s\n", cipher_len, cipher_text);

    char key_str[10] = {};
    int key_str_len = 0;
    while ((c = (char)getchar()) != '\n') {
        key_str[key_str_len] = c;
        key_str_len++;
    }
    printf("key_string(len:%d): %s\n", key_str_len, key_str);

    // estimate a, b
    int a, b;
    int a_tmp, b_tmp;
    int a_candiate[13] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25};


    int find_params = 0;
    for (int ci = 0; ci <= cipher_len - key_str_len; ++ci) {
        if (find_params) {
            break;
        }

        for (int ai = 0; ai < 13; ++ai) {
            a_tmp = a_candiate[ai];
            for (int bi = 0; bi < 26; ++bi) {
                b_tmp = bi;
                int check_i = 0;
                for (int ki = 0; ki < key_str_len; ++ki) {
                    if (affine_encode(key_str[ki], a_tmp, b_tmp) != cipher_text[ci + ki]) {
                        break;
                    } else {
                        check_i++;
                    }
                }

                if (find_params == 0 && check_i == key_str_len) {
                    find_params = 1;
                    a = a_tmp;
                    b = b_tmp;
                }
            }
        }
    }

    printf("a: %d, b: %d\n", a, b);

    // make_table
    char table[26];
    for (int i = 0; i < 26; ++i) {
        table[(a * i + b) % 26] = i + 'a';
    }

    // decode
    for (int i = 0; i < cipher_len; ++i) {
        c = cipher_text[i];
        if (cipher_text[i] >= 'a' && cipher_text[i] <= 'z') {
            c = table[c - 'a'];
        }
        printf("%c", c);
    }
    printf("\n");

    return 0;
}