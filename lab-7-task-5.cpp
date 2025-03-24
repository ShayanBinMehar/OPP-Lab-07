#include <iostream>
#include <string>

using namespace std;

class Media {
protected:
    string title;
    string publicationDate;
    string uniqueID;
    string publisher;

public:
    Media(const string& title, const string& publicationDate, const string& uniqueID, const string& publisher)
        : title(title), publicationDate(publicationDate), uniqueID(uniqueID), publisher(publisher) {}

    virtual ~Media() {}

    virtual void displayInfo() const {
        cout << "Title: " << title << endl;
        cout << "Publication Date: " << publicationDate << endl;
        cout << "Unique ID: " << uniqueID << endl;
        cout << "Publisher: " << publisher << endl;
    }

    void checkOut() const {
        cout << "Checked out: " << title << endl;
    }

    void returnItem() const {
        cout << "Returned: " << title << endl;
    }

    string getTitle() const { return title; }
    string getPublicationDate() const { return publicationDate; }
};

class Book : public Media {
private:
    string author;
    string isbn;
    int numberOfPages;

public:
    Book(const string& title, const string& publicationDate, const string& uniqueID, const string& publisher,
         const string& author, const string& isbn, int numberOfPages)
        : Media(title, publicationDate, uniqueID, publisher), author(author), isbn(isbn), numberOfPages(numberOfPages) {}

    void displayInfo() const override {
        Media::displayInfo();
        cout << "Author: " << author << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Number of Pages: " << numberOfPages << endl;
    }

    string getAuthor() const { return author; }
};

class DVD : public Media {
private:
    string director;
    int duration;
    string rating;

public:
    DVD(const string& title, const string& publicationDate, const string& uniqueID, const string& publisher,
        const string& director, int duration, const string& rating)
        : Media(title, publicationDate, uniqueID, publisher), director(director), duration(duration), rating(rating) {}

    void displayInfo() const override {
        Media::displayInfo();
        cout << "Director: " << director << endl;
        cout << "Duration: " << duration << " minutes" << endl;
        cout << "Rating: " << rating << endl;
    }
};

class CD : public Media {
private:
    string artist;
    int numberOfTracks;
    string genre;

public:
    CD(const string& title, const string& publicationDate, const string& uniqueID, const string& publisher,
       const string& artist, int numberOfTracks, const string& genre)
        : Media(title, publicationDate, uniqueID, publisher), artist(artist), numberOfTracks(numberOfTracks), genre(genre) {}

    void displayInfo() const override {
        Media::displayInfo();
        cout << "Artist: " << artist << endl;
        cout << "Number of Tracks: " << numberOfTracks << endl;
        cout << "Genre: " << genre << endl;
    }
};

Media* searchMediaByTitle(Media* mediaList[], int size, const string& title) {
    for (int i = 0; i < size; ++i) {
        if (mediaList[i]->getTitle() == title) {
            return mediaList[i];
        }
    }
    return nullptr;
}

Media* searchMediaByAuthor(Media* mediaList[], int size, const string& author) {
    for (int i = 0; i < size; ++i) {
        if (Book* book = dynamic_cast<Book*>(mediaList[i])) {
            if (book->getAuthor() == author) {
                return mediaList[i];
            }
        }
    }
    return nullptr;
}

Media* searchMediaByPublicationDate(Media* mediaList[], int size, const string& publicationDate) {
    for (int i = 0; i < size; ++i) {
        if (mediaList[i]->getPublicationDate() == publicationDate) {
            return mediaList[i];
        }
    }
    return nullptr;
}

int main() {
    Media* mediaList[3];

    mediaList[0] = new Book("The C++ Programming Language", "1985", "B123", "Addison-Wesley", "Bjarne Stroustrup", "978-0321563842", 1376);
    mediaList[1] = new DVD("Inception", "2010", "D456", "Warner Bros.", "Christopher Nolan", 148, "PG-13");
    mediaList[2] = new CD("Thriller", "1982", "C789", "Epic Records", "Michael Jackson", 9, "Pop");

    cout << "Displaying all media:\n";
    for (int i = 0; i < 3; ++i) {
        mediaList[i]->displayInfo();
        cout << "---------------------\n";
    }

    mediaList[0]->checkOut();
    mediaList[0]->returnItem();

    Media* foundTitle = searchMediaByTitle(mediaList, 3, "Inception");
    cout << "\nSearch results by title (Inception):\n";
    if (foundTitle) {
        foundTitle->displayInfo();
    } else {
        cout << "No media found with that title.\n";
    }

    Media* foundAuthor = searchMediaByAuthor(mediaList, 3, "Bjarne Stroustrup");
    cout << "\nSearch results by author (Bjarne Stroustrup):\n";
    if (foundAuthor) {
        foundAuthor->displayInfo();
    } else {
        cout << "No media found with that author.\n";
    }

    Media* foundPublicationDate = searchMediaByPublicationDate(mediaList, 3, "2010");
    cout << "\nSearch results by publication date (2010):\n";
    if (foundPublicationDate) {
        foundPublicationDate->displayInfo();
    } else {
        cout << "No media found with that publication date.\n";
    }

    for (int i = 0; i < 3; ++i) {
        delete mediaList[i];
    }

    return 0;
}
