#ifndef AdminAction_H
#define AdminAction_H

void administrator(int *data_amount);

void sort(int *data_amount);

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

#endif