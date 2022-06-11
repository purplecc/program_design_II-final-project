#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
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
    int flag;                                          // 是否被喜歡過
} Data;

typedef struct {
    char id[21];
    char pw[21];
} ad;

void swap(Data *a, Data *b){
    Data temp = *a;
    *a = *b;
    *b = temp;
}


char *ltrim(char *s){
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s){
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s){
    return rtrim(ltrim(s));
}

bool check_height(char *str);
bool check_boundary(int x, int y, int row, int col);
void add(int *data_amount);
int read_file(char *file);//
bool search_duplicates(int data_amount);

void addusr(int *data_amount);
void print_data(int *data_amount);//all
void sort(int *data_amount);
void init();
int login(int *data_amount);
int search_user(char *us, char *pn, int *data_amounts);
int search_admin(char *s);
int search(int pnum, int *data_amount);
void administrator(int *data_amount);
void user(int *data_amount);
void print(int id);//single
void write_file(int *data_amount, char *s);
int cmp_gender(const void *a, const void *b);
int cmp_phone(const void *a, const void *b);
int cmp_area(const void *a, const void *b);
int cmp_target(const void *a, const void *b);
int cmp_height(const void *a, const void *b);
int cmp_age(const void *a, const void *b);
int cmp_zodiac(const void *a, const void *b);
int cmp_income(const void *a, const void *b);

Data person[1000];
ad m[5];

int main(){
    int data_amount;
    int mode;
    data_amount = 0;
    init();
    data_amount = read_file("all.txt");
    while (1){
        mode = login(&data_amount);
        if (mode == -1) break;
        if (mode)
            administrator(&data_amount);
        else 
            user(&data_amount);
    }
    write_file(&data_amount, "all.txt");//
    return 0;
}
int login(int *data_amount){
    char *namePtr;
    char *Ptr;
    char buffer[1024];
    char buffer1[1024];
    int ret;
    char w;

cmod:
    printf("enter 'u' or 'a' to change mode\n");
    scanf("%c", &w);
    getchar();
    if (w == 'u'){
        goto userlogin;
    }
    else if (w == 'a'){
        goto adminlogin;
    }
    else {

        return -1;
    }
adminlogin:
    printf("enter your github id, enter 'BACK' to go back\n");
    namePtr = fgets(buffer, 1024, stdin);    
    //將字串前後的非ASCII的符號去掉
    namePtr = trim(namePtr);

    if (strcmp(namePtr,"BACK") == 0)
        goto cmod;
    ret = search_admin(namePtr);
    //if admin doesn't exist -> relogin
    if (ret == 0) {
        printf("Administrator '%s' doesn't exist\n", namePtr);
        goto adminlogin;
    } else    
        return 1;//administrator

    //printf("password: ");
    //fgets(buffer, 1024, stdin);
    //if (buffer[strlen(buffer) - 1] == '\n') {
    //    buffer[strlen(buffer) - 1] =  '\0';
    //}
    //if (CheckPassword(namePtr, buffer)) {
    //    printf("Incorrect, please try again.\n");
    //    goto adminlogin;
    //}
userlogin:
    printf("enter your name, enter 'BACK' to go back, enter 'REGIST' to regist\n");
    fgets(buffer, 1024, stdin);    
    //將字串前後的非ASCII的符號去掉
    namePtr = trim(buffer);
    if (strcmp(namePtr,"BACK") == 0)
        goto cmod;
    if (strcmp(namePtr,"REGIST") == 0)
        goto regist;

    printf("phonenumber: \n");
    fgets(buffer1, 1024, stdin);
    Ptr = trim(buffer1);

    //查詢這個使用者是否在資料庫系統中
    ret = search_user(namePtr, Ptr, data_amount);
    
    //if user's phonenumber doesn't exist -> relogin
    //else if user's name incorrect -> relogin
    //
    if (ret == 0) {
        printf("User's phonenumber '%s' doesn't exist\n", Ptr);
        goto userlogin;
    } else if (ret == -1) {
        printf("Incorrect user's name, please try again.\n");
        goto userlogin;
    } else
        return 0;
regist:
    add(data_amount);
    return 0;
}

int read_file(char *file){
    int i = 0;                                    // 檔名要記得改自己txt的名字喔
    
    FILE *input_file = fopen(file, "r");
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

 void print_data(int *data_amount){
    for (int i = 0; i < *data_amount; i++){
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
         , person[i].job
         , person[i].self_introduction);
    }     
}

void init(){
    strcpy(m[0].id, "AllenWong2002");
    strcpy(m[1].id, "nefertariii");
    strcpy(m[2].id, "ChiuYiHsien");
    strcpy(m[3].id, "apin0125");
    strcpy(m[4].id, "purplecc");
}

