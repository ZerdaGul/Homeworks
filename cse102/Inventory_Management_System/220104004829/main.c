#include <stdio.h>
#include <math.h>
#define SIZE_FEATURE 100
#define LENGTH_FEATURE 100

int menu();
int search_product();
int check_stock_status();
void stock_report(double brand_stock_control_array[200][3], int *max);
void list_products();


int file_operations(int *feature_number, char feature_name[SIZE_FEATURE][LENGTH_FEATURE], char feature_value[SIZE_FEATURE][LENGTH_FEATURE], int size_feature_name, int *max_pID);
void calculate_max_pID(int *max_pID);
void calculate_feature_number(int *feature_number,char feature_name[SIZE_FEATURE][LENGTH_FEATURE]);
void add_feature(int *feature_number, char feature_name[SIZE_FEATURE][LENGTH_FEATURE], char feature_value[SIZE_FEATURE][LENGTH_FEATURE], int size_feature_name, int *max_pID);
void add_new_product(int *feature_number,char feature_name[SIZE_FEATURE][LENGTH_FEATURE], char feature_value[SIZE_FEATURE][LENGTH_FEATURE],int *max_pID);
void delete_product(int *feature_number, char feature_value[SIZE_FEATURE][LENGTH_FEATURE],int *max_pID);
int compare(char feature[], char selected[]);
void update_product(int *feature_number,char feature_name[SIZE_FEATURE][LENGTH_FEATURE], char feature_value[SIZE_FEATURE][LENGTH_FEATURE],int *max_pID);
void add_stock();
void delete_stock();
void update_stock();

int brand_stock_match(int *feature_number, char feature_value[SIZE_FEATURE][LENGTH_FEATURE], double brand_stock_control_array[200][3], int *max);
void match_printf(int *max, double brand_stock_control_array[200][3]);
void brand_stock_control(int *feature_number, char feature_value[SIZE_FEATURE][LENGTH_FEATURE], double brand_stock_control_array[200][3], int * max);


int main(){

int max_pID; 
char feature_name[SIZE_FEATURE][LENGTH_FEATURE];
char feature_value[SIZE_FEATURE][LENGTH_FEATURE];
double brand_stock_control_array[200][3];
int feature_number=5;
int option=0;
int back_to_main_menu=0;
int flag=0;
int max=0;
calculate_max_pID(&max_pID);
calculate_feature_number(&feature_number, feature_name);

for(int i=0; i<200; i++){
    for(int j=0; j<3; j++){
        brand_stock_control_array[i][j]=0;
    }
}

while(option!=5){

	back_to_main_menu=0;
	option= menu(); //selects option
	if(option==5){
		stock_report(brand_stock_control_array, &max); //give report
        flag=1;
		break;
	}
	switch(option){
		case 1:
			back_to_main_menu = file_operations(&feature_number, feature_name, feature_value, SIZE_FEATURE, &max_pID);
			break;
		case 2:
			back_to_main_menu = search_product();
			break;
		case 3:
			back_to_main_menu = check_stock_status();
			break;
		case 4:
			brand_stock_control(&feature_number, feature_value, brand_stock_control_array, &max);
			break;
		case 5:
			stock_report(brand_stock_control_array, &max);
			flag=1;
	}
	if(flag==1){
		break;
	}
	else if(back_to_main_menu == 1){
		continue;
	}

}
}

int menu(){

//option from the user
char option;
do{
	printf("\nWelcome operator, please select an option to continue: \n");
	printf("1- File Operation\n2- Query products\n3- Check stock status\n4- Stock control by brand\n5- Export report\n");
	scanf(" %c", &option);
}
while(option<'1' || option>'5') ;

return (option-'0');
}

