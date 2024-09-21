#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book {
    char ISBN[20];
    char title[100];
    char author[100];
    char year[5];
    int reversed_status;
    struct Book *next;
} Book;

typedef struct Student {
    char name[50];
    int ID;
    char borrowed_books[10][100];
    struct Student *next;
} Student;

void borrowedBookList(Student **student_ll, int id);
void addBook(Book **book_ll, char *isbn, char *title, char *author, char *publicationYear, int method);
void deleteBook(Book **book_ll, char *isbn);
void updateBook(Book **book_ll, char *isbn, char *feature, char* value);
void searchBook(Book **book_ll, int searchChoice, char *searchValue);
void borrowBook();

int main() {
    Book *book_ll=(Book *)malloc(sizeof(Book)); // pointer to Book linked list
    Student *student_ll=(Student *)malloc(sizeof(Student));
    Book *tempb=book_ll;
    Student *temps=student_ll;
    FILE *bf;//book file
    FILE *sf;//student file
    char c,a,i=1,w=0,l=0;
    char isbn[20];
    char title[100];
    char author[100];
    char year[5];
    int id;
    int method;
    char feature[10];
    char value[50];
    int option;
    int searchChoice;
    char searchValue[50];
    int exit=0;

    bf = fopen("book.txt", "r");
    if (bf == NULL) {
        printf("File cannot be opened.\n");
        return 0;
    }

    while(feof(bf) == 0){

        fscanf(bf,"%[^,],%[^,],%[^,],%[^,],%d", tempb->ISBN, tempb->title, tempb->author, tempb->year, &tempb->reversed_status);
        c=fgetc(bf);
        if(c=='\n'){
            tempb->next = (Book *)malloc(sizeof(Book));
            tempb = tempb->next;
            tempb->next = NULL;
        }
        else{
            tempb->next = NULL;
        }
    }    
    fclose(bf);

    sf = fopen("student.txt", "r");
    if (sf == NULL) {
        printf("File cannot be opened.\n");
        return 0;
    }

    while(feof(sf) == 0){

        fscanf(sf,"%[^,],%d,", temps->name, &temps->ID);
        for(int j=0; j<10; j++){
            temps->borrowed_books[j][0]='\0';
        }
        w=0;
        l=0;
        while((a=fgetc(sf))!=EOF){
            if(a==','){
                temps->borrowed_books[w][l]='\0';
                w++;
                l=0;
            }
            else if(a=='\n'){
                temps->borrowed_books[w][l]='\0';
                break;
            }
            else{
                temps->borrowed_books[w][l]=a;
                l++;
            }
        }
        
        if(a=='\n'){
            i=1;
            temps->next = (Student *)malloc(sizeof(Student));
            temps = temps->next;
            temps->next = NULL;
        }
        else{
            temps->next = NULL;
            i=1;
        }
    }    
    fclose(sf);

do{

    do{
        printf("\nMenu:\n1. Student's Borrowed Book List\n2. Add Book\n3. Delete Book\n4. Update Book\n5. Filter and Sort Books\n6. Reverse Book List\n7. Search Books\n8. Borrow Books\n9. Return Books\n10.Exit\n");
        scanf("%d", &option);
    }
    while(option<1 || option>10);

    switch(option){
        case 1: //student's borrowed book list
            printf("\nEnter the ID of the student: ");
            scanf("%d", &id);
            borrowedBookList(&student_ll, id);
            break;
        case 2://add book
            printf("\nEnter the ISBN: ");
            scanf(" %[^\n]", isbn);
            printf("\nEnter the title: ");
            scanf(" %[^\n]", title);
            printf("\nEnter the author: ");
            scanf(" %[^\n]", author);
            printf("\nEnter the year: ");
            scanf(" %[^\n]", year);
            printf("\nEnter the method(0=FIFO, 1=LIFO): ");
            scanf("%d", &method);
            addBook(&book_ll, isbn, title, author, year, method);
            break;
        case 3://delete book
            printf("\nEnter the ISBN number: ");
            scanf(" %[^\n]", isbn);
            deleteBook(&book_ll, isbn);
            break;
        case 4: //update book
            printf("\nEnter the ISBN: ");
            scanf(" %[^\n]", isbn);
            printf("\nEnter the feature: ");
            scanf(" %[^\n]", feature);
            printf("\nEnter the value: ");
            scanf(" %[^\n]", value);
            updateBook(&book_ll, isbn, feature, value);
            break;
        case 5: //
            printf("\nyapmadım");
            break;
        case 6: //
            printf("\nyapmadım");
            break;  
        case 7: //search books
            printf("\nEnter the search choice(0=ISBN, 1=author, 2=title) and search value: ");
            scanf("%d %[^\n]", &searchChoice, searchValue);
            searchBook(&book_ll, searchChoice, searchValue);
            break;  
        case 8: //
            printf("\nyapmadım");
            break; 
        case 9: //
            printf("\nyapmadım");
            break;
        case 10: //exit
            exit=1;
            break;    
    }

}
while(exit==0);
    return 0;
}

