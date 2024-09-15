#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include<string.h>

void printMatrix(int H, int W, int matrix[H][W], char CHAR) {
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			mvaddch(y, x, matrix[y][x] ? CHAR : ' ');
		}
	}
	refresh();
}

int argParse(int argc, char* argv[], int* delay, char* aliveChar) {
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-d") == 0) {
			if (i + 1 < argc) {
				*delay = atoi(argv[++i]);
			} else {
				fprintf(stderr, "Error: -d option requires an argument.\n");
				exit(1);
			}
		} else if (strcmp(argv[i], "-c") == 0) {
			if (i + 1 < argc) {
				*aliveChar = argv[++i][0];
			} else {
				fprintf(stderr, "Error: -c option requires an argument.\n");
				exit(1);
			}
		} else if (strcmp(argv[i], "-h") == 0) {
			printf("Conway's Game of Life - A living world in your terminal!\n\n");
			printf("Usage: conway [OPTIONS]\n");
			printf("Options:\n");
			printf("	-c [char]        Character representing a living cell. Default: '#'.\n");
			printf("	-d [int]         Delay time between ticks in milliseconds. Default: 50.\n");
			printf("	-h               Show this help message.\n");
			printf("Example:\n");
			printf("	conway -c 8 -d 25\n\n");
			printf("Press 'q' to exit.\n\n");
			exit(0);
		} else {
			fprintf(stderr, "Error: Unknown option %s\n", argv[i]);
			exit(1);
		}
	}
}

int main(int argc, char* argv[]) {	
	// input
	int DELAY = 50;
	char CHAR = '#';
	argParse(argc, argv, &DELAY, &CHAR);

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
	
	// starting config
	matrix[3][3] = 1; matrix[4][3] = 1; matrix[5][3] = 1;
	matrix[4][2] = 1; matrix[5][4] = 1;

	// === THE GAME OF LIFE === //
	while(1) {
		// exit program
		int ch = getch();
		if (ch == 'q') break;

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

		printMatrix(H, W, matrix, CHAR);
		napms(DELAY);
	}
	
	curs_set(1);
	endwin();
	return 0;
}
