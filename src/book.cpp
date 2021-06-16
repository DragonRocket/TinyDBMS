#include "cbook"

Book::Book() : book_id(0), authorsCount(0), date_of_publication(1, 1, 1)
{
    strcpy(title, "\0");

    for (int i = 0; i < authorsCount; i++)
        strcpy(authors[i], "\0");

    strcpy(publisher, "\0");
}

Book::Book(unsigned int book_id, const char title[MAX_TITLE_LENGTH], unsigned int authorsCount, const char authors[MAX_AUTHORS][MAX_NAME_LENGTH], Date date_of_publication, const char publisher[MAX_NAME_LENGTH]) : book_id(book_id), authorsCount(authorsCount), date_of_publication(date_of_publication)
{
    strcpy(this->title, title);

    for (int i = 0; i < authorsCount; i++)
        strcpy(this->authors[i], authors[i]);

    strcpy(this->publisher, publisher);
}

Book::Book(const Book &obj) : book_id(obj.book_id), authorsCount(obj.authorsCount), date_of_publication(obj.date_of_publication)
{
    strcpy(title, obj.title);

    for (int i = 0; i < authorsCount; i++)
        strcpy(authors[i], obj.authors[i]);

    strcpy(publisher, obj.publisher);
}

unsigned int Book::getBookID() const
{
    return book_id;
}

const char *Book::getBookTitle() const
{
    return title;
}

void Book::setBookID(unsigned int book_id)
{
    this->book_id = book_id;
}

void Book::setBookTitle(const char title[MAX_TITLE_LENGTH])
{
    strcpy(this->title, title);
}

void Book::setBookAuthors(const char authors[MAX_AUTHORS][MAX_NAME_LENGTH], unsigned int authorsCount)
{
    this->authorsCount = authorsCount;

    for (int i = 0; i < authorsCount; i++)
        strcpy(this->authors[i], authors[i]);
}

void Book::setBookDOP(Date date_of_publication)
{
    this->date_of_publication = date_of_publication;
}

void Book::setBookPublisher(const char publisher[MAX_NAME_LENGTH])
{
    strcpy(this->publisher, publisher);
}

void Book::printBookRecord()
{
    cout << endl;
    cout << "Book ID: " << book_id << endl;
    cout << "Book Title: " << title << endl;
    cout << "Author Name(s): ";
    for (int i = 0; i < authorsCount; i++)
    {
        cout << authors[i];
        if (i < authorsCount - 1)
            cout << ", ";
    }
    cout << endl;
    cout << "Published Date: ";
    date_of_publication.showDate();
    cout << endl;
    cout << "Publisher: " << publisher << endl;
}

Book &Book::operator=(const Book &obj)
{
    if (this != &obj)
    {
        book_id = obj.book_id;
        authorsCount = obj.authorsCount;

        strcpy(title, obj.title);

        for (int i = 0; i < authorsCount; i++)
            strcpy(authors[i], obj.authors[i]);

        date_of_publication = obj.date_of_publication;
        strcpy(publisher, obj.publisher);
    }

    return *this;
}