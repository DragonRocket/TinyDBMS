#include "ctinydbms"

int main()
{
    Book *map = createMap();
    Index *index = createIndex(map);

    bool exit = false;

    while (!exit)
    {
        intro();
        menu();

        int o = readOption();

        if (o == 1)
        {
            bool back = false;

            while (!back)
            {
                intro();
                cout << "Search" << endl;
                cout << endl;
                submenu();
                o = readOption();

                switch (o)
                {
                case 1:
                    intro();
                    cout << "Search by Book ID" << endl;
                    cout << endl;
                    unsigned int book_id;
                    readID(book_id);
                    cin.ignore();
                    searchByID(book_id, map);
                    break;
                case 2:
                    intro();
                    cout << "Search by Book Title" << endl;
                    cout << endl;
                    char title[MAX_TITLE_LENGTH];
                    readTitle(title);
                    searchByTitle(title, index, map);
                    break;
                case 99:
                    back = true;
                    break;
                default:
                    invalidSelection();
                }
            }
        }
        else if (o == 2)
        {
            intro();
            cout << "Add Record" << endl;
            cout << endl;
            Book book;
            readBookInfo(book);
            addRecord(book, map, index);
        }
        else if (o == 3)
        {
            intro();
            cout << "Delete Record" << endl;
            cout << endl;
            unsigned int book_id;
            readID(book_id);
            cin.ignore();
            deleteRecord(book_id, map, index);
        }
        else if (o == 99)
            exit = true;
        else
            invalidSelection();
    }

    unMapBookFile(map);
    exitingMessage();
    return 0;
}