#include "functions.h"

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

int cursor = 1, mode = 1, objectCounter = 0, index, i, key, studCounter;
char data[100], n;
bool terminate = false, sorted = false;
string filename;
vector<student_cls> student;
ifstream infile;


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
                break;
            case 80:
                if(cursor == 4){
                    cursor = 4;
                }
                else{
                    cursor++;
                }
                break;
        }
        system("cls");
        display_menu(cursor);
    }
    else if(key == 13){
        system("cls");
        switch(cursor){
            case 1:
                objectCounter++;
                index = objectCounter - 1;
                student.resize(objectCounter);
                cout << "Surname: ";
                cin >> student[index].surname;
                cout << "Name: ";
                cin >> student[index].name;
                cout << "Homework marks (enter a single character when done)...\n";
                while(true){
                    cout << "HW_" << student[index].mark_counter+1 << ": ";
                    cin >> student[index].mark_hw[student[index].mark_counter];
                    if(cin.fail()){
                        break;
                    }
                    student[index].mark_counter++;
                }
                cin.clear();
                cin.ignore();
                cout << "Exam mark: ";
                cin >> student[index].mark_exam;
                sorted = false;
                break;
            case 2:
                cout << "Enter full file name from which to enter data: ";
                cin >> filename;
                infile.open(filename);
                infile.seekg(40);    // BUG
                infile >> data;
                while(infile.peek() != EOF){
                    objectCounter++;
                    index = objectCounter - 1;
                    student.resize(objectCounter);
                    student[index].surname = data;
                    infile >> student[index].name;

                    infile >> data;
                    i = 0;
                    while(data[0] > 47 && data[0] < 58){
                        if(data[1] == 48){
                            student[index].mark_hw[i] = 10;
                        }
                        else{
                            student[index].mark_hw[i] = data[0] - 48;
                        }
                        student[index].mark_counter++;
                        i++;
                        if(infile.peek() == EOF){
                            break;
                        }
                        infile >> data;
                        }
                        student[index].mark_exam = student[index].mark_hw[student[index].mark_counter-1];
                        student[index].mark_counter--;
                }
                sorted = false;
                break;
            case 3:
                if(sorted == false){
                    n = 'A';
                    studCounter = 0;
                    while(n < 123){
                        for(int i=0;i<objectCounter;i++){
                            if(student[i].surname[0] == n){
                                student[i].ID = studCounter;
                                studCounter++;
                            }
                        }
                        n++;
                    }
                    sorted = true;
                }
                while(true){
                    display_results(mode);
                    if(mode < 3){
                        for(int i=0;i<objectCounter;i++){
                            for(int j=0;j<objectCounter;j++){
                                if(student[j].ID == i){
                                    student[j].show_mark(student[j].calculate_final(student[j].calculate_hw(mode)));
                                    break;
                                }
                            }
                        }
                    }
                    else{
                        for(int i=0;i<objectCounter;i++){
                            for(int j=0;j<objectCounter;j++){
                                if(student[j].ID == i){
                                    student[j].show_mark(student[j].random());
                                    break;
                                }
                            }
                        }
                    }
                    cout << "\n\nPress 'm' to switch between modes. Press any other key to continue...\n";
                    key = getch();
                    if(key == 'm'){
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
                break;
            case 4:
                terminate = true;
                break;
        }
        system("cls");
        display_menu(cursor);
    }

}while(terminate == false);
}

void display_menu(int option){
    cout << "********  MENU  ********\n\n";
    switch(option){
        case 1:
            cout << "1. Enter data  <--\n\n2. Load data \n\n3. Show results\n\n4. Exit";
            break;
        case 2:
            cout << "1. Enter data   \n\n2. Load data  <--\n\n3. Show results\n\n4. Exit";
            break;
        case 3:
            cout << "1. Enter data   \n\n2. Load data \n\n3. Show results  <--\n\n4. Exit";
            break;
        case 4:
            cout << "1. Enter data   \n\n2. Load data \n\n3. Show results\n\n4. Exit  <--";
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
            Sleep(700);
            gotoxy(47,12);
            cout << "Press spacebar to continue...";
            Sleep(700);
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
