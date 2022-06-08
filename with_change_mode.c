#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>

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

struct like{ // 存喜歡的人
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
};

typedef struct like NODE;

struct pair{ // 互相喜歡
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
};

typedef struct pair PAIR;

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
    int dest;
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
void choose(int i, int like_people);
void match();
void print_liked_ppl();
void ran();
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

char hobbies[6][5][13] = {{{"Writing"}, {"Reading"}, {"Singing"}, {"Photography"}, {"Gardening"}},
                        {{"Cooking"}, {"Baking"}, {"Jogging"}, {"Swimming"}, {"Working-out"}},
                        {{"badminton"}, {"Tennis"}, {"Basketball"}, {"Volleyball"},{"Cycling"}},
                        {{"Dancing"}, {"Films"}, {"Fashion"}, {"Collecting"}, {"Music"}},
                        {{"Anime"}, {"Delicacy"}, {"Shopping"}, {"Yoga"}, {"Memes"}},
                        {{"Diving"},{"Sunbathing"},{"Piano"},{"Guitar"},{"Makeup"}}};
char decision[2][27] = {"Yes", "No(enter my profile again)"};
int loca[5];
bool hobbies_flag[6][5];
Data person[1000];
Data correct_person[500]; 
NODE *pre, *cur, *head;  // for user like
NODE *pre2, *cur2, *head2; // for match

int main(){
    int data_amount = 0;
    data_amount = read_file();
    printf("%d\n", data_amount);                            // 看讀到的人數對不對
    printf("%lf\n", (double)clock() / CLOCKS_PER_SEC);      // 讀檔時間(/s)
    add_account(&data_amount);
    calculate_score(&person[data_amount-1], &data_amount);
    qsort(person,data_amount,sizeof(Data),comp);
    //print_data(data_amount);
    while(1) {
        display(&data_amount);
        match(&data_amount);
    }
    // printf("%d\n", data_amount);
    return 0;
}

