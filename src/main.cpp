#include <iostream>
#include <conio.h>
#include "Task3.cpp"

using namespace std;

int main()
{
    cout << "\t hello this is task 3 \n";
    cout << "\t choose 1 option: \n";
    cout << "\t 1- Original given question \n";
    cout << "\t 2- Change question \n";
    cout << "\t 3- exit \n";


    char choice;
    while (true) {
        choice = _getch();

        switch (choice) {
            case '1':
                cout << "Original given question \n";

                break;
            case '2':
                cout << "Change question \n";

                break;
            case '3':
                cout << "Exiting program \n";
                return 0;
            default:
                break;
        }
    }
}
