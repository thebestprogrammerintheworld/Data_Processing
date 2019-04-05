#include "functions.h"

int main()
{
    srand(time(NULL));
    ShowConsoleCursor(false);
    display_intro(1);
    Sleep(100);
    system("cls");
    display_intro(2);
    system("cls");
    menu_navigation();

    return 0;
}
