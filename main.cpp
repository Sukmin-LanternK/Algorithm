#include <stdio.h>
#include <string.h>

void bubbleSort(int Dataset[], int length);
void insertSort(int Dataset[], int length);

int newIndexCreate(int Dataset[], int Left, int Right);
void quickSort(int Dataset[],int Left, int Right);


int main() {
	int dataset[] = { 6,4,3,2,1,5 };
	int len = sizeof(dataset) / sizeof(dataset[0]);
	
	quickSort(dataset,0,len-1);

	for (int i = 0; i < len;i++) {
		printf("%d ",dataset[i]	);
	}


	return 0;
}


void bubbleSort(int Dataset[], int length) {
	for (int i = 0;i < length-1; i++) {
		for (int j = 0;j < length-1-i;j++) {
			if (Dataset[j] - Dataset[j + 1] > 0) {
				int temp = Dataset[j];
				Dataset[j] = Dataset[j + 1];
				Dataset[j + 1] = temp;
			}
		}
	}
}

void insertSort(int Dataset[], int length) {
	for (int i = 1;i < length;i++) {
		int value = Dataset[i];
		if (value - Dataset[i - 1] > 0) {
			continue;
		}

		for (int j = 0;j < i;j++) {
			if (value - Dataset[j] < 0) {
				memmove(&Dataset[j + 1], &Dataset[j], sizeof(Dataset[0]) * (i - j));
				Dataset[j] = value;
				break;
			}
		}
	}
}

int newIndexCreate(int Dataset[],int Left, int Right) {
	/* 
	레프트에서 인덱스보다 큰 숫자 찾기
	라이트에서 인덱스보다 작은 숫자 찾기 
	레프트 라이트 교환 
	*/
	int First = Left;
	int index = Dataset[First];
	++Left;

	while (Left <= Right) {  // 교차될 때까지 반복
		while (Left <= Right && Dataset[Left] < index) {
			++Left;
		}
		while (Left <= Right && Dataset[Right] > index) {
			--Right;
		}

		if (Left < Right) {  // 교환 가능한 경우에만 교환
			int temp = Dataset[Left];
			Dataset[Left] = Dataset[Right];
			Dataset[Right] = temp;
			++Left;
			--Right;
		}
	}

	// 피벗과 Right 위치를 교환 (Right가 피벗의 올바른 위치)
	int temp = Dataset[First];
	Dataset[First] = Dataset[Right];
	Dataset[Right] = temp;

	return Right;
}

void quickSort(int Dataset[], int Left, int Right) {
	/*
	인덱스를 받는다
	레프트 라이트 전부 검토 끝나면 -> 인덱스 옮기기 

	인덱스 내에서 다시 레프트 라이트 설정해주기
	갱신된 인덱스 기반으로 퀵소트 다시 돌리기 
	ㅇ 안돌리는 조건 넣어야 됨 
	*/
	if (Left < Right) {
		int new_index = newIndexCreate(Dataset,Left,Right);

		quickSort(Dataset, Left, new_index - 1);
		quickSort(Dataset, new_index+1, Right);
	}


}


