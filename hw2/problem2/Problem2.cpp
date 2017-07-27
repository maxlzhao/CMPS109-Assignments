// Max Zhao mlzhao 1466223

#include "Problem2.h"

Inventory::~Inventory() // destructor
{
	delete[] products;
}

void Inventory::addProduct(int productID, int number){ // acessor function to add stock to a product
	if(products[productID] == 0){ // if stock was initially zero, increase the counter for total products available
		totalProducts++;
	}

	products[productID] += number; // adds stock to respective product ID
	if(products[productID] > 256){ // if user tries to add stock more than 256, sets to max capacity of 256
		//printf("max product stock is 256\n");
		printf("Maximum capacity = 256. Added 256 stock to product %d\n", productID);
		products[productID] = 256;
	}else{
		printf("Added %d stock to product %d\n", number, productID);
	}
}

void Inventory::removeProduct(int productID, int number){ // accessor function to remove stock from product
	products[productID] -= number; // removes stock from respective product ID
	if(products[productID] < 0){ // if stock goes to less than zero, set total stock to minimum capacity of 0
		printf("Minimum capacity = 0. Set stock of product %d to 0.\n", productID);
 		products[productID] = 0;
 		totalProducts--; // lowers total number of products available if out of stock
	}else{
		printf("Removed %d stock from product %d\n", number, productID);
	}
}

bool Inventory::productExists(int productID){ // accessor function to check if a product has stock
	if(products[productID] > 0){
		printf("Product %d exists\n", productID);
		return true;
	}else{
		printf("Product %d does not exist\n", productID);
		return false;
	}
}

int Inventory::getStock(int productID){ // returns stock for respective product
	printf("Product %d has %d stock available\n", productID, products[productID]);
	return products[productID];
}

int Inventory::getProducts() const{ // returns total number of products available
	printf("There are %d products available\n", totalProducts);
	return totalProducts;
}
