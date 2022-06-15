#ifndef setting_H
#define setting_H

#include <stdbool.h>

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
    char self_introduction[151];
    int score;
    int flag;
    int id;
} Data;

typedef struct {
    char id[21];
    char pw[21];
} ad;

char prefer_zodiac[3][15];
Data person[1000];
ad m[5];

int read_file();

void add_account(int *data_amount);

void regist_account(int *data_amount);

void preference(int *times1,int *times2,int *times3,float *left,float *right,int *l_age,int *r_age);

void height(int *times2,int *x1,int *x2,float *left,float *right);

void age(int *times3,int *l_age,int *r_age);

bool search_duplicates(int data_amount);

bool check_boundary(int x, int y, int row, int col);

void zodiac_choice(int *times1,int *x_zodiac,int *y_zodiac);

bool check_height(char *str);

void calculate_score(int *times1,int *times2,int *times3,float *left,float *right, int *l_age,int *r_age,Data *User,int data_amount);

int judge_mode(Data *User);

void sexuality_score(Data *User,int data_amount);

void age_score(int *times3,int *l_age,int *r_age,Data *User,int data_amount);

void area_score(Data *User,int data_amount);

void hobby_score(Data *User,int data_amount);

void prefer_zodiac_score(int *times1,int data_amount);

void prefer_height_score(int *times2,int data_amount,float *left,float *right);

int comp(const void *p, const void *q);

void init();

int login(int *data_amount);

int search_user(char *us, char *pn, int *data_amount);

int search_admin(char *s, char *s1);

int search(char *pnum, int *data_amount);

void initial_score_and_flag(int data_amount, int *times1, int *times2, int *times3);

#endif