int file_operations(int *feature_number, char feature_name[SIZE_FEATURE][LENGTH_FEATURE], char feature_value[SIZE_FEATURE][LENGTH_FEATURE], int size_feature_name, int *max_pID){

char option;
int back_to_main_menu = 0;

do{
printf("\nSelect an file operation:\n1. Add a new product\n2. Delete a product\n3. Update a product\n4. Add feature to products\n5. Add a new stock entry\n6. Delete a stock entry\n7. Update a stock entry\n8. Back to main menu\n");
scanf(" %c", &option);
}
while(option<'1' || option>'8');

//implement the desired operation
switch(option){
	case '1':
		add_new_product(feature_number,feature_name, feature_value, max_pID);
		break;
	case '2':
		delete_product(feature_number, feature_value, max_pID);
		break;
	case '3':
		update_product(feature_number,feature_name, feature_value, max_pID);
		break;
	case '4':
		add_feature(feature_number, feature_name, feature_value, size_feature_name, max_pID);
		break;
	case '5':
		add_stock();
		break;
	case '6':
		delete_stock();
		break;
	case '7':
		update_stock();
		break;
	case '8':
		back_to_main_menu=1;
		break;
}

return back_to_main_menu;

}
int search_product(){

char option;
int back_to_main_menu = 0;
do{
printf("\nMenu:\n1. List all products\n2. Filter products by brand, type, price or a user defined feature\n3. Back to main menu\n");
scanf(" %c", &option);
}
while(option<'1' || option>'3');

switch(option){
	case '1':
		list_products();
		break;
	case '2':
		printf("this part doens't work\n");
		break;
	case '3':
		back_to_main_menu=1;	
		break;
}

return back_to_main_menu;
}


int check_stock_status(){

char option;
int back_to_main_menu = 0;
do{
printf("\nMenu:\n1. \n2. \n3. \n4. Back to main menu\n");
scanf(" %c", &option);
}
while(option<'1' || option>'4');

switch(option){
	case '1':
		printf("this part doens't work\n");
		break;
	case '2':
		printf("this part doens't work\n");
		break;
	case '3':
		printf("this part doens't work\n");
		break;
	case '4':
		back_to_main_menu=1;	
		break;
}

return back_to_main_menu;

}



void add_feature(int *feature_number, char feature_name[SIZE_FEATURE][LENGTH_FEATURE], char feature_value[SIZE_FEATURE][LENGTH_FEATURE], int size_feature_name, int *max_pID){

FILE *pf;
FILE *npf;
int pID;
char type;
char name[9];
char brand[6];
double price;
char c;


pf = fopen("products.txt", "r");
npf= fopen("new_products.txt", "w+");
if(pf==NULL){
    printf("Files can not be opened.\n");
    return ;
}
if(npf==NULL){
    printf("Files can not be opened.\n");
    return ;   
}
if(*feature_number==size_feature_name){
    printf("\nNew feature can not append, size is full.\n");
}

printf("Enter the name of the new feature: ");
scanf(" %[^\n]", feature_name[*feature_number-5]);


while((c = fgetc(pf)) != EOF && c != '\n'){ //pass the first line in txt file
    fprintf(npf, "%c", c);
}
fprintf(npf, ",%s\n", feature_name[*feature_number-5]); //get the feature names which are not default

//get the values, add new feature value and printf to the new file
while(fscanf(pf, "%d,%c,%[^,],%[^,],%lf", &pID, &type, name, brand, &price)==5){
    for(int i=5; i<*feature_number; i++){
        if(i==(*feature_number)-1){
            fscanf(pf, ",%[^\n]", feature_value[i-5]);
        }
        else{
            fscanf(pf, ",%[^,]", feature_value[i-5]);
        }
    }
    fscanf(pf, "\n");

    fprintf(npf, "%d,%c,%s,%s,%.2lf", pID, type, name, brand, price);
    for(int i=5; i<*feature_number; i++){
        fprintf(npf, ",%s", feature_value[i-5]);
    }
    if(pID==*max_pID){
        fprintf(npf, ",%s", "None");
    }
    else{
        fprintf(npf, ",%s", "None\n");
    }
}
(*feature_number)++;
fclose(pf);
fclose(npf);
remove("products.txt");
rename("new_products.txt", "products.txt");

}


void add_new_product(int *feature_number,char feature_name[SIZE_FEATURE][LENGTH_FEATURE], char feature_value[SIZE_FEATURE][LENGTH_FEATURE],int *max_pID){

FILE *pf;
char type;
char name[9];
char brand[6];
double price;

pf = fopen("products.txt", "a+");
if(pf==NULL){
    printf("Files can not be opened.\n");
    return ;
}

(*max_pID)++; //increment the value of max_pID
//get the values of new product
printf("Enter Type: ");
scanf(" %c",&type);
printf("Enter Name: ");
scanf(" %[^\n]", name);
printf("Enter Brand: ");
scanf(" %[^\n]", brand);
printf("Enter Price: ");
scanf("%lf", &price);

//add the values
fprintf(pf, "%d,%c,%s,%s,%.2lf", *max_pID, type, name, brand, price);

//get the feature values of the new product and add to the new file
for(int i=5; i<*feature_number; i++){
    printf("Enter %s:", feature_name[i-5]); 
    scanf(" %[^\n]", feature_value[i-5]);
    fprintf(pf, ",%s", feature_value[i-5]);
}

fclose(pf);

}

