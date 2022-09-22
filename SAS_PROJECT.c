#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
//#include <stdio_ext.h>
#include <stdbool.h>


struct product {
	char name[20];
	char code[30];
	int quantity;
	float price;
	float priceTVA;
};


// global variales
int i;
float total;
float totalOfProducts;
float average;
float max=0;
float min=0;
//how many products
int nbr=4;
//where we stock the products 
struct product prd[200] = {
	{"A_name", "5566", 10, 50, 55},
	{"B_name", "1122", 20, 100, 115},
	{"C_name", "6688", 30, 150, 165},
	{"D_name", "7788", 40, 200, 230},
};


void menu(){
    int Choice;
    int decision;
    
	system("cls");
	do{
	printf("------------------     (Pharmacy Management)     ------------------\n");
    printf("\n ======================== THE MAIN MENU ==========================\n\n");
    printf("\t 1  : ADD NEW PRODUCT(s)\n");
    printf("\t 2  : LIST ALL THE PRODUCTS (NAME, PRICE, PRICE + TVA)\n");
    printf("\t 3  : BUY A NEW PRODUCT\n"); 
    printf("\t 4  : SEARCH FOR A PRODUCT \n");
    printf("\t 5  : CHECK THE STATUS OF THE STOCK \n");
    printf("\t 6  : ADD TO THE STOCK\n");
    printf("\t 7  : DELETE A PRODUCT\n");
    printf("\t 8  : SALES STATISTICS\n");
    printf("\t 9  : EXIT THE PROGRAM\n");
    printf("\n =================================================================\n\n");
    printf("\n Enter your choice: ");
    scanf("%d", &Choice);
    system("cls");
    
   	switch(Choice){
   		case 1 : addNewProduct();
        	     break;
        case 2 : listProductsByNameAndByPrice();
                 break;
        case 3 : buyProduct();
        		 break;
        case 4 : searchForAProduct();
        		 break;
        case 5 : statusOfTheStock();
				 break;
        case 6 : supplyTheStock();
        		break;
        case 7 : deleteProduct();
        		break;
        case 8 : salesStatistics();
        		break;	 
		case 9 : break;		 
		default:
    	printf("Wrong choice\n");
//    	__fpurge(stdin);
    }
	}while(Choice!=10);

}


void addNewProduct(){ 

	int numberOfProducts;
	
    printf("\n Enter the number of the products that you want to add: ");
    scanf("%d", &numberOfProducts);
    
    for(i = 0; i < numberOfProducts; i++){
    	printf("\n  -----------------------------------------\n");
    	printf(" | Fill the inforamtion of product (%d)     |\n",i+1);

    	printf("\n | Enter the name of the product: ");
    	scanf("%s", prd[nbr].name);
    	
    	printf(" | Enter the code of the product:  ");
    	scanf("%s", prd[nbr].code);
    
    	printf(" | Enter the quantity of the product: ");
    	scanf("%d", &(prd[nbr].quantity));
    
    	printf(" | Enter the price of the product: ");
    	scanf("%f", &(prd[nbr].price));
    
		prd[nbr].priceTVA = prd[nbr].price  + (prd[nbr].price * 0.15);
		printf(" | (The price plus TVA is: %.2f)     |\n", prd[nbr].priceTVA);
		
		printf("\n |  (PRODUCT %d WAS ADDED SUCCESSFULLY!)   |", i+1);
		printf("\n  ---------------------------------------\n\n");

    	nbr++;
	}
}


void displayTheProductsInTheStock(){
	int i;
	
	for(i = 0; i<nbr; i++){
	
//	printf("--------------------------------------------------------------------------------------------");
//	printf("|      Name      |      Code      |      Quantity      |      Price      |      PriceTVA      ");
//	printf("--------------------------------------------------------------------------------------------");	

	
	printf("------------------------------------------------------------------------------------------\n");
    printf("|Name: %s |Code: %s |Quantity: %d |Price: %.2f DH |Price TVA: %.2f DH TTC |\n", prd[i].name, prd[i].code, prd[i].quantity, prd[i].price, prd[i].priceTVA );
    printf("------------------------------------------------------------------------------------------\n");
	}
	

}

void listProductsByNameAndByPrice(){
	
	int decision;
	
	printf("-------------------- LIST PRODUCTS: --------------------------\n");
	printf(" 1  : In ascending alphabetical order. \n");
    printf(" 2  : In descending order of price. \n");
    printf("\nEnter your choice: ");
    scanf("%d", &decision);
    
    if(decision == 1){
        listByNames();
    }else if (decision == 2){
        listByPrice();
    }
}

void  listByNames(){
	// sort bubble
    struct product temprod;

    int i,j;
    
    for(i=0;i<nbr;i++)
	{
        for(j=i+1;j<nbr;j++)
		{
       		if(strcmp(prd[i].name,prd[j].name)>0)
			{
              	temprod=prd[i];
              	prd[i]=prd[j];
              	prd[j]=temprod;
            }
    	}
	}
	
    displayTheProductsInTheStock();

}

 
void listByPrice(){
	
    struct product temprod;

	int i, j;
	for(i = 0; i < nbr; i++){
		for(j = i+1; j < nbr; j++){
			if(prd[i].price < prd[j].price){
				temprod = prd[j];
				prd[j] = prd[i];
				prd[i] = temprod;
			}
		}
	}
	displayTheProductsInTheStock();
	
}



void buyProduct() 
{
	displayTheProductsInTheStock();
//   system("cls");
    printf("\n========== You are about to buy a new product ==============\n\n");
     
    char userCode[20];
    int userQuantity = 0;
    int cmp=0; // counter
    printf("Enter the code of the product: ");
    scanf("%s", userCode); 
    
    for (i = 0; i < nbr; i++)
    {
        if ( strcmp(prd[i].code, userCode) == 0 ){
               
                printf("The product you are about to buy is %s and the quantity is: %d\n", prd[i].name,prd[i].quantity);
                 enterAnotherQuantity:
                printf("Give the quantity you want to buy: ");
                scanf("%d", &userQuantity);
                if ( userQuantity <= prd[i].quantity)
                {
                    
                    prd[i].quantity -= userQuantity;
                    
                    //total :total price of all the products that were bought
                    total += userQuantity*prd[i].priceTVA;
                 // totalOfProducts:ch7al man 7aba ba3ti falmajmo3
                    totalOfProducts += userQuantity;
                    
                    // 7esab max (statistics)
                    if(prd[i].priceTVA > max){
                    	max = prd[i].priceTVA;
					}
					if(prd[i].priceTVA < min || min == 0){
                    	min = prd[i].priceTVA;
					}
                }       
                else {
                	printf("Quantity not avalaible\nPlease enter a reasonable quantity\n");
                	goto enterAnotherQuantity;
				}
                cmp++;
        }
    }
        if (cmp==0){
		printf("The code you entered doesn't match any product\n");
		}
        
        
    
}


void searchForAProduct(){
	int decision;
	printf("-------------------  SEARCH FOR A PRODUCT  -------------------\n");
    printf(" 1  : Search by Code: \n");
    printf(" 2  : Search by Quantity: \n");
    printf("\nEnter your choice: ");
    scanf("%d", &decision);
    if(decision == 1)
	{
	printf("\n------------- THE RESULTS OF THE SEARCH ------------- \n\n");
    SearchByCode();                
    }
    else if(decision == 2)
	{
    printf("\n------------- THE RESULTS OF THE SEARCH ------------- \n\n");
        searchByQuantity();      
    }
}

void SearchByCode()
{
    char x_code[15];
    printf("Enter the code of the product you want to search for:\n");
    scanf("%s",x_code);
    for(i=0;i<nbr;i++)
    {
        if (strcmp(prd[i].code,x_code)==0)
            {
                system("cls");
                 printf("exist\n");
                printf(" Code : %s \tName: %s\t Quantity : %d Price : \t %.2f Dh  PriceTVA : %.2f Dh\n",prd[i].code,prd[i].name,prd[i].quantity,prd[i].price,(prd[i].price+(prd[i].price*0.15)));
                return;
            }
        }
        printf("This product doesn't exist'\n");
}

void searchByQuantity()
{
    int xQuantity;
    int find=0;

    printf("Enter the quantity :\t");
    scanf("%d",&xQuantity);
    for(i=0;i<nbr;i++)
    {
        if (prd[i].quantity == xQuantity)
        {
            printf("Exist\n");
            printf(" Code : %s \tName: %s\t Quantity : %d Price : \t %.2f Dh  PriceTVA : %.2f Dh\n",prd[i].code,prd[i].name,prd[i].quantity,prd[i].price,(prd[i].price+(prd[i].price*0.15)));
            find++;
            }
        }
        if(find==0)
          printf("Quantity doesn't exist'\n");
}

void statusOfTheStock()
{
	printf("The products available on the stock: \n");
    for(i=0;i<nbr;i++)
    {
		if(prd[i].quantity<3)
        printf(" Code : %s \tName: %s\t Quantity : %d Price : \t %.2f Dh  PriceTVA : %.2f Dh\n",prd[i].code,prd[i].name,prd[i].quantity,prd[i].price,(prd[i].price+(prd[i].price*0.15)));
    }
}

void supplyTheStock()
    {
        char userCode[15];
        int deletedQuantity;
        
        printf("--------------- DELET A PRODUCT ---------------\n");
        printf("Enter the code of the product :\t");
        scanf("%s",userCode);
        
        for(i=0;i<nbr;i++)
        {
            if (strcmp(prd[i].code, userCode)==0)
            {
                 printf("This product does exist.\n");
                 printf("Enter the quantity you want to delete from this produt: \t");
                 scanf("%d",&deleteQuantity);
//                 if(x_quantite_add <= 0)
                 prd[i].quantity += userCode;
                return;
            }
        }
          printf("se produit n'existe pas\n");
}

void deleteProduct()
{
    system("cls");
    char tmpCode[20];
    int tmpindex=-1;
    printf("\nEnter the product code  \n");
    scanf("%s", tmpCode);

    for (i = 0; i < nbr; i++)
        {
                  if ( strcmp(prd[i].code, tmpCode) == 0 )
                    {    
                        tmpindex=i;
                        break ;                        
                       }
        }

    if(tmpindex==-1)
    {
        printf("se produit n'existe pas\n");
    }
    
    else
    {
          for(i =tmpindex;i<nbr;i++)
            {
                
                prd[i]=prd[i+1];
            }
            nbr--;
    }
    
}

void salesStatistics(){
	int decision;
	
	printf("\n---------------- SALES STATISTICS ---------------- \n\n");
       			 printf("================== Choose which statistics do you want to Display: ============= \n");
       			 printf("1: Display the total price of the products sold in the current day\n");
       			 printf("2: Display the minimum price of the products sold in the current day\n");
       			 printf("3: Display the max price of the products sold in the current day\n");
       			 printf("4: Display the minumum price of the products sold in the current day\n");
       			 printf("\t\tWhat statistics do you want to display. \n");
                 printf("\nEnter your choice: ");
                 scanf("%d", &decision);
                 
                 switch(decision){
                 	case 1 : totalPrice();
                 		break;
                 	case 2 : averagePrice();
                 		break;
                 	case 3 : maxPrice();
                 		break;
                 	case 4 : minimumPrice();
                 		break;
                 	default:
    					printf("ERROR 404\n");
				 }
}

void totalPrice(){
	
    printf("The total price of the products sold in a day : %.2f\n", total);
}

void averagePrice(){
	
	average = total / totalOfProducts;
    
    printf("The average price of the products sold in a day is %.2f.\n", average);
}



void maxPrice(){
    printf("The maximum price is: %.4f DH\n", max);
}


void minimumPrice()
{
    printf("The minimun price is: %.4f DH \n", min);
}

int main() {
 	
	menu();

	return 0;
}
