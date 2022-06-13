#include "basic.h"
#include "UserAction.h"

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

void choose(int i, int like_people, char like[20][100]){
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

void delete_like(){
    Like *temp=head, *del ;
    while(temp->next!=NULL){
        del = temp;
        temp = temp->next;
        free(del);
    }
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
        const char *filename = "../final_decision.txt";
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

void relike(int g, int like_people, char like[20][100]){
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

bool check_boundary2(int x){
    if(x<0 || x>20){
        return false;
    }
    return true;
}
