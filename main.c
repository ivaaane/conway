#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/ioctl.h>
#include<signal.h>

#define DELAY 150000

void terminalSize(int *W, int *H) {
	struct winsize ws;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
		perror("ioctl");
		exit(EXIT_FAILURE);
	}
	*W = ws.ws_col; // width
	*H = ws.ws_row; // height
}

// exit and re-show cursor
void signalHandler(int signum) {
	printf("\033[?25h\n");
	fflush(stdout);
	exit(signum);
}

void printMatrix(int H, int W, int matrix[H][W]) {
	printf("\033[2J\033[1;1H"); // Clear screen and move cursor to top-left
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			printf("%c", matrix[y][x] ? '#' : ' ');
		}
		printf("\n");
	}
	fflush(stdout);
}

int main() {
	// hide cursor
	printf("\033[?25l");
	fflush(stdout);
	
	signal(SIGINT, signalHandler);
	signal(SIGTERM, signalHandler);
	signal(SIGQUIT, signalHandler);

	int W, H;
	terminalSize(&W, &H);

	// initial generation
	int matrix[H][W];
	int nextgen[H][W];

	for(int y=0;y<H;y++) {
		for(int x=0;x<W;x++) {
			matrix[y][x] = 0;
		}
	}
	
	matrix[3][3] = 1; matrix[4][4] = 1;
	matrix[5][2] = 1; matrix[5][3] = 1;
	matrix[5][4] = 1;
	
	// === THE GAME OF LIFE === //
	while(1) {
		// itinerate matrix
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
		usleep(DELAY);
	}
}