void calculate_max_pID(int *max_pID){ //calculates maximum number of pID

FILE *pf;
FILE *npf;
int line_number=0;
char a;

pf = fopen("products.txt", "r");
if(pf==NULL){
    printf("Files can not be opened.\n");
    return ;
}


while((a=fgetc(pf))!=EOF){
	if(a=='\n'){
		line_number++;
	}
}
*max_pID=line_number-1;
fclose(pf);

}



void calculate_feature_number(int *feature_number, char feature_name[SIZE_FEATURE][LENGTH_FEATURE]){

//calculates the total number of features
FILE *pf;
FILE *npf;
char c;
char a;
char pID[4];
char type[5];
char name[9];
char brand[6];
char price[6];
int i=0;

pf = fopen("products.txt", "r");
if(pf==NULL){
    printf("Files can not be opened.\n");
    return ;
}

fscanf(pf, "%[^,],%[^,],%[^,],%[^,],%[^,\n]", pID, type, name, brand, price);

if((c=fgetc(pf))==','){
	while(fscanf(pf, "%[^,\n]", feature_name[i])==1){
		i++;
		a=fgetc(pf);
		if(a=='\n'){
			break;
		}
	}
	*feature_number=i+5;
}
else{
	*feature_number=5;
}

fclose(pf);

}



void delete_product(int *feature_number, char feature_value[SIZE_FEATURE][LENGTH_FEATURE],int *max_pID){

FILE *pf;
FILE *npf;
int pID;
char type;
char name[9];
char brand[6];
double price;
int number;
int flag=0;
char c;

pf = fopen("products.txt", "r");
npf= fopen("new_products.txt", "w+");
if(pf==NULL){
    printf("Files can not be opened.\n");
    return ;
}
if(npf==NULL){
    printf("Files can not be opened.\n");
    return ;   
}

printf("Enter the pID number of the product: ");
scanf("%d", &number);

while((c = fgetc(pf)) != EOF && c != '\n'){
    fprintf(npf, "%c", c);
}
fprintf(npf, "\n");


//get values from old txt file and add to new txt file until reaches the product to be deleted and do not add it
while(fscanf(pf, "%d,%c,%[^,],%[^,],%lf", &pID, &type, name, brand, &price)==5){
    if(pID==number){
        flag=1;
        (*max_pID)--;
        while((c = fgetc(pf)) != EOF && c != '\n'){
        }
        break;
    }
    for(int i=5; i<*feature_number; i++){
        if(i==(*feature_number)-1){
            fscanf(pf, ",%[^\n]", feature_value[i-5]);
        }
        else{
            fscanf(pf, ",%[^,]", feature_value[i-5]);
        }
    }
    fscanf(pf, "\n");

    fprintf(npf, "%d,%c,%s,%s,%.2lf", pID, type, name, brand, price);
    for(int i=5; i<*feature_number; i++){
        fprintf(npf, ",%s", feature_value[i-5]);
    }
    if(pID!=*max_pID){
        fprintf(npf, "\n");
    }
}

//add the products under the deleted product
while(fscanf(pf, "%d,%c,%[^,],%[^,],%lf", &pID, &type, name, brand, &price)==5){
    pID--;
    for(int i=5; i<*feature_number; i++){
        if(i==(*feature_number)-1){
            fscanf(pf, ",%[^\n]", feature_value[i-5]);
        }
        else{
            fscanf(pf, ",%[^,]", feature_value[i-5]);
        }
    }
    if(pID!=*max_pID){
        fscanf(pf, "\n");
    }
    
    fprintf(npf, "%d,%c,%s,%s,%.2lf", pID, type, name, brand, price);
    for(int i=5; i<*feature_number; i++){
        fprintf(npf, ",%s", feature_value[i-5]);
    }
    if(pID!=*max_pID){ //decrement the number of maximum pID
        fprintf(npf, "\n");
    }
}

if(flag==0){
    printf("There is no item with this pID.\n");
}

fclose(pf);
fclose(npf);
remove("products.txt");
rename("new_products.txt", "products.txt");

}


