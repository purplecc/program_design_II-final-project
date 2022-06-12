#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <termios.h>
// typedef int bool;
// #define false 0
// #define true 1

#define finish          "\033[0m"
#define light           "\033[01m"
#define black           "\033[30m"
#define B_B_red         "\033[1;31;43m"
#define B_I_green       "\033[1;3;32m"
#define B_U_I_yellow    "\033[1;3;4;33m"
#define B_U_I_green     "\033[1;3;4;32m"
#define B_yellow        "\033[1;33m"
#define blue            "\033[34m"
#define B_purple        "\033[1;35m"
#define B_cyan          "\033[1;36m"
#define B_white         "\033[1;37m"
#define B_BLUE          "\x1B[1;36m"
#define BLUE            "\x1B[0;36m"
#define DBLUE           "\x1B[0;34m"
#define BACK_YELLOW     "\x1B[3;33m"
#define PURPLE          "\x1B[0;35m"
#define B_PURPLE        "\x1B[1;35m"
#define B_I_BA_red      "\033[1;3;2;41m"
#define B_I_BA_green    "\033[1;3;2;42m"

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
    int flag;                                          // 是否被喜歡過
    int id;
} Data;

typedef struct like{ // 存喜歡的人
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
    int dest;      // 喜歡user
    struct like *next;
} Like;

int read_file();
void add_account(int *data_amount);
void preference(int *times1,int *times2,int *times3,float *left,float *right,int *l_age,int *r_age);
void height(int *times,int *x1,int *x2,float *left,float *right);
void age(int *times3,int *l_age,int *r_age);
bool search_duplicates(int data_amount);
bool check_boundary(int x, int y, int row, int col);
void print_data(int data_amount);
void zodiac_choice(int *times,int *x_zodiac,int *y_zodiac);
bool check_height(char *str);

void calculate_score(int *times1,int *times2,int *times3,float *left,float *right,\
int *l_age,int *r_age,Data *User,int *data_amount);
int judge_mode(Data *User);                            // 回傳使用者性向狀況
void sexuality_score(Data *User,int *data_amount);
void age_score(int *times3,int *l_age,int *r_age,Data *User,int *data_amount);
void area_score(Data *User,int *data_amount);
void hobby_score(Data *User,int *data_amount);
void prefer_zodiac_score(int *times1,int *data_amount);
void prefer_height_score(int *times2,int *data_amount,float *left,float *right);
int comp(const void *p, const void *q);
void display(int *data_amount);
void choose (int , int);
void match(int*);
void delete_like();
void matching_success();

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
char twelve_zodiac[2][6][15] = {{{"Capricorn"},{"Aquarius"},{"Pisces"},{"Aries"},{"Taurus"},{"Gemini"}},
                                {{"Cancer"},{"Leo"},{"Virgo"},{"Libra"},{"Scorpio"},{"Sagittarius"}}};
int zodiac_flag[2][6] = {{0,0,0,0,0,0,},{0,0,0,0,0,0,}};
char prefer_zodiac[3][15];
int loca[5];
Data person[1000];
Data correct_person[500];
Like *pre, *cur, *head;

int main(){
    int data_amount = 0;
    int times1 = 0,times2 = 0,times3 = 0;
    int l_age = 0,r_age = 0;
    float left,right;

    data_amount = read_file();
    printf("%d\n", data_amount);                            // 看讀到的人數對不對
    printf("%lf\n", (double)clock() / CLOCKS_PER_SEC);      // 讀檔時間(/s)
    //print_data(data_amount);
    add_account(&data_amount);
    preference(&times1,&times2,&times3,&left,&right,&l_age,&r_age);
    calculate_score(&times1,&times2,&times3,&left,&right,&l_age,&r_age,&person[data_amount-1],&data_amount);
    qsort(person,data_amount,sizeof(Data),comp);
    print_data(data_amount);
    while(1) {
        display(&data_amount);
        match(&data_amount);
    }
    // printf("%d\n", data_amount);
    return 0;
}

