#include "basic.h"
#include "setting.h"
#include "AdminAction.h"
#include "UserAction.h"

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
            qsort(person, data_amount-1, sizeof(Data), comp);
            int a = 0;
            while(1){
                if(a==1){
                    initial_score_and_flag(data_amount, &times1, &times2, &times3);
                    preference(&times1, &times2, &times3, &left, &right, &l_age, &r_age);
                    calculate_score(&times1, &times2, &times3, &left, &right, &l_age, &r_age, &person[data_amount - 1], data_amount-1);
                    qsort(person, data_amount-1, sizeof(Data), comp);
                }
                a = display(data_amount);
            }
        }
        else if (mode == 1){    //* Admin operation
            administrator(&data_amount);
        }
        else if(mode == 2){     //* User login and match
            preference(&times1, &times2, &times3, &left, &right, &l_age, &r_age);
            calculate_score(&times1, &times2, &times3, &left, &right, &l_age, &r_age, &person[data_amount - 1], data_amount-1);
            qsort(person, data_amount-1, sizeof(Data), comp);
            int a = 0;
            while(1){
                if(a==1){
                    initial_score_and_flag(data_amount, &times1, &times2, &times3);
                    preference(&times1, &times2, &times3, &left, &right, &l_age, &r_age);
                    calculate_score(&times1, &times2, &times3, &left, &right, &l_age, &r_age, &person[data_amount - 1], data_amount-1);
                    qsort(person, data_amount-1, sizeof(Data), comp);
                }
                a = display(data_amount);
            }
        }
    }
}