void update_product(int *feature_number,char feature_name[SIZE_FEATURE][LENGTH_FEATURE], char feature_value[SIZE_FEATURE][LENGTH_FEATURE],int *max_pID){

FILE *pf;
FILE *npf;
int pID;
char type;
char name[9];
char brand[6];
double price;
int number;
char feature[20];
int flag=0;
char c;

pf = fopen("products.txt", "r");
npf= fopen("new_products.txt", "w+");
if(pf==NULL){
    printf("Files can not be opened.\n");
    return ;
}
if(npf==NULL){
    printf("Files can not be opened.\n");
    return ;   
}

while((c = fgetc(pf)) != EOF && c != '\n'){
    fprintf(npf, "%c", c);
}
fprintf(npf, "\n");

printf("Enter the pID: ");
scanf("%d", &number);
printf("Enter name of the feature to be updated: ");
scanf(" %[^\n]", feature);

//until reaching the desired product scan and add to new txt file
while(fscanf(pf, "%d,%c,%[^,],%[^,],%lf", &pID, &type, name, brand, &price)==5){

    for(int i=5; i<*feature_number; i++){
    if(i==(*feature_number)-1){
        fscanf(pf, ",%[^\n]", feature_value[i-5]);
    }
    else{
        fscanf(pf, ",%[^,]", feature_value[i-5]);
    }
    }
    fscanf(pf, "\n");

    if(pID==number){
        flag=1;
        //get the new value
        if(compare(feature ,"type")==1 || compare(feature,"Type")==1){
            printf("Enter the value for the feature: ");
            scanf(" %c", &type);
        }
        else if(compare(feature, "name")==1 || compare(feature, "Name")==1){
            printf("Enter the value for the feature: ");
            scanf(" %[^\n]", name);
        }
        else if(compare(feature,"brand")==1 || compare(feature, "Brand")==1){
            printf("Enter the value for the feature: ");
            scanf(" %[^\n]", brand);
        }
        else if(compare(feature,"price")==1 || compare(feature, "Price")==1){
            printf("Enter the value for the feature: ");
            scanf("%lf", &price);
        }
        else if(*feature_number>5){
        	for(int i=5; i<*feature_number; i++){
        		if(compare(feature,feature_name[i-5])==1){
        			printf("Enter the value for the feature: ");
        			scanf(" %[^\n]", feature_value[i-5]);
        		}
        	}
        }
    }

    fprintf(npf, "%d,%c,%s,%s,%.2lf", pID, type, name, brand, price);
    for(int i=5; i<*feature_number; i++){
        fprintf(npf, ",%s", feature_value[i-5]);
    }
    if(pID!=*max_pID){
        fprintf(npf, "\n");
    }
}
if(flag==0){
    printf("There is no product with this pID.\n");
}

fclose(pf);
fclose(npf);
remove("products.txt");
rename("new_products.txt", "products.txt");

}

int compare(char feature[], char selected[]){ //compares two string

char *a ;
a=feature;
char *b;
b=selected;

while(*a!='\0'&&*b!='\0'){
	if(*a != *b){
		return 0;
	}
	a++;
	b++;
}

if(*a!='\0' || *b!='\0'){
    return 0;
}
return 1;
}


void add_stock(){

//add new stock entry to the end of the file
FILE *sf;
char c;
int sID=0;
int pID;
char branch[16];
int current_stock;

sf = fopen("stocks.txt", "a+");
if(sf==NULL){
    printf("Files can not be opened.\n");
    return ;
}

while((c=fgetc(sf))!=EOF){
    if(c=='\n'){
        sID++;
    }
}
sID++;
sID++;
printf("Enter pID: ");
scanf("%d", &pID);
printf("Enter Branch: ");
scanf(" %[^\n]", branch);
printf("Enter Current_stock: ");
scanf("%d", &current_stock);

fprintf(sf, "%d,%d,%s,%d", sID, pID, branch, current_stock);

fclose(sf);
}

