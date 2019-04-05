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

void student_cls::init(){
    cout << "Surname: ";
    cin >> surname;
    cout << "Name: ";
    cin >> name;
    cout << "Homework marks (enter a single character when done)...\n";
    while(true){
        try{
            cout << "HW_" << mark_counter+1 << ": ";
            cin >> mark_hw[mark_counter];
            if(mark_hw[mark_counter] < 0 || mark_hw[mark_counter] > 10){
                throw range_error("error: number is out of range!");
            }
        }
            catch(const range_error& e){
                cout << e.what() << endl;
                mark_counter--;
            }
        if(cin.fail()){
            break;
        }
        mark_counter++;
    }
    cin.clear();
    cin.ignore();
    while(true){
        try{
            cout << "Exam mark: ";
            cin >> mark_exam;
            if(mark_exam < 0 || mark_exam > 10){
                throw range_error("error: number is out of range!");
            }
            else{
                break;
            }
        }
        catch(const range_error& e){
            cout << e.what() << endl;
        }
    }
}

void menu_navigation(){

int cursor = 1, mode = 1, objectCounter = 0, index, key, studCounter, numOfHwOut;
char n;
bool terminate = false, sorted = false, filesCreated = false;
string filename;
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
                break;
            case 80:
                if(cursor == 6){
                    cursor = 6;
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
                student[index].init();
                sorted = false;
                break;
            case 2:
                cout << "Enter full file name from which to enter data: ";
                cin >> filename;
                loadFromFile(student, objectCounter, filename);
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
                        (mode<3)?mode+=1:mode=1;
                    }
                    else{
                        break;
                    }
                    system("cls");
                }
                break;
            case 4:
                cout << "Enter how many homeworks do you want students to have: ";
                cin >> numOfHwOut;
                cout << "\nYour files are being created, this may take a while...\n\n";
                for(int i=100;i<=1000000;i*=10){
                    high_resolution_clock::time_point t1 = high_resolution_clock::now();
                    createFiles(i,numOfHwOut);
                    high_resolution_clock::time_point t2 = high_resolution_clock::now();
                    auto duration = duration_cast<milliseconds>( t2 - t1 ).count();
                    cout << "It took " << duration*0.001 << " seconds to generate a " << i << " students.\n";
                }
                system("pause");
                filesCreated = true;
                break;
            case 5:
                if(filesCreated == true){
                    for(int i=100;i<=1000000;i*=10){
                        loadFromFile(student, objectCounter, to_string(i)+".txt");
                        sortFiles(student, i, numOfHwOut);
                    }
                }
                else{
                    cout << "You need to create the files first.\n\n";
                    system("pause");
                }
                system("pause");
                break;
            case 6:
                terminate = true;
                break;
        }
        Sleep(100);
        system("cls");
        display_menu(cursor);
    }

}while(terminate == false);
}

void display_menu(int option){
    cout << "********  MENU  ********\n\n";
    switch(option){
        case 1:
            cout << "1. Enter data  <--\n\n2. Load data \n\n3. Show results \n\n4. Create files (v0.4) \n\n5. Sort files (v0.4) \n\n6. Exit";
            break;
        case 2:
            cout << "1. Enter data \n\n2. Load data <--\n\n3. Show results \n\n4. Create files (v0.4) \n\n5. Sort files (v0.4) \n\n6. Exit";
            break;
        case 3:
            cout << "1. Enter data \n\n2. Load data \n\n3. Show results <--\n\n4. Create files (v0.4) \n\n5. Sort files (v0.4) \n\n6. Exit";
            break;
        case 4:
            cout << "1. Enter data \n\n2. Load data \n\n3. Show results \n\n4. Create files (v0.4) <--\n\n5. Sort files (v0.4) \n\n6. Exit";
            break;
        case 5:
            cout << "1. Enter data \n\n2. Load data \n\n3. Show results \n\n4. Create files (v0.4) \n\n5. Sort files (v0.4) <--\n\n6. Exit";
            break;
        case 6:
            cout << "1. Enter data \n\n2. Load data \n\n3. Show results \n\n4. Create files (v0.4) \n\n5. Sort files (v0.4) \n\n6. Exit <--";
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

void loadFromFile(vector<student_cls>& student, int& counter, string filename){
    ifstream infile;
    char data[100];
    int index, i;
    counter = 0;
    student.resize(counter);

    try {
        infile.open(filename);
        if(!infile){
            throw "The file does not exist";
        }
    }
    catch(const char* e){
        cout << e << endl;
        Sleep(1000);
        return;
    }

    while(data[0] != 'E'){
        infile >> data;
    }
        infile >> data;
        while(infile.peek() != EOF){
            counter++;
            index = counter - 1;
            student.resize(counter);
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
        infile.close();
}

void createFiles(int students, int hw_num){
    string fname = "" + to_string(students) + ".txt";
    srand(time(NULL));
    ofstream outfile;
    outfile.open(fname);
    outfile << left << setw(29) << "Surname" << setw(18) << "Name";
    for(int i=1;i<=hw_num;i++){
        outfile << setw(2) << "HW" << setw(5)  << i;
    }
    outfile << setw(7) << "Exam" << endl;

    for(int i=1;i<=students;i++){
        outfile << setw(7) << "Surname" << setw(22) << i << setw(4) << "Name" << setw(14) << i;
        for(int j=1;j<=hw_num;j++){
            outfile << setw(2) << rand()%11 << setw(5) << "";
        }
        outfile << setw(7) << rand()%11 << endl;
    }

    outfile.close();
}

void sortFiles(vector<student_cls>& student, int students, int hw_num){
    string fname;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for(int i=0;i<students;i++){
        (student[i].calculate_final(student[i].calculate_hw(1)) >= 5)?student[i].pass = true:student[i].pass = false;
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>( t2 - t1 ).count();
    cout << "It took " << duration*0.001 << " seconds to sort " << students << " students.\n";

    t1 = high_resolution_clock::now();
    for(int k=0;k<2;k++){
        (k==0)?fname = "" + to_string(students) + " passed" + ".txt":fname = "" + to_string(students) + " failed" + ".txt";
        ofstream outfile;
        outfile.open(fname);
        outfile << left << setw(29) << "Surname" << setw(18) << "Name";
        for(int i=1;i<=hw_num;i++){
            outfile << setw(2) << "HW" << setw(5)  << i;
        }
        outfile << setw(7) << "Exam" << endl;

        for(int i=0;i<students;i++){
            if(student[i].pass == true && k == 0){
                outfile << setw(29) << student[i].surname << setw(18) << student[i].name;
                for(int j=0;j<hw_num;j++){
                    outfile << setw(2) << student[i].mark_hw[j] << setw(5) << "";
                }
                outfile << setw(7) << student[i].mark_exam << endl;
            }
            else if(student[i].pass == false && k == 1){
                outfile << setw(29) << student[i].surname << setw(18) << student[i].name;
                for(int j=0;j<hw_num;j++){
                    outfile << setw(2) << student[i].mark_hw[j] << setw(5) << "";
                }
                outfile << setw(7) << student[i].mark_exam << endl;
            }
        }
        outfile.close();
    }
    t2 = high_resolution_clock::now();
    duration = duration_cast<milliseconds>( t2 - t1 ).count();
    cout << "It took " << duration*0.001 << " seconds to split " << students << " students into files.\n\n";
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
