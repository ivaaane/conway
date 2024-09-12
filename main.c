#include<stdio.h>
#include <unistd.h>

#define SIZE 20

int main() {
	int matrix[SIZE][SIZE] = {0};	// current gen
	matrix[3][3] = 1; matrix[4][4] = 1; matrix[5][2] = 1; matrix[5][3] = 1; matrix[5][4] = 1;

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

		// update current generation
		for(int y = 0; y < SIZE; y++) {
			for(int x = 0; x < SIZE; x++) {
				// dae rules
				if (matrix[y][x] && (nextgen[y][x] < 2 || nextgen[y][x] > 3)) {
					matrix[y][x] = 0; // cell dies
				} else if (!matrix[y][x] && nextgen[y][x] == 3) {
					matrix[y][x] = 1; // cell is born
				}
			}
		}

		// print matrix
		printf("\033[2J\033[1;1H");
		for(int y = 0; y < SIZE; y++) {
			for(int x = 0; x < SIZE; x++) {
				char square = 0x25A0;
				printf("%c", matrix[y][x] ? '#' : ' ');
			}
			printf("\n");
		}

		usleep(100000);
	}
	return 0;
}