void delete_stock(){

FILE *sf;
FILE *nsf;
char c;
int sID;
int number;
char line[200];
int flag=0;
int max_sID=0;

sf = fopen("stocks.txt", "r");
nsf= fopen("new_stocks.txt", "w+");
if(sf==NULL){
    printf("Files can not be opened.\n");
    return ;
}
if(nsf==NULL){
    printf("Files can not be opened.\n");
    return ;
}

while((c = fgetc(sf)) != EOF){
    if(c=='\n'){
        max_sID++; //calculate the number of maximum sID
    }
}
rewind(sf); //get back to the head of the file

while((c = fgetc(sf))!= '\n'){ //pass the first line
    fprintf(nsf, "%c", c);
}
fprintf(nsf, "\n");

printf("Enter the sID number of the stock: ");
scanf("%d", &number);

//add the stocks to new txt file until reach the product to be deleted
while(fscanf(sf, "%d,%[^\nEOF]", &sID, line)==2){
    fgetc(sf);
    if(sID==number){
        max_sID--; //decrease the number of maximum sID when reach to the selected stock
        flag=1;
        break;
    }
    fprintf(nsf, "%d,%s\n", sID, line);
}
//add the rest of the stocks to new txt file
while(fscanf(sf, "%d,%[^\nEOF]", &sID, line)==2){
    
    sID--;
    fprintf(nsf, "%d,%s", sID, line);
    if(sID!=max_sID){
        
        fprintf(nsf, "\n");
        fgetc(sf);
    }
}
if(flag==0){
    printf("There is no item with this sID.\n");
}

fclose(sf);
fclose(nsf);
remove("stocks.txt");
rename("new_stocks.txt", "stocks.txt");
}


void update_stock(){

FILE *sf;
FILE *nsf;
char c;
int max_sID=0;
int sID;
int pID;
int number;
char branch[16];
int current_stock;
char feature[20];
int flag=0;

sf = fopen("stocks.txt", "r");
nsf= fopen("new_stocks.txt", "w+");
if(sf==NULL){
    printf("Files can not be opened.\n");
    return ;
}
if(nsf==NULL){
    printf("Files can not be opened.\n");
    return ;
}

while((c = fgetc(sf)) != EOF){
    if(c=='\n'){
        max_sID++;
    }
}
rewind(sf);

while((c = fgetc(sf))!= '\n'){
    fprintf(nsf, "%c", c);
}
fprintf(nsf, "\n");

//get the sID and feature of the updated product
printf("Enter the sID: ");
scanf("%d", &number);
printf("Enter name of the feature to be updated: ");
scanf(" %[^\n]", feature);


while(fscanf(sf, "%d,%d,%[^,],%d", &sID, &pID, branch, &current_stock)==4){
    if(sID==number){//when reach the desired stock, get the new value and update the stock entry
        if(compare(feature, "branch")==1 || compare(feature, "Branch")==1){
            printf("Enter the value of the feature to be updated: ");
            scanf(" %[^\n]", branch);
            fprintf(nsf, "%d,%d,%s,%d", sID, pID, branch, current_stock);
            flag=1;
        }
        else if(compare(feature, "current_stock")==1 || compare(feature, "Current_stock")==1){
            printf("Enter the value of the feature to be updated: ");
            scanf("%d", &current_stock);
            fprintf(nsf, "%d,%d,%s,%d", sID, pID, branch, current_stock);
            flag=1;
        }
    }
    else{
        fprintf(nsf, "%d,%d,%s,%d", sID, pID, branch, current_stock);
    }
    if(sID!=max_sID){
        fprintf(nsf, "\n");
        fgetc(sf);
    }   
}

if(flag==0){ //when there is no change print this message
    printf("There is no product with this sID and feature.\n");
}

fclose(sf);
fclose(nsf);
remove("stocks.txt");
rename("new_stocks.txt", "stocks.txt");

}


void brand_stock_control(int *feature_number, char feature_value[SIZE_FEATURE][LENGTH_FEATURE], double brand_stock_control_array[200][3], int *max){

int flag=0;
flag=brand_stock_match(feature_number, feature_value, brand_stock_control_array, max); //collect pID, price and currrent_stocks in a 2D array and return 1 if brand is found

if(flag==0){
    printf("There is no product with this brand.\n");
}
else if(flag==1){
    match_printf(max, brand_stock_control_array); //print the table of pID, price and current_stocks after match done
}

}

