#include <stdio.h>

typedef unsigned long ULONG; //64bit 
typedef struct tagMatrix2x2 {
	ULONG Data[2][2];
}Matrix2x2;


Matrix2x2 Matrix2x2Multiply(Matrix2x2 MAT1, Matrix2x2 MAT2) {

	Matrix2x2 NewMAT;

	NewMAT.Data[0][0] = MAT1.Data[0][0] * MAT2.Data[0][0] + MAT1.Data[0][1] * MAT2.Data[1][0];
	NewMAT.Data[0][1] = MAT1.Data[0][0] * MAT2.Data[0][1] + MAT1.Data[0][1] * MAT2.Data[1][1];
	NewMAT.Data[1][0] = MAT1.Data[1][0] * MAT2.Data[0][0] + MAT1.Data[1][1] * MAT2.Data[1][0];
	NewMAT.Data[1][1] = MAT1.Data[1][0] * MAT2.Data[0][1] + MAT1.Data[1][1] * MAT2.Data[1][1];

	return NewMAT;
}


Matrix2x2 Matrix2x2Power(Matrix2x2 MAT, int N) {
	if (N > 1) {
		MAT = Matrix2x2Power(MAT, N/2);
		MAT = Matrix2x2Multiply(MAT, MAT);

		if (N % 2 == 1) {
			Matrix2x2 TempMAT;
			TempMAT.Data[0][0] = 1; TempMAT.Data[0][1] = 1;
			TempMAT.Data[1][0] = 1; TempMAT.Data[1][1] = 0;

			MAT = Matrix2x2Multiply(MAT,TempMAT);
		}
	}

	return MAT;
}


ULONG Fibonacci(int N) {

	Matrix2x2 MAT;
	MAT.Data[0][0] = 1; MAT.Data[0][1] = 1;
	MAT.Data[1][0] = 1; MAT.Data[1][1] = 0;

	MAT = Matrix2x2Power(MAT, N);

	return MAT.Data[0][1];
}

int main() {
	int  N = 10;
	ULONG Result = Fibonacci(N);
	printf("N: %d, Fibonacci: %lu",N,Result);

	return 0
; 
}