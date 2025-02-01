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
	����Ʈ���� �ε������� ū ���� ã��
	����Ʈ���� �ε������� ���� ���� ã�� 
	����Ʈ ����Ʈ ��ȯ 
	*/
	int First = Left;
	int index = Dataset[First];
	++Left;

	while (Left <= Right) {  // ������ ������ �ݺ�
		while (Left <= Right && Dataset[Left] < index) {
			++Left;
		}
		while (Left <= Right && Dataset[Right] > index) {
			--Right;
		}

		if (Left < Right) {  // ��ȯ ������ ��쿡�� ��ȯ
			int temp = Dataset[Left];
			Dataset[Left] = Dataset[Right];
			Dataset[Right] = temp;
			++Left;
			--Right;
		}
	}

	// �ǹ��� Right ��ġ�� ��ȯ (Right�� �ǹ��� �ùٸ� ��ġ)
	int temp = Dataset[First];
	Dataset[First] = Dataset[Right];
	Dataset[Right] = temp;

	return Right;
}

void quickSort(int Dataset[], int Left, int Right) {
	/*
	�ε����� �޴´�
	����Ʈ ����Ʈ ���� ���� ������ -> �ε��� �ű�� 

	�ε��� ������ �ٽ� ����Ʈ ����Ʈ �������ֱ�
	���ŵ� �ε��� ������� ����Ʈ �ٽ� ������ 
	�� �ȵ����� ���� �־�� �� 
	*/
	if (Left < Right) {
		int new_index = newIndexCreate(Dataset,Left,Right);

		quickSort(Dataset, Left, new_index - 1);
		quickSort(Dataset, new_index+1, Right);
	}


}


