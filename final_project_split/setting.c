#include "basic.h"
#include "setting.h"

int read_file(){
    int i = 0;
    const char *filename = "../output.txt";
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
    FILE *output_file = fopen("../output.txt", "a");
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
    FILE *output_file = fopen("../output.txt", "a");
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

void calculate_score(int *times1,int *times2,int *times3,float *left,float *right, int *l_age,int *r_age,Data *User,int data_amount){
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

void sexuality_score(Data *User,int data_amount){
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

void age_score(int *times3,int *l_age,int *r_age,Data *User,int data_amount){
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

void area_score(Data *User,int data_amount){
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

void hobby_score(Data *User,int data_amount){
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

int comp(const void *p, const void *q){
    return (((Data *)q)->score - ((Data *)p)->score);
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

int search_admin(char *s, char *s1){
    for (int i = 0; i < 5; i++){
        if (!strcmp(m[i].id, s) && !strcmp(m[i].pw,s1)){
            return 1;
        }
    }
    return 0;
}

int search(char *pnum, int *data_amount){
    for (int i = 0; i < *data_amount; i++){
        if (!strcmp(pnum,person[i].phone_number)){
            return i;
        }
    }
    return -1;
}
