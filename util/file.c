#include "file.h"


int main(int argc, char const *argv[]){
    FILE *file = NULL;
    str s[100];
    file = fopen("../sample_of_name.txt", "r");
    read_file(file, s, 10);
    for(int i = 0; i < 10; i++){
        printf("%s", s[i].string);    
    }
    return 0;
}

// Problem: 传递一个空数组，经过读文件获取到一个有数据的数组
str *read_file(FILE *file, str string[], int size){
    int len;
    char buff[100];
    FILE *stream;
    for(int i=0; i < size-1; i++){
        fgets(buff, 255, (FILE*) file);
        if (feof(file)) break;
        else {
            len = strlen(string[i].string);
            if (buff[len-1] == '\n') {
                len--;
                buff[len] = 0;
            }
            strcpy(string[i].string, buff);
            // printf("%s\n", buff);
        }
    }
    fclose(file);
    return string;
}
