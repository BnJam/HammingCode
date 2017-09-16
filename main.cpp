/**
 * Title: HammingCode.cpp
 * Author: Benjamin Smith
 * Date: September 15th 2017
 *
 * Purpose: 
 * Program takes user input of 8 bit string and utilizes the
 * Hamming Code procedure to check for one or two bit errors. 
 * If one bit error occurred then make correction. If two bit
 * error occurs, return detection.
 *
 * main:
 * See purpose
 * 
 */

#include <iostream>
#include <string>
#include <math.h>
#include <assert.h>

/**
 * [main description]
 * 
 * @return [description]
 */
int main() {
	
	// Store bit string
	std::string input; 
	int ham[7];

	// Get input from user
	std::cout << "Enter 8 bit string:" << std::endl;
	std::cin >> input;
	
	// Convert user input from string to int array 
	input = input.c_str();
	for(int i=0; i<8; i++) {
		ham[i] = (int)input[i] - '0';
	}

	//std::cout << ham[0] << std::endl; // Debug print statement

	/**
	 * Program conceptual layout
	 * 
	 * | P1 | P2 | D1 | P3 | D2 | D3 | D4 | P4 |
	 * | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  |
	 *
	 * 0 0 0 0 | 0   | 
	 * 0 0 0 1 | P1  | 1
	 * 0 0 1 0 | P2  | 2
	 * 0 0 1 1 | D1  | 3
	 * 0 1 0 0 | P3  | 4
	 * 0 1 0 1 | D2  | 5
	 * 0 1 1 0 | D3  | 6
	 * 0 1 1 1 | D4  | 7
	 * 1 0 0 0 | P4  | 8
	 */

	// Set parity bits
	int p1, p2, p3, p4;
	p1 = (ham[3-1] ^ ham[5-1] ^ ham[7-1]);
	p2 = (ham[3-1] ^ ham[6-1] ^ ham[7-1]);
	p3 = (ham[5-1] ^ ham[6-1] ^ ham[7-1]);
	p4 = (ham[1-1] ^ ham[2-1] ^ ham[3-1] ^ ham[4-1] ^ ham[5-1] ^ ham[6-1] ^ ham[7-1]);

	// Check if parity bits are the same in the given hamming code
	// Return which bits are in error
	if(p1 != ham[1-1] && p2 == ham[2-1] && p3 == ham[4-1]) {
		std::cout << "P1 is in error" << std::endl;
	} else if(p1 == ham[1-1] && p2 != ham[2-1] && p3 != ham[4-1]) {
		std::cout << "P2 is in error" << std::endl;
	} else if(p1 == ham[1-1] && p2 == ham[2-1] && p3 != ham[4-1]) {
		std::cout << "P3 is in error" << std::endl;
	} else if(p1 != ham[1-1] && p2 != ham[2-1]) {
		std::cout << "d1 is in error" << std::endl; 
	} else if(p1 != ham[1-1] && p3 != ham[4-1]) {
		std::cout << "d2 is in error" << std::endl;
	} else if(p2 != ham[2-1] && p3 != ham[4-1]) {
		std::cout << "d3 is in error" << std::endl;
	} else if(p1 != ham[1-1] && p2 != ham[2-1] && p3 != ham[4-1]) {
		std::cout << "d4 is in error" << std::endl;
	}

	// Set check bits
	int c1, c2, c3, c4;
	c1 = (ham[1-1] ^ ham[3-1] ^ ham[5-1] ^ ham[7-1]);
	c2 = (ham[2-1] ^ ham[3-1] ^ ham[6-1] ^ ham[7-1]);
	c3 = (ham[4-1] ^ ham[5-1] ^ ham[6-1] ^ ham[7-1]);
	c4 = (ham[1-1] ^ ham[2-1] ^ ham[3-1] ^ ham[4-1] ^ ham[5-1] ^ ham[6-1] ^ ham[7-1] ^ ham[8-1]);


	// Print 4th check bit status
	std::cout << "c4 is " << std::to_string(c4) << std::endl;

	// put check bits into array for converting to string
	int check[3];
	check[0] = c3;
	check[1] = c2;
	check[2] = c1; 

	// Convert check bits into string to print for user
	std::string error;
	for(int i=0; i<3; i++) {
		error += std::to_string(check[i]);
	}

	// Determine syndrome
	int syndrome = (c1 ^ c2 ^ c3);

	// Print syndrome for user
	std::cout << "syndrome is: " << syndrome << std::endl;

	// Check syndrome against 4th check bit to determine 
	// error status in given hamming code
	if(c4 == 0 && syndrome == 0) {
		std::cout << "No error" << std::endl;
	} else if(c4 == 0 && syndrome != 0) {
		std::cout << "2 bits are in error" << std::endl;
	} else if(c4 == 1 && syndrome == 0) {
		std::cout << "P4 is in error" << std::endl;
		if(ham[8-1] == 0) {
			ham[8-1] = 1;
		} else if(ham[8-1] == 1) {
			ham[8-1] = 0;
		}
	} else if(c4 == 1 && syndrome != 0) {
		std::cout << "1 bit is in error.. correcting..." << std::endl << std::endl;
		//std::cout << "The " << error << " bit is in error" << std::endl << std::endl;

		// Print check bit result for user
		std::cout << "Error at: " << error << std::endl;
		// Fix given hammign code
		int fix = pow(check[0],2) + pow(check[1],2) + pow(check[2],2);
		if(fix == 0) {
			std::cout << "No errors" << std::endl;
		} else if(ham[fix-1] == 0) {
			ham[fix-1] = 1;
		} else if(ham[fix-1] == 1) {
			ham[fix-1] = 0;
		} else {
			std::cout << "uh oh" << std::endl;
		}


		// Print fixed hamming code string for user
		//std::cout << "Fixed code is " << output << std::endl;
	
	}

	// Convert int array into string for printing for user
	std::string output;
	for(int i=0; i<8; i++) {
		output += std::to_string(ham[i]);
	}
	// Print fixed hamming code string for user
	std::cout << "Fixed code is " << output << std::endl;
	
	return 0;
}