#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct data{
    char name[21];
    char gender;
    char hobby[5][36];
    char phone_number[11];
    char area[16];
    char target;
    int age;
    float height;
    char zodiac[21];
    char income[11];
    char job[41];
    int index_of_area;
    int score;
    char self_introduction[151];
} Data;

int read_file(Data *person);

int main(){
    int data_amount = 0;
    Data person[1000];
    data_amount = read_file(person);
    printf("%d\n", data_amount);                        // 看讀到的人數對不對
    printf("%lf", (double)clock() / CLOCKS_PER_SEC);    // 看整個程式執行時間(/s)
}

int read_file(Data *person){
    int i = 0;                                    // 檔名要記得改自己txt的名字喔
    const char *filename = "apin.txt";
    FILE *input_file = fopen(filename, "r");
    if (!input_file){
        exit(EXIT_FAILURE);
    }
    while (fscanf(input_file, "%s %c %s %s %s %s %s %s %s %c %d %f %s %s %d %s "
    , person[i].name
    , &person[i].gender
    , person[i].hobby[0]
    , person[i].hobby[1]
    , person[i].hobby[2]
    , person[i].hobby[3]
    , person[i].hobby[4]
    , person[i].phone_number
    , person[i].area
    , &person[i].target
    , &person[i].age
    , &person[i].height
    , person[i].zodiac
    , person[i].income
    , &person[i].index_of_area
    , person[i].job) != EOF){
        fgets(person[i].self_introduction, 151, input_file);
        i++;
    }
    fclose(input_file);
    int temp_i = i;
    for (int i = 0; i < temp_i; i++){
        printf("%s %c %s %s %s %s %s %s %s %c %d %.1f %s %s %s %d\n%s\n"
        , person[i].name
        , person[i].gender
        , person[i].hobby[0]
        , person[i].hobby[1]
        , person[i].hobby[2]
        , person[i].hobby[3]
        , person[i].hobby[4]
        , person[i].phone_number
        , person[i].area
        , person[i].target
        , person[i].age
        , person[i].height
        , person[i].zodiac
        , person[i].income
        , person[i].job
        , person[i].index_of_area
        , person[i].self_introduction);
    }
    return i;
}