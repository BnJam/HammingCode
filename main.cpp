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
 * 
 */

#include <iostream>
#include <string>


int main() {
	
	// Store bit string
	std::string ham; 

	// Get input from user
	std::cout << "Enter 8 bit string:" << std::endl;
	std::cin >> ham;
	// Convert to char array
	ham = ham.c_str();

//	std::cout << ham[0] << std::endl; // Debug print statement

	/**
	 * | P1 | P2 | D1 | P3 | D2 | D3 | D4 | P4 |
	 * | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  |
	 *
	 * 0 0 0 | 0
	 * 0 0 1 | P1
	 * 0 1 0 | P2
	 * 0 1 1 | D1
	 * 1 0 0 | P3
	 * 1 0 1 | D2
	 * 1 1 0 | D3
	 * 1 1 1 | D4
	 *   
	 * 
	 */

	int p1, p2, p3, p4;
	p1 = (ham[3-1] ^ ham[5-1] ^ ham[7-1]);
	p2 = (ham[3-1] ^ ham[6-1] ^ ham[7-1]);
	p3 = (ham[5-1] ^ ham[6-1] ^ ham[7-1]);

	if(p1 != ham[1-1] && p2 != ham[2-1]) {
		std::cout << "d1 is in error" << std::endl; 
	}
	if(p1 != ham[1-1] && p3 != ham[4-1]) {
		std::cout << "d2 is in error" << std::endl;
	}
	if(p2 != ham[2-1] && p3 != ham[4-1]) {
		std::cout << "d3 is in error" << std::endl;
	}
	if(p1 != ham[1-1] && p2 != ham[2-1] && p3 != ham[4-1]) {
		std::cout << "d4 is in error" << std::endl;
	}

	int c1, c2, c3, c4;
	c1 = (ham[1-1] ^ ham[3-1] ^ ham[5-1] ^ ham[7-1]);
	c2 = (ham[2-1] ^ ham[3-1] ^ ham[6-1] ^ ham[7-1]);
	c3 = (ham[4-1] ^ ham[5-1] ^ ham[6-1] ^ ham[7-1]);

	int check[3];
	check[0] = c3;
	check[1] = c2;
	check[2] = c1; 

	std::string error;
	for(int i=0; i<3; i++) {
		error += std::to_string(check[i]);
	}

	std::cout << "The " << error << " bit is in error" << std::endl;

}