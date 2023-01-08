#include "assignment_4.h"

int main()
{
    covidDB dataBase(17);

    bool end = true;
    int Case;

    string Country;
    string Date;

    int Cases;
    int Deaths;

    while (end != false)
    {
        cout << endl;
        cout << "Covid Tracker" << endl;
        cout << "Please choose the operation you want: " << endl;
        cout << "1. Create the initial hash table" << endl;
        cout << "2. Add a new data entry" << endl;
        cout << "3. Get a data entry" << endl;
        cout << "4. Remove a data entry" << endl;
        cout << "5. Display hash table" << endl;
        cout << "0. Quit the system" << endl;
        cout << "Your Choice: ";

        cin >> Case;
        switch (Case)
        {
        case 1:
            dataBase.readFile();
            break;
        case 2:
        {
            cout << "Enter a Country you would like to add (Capitalize first character): ";
            cin >> Country;

            cout << "Enter Date for entry (MM/DD/YYYY): ";
            cin >> Date;

            cout << "Enter number of Cases: ";
            cin >> Cases;

            cout << "Enter number of Deaths: ";
            cin >> Deaths;

            cvsdata entry(Date, Country, Cases, Deaths);
            cout << endl;

            if (dataBase.add(entry) == true)
            {
                cout << "New Entry added" << endl;
                cout << dataBase.get(Country).toString() << endl;
            }
            else
            {
                cout << "Entry was not added" << endl;
            }
            break;
        }
        case 3:
            cout << "Provide a country's data (put a '_' for spaces): ";
            cin >> Country;
            cout << endl;
            if (dataBase.get(Country).toString() == "0 0 0 0")
            {
                cout << "Entry does not exist";
            }
            else
            {
                cout << dataBase.get(Country).toString();
            }
            cout << endl;
            break;
        case 4:
            cout << "Provide a Country to remove: ";
            cin >> Country;
            cout << endl;
            dataBase.remove(Country);
            break;
        case 5:
            dataBase.display();
            break;
        case 0:
            end = false;
            break;
        default:
            cout << "Misinput, try again!: ";
            cin >> Case;
            cout << endl;
            break;
        }
    }
}
