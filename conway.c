#define TB_IMPL

#include "termbox2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void nextGeneration(int H, int W, int matrix[H][W]);
void printMatrix(int H, int W, int matrix[H][W], char CHAR);
void configParse(int H, int W, int matrix[H][W]);
void exitCheck();
void argParse(int argc, char* argv[], int* delay, char* aliveChar);

int main(int argc, char* argv[]) {	
	// input
	int DELAY = 100;
	char CHAR = '@';
	argParse(argc, argv, &DELAY, &CHAR);

	// start termbox2
	if (tb_init() != 0) {
		printf("Something very very very bad happened with termbox\n");
		return 1;
	}
	tb_clear();

	// terminal size
	int H = tb_width();
	int W = tb_height();

	// initial generation
	int matrix[H][W];
	memset(matrix, 0, sizeof(matrix));
	configParse(H, W, matrix);	
	
	// loop
	while(1) {
		exitCheck();
		nextGeneration(H, W, matrix);
		printMatrix(H, W, matrix, CHAR);
		usleep(DELAY * 1000);
	}
}

void nextGeneration(int H, int W, int matrix[H][W]) {
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
}

void printMatrix(int H, int W, int matrix[H][W], char CHAR) {
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			tb_set_cell(y, x, matrix[y][x] ? CHAR : ' ', TB_WHITE, TB_DEFAULT);
		}
	}
	tb_present();
}

void configParse(int H, int W, int matrix[H][W]) {
	H = H / 2 - 1;
	W = W / 2 - 1;

	matrix[H][W + 1] = 1;
	matrix[H][W + 2] = 1;
	matrix[H + 1][W] = 1;
	matrix[H + 1][W + 1] = 1;
	matrix[H + 2][W + 1] = 1;
}

void exitCheck() {
	static struct tb_event event = {0};
	while ((tb_peek_event(&event, 0)) == TB_OK) {
		if (event.key == TB_KEY_CTRL_C) {
			tb_shutdown();
			exit(0);
		}
	}
}

void argParse(int argc, char* argv[], int* delay, char* aliveChar) {
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
			printf("	-c [char]        Character representing a living cell.\n");
			printf("	-d [int]         Delay time between ticks in milliseconds.\n");
			printf("	-h               Show this help message.\n");
			printf("Example:\n");
			printf("	conway -c 8 -d 25\n\n");
			exit(0);
		} else {
			fprintf(stderr, "Error: Unknown option %s\n", argv[i]);
			exit(1);
		}
	}
}
