#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STUDENT_NUMBER "220104004829"
#define STONE '1'
#define PAPER '2'
#define SCISSORS '3'

void print_menu(); //show the items in the menu to the terminal
void head_of_receipt(); //print the student number, time and "Product Price(TL)" to the receipt file
int choose_dish(); //get dish number from user
int choose_serving();	//get serving number from user 
void print_after_discount(float total);	//calculate and print prices, discounts, VAT to the receipt file
void print_receipt_file();  //print receipt file to the terminal
void part1(); //do part1 missions, print selected dish name to the receipt file, calculate prices before discounts
void part2(); //stone-paper-scissors game

int main(){

    part1();  //generate the receipt
    part2();	//stone-paper-scissors game
}

void print_menu(){ //print the menu to the terminal

    FILE *menu;
    char a;
    int counter1=0, counter2=0;

    if((menu = fopen("menu.txt", "r"))!=NULL){ //open "menu.txt" file for reading
    while((a=fgetc(menu))!=EOF){	//pass "Product Price (TL)" text while reading menu.txt
        if(a==' ' || a=='\n'){
            counter1++;
        }
        if(counter1==3){
            break;
        }
    }
    printf("%d. ", (counter2/2+1)); //print row number "1." for the first item in the menu to the terminal.

    while((a=fgetc(menu))!=EOF){

        if(a==' ' || a=='\n'){
            counter2++;
        }
        if(counter2%2==0){	//when counter2 is even, print the characters (dish names in menu) to the terminal
            printf("%c", a);
            if(a=='\n' && counter2!=20){
                printf("%d. ", (counter2/2+1));    //print row numbers before the items in the menu to the terminal 
            }
        }
    }
}
fclose(menu);	//close the "menu.txt" file

}

void head_of_receipt(){	//print the school number, time and "Product Price(TL)" to the receipt file

FILE *receipt;
time_t t= time(NULL);
struct tm *tm = localtime(&t);
char s[64];

receipt= fopen("receipt.txt", "w");	// open "receipt.txt" file for writing
strftime(s,sizeof(s),"%d.%m.%Y/%H:%M",tm); //get the current time

fprintf(receipt, "%s", STUDENT_NUMBER);	//print the student number to receipt file
fprintf(receipt,"%24s\n\n",s);	//print the time to receipt file
fprintf(receipt, "------------------------------------%c\n", '\n');
fprintf(receipt, "%s%29s\n\n", "Product", "Price (TL)");	//print "Product Price(TL)" to the receipt file

fclose(receipt);	//close the "receipt.txt" file

}

int choose_dish(){	
    int dish;
    //get dish number from the user until number is between 0-10
    do{
        printf("Please choose a product (1-10): ");
        scanf("%d", &dish);
    }
    while(dish<0 || dish>10);
    return dish; 	//return dish number
}

int choose_serving(){
    int serving;
    //get serving number
    printf("How many servings do you want? ");
    scanf("%d", &serving);
    return serving;	//return serving number
}


void print_after_discount(float total){

FILE *receipt;
float last_total, vat, student_discount=0;
char student;
float discount_150=0;

receipt=fopen("receipt.txt", "a+");	//open receipt.txt for adding
//ask user if him/her is a student
do{
    printf("Are you student? (Y/N): ");
    scanf(" %c", &student);
}
while(student!='Y' && student!='N');

if(student=='Y'){	//calculate student discount and 150tl or more discount and price after all discounts
    student_discount=(0-((total*125)/1000));
    if(total>=150){
        last_total=((total*775)/1000); 
        discount_150=0-(total*0.1);      
    }
    else{
        last_total=((total*875)/1000);
    }
}
else if(total>=150){
    discount_150=0-(total*0.1);
    last_total=((total*9)/10);
}
else{
    last_total=total;
}

vat=last_total*0.18;	//calculate VAT %18
//print price before discounts, student discount,150 tl or more discount, price after discounts, price+VAT to the receipt file.
fprintf(receipt, "Total:%30.2f\n\n", total);
fprintf(receipt, "Student discount:%19.2f\n\n", student_discount);
fprintf(receipt,"150 TL or more discount:%12.2f\n\n", discount_150);
fprintf(receipt, "------------------------------------%c\n", '\n');
fprintf(receipt, "Price:%30.2f\n\n", last_total);
fprintf(receipt, "Price + VAT:%24.2f\n\n", (last_total+vat));
fclose(receipt);	//close "receipt.txt" file

}

void print_receipt_file(){  //print receipt file to the terminal

        FILE *receipt = fopen("receipt.txt","r");
        char a;
        printf("\n\n");
        while((a=fgetc(receipt))!=EOF){
            printf("%c",a);
        }
        fclose(receipt); //close the receipt file

}

