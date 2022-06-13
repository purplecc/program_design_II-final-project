#ifndef UserAction_H
#define UserAction_H

#include "setting.h"

typedef struct like{
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
    char self_introduction[151];
    int score;
    int flag;
    int dest;
    struct like *next;
} Like;

Data correct_person[500];
Like *pre, *cur, *head;

void display(int data_amount);

void choose(int i, int like_people, char like[20][100]);

void match(int *data_amount, int like_people);

void delete_like();

void matching_success(int loca[], int *data_amount);

void very_cool(int like_people, int x, int y, char yes_no[1][2][6], char send[6], int *data_amount, char like[20][100]);

void relike(int g, int like_people, char like[20][100]);

bool check_boundary2(int x);

#endif