int search_admin(char *s){
    for (int i = 0; i < 5; i++){
        if (strcmp(m[i].id, s) == 0)
            return 1;
    }
    return 0;
}
int search_user(char *us, char *pn, int *data_amount){
    int d = search(atoi(pn) , data_amount);
    //printf("|person[%d].name|%s|\n", d, person[d].name);
    //printf("|%s|%s|\n",us, pn);
    if (d == -1){
        return 0;
    }
    else {
        if (strcmp(person[d].name, us) == 0){
            return 1;
        }
        else{
            
            //printf("%s\n%s",person[d].name,us);
            return -1;
        }
    }
}
void administrator(int *data_amount){
    char *namePtr;
    char buffer[1024];
    printf("administrator interface: \n");
    while (1){
        printf("enter 'exit' to exit\n");
        namePtr = fgets(buffer, 1024, stdin);    
        if (buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] =  '\0';
        }
        //char *p = strtok(buffer, ".");
        //p = strtok(NULL, ".");
	    if (strcmp(namePtr, "exit") == 0){
            break;
        } else if(strcmp(namePtr, "add") == 0){
            addusr(data_amount);
        } else if(strcmp(namePtr, "delete") == 0){
            int pnum;
            int k;
            printf("enter phonenumber");
            scanf("%d", &pnum);
            getchar();
            k = search(pnum, data_amount);
            if (k != -1){
                swap(&person[k], &person[*data_amount]);
                data_amount--;
            }
            else
                printf("Not exist\n");
        } else if(strcmp(namePtr, "traverse") == 0){
            print_data(data_amount);
        } else if(strcmp(namePtr, "search") == 0){
            int pnum;
            int k;
            printf("enter phonenumber");
            scanf("%d", &pnum);
            getchar();
            k = search(pnum, data_amount);
            if (k != -1)
                print(k);
            else
                printf("Not exist\n");
        } else if(strcmp(namePtr, "sort") == 0){
            printf("Enter the target you want to sort\n");
            sort(data_amount);
        } else if(strcmp(namePtr, "input") == 0){
            printf("Enter the filename you want to input\n");
            char buf[4096];
            scanf("%s ", buf);
            *data_amount = read_file(buf);
        } else if(strcmp(namePtr, "output") == 0){
            char buf[1024];
            printf("Enter the 'filename.txt' you want to output\n");
            scanf("%s ", buf);
            write_file(data_amount, buf);
        }
        else {
            printf("error\n");
        }
        
    }
    return;
}
void user(int *data_amount){
    printf("user interface\n");
    return;
}

int search(int pnum, int *data_amount){
    for (int i = 0; i < *data_amount; i++){
        if (atoi(person[i].phone_number) == pnum)
            return i;
    }
    return -1;
}

void print(int id){
    printf("%s %c %s %s %s %s %s %s %s %c %d %.1f %s %s %s\n%s\n"
         , person[id].name
         , person[id].gender
         , person[id].hobby[0]
         , person[id].hobby[1]
         , person[id].hobby[2]
         , person[id].hobby[3]
         , person[id].hobby[4]
         , person[id].phone_number
         , person[id].area
         , person[id].target
         , person[id].age
         , person[id].height
         , person[id].zodiac
         , person[id].income
         , person[id].job
         , person[id].self_introduction);
}

void add(int *data_amount){
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

void sort(int *data_amount){
    //
    /*    
    gender
    phone_number
    area
    target
    age
    height
    zodiac
    income
    */
    char temp[10];
    scanf("%s", temp);
    getchar();
        if (strcmp(temp, "gender") == 0)
            qsort(person, *data_amount, sizeof(*person), cmp_gender);
        else if (strcmp(temp, "phone") == 0)
            qsort(person, *data_amount, sizeof(*person), cmp_phone);
        else if (strcmp(temp, "area") == 0)
            qsort(person, *data_amount, sizeof(*person), cmp_area);
        else if (strcmp(temp, "target") == 0)
            qsort(person, *data_amount, sizeof(*person), cmp_target);
        else if (strcmp(temp, "height") == 0)
            qsort(person, *data_amount, sizeof(*person), cmp_height);
        else if (strcmp(temp, "age") == 0)
            qsort(person, *data_amount, sizeof(*person), cmp_age);
        else if (strcmp(temp, "zodiac") == 0)
            qsort(person, *data_amount, sizeof(*person), cmp_zodiac);
        else if (strcmp(temp, "income") == 0)
            qsort(person, *data_amount, sizeof(*person), cmp_income);
        else {
            printf("error\n");
            return;
        }
        print_data(data_amount);
}
int cmp_gender(const void *a, const void *b){
    char c = ((Data *)a)->gender;
    char d = ((Data *)b)->gender;
    return c - d; 
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
    return c - d; 
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
bool check_boundary(int x, int y, int row, int col){
    if(x<0 || x>5 || y<0 || y>4){
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
        }
        else{
            str += 1;
        }
    }
    return true;
}

void write_file(int *data_amount, char *s){
    FILE *output_file = fopen(s, "w");
    for (int i = 0; i < *data_amount; i++){
         fprintf(output_file, "%s %c %s %s %s %s %s %s %s %c %d %.1f %s %s %s\n%s\n"
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

void addusr(int *data_amount){
    
    scanf("%s %c %s %s %s %s %s %s %s %c %d %f %s %s %s "
    , person[*data_amount].name
    , &person[*data_amount].gender
    , person[*data_amount].hobby[0]
    , person[*data_amount].hobby[1]
    , person[*data_amount].hobby[2]
    , person[*data_amount].hobby[3]
    , person[*data_amount].hobby[4]
    , person[*data_amount].phone_number
    , person[*data_amount].area
    , &person[*data_amount].target
    , &person[*data_amount].age
    , &person[*data_amount].height
    , person[*data_amount].zodiac
    , person[*data_amount].income
    , person[*data_amount].job);
    fgets(person[*data_amount].self_introduction, 151, stdin);
    *data_amount++;
}
