//#include <stdio.h>
//#include <stdlib.h>
//
//typedef unsigned long ULONG; //64bit 
//
//ULONG Power(int Base, int Exponent) {
//	if (Exponent == 1) {
//		return Base;
//	}
//	else if (Exponent == 0) {
//		return 1; 
//	}
//
//	if (Exponent % 2 == 0) {
//		ULONG NewBase = Power(Base, Exponent / 2);
//		return NewBase * NewBase;
//	}
//	else if (Exponent % 2 == 1) {
//		ULONG NewBase = Power(Base, (Exponent - 1) / 2);
//		return NewBase * NewBase * Base;
//	}
//}

//int main() {
//	int Base = 2; 
//	int Exponent = 30;
//
//	printf("Base: %d , Exponent: %d , Result : %d",Base,Exponent,Power(Base,Exponent));
//
//
//	return 0; 
//}