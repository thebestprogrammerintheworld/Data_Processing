#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <vector>
#include <fstream>
#include <string.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

class student_cls{
    public:
        string name, surname;
        int mark_hw[50], mark_exam, mark_counter = 0, ID;
        bool pass;
        float calculate_hw(int option);
        float calculate_final(float value);
        float random();
        void show_mark(float value);
        void init();
};
void menu_navigation();
void display_menu(int option);
void display_results(int option);
void display_intro(int option);
void loadFromFile(vector<student_cls>& student, int& counter, string filename);
void createFiles(int students, int hw_num);
void sortFiles(vector<student_cls>& student, int students, int hw_num);
void gotoxy(int x, int y);
void ShowConsoleCursor(bool showFlag);

#endif // FUNCTIONS_H_INCLUDED
