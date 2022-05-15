#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data{
    char name[21];
    char gender;
    char hobby[5][21];
    char phone_number[11];
    char area[16];
    char target;
    int age;
    float height;
    char zodiac[21];
    char income[11];
    char job[41];
    char self_introduction[151];
} Data;

int read_file(Data *person);

int main(){
    int data_amount = 0;
    Data person[780];
    data_amount = read_file(person);
    printf("%d", data_amount);                      // 看讀到的人數對不對
}

int read_file(Data *person){
    int data_id = 0;                                // 檔名要記得改自己txt的名字喔
    const char *filename = "allen.txt";
    FILE *input_file = fopen(filename, "r");
    if (!input_file){
        exit(EXIT_FAILURE);
    }
    while (fscanf(input_file, "%s %c %s %s %s %s %s %s %s %c %d %f %s %s %s "
    , person[data_id].name
    , &person[data_id].gender
    , person[data_id].hobby[0]
    , person[data_id].hobby[1]
    , person[data_id].hobby[2]
    , person[data_id].hobby[3]
    , person[data_id].hobby[4]
    , person[data_id].phone_number
    , person[data_id].area
    , &person[data_id].target
    , &person[data_id].age
    , &person[data_id].height
    , person[data_id].zodiac
    , person[data_id].income
    , person[data_id].job) != EOF){
        fgets(person[data_id].self_introduction, 151, input_file);
        data_id++;
    }
    fclose(input_file);
    /*int temp_i = data_id;                       //這個只是看他有沒有讀進去 要測試有沒有讀對的話把註解弄掉
    for (int data_id = 0; data_id < temp_i; data_id++){
        printf("%s %c %s %s %s %s %s %s %s %c %d %.1f %s %s %s\n%s\n"
        , person[data_id].name
        , person[data_id].gender
        , person[data_id].hobby[0]
        , person[data_id].hobby[1]
        , person[data_id].hobby[2]
        , person[data_id].hobby[3]
        , person[data_id].hobby[4]
        , person[data_id].phone_number
        , person[data_id].area
        , person[data_id].target
        , person[data_id].age
        , person[data_id].height
        , person[data_id].zodiac
        , person[data_id].income
        , person[data_id].job
        , person[data_id].self_introduction);
    }*/
    return data_id;
}
