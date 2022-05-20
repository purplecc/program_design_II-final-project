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
//#define  "\x1B[1;30m"

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
    //int index_of_area;
    char self_introduction[151];
} Data;

int read_file(Data *person);
void add_account(Data *person, int *data_amount);
bool search_duplicates(Data *person, int data_amount);
bool check_boundary(int x, int y);

char hobbies[6][5][13] = {{{"Writing"}, {"Reading"}, {"Singing"}, {"Photography"}, {"Gardening"}},
                        {{"Cooking"}, {"Baking"}, {"Jogging"}, {"Swimming"}, {"Working-out"}},
                        {{"badminton"}, {"Tennis"}, {"Basketball"}, {"Volleyball"},{"Cycling"}},
                        {{"Dancing"}, {"Films"}, {"Fashion"}, {"Collecting"}, {"Music"}},
                        {{"Anime"}, {"Delicacy"}, {"Shopping"}, {"Yoga"}, {"Memes"}}};
char decision[2][27] = {"Yes", "No(enter my profile again)"};
bool hobbies_flag[6][5];

int main(){
    int data_amount = 0;
    Data person[1000];
    data_amount = read_file(person);
    printf("%d\n", data_amount);                            // 看讀到的人數對不對
    printf("%lf\n", (double)clock() / CLOCKS_PER_SEC);      // 看整個程式執行時間(/s)
    add_account(person, &data_amount);
}

int read_file(Data *person){
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

void add_account(Data *person, int *data_amount){
    printf("Welecome to omni, please enter your mobile number to register before you start: ");
    scanf("%s", person[*data_amount].phone_number);
    while(search_duplicates(person, *data_amount)){
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
            printf("Age: %s\n\n"finish, person[*data_amount].income);
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
    printf("%d\n", *data_amount);
}

bool search_duplicates(Data *person, int data_amount){
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