void addBook(Book **book_ll, char *isbn, char *title, char *author, char *publicationYear, int method) {
    Book *nb = (Book *)malloc(sizeof(Book)); // new book
    Book *temp1 = *book_ll;
    Book *temp2= *book_ll;
    FILE *bf;
    FILE *newf;
    char c;
    int i=0;

    strcpy(nb->ISBN, isbn);
    strcpy(nb->title, title);
    strcpy(nb->author, author);
    strcpy(nb->year, publicationYear);
    nb->reversed_status = 0;
    nb->next = NULL;

    if (method == 1) { // LIFO
        if (*book_ll == NULL) {
            *book_ll = nb;
        } else {
            nb->next = *book_ll;
            *book_ll = nb;
            temp2= *book_ll;//ekledim
        }
    } else if (method == 0) { // FIFO
        if (*book_ll == NULL) {
            *book_ll = nb;
        } else {
            while (temp1->next!= NULL) temp1 = temp1->next;
            temp1->next=nb;
        }
    }

    bf=fopen("book.txt", "r");
    newf= fopen("newbook.txt", "w+");
    if (bf == NULL) {
        printf("File cannot be opened.\n");
        return ;
    }
    if (newf == NULL) {
        printf("File cannot be opened.\n");
        return ;
    }
    while(temp2->next!=NULL){
        fprintf(newf, "%s,%s,%s,%s,%d\n", temp2->ISBN, temp2->title, temp2->author, temp2->year, temp2->reversed_status);
        temp2=temp2->next;
    }
    fprintf(newf, "%s,%s,%s,%s,%d", temp2->ISBN, temp2->title, temp2->author, temp2->year, temp2->reversed_status);
    fclose(bf);
    fclose(newf);
    remove("book.txt");
    rename("newbook.txt", "book.txt");
}

void deleteBook(Book **book_ll, char *isbn){
    FILE *bf;
    FILE *newf;
    Book *cp, *bp, *temp3;
    cp=bp=temp3=*book_ll;
    char c;

    while(cp!=NULL && strcmp(cp->ISBN, isbn)!=0){
        bp=cp;
        cp=cp->next;
    }
    if(cp!=NULL){

        if(cp==bp){
            *book_ll= cp->next; //removes first node
        } 
        else{
             bp->next=cp->next;
        }
        free(cp);
        printf("Deletion is susccesful.\n\n");


        bf=fopen("book.txt", "r");
        newf= fopen("newbook.txt", "w+");
        if (bf == NULL) {
            printf("File cannot be opened.\n");
            return ;
        }
        if (newf == NULL) {
            printf("File cannot be opened.\n");
            return ;
        }
        temp3=*book_ll;
        while(temp3->next!=NULL){
            fprintf(newf, "%s,%s,%s,%s,%d\n", temp3->ISBN, temp3->title, temp3->author, temp3->year, temp3->reversed_status);
            temp3=temp3->next;
        }
        fprintf(newf, "%s,%s,%s,%s,%d", temp3->ISBN, temp3->title, temp3->author, temp3->year, temp3->reversed_status);
        fclose(bf);
        fclose(newf);
        remove("book.txt");
        rename("newbook.txt", "book.txt");
        return;
    }
    printf("Book does not exist.\n\n");
}


