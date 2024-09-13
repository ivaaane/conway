#include<stdio.h>
#include<ncurses.h>
#include<string.h>

#define DELAY 50

void printMatrix(int H, int W, int matrix[H][W]) {
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			mvaddch(y, x, matrix[y][x] ? '#' : ' ');
		}
	}
	refresh();
}

int main() {
	// start ncurses
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	timeout(0);
	curs_set(0);

	// terminal size
	int W, H;
	getmaxyx(stdscr, H, W);

	// initial generation
	int matrix[H][W];
	memset(matrix, 0, sizeof(matrix));
	
	// starting config (temporal)
	matrix[3][3] = 1; matrix[4][3] = 1; matrix[5][3] = 1;
	matrix[4][2] = 1; matrix[5][4] = 1;

	// === THE GAME OF LIFE === //
	while(1) {
		// exit program
		int ch = getch();
		if (ch == 'q') {
		    break;
		}

		// itinerate matrix
		int nextgen[H][W];
		for(int y = 0; y < H; y++) {
			for (int x = 0; x < W; x++) {
				// moore neighbourhood
				int count = 0;
				for(int dy = -1; dy < 2; dy++) {
                			for(int dx = -1; dx < 2; dx++) {
                				if (dy == 0 && dx == 0) continue;
                				int ny = (y + dy + H) % H;
                				int nx = (x + dx + W) % W;
                				count += matrix[ny][nx];
                			}
            			}
				nextgen[y][x] = count;
			}
		}

		// update current generation
		for(int y = 0; y < H; y++) {
			for(int x = 0; x < W; x++) {
				// dae rules
				if (matrix[y][x] && (nextgen[y][x] < 2 || nextgen[y][x] > 3)) {
					matrix[y][x] = 0; // cell dies
				} else if (!matrix[y][x] && nextgen[y][x] == 3) {
					matrix[y][x] = 1; // cell is born
				}
			}
		}

		printMatrix(H, W, matrix);
		napms(DELAY);
	}
	
	curs_set(1);
	endwin();
	return 0;
}
