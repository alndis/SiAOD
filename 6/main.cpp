#include "Hash_Table.hpp"
#include <limits>
Hash_Table library(5);

void add_initial_records()
{
    library.insert(new Data_Record(11234, "GreenTech Solutions", "Ivan Petrov"));
    library.insert(new Data_Record(12972, "FreshBake Bakery", "Olga Sidorova"));
    library.insert(new Data_Record(12345, "SmartHome Systems", "Sergey Kuznetsov"));
    library.insert(new Data_Record(12356, "EcoClean Services", "Natalia Romanova"));
    library.insert(new Data_Record(34567, "DigitalMedia Agency", "Andrey Ivanov"));
}

void clear_cin()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
}

int get_id_from_user()
{
    int license;
    while (true)
    {
        cout << "Enter license: ";
        if (cin >> license && license >= 10000 && license <= 99999)
        {
            clear_cin();
            return license;
        }
        clear_cin();
        cout << "Invalid license\n";
    }
}

string get_string_from_user(string prompt)
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

void insert()
{
    int license = get_id_from_user();
    string name = get_string_from_user("Enter name: ");
    string owner = get_string_from_user("Enter owner: ");
    Data_Record* new_record = new Data_Record(license, name, owner);
    library.insert(new_record);
    cout << "Successfully inserted record: " << new_record->string_rep() << endl;
};

void del()
{
    int license = get_id_from_user();
    int return_code = library.remove(license);
    if (return_code == 0)
    {
        cout << "Record with license = " << license << " was successfully deleted" << endl;
    }
    else
    {
        cout << "Record with license = " << license << " wasn't found" << endl;
    }
};

void search()
{
    int license = get_id_from_user();
    Data_Record* record = library.search(license);
    if (record == nullptr)
    {
        cout << "Record with license = " << license << " not found" << endl;
        return;
    }
    cout << "Found record: " << record->string_rep() << endl;

};

void display()
{
    cout << "Displaying all records: " << endl;
    library.display();
}

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    add_initial_records();

    int cmd;
    while (true)
    {
        while (true)
        {
            cout << "\n\t-- Enter Your Command Code --" << endl;
            cout << "1: Insert" << endl;
            cout << "2: Delete" << endl;
            cout << "3: Search" << endl;
            cout << "4: Display" << endl;
            cout << "0: Exit" << endl;
            cout << "\tCommand Code: ";
            if (cin >> cmd && cmd >= 0 && cmd <= 4) break;
            clear_cin();
            cout << "Invalid Command Code\n";
        }

        switch (cmd)
        {
        case 0:
            cout << "Exiting...";
            return 0;
        case 1:
            insert();
            break;
        case 2:
            del();
            break;
        case 3:
            search();
            break;
        case 4:
            display();
            break;
        }
    }
}