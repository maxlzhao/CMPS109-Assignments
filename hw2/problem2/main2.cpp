// Max zhao mlzhao 1466223

#include "Problem2.h"

int main()
{
	Inventory test(256); // sets total number of seats

	test.addProduct(157, 13); // adds stock to product
	test.addProduct(3, 300); // checks for overflow on max capacity
	test.addProduct(2, 150);
	test.addProduct(1, 57);
	test.addProduct(13, 152);
	test.addProduct(57, 35);


	printf("\n");
	test.removeProduct(13, 15); // removes stock from products
	test.removeProduct(57, 2);
	test.removeProduct(3, 150);
	test.removeProduct(2, 1000); // checks for overflow on min capacity

	printf("\n");
	test.productExists(0); // checks if products exist
	test.productExists(3);
	test.productExists(157);

	printf("\n");
	test.getStock(3); // gets stock on selected product IDs
	test.getStock(1);
	test.getStock(15);
	test.getStock(57);

	printf("\n");
	test.getProducts();

	printf("\n");
	for (int i = 0; i < 255; i++){ // iterates through seats
		printf("%d " ,test.products[i]);
	}
	printf("\n");

	return 0;
}