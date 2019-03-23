#include "functions.h"

student_cls::student_cls(){
    cout << "Name: ";
    cin >> name;
    cout << "Surname: ";
    cin >> surname;
    cout << "Homework marks (enter a single character when done)...\n";
    while(true){
        cout << "HW_" << mark_counter+1 << ": ";
        cin >> mark_hw[mark_counter];
        if(cin.fail()){
        break;
        }
    mark_counter++;
    }
    cin.clear();
    cin.ignore();
    cout << "Exam mark: ";
    cin >> mark_exam;
}

float student_cls::calculate_hw(int option){
    float result = 0;
    // average
    if(option == 1){
        for(int i=0;i<mark_counter;i++){
        result += mark_hw[i];
        }
        result /= mark_counter;
    }
    // median
    else{
        int memory, index;

        for(int i=0;i<mark_counter;i++){
            memory = mark_hw[i];
            index = i;
            for(int j=i;j<mark_counter;j++){
                if(mark_hw[i] > mark_hw[j] && memory > mark_hw[j]){
                memory = mark_hw[j];
                index = j;
                }
            }
            mark_hw[index] = mark_hw[i];
            mark_hw[i] = memory;
        }
        // if the number of marks is an even number
        if((mark_counter)%2==0){
            result = float(mark_hw[(mark_counter)/2 - 1] + mark_hw[(mark_counter)/2]) / 2;
        }
        // if the number of marks is an odd number
        else{
            result = mark_hw[mark_counter/2];
        }
    }
    return result;
}

float student_cls::calculate_final(float value){
    return 0.4 * value + 0.6 * mark_exam;
}

float student_cls::random(){
    return (rand()%1000+1) * 0.01;
}

void student_cls::show_mark(float value){
    cout << setw(15) << surname << setw(28) << name << setprecision(3) << value << endl;
}

void menu_navigation(){

int cursor = 1, mode = 1, objectCounter = 0, key;
bool terminate = false;
vector<student_cls> student;

display_menu(1);
do{
    key = getch();
    if(key == 224){
        switch(getch()){
            case 72:
                if(cursor == 1){
                    cursor = 1;
                }
                else{
                    cursor--;
                }
                system("cls");
                display_menu(cursor);
                break;
            case 80:
                if(cursor == 3){
                    cursor = 3;
                }
                else{
                    cursor++;
                }
                system("cls");
                display_menu(cursor);
                break;
        }
    }
    else if(key == 13){
        system("cls");
        switch(cursor){
            case 1:
                objectCounter++;
                student.resize(objectCounter);
                system("cls");
                display_menu(cursor);
                break;
            case 2:
                while(true){
                    display_results(mode);
                    if(mode < 3){
                        for(int i=0;i<objectCounter;i++){
                            student[i].show_mark(student[i].calculate_final(student[i].calculate_hw(mode)));
                        }
                    }
                    else{
                        for(int i=0;i<objectCounter;i++){
                            student[i].show_mark(student[i].random());
                        }
                    }
                    cout << "\n\nPress 'm' to switch between modes. Press any other key to continue...\n";
                    if(getch() == 'm'){
                        if(mode<3){
                            mode += 1;
                        }
                        else{
                            mode = 1;
                        }
                    }
                    else{
                        break;
                    }
                    system("cls");
                }
                system("cls");
                display_menu(cursor);
                break;
            case 3:
                terminate = true;
                break;
        }
    }

}while(terminate == false);
}

void display_menu(int option){
    cout << "********  MENU  ********\n\n";
    switch(option){
        case 1:
            cout << "1. Enter data  <--  \n\n2. Show results\n\n3. Exit";
            break;
        case 2:
            cout << "1. Enter data   \n\n2. Show results  <--\n\n3. Exit";
            break;
        case 3:
            cout << "1. Enter data   \n\n2. Show results\n\n3. Exit  <--";
            break;
    }
}

void display_results(int option){
    if(option == 1){
        cout << left << setw(15) << "Surname" << setw(15) << "Name" << "Final points (Avg.)\n";
    }
    else if(option == 2){
        cout << left << setw(15) << "Surname" << setw(15) << "Name" << "Final points (Med.)\n";
    }
    else if(option == 3){
        cout << left << setw(15) << "Surname" << setw(15) << "Name" << "Final points (Rand.)\n";
    }
    cout.fill('-');
    cout << setw(49) << "" << endl;
    cout.fill(' ');
}

void display_intro(int option){
    if(option == 1){
        string a = "\t\t\t\t   ###################\n";
        string b = "\t\t\t\t #####################\n";
        string c = "\t\t\t\t####\n";
        string d = "\t\t\t\t####                            ###            ###\n";
        string e = "\t\t\t\t####                        ###########    ###########\n";
        string f = "\t\t\t\t   ###################      Hello and welcome to this C++ program!\n";
        cout << "\n\n\n\n\n\n\n";
        cout << a << b << c << c << d << d << e << e << d << d << c << c << b << f;
    }
    else{
        cout << "\n\n\n\n\n\n\n";
        cout << setw(85) << "***************** INSTRUCTIONS *****************\n";
        cout << setw(85) << "*                                              *\n";
        cout << setw(85) << "*     Please use arrow keys on your keyboard   *\n";
        cout << setw(85) << "*         to navigate through the menu.        *\n";
        cout << setw(85) << "*                                              *\n";
        cout << setw(85) << "*          Press spacebar to continue...       *\n";
        cout << setw(85) << "*                                              *\n";
        cout << setw(85) << "************************************************\n";

        while(true){
            gotoxy(47,12);
            cout << "                             ";
            Sleep(1000);
            gotoxy(47,12);
            cout << "Press spacebar to continue...";
            Sleep(1000);
            if(GetAsyncKeyState(VK_SPACE)){
                break;
            }
        }
    }
}

void gotoxy(int x, int y){
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ShowConsoleCursor(bool showFlag){
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
