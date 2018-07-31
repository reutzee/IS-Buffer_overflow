
#include "stdafx.h"


// Task3.cpp : Defines the entry point for the console application.
//



#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include<stdio.h>

namespace {
	class CreditCard {
		friend std::ostream& operator<<(std::ostream&, const CreditCard&);
	private:
		char number[17];
		char expiration[5];
		int pin;
		int creditLimit;
	public:
		CreditCard(char* number, char* expiration, int pin, int creditLimit)
			: pin(pin), creditLimit(creditLimit) {
			std::strncpy(this->number, number, sizeof(this->number));
			std::strncpy(this->expiration, expiration, sizeof(this->expiration));
			this->number[sizeof(this->number) - 1] = '\0';
			this->expiration[sizeof(this->expiration) - 1] = '\0';
		}
	};
	// For debugging purposes only -- do not use in malicious()
	std::ostream& operator<<(std::ostream& out, const CreditCard &cc) {
		return out << "[DEBUG] " << cc.number << ' ' << cc.expiration
			<< ' ' << cc.pin << ' ' << cc.creditLimit;
	}
	void malicious(const CreditCard &cc) {
		// &obj -> the starting addr of obj
		// (int *)(&obj)             typecast the starting address of obj to int *
		// *((int *)(&obj))          the value at the above location interpreted as an integer type
		// *((int *)(&obj)) = 12345  store something in it

		// Print the 'private' credit card number
		printf("the 'private' credit card number is            : %s \n", (char*)&cc);
		// Change the credit limit to 100,000
		*(int *)(((char*)(&cc) + 22) + 2 + 4) = 100000;
		// Change the PIN to 1234
		*(int *)(((char*)(&cc) + 22) + 2) = 1234;

		printf("------------- Changing details ... -------------\n");

		// Print all the updated values
		printf("THE UPDATED VALUES\n");
		printf("the 'private' credit card updated number is     : %s \n", (char*)&cc);
		printf("the 'private' credit card updated expiration is : %s \n", (char*)&cc + 17);
		printf("the 'private' credit card updated PIN is        : %d \n", *(int *)(((char*)(&cc) + 17 + 5) + 2));
		printf("the 'private' credit card updated limit  is     : %d \n", *(int *)(((char*)(&cc) + 22) + 2 + 4));

	}
}
extern "C"
int task3() {
	CreditCard cc("3717422122321221", "0805", 4321, 1000);
	std::cout << "Before: " << cc << std::endl;
	malicious(cc);
	std::cout << "After: " << cc << std::endl;
	return 0;
}
int main() {
	return task3();
}
