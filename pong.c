#include <ncurses.h>

#define RIGHT 111111
#define LEFT 111110
#define LEFT_UP 111112
#define LEFT_DOWN 111113
#define RIGHT_UP 111114
#define RIGHT_DOWN 111115
#define RIGHT_OUT 111116
#define LEFT_OUT 111117

int ball_movement(int player_1, int player_2, int ballX, int ballY, int direction);

int main() {
    int field_X = 81;
    int field_Y = 30;
    int score_p1 = 0;
    int score_p2 = 0;
    int player_1 = 13;
    int player_2 = 13;
    int ballX = 41;
    int ballY = 13;
    int direction = RIGHT;

    initscr();

    curs_set(0);  // "Убиваем" курсор
    nodelay(stdscr, TRUE);

    while ( true ) {
        erase();
        timeout(50);

        if (direction == LEFT) {
            ballX--;
        } else if (direction == RIGHT) {
            ballX++;
        } else if (direction == LEFT_UP) {
            ballX--;
            ballY++;
        } else if (direction == LEFT_DOWN) {
            ballX--;
            ballY--;
        } else if (direction == RIGHT_UP) {
            ballX++;
            ballY++;
        } else if (direction == RIGHT_DOWN) {
            ballX++;
            ballY--;
        } else if (direction == RIGHT_OUT) {  // Выход мяча за правое поле, начисление очков второму игроку
            ballX = 41;
            ballY = 13;
            score_p2++;
            direction = RIGHT;
        } else if (direction == LEFT_OUT) {  // Выход мяча за левое поле, начисление очков первому игроку
            ballX = 41;
            ballY = 13;
            score_p1++;
            direction = LEFT;
        }

        direction = ball_movement(player_1, player_2, ballX, ballY, direction);

        for (int i = 0; i <= field_Y; i++) {
            for (int j = 0; j <= field_X; j++) {
                if (i == ballY && j == ballX) {
                    printw("*");
                }

                if (i == ballY) {
                    if (j == 0 || j == 80) {
                        printw("#");  // отрисовка по вертикали
                    } else  if ((j == 1) && ((i == player_1) || (i == player_1 + 1) || (i == player_1 - 1))) {
                        printw("]");
                    } else if ((j == 79) && ((i == player_2) || (i == player_2 + 1) || (i == player_2 - 1))) {
                        printw("[#");
                        j = j + 1;
                    } else {
                        printw(" ");
                    }
                } else {
                    if (i == 0 || i == 26) {
                        printw("#");  // отрисовка по горизонтали
                    } else if (j == 0 || j == 81) {
                        printw("#");  // отрисовка по вертикали
                    } else  if ((j == 1) && ((i == player_1) || (i == player_1 + 1) || (i == player_1 - 1))) {
                        printw("]");
                    } else if ((j == 80) && ((i == player_2) || (i == player_2 + 1) || (i == player_2 - 1))) {
                        printw("[#");
                        j = j + 1;
                    } else {
                        if (j > 39 && j < 44 && i == field_Y - 3) {
                            printw("%d  %d", score_p1, score_p2);
                            j += 4;
                        }
                        if (j > 39 && j < 44 && i == field_Y-2 && (score_p2 == 21 || score_p1 == 21)) {
                            printw("WIN!");
                            score_p2 = 0;
                            score_p1 = 0;
                            j += 4;
                            timeout(5000);
                        } else if (i == 29 && j == 5) {
                            printw("player 1 a-z; player 2 k-m");
                            j += 25;
                        } else if (i == 30 && j == 5) {
                            printw("q - quit");
                            j += 7;
                        } else {
                            printw(" ");
                        }
                    }
                }
           }
        printw("\n");
        }
         // Получаем нажатие пользователя
        switch (getch()) {
            case 'a':
                if ( player_1 > 2)  // Если возможно, переводим указатель вверх
                    player_1--;
                break;
            case 'z':
                if ( player_1 < 24)  // Если возможно, переводим указатель вниз
                    player_1++;
                break;
            case 'k':
                if ( player_2 > 2)  // Если возможно, переводим указатель вверх
                    player_2--;
                break;
            case 'm':
                if ( player_2 < 24)  // Если возможно, переводим указатель вниз
                    player_2++;
                break;
            case 'q':
                endwin();
                return 0;
                break;
        }
    }
    endwin();
    return 0;
}

int ball_movement(int player_1, int player_2, int ballX, int ballY, int direction) {
    if (player_1 == ballY && ballX == 2) {
        return RIGHT;
    } else if (player_2 == ballY && ballX == 79) {
        return LEFT;
    } else if (player_2 - 1 == ballY && ballX == 79) {
        return LEFT_DOWN;
    } else if (player_2 + 1 == ballY && ballX == 79) {
        return LEFT_UP;
    } else if (player_1 - 1 == ballY && ballX == 2) {
        return RIGHT_DOWN;
    } else if (player_1 + 1 == ballY && ballX == 2) {
        return RIGHT_UP;
    } else if (direction == RIGHT_UP && ballY == 25) {
        return RIGHT_DOWN;
    } else if (direction == RIGHT_DOWN && ballY == 1) {
        return RIGHT_UP;
    } else if (direction == LEFT_DOWN && ballY == 1) {
        return LEFT_UP;
    } else if (direction == LEFT_UP && ballY == 25) {
        return LEFT_DOWN;
    } else if (ballX == 1) {  // Обработка забитого гола
        return RIGHT_OUT;
    } else if (ballX == 80) {  //  Обработка забитого гола
        return LEFT_OUT;
    }
    return direction;
}