void matching_success (int loca[] , int *data_amount) {
    int choice = 0;
    Like *first2 = head;
    Like *matched[10];
    printf(B_white"Congrats on the matches!!! Here are their information.\n\n"finish);
    for(int j = 0; j < 5; j++) {
        for(int i = 0; i < loca[j]; i++)
            first2 = first2->next;
        printf(B_white"%s\n"finish , first2 -> name);
        printf(B_white"Gender :%c\n"finish , first2 -> gender);
        printf(B_white"Age    :%d\n"finish , first2 -> age);
        printf(B_white"Height :%.1f\n"finish , first2 -> height);
        printf(B_white"Zodiac :%s\n"finish , first2 -> zodiac);
        printf(B_white"Area   :%s\n"finish , first2 -> area);
        printf(B_white"Hobbies:%s %s %s %s %s\n"finish , first2 -> hobby[0] , first2 -> hobby[1] , first2 -> hobby[2] , first2 -> hobby[3] , first2 -> hobby[4]);
        printf(B_white"Job    :%s\n"finish , first2 -> job);
        printf(B_white"Phone Numbers    :%s\n"finish , first2 -> phone_number);
        printf(B_white"Self introduction :\n  %s\n"finish , first2 -> self_introduction);
        printf(B_purple"__________________________________________________\n\n\n"finish);
        matched[j] = first2;
        first2 = head;
    }
    //system("clear");
              
    printf(B_white"\n\nTake good use of the phone numbers and get to know each others!\n"finish);
    printf(B_white"Who do you like the most?\n"finish);
    printf(B_white"[1]%s [2]%s [3]%s [4]%s [5]%s [6]None : "finish , matched[0]->name , matched[1]->name , matched[2]->name , matched[3]->name , matched[4]->name);
    scanf("%d" , &choice);
    system("clear");
    if (choice == 6) {                  // doesn't like anyone
        printf(B_white"Do you want to keep pairing or exiting the app?\n"finish);
        printf(B_white"[1]Pairing [2]exit : "finish);
        scanf("%d" , &choice);
        if (choice == 1) {          // pairing
            delete_like(); 
            printf(B_B_red"Please wait for a seconds\n"finish);
            sleep(2);
            printf("\n\n");
            printf(B_white"Welcome! It's a whole new day.\n"finish);
            sleep(1);
            return;
        }
        else 
            exit(0);    
    }
    else {             // like someone
        printf(B_white"Bye Bye! See ya next time!\n"finish);
        const char *filename = "final_decision.txt";
        FILE *output_file = fopen(filename, "w");
        if (!output_file){
            exit(EXIT_FAILURE);
        }
        fprintf(output_file , "Name   :%s\n" , matched[choice - 1] -> name);
        fprintf(output_file , "Gender :%c\n" , matched[choice - 1] -> gender);
        fprintf(output_file , "Age    :%d\n" , matched[choice - 1] -> age);
        fprintf(output_file , "Height :%.1f\n" , matched[choice - 1] -> height);
        fprintf(output_file , "Zodiac :%s\n" , matched[choice - 1] -> zodiac);
        fprintf(output_file , "Area   :%s\n" , matched[choice - 1] -> area);
        fprintf(output_file , "Hobbies:%s %s %s %s %s\n" , matched[choice - 1] -> hobby[0] , matched[choice - 1] -> hobby[1] , matched[choice - 1] -> hobby[2] , matched[choice - 1] -> hobby[3] , matched[choice - 1] -> hobby[4]);
        fprintf(output_file , "Job    :%s\n" , matched[choice - 1] -> job);
        fprintf(output_file , "Phone Numbers    :%s\n" , matched[choice - 1] -> phone_number);
        fprintf(output_file , "Self introduction :\n  %s\n\n" , matched[choice - 1] -> self_introduction);
        fclose(output_file);
        system("clear");
        exit(0);
    }
}