void match_printf(int *max, double brand_stock_control_array[200][3]){  //print the table of pID, price and current_stocks after match done

int pid1=0;
int cs=0;
    printf("pID  Price  Current_stock\n");
    for(int a=0; a<=*max; a++){
        pid1= round(brand_stock_control_array[a][0]);
        cs= round(brand_stock_control_array[a][2]);
        printf("%-4d %-6.2lf %-14d\n", pid1, brand_stock_control_array[a][1], cs);
    }
}

int brand_stock_match(int *feature_number, char feature_value[SIZE_FEATURE][LENGTH_FEATURE], double brand_stock_control_array[200][3], int *max){

FILE *pf;
FILE *sf;
double pID;
int pid1;
double pID2;
int pid2;
char type;
char name[9];
char brand[6];
double price;
double current_stock;
char selectedBrand[10];
int flag=0;
char c;
char line[200];
int i=0;
char pass[16];

pf = fopen("products.txt", "r");
sf= fopen("stocks.txt", "r");
if(pf==NULL){
    printf("Files can not be opened.\n");
    return 0;
}
if(sf==NULL){
    printf("Files can not be opened.\n");
    return 0;   
}
//get the selected brand
printf("Enter brand: ");
scanf(" %[^\n]", selectedBrand);

for(int i=0; i<200; i++){
    for(int j=0; j<3; j++){
        brand_stock_control_array[i][j]=0;
    }
}

while((c = fgetc(pf)) != EOF && c != '\n'){// pass the first line of txt file
}

//find the products that match with brand, pass the pID, price and current_stock to a 2D array
while(fscanf(pf, "%lf,%c,%[^,],%[^,],%lf", &pID, &type, name, brand, &price)==5){
    
    fscanf(pf, "%[^\n]\n", line);
    rewind(sf);
    if(compare(selectedBrand, brand)==1){
        flag=1;
        brand_stock_control_array[i][0]=pID;
        brand_stock_control_array[i][1]= price;
        while((c = fgetc(sf)) != '\n'){
        }
        while(fscanf(sf, "%[^,],%lf,%[^,],%lf", pass, &pID2, pass, &current_stock)==4){
            
            pid1=round(pID);
            pid2=round(pID2);
            if(pid1==pid2){
                brand_stock_control_array[i][0]=pID;
                brand_stock_control_array[i][1]= price;
                brand_stock_control_array[i][2]= current_stock;
                if(i>*max){
                    *max=i;
                }
                i++;
            }
            fgetc(sf);
        }
    }
}

fclose(pf);
fclose(sf);

return flag;
}

void stock_report(double brand_stock_control_array[200][3], int *max){

FILE *file;
int max_stock;
int min_stock;
int median;
int pid;
int cs;
int temp;
int array[30]={0};

file= fopen("report.txt", "w+");
if(file==NULL){
    printf("Files can not be opened.\n");
    return ;
}

//get the integer values of current_stocks in a array
for(int i=0; i<=*max; i++){
    temp=round(brand_stock_control_array[i][2]);
    array[i]=temp;
}
//sort the array
for(int i=0; i<*max; i++){
    for(int j=0; j<((*max)-1-i); i++){
        if(array[j]>array[j+1]){
            temp=array[j+1];
            array[j+1]=array[j];
            array[j]=temp;
        }
    }
}

max_stock= array[*max];
min_stock= array[0];

if((*max)%2!=0){
    median= array[((*max)-1)/2] + array[((*max)+1)/2];
    median=median/2;
}
else{
    median=array[(*max)/2];
}

//print the stock report
fprintf(file, "pID Min_Stock Max_Stock Median Stock\n");
for(int i=0; i<=*max; i++){
    pid=round(brand_stock_control_array[i][0]);
    cs= round(brand_stock_control_array[i][2]);
    fprintf(file, "%-3d %-9d %-9d %-12d\n", pid, max_stock, min_stock, median); 
}

fclose(file);

}

void list_products(){

FILE *file;
char c;

file= fopen("products.txt", "r");
if(file==NULL){
    printf("Files can not be opened.\n");
    return ;
}


while((c = fgetc(file))!= EOF){ //print all the products.
    printf("%c", c);
}

printf("\n");




}
