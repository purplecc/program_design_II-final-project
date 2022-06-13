#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>

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
#define red             "\033[41m"
#define Move_the_cursor_up_one      "\e[1A"
#define Move_the_cursor_right_14    "\e[14C"
#define Move_the_cursor_right_11    "\e[11C"
#define Move_the_cursor_left_1      "\e[1D"
#define Clear_one_word              "\e[K"

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

typedef struct {
    char id[21];
    char pw[21];
} ad;

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

void calculate_score(int *times1,int *times2,int *times3,float *left,float *right,\
int *l_age,int *r_age,Data *User,int data_amount);
int judge_mode(Data *User);                            // 回傳使用者性向狀況
void sexuality_score(Data *User,int data_amount);
void age_score(int *times3,int *l_age,int *r_age,Data *User,int data_amount);
void area_score(Data *User,int data_amount);
void hobby_score(Data *User,int data_amount);
void prefer_zodiac_score(int *times1,int data_amount);
void prefer_height_score(int *times2,int data_amount,float *left,float *right);
int comp(const void *p, const void *q);
void display(int data_amount);

void sort(int *data_amount);
void init();
int login(int *data_amount);
int search_user(char *us, char *pn, int *data_amount);
int search_admin(char *s, char *s1);
int search(char *pnum, int *data_amount);
void administrator(int *data_amount);
int cmp_gender(const void *a, const void *b);
int cmp_phone(const void *a, const void *b);
int cmp_area(const void *a, const void *b);
int cmp_target(const void *a, const void *b);
int cmp_height(const void *a, const void *b);
int cmp_age(const void *a, const void *b);
int cmp_zodiac(const void *a, const void *b);
int cmp_income(const void *a, const void *b);
void traverse(int data_amount);
void write_file(int *data_amount);

void choose(int i, int like_people, char like[20][100]);
void match(int *data_amount, int like_people);
void delete_like();
void matching_success(int loca[] , int *data_amount);
void very_cool(int like_people, int x, int y, char yes_no[1][2][6], char send[6], int *data_amount, char like[20][100]);
void relike(int g, int like_people, char like[20][100]);
bool check_boundary2(int x);

char prefer_zodiac[3][15];
Data person[1000];
Data correct_person[500];
ad m[5];
Like *pre, *cur, *head;

int main(){
    int data_amount = 0;
    int times1 = 0, times2 = 0, times3 = 0;
    int l_age = 0, r_age = 0;
    float left, right;
    int mode;
    init();
    data_amount = read_file();
    while (1){
        mode = login(&data_amount);
        if (mode == -1){        //* 選Exit
            break;
        }
        if(mode == 0){          //* User 註冊 然後配對
            system("cls");
            regist_account(&data_amount);
            preference(&times1, &times2, &times3, &left, &right, &l_age, &r_age);
            calculate_score(&times1, &times2, &times3, &left, &right, &l_age, &r_age, &person[data_amount - 1], data_amount-1);
            qsort(person, data_amount, sizeof(Data), comp);
            while(1){
                display(data_amount);
            }
        }
        else if (mode == 1){    //* Admin operation
            administrator(&data_amount);
        }
        else if(mode == 2){     //* User login and match
            preference(&times1, &times2, &times3, &left, &right, &l_age, &r_age);
            calculate_score(&times1, &times2, &times3, &left, &right, &l_age, &r_age, &person[data_amount - 1], data_amount-1);
            qsort(person, data_amount, sizeof(Data), comp);
            while(1){
                display(data_amount);
            }
        }
    }
}

int read_file(){
    int i = 0;                                    // 檔名要記得改自己txt的名字喔
    const char *filename = "output.txt";
    FILE *input_file = fopen(filename, "r");
    if (!input_file){
        exit(EXIT_FAILURE);
    }
    while (fscanf(input_file, "%s %c %s %s %s %s %s %s %s %c %d %f %s %s %s "
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
    , person[i].job) != EOF){
        fgets(person[i].self_introduction, 151, input_file);
        if(!strcasecmp("Taipei",person[i].area)){
            person[i].index_of_area = 22;
        }
        else if(!strcasecmp("New-Taipei",person[i].area)){
            person[i].index_of_area = 23;
        }
        else if(!strcasecmp("Keelung",person[i].area)){
            person[i].index_of_area = 24;
        }
        else if(!strcasecmp("Taoyuan",person[i].area)){
            person[i].index_of_area = 25;
        }
        else if(!strcasecmp("Hsinchu",person[i].area)){
            person[i].index_of_area = 26;
        }
        else if(!strcasecmp("Miaoli",person[i].area)){
            person[i].index_of_area = 28;
        }
        else if(!strcasecmp("Taichung",person[i].area)){
            person[i].index_of_area = 29;
        }
        else if(!strcasecmp("Changhua",person[i].area)){
            person[i].index_of_area = 31;
        }
        else if(!strcasecmp("Nantou",person[i].area)){
            person[i].index_of_area = 30;
        }
        else if(!strcasecmp("Yunlin",person[i].area)){
            person[i].index_of_area = 33;
        }
        else if(!strcasecmp("Chiayi",person[i].area)){
            person[i].index_of_area = 34;
        }
        else if(!strcasecmp("Tainan",person[i].area)){
            person[i].index_of_area = 35;
        }
        else if(!strcasecmp("Kaohsiung",person[i].area)){
            person[i].index_of_area = 36;
        }
        else if(!strcasecmp("Pingtung",person[i].area)){
            person[i].index_of_area = 37;
        }
        else if(!strcasecmp("Yilan",person[i].area)){
            person[i].index_of_area = 27;
        }
        else if(!strcasecmp("Hualien",person[i].area)){
            person[i].index_of_area = 32;
        }
        else if(!strcasecmp("Taitung",person[i].area)){
            person[i].index_of_area = 38;
        }
        else if(!strcasecmp("Penghu",person[i].area)){
            person[i].index_of_area = 4;
        }
        else if(!strcasecmp("Kinmen",person[i].area)){
            person[i].index_of_area = 2;
        }
        else if(!strcasecmp("Lienchiang",person[i].area)){
            person[i].index_of_area = 1;
        }
        else{
            person[i].index_of_area = 0;
        }
        i++;
    }
    fclose(input_file);
    return i;
}

