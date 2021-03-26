#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
void upper_str(char* str)
{
    for(; *str; str++){
        if (*str >= 'a' && *str <= 'z'){
            *str = *str - 'a' + 'A';
        }
    }
}
void lower_str(char* str)
{
    for (; *str; str++){
        if (*str >= 'A' && *str <= 'Z'){
            *str = *str - 'A' + 'a';
        }
    }
}
bool strcmp_asc(const char* str1, const char* str2)
{
    return strcmp(str2, str1) >= 0;
}
bool strcmp_dec(const char* str1, const char* str2)
{
    return strcmp(str1, str2) >= 0;
}
void merge_file(const char *src1, const char *src2, const char *dst) 
{
    FILE* psrc1 = fopen(src1, "r");
    FILE* psrc2 = fopen(src2, "r");
    FILE* pdst = fopen(dst, "w");
    if (!psrc1 || !psrc2 || !pdst){
        cout << "Open Failed\n";
        exit(254);
    }
    
    for(char* word = new char[12]; fgets(word, 12, psrc1) != NULL; word = new char[12]){
        fputs(word, pdst);
        delete[] word;
    }
    
    for(char* word = new char[12]; fgets(word, 12, psrc2) != NULL; word = new char[12]){
        fputs(word, pdst);
        delete[] word;
    }

    fclose(psrc1);
    fclose(psrc2);
    fclose(pdst);
}
void upper_file(const char *src, const char *dst) 
{
    FILE* psrc = fopen(src, "r");
    FILE* pdst = fopen(dst, "w");
    if (!psrc || !pdst){
        cout << "Open Failed\n";
        exit(254);
    }
    for(char* word = new char[12]; fgets(word, 12, psrc); word = new char[12]){
        upper_str(word);
        fputs(word, pdst);
        delete[] word;
    }
    fclose(pdst);
    fclose(psrc);
}
void lower_file(const char *src, const char *dst)
{
    FILE* psrc = fopen(src, "r");
    FILE* pdst = fopen(dst, "w");
    if (!psrc || !pdst){
        cout << "Open Failed\n";
        exit(254);
    }
    for(char* word = new char[12]; fgets(word, 12, psrc); word = new char[12]){
        lower_str(word);
        fputs(word, pdst);
        delete[] word;
    }
    fclose(pdst);
    fclose(psrc);
}
void sort_inc_file(const char *src, const char *dst)
{
    FILE* psrc = fopen(src, "r");
    FILE* pdst = fopen(dst, "w");
    if (!psrc || !pdst){
        cout << "Open Failed\n";
        exit(254);
    }
    char* words[101];
    for (int i = 0; i <= 100; i++){
        char* p = new char[12];
        words[i] = p;
    }
    int i = 0;
    for (; fgets(words[i], 12, psrc) != NULL; i++);
    sort(words, words + i, strcmp_asc);
    for(int j = 0; j < i; j++){
        fputs(words[j], pdst);
    }
    fclose(pdst);
    fclose(psrc);
}
void sort_dec_file(const char *src, const char *dst)
{
    FILE* psrc = fopen(src, "r");
    FILE* pdst = fopen(dst, "w");
    if (!psrc || !pdst){
        cout << "Open Failed\n";
        exit(254);
    }
    char* words[101];
    int i = 0;
    for (; i <= 100; i++){
        char* p = new char[12];
        words[i] = p;
    }
    i = 0;
    for (; fgets(words[i], 12, psrc) != NULL; i++);
    sort(words, words + i, strcmp_dec);
    for(int j = 0; j < i; j++){
        fputs(words[j], pdst);
    }
    fclose(pdst);
    fclose(psrc);
}


#include "test.hpp"
int main()
{
    test();
    return 0;
}