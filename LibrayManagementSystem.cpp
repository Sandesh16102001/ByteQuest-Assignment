#include <iostream>
#include <vector>
#include <fstream>
#include<string>

class Book
{
public:
    int id;
    std::string title;
    std::string author;
    int quantity;

    Book() : id(0), quantity(0) {}

    Book(int inputID, std::string inputTitle, std::string inputAuthor, int inputQuantity)
    {
        id              =  inputID;
        title           = inputTitle;
        author          = inputAuthor;
        quantity        = inputQuantity;
    }

    void show() const
    {
        std::cout << "ID: " << id << " | Title: " << title << " | Author: " << author << " | Quantity: " << quantity << std::endl;
    }
};

class Library
{
private:
    std::vector<Book> books;

public:
    Library()
    {
        loadFromFile();
    }

    ~Library()
    {
        saveToFile();
    }

    void addBook()
    {
        int id, qty;
        std::string title, author;

        std::cout << "Enter Book ID: ";
        std::cin >> id;

        for (auto& b : books)
        {
            if (b.id == id)
            {
                std::cout << "Book ID already exists.\n";
                return;
            }
        }

        std::cin.ignore();

        std::cout << "Enter Book Title: ";
        std::getline(std::cin, title);

        std::cout << "Enter Author Name: ";
        std::getline(std::cin, author);

        std::cout << "Enter Quantity: ";
        std::cin >> qty;

        books.push_back(Book(id, title, author, qty));
        std::cout << "Book added successfully.\n";
    }

    void searchById()
    {
        int id;
        std::cout << "Enter Book ID: ";
        std::cin >> id;

        for (auto& b : books)
        {
            if (b.id == id)
            {
                b.show();
                return;
            }
        }

        std::cout << "Book not found.\n";
    }

    void searchByTitle()
    {
        std::string title;
        std::cin.ignore();

        std::cout << "Enter Book Title: ";
        std::getline(std::cin, title);

        bool found = false;

        for (auto& b : books)
        {
            if (b.title.find(title) != std::string::npos)
            {
                b.show();
                found = true;
            }
        }

        if (!found)
            std::cout << "Book not found.\n";
    }

    void showAllBooks()
    {
        if (books.empty())
        {
            std::cout << "Library is empty.\n";
            return;
        }

        for (auto& b : books)
            b.show();
    }

    void updateQuantity()
    {
        int id, newQty;
        std::cout << "Enter Book ID: ";
        std::cin >> id;

        for (auto& b : books)
        {
            if (b.id == id)
            {
                std::cout << "Enter new Quantity: ";
                std::cin >> newQty;

                if (newQty < 0)
                {
                    std::cout << "Invalid quantity.\n";
                    return;
                }

                b.quantity = newQty;
                std::cout << "Quantity updated.\n";
                return;
            }
        }

        std::cout << "Book not found.\n";
    }

    void deleteBook()
    {
        int id;
        std::cout << "Enter Book ID: ";
        std::cin >> id;

        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].id == id)
            {
                books.erase(books.begin() + i);
                std::cout << "Book deleted.\n";
                return;
            }
        }

        std::cout << "Book not found.\n";
    }

    // -------- FILE HANDLING --------

    void saveToFile()
    {
        std::ofstream file("books.txt");

        for (auto& b : books)
        {
            file << b.id << "\n";
            file << b.title << "\n";
            file << b.author << "\n";
            file << b.quantity << "\n";
        }

        file.close();
    }


    void loadFromFile()
    {
        std::ifstream file("books.txt");

        if (!file.is_open())
        {
            std::cout << "No saved data found. New database created.\n";
            return;
        }

        books.clear(); // clear previous memory

        int id, qty;
        std::string title, author;

        while (file >> id)
        {
            file.ignore();
            std::getline(file, title);
            std::getline(file, author);
            file >> qty;
            file.ignore();

            books.push_back(Book(id, title, author, qty));
        }

        file.close();

        std::cout << books.size() << " books loaded from file.\n";
    }


};

int main()
{
    Library library;
    int choice;
    std::string name;

    std::cout << "Welcome to ByteQuest Library\n";
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    do
    {
        std::cout << "\nHello " << name << "\n";
        std::cout << "1. Add Book\n";
        std::cout << "2. Search by ID\n";
        std::cout << "3. Search by Title\n";
        std::cout << "4. Show All Books\n";
        std::cout << "5. Update Quantity\n";
        std::cout << "6. Delete Book\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter choice: ";

        std::cin >> choice;

        switch (choice)
        {
        case 1:
            library.addBook();
            break;

        case 2:
            library.searchById();
            break;

        case 3:
            library.searchByTitle();
            break;

        case 4:
            library.showAllBooks();
            break;

        case 5:
            library.updateQuantity();
            break;

        case 6:
            library.deleteBook();
            break;

        case 7:
            std::cout << "Data saved. Exiting...\n";
            break;

        default:
            std::cout << "Invalid choice.\n";
        }

    } while (choice != 7);

    return 0;
}