void regist_account(int *data_amount){
    char hobbies[10][5][13] = {{{"Writing"}, {"Reading"}, {"Singing"}, {"Photography"}, {"Gardening"}},
                            {{"Cooking"}, {"Baking"}, {"Jogging"}, {"Swimming"}, {"Working-out"}},
                            {{"badminton"}, {"Tennis"}, {"Basketball"}, {"Volleyball"},{"Cycling"}},
                            {{"Dancing"}, {"Films"}, {"Fashion"}, {"Collecting"}, {"violin"}},
                            {{"Anime"}, {"Delicacy"}, {"Shopping"}, {"Yoga"}, {"Memes"}},
                            {{"Diving"},{"Sunbathing"},{"Piano"},{"Guitar"},{"Makeup"}},
                            {{"Choir"},{"Baseball"},{"Comedy"},{"Skincare"},{"Korean-Drama"}},
                            {{"Pop-music"},{"Astrology"},{"Meditation"},{"Surfing"},{"Motorcycles"}},
                            {{"Camping"},{"Picnicking"},{"knitting"},{"Cosplay"},{"Fishing"}},
                            {{"Podcasts"},{"Fencing"},{"Climbing"},{"Hiking"},{"Travel"}}};
    char decision[2][27] = {"Yes", "No(enter my profile again)"};
    char cities[4][5][11] = {{{"Keelung"}, {"New-Taipei"}, {"Taipei"}, {"Taoyuan"}, {"Hsinchu"}},
                            {{"Miaoli"}, {"Taichung"}, {"Changhua"}, {"Nantou"}, {"Yunlin"}},
                            {{"Chiayi"}, {"Tainan"}, {"Kaohsiung"}, {"Pintung"}, {"Yilan"}},
                            {{"Hualien"}, {"Taitung"}, {"Penghu"}, {"Kinmen"}, {"Lienchiang"}}};
    char Zodiac[3][4][12] = {{{"Capricorn"}, {"Aquarius"}, {"Pisces"}, {"Aries"}},
                            {{"Taurus"}, {"Gemini"}, {"Cancer"}, {"Leo"}},
                            {{"Virgo"}, {"Libra"}, {"Scorpio"}, {"Sagittarius"}}};
    char Income[4][8] = {{"<100"}, {"100~300"}, {"300~500"}, {">500"}};
    bool hobbies_flag[10][5];
    printf("Welecome to Pretty Babe, please enter your mobile number to register before you start: ");
    scanf("%s", person[*data_amount].phone_number);
    char *str = person[*data_amount].phone_number;
    bool invalid = false;
    while((*str)!='\0'){
        if(isdigit(*str)==0){
            invalid = true;
            break;
        }else{
            str+=1;
        }
    }
    while(search_duplicates(*data_amount) || (person[*data_amount].phone_number[0]!='0' || person[*data_amount].phone_number[1] !='9') || strlen(person[*data_amount].phone_number)!=10 || invalid == true){
        system("cls");
        if(search_duplicates(*data_amount)){
            printf(red"The phone number that already exists!!!\n"finish);
            printf("Enter another phone number again: ");
            scanf("%s", person[*data_amount].phone_number);
            invalid = false;
            str = person[*data_amount].phone_number;
            while((*str)!='\0'){
                if(isdigit(*str)==0){
                    invalid = true;
                    break;
                }else{
                    str+=1;
                }
            }
            system("cls");
        }
        else if((person[*data_amount].phone_number[0]!='0' || person[*data_amount].phone_number[1] !='9') || strlen(person[*data_amount].phone_number)!=10 || invalid == true){
            printf(red"The phone number format is invalid!\n"finish);
            printf("Enter correct phone number again: ");
            scanf("%s", person[*data_amount].phone_number);
            invalid = false;
            str = person[*data_amount].phone_number;
            while((*str)!='\0'){
                if(isdigit(*str)==0){
                    invalid = true;
                    break;
                }else{
                    str+=1;
                }
            }
            system("cls");
        }
    }
    printf("Next, please enter your age: ");
    char temp_a[5];
    str = temp_a;
    scanf("%s", temp_a);
    while(atoi(temp_a) < 18 || atoi(temp_a)==0 || atoi(temp_a)>120){
        invalid = false;
        while((*str)!='\0'){
            if(isdigit(*str)==0){
                invalid = true;
                break;
            }else{
                str+=1;
            }
        }
        system("cls");
        if(atoi(temp_a) < 18 && atoi(temp_a)>0 && invalid == false){
            printf(red"You are too young to register an account\n"finish);
            printf("Please re-enter your age: ");
            scanf("%s", temp_a);
            continue;
        }
        else if(atoi(temp_a)==0 || atoi(temp_a)>120 || invalid == true || atoi(temp_a)<0){
            printf(red"Invalid input! Please ensure your input are real age and must be an integer\n"finish);
            printf("Please re-enter your age: ");
            scanf("%s", temp_a);
            continue;
        }
    }
    system("cls");
    person[*data_amount].age = atoi(temp_a);
    while(1){
        memset(hobbies_flag, false, sizeof(hobbies_flag));
        int print_to_where = 0;
        int count = 0;
        int cx = 0, cy = 0;
        int zx = 0, zy = 0;
        int ix = 0;
        while(1){
            printf("Great! Let's create your personal profile!\n");
            if(print_to_where == 0){
                printf("Name: ");
                scanf("%s", person[*data_amount].name);
                print_to_where = 1;
            }else{
                printf("Name: %s\n", person[*data_amount].name);
            }
            if(print_to_where == 1){
                printf("Gender(M or F): ");
                scanf(" %c", &person[*data_amount].gender);
            }else{
                printf("Gender: %c\n", person[*data_amount].gender);
            }
            if(person[*data_amount].gender != 'M' && person[*data_amount].gender != 'F'){
                system("cls");
                printf(red"Invalid input !!! Please enter again\n"finish);
                continue;
            }else{
                if(count==0){
                    print_to_where = 2;
                    system("cls");
                    count++;
                    continue;
                }
            }
            if(print_to_where==2){
                printf("Sexual Orientation(M or F or B): ");
                scanf(" %c", &person[*data_amount].target);
            }else{
                printf("Sexual Orientation: %c\n", person[*data_amount].target);
            }
            if(person[*data_amount].target != 'M' && person[*data_amount].target != 'F' && person[*data_amount].target != 'B'){
                system("cls");
                printf(red"Invalid input !!! Please enter again\n"finish);
                continue;
            }else{
                if(count==1){
                    print_to_where = 3;
                    system("cls");
                    count++;
                    continue;
                }
            }
            char temp_h[10];
            if(print_to_where==3){
                printf("Height: ");
                scanf("%s", temp_h);
            }else{
                printf("Height: %.1f\n", person[*data_amount].height);
            }
            if(check_height(temp_h) == false || atof(temp_h) > 250 || atof(temp_h) < 75){
                system("cls");
                printf(red"Invalid input !!! Please enter again\n"finish);
                continue;
            }else{
                if(count==2){
                    person[*data_amount].height = atof(temp_h);
                    print_to_where = 4;
                    system("cls");
                    count++;
                    continue;
                }
            }
            if(print_to_where==4){
                printf("Job(if have space between words, must replace to '-'): ");
                scanf("%s", person[*data_amount].job);
                print_to_where++;
            }else{
                printf("Job: %s\n", person[*data_amount].job);
            }
            printf("*******************************************************************\n");
            printf("City:\n");
            char key;
            for (int i = 0; i < 4; i++){
                for (int j = 0; j < 5; j++){
                    if(i==cx && j==cy){
                        printf(B_U_I_yellow"%s    \t"finish, cities[i][j]);
                    }
                    else{
                        printf("%s    \t", cities[i][j]);
                    }
                }
                printf("\n");
            }
            if(print_to_where==5){
                key = getch();
                if((key == 'W' || key =='w' || key == 72) && check_boundary(cx-1,cy,4,5)){
                    cx -= 1;
                    system("cls");
                    continue;
                }
                else if((key == 'A' || key =='a' || key == 75) && check_boundary(cx,cy-1,4,5)){
                    cy -= 1;
                    system("cls");
                    continue;
                }
                else if((key == 'S' || key =='s' || key == 80) && check_boundary(cx+1,cy,4,5)){
                    cx += 1;
                    system("cls");
                    continue;
                }
                else if((key == 'D' || key =='d' || key== 77) && check_boundary(cx,cy+1,4,5)){
                    cy += 1;
                    system("cls");
                    continue;
                }
                else if(key == '\r'){
                    strcpy(person[*data_amount].area, cities[cx][cy]);
                    print_to_where++;
                }
                else{
                    system("cls");
                    continue;
                }
            }
            printf("\n*******************************************************************\n");
            printf("Zodiac:\n");
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 4; j++){
                    if(i==zx && j==zy){
                        printf(B_U_I_yellow"%s    \t"finish, Zodiac[i][j]);
                    }
                    else{
                        printf("%s    \t", Zodiac[i][j]);
                    }
                }
                printf("\n");
            }
            if(print_to_where==6){
                key = getch();
                if((key == 'W' || key =='w' || key == 72) && check_boundary(zx-1,zy,3,4)){
                    zx -= 1;
                    system("cls");
                    continue;
                }
                else if((key == 'A' || key =='a' || key == 75) && check_boundary(zx,zy-1,3,4)){
                    zy -= 1;
                    system("cls");
                    continue;
                }
                else if((key == 'S' || key =='s' || key == 80) && check_boundary(zx+1,zy,3,4)){
                    zx += 1;
                    system("cls");
                    continue;
                }
                else if((key == 'D' || key =='d' || key== 77) && check_boundary(zx,zy+1,3,4)){
                    zy += 1;
                    system("cls");
                    continue;
                }
                else if(key == '\r'){
                    strcpy(person[*data_amount].zodiac, Zodiac[zx][zy]);
                    print_to_where++;
                }
                else{
                    system("cls");
                    continue;
                }
            }
            printf("*******************************************************************\n");
            printf("Income: ");
            for (int i = 0; i < 4; i++){
                if(i==ix){
                    printf(B_U_I_yellow"%s    \t"finish, Income[i]);
                }
                else{
                    printf("%s    \t", Income[i]);
                }
            }
            printf("\n");
            if(print_to_where==7){
                key = getch();
                if((key == 'A' || key =='a' || key == 75) && (ix > -1 && ix < 4)){
                    ix -= 1;
                    system("cls");
                    continue;
                }
                else if((key == 'D' || key =='d' || key== 77) && (ix > -1 && ix < 4)){
                    ix += 1;
                    system("cls");
                    continue;
                }
                else if(key == '\r'){
                    strcpy(person[*data_amount].income, Income[ix]);
                    print_to_where++;
                }
                else{
                    system("cls");
                    continue;
                }
            }
            getchar();
            printf("*******************************************************************\n");
            printf("Write something to introduce yourself: \n");
            fgets(person[*data_amount].self_introduction, 151, stdin);
            break;
        }
        int x = 0, y = 0;
        int count_hobby = 0;
        while(1){
            system("cls");
            printf("\nAfter filling out the basic information, let's Choose 5 hobbies from the following list:\n\n");
            char key;
            for (int i = 0; i < 10; i++){
                printf("%d.\t", i + 1);
                for (int j = 0; j < 5; j++){
                    if(i==x && j==y){
                        printf(B_U_I_yellow"%s    \t"finish, hobbies[i][j]);
                    }
                    else if(hobbies_flag[i][j]){
                        printf(B_U_I_yellow"%s    \t"finish, hobbies[i][j]);
                    }
                    else{
                        printf("%s    \t", hobbies[i][j]);
                    }
                }
                printf("\n\n");
            }
            key = getch();
            if((key == 'W' || key =='w' || key == 72) && check_boundary(x-1,y,10,5)){
                x -= 1;
            }
            else if((key == 'A' || key =='a' || key == 75) && check_boundary(x,y-1,10,5)){
                y -= 1;
            }
            else if((key == 'S' || key =='s' || key == 80) && check_boundary(x+1,y,10,5)){
                x += 1;
            }
            else if((key == 'D' || key =='d' || key== 77) && check_boundary(x,y+1,10,5)){
                y += 1;
            }
            else if(key == '\r' && hobbies_flag[x][y] == false){
                strcpy(person[*data_amount].hobby[count_hobby], hobbies[x][y]);
                hobbies_flag[x][y] = true;
                count_hobby++;
            }
            if(count_hobby==5){
                Sleep(2000);
                break;
            }
        }
        system("cls");
        int yes_no_position = 0;
        while(1){
            system("cls");
            printf(B_B_red"\nCongratulations on completing your registration, the following is your information:\n\n"finish);
            printf(B_U_I_yellow"Personal Profile\n"finish);
            printf(B_I_green"*******************************************************************\n"finish);
            printf(B_cyan"Name: %s\n", person[*data_amount].name);
            printf("Phone Number: %s\n", person[*data_amount].phone_number);
            printf("Gender: %c\n", person[*data_amount].gender);
            printf("Sexual Orientation: %c\n", person[*data_amount].target);
            printf("Age: %d\n", person[*data_amount].age);
            printf("Height: %.1f\n", person[*data_amount].height);
            printf("City: %s\n", person[*data_amount].area);
            printf("Zodiac: %s\n", person[*data_amount].zodiac);
            printf("Job: %s\n", person[*data_amount].job);
            printf("Income: %s\n\n"finish, person[*data_amount].income);
            printf(B_U_I_yellow"Hobbies:\n"finish);
            printf(B_I_green"*******************************************************************\n"finish);
            printf(B_cyan"%s\n", person[*data_amount].hobby[0]);
            printf("%s\n", person[*data_amount].hobby[1]);
            printf("%s\n", person[*data_amount].hobby[2]);
            printf("%s\n", person[*data_amount].hobby[3]);
            printf("%s\n\n", person[*data_amount].hobby[4]);
            printf(B_U_I_yellow"Self introduction:\n"finish);
            printf(B_I_green"*******************************************************************\n"finish);
            printf(B_cyan"%s\n"finish, person[*data_amount].self_introduction);
            printf(B_white"Finally, are you ready for this romantic trip?\n");
            char key;
            for (int i = 0; i < 2;i++){
                if(i == yes_no_position){
                    printf(B_yellow"%s"finish, decision[i]);
                }else{
                    printf(B_white"%s"finish, decision[i]);
                }
                printf("\n");
            }
            key = getch();
            if((key == 'W' || key =='w' || key == 72) && (yes_no_position-1) > -1){
                yes_no_position -= 1;
            }
            else if((key == 'S' || key =='s' || key == 80) && (yes_no_position+1 < 2)){
                yes_no_position += 1;
            }
            else if(key == '\r'){
                break;
            }
        }
        if(yes_no_position==0){
            person[*data_amount].flag = 1;
            break;
        }
        system("cls");
    }
    FILE *output_file = fopen("output.txt", "a");
    fprintf(output_file,"%s %c %s %s %s %s %s %s %s %c %d %.1f %s %s %s %s"
    , person[*data_amount].name
    , person[*data_amount].gender
    , person[*data_amount].hobby[0]
    , person[*data_amount].hobby[1]
    , person[*data_amount].hobby[2]
    , person[*data_amount].hobby[3]
    , person[*data_amount].hobby[4]
    , person[*data_amount].phone_number
    , person[*data_amount].area
    , person[*data_amount].target
    , person[*data_amount].age
    , person[*data_amount].height
    , person[*data_amount].zodiac
    , person[*data_amount].income
    , person[*data_amount].job
    , person[*data_amount].self_introduction);
    fclose(output_file);
    (*data_amount)+=1;
}

