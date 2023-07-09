//Hi
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
const int minX = 3, minY = 2, maxX = 60, maxY = 20;
int ballX = 24, ballY = 17, velX = 1, velY = 1, loop1 = 0, loop2 = 0, lives = 3;
int sliderX = 22, sliderY = 19, barrierX = 15, barrierY = 11, // slider and barrier initial x and y position 
bricks[3][9][2] = { {4,4, 10,4, 16,4, 22,4, 28,4, 34,4, 40,4, 46,4, 52,4}, //Bricks Frquency
					 {4,6, 10,6, 16,6, 22,6, 28,6, 34,6, 40,6, 46,6, 52,6},
					 {4,8, 10,8, 16,8, 22,8, 28,8, 34,8, 40,8, 46,8, 52,8} },
	bricksFreq[3][3][9] =
{ {1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1},     //level1 bricks freq 
{0,0,0,1,1,1,0,0,0, 0,0,2,2,2,2,2,0,0, 0,1,1,1,1,1,1,1,0},     //level2 bricks freq
{1,1,1,0,0,0,1,1,1, 3,3,3,3,3,3,3,3,3, 1,1,1,0,0,0,1,1,1} }, tempBricksFreq[3][3][9];     //level3 bricks freq 	

void gotoxy(int x, int y)
{
	COORD coordinates;
	coordinates.X = x;
	coordinates.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void values(int tempArray1[3][3][9], int tempArray2[3][3][9]) {  // to restore bricks frequency after every level stcpy wasnt working to copy one array to other.
	int i, j, k;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			for (k = 0; k < 9; k++)
				tempArray1[i][j][k] = tempArray2[i][j][k];
		}
	}
}
void initializeBricks(int a) { //will initialize level brciks, the parameter a is level number
	for (loop1 = 0; loop1 < 3; loop1++) {
		for (loop2 = 0; loop2 < 9; loop2++) {
			if (bricksFreq[a][loop1][loop2] >= 1) {
				gotoxy(bricks[loop1][loop2][0], bricks[loop1][loop2][1]);
				if (bricksFreq[a][loop1][loop2] == 2)
					printf("\033[0;35m%c%c%c%c%c", 254, 254, 254, 254, 254);
				else if (bricksFreq[a][loop1][loop2] == 3)
					printf("\033[0;34m%c%c%c%c%c", 254, 254, 254, 254, 254);
				else if (bricksFreq[a][loop1][loop2] == 1)
					printf("\033[0;36m%c%c%c%c%c", 254, 254, 254, 254, 254);
			}
		}
	}
}
void ballHitBricks(int a) {           // if ball hits bricks of levels paratmeter a is level number
	for (loop1 = 0; loop1 < 3; loop1++) {
		for (loop2 = 0; loop2 < 9; loop2++) {
			if ((ballY == bricks[loop1][loop2][1] + 1 || ballY == bricks[loop1][loop2][1] - 1) && ballX >= bricks[loop1][loop2][0] && ballX <= bricks[loop1][loop2][0] + 5 && bricksFreq[a][loop1][loop2] >= 1) {

				velY = -velY;
				bricksFreq[a][loop1][loop2]--; // will reduce the frequency
			}
			if (ballY == bricks[loop1][loop2][1] && ballX >= bricks[loop1][loop2][0] && ballX <= bricks[loop1][loop2][0] + 5 && bricksFreq[a][loop1][loop2] >= 1) {
				velX = -velX;
				bricksFreq[a][loop1][loop2]--;
			}
		}
	}
}
void levelBorder() {  //border around the game 
	for (loop1 = minY + 1; loop1 < maxY; loop1++) {
		gotoxy(minX, loop1);
		printf("\033[0;36m*");
		gotoxy(maxX, loop1);
		printf("\033[0;36m*");             //right  and left border
	}
	for (loop1 = minX; loop1 <= maxX; loop1++) {
		gotoxy(loop1, minY);
		printf("\033[0;36m*");
		gotoxy(loop1, maxY);                   // Top and bottom border
		printf("\033[0;36m-");
	}
}
void moveSlider() { // will move the slider
	char choice;
	gotoxy(sliderX, sliderY);
	printf("\033[0;36m%c%c%c%c%c%c", 254, 254, 254, 254, 254, 254);
	if (kbhit()) {   // if keyboard key is pressed
		choice = getch();
		if (choice == 's' && sliderX > 4)
			sliderX -= 2;
		else if (choice == 'd' && sliderX < 53)
			sliderX += 2;
	}
}
void moveBall() { // movement of ball
	gotoxy(ballX, ballY);
	printf("\033[0;36m%c", 2);
	ballX += velX;
	ballY += velY;
	if (ballX < minX + 1 || ballX > maxX - 1)
		velX = -velX;
	if (ballY < minY + 1)
		velY = -velY;
}
void ballHitSlider() { // if ball hits slider it will rebounce
	if (ballY == sliderY - 1 && ballX >= sliderX - 1 && ballX <= sliderX + 6) // if ball is within this x range
		velY = -velY;
}
void printMenu() {  // print lives of player
	gotoxy(65, 2);
	printf("\033[0;36mLives: %d", lives);
}
void lose() { //if player wins
	char choice;
	while (1) {
		system("cls");
		Sleep(100);
		gotoxy(20, 12);
		printf("|You Lose| ");
		printf("Press c to continue and e to exit the game: ");
		choice = getch();
		if (choice == 'c' || choice == 'C') break;
		else if (choice == 'e' || choice == 'E')
			exit(0);
	}

}
void win() { //if player loses
	char choice;
	while (1) {
		system("cls");
		Sleep(100);
		gotoxy(20, 12);
		printf("|Conragulations you have won| ");
		printf("Press c to continue and e to exit the game: ");
		choice = getch();
		if (choice == 'c' || choice == 'C') break;
		else if (choice == 'e' || choice == 'E')
			exit(0);
	}
}
int  instructions() { //Startup menu
	loop1 = 55; char choice;
	while (1) {

		while (loop1 >= 30) {
			system("cls");
			gotoxy(30, 7);
			printf("\033[0;36mWelcome to Brick Mansion Game");
			printf("\033[0;35m");
			gotoxy(loop1, 9);
			printf("Start Game");
			gotoxy(loop1, 11);
			printf("Instructions");
			gotoxy(loop1, 13);
			printf("Press s to start game and i to read instructions: ");
			Sleep(20);
			loop1--;
		}
		choice = getch();
		if (choice == 's' || choice == 'S') {
			return 1; break;
		}
		else if (choice == 'i' || choice == 'I') {
			system("cls");
			printf("\n\n\t\033[0;35m1. Use \'s'  and \'d' keys to move the slider to the left and right"
				"\n\n\t2. If ball hits the bottom of screen then you will lose a life\n\n\t3. Press any key to go back");
			getch();
		}
		loop1 = 55;
	}
}
int check(int a) { // check if the player has losen a life or there are no bricks left
	if (ballY == maxY + 1) {
		--lives;
		ballX = 24;
		ballY = 17;
		sliderX = 22;
		sliderY = 19;
		getch();
	}
	int thisCheck = 0, k, l;
	for (k = 0; k < 3; k++) {
		for (l = 0; l < 9; l++) {
			if (bricksFreq[a][k][l] == 0) {
				continue;
			}
			else {
				thisCheck = 1;
				break;
			}
		}
		if (thisCheck == 1)
			break;
	}
	return !thisCheck;

}
int level1() {
	lives = 2;
	while (1) {
		system("cls");
		levelBorder();
		printMenu();
		moveSlider();
		moveBall();
		initializeBricks(0);
		ballHitBricks(0);
		if (lives == 0) { ballX = 24; ballY = 17; return 0; }
		if (check(0)) return 1;
		ballHitSlider();
		Sleep(30);
	}
}
int level2() {

	lives = 3;
	while (1) {
		system("cls");
		levelBorder();
		printMenu();
		moveSlider();
		moveBall();
		initializeBricks(1);
		ballHitBricks(1);
		if (lives == 0) { ballX = 24; ballY = 17; return 0; }
		if (check(1)) return 1;
		ballHitSlider();
		Sleep(30);
	}
}
int level3() {
	lives = 4;
	while (1) {
		system("cls");
		levelBorder();
		printMenu();
		moveSlider();
		moveBall();
		initializeBricks(2);
		ballHitBricks(2);
		if (lives == 0) { ballX = 24; ballY = 17; return 0; } // if player has losen lives
		if (check(2)) return 1; // if there are no bricks left
		ballHitSlider();
		for (loop1 = barrierX; loop1 < barrierX + 30; loop1++) {
			gotoxy(loop1, barrierY);
			printf("\033[0;36m%c", 254);
		}
		if ((ballY == barrierY + 1 || ballY == barrierY - 1) && (ballX >= barrierX && ballX <= barrierX + 30))
			velY = -velY;
		if ((ballY == barrierY && ballX == barrierX - 1) || (ballY == barrierY && ballX == barrierX + 31))
			velX = -velX;
		// incase ball hit edge of barrier
		Sleep(30);
	}
}
int main() {
	int num, i = 0, randomArray[3];
	srand(time(0));
	values(tempBricksFreq, bricksFreq);
	while (1) {
		instructions();
		randomArray[0] = rand() % 3;  // create random array with three elements
		while (1) {
			randomArray[1] = rand() % 3;
			if (randomArray[1] != randomArray[0]) break;
		}
		while (1) {
			randomArray[2] = rand() % 3;
			if (randomArray[2] != randomArray[0] && randomArray[2] != randomArray[1]) break;
		}
		for (i = 0; i < 3; i++) {
			values(bricksFreq, tempBricksFreq);   // restoring original frequency of bricks again and again
			if (randomArray[i] == 0)
				num = level1();
			else if (randomArray[i] == 1)
				num = level2();
			else if (randomArray[i] == 2)
				num = level3();

			if (num == 1)
				continue;
			else {
				lose();
				break;
			}
		}
		if (i == 3) {
			win();
			ballX = 24; ballY = 17;
		}
	}
}
