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

void printCustomer(struct Customer c)
{
	printf("CUSTOMER NAME: %s \nCUSTOMER BUDGET: %.2f\n", c.name, c.budget);
	printf("-------------\n");
	for(int i = 0; i < c.index; i++)
	{
		printProduct(c.shoppingList[i].product);
		printf("%s ORDERS %d OF ABOVE PRODUCT\n", c.name, c.shoppingList[i].quantity);
		double cost = c.shoppingList[i].quantity * c.shoppingList[i].product.price; 
		printf("The cost to %s will be €%.2f\n", c.name, cost);
	}
}

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

    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);
        // printf("%s IS A LINE", line);
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
		// printf("NAME OF PRODUCT %s PRICE %.2f QUANTITY %d\n", name, price, quantity);
    }
	
	return shop;
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
	scanf("%d", &choice);
    if(choice == 1)
	{
		printShop(s);
	}
	else if(choice == 2)
	{
		exit(0);
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