void add_account(int *data_amount){
    char hobbies[10][5][13] = {{{"Writing"}, {"Reading"}, {"Singing"}, {"Photography"}, {"Gardening"}},
                            {{"Cooking"}, {"Baking"}, {"Jogging"}, {"Swimming"}, {"Working-out"}},
                            {{"badminton"}, {"Tennis"}, {"Basketball"}, {"Volleyball"},{"Cycling"}},
                            {{"Dancing"}, {"Films"}, {"Fashion"}, {"Collecting"}, {"violin"}},
                            {{"Anime"}, {"Delicacy"}, {"Shopping"}, {"Yoga"}, {"Memes"}},
                            {{"Diving"},{"Sunbathing"},{"Piano"},{"Guitar"},{"Makeup"}},
                            {{"Choir"},{"Baseball"},{"Comedy"},{"Skincare"},{"Korean-Drama"}},
                            {{"Pop-music"},{"Astrology"},{"Meditation"},{"Surfing"},{"Motorcycles"}},
                            {{"Camping"},{"Picnicking"},{"knitting"},{"Cosplay"},{"Fishing"}},
                            {{"Podcasts"},{"Fencing"},{"Climbing"},{"Hiking"},{"Travel"}}};
    char decision[2][27] = {"Yes", "No(enter my profile again)"};
    char cities[4][5][11] = {{{"Keelung"}, {"New-Taipei"}, {"Taipei"}, {"Taoyuan"}, {"Hsinchu"}},
                            {{"Miaoli"}, {"Taichung"}, {"Changhua"}, {"Nantou"}, {"Yunlin"}},
                            {{"Chiayi"}, {"Tainan"}, {"Kaohsiung"}, {"Pintung"}, {"Yilan"}},
                            {{"Hualien"}, {"Taitung"}, {"Penghu"}, {"Kinmen"}, {"Lienchiang"}}};
    char Zodiac[3][4][12] = {{{"Capricorn"}, {"Aquarius"}, {"Pisces"}, {"Aries"}},
                            {{"Taurus"}, {"Gemini"}, {"Cancer"}, {"Leo"}},
                            {{"Virgo"}, {"Libra"}, {"Scorpio"}, {"Sagittarius"}}};
    char Income[4][8] = {{"<100"}, {"100~300"}, {"300~500"}, {">500"}};
    bool hobbies_flag[10][5];
    printf("Enter the phone number: ");
    scanf("%s", person[*data_amount].phone_number);
    char *str = person[*data_amount].phone_number;
    bool invalid = false;
    while((*str)!='\0'){
        if(isdigit(*str)==0){
            invalid = true;
            break;
        }else{
            str+=1;
        }
    }
    while(search_duplicates(*data_amount) || (person[*data_amount].phone_number[0]!='0' || person[*data_amount].phone_number[1] !='9') || strlen(person[*data_amount].phone_number)!=10 || invalid == true){
        system("cls");
        if(search_duplicates(*data_amount)){
            printf(red"The phone number that already exists\n\n"finish);
            Sleep(2000);
            return;
        }
        else if((person[*data_amount].phone_number[0]!='0' || person[*data_amount].phone_number[1] !='9') || strlen(person[*data_amount].phone_number)!=10 || invalid == true){
            printf(red"The phone number format is invalid!\n"finish);
            printf("Enter the phone number again: ");
            scanf("%s", person[*data_amount].phone_number);
            invalid = false;
            str = person[*data_amount].phone_number;
            while((*str)!='\0'){
                if(isdigit(*str)==0){
                    invalid = true;
                    break;
                }else{
                    str+=1;
                }
            }
            system("cls");
        }
    }
    printf("Enter the age: ");
    char temp_a[5];
    str = temp_a;
    scanf("%s", temp_a);
    while(atoi(temp_a) < 18 || atoi(temp_a)==0 || atoi(temp_a)>120){
        invalid = false;
        while((*str)!='\0'){
            if(isdigit(*str)==0){
                invalid = true;
                break;
            }else{
                str+=1;
            }
        }
        system("cls");
        if(atoi(temp_a) < 18 && atoi(temp_a)>0 && invalid == false){
            printf(red"The age is too young\n"finish);
            printf("Please re-enter your age: ");
            scanf("%s", temp_a);
            continue;
        }
        else if(atoi(temp_a)==0 || atoi(temp_a)>120 || invalid == true || atoi(temp_a)<0){
            printf(red"Invalid input! Your input must be real age and is integer\n"finish);
            printf("Please re-enter your age: ");
            scanf("%s", temp_a);
            continue;
        }
    }
    system("cls");
    person[*data_amount].age = atoi(temp_a);
    while(1){
        memset(hobbies_flag, false, sizeof(hobbies_flag));
        int print_to_where = 0;
        int count = 0;
        int cx = 0, cy = 0;
        int zx = 0, zy = 0;
        int ix = 0;
        while(1){
            printf("Create personal profile!\n");
            if(print_to_where == 0){
                printf("Name: ");
                scanf("%s", person[*data_amount].name);
                print_to_where = 1;
            }else{
                printf("Name: %s\n", person[*data_amount].name);
            }
            if(print_to_where == 1){
                printf("Gender(M or F): ");
                scanf(" %c", &person[*data_amount].gender);
            }else{
                printf("Gender: %c\n", person[*data_amount].gender);
            }
            if(person[*data_amount].gender != 'M' && person[*data_amount].gender != 'F'){
                system("cls");
                printf(red"Invalid input !!! Please enter again\n"finish);
                continue;
            }else{
                if(count==0){
                    print_to_where = 2;
                    system("cls");
                    count++;
                    continue;
                }
            }
            if(print_to_where==2){
                printf("Sexual Orientation(M or F or B): ");
                scanf(" %c", &person[*data_amount].target);
            }else{
                printf("Sexual Orientation: %c\n", person[*data_amount].target);
            }
            if(person[*data_amount].target != 'M' && person[*data_amount].target != 'F' && person[*data_amount].target != 'B'){
                system("cls");
                printf(red"Invalid input !!! Please enter again\n"finish);
                continue;
            }else{
                if(count==1){
                    print_to_where = 3;
                    system("cls");
                    count++;
                    continue;
                }
            }
            char temp_h[10];
            if(print_to_where==3){
                printf("Height: ");
                scanf("%s", temp_h);
            }else{
                printf("Height: %.1f\n", person[*data_amount].height);
            }
            if(check_height(temp_h) == false || atof(temp_h) > 250 || atof(temp_h) < 75){
                system("cls");
                printf(red"Invalid input !!! Please enter again\n"finish);
                continue;
            }else{
                if(count==2){
                    person[*data_amount].height = atof(temp_h);
                    print_to_where = 4;
                    system("cls");
                    count++;
                    continue;
                }
            }
            if(print_to_where==4){
                printf("Job(if have space between words, must replace to '-'): ");
                scanf("%s", person[*data_amount].job);
                print_to_where++;
            }else{
                printf("Job: %s\n", person[*data_amount].job);
            }
            printf("*******************************************************************\n");
            printf("City:\n");
            char key;
            for (int i = 0; i < 4; i++){
                for (int j = 0; j < 5; j++){
                    if(i==cx && j==cy){
                        printf(B_U_I_yellow"%s    \t"finish, cities[i][j]);
                    }
                    else{
                        printf("%s    \t", cities[i][j]);
                    }
                }
                printf("\n");
            }
            if(print_to_where==5){
                key = getch();
                if((key == 'W' || key =='w' || key == 72) && check_boundary(cx-1,cy,4,5)){
                    cx -= 1;
                    system("cls");
                    continue;
                }
                else if((key == 'A' || key =='a' || key == 75) && check_boundary(cx,cy-1,4,5)){
                    cy -= 1;
                    system("cls");
                    continue;
                }
                else if((key == 'S' || key =='s' || key == 80) && check_boundary(cx+1,cy,4,5)){
                    cx += 1;
                    system("cls");
                    continue;
                }
                else if((key == 'D' || key =='d' || key== 77) && check_boundary(cx,cy+1,4,5)){
                    cy += 1;
                    system("cls");
                    continue;
                }
                else if(key == '\r'){
                    strcpy(person[*data_amount].area, cities[cx][cy]);
                    print_to_where++;
                }
                else{
                    system("cls");
                    continue;
                }
            }
            printf("\n*******************************************************************\n");
            printf("Zodiac:\n");
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 4; j++){
                    if(i==zx && j==zy){
                        printf(B_U_I_yellow"%s    \t"finish, Zodiac[i][j]);
                    }
                    else{
                        printf("%s    \t", Zodiac[i][j]);
                    }
                }
                printf("\n");
            }
            if(print_to_where==6){
                key = getch();
                if((key == 'W' || key =='w' || key == 72) && check_boundary(zx-1,zy,3,4)){
                    zx -= 1;
                    system("cls");
                    continue;
                }
                else if((key == 'A' || key =='a' || key == 75) && check_boundary(zx,zy-1,3,4)){
                    zy -= 1;
                    system("cls");
                    continue;
                }
                else if((key == 'S' || key =='s' || key == 80) && check_boundary(zx+1,zy,3,4)){
                    zx += 1;
                    system("cls");
                    continue;
                }
                else if((key == 'D' || key =='d' || key== 77) && check_boundary(zx,zy+1,3,4)){
                    zy += 1;
                    system("cls");
                    continue;
                }
                else if(key == '\r'){
                    strcpy(person[*data_amount].zodiac, Zodiac[zx][zy]);
                    print_to_where++;
                }
                else{
                    system("cls");
                    continue;
                }
            }
            printf("*******************************************************************\n");
            printf("Income: ");
            for (int i = 0; i < 4; i++){
                if(i==ix){
                    printf(B_U_I_yellow"%s    \t"finish, Income[i]);
                }
                else{
                    printf("%s    \t", Income[i]);
                }
            }
            printf("\n");
            if(print_to_where==7){
                key = getch();
                if((key == 'A' || key =='a' || key == 75) && (ix > -1 && ix < 4)){
                    ix -= 1;
                    system("cls");
                    continue;
                }
                else if((key == 'D' || key =='d' || key== 77) && (ix > -1 && ix < 4)){
                    ix += 1;
                    system("cls");
                    continue;
                }
                else if(key == '\r'){
                    strcpy(person[*data_amount].income, Income[ix]);
                    print_to_where++;
                }
                else{
                    system("cls");
                    continue;
                }
            }
            getchar();
            printf("*******************************************************************\n");
            printf("Self introduction: \n");
            fgets(person[*data_amount].self_introduction, 151, stdin);
            break;
        }
        int x = 0, y = 0;
        int count_hobby = 0;
        while(1){
            system("cls");
            printf("\nChoose 5 hobbies from the following list:\n\n");
            char key;
            for (int i = 0; i < 10; i++){
                printf("%d.\t", i + 1);
                for (int j = 0; j < 5; j++){
                    if(i==x && j==y){
                        printf(B_U_I_yellow"%s    \t"finish, hobbies[i][j]);
                    }
                    else if(hobbies_flag[i][j]){
                        printf(B_U_I_yellow"%s    \t"finish, hobbies[i][j]);
                    }
                    else{
                        printf("%s    \t", hobbies[i][j]);
                    }
                }
                printf("\n\n");
            }
            key = getch();
            if((key == 'W' || key =='w' || key == 72) && check_boundary(x-1,y,10,5)){
                x -= 1;
            }
            else if((key == 'A' || key =='a' || key == 75) && check_boundary(x,y-1,10,5)){
                y -= 1;
            }
            else if((key == 'S' || key =='s' || key == 80) && check_boundary(x+1,y,10,5)){
                x += 1;
            }
            else if((key == 'D' || key =='d' || key== 77) && check_boundary(x,y+1,10,5)){
                y += 1;
            }
            else if(key == '\r' && hobbies_flag[x][y] == false){
                strcpy(person[*data_amount].hobby[count_hobby], hobbies[x][y]);
                hobbies_flag[x][y] = true;
                count_hobby++;
            }
            if(count_hobby==5){
                Sleep(2000);
                break;
            }
        }
        system("cls");
        int yes_no_position = 0;
        while(1){
            system("cls");
            printf(B_U_I_yellow"Personal Profile\n"finish);
            printf(B_I_green"*******************************************************************\n"finish);
            printf(B_cyan"Name: %s\n", person[*data_amount].name);
            printf("Phone Number: %s\n", person[*data_amount].phone_number);
            printf("Gender: %c\n", person[*data_amount].gender);
            printf("Sexual Orientation: %c\n", person[*data_amount].target);
            printf("Age: %d\n", person[*data_amount].age);
            printf("Height: %.1f\n", person[*data_amount].height);
            printf("City: %s\n", person[*data_amount].area);
            printf("Zodiac: %s\n", person[*data_amount].zodiac);
            printf("Job: %s\n", person[*data_amount].job);
            printf("Income: %s\n\n"finish, person[*data_amount].income);
            printf(B_U_I_yellow"Hobbies:\n"finish);
            printf(B_I_green"*******************************************************************\n"finish);
            printf(B_cyan"%s\n", person[*data_amount].hobby[0]);
            printf("%s\n", person[*data_amount].hobby[1]);
            printf("%s\n", person[*data_amount].hobby[2]);
            printf("%s\n", person[*data_amount].hobby[3]);
            printf("%s\n\n", person[*data_amount].hobby[4]);
            printf(B_U_I_yellow"Self introduction:\n"finish);
            printf(B_I_green"*******************************************************************\n"finish);
            printf(B_cyan"%s\n"finish, person[*data_amount].self_introduction);
            printf(B_white"[Confirm Submission]\n");
            char key;
            for (int i = 0; i < 2;i++){
                if(i == yes_no_position){
                    printf(B_yellow"%s"finish, decision[i]);
                }else{
                    printf(B_white"%s"finish, decision[i]);
                }
                printf("\n");
            }
            key = getch();
            if((key == 'W' || key =='w' || key == 72) && (yes_no_position-1) > -1){
                yes_no_position -= 1;
            }
            else if((key == 'S' || key =='s' || key == 80) && (yes_no_position+1 < 2)){
                yes_no_position += 1;
            }
            else if(key == '\r'){
                break;
            }
        }
        if(yes_no_position==0){
            person[*data_amount].flag = 1;
            break;
        }
        system("cls");
    }
    FILE *output_file = fopen("output.txt", "a");
    fprintf(output_file,"%s %c %s %s %s %s %s %s %s %c %d %.1f %s %s %s %s"
    , person[*data_amount].name
    , person[*data_amount].gender
    , person[*data_amount].hobby[0]
    , person[*data_amount].hobby[1]
    , person[*data_amount].hobby[2]
    , person[*data_amount].hobby[3]
    , person[*data_amount].hobby[4]
    , person[*data_amount].phone_number
    , person[*data_amount].area
    , person[*data_amount].target
    , person[*data_amount].age
    , person[*data_amount].height
    , person[*data_amount].zodiac
    , person[*data_amount].income
    , person[*data_amount].job
    , person[*data_amount].self_introduction);
    fclose(output_file);
    (*data_amount)+=1;
    system("cls");
    printf(B_yellow"successfully added !\n\n"finish);
    Sleep(2000);
}

void preference(int *times1,int *times2,int *times3,float *left,float *right,int *l_age,int *r_age){ 
    char four_choices[1][4][10] = {{{" Zodiac "},{" Height "},{" Age "},{" Next "}}};
    int x = 0,y = 0;
    int x1 = 0,x2 = 41;
    int x_zodiac = 0,y_zodiac = 0;
    system("cls");
    while(1){
        printf("\nDo You have preferred characteristic?\n\n");
        for(int i = 0; i < 1 ;i++){
            for(int j = 0; j < 4 ;j++){
                if(i == x && j == y)
                    printf(B_U_I_yellow"\t%s\t\t"finish,four_choices[i][j]);
                else
                    printf("\t%s\t\t",four_choices[i][j]);
            }
        }
        char key;
        key = getch();
        if((key == 'A' || key == 'a' || key == 75) && y-1 >= 0){
            y-=1;
        }
        else if((key == 'D' || key == 'd' || key == 77) && y+1 <= 3){
            y+=1;
        }
        else if(key == '\r' && !strcmp(four_choices[x][y]," Zodiac ")){
            zodiac_choice(times1,&x_zodiac,&y_zodiac);
        }
        else if(key == '\r' && !strcmp(four_choices[x][y]," Height ")){
            height(times2,&x1,&x2,left,right);
        }
        else if(key == '\r' && !strcmp(four_choices[x][y]," Age ")){
            age(times3,l_age,r_age);
        }
        else if(key == '\r' && !strcmp(four_choices[x][y]," Next ")){
            break;
        }
        system("cls");
    }
}

void zodiac_choice(int *times1,int *x_zodiac,int *y_zodiac){
    char twelve_zodiac[2][6][15] = {{{"Capricorn"},{"Aquarius"},{"Pisces"},{"Aries"},{"Taurus"},{"Gemini"}},
                                {{"Cancer"},{"Leo"},{"Virgo"},{"Libra"},{"Scorpio"},{"Sagittarius"}}};
    int zodiac_flag[2][6] = {{0,0,0,0,0,0,},{0,0,0,0,0,0,}};
    if(*times1 == 3){
        printf("\nDo you want to modify your chioces?\n(Enter Y or N)\n");
        char ch = getchar();
        if(ch == 'Y'){
            *x_zodiac = 0;
            *y_zodiac = 0;
            *times1 = 0;
            for(int i = 0;i < 2;i++){
                for(int j = 0;j < 6;j++){
                    zodiac_flag[i][j] = 0;
                }
            }
            getchar();
        }
        else{
            return;
        }
    }
    while(1){
        system("cls");
        printf("\nChoose 3 preferred zoidac:\n");
        for(int i = 0; i < 2;i++){
            for(int j = 0; j < 6;j++){
                if(i == *x_zodiac && j == *y_zodiac)
                    printf(B_U_I_green"%s      \t"finish,twelve_zodiac[i][j]);
                else if(zodiac_flag[i][j])
                    printf(B_U_I_green"%s      \t"finish,twelve_zodiac[i][j]);
                else
                    printf("%s      \t",twelve_zodiac[i][j]);
            }
            printf("\n");
        }
        char key_z;
        key_z = getch();
        if((key_z == 'W' || key_z == 'w' || key_z == 72) && (*x_zodiac-1) >= 0){
            *x_zodiac-=1;
        }
        else if((key_z == 'S' || key_z == 's' || key_z == 80) && (*x_zodiac+1) <= 1){
            *x_zodiac+=1;
        }
        else if((key_z == 'A' || key_z == 'a' || key_z == 75) && (*y_zodiac-1) >= 0){
            *y_zodiac-=1;
        }
        else if((key_z == 'D' || key_z == 'd' || key_z == 77) && (*y_zodiac+1) <= 5){
            *y_zodiac+=1;
        }
        else if(key_z == '\r' && zodiac_flag[*x_zodiac][*y_zodiac] == 0){
            strcpy(prefer_zodiac[*times1],twelve_zodiac[*x_zodiac][*y_zodiac]);
            (*times1)++;
            zodiac_flag[*x_zodiac][*y_zodiac] = 1;
            if(*times1 == 3){
                break;
            }
        }
        
    }
    printf(B_BLUE"Preferred zodiac :\n%s\n%s\n%s\nPress enter and continue..."finish,prefer_zodiac[0],prefer_zodiac[1],prefer_zodiac[2]);
    getchar();
}

void height(int *times2,int *x1,int *x2,float *left,float *right){ 
    if(*times2 == 1){
        printf("\nDo you want to modify your chioces?\n(Enter Y or N)\n");
        char ch = getchar();
        if(ch == 'Y'){
            *x1 = 0;
            *x2 = 41;
            *times2 = 0;
            getchar();
        }
        else{
            return;
        }
    }
    int num[6] = {160,165,170,175,180,185};
    char line[49] = "------------------------------------------> (cm)";                                                         
    while(1){
        system("cls");
        printf("Set the range of your soulmate's height!\n");
        printf("Please move the left hand side to your ideal height lower limit:\n\n");
        printf("  ");
        for(int i = 0;i < 6;i++){
            printf("%d    ",num[i]);
        }
        printf("\n");
        for(int i = 0;i < 50;i++){
            if(i == *x1){
                printf(B_I_BA_red"%c"finish,line[i]);
            }
            else{
                printf("%c",line[i]);
            }
        }
        char key;
        key = getch();
        if((key == 'A' || key == 'a' || key == 75) && (*x1)-1 >= 0){
            (*x1)-=1;
        }
        else if((key == 'D' || key == 'd' || key == 77) && (*x1)+1 <= 42){
            (*x1)+=1;
        }
        else if(key == '\r'){
            if(*x1 < 3) *left = 157.5;  
            else if(*x1 == 3) *left = 160;
            else if(*x1 > 3 && *x1 < 10) *left = 162.5;
            else if(*x1 == 10) *left = 165;
            else if(*x1 > 10 && *x1 < 17) *left = 167.5;
            else if(*x1 == 17) *left = 170;
            else if(*x1 > 17 && *x1 < 24) *left = 172.5;
            else if(*x1 == 24) *left = 175;
            else if(*x1 > 24 && *x1 < 31) *left = 177.5;
            else if(*x1 == 31) *left = 180;
            else if(*x1 > 31 && *x1 < 38) *left = 182.5;
            else if(*x1 == 38) *left = 185;
            else *left = 187.5;        
            break; 
        }
    }
    while(1){
        system("cls");
        printf("Set the range of your soulmate's height!\n");
        printf("Please move the right hand side to your ideal height upper limit:\n\n");
        printf("  ");
        for(int i = 0;i < 6;i++){
            printf("%d    ",num[i]);
        }
        printf("\n");
        for(int i = 0;i < 50 ;i++){
            if(i == *x1){
                printf(B_I_BA_red"%c"finish,line[i]);
            }
            else if(i == *x2){
                printf(B_I_BA_red"%c"finish,line[i]);
            }
            else{
                printf("%c",line[i]);
            }
        }
        char key;
        key = getch();
        if((key == 'A' || key == 'a' || key == 75) && (*x2)-1 > *x1 ){
            (*x2)-=1;
        }
        else if((key == 'D' || key == 'd' || key == 77) && (*x2)+1 <= 41){
            (*x2)+=1;
        }
        else if(key == '\r'){                                        //160 165 170 175 180 185 
                                                                     //3  10  17   24  31  38
            if(*x2 < 3) *right = 157.5;  
            else if(*x2 == 3) *right = 160;
            else if(*x2 > 3 && *x2 < 10) *right = 162.5;
            else if(*x2 == 10) *right = 165;
            else if(*x2 > 10 && *x2 < 17) *right = 167.5;
            else if(*x2 == 17) *right = 170;
            else if(*x2 > 17 && *x2 < 24) *right = 172.5;
            else if(*x2 == 24) *right = 175;
            else if(*x2 > 24 && *x2 < 31) *right = 177.5;
            else if(*x2 == 31) *right = 180;
            else if(*x2 > 31 && *x2 < 38) *right = 182.5;
            else if(*x2 == 38) *right = 185;
            else *right = 187.5;        
            break;
        }
    }
    *times2 = 1;
    printf(B_BLUE"\nPreferred height :\n%.2lf ~ %.2lf\nPress enter to continue..."finish,*left,*right);
    getchar();
}

void age(int *times3,int *l_age,int *r_age){
    system("cls");
    if(*times3 != 0){
        printf("\nDo you want to modify your chioces?\n(Enter Y or N)\n");
        char ch = getchar();
        if(ch == 'Y'){
            *l_age = 0;
            *r_age = 0;
            getchar();
        }
        else{
            return;
        }
    }
    char c;
    printf(B_BLUE"Please enter your preferred soulmate's age :\n"finish);
    printf(B_BLUE"Ex:18-25\n"finish);
    scanf("%d%c%d",l_age,&c,r_age);

    printf(B_BLUE"\nPreferred age: %d ~ %d.\nPress enter to continue...\n"finish,*l_age,*r_age);
    (*times3) ++;
    getchar();
    getchar();
}

bool search_duplicates(int data_amount){
    for (int i = 0; i < data_amount; i++){
        if(!strcmp(person[i].phone_number, person[data_amount].phone_number)){
            return true;
        }
    }
    return false;
}

bool check_boundary(int x, int y, int row, int col){
    if(x<0 || x>row-1 || y<0 || y>col-1){
        return false;
    }
    return true;
}

void calculate_score(int *times1,int *times2,int *times3,float *left,float *right,int *l_age,int *r_age,Data *User,int data_amount){
    sexuality_score(User,data_amount);
    age_score(times3,l_age,r_age,User,data_amount); 
    area_score(User,data_amount);
    hobby_score(User,data_amount);
    prefer_zodiac_score(times1,data_amount);
    prefer_height_score(times2,data_amount,left,right);
}

int judge_mode(Data *User){
    if (User->gender == 'F'){
        if (User->target == 'M')
            return 1; //直女回傳1
        else if (User->target == 'F')
            return 2; //女同回傳2
        else if (User->target == 'B')
            return 3; //女雙回傳3
    }
    else if (User->gender == 'M'){
        if (User->target == 'F')
            return 4; //直男回傳4
        else if (User->target == 'M')
            return 5; //男同回傳5
        else if (User->target == 'B')
            return 6; //男雙回傳6
    }
    return -1;
}

void sexuality_score(Data *User,int data_amount){     // 性向對了+1500
    int mode = judge_mode(User);
    int i = 0;
    if(mode == 1){
        for (i = 0; i < data_amount; i++){
            if((person + i)->gender == 'M' && (person + i)->target == 'F'){
                (person + i)->score += 1500;                  
            }
            else{
                (person + i)->score = 0;
            }
            (person + i)->flag = 0;
        }
    }
    else if(mode == 2){
        for (i = 0; i < data_amount; i++){
            if((person + i)->gender == 'F'){
                if((person + i)->target == 'F' || (person + i)->target == 'B')
                    (person + i)->score += 1500;
            }
            else{
                (person + i)->score = 0;
            }
            (person + i)->flag = 0;
        }
    }
    else if(mode == 3){
        for (i = 0; i < data_amount; i++){
            if((person + i)->target == 'F' || (person + i)->target == 'B')
                (person + i)->score += 1500;
            else{
                (person + i)->score = 0;
            }
            (person + i)->flag = 0;
        }
    }
    else if(mode == 4){
        for (i = 0; i < data_amount; i++){
            if((person + i)->gender == 'F' && (person + i)->target == 'M'){
                (person + i)->score += 1500;
            }
            else{
                (person + i)->score = 0;
            }
            (person + i)->flag = 0;
        }
    }
    else if(mode == 5){
        for (i = 0; i < data_amount; i++){
            if((person + i)->gender == 'M'){
                if((person + i)->target == 'M' || (person + i)->target == 'B')
                    (person + i)->score += 1500;
            }
            else{
                (person + i)->score = 0;
            }
            (person + i)->flag = 0;
        }
    }
    else if(mode == 6){
        for(i = 0 ; i < data_amount ; i++){
            if((person + i)->target == 'M' || (person + i)->target == 'B')
                (person + i)->score += 1500;
            else
                (person + i)->score = 0;
            (person + i)->flag = 0;
        }
    }
}

void age_score(int *times3,int *l_age,int *r_age,Data *User,int data_amount){           // 沒有偏好的情況下，和使用者年齡相差超過10就沒局囉
    if(*times3 == 0){
        for(int i = 0;i < data_amount;i++){
            if(abs(((person + i)->age)- (User->age)) > 10){
                (person + i)->score = 0;
            }
        }
    }
    else{
        for(int i = 0;i < data_amount;i++){
            if((*l_age <= (person + i)->age) && ((person + i)->age <= *r_age)){              // 有偏好的情況下，對了 +500
                (person + i)->score += 500;
            }
            else
                (person + i)->score = 0;                                                     // 不在我想要的範圍我就不印了
        }
    }
}

void area_score(Data *User,int data_amount){          // 距離差0加100,差1加90,差2加80...10以上不加了
    for(int i = 0;i < data_amount;i++){
        int ans = abs(((person + i)->index_of_area)- (User->index_of_area));
        if(ans == 0){
            (person + i)->score += 100;
        }
        else if(ans < 10){
            (person + i)->score += ((10-i)*10);
        }
    }
}

void hobby_score(Data *User,int data_amount){         //每對一個+20
    for(int i = 0;i < 5;i++){       
        for(int j = 0;j < data_amount;j++){
            for(int k = 0;k < 5;k++){
                if(!strcasecmp(User->hobby[i],(person + j)->hobby[k])){
                    (person + j)->score += 20;
                }
            }
        }
    }
}

void prefer_zodiac_score(int *times1,int data_amount){
    if(*times1 == 3){
        for(int i = 0;i < data_amount;i++){
            for(int j = 0;j < 3;j++){
                if(!strcasecmp((person+i)->zodiac,prefer_zodiac[j])){
                    (person+i)->score += 300;
                }
            }
        }
    }
    else
        return;
}

void prefer_height_score(int *times2,int data_amount,float *left,float *right){
    if(*times2 == 1){
        for(int i = 0;i < data_amount;i++){
            if((*left <= (person+i)->height) && ((person+i)->height <= *right)){
                (person+i)->score += 300;
            }
            else{
                (person+i)->score = 0;
            }
        }
    }
    else
        return;
}

int comp(const void *p,const void *q){
    return (((Data *)q)->score - ((Data *)p)->score);
}

void display(int data_amount){
    char like[20][100];
    int x = 0,y = 0;
    int right = 0;
    int like_people = 0;
    char yes_no[1][2][6] = {{{ " YES " },{ " NO " }}};
    char send[6] = {"SEND"};
    int correct = 0;
    for(int i = 0; i < data_amount; i++){
        if(person[i].score >= 1500 && person[i].flag == 0){
            correct_person[correct] = person[i];            // 對的人才會印，縮短判斷的時間
            correct_person[correct].id = i;
            correct++;
        }
    }
    while(like_people < 20){
        for(int i = 0;i < correct;i++){
            system("cls");
            if(like_people < 20){
                while(1){
                    // printf("\n%d\n",correct_person[i].score);
                    printf(BACK_YELLOW"\nFIND YOUR SOULMATE!\n\n"finish);
                    printf(B_U_I_yellow"***************************************************************************\n\n"finish); 
                    int space = (70 - strlen(correct_person[i].name))/2;
                    for(int j = 0;j < space;j++){
                        printf(" ");
                    }
                    printf(B_BLUE"%s\n"finish,correct_person[i].name);
                    printf(B_BLUE"Gender :%c\n"finish,correct_person[i].gender);
                    printf(B_BLUE"Age    :%d\n"finish,correct_person[i].age);
                    printf(B_BLUE"Height :%.1f\n"finish,correct_person[i].height);
                    printf(B_BLUE"Zodiac :%s\n"finish,correct_person[i].zodiac);
                    printf(B_BLUE"Area   :%s\n"finish,correct_person[i].area);
                    printf(B_BLUE"Hobbies:%s %s %s %s %s\n"finish,correct_person[i].hobby[0],correct_person[i].hobby[1],correct_person[i].hobby[2],correct_person[i].hobby[3],correct_person[i].hobby[4]);
                    printf(B_BLUE"Job    :%s\n"finish,correct_person[i].job);
                    printf(B_PURPLE"Self introduction :\n  %s\n\n"finish,correct_person[i].self_introduction);  
                    for(int i = 0;i < 1;i++){
                        for(int j = 0;j < 2;j++){
                            if(i == x && j == y ){
                                if(y == 0)printf(B_I_BA_green"\t\t\t%s"finish,yes_no[i][j]);
                                else if(y == 1)printf(B_I_BA_red"\t\t\t%s"finish,yes_no[i][j]);
                            }
                            else
                                printf("\t\t\t%s",yes_no[i][j]);
                        }
                    }
                    printf("\n\n");
                    printf(B_U_I_yellow"***************************************************************************\n\n"finish);
                    char key;
                    key = getch();
                    if((key == 'A' || key == 'a' || key == 75) && ((y - 1) >= 0)){
                        y-=1;
                    }
                    else if((key == 'D' || key =='d' || key == 77) && ((y + 1) <= 1)){
                        y+=1;
                    }
                    else if(key == '\r' && !strcmp(yes_no[x][y]," YES ")){
                        person[correct_person[i].id].flag = 1;
                        choose(right, like_people, like);
                        right++;
                        like_people++;
                        break;
                    }
                    else if(key == '\r' && !strcmp(yes_no[x][y]," NO ")){
                        break;
                    }
                    system("cls");
                }
            }
            if(like_people==20){
                system("cls");
                break;
            }
        }
        very_cool(like_people, x,  y,  yes_no, send , &data_amount, like);
    }
}

bool check_height(char *str){
    int count = 0;
    while((*str)!='\0'){
        if((*str)=='.'){
            count++;
        }
        if((isdigit(*str)==0 && (*str)!='.') || count>1){
            return false;
        }
        else{
            str += 1;
        }
    }
    return true;
}

int login(int *data_amount){
    int x = 0;
    int ret;
    char word[21];
    char word2[21];
    char key;
    char status[3][6] = {{"Admin"}, {"User"}, {"Exit"}};
    char admin[2][9] = {{"[Log in]"}, {"[Back]"}};
    char user[3][9] = {{"[Log in]"}, {"[Regist]"}, {"[Back]"}};

cmod:
    x = 0;
    while(1){
        system("cls");
        printf("Choose identity:\n");
        printf("*************************************\n");
        for (int i = 0; i < 3; i++){
            if(i == x){
                printf(B_yellow"%s"finish, status[i]);
            }else{
                printf(B_white"%s"finish, status[i]);
            }
            printf("\t");
        }
        printf("\n\n");
        key = getch();
        if((key == 'A' || key =='a' || key == 75) && (x-1) > -1){
            x -= 1;
        }
        else if((key == 'D' || key =='d' || key == 77) && (x+1) < 3){
            x += 1;
        }
        else if(key == '\r'){
            strcpy(word, status[x]);
            break;
        }
    }
    if (!strcmp(word,"User")){
        goto userlogin;
    }
    else if (!strcmp(word,"Admin")){
        goto adminlogin;
    }
    else if(!strcmp(word,"Exit")){
        system("cls");
        printf("Bye! See ya :)\n");
        return -1;
    }

adminlogin:
    x = 0;
    while(1){
        system("cls");
        printf("Admin:\n");
        printf("*************************************\n");
        for (int i = 0; i < 2; i++){
            if(i == x){
                printf(B_yellow"%s"finish, admin[i]);
            }else{
                printf(B_white"%s"finish, admin[i]);
            }
            printf("\t");
        }
        printf("\n\n");
        key = getch();
        if((key == 'A' || key =='a' || key == 75) && (x-1) > -1){
            x -= 1;
        }
        else if((key == 'D' || key =='d' || key == 77) && (x+1) < 2){
            x += 1;
        }
        else if(key == '\r'){
            strcpy(word, admin[x]);
            break;
        }
    }
    if (!strcmp(word,"[Back]")){
        goto cmod;
    }
    else if(!strcmp(word,"[Log in]")){
        int i = 0;
        char c;
        printf("Github ID: \n");
        printf("Password : ");
        printf(Move_the_cursor_up_one "" finish);
        while((c = getch()) != '\r'){
            if(c =='\b' && i > 0){
                i--;
                printf(Move_the_cursor_left_1""finish);
                printf(Clear_one_word""finish);
            }
            else if(c =='\b' && i == 0){
                continue;
            }
            else if(i == 20){
                continue;
            }
            else{
                word[i] = c;
                printf("%c", word[i]);
                i++;
            }
        }
        word[i] = '\0';
        printf("\n");
        printf(Move_the_cursor_right_11 "" finish);
        i = 0;
        while((c = getch()) != '\r'){
            if(c =='\b' && i > 0){
                i--;
                printf(Move_the_cursor_left_1""finish);
                printf(Clear_one_word""finish);
            }
            else if(c =='\b' && i == 0){
                continue;
            }
            else if(i == 20){
                continue;
            }
            else{
                word2[i] = c;
                printf("*");
                i++;
            }
        }
        word2[i] = '\0';
        ret = search_admin(word, word2);
    }
    if (ret == 0) {
        printf(red"\nIncorrect username or password. Try again\n\n"finish);
        Sleep(2000);
        goto adminlogin;
    }else{
        return 1;
    }

userlogin:
    x = 0;
    while(1){
        system("cls");
        printf("User:\n");
        printf("******************************************\n");
        for (int i = 0; i < 3; i++){
            if(i == x){
                printf(B_yellow"%s"finish, user[i]);
            }else{
                printf(B_white"%s"finish, user[i]);
            }
            printf("\t");
        }
        printf("\n\n");
        key = getch();
        if((key == 'A' || key =='a' || key == 75) && (x-1) > -1){
            x -= 1;
        }
        else if((key == 'D' || key =='d' || key == 77) && (x+1) < 3){
            x += 1;
        }
        else if(key == '\r'){
            strcpy(word, user[x]);
            break;
        }
    }
    if(!strcmp(word,"[Back]"))
        goto cmod;
    else if(!strcmp(word,"[Regist]"))
        goto regist;
    else if(!strcmp(word,"[Log in]")){
        int i = 0;
        char c;
        printf("Account Name: \n");
        printf("Phone Number: ");
        printf(Move_the_cursor_up_one "" finish);
        while((c = getch()) != '\r'){
            if(c =='\b' && i > 0){
                i--;
                printf(Move_the_cursor_left_1""finish);
                printf(Clear_one_word""finish);
            }
            else if(c =='\b' && i == 0){
                continue;
            }
            else if(i == 20){
                continue;
            }
            else{
                word[i] = c;
                printf("%c", word[i]);
                i++;
            }
        }
        word[i] = '\0';
        printf("\n");
        printf(Move_the_cursor_right_14 "" finish);
        i = 0;
        while((c = getch()) != '\r'){
            if(c =='\b' && i > 0){
                i--;
                printf(Move_the_cursor_left_1""finish);
                printf(Clear_one_word""finish);
            }
            else if(c =='\b' && i == 0){
                continue;
            }
            else if(i == 10){
                continue;
            }
            else{
                word2[i] = c;
                printf("%c",word2[i]);
                i++;
            }
        }
        word2[i] = '\0';
        ret = search_user(word, word2, data_amount);
    }
    if (ret == 0) {
        printf(red"\nThe phone number entered may be wrong\n\n"finish);
        Sleep(2000);
        goto userlogin;
    } else if (ret == -1) {
        printf(red"\nIncorrect user's name, please try again.\n\n"finish);
        Sleep(2000);
        goto userlogin;
    } else
        return 2;

regist:
    return 0;
}

void init(){
    strcpy(m[0].id, "AllenWong2002");
    strcpy(m[0].pw, "apex");

    strcpy(m[1].id, "nefertariii");
    strcpy(m[1].pw, "allpass");

    strcpy(m[2].id, "ChiuYiHsien");
    strcpy(m[2].pw, "1234567890");

    strcpy(m[3].id, "apin0125");
    strcpy(m[3].pw, "1234567890");

    strcpy(m[4].id, "purplecc");
    strcpy(m[4].pw, "1234567890");
}

int search_admin(char *s, char *s1){
    for (int i = 0; i < 5; i++){
        if (!strcmp(m[i].id, s) && !strcmp(m[i].pw,s1)){
            return 1;
        }
    }
    return 0;
}

int search_user(char *us, char *pn, int *data_amount){
    int d = search(pn, data_amount);
    if (d == -1){
        return 0;
    }
    else {
        if (strcmp(person[d].name, us) == 0)
            return 1;
        else
            return -1;
    }
}

void administrator(int *data_amount){
    system("cls");
    char option[2][3][9] = {{{"Add"}, {"Delete"}, {"Traverse"}},
                            {{"Sort"}, {"Search"}, {"Exit"}}};
    char select[9];
    char key;
    int x = 0, y = 0;
    while (1){
        while(1){
            system("cls");
            printf("[Administrator Interface]\n");
            printf("  <<Select Operations>>\n");
            printf("*******************************************************************\n");
            for (int i = 0; i < 2; i++){
                for (int j = 0; j < 3; j++){
                    if(i==x && j==y){
                        printf(B_U_I_yellow"%s\t\t"finish, option[i][j]);
                    }
                    else{
                        printf("%s\t\t", option[i][j]);
                    }
                }
                printf("\n\n");
            }
            key = getch();
            if((key == 'W' || key =='w' || key == 72) && check_boundary(x-1,y,2,3)){
                x -= 1;
            }
            else if((key == 'A' || key =='a' || key == 75) && check_boundary(x,y-1,2,3)){
                y -= 1;
            }
            else if((key == 'S' || key =='s' || key == 80) && check_boundary(x+1,y,2,3)){
                x += 1;
            }
            else if((key == 'D' || key =='d' || key== 77) && check_boundary(x,y+1,2,3)){
                y += 1;
            }
            else if(key == '\r'){
                strcpy(select, option[x][y]);
                break;
            }
        }
        if (strcmp(select, "Exit") == 0){
            break;
        } 
        else if(strcmp(select, "Add") == 0){
            add_account(data_amount);
        }
        else if(strcmp(select, "Delete") == 0){
            char pnum[50];
            int k;
            printf("Enter phone number: ");
            scanf("%s", pnum);
            k = search(pnum, data_amount);
            if (k != -1){
                for (int i = k; i < *data_amount - 1; i++){
                    person[i] = person[i + 1];
                }
                (*data_amount)--;
                write_file(data_amount);
                system("cls");
                printf(B_yellow"successfully deleted !\n\n"finish);
                Sleep(2000);
            }
            else{
                system("cls");
                printf(red"Not exist\n\n"finish);
                Sleep(2000);
            }
        }
        else if(strcmp(select, "Traverse") == 0){
            traverse(*data_amount);
        }
        else if(strcmp(select, "Search") == 0){
            char pnum[50];
            int k;
            printf("Enter phone number: ");
            scanf("%s", pnum);
            k = search(pnum, data_amount);
            if (k != -1){
                system("cls");
                printf(B_U_I_yellow"Here is the person's progile\n"finish);
                printf(B_I_green"*******************************************************************\n"finish);
                printf(B_cyan"Name: %s\n", person[k].name);
                printf("Phone Number: %s\n", person[k].phone_number);
                printf("Gender: %c\n", person[k].gender);
                printf("Sexual Orientation: %c\n", person[k].target);
                printf("Age: %d\n", person[k].age);
                printf("Height: %.1f\n", person[k].height);
                printf("City: %s\n", person[k].area);
                printf("Zodiac: %s\n", person[k].zodiac);
                printf("Job: %s\n", person[k].job);
                printf("Income: %s\n\n"finish, person[k].income);
                printf(B_U_I_yellow"Hobbies:\n"finish);
                printf(B_I_green"*******************************************************************\n"finish);
                printf(B_cyan"%s\n", person[k].hobby[0]);
                printf("%s\n", person[k].hobby[1]);
                printf("%s\n", person[k].hobby[2]);
                printf("%s\n", person[k].hobby[3]);
                printf("%s\n\n", person[k].hobby[4]);
                printf(B_U_I_yellow"Self introduction:\n"finish);
                printf(B_I_green"*******************************************************************\n"finish);
                printf(B_cyan"%s\n"finish, person[k].self_introduction);
                printf(B_BLUE"Press enter to continue..."finish);
                getchar();
                getchar();
            }
            else{
                system("cls");
                printf(red"Not exist\n\n"finish);
                Sleep(2000);
            }
        }
        else if(strcmp(select, "Sort") == 0){
            sort(data_amount);
        }
    }
    return;
}

void traverse(int data_amount){
    char operation[3][6] = {{"Next"}, {"Prior"}, {"Exit"}};
    int position = 0;
    int now = 0;
    char key;
    while(1){
        while(1){
            system("cls");
            printf(B_U_I_yellow"Personal Profile\n"finish);
            printf(B_I_green"*******************************************************************\n"finish);
            printf(B_cyan"Name: %s\n", person[now].name);
            printf("Phone Number: %s\n", person[now].phone_number);
            printf("Gender: %c\n", person[now].gender);
            printf("Sexual Orientation: %c\n", person[now].target);
            printf("Age: %d\n", person[now].age);
            printf("Height: %.1f\n", person[now].height);
            printf("City: %s\n", person[now].area);
            printf("Zodiac: %s\n", person[now].zodiac);
            printf("Job: %s\n", person[now].job);
            printf("Income: %s\n\n"finish, person[now].income);
            printf(B_U_I_yellow"Hobbies:\n"finish);
            printf(B_I_green"*******************************************************************\n"finish);
            printf(B_cyan"%s\n", person[now].hobby[0]);
            printf("%s\n", person[now].hobby[1]);
            printf("%s\n", person[now].hobby[2]);
            printf("%s\n", person[now].hobby[3]);
            printf("%s\n\n", person[now].hobby[4]);
            printf(B_U_I_yellow"Self introduction:\n"finish);
            printf(B_I_green"*******************************************************************\n"finish);
            printf(B_cyan"%s\n"finish, person[now].self_introduction);
            for (int i = 0; i < 3; i++){
                if(i == position){
                    printf(B_yellow"%s"finish, operation[i]);
                }else{
                    printf(B_white"%s"finish, operation[i]);
                }
                printf("\t");
            }
            key = getch();
            if((key == 'A' || key =='a' || key == 75) && (position - 1) > -1){
                position -= 1;
            }
            else if((key == 'D' || key =='d' || key == 77) && (position + 1) < 3){
                position += 1;
            }
            else if(key == '\r'){
                break;
            }
        }
        if(position==0){
            now++;
            if(now==data_amount){
                now = 0;
            }
        }else if(position==1){
            now--;
            if(now==-1){
                now = data_amount-1;
            }
        }else if(position==2){
            break;
        }
    }
}

int search(char *pnum, int *data_amount){
    for (int i = 0; i < *data_amount; i++){
        if (!strcmp(pnum,person[i].phone_number)){
            return i;
        }
    }
    return -1;
}

void sort(int *data_amount){
    int x = 0, y = 0;
    char option[2][4][7] = {{{"Gender"}, {"Phone"}, {"Area"}, {"Target"}},
                            {{"Height"}, {"Zodiac"}, {"Age"}, {"Income"}}};
    char temp[7];
    char key;
    while(1){
        system("cls");
        printf("Choose the target you want to sort:\n");
        printf("*******************************************************************\n");
        for (int i = 0; i < 2; i++){
            for (int j = 0; j < 4; j++){
                if(i==x && j==y){
                    printf(B_U_I_yellow"%s\t\t"finish, option[i][j]);
                }
                else{
                    printf("%s\t\t", option[i][j]);
                }
            }
            printf("\n\n");
        }
        key = getch();
        if((key == 'W' || key =='w' || key == 72) && check_boundary(x-1,y,2,4)){
            x -= 1;
        }
        else if((key == 'A' || key =='a' || key == 75) && check_boundary(x,y-1,2,4)){
            y -= 1;
        }
        else if((key == 'S' || key =='s' || key == 80) && check_boundary(x+1,y,2,4)){
            x += 1;
        }
        else if((key == 'D' || key =='d' || key== 77) && check_boundary(x,y+1,2,4)){
            y += 1;
        }
        else if(key == '\r'){
            strcpy(temp, option[x][y]);
            break;
        }
    }
    printf("%s\n", temp);
    if (!strcmp(temp, "Gender"))
        qsort(person, *data_amount, sizeof(Data), cmp_gender);
    else if (!strcmp(temp, "Phone"))
        qsort(person, *data_amount, sizeof(Data), cmp_phone);
    else if (!strcmp(temp, "Area"))
        qsort(person, *data_amount, sizeof(Data), cmp_area);
    else if (!strcmp(temp, "Target"))
        qsort(person, *data_amount, sizeof(Data), cmp_target);
    else if (!strcmp(temp, "Height"))
        qsort(person, *data_amount, sizeof(Data), cmp_height);
    else if (!strcmp(temp, "Age"))
        qsort(person, *data_amount, sizeof(Data), cmp_age);
    else if (!strcmp(temp, "Zodiac"))
        qsort(person, *data_amount, sizeof(Data), cmp_zodiac);
    else if (!strcmp(temp, "Income"))
        qsort(person, *data_amount, sizeof(Data), cmp_income);
    write_file(data_amount);
    system("cls");
    printf(B_yellow"successfully sorted !\n\n"finish);
    Sleep(2000);
}

int cmp_gender(const void *a, const void *b){
    char c = ((Data *)a)->gender;
    char d = ((Data *)b)->gender;
    return d - c; 
}

int cmp_phone(const void *a, const void *b){
    char *c = ((Data *)a)->phone_number;
    char *d = ((Data *)b)->phone_number;
    return strcmp(c, d); 
}

int cmp_area(const void *a, const void *b){
    int c = ((Data *)a)->index_of_area;
    int d = ((Data *)b)->index_of_area;
    return c - d; 
}

int cmp_target(const void *a, const void *b){
    char c = ((Data *)a)->target;
    char d = ((Data *)b)->target;
    return d - c;
}

int cmp_height(const void *a, const void *b){
    int c = ((Data *)a)->height;
    int d = ((Data *)b)->height;
    return c - d; 
}

int cmp_age(const void *a, const void *b){
    int c = ((Data *)a)->age;
    int d = ((Data *)b)->age;
    return c - d; 
}

int cmp_zodiac(const void *a, const void *b){
    char zo[12][30] = {"Capricorn","Aquarius","Pisces","Aries","Taurus","Gemini","Cancer","Leo","Virgo","Libra","Scorpio","Sagittarius"};
    char* c = ((Data *)a)->zodiac;
    char* d = ((Data *)b)->zodiac;
    int e;
    int f;
    for (int i = 0; i < 12; i++){
        if (strcmp(c, zo[i]) == 0)
            e = i;
        if (strcmp(d, zo[i]) == 0)
            f = i;
    }
    return e - f;
}

int cmp_income(const void *a, const void *b){
    char Income[4][10] = {"<100", "100~300", "300~500", ">500"};
    char* c = ((Data *)a)->income;
    char* d = ((Data *)b)->income;
    int e;
    int f;
    for (int i = 0; i < 4; i++){
        if (strcmp(c, Income[i]) == 0)
            e = i;
        if (strcmp(d, Income[i]) == 0) 
            f = i;
    }
    return e - f; 
}

void write_file(int *data_amount){
    const char *filename = "output.txt";
    FILE *output_file = fopen(filename, "w");
    for (int i = 0; i < *data_amount; i++){
        fprintf(output_file, "%s %c %s %s %s %s %s %s %s %c %d %.1f %s %s %s %s"
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
        , person[i].self_introduction);
    } 
    fclose(output_file);
    return;
}

void very_cool(int like_people, int x, int y, char yes_no[1][2][6], char send[6], int *data_amount, char like[20][100]){
    int g = 0;
    int count_del=0;
    while(1){
        if(count_del >= 3){
            printf(B_U_I_yellow"You cannot delete more people today!\n\n"finish);
            printf(B_U_I_yellow"Please push the 'SEND' button\n\n"finish);
        }
        else{
            printf(B_U_I_yellow"You can delete at most 3 people today!\n\n"finish);
        }
        for (int i = 0; i < like_people; i++){
            if(i==g){
                printf(B_U_I_yellow"%s    \t"finish, like[i]);
            }
            else{
                printf(DBLUE"%d."finish, i+1);
                printf("%s    \t", like[i]);
            }
            printf("\n");
        }
        if(g == like_people){
            printf(B_U_I_yellow"%s    \t"finish, send);
        }
        else{
            printf("%s    \t", send);
        }
        char k;
        k = getch();
        if((k == 'W' || k =='w' || k == 72) && check_boundary2(g-1)){
            g -= 1;
        }
        else if((k == 'S' || k =='s' || k == 80) && check_boundary2(g+1+count_del)){
            g += 1;
        }
        else if(k == '\r' && g == like_people){
            system("cls");
            printf("Waiting for the resault......\n");
            Sleep(3000);
            system("cls");
            break;
        }
        else if(k == '\r' && count_del < 3){
            system("cls");
            Like *first = head;
            for(int i = 0; i < g; i++){
                    first = first->next;
                }
            while(1){
                printf("\n\n");
                printf(PURPLE"%s\n"finish , first->name);
                printf("\n\n");
                printf(B_purple"__________________________________________________\n\n\n"finish);
                printf(B_white"Gender :%c\n"finish , first->gender);
                printf(B_white"Age    :%d\n"finish , first->age);
                printf(B_white"Height :%.1f\n"finish , first->height);
                printf(B_white"Zodiac :%s\n"finish , first->zodiac);
                printf(B_white"Area   :%s\n"finish , first->area);
                printf(B_white"Hobbies:%s %s %s %s %s\n"finish , first->hobby[0] , first->hobby[1] , first->hobby[2] , first->hobby[3] , first->hobby[4]);
                printf(B_white"Job    :%s\n"finish , first->job);
                printf(B_white"Phone Numbers    :%s\n"finish , first->phone_number);
                printf(B_white"Self introduction :\n  %s\n"finish , first->self_introduction);
                printf(B_purple"__________________________________________________\n\n\n"finish);
                printf("\n\nAre you sure to delete her/him?: ");
                for(int i = 0;i < 1;i++){
                    for(int j = 0;j < 2;j++){
                        if(i == x && j == y ){
                            if(y == 0)printf(B_I_BA_green"\t%s"finish,yes_no[i][j]);
                            else if(y == 1)printf(B_I_BA_red"\t%s"finish,yes_no[i][j]);
                        }
                        else
                            printf("\t%s",yes_no[i][j]);
                    }
                }
                printf("\n\n");
                char key;
                key = getch();
                if((key == 'A' || key == 'a' || key == 75) && ((y - 1) >= 0)){
                    y-=1;
                }
                else if((key == 'D' || key =='d' || key == 77) && ((y + 1) <= 1)){
                    y+=1;
                }
                else if(key == '\r' && !strcmp(yes_no[x][y]," YES ")){
                    count_del++;
                    like_people--;
                    relike(g, like_people, like);
                    break;
                }
                else if(key == '\r' && !strcmp(yes_no[x][y]," NO ")){
                    break;
                }
                system("cls");
            }
        }
        system("cls");
    }
    match(data_amount, like_people);
}

void relike(int g, int like_people, char like[20][100]){ //刪除節點並且把後面接好
    int find = g-1;
    Like *ptr = head, *del, *cool;
    if(head == NULL){
        printf("Nothing\n");
    }
    if(find == -1){
        del = head;
        head = head->next;
        cool = head;
    }
    else{
        while(find--){
            ptr = ptr->next;
        }
        del = ptr->next;
        ptr->next = ptr->next->next;
    }
    free(del);
    memset(like, 0, sizeof(&like));
    cool = head;
    for(int i = 0; i < like_people; i++){// 重新把like陣列搞好
        strcpy(like[i], cool->name);
        cool = cool->next;
    }
}

void choose(int i, int like_people, char like[20][100]){     //存喜歡的人 
    cur =(Like *) malloc(sizeof(Like));
    strcpy(cur->name, correct_person[i].name);
    strcpy(like[i], correct_person[i].name); // 喜歡的人存到like陣列裡面ㄛ
    cur->gender = correct_person[i].gender;
    strcpy(cur->hobby[0], correct_person[i].hobby[0]);
    strcpy(cur->hobby[1], correct_person[i].hobby[1]);
    strcpy(cur->hobby[2], correct_person[i].hobby[2]);
    strcpy(cur->hobby[3], correct_person[i].hobby[3]);
    strcpy(cur->hobby[4], correct_person[i].hobby[4]);
    strcpy(cur->phone_number, correct_person[i].phone_number);
    strcpy(cur->area, correct_person[i].area);
    cur->target = correct_person[i].target;
    cur->age = correct_person[i].age;
    cur->height = correct_person[i].height;
    strcpy(cur->zodiac, correct_person[i].zodiac);
    strcpy(cur->income, correct_person[i].income);
    strcpy(cur->job, correct_person[i].job);
    strcpy(cur->self_introduction, correct_person[i].self_introduction);
    if(like_people == 0){
        head = cur;
    }
    else{
        pre -> next = cur;
    }
    cur -> next = NULL;
    pre = cur;
}

void match(int *data_amount, int like_people){
    int loca[5]={0};
    srand(time(NULL));
    int i, n , counter[like_people];
    for(int i = 0; i < like_people; i++){
        counter[i]=0;
    }
    for(i = 0; i < 5 ; i++){  // 隨機選5個不重複數字
        do{
            n = rand()%like_people;
            loca[i] = n;
        }while(counter[n-1]!= 0);
        counter[n-1]++;
    }
    matching_success(loca , data_amount);
}

void delete_like(){ // 清空整個list
    Like *temp=head, *del ;
    while(temp->next!=NULL){
        del = temp;
        temp = temp->next;
        free(del);
    }
}

bool check_boundary2(int x){
    if(x<0 || x>20){
        return false;
    }
    return true;
}

void matching_success(int loca[], int *data_amount){
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
        printf(B_white"Income :%s\n"finish , first2 -> income);
        printf(B_white"Phone Numbers    :%s\n"finish , first2 -> phone_number);
        printf(B_white"Self introduction :\n  %s\n"finish , first2 -> self_introduction);
        printf(B_purple"__________________________________________________\n\n\n"finish);
        matched[j] = first2;
        first2 = head;
    }
    printf(B_white"\n\nTake good use of the phone numbers and get to know each others!\n"finish);
    printf(B_white"Who do you like the most?\n"finish);
    printf(B_white"[1]%s [2]%s [3]%s [4]%s [5]%s [6]None : "finish , matched[0]->name , matched[1]->name , matched[2]->name , matched[3]->name , matched[4]->name);
    scanf("%d" , &choice);
    system("cls");
    if (choice == 6) {                  // doesn't like anyone
        printf(B_white"Do you want to keep pairing or exiting the app?\n"finish);
        printf(B_white"[1]Pairing [2]exit : "finish);
        scanf("%d" , &choice);
        if (choice == 1) {          // pairing
            delete_like();
            printf(B_B_red"Please wait for a seconds\n"finish);
            Sleep(2000);
            printf("\n\n");
            system("cls");
            printf(B_white"Welcome! It's a whole new day.\n"finish);
            Sleep(2000);
            return;
        }
        else{
            system("cls");
            printf(B_white"Bye Bye! See ya next time!\n"finish);
            exit(0);
        }
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
        fprintf(output_file , "Income:%s\n", matched[choice - 1]->income);
        fprintf(output_file , "Phone Numbers: %s\n" , matched[choice - 1] -> phone_number);
        fprintf(output_file , "Self introduction :\n  %s\n\n" , matched[choice - 1] -> self_introduction);
        fclose(output_file);
        exit(0);
    }
}
