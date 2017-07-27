//Max Zhao mlzhao 1466223

#include <stdio.h> // includes c stdio
#include <stdlib.h> // includes c standard library


class Classroom{ // begin declaration of Classroom class
	private:
		unsigned short openSeats; // private member variable tracking # of open seats

	public: 
		unsigned short* seats; 
		Classroom(unsigned short totalAvail)
		{
			seats = (unsigned short*)calloc(totalAvail, sizeof(unsigned short)); 
			// allocates seats with 'totalAvail' number of spaces w/ 0's (open seats)
			// 1 = taken, 0 = free
			openSeats = totalAvail;
		}
		~Classroom(); // destructor
		void reserveSeat(unsigned short student); // accessor function to reserve seat
		void availSeat(unsigned short student); // accessor function to make seat available
		bool checkSeat(unsigned short student); // accessor function to check if seat is available
		unsigned short getAvailSeats() const; // accessor function to get total number of open seats
};