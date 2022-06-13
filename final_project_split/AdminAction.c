#include "basic.h"
#include "AdminAction.h"
#include "setting.h"

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

void write_file(int *data_amount){
    const char *filename = "../output.txt";
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