void updateBook(Book **book_ll, char *isbn, char *feature, char* value){
    FILE *bf,*newf;
    Book* temp4= *book_ll;
    Book* temp5= *book_ll;

    if(temp4==NULL){
        printf("Book does not exist.\n\n");
        return ;
    }
    while(strcmp(temp4->ISBN, isbn)!=0) temp4= temp4->next;
    if(strcmp(feature, "title")==0 || strcmp(feature, "Title")==0){
        strcpy(temp4->title, value);
    }
    else if(strcmp(feature, "author")==0 || strcmp(feature, "Author")==0){
        strcpy(temp4->author, value);
    }
    else if(strcmp(feature, "publication year")==0 || strcmp(feature, "Publication year")==0){
        strcpy(temp4->year, value);
    }
    else{
        printf("Feature is wrong.\n\n");
        
    }

    bf=fopen("book.txt", "r");
    newf= fopen("newbook.txt", "w+");
    if (bf == NULL) {
        printf("File cannot be opened.\n");
        return ;
    }
    if (newf == NULL) {
        printf("File cannot be opened.\n");
        return ;
    }
    while(temp5->next!=NULL){
        fprintf(newf, "%s,%s,%s,%s,%d\n", temp5->ISBN, temp5->title, temp5->author, temp5->year, temp5->reversed_status);
        temp5=temp5->next;
    }
    fprintf(newf, "%s,%s,%s,%s,%d", temp5->ISBN, temp5->title, temp5->author, temp5->year, temp5->reversed_status);
    fclose(bf);
    fclose(newf);
    remove("book.txt");
    rename("newbook.txt", "book.txt");

}

void searchBook(Book **book_ll, int searchChoice, char *searchValue){

    Book *temp6= *book_ll;
    int flag=0;

    switch(searchChoice){
        case 0:
            while(temp6!=NULL){
                if(strcmp(temp6->ISBN, searchValue)==0){
                    printf("%s, %s, %s, %s, %d\n", temp6->ISBN, temp6->title, temp6->author, temp6->year, temp6->reversed_status);
                    flag=1;
                }
                temp6=temp6->next;
            }
            break;
        case 1:
            while(temp6!=NULL){
                if(strcmp(temp6->author, searchValue)==0){
                    printf("%s, %s, %s, %s, %d\n", temp6->ISBN, temp6->title, temp6->author, temp6->year, temp6->reversed_status);
                    flag=1;
                }
                temp6=temp6->next;
            }           
            break;
        case 2:
            while(temp6!=NULL){
                if(strcmp(temp6->title, searchValue)==0){
                    printf("%s, %s, %s, %s, %d\n", temp6->ISBN, temp6->title, temp6->author, temp6->year, temp6->reversed_status);
                    flag=1;
                }
                temp6=temp6->next;
            }
             break;
    }
    if(flag==0){
        printf("Book was not found.\n\n");
    }
}

void borrowedBookList(Student **student_ll, int id){

    Student *temp7= *student_ll;;

    while(temp7!=NULL){
        if(temp7->ID==id){
            for(int j=0; temp7->borrowed_books[j][0]!='\0'; j++){
                if(j==10){
                    break;
                }
                printf("%s\n", temp7->borrowed_books[j]);
            }
            return ;
        }
        else{
            temp7=temp7->next;
        }
    }
    printf("Stundent with this ID was not found.\n\n");
    return ;

}
