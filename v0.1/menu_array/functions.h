#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <time.h>
using namespace std;

struct Student{
    string name, surname;
    int mark_hw[50], mark_exam, mark_counter = 0;
    Student *next;
    float calculate(int option);
    float calculate_final(float value);
    float random();
    void show_result(float value);
};
void display_menu(int option);
void Menu();
void ShowConsoleCursor(bool showFlag);
void display_results(int option);
void gotoxy(int x, int y);
void display_intro(int option);

#endif // FUNCTIONS_H_INCLUDED