void part1(){

FILE *menu;
FILE *receipt;
char a;
int counter1=0, counter2=0;
int dish=1, serving=1;
float num;
float p1,p2,p3,p4,p5,p6,p7,p8,p9,p10; //prices of each item in menu
float total; //price before discounts
int character=0;

print_menu(); //print the menu to the terminal

if((menu = fopen("menu.txt", "r"))!=NULL){
    while((a=fgetc(menu))!=EOF){ //pass "Product Price (TL)" text while reading menu.txt
        if(a==' ' || a=='\n'){
            counter1++;
        }
        if(counter1==3){
            break;
        }
    }
    while((a=fgetc(menu))!=EOF){

        if(a==' ' || a=='\n'){
            counter2++;
        }
        if(counter2%2!=0){	
            //when counter2 is odd get the prices of each item
            fscanf(menu, "%f", &num);	
            switch(counter2){
                case 1:
                    p1=num;
                    break;
                case 3:
                    p2=num;
                    break;
                case 5:
                    p3=num;
                    break;
                case 7:
                    p4=num;
                    break;
                case 9:
                    p5=num;
                    break;
                case 11:
                    p6=num;
                    break;
                case 13:
                    p7=num;
                    break;
                case 15:
                    p8=num;
                    break;
                case 17:
                    p9=num;
                    break;
                case 19:
                    p10=num;
                    break;
            }
        }
    }
    fclose(menu);	//close "menu.txt" file
    
    head_of_receipt();	//print the head of the receipt to receipt file.
    receipt=fopen("receipt.txt", "a+");	//open receipt.txt file for adding
       
    while(serving!=0){
        dish= choose_dish();	//get the dish number
        serving= choose_serving();	//get the serving number
        counter1=0;
        counter2=0;
        character=0;	//number characters in dish name
        if(serving==0 || dish==0){
            break;	//stops adding new dish to the receipt file
        }
        else{
            menu=fopen("menu.txt", "r");	//open menu for reading
            if(serving!=1){	//when serving is a number other then 1, print the number to the receipt file
                fprintf(receipt, "%d* ", serving);
            }
            while((a=fgetc(menu))!=EOF){//pass "Product Price (TL)" text while reading menu.txt
                if(a==' ' || a=='\n'){
                    counter1++;
                }
                if(counter1==3){
                    break;
                }
            }
            //when counter reaches the desired dish calculate the character number in the dish and print the dish name to the receipt file
            while(counter2<=((2*dish)-2)){	
                a=fgetc(menu);
                if(a==' ' || a=='\n'){
                    counter2++;
                }
                if(counter2==((2*dish)-2)&& a!='\n'){
                    character++;
                    fprintf(receipt, "%c", a);
                    
                }   
            }
            fclose(menu);	//close menu.txt file
            if(serving==1){	//is for arranging the tidy image of receipt
                fprintf(receipt, "    ");
            }
            else if(serving<10){
                fprintf(receipt, " ");
            }
            switch(dish){
                //add the price of desired dish times serving to the total price and print the price to the receipt file
                case 1:
                    total+= p1*serving;
                    fprintf(receipt, "%*.2f\n\n",(32-character), p1*serving);
                    break;
                case 2:
                    total+= p2*serving;
                    fprintf(receipt, "%*.2f\n\n",(32-character), p2*serving);
                    break;
                case 3:
                    total+= p3*serving;
                    fprintf(receipt, "%*.2f\n\n",(32-character), p3*serving);
                    break;
                case 4:
                    total+= p4*serving;
                    fprintf(receipt, "%*.2f\n\n",(33-character) ,p4*serving);
                    break;
                case 5:
                    total+= p5*serving;
                    fprintf(receipt, "%*.2f\n\n",(32-character) , p5*serving);
                    break;
                case 6:
                    total+= p6*serving;
                    fprintf(receipt, "%*.2f\n\n",(32-character) , p6*serving);
                    break;
                case 7:
                    total+= p7*serving;
                    fprintf(receipt, "%*.2f\n\n",(33-character) , p7*serving);
                    break;
                case 8:
                    total+= p8*serving;
                    fprintf(receipt, "%*.2f\n\n",(34-character) , p8*serving);
                    break;
                case 9:
                    total+= p9*serving;
                    fprintf(receipt, "%*.2f\n\n",(32-character) , p9*serving);
                    break;
                case 10:
                    total+= p10*serving;
                    fprintf(receipt, "%*.2f\n\n",(32-character) , p10*serving);
                    break;
            }

        }
    }

}
fclose(receipt);	//close the receipt.txt file
print_after_discount(total);	//calculate and print prices, discounts, VAT to the receipt file
print_receipt_file();   //print the receipt file to the terminal

}

void part2(){

char user;
char flag='Y';
int comp;

//stone-paper-scissors game

while(flag=='Y'){ //While user say yes ('Y'), game continues
	do{
		//get the choice of user until it is 1, 2 or 3.
		printf("Please make a choice!\n");
		printf("1: Stone, 2: Paper, 3: Scissors\n");
		scanf(" %c", &user);}
	while(user!='1' && user!='2' && user!='3');
        srand(time(NULL));	//feed srand
        comp= ((rand()%3)+1);	//generate a random number between 1-3
        
        switch(user){	//according to the considitions print the winner
            case STONE :
                printf("You chose Stone. I chose ");
                switch(comp){
                    case 1:
                        printf("Stone. It's a tie!\n");
                        break;
                    case 2:
                        printf(" Paper. I won!\n");
                        break;
                    case 3:
                        printf(" Scissors. You won!\n");
                        break;
                }
                break;
            case PAPER :
                printf("You chose Paper. I chose ");
                switch(comp){
                    case 1:
                        printf(" Stone. You won!\n");
                        break;
                    case 2:
                        printf(" Paper. It's a tie!\n");
                        break;
                    case 3:
                        printf(" Scissors. I won!\n");
                        break;
                }
                break;
            case SCISSORS :
                printf("You chose Scissors. I chose ");
                switch(comp){
                    case 1:
                        printf(" Stone. I won!\n");
                        break;
                    case 2:
                        printf(" Paper. You won!\n");
                        break;
                    case 3:
                        printf(" Scissors. It's a tie!\n");
                        break;
                }
                break;       
        }
        do{	//ask user whether continue or nor
		printf("Do you want to play again? (Y/N): ");
		scanf(" %c", &flag);
        }
        while(flag!='Y'&& flag!='N');
}

if(flag=='N'){	//print game is over message
	printf("Game is over!\n");
}

}
