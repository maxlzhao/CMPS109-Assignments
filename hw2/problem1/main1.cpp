//Max Zhao mlzhao 1466223

#include "Problem1.h" // includes Problem1's header file

int main()
{
	Classroom myRoom(256); // sets total number of seats

	myRoom.reserveSeat(0);
	myRoom.reserveSeat(3); // reserves a seat
	myRoom.reserveSeat(6);
	myRoom.reserveSeat(37);
	myRoom.reserveSeat(52);
	myRoom.reserveSeat(74);
	myRoom.reserveSeat(117);
	myRoom.reserveSeat(255);
	myRoom.reserveSeat(3); // error catching if seat already taken

	printf("\n");
	myRoom.availSeat(52); // makes seat available
	myRoom.availSeat(117); 
	myRoom.availSeat(2); // error catching if seat is already available

	printf("\n");
	for (unsigned short i = 0; i < 256; i++){ // iterates through seats and prints out to test
		printf("%d " ,myRoom.seats[i]);
	}
	printf("\n");

	unsigned short res = myRoom.getAvailSeats(); // gets number of open seats
	printf("there are %d seats available\n", res);

	printf("%d\n", myRoom.checkSeat(3)); // checks if seat is available, 1 if taken 0 if free
	printf("%d\n", myRoom.checkSeat(20));
	return 0;
}