int read_file(){
    int i = 0;                                    // 檔名要記得改自己txt的名字喔
    const char *filename = "celeste.txt";
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

void add_account(int *data_amount){ //一直到yes or no
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
            system("clear");
            printf("\nAfter filling out the basic information, let's choose 5 hobbies from the following list:\n\n");
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
            else if(key == '\n' && hobbies_flag[x][y] == false){
                strcpy(person[*data_amount].hobby[count_hobby], hobbies[x][y]);
                hobbies_flag[x][y] = true;
                count_hobby++;
            }
            if(count_hobby==5){
                sleep(2);
                break;
            }
        }
        system("clear");
        int yes_no_position = 0;
        while(1){
            system("clear");
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
            else if(key == '\n'){
                break;
            }
        }
        if(yes_no_position==0){
            break;
        }
        system("clear");
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
        for (i = 0; i < *data_amount; i++){
            if((person + i)->gender == 'M' && (person + i)->target == 'F'){
                (person + i)->score += 500;                  
            }
            else{
                (person + i)->score = 0;
            }
            (person + i)->flag = 0;
        }
    }
    else if(mode == 2){
        for (i = 0; i < *data_amount; i++){
            if((person + i)->gender == 'F'){
                if((person + i)->target == 'F' || (person + i)->target == 'B')
                    (person + i)->score += 500;
            }
            else{
                (person + i)->score = 0;
            }
            (person + i)->flag = 0;
        }
    }
    else if(mode == 3){
        for (i = 0; i < *data_amount; i++){
            if((person + i)->target == 'F' || (person + i)->target == 'B')
                (person + i)->score += 500;
            else{
                (person + i)->score = 0;
            }
            (person + i)->flag = 0;
        }
    }
    else if(mode == 4){
        for (i = 0; i < *data_amount; i++){
            if((person + i)->gender == 'F' && (person + i)->target == 'M'){
                (person + i)->score += 500;
            }
            else{
                (person + i)->score = 0;
            }
            (person + i)->flag = 0;
        }
    }
    else if(mode == 5){
        for (i = 0; i < *data_amount; i++){
            if((person + i)->gender == 'M'){
                if((person + i)->target == 'M' || (person + i)->target == 'B')
                    (person + i)->score += 500;
            }
            else{
                (person + i)->score = 0;
            }
            (person + i)->flag = 0;
        }
    }
    else if(mode == 6){
        for(i = 0 ; i < *data_amount ; i++){
            if((person + i)->target == 'M' || (person + i)->target == 'B')
                (person + i)->score += 500;
            else
                (person + i)->score = 0;
            (person + i)->flag = 0;
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
    int like_people = 0;
    NODE Like;
    char yes_no[1][2][6];
    strcpy(yes_no[0][0], " YES ");
    strcpy(yes_no[0][1], " NO ");
    NODE *pre, *cur, *head;
    int correct = 0;
    for(int i = 0;i < *data_amount;i++){
        if(person[i].score >= 500){
            correct_person[correct] = person[i];            // 對的人才會印，縮短判斷的時間
            correct++;
        }
    }
    while(like_people < 20){
        for(int i = 0;i < correct;i++){
            system("clear");
            if(correct_person[i].flag == 0 && like_people < 20){
                while(1){
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
                    else if(key == '\n' && !strcmp(yes_no[x][y]," YES ")){
                        correct_person[i].flag = 1;
                        choose(i, like_people);
                        like_people++;
                        break;
                    }
                    else if(key == '\n' && !strcmp(yes_no[x][y]," NO ")){
                        break;
                    }
                    system("clear");
                }
            }
        }
        
        printf("\n\n");
        
    }
}

void choose(int i, int like_people){     //存喜歡的人 
    cur =(NODE *) malloc(sizeof(NODE));
    strcpy(cur->name, correct_person[i].name);
    cur->gender = correct_person[i].gender;
    strcpy(cur->hobby[i], correct_person[i].hobby[i]);
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

void print_liked_ppl(){ 
    // NODE *first = head;
    //     first = head;
    //     while(first != NULL){
    //         printf("%s\n", first->name);
    //         first = first->next;
    //     }
}


void match(int *data_amount){
    NODE *first2 = head;
    int k = 0;
    int x = 0;
    srand(time(0));
    srand(time(NULL));
    int i, n , counter[20] = {0};
    for(i = 0; i < 5 ; i++){  // 隨機選5個不重複數字
        do{
            n = rand()%20;
            loca[i] = n;
        }while(counter[n-1]!= 0);
        counter[n-1]++;
    }
    matching_success(&loca , data_amount);
    // for(int j = 0; j < 5; j++){
    //     for(int i = 0; i < loca[j]; i++){
    //         first2 = first2->next;
    //     }
    //     printf("%s\n", first2->name);
    //     first2 = head;
        /*cur2 =malloc(sizeof(PAIR)); //這邊應該是用不到啦
        strcpy(cur2->name, first2->name);
        cur2->gender = first2->gender;
        for(int i = 0; i < 5; i++){
            strcpy(cur2->hobby[i], first2->hobby[i]);
        }
        strcpy(cur2->phone_number, first2->phone_number);
        strcpy(cur2->area, first2->area);
        cur2->target = first2->target;
        cur2->age = first2->age;
        cur2->height = first2->height;
        strcpy(cur2->zodiac, first2->zodiac);
        strcpy(cur2->income, first2->income);
        strcpy(cur2->job, first2->job);
        strcpy(cur2->self_introduction, first2->self_introduction);
        first2->dest = 1; //1表示喜歡user
        cur->dest = first2->dest;
        if(k == 0){
            head2 = cur2;
        }
        else{
            pre2 -> next = cur2;
        }
        cur2 -> next = NULL;
        pre2 = cur2;*/
        //k++;
        //x++;
    // }
}

void delete_like(){
    NODE *p = head->next;//p指向頭結點的下一個節點
	NODE *q;
	while (p!=NULL)
	{
		q = p->next;//q指向p的下一個節點
		free(p);   //清除p
		p = q;		//再將p指向q
	}
	head->next = NULL;
};

// 婕
void matching_success (int loca[] , int *data_amount) {
    int choice = 0;
    NODE *first2 = head;
    NODE *matched[10];
    printf(B_white"Congrats on the matches!!! Here are their information.\n\n"finish);
    for(int j = 0; j < 5; j++){
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
    delete_like();
    printf(B_white"Take good use of the phone numbers and get to know each others!\n"finish);
    printf(B_white"Who do you like the most?\n"finish);
    printf(B_white"[1]%s [2]%s [3]%s [4]%s [5]%s [6]None : "finish , matched[0]->name , matched[1]->name , matched[2]->name , matched[3]->name , matched[4]->name);
    scanf("%d" , &choice);
    if (choice == 6) {                  // doesn't like anyone
        printf(B_white"Do you want to keep pairing or exiting the app?\n"finish);
        printf(B_white"[1]Pairing [2]exit : "finish);
        scanf("%d" , &choice);
        if (choice == 1) {          // pairing
            printf(B_B_red"Please wait for a seconds\n"finish);
            sleep(3);
            printf("\n\n");
            printf(B_white"Welcome! It's a whole new day.\n"finish);
            // printf(B_white"Let's find your soulmate!\n"finish);
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
        exit(0);
    }
}
