//Max Zhao mlzhao 1466223

#include <stdio.h> // includes c stdio
#include <stdlib.h> // includes c standard library

class Inventory{ // begin declaration of inventory class
	private:
		//int productID; 
		int totalProducts; // private member variable tracking total products available

	public:
		int *products;
		Inventory(int totalAvail)
		{
			products = (int*)calloc(totalAvail, sizeof(int));
			// allocates products with 'totalAvail' number of products, w/ zeros indiciating that
			// they have zero stock
			totalProducts = 0;
		}
		~Inventory(); // destructor

		void addProduct(int productID, int number); // accessor function to add stock
		void removeProduct(int productID, int number); // accessor function to remove stock
		bool productExists(int productID); // accessor function to check if product exists
		int getStock(int productID); // accessor function to check stock of product
		int getProducts() const; // accessor function to get total # of products available

};