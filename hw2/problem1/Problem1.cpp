//Max Zhao mlzhao 1466223

#include "Problem1.h" //includes header file for Problem1

Classroom::~Classroom() // destructor
{
	delete[] seats;
}

void Classroom::reserveSeat(unsigned short student) // accessor function to reserve a seat
{
	if(seats[student] == 1){
		printf("seat %d already taken\n", student);
		return;
	}
	seats[student] = 1; // sets respective student's seat to 1/taken
	openSeats--; // lowers total number of open seats
	printf("reserved seat %d\n", student);
}

void Classroom::availSeat(unsigned short student)
{
	if(seats[student] == 0){
		printf("seat %d already free\n", student);
		return;
	}
	seats[student] = 0; // sets respective student's seat to 0/free
	openSeats++; // raises total number of open seats
	printf("made seat %d available\n", student);
}

unsigned short Classroom::getAvailSeats() const{ // getter function to retrieve # of open seats
	return openSeats;
}

bool Classroom::checkSeat(unsigned short student) // checks individual seats if they're open
{
	if(seats[student] == 1){ // if chosen student is 1/taken, returns false
		printf("seat %d is taken\n", student);
		return false;
	}else{
		printf("seat %d is open\n", student);
		return true;
	}
}

