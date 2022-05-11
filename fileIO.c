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
    char income[21];
    char work[21];
    char self_introduction[151];
} Data;

int main()
{
    const char *filename = "test.txt";
    Data person[780];
    FILE *input_file = fopen(filename, "r");
    if (!input_file){
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (fscanf(input_file, "%s %c %s %s %s %s %s %s %s %c %d %f %s %s %s\n"
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
    , person[i].work) != EOF){
        fgets(person[i].self_introduction, 151, input_file);
        i++;
    }
    int temp_i = i;
    for (int i = 0; i < temp_i; i++){
        printf("%s %c %s %s %s %s %s %s %s %c %d %.1f %s %s %s\n%s\n"
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
        , person[i].work
        , person[i].self_introduction);
    }
}// 讀進去了