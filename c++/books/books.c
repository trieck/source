
/* books.c
 *
 * a book database
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* represents a book
*/
typedef struct Book {
    char title[100];
    char author[100];
    char isbn[20];
    int year;
    struct Book *left;
    struct Book *right;
} Book;

/*
 * the root of the tree
 */
static Book *books = NULL;
static const char *usage = "usage: books [-A | -l | -a][title][author][isbn][year]\n"
                           "\t-A, list all books.\n"
                           "\t-l, look up a book supplying title.\n"
                           "\t-a, add a book supplying title, author, isbn, year.\n";

static const char *filename = "books.db";

static void cleanup(void);
static void addBook(Book **root, Book *book);
static Book * allocBook(void);
static void freeBook(Book *book);
static Book * lookupBook(Book *root, const char *title);
static void writeDb(Book *book, FILE *fp);
static void readDb(void);
static int readRecord(FILE *fp);
static void printBook(Book *book);
static void viewBooks(Book *root);

int main(int argc, char *argv[])
{
    const char **pargs = argv;
    argv++;
    argc--;

    atexit(cleanup);

    if (argc < 1) {
        fprintf(stderr, usage);
        return 1;
    }

    /* read the database into memory */
    readDb();

    /* parse command line arguments */
    for ( ; *pargs; pargs++) {
        switch (pargs[0][0]) {
        case '-':
            if (pargs[0][1] == 'A') {
                /* display all books */
                viewBooks(books);
            } else if (pargs[0][1] == 'l') {
                /* lookup the book by title */
                Book *B;
                if (argc < 2) {
                    fprintf(stderr, usage);
                    return 1;
                }
                B = lookupBook(books, *(++pargs));
                if (B == NULL)
                    fprintf(stderr, "\ncould not find book.\n");
                else printBook(B);
                argc--;
                argc--;
            } else if (pargs[0][1] == 'a') {
                /* add a book */
                Book book;
                if (argc < 4) {
                    fprintf(stderr, usage);
                    return 1;
                }
                strcpy(book.title, *(++pargs));
                strcpy(book.author, *(++pargs));
                strcpy(book.isbn, *(++pargs));
                book.year = atoi(*(++pargs));
                addBook(&books, &book);
                printBook(&book);
                argc--;
                argc -= 4;
            }
            break;
        default:
            break;
        }
    }

    return 0;
}

/*
 * write database to file and
 * free allocated resources
 */
void cleanup(void)
{
    if (NULL != books) {
        FILE *fp = fopen(filename, "w+");
        if (NULL != fp) {
            writeDb(books, fp);
            fclose(fp);
        }
        freeBook(books);
    }
}

/*
 * add a book to the tree
 */
void addBook(Book **root, Book *book)
{
    int M;
    Book *B = *root;

    if (*root == NULL) {
        *root = allocBook();
        strcpy((*root)->title, book->title);
        strcpy((*root)->author, book->author);
        strcpy((*root)->isbn, book->isbn);
        (*root)->year = book->year;
        return;	// we inserted the book
    }

    // compare the title descriptions
    M = stricmp(book->title, B->title);
    if (M < 0) {
        addBook(&B->left, book);
    } else if (M >= 1) {
        addBook(&B->right, book);
    } else {
        // they're the same
        fprintf(stderr, "\nyou cannot add duplicate items.\n");
        return;
    }
}

/*
 * allocate a book
 */
Book * allocBook()
{
    Book *B = (Book*)malloc(sizeof(Book));
    if (NULL == B) {
        fprintf(stderr, "could not allocate a book!\n");
        exit(-1);
    }

    memset(B, 0, sizeof(Book));

    return B;
}

/*
 * free a book
 */
void freeBook(Book *B)
{
    if (B != NULL) {
        freeBook(B->left);
        freeBook(B->right);
        free(B);
    }
}

/*
 * lookup a book by title
 */
Book * lookupBook(Book *root, const char *title)
{
    int M;

    if (NULL == root)
        return NULL;

    M = stricmp(title, root->title);
    if (M < 0)
        return lookupBook(root->left, title);
    else if (M >= 1)
        return lookupBook(root->right, title);

    return root;
}

/*
 * write database to a file
 */
void writeDb(Book *book, FILE *fp)
{
    if (NULL != book) {
        fprintf(fp, "%d\1%s%d\1%s%d\1%s%d\1",
                strlen(book->title),
                book->title,
                strlen(book->author),
                book->author,
                strlen(book->isbn),
                book->isbn,
                book->year);

        writeDb(book->left, fp);
        writeDb(book->right, fp);
    }
}

/*
 * read database from a file
 */
void readDb(void)
{
    FILE *fp;

    fp = fopen(filename, "r");
    if (NULL == fp) {
        fprintf(stderr, "warning: database file not found.\n");
        return;	// empty or not found
    }

    while (readRecord(fp))
        ;

    fclose(fp);
}

/*
 * read a record
 */
int readRecord(FILE *fp)
{
    int c, len;
    Book b;
    b.left = b.right = NULL;

    /* check for eof, since we don't know file size */
    c = fgetc(fp);
    if (EOF == c)
        return 0;

    ungetc(c, fp);

    fscanf(fp, "%d", &len);
    fgetc(fp);	// throw away terminator
    fread(b.title, len, 1, fp);
    b.title[len] = '\0';

    fscanf(fp, "%d", &len);
    fgetc(fp);	// throw away terminator
    fread(b.author, len, 1, fp);
    b.author[len] = '\0';

    fscanf(fp, "%d", &len);
    fgetc(fp);	// throw away terminator
    fread(b.isbn, len, 1, fp);
    b.isbn[len] = '\0';

    fscanf(fp, "%d", &b.year);
    fgetc(fp);	// throw away terminator

    addBook(&books, &b);

    return 1;
}

/*
 * print book details
 */
void printBook(Book *book)
{
    printf("\nTitle:\t\t%s\n", book->title);
    printf("Author:\t\t%s\n", book->author);
    printf("ISBN:\t\t%s\n", book->isbn);
    printf("Year Published:\t%d\n", book->year);
}

/*
 * view all the books
 */
void viewBooks(Book *root)
{
    if (root == NULL)
        return;

    printBook(root);

    viewBooks(root->left);
    viewBooks(root->right);
}