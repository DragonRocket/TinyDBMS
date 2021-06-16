#include "ctinydbms"

struct Index
{
    char title[MAX_TITLE_LENGTH];
    unsigned int book_id;

    Index() : book_id(0)
    {
        strcpy(title, "\0");
    }

    Index(const char title[MAX_TITLE_LENGTH], unsigned int book_id) : book_id(book_id)
    {
        strcpy(this->title, title);
    }

    Index(const Index &obj) : book_id(obj.book_id)
    {
        strcpy(title, obj.title);
    }

    bool operator==(const Index &obj) { return strcmp(title, obj.title) == 0; }

    bool operator!=(const Index &obj) { return strcmp(title, obj.title) != 0; }

    bool operator<(const Index &obj) { return strcmp(title, obj.title) < 0; }
    bool operator<=(const Index &obj) { return strcmp(title, obj.title) < 0 || strcmp(title, obj.title) == 0; }

    bool operator>(const Index &obj) { return strcmp(title, obj.title) > 0; }
    bool operator>=(const Index &obj) { return strcmp(title, obj.title) > 0 || strcmp(title, obj.title) == 0; }

    Index &operator=(const Index &obj)
    {
        if (this != &obj)
        {
            strcpy(title, obj.title);
            book_id = obj.book_id;
        }

        return *this;
    }
};

Book *createMap()
{
    FD fd = open(FILENAME, O_RDWR | O_CREAT, (mode_t)0600);
    if (fd == -1)
    {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    // Stretch the file size to the size of the (mmapped) array of structs
    int offset = lseek(fd, FILESIZE - 1, SEEK_SET);
    if (offset == -1)
    {
        close(fd);
        perror("Error calling lseek() to 'stretch' the file");
        exit(EXIT_FAILURE);
    }

    offset = write(fd, "", 1);
    if (offset != 1)
    {
        close(fd);
        perror("Error writing last byte of the file");
        exit(EXIT_FAILURE);
    }

    Book *map = (Book *)mmap(0, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd); // close the file

    if (map == MAP_FAILED)
    {
        close(fd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }

    return map;
}

Index *createIndex(Book *map)
{
    vector<Index> index;

    Index tmp;
    for (int i = 0; i < DATA_LENGTH; i++)
    {
        Book *book = &map[i];
        if (book->getBookID() - 1 >= 0 && book->getBookID() - 1 == i)
        {
            tmp.book_id = i + 1;
            strcpy(tmp.title, book->getBookTitle());
            index.push_back(tmp);
        }
    }

    int filesize = index.size() * sizeof(Index);

    if (filesize > 0)
    {
        sort(index.begin(), index.end());

        FD fd = open(INDEX_FILENAME, O_RDWR | O_CREAT, (mode_t)0600);
        if (fd == -1)
        {
            perror("Error opening file for writing");
            exit(EXIT_FAILURE);
        }

        // Stretch the file size to the size of the (mmapped) array of structs
        int offset = lseek(fd, filesize - 1, SEEK_SET);
        if (offset == -1)
        {
            close(fd);
            perror("Error calling lseek() to 'stretch' the file");
            exit(EXIT_FAILURE);
        }

        offset = write(fd, "", 1);
        if (offset != 1)
        {
            close(fd);
            perror("Error writing last byte of the file");
            exit(EXIT_FAILURE);
        }

        Index *imap = (Index *)mmap(0, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        close(fd); // close the file

        if (imap == MAP_FAILED)
        {
            close(fd);
            perror("Error mmapping the file");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < index.size(); i++)
            imap[i] = index[i];

        return imap;
    }
    return NULL;
}

void updateIndex(Book *map, Index *&imap)
{
    vector<Index> index;

    Index tmp;
    for (int i = 0; i < DATA_LENGTH; i++)
    {
        Book *book = &map[i];
        if (book->getBookID() - 1 >= 0 && book->getBookID() - 1 == i)
        {
            tmp.book_id = i + 1;
            strcpy(tmp.title, book->getBookTitle());
            index.push_back(tmp);
        }
    }

    int filesize = index.size() * sizeof(Index);
    if (filesize > 0)
    {
        sort(index.begin(), index.end());

        FD fd = open(INDEX_FILENAME, O_RDWR | O_CREAT, (mode_t)0600);
        if (fd == -1)
        {
            perror("Error opening file for writing");
            exit(EXIT_FAILURE);
        }

        // Stretch the file size to the size of the (mmapped) array of structs
        int offset = lseek(fd, filesize - 1, SEEK_SET);
        if (offset == -1)
        {
            close(fd);
            perror("Error calling lseek() to 'stretch' the file");
            exit(EXIT_FAILURE);
        }

        offset = write(fd, "", 1);
        if (offset != 1)
        {
            close(fd);
            perror("Error writing last byte of the file");
            exit(EXIT_FAILURE);
        }

        struct stat stat_buf;
        int rc = stat(INDEX_FILENAME, &stat_buf);
        if (imap != NULL && rc == -1)
        {
            perror("Indexing Failed");
            exit(EXIT_FAILURE);
        }

        if (imap != NULL && munmap(imap, stat_buf.st_size) == -1) // free the mmapped memory
            perror("Error un-mmapping the file");

        imap = (Index *)mmap(0, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        close(fd); // close the file

        if (imap == MAP_FAILED)
        {
            close(fd);
            perror("Error mmapping the file");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < index.size(); i++)
            imap[i] = index[i];
    }
}

void clear()
{
    system("clear");
}

void intro()
{
    clear();

    cout << "Welcome to A Tiny DBMS" << endl;
    cout << endl;
}

void menu()
{
    cout << "1 . Search a Record" << endl;
    cout << "2 . Add/Update a Record" << endl;
    cout << "3 . Delete a Record" << endl;
    cout << "99. Exit" << endl;
    cout << endl;
}

void submenu()
{
    cout << "1 . Search by Book ID" << endl;
    cout << "2 . Search by Book Title" << endl;
    cout << "99. Back" << endl;
    cout << endl;
}

int readOption()
{
    int o;

    cout << "Select an Option: ";
    cin >> o;

    cout << endl;

    return o;
}

void readBookInfo(Book &book)
{
    unsigned int book_id;
    readID(book_id);

    char title[MAX_TITLE_LENGTH];
    readTitle(title);

    char authors[MAX_AUTHORS][MAX_NAME_LENGTH];
    unsigned int authorsCount = readAuthors(authors);

    Date dop;
    readDOP(dop);

    char publisher[MAX_NAME_LENGTH];
    readPublisher(publisher);

    book.setBookID(book_id);
    book.setBookTitle(title);
    book.setBookAuthors(authors, authorsCount);
    book.setBookDOP(dop);
    book.setBookPublisher(publisher);
}

void addRecord(const Book &book, Book *map, Index *&index)
{
    if (book.getBookID() - 1 >= 0)
    {
        if (map[book.getBookID() - 1].getBookID() == book.getBookID())
        {
            cout << "\nWarning! Data Already Exists" << endl;
            cout << "Do you want to Update(Y/n): ";
            char c = getchar();
            if (c == 'Y' || c == 'y')
            {
                map[book.getBookID() - 1] = book;
                cout << "\nRecord Updated in File Successully" << endl;
                updateIndex(map, index);
            }
            else
                cout << "Nothing Changed" << endl;

            cin.ignore();
        }
        else
        {
            map[book.getBookID() - 1] = book;
            cout << "\nRecord Added in File Successully" << endl;
            updateIndex(map, index);
        }
    }
    else
        cout << "\nData Not Added/Updated (Invalid Data)" << endl;

    cout << "\nPress Any Key to Continue...";
    getchar();
    cout << endl;
}

void deleteRecord(unsigned int book_id, Book *map, Index *&index)
{
    Book *book = &map[book_id - 1];
    if (book->getBookID() - 1 >= 0 && book->getBookID() == book_id)
    {
        book->printBookRecord();
        cout << "\nAre you sure to Delete this Record(Y/n): ";
        char c = getchar();
        if (c == 'y' || c == 'Y')
        {
            book->setBookID(!book_id);
            cout << "Record Deleted" << endl;
        }
        else
            cout << "Deletion Terminated" << endl;
    }
    else
        cout << "\nRecord Not Found" << endl;

    updateIndex(map, index);

    cout << "\nPress Any Key to Continue...";
    cin.ignore();
    getchar();
    cout << endl;
}

int binaryTitleIndexSearch(Index *imap, int p, int r, const char title[MAX_TITLE_LENGTH])
{
    if (p <= r)
    {
        int mid = (p + r) / 2;
        if (strcmp(imap[mid].title, title) == 0)
            return mid;
        if (strcmp(imap[mid].title, title) > 0)
            return binaryTitleIndexSearch(imap, p, mid - 1, title);
        if (strcmp(imap[mid].title, title) < 0)
            return binaryTitleIndexSearch(imap, mid + 1, r, title);
    }
    return -1;
}

void searchByID(unsigned int book_id, Book *map)
{
    if (book_id > 0)
    {
        Book *book = &map[book_id - 1];
        if (book->getBookID() - 1 >= 0 && book->getBookID() == book_id)
            book->printBookRecord();
        else
            cout << "\nRecord Not Found" << endl;
    }
    else
        cout << "\nRecord Not Found" << endl;

    cout << "\nPress Any Key to Continue...";
    getchar();
}

void searchByTitle(char title[MAX_TITLE_LENGTH], Index *index, Book *map)
{
    struct stat stat_buf;
    int rc = stat(INDEX_FILENAME, &stat_buf);
    if (index != NULL && rc == -1)
    {
        perror("Indexing Failed");
        exit(-1);
    }

    int ind = binaryTitleIndexSearch(index, 0, stat_buf.st_size / sizeof(Index) - 1, title);
    if (ind == -1)
    {
        cout << "\nRecord Not Found" << endl;

        cout << "\nPress Any Key to Continue...";
        getchar();
    }
    else
        searchByID(index[ind].book_id, map);
}

void readID(unsigned int &book_id)
{
    do
    {
        cout << "Enter Book ID: ";
        cin >> book_id;
        if (book_id <= 0)
        {
            cout << "Postive Integers Allowed Only" << endl;
            cout << endl;
        }
    } while (book_id <= 0);
}

void readTitle(char title[MAX_TITLE_LENGTH])
{
    cout << "Enter Book Title: ";
    cin.ignore();
    cin.getline(title, MAX_TITLE_LENGTH, '\n');
}

void readAuthorsCount(unsigned int &authorsCount)
{
    do
    {
        cout << "Enter Book Authors Count: ";
        cin >> authorsCount;
        if (authorsCount == 0 || authorsCount > 5)
        {
            cout << "Minimum Authors: 1 and Maximum Authors: 5" << endl;
            cout << endl;
        }
    } while (authorsCount == 0 || authorsCount > 5);
}

unsigned int readAuthors(char authors[MAX_AUTHORS][MAX_NAME_LENGTH])
{
    unsigned int authorsCount;
    readAuthorsCount(authorsCount);
    cin.ignore();
    for (int i = 0; i < authorsCount; i++)
    {
        cout << "Enter Book Author #" + to_string(i + 1) + ": ";
        cin.getline(authors[i], MAX_NAME_LENGTH, '\n');
    }

    return authorsCount;
}

void readDOP(Date &date)
{
    unsigned int year;
    cout << "Enter Book Year of Publication: ";
    cin >> year;

    unsigned int month;
    cout << "Enter Book Month of Publication: ";
    cin >> month;

    unsigned int day;
    cout << "Enter Book Day of Publication: ";
    cin >> day;

    date.setDate(day, month, year);
}

void readPublisher(char publisher[MAX_NAME_LENGTH])
{
    cout << "Enter Book Publisher: ";
    cin.ignore();
    cin.getline(publisher, MAX_NAME_LENGTH, '\n');
}

void invalidSelection()
{
    cout << "Invalid Option Selected" << endl;
    cout << "\nPress Any Key to Continue...";
    cin.ignore();
    getchar();
}

void unMapBookFile(Book *map)
{
    if (munmap(map, FILESIZE) == -1) // free the mmapped memory
        perror("Error un-mmapping the file");
}

void exitingMessage()
{
    cout << "Exiting..." << endl;
    cout << "Program Exited Successfully" << endl;
}