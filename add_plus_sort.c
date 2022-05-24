#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define finish          "\033[0m"
#define light           "\033[01m"
#define black           "\033[30m"
#define B_B_red         "\033[1;31;43m"
#define B_I_green       "\033[1;3;32m"
#define B_U_I_yellow    "\033[1;3;4;33m"
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
} Data;

int read_file();
void add_account(int *data_amount);
bool search_duplicates(int data_amount);
bool check_boundary(int x, int y);
void print_data(int data_amount);

void calculate_score(Data *User,int *data_amount);
int judge_mode(Data *User);                            // 回傳使用者性向狀況
void sexuality_score(Data *User,int *data_amount);
void age_score(Data *User,int *data_amount);
void area_score(Data *User,int *data_amount);
void hobby_score(Data *User,int *data_amount);
int comp(const void *p, const void *q);
void display(int *data_amount);

char hobbies[6][5][13] = {{{"Writing"}, {"Reading"}, {"Singing"}, {"Photography"}, {"Gardening"}},
                        {{"Cooking"}, {"Baking"}, {"Jogging"}, {"Swimming"}, {"Working-out"}},
                        {{"badminton"}, {"Tennis"}, {"Basketball"}, {"Volleyball"},{"Cycling"}},
                        {{"Dancing"}, {"Films"}, {"Fashion"}, {"Collecting"}, {"Music"}},
                        {{"Anime"}, {"Delicacy"}, {"Shopping"}, {"Yoga"}, {"Memes"}},
                        {{"Diving"},{"Sunbathing"},{"Piano"},{"Guitar"},{"Makeup"}}};
char decision[2][27] = {"Yes", "No(enter my profile again)"};
bool hobbies_flag[6][5];
Data person[1000];

int main(){
    int data_amount = 0;
    data_amount = read_file();
    printf("%d\n", data_amount);                            // 看讀到的人數對不對
    printf("%lf\n", (double)clock() / CLOCKS_PER_SEC);      // 讀檔時間(/s)
    add_account(&data_amount);
    calculate_score(&person[data_amount-1], &data_amount);
    qsort(person,data_amount,sizeof(Data),comp);
    print_data(data_amount);
    display(&data_amount);
    printf("You skip too many people today!\n");
    printf("%d\n", data_amount);
}

int read_file(){
    int i = 0;                                    // 檔名要記得改自己txt的名字喔
    const char *filename = "allen.txt";
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
        i++;
    }
    fclose(input_file);
    return i;
}

void print_data(int data_amount){
//     for (int i = 0; i < data_amount; i++){
//         printf("%s %c %s %s %s %s %s %s %s %c %d %.1f %s %s %s\n%s\n"
//         , person[i].name
//         , person[i].gender
//         , person[i].hobby[0]
//         , person[i].hobby[1]
//         , person[i].hobby[2]
//         , person[i].hobby[3]
//         , person[i].hobby[4]
//         , person[i].phone_number
//         , person[i].area
//         , person[i].target
//         , person[i].age
//         , person[i].height
//         , person[i].zodiac
//         , person[i].income
//         , person[i].job
//         , person[i].self_introduction);
//     }
    // for (int i = 0; i < data_amount - 1;i++){
    //     printf("%d\n", person[i].score);
        
    // }
}

void add_account(int *data_amount){
    printf("Welecome to omni, please enter your mobile number to register before you start: ");
    scanf("%s", person[*data_amount].phone_number);
    while(search_duplicates(*data_amount)){
        printf("The phone number is already exist, please enter another phone number: ");
        scanf("%s", person[*data_amount].phone_number);
    }
    printf("Great! Let's create your personal profile!\n");
    while(1){
        for (int i = 0; i < 6;i++){
            for (int j = 0; j < 5;j++){
                hobbies_flag[i][j] = 0;
            }
        }
        printf("Name: ");
        scanf("%s", person[*data_amount].name);
        printf("Gender: ");
        scanf(" %c", &person[*data_amount].gender);
        printf("Sexual Orientation: ");
        scanf(" %c", &person[*data_amount].target);
        printf("Age: ");
        scanf("%d", &person[*data_amount].age);
        printf("Height: ");
        scanf("%f", &person[*data_amount].height);
        printf("City: ");
        scanf("%s", person[*data_amount].area);
        printf("Zodiac: ");
        scanf("%s", person[*data_amount].zodiac);
        printf("Job: ");
        scanf("%s", person[*data_amount].job);
        printf("Income: ");
        scanf("%s", person[*data_amount].income);
        char absorb_return;
        scanf("%c", &absorb_return);
        printf("Write something to introduce yourself: \n");
        fgets(person[*data_amount].self_introduction, 151, stdin);
        int x = 0, y = 0;
        int count_hobby = 0;
        while(1){
            system("cls");
            printf("\nAfter filling out the basic information, let's Choose 5 hobby from the following list:\n\n");
            char key;
            for (int i = 0; i<6; i++){
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
                printf("\n");
            }
            key = getch();
            if((key == 'W' || key =='w' || key == 72) && check_boundary(x-1,y)){
                x -= 1;
            }
            else if((key == 'A' || key =='a' || key == 75) && check_boundary(x,y-1)){
                y -= 1;
            }
            else if((key == 'S' || key =='s' || key == 80) && check_boundary(x+1,y)){
                x += 1;
            }
            else if((key == 'D' || key =='d' || key== 77) && check_boundary(x,y+1)){
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
            break;
        }
        system("cls");
    }
    (*data_amount)+=1;
}

bool search_duplicates(int data_amount){
    for (int i = 0; i < data_amount; i++){
        if(!strcmp(person[i].phone_number, person[data_amount].phone_number)){
            return true;
        }
    }
    return false;
}

bool check_boundary(int x, int y){
    if(x<0 || x>5 || y<0 || y>4){
        return false;
    }
    return true;
}
//* 柯的
void calculate_score(Data *User,int *data_amount){
    sexuality_score(User,data_amount);
    age_score(User,data_amount);
    area_score(User,data_amount);
    hobby_score(User,data_amount);
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

void sexuality_score(Data *User,int *data_amount){     // 性向對了+500
    int mode = judge_mode(User);
    int i = 0;
    if(mode == 1){
        for ( i = 0; i < *data_amount; i++){
            if((person + i)->gender == 'M' && (person + i)->target == 'F'){
                (person + i)->score += 500;                  
            }
            else{
                (person + i)->score = 0;
            }
        }
    }
    else if(mode == 2){
        for ( i = 0; i < *data_amount; i++){
            if((person + i)->gender == 'F'){
                if((person + i)->target == 'F' || (person + i)->target == 'B')
                    (person + i)->score += 500;
            }
            else{
                (person + i)->score = 0;
            }
        }
    }
    else if(mode == 3){
        for ( i = 0; i < *data_amount; i++){
            if((person + i)->target == 'F' || (person + i)->target == 'B')
                (person + i)->score += 500;
            else{
                (person + i)->score = 0;
            }
        }
    }
    else if(mode == 4){
        for ( i = 0; i < *data_amount; i++){
            if((person + i)->gender == 'F' && (person + i)->target == 'M'){
                (person + i)->score += 500;
            }
            else{
                (person + i)->score = 0;
            }
        }
    }
    else if(mode == 5){
        for ( i = 0; i < *data_amount; i++){
            if((person + i)->gender == 'M'){
                if((person + i)->target == 'M' || (person + i)->target == 'B')
                    (person + i)->score += 500;
            }
            else{
                (person + i)->score = 0;
            }
        }
    }
    else if(mode == 6){
        if((person + i)->target == 'M' || (person + i)->target == 'B')
                (person + i)->score += 500;
            else{
                (person + i)->score = 0;
            }
    }
}


void age_score(Data *User,int *data_amount){           // 年齡對了+100
    for(int i = 0;i < *data_amount;i++){
        if(abs(((person + i)->age)- (User->age))<=10){
            (person + i)->score += 100;
        }
    }
}

void area_score(Data *User,int *data_amount){          // 距離差0加100,差1加90,差2加80...10以上不加了
    for(int i = 0;i < *data_amount;i++){
        int ans = abs(((person + i)->index_of_area)- (User->index_of_area));
        if(ans == 0){
            (person + i)->score += 100;
        }
        else if(ans < 10){
            (person + i)->score += ((10-i)*10);
        }
    }
}

void hobby_score(Data *User,int *data_amount){         //每對一個+20
    for(int i = 0;i < 5;i++){       
        for(int j = 0;j < *data_amount;j++){
            for(int k = 0;k < 5;k++){
                if(!strcasecmp(User->hobby[i],(person + j)->hobby[k]))
                    (person + j)->score += 20;
            }
        }
    }
}

int comp(const void *p,const void *q){
    return (((Data *)q)->score - ((Data *)p)->score);
}

void display(int *data_amount){
    int x = 0,y = 0;
    char yes_no[1][2][6];
    strcpy(yes_no[0][0], " YES ");
    strcpy(yes_no[0][1], " NO ");
    for(int i = 0;i < *data_amount;i++){
        system("cls");
        if(person[i].score >= 500){
            while(1){
            printf(BACK_YELLOW"\nFIND YOUR SOUL MATE!\n\n"finish);
            printf(B_U_I_yellow"***************************************************************************\n\n"finish); //看能不能把justify拿出來用 再修改邊幅
            int space = (70 - strlen(person[i].name))/2;
            for(int j = 0;j < space;j++){
                printf(" ");
            }
            printf(B_BLUE"%s\n"finish,person[i].name);
            printf(B_BLUE"Gender :%c\n"finish,person[i].gender);
            printf(B_BLUE"Age    :%d\n"finish,person[i].age);
            printf(B_BLUE"Area   :%s\n"finish,person[i].area);
            printf(B_BLUE"Hobbies:%s %s %s %s %s\n"finish,person[i].hobby[0],person[i].hobby[1],person[i].hobby[2],person[i].hobby[3],person[i].hobby[4]);
            printf(B_PURPLE"Self introduction :\n  %s\n\n"finish,person[i].self_introduction);  //justify內容?
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
            else if(key == '\r' ){
                break;
            }
            system("cls");
            }
        }
    }
}