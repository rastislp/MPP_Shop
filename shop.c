// MPP - Shop application in C-Language
//Rastislav Petras G00252861


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Product 
{
	char* name;
	double price;
};

struct ProductStock 
{
	struct Product product;
	int quantity;
};

struct Shop 
{
	double cash;
	struct ProductStock stock[20];
	int index;
};

struct Customer 
{
	char* name;
	double budget;
	struct ProductStock shoppingList[10];
	int index;
};

void printProduct(struct Product p)
// Print all shop Inventory
{
	printf("| %-20.20s   €%.2f |\n", p.name, p.price);
};

void displayCustomer(struct Customer c)
{
   printf("--------------------------------\n");
   printf("| Name of customer: %s      |\n",  c.name);
   printf("| %s's budget: %.2f        |\n", c.name,  c.budget);
   printf("--------------------------------\n");
   printf("| Product             |  Q-ty  |\n");
   for(int i =0; i<c.index; i++)
   {
        printf("| %-20.20s|   %.2d   |\n", c.shoppingList[i].product.name, c.shoppingList[i].quantity);
   };
   printf("--------------------------------\n");
};

void printInvoice(struct Customer c)
{
   double SubTotal = 0.0;
   printf("--------------------------------\n");
   printf("| Name of customer: %s      |\n",  c.name);
   printf("| %s's budget: %.2f        |\n", c.name,  c.budget);
   printf("---------------------------------------------------\n");
   printf("| Product             |  Q-ty  |  Price |  Total  |\n");
   for(int i =0; i<c.index; i++){
      double total = c.shoppingList[i].quantity * c.shoppingList[i].product.price;
      printf("| %-20.20s|   %.2d   | %5.2f  | %5.2f   |\n", c.shoppingList[i].product.name, c.shoppingList[i].quantity,c.shoppingList[i].product.price,total);
      SubTotal += total;
   };
   printf("|                                                 |\n");
   printf("| Subtotal :                                %.2f |\n", SubTotal);
   printf("---------------------------------------------------\n");
};



struct Shop createAndStockShop()
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("stock.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
	
	getline(&line, &len, fp);
    double cashInShop = atof(line);
	struct Shop shop = { cashInShop };

    while ((read = getline(&line, &len, fp)) != -1) 
	{
		char *n = strtok(line, ",");
		char *p = strtok(NULL, ",");
		char *q = strtok(NULL, ",");
		int quantity = atoi(q);
		double price = atof(p);
		char *name = malloc(sizeof(char) * 50);
		strcpy(name, n);
		struct Product product = { name, price };
		struct ProductStock stockItem = { product, quantity };
		shop.stock[shop.index++] = stockItem;
    }
	
	return shop;
}
struct Customer selectCustomer (struct Shop s, char* csvFile)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(csvFile, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
	
	getline(&line, &len, fp);
	char* cn = strtok(line, ",");
    char* cb = strtok(NULL, ",");
    char* name = malloc(sizeof(char) * 50);
    strcpy(name,cn);
    double budget = atof(cb);
	struct Customer customer = { name,budget };

    while ((read = getline(&line, &len, fp)) != -1)
	{
		char *pn = strtok(line, ",");
		char *qn = strtok(NULL, ",");
		int quantity = atoi(qn);
		char *prodName = malloc(sizeof(char) * 50);
		strcpy(prodName, pn);
		struct Product product = { prodName, quantity };
		struct ProductStock listItem = { product, quantity };
		customer.shoppingList[customer.index++] = listItem;
    }
	
	return customer;
}

void printShop(struct Shop s)
{
	printf("--------------------------------\n");
	printf("|   Shop has € %.2f in cash  |\n",  s.cash);
	printf("--------------------------------\n");
	for (int i = 0; i < s.index; i++)
	{
		printProduct(s.stock[i].product);
		printf("| Stock quantity           %.3d | \n", s.stock[i].quantity);
		printf("--------------------------------\n");
	}
}


void menu(struct Shop s)
{
	int choice = 0;
	char customerFile;
	char process;
	
	printf("\n\n");
	printf("------------------------------------------------------\n");
	printf("|             Welcome in Shop application            |\n");
    printf("------------------------------------------------------\n");
	printf("\n");
    printf("Choose one from below:\n");
    printf("\n");
    printf("1 Display shop inventory\n");
    printf("\n");
    printf("2 Display customer shopping list\n");
    printf("\n");
    printf("3 Go to checkout\n");
    printf("\n");
    printf("4 Exit \n");
	printf("\n\nType your choice here >>> ");
	scanf("%d", &choice);
    if(choice == 1)
	{
		printShop(s);
		menu(s);
		
	}
	else if(choice == 2)
	{
		printf("\n\nFor displaying customer list please type customer file name in following format:	customer1.csv , customer2.csv ...\n");
		printf("File name >>> ");
		scanf("%s", &customerFile);
		struct Customer newCustomer = selectCustomer(s, &customerFile);
		displayCustomer(newCustomer); 
		printf("\nWhould you like to proceed to checkout? >>> ");
		scanf("%s", &process);
		if(process == 'y')
		{
			printf("Please confirm your selection by typing customer file once again:\n >>> ");
			scanf("%s", &customerFile);
			struct Customer newCustomer = selectCustomer(s, &customerFile);
			printInvoice(newCustomer);
			menu(s);
		}
		if(process == 'n')
		{	  
		    menu(s);
		}
		else
	    {
			exit(0); 
		}	
	}		
	else if(choice == 3)
	{
		exit(0);
	}		
	else if(choice == 4)
	{
		exit(0);
	}		
	
		
}

int main(void) 
{   // Create a shop stock
	struct Shop shop = createAndStockShop();
	
	// Display application menu
	menu(shop);
	
    return 0;
}