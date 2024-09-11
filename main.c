#include<stdio.h>
#include <unistd.h>

#define SIZE 20

int main() {
	int matrix[SIZE][SIZE] = {0};	// current gen
	
	// glinder
			  matrix[4][3] = 1;
					    matrix[4][4] = 1;
	matrix[5][2] = 1; matrix[5][3] = 1; matrix[5][4] = 1;

	while(1) {
		int nextgen[SIZE][SIZE] = {0};

		// itinerate matrix
		for(int y = 0; y < SIZE; y++) {
			for (int x = 0; x < SIZE; x++) {
				// moore neighbourhood
				int count = 0;
				for(int dy = -1; dy < 2; dy++) {
                			for(int dx = -1; dx < 2; dx++) {
                				if (dy == 0 && dx == 0) continue;
                				int ny = (y + dy + SIZE) % SIZE;
                				int nx = (x + dx + SIZE) % SIZE;
                				count += matrix[ny][nx];
                			}
            			}
				nextgen[y][x] = count;
			}
		}

		// copy nextgen to matrix
		for(int y = 0; y < SIZE; y++) {
			for(int x = 0; x < SIZE; x++) {
				matrix[y][x] = nextgen[y][x];
			}
		}

		// print
		for(int y = 0; y < SIZE; y++) {
			for(int x = 0; x < SIZE; x++) {
				printf("%i", matrix[y][x]);
			}
			printf("\n");
		}

		sleep(1);
	}
}
