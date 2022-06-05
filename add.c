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
#define B_I_BA_red      "\033[1;3;31m"

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
bool check_boundary(int x, int y, int row, int col);
void print_data(int data_amount);
bool check_height(char *str);

Data person[1000];

int main(){
    int data_amount = 0;
    data_amount = read_file();
    printf("%d\n", data_amount);                            // 看讀到的人數對不對
    printf("%lf\n", (double)clock() / CLOCKS_PER_SEC);      // 讀檔時間(/s)
    add_account(&data_amount);
    //print_data(data_amount);
}

int read_file(){
    int i = 0;                                    // 檔名要記得改自己txt的名字喔
    const char *filename = "nefertari.txt";
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
    for (int i = 0; i < data_amount - 1;i++){
        printf("%d\n", person[i].index_of_area);
        
    }
}

void add_account(int *data_amount){
    char hobbies[6][5][13] = {{{"Writing"}, {"Reading"}, {"Singing"}, {"Photography"}, {"Gardening"}},
                            {{"Cooking"}, {"Baking"}, {"Jogging"}, {"Swimming"}, {"Working-out"}},
                            {{"badminton"}, {"Tennis"}, {"Basketball"}, {"Volleyball"},{"Cycling"}},
                            {{"Dancing"}, {"Films"}, {"Fashion"}, {"Collecting"}, {"Music"}},
                            {{"Anime"}, {"Delicacy"}, {"Shopping"}, {"Yoga"}, {"Memes"}},
                            {{"Diving"},{"Sunbathing"},{"Piano"},{"Guitar"},{"Makeup"}}};
    char decision[2][27] = {"Yes", "No(enter my profile again)"};
    char cities[4][5][11] = {{{"Keelung"}, {"New-Taipei"}, {"Taipei"}, {"Taoyuan"}, {"Hsinchu"}},
                            {{"Miaoli"}, {"Taichung"}, {"Changhua"}, {"Nantou"}, {"Yunlin"}},
                            {{"Chiayi"}, {"Tainan"}, {"Kaohsiung"}, {"Pintung"}, {"Yilan"}},
                            {{"Hualien"}, {"Taitung"}, {"Penghu"}, {"Kinmen"}, {"Lienchiang"}}};
    char Zodiac[3][4][12] = {{{"Capricorn"}, {"Aquarius"}, {"Pisces"}, {"Aries"}},
                            {{"Taurus"}, {"Gemini"}, {"Cancer"}, {"Leo"}},
                            {{"Virgo"}, {"Libra"}, {"Scorpio"}, {"Sagittarius"}}};
    char Income[4][8] = {{"<100"}, {"100~300"}, {"300~500"}, {">500"}};
    bool hobbies_flag[6][5];
    printf("Welecome to omni, please enter your mobile number to register before you start: ");
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
            printf("The phone number is already exist, please enter another phone number: ");
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
        }
        else if((person[*data_amount].phone_number[0]!='0' || person[*data_amount].phone_number[1] !='9') || strlen(person[*data_amount].phone_number)!=10 || invalid == true){
            printf("The phone number format is invalid! Please ensure your input are correct:\n");
            printf("Enter your phone number again: ");
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
        }
    }
    printf("Next, please enter your age. We have to make sure you are of age: ");
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
            printf("You are too young to register an account, please enter again\n");
            printf("Please renter your age: ");
            scanf("%s", temp_a);
            continue;
        }
        else if(atoi(temp_a)==0 || atoi(temp_a)>120 || invalid == true){
            printf("Invalid input! Please ensure your input are real age and must be an integer\n");
            printf("Please renter your age: ");
            scanf("%s", temp_a);
            continue;
        }
    }
    person[*data_amount].age = atoi(temp_a);
    printf("Great! Let's create your personal profile!\n");
    Sleep(2000);
    system("cls");
    while(1){
        memset(hobbies_flag, false, sizeof(hobbies_flag));
        int print_to_where = 0;
        int count = 0;
        int cx = 0, cy = 0;
        int zx = 0, zy = 0;
        int ix = 0;
        while(1){
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
                printf(B_I_BA_red"Invalid input !!! Please enter again\n"finish);
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
                printf(B_I_BA_red"Invalid input !!! Please enter again\n"finish);
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
            if(check_height(temp_h) == false){
                system("cls");
                printf(B_I_BA_red"Invalid input !!! Please enter again\n"finish);
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
            if((key == 'W' || key =='w' || key == 72) && check_boundary(x-1,y,6,5)){
                x -= 1;
            }
            else if((key == 'A' || key =='a' || key == 75) && check_boundary(x,y-1,6,5)){
                y -= 1;
            }
            else if((key == 'S' || key =='s' || key == 80) && check_boundary(x+1,y,6,5)){
                x += 1;
            }
            else if((key == 'D' || key =='d' || key== 77) && check_boundary(x,y+1,6,5)){
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
    printf("%d\n", *data_amount);
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
    if(x < 0 || x > row-1 || y < 0 || y > col-1){
        return false;
    }
    return true;
}

bool check_height(char *str){
    int count = 0;
    while((*str)!='\0'){
        if((*str)=='.'){
            count++;
        }
        if((isdigit(*str)==0 && (*str)!='.') || count>1){
            return false;
        }else{
            str += 1;
        }
    }
    return true;
}