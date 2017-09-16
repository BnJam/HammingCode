# Hamming Code 
## by
## BnJam

Here is a simple implementation for the Hamming Code that takes in an 8 bit string of ones and zeroes

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
   
Where 'P' indicates the parity bits and 'D' indicates the data bits. 
  ``` 
   P1 = XOR(3,5,7)
   P2 = XOR(3,6,7)
   P3 = XOR(5,6,7)
   P4 = XOR(1,2,3,4,5,6,7)
```
These parity bits are used along with themselves to determine the delivered check
```   
   C1 = XOR(1,3,5,7)
   C2 = XOR(2,3,6,7)
   C3 = XOR(4,5,6,7)
   C4 = XOR(1,2,3,4,5,6,7,8)
```   
Exclusive OR-ing the check bits 1, 2, and 3, you will result in the Syndrome of the delivered string. This is used in 
comparison with check bit 4 to determine the following:
```
  C4 Syndrome
   0  0         No Error
   0  !0        2 bits in error
   1  0         P4 is in error
   1  !0        1 bit is in error and can be corrected
```   
If one bit is in error, then we can correct it by reading the detail of the Syndrome C3 C2 C1 to determine
the binary representation of the index that requires fixing (flipping to the opposite state). 
