#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BOOKS 100
#define MAX_PATRONS 50
#define MAX_BORROWED 3
#define FINE_PER_DAY 1.0

typedef struct {
    int id;
    char title[100];
    char author[100];
    int isAvailable;
} Book;

typedef struct {
    int id;
    char name[100];
    int numBooksBorrowed;
    int borrowedBooks[MAX_BORROWED];
} Patron;

void addBook(Book books[], int *numBooks);
void addPatron(Patron patrons[], int *numPatrons);
void borrowBook(Book books[], Patron patrons[], int numBooks, int numPatrons);
void returnBook(Book books[], Patron patrons[], int numBooks, int numPatrons);
void generateReport(Patron patrons[], int numPatrons);

int main() {
    Book books[MAX_BOOKS];
    Patron patrons[MAX_PATRONS];
    int numBooks = 0;
    int numPatrons = 0;
    
    int choice;
    do {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Add Patron\n");
        printf("3. Borrow Book\n");
        printf("4. Return Book\n");
        printf("5. Generate Report\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addBook(books, &numBooks);
                break;
            case 2:
                addPatron(patrons, &numPatrons);
                break;
            case 3:
                borrowBook(books, patrons, numBooks, numPatrons);
                break;
            case 4:
                returnBook(books, patrons, numBooks, numPatrons);
                break;
            case 5:
                generateReport(patrons, numPatrons);
                break;
            case 6:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 6);
    
    return 0;
}

void addBook(Book books[], int *numBooks) {
    if (*numBooks >= MAX_BOOKS) {
        printf("Cannot add more books. Library capacity reached.\n");
        return;
    }
    
    printf("Enter book title: ");
    scanf(" %[^\n]", books[*numBooks].title);
    printf("Enter book author: ");
    scanf(" %[^\n]", books[*numBooks].author);
    books[*numBooks].id = *numBooks + 1;
    books[*numBooks].isAvailable = 1;
    (*numBooks)++;
    printf("Book added successfully.\n");
}

void addPatron(Patron patrons[], int *numPatrons) {
    if (*numPatrons >= MAX_PATRONS) {
        printf("Cannot add more patrons. Patron capacity reached.\n");
        return;
    }
    
    printf("Enter patron name: ");
    scanf(" %[^\n]", patrons[*numPatrons].name);
    patrons[*numPatrons].id = *numPatrons + 1;
    patrons[*numPatrons].numBooksBorrowed = 0;
    (*numPatrons)++;
    printf("Patron added successfully.\n");
}

void borrowBook(Book books[], Patron patrons[], int numBooks, int numPatrons) {
    int patronId, bookId;
    printf("Enter patron ID: ");
    scanf("%d", &patronId);
    if (patronId < 1 || patronId > numPatrons) {
        printf("Invalid patron ID.\n");
        return;
    }
    
    printf("Enter book ID to borrow: ");
    scanf("%d", &bookId);
    if (bookId < 1 || bookId > numBooks) {
        printf("Invalid book ID.\n");
        return;
    }
    
    Patron *patron = &patrons[patronId - 1];
    Book *book = &books[bookId - 1];
    
    if (patron->numBooksBorrowed >= MAX_BORROWED) {
        printf("Patron has already borrowed the maximum number of books.\n");
        return;
    }
    
    if (!book->isAvailable) {
        printf("Book is not available for borrowing.\n");
        return;
    }
    
    patron->borrowedBooks[patron->numBooksBorrowed++] = bookId;
    book->isAvailable = 0;
    printf("Book borrowed successfully.\n");
}

void returnBook(Book books[], Patron patrons[], int numBooks, int numPatrons) {
    int patronId, bookId;
    printf("Enter patron ID: ");
    scanf("%d", &patronId);
    if (patronId < 1 || patronId > numPatrons) {
        printf("Invalid patron ID.\n");
        return;
    }
    
    printf("Enter book ID to return: ");
    scanf("%d", &bookId);
    if (bookId < 1 || bookId > numBooks) {
        printf("Invalid book ID.\n");
        return;
    }
    
    Patron *patron = &patrons[patronId - 1];
    Book *book = &books[bookId - 1];
    
    int i;
    for (i = 0; i < patron->numBooksBorrowed; i++) {
        if (patron->borrowedBooks[i] == bookId) {
            for (int j = i; j < patron->numBooksBorrowed - 1; j++) {
                patron->borrowedBooks[j] = patron->borrowedBooks[j + 1];
            }
            patron->numBooksBorrowed--;
            book->isAvailable = 1;
            printf("Book returned successfully.\n");
            return;
        }
    }
    
    printf("Patron hasn't borrowed this book.\n");
}

void generateReport(Patron patrons[], int numPatrons) {
    printf("\nPatron Report:\n");
    printf("ID\tName\tBooks Borrowed\n");
    for (int i = 0; i < numPatrons; i++) {
        printf("%d\t%s\t%d\n", patrons[i].id, patrons[i].name, patrons[i].numBooksBorrowed);
    }
}
