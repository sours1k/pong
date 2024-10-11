#include <stdio.h>

#define ROW 80
#define STR 25
#define SPD 1
#define STW 1

/* Функция отрисовки */
void drawScreen(int ballX, int ballY, int rocketOneX, int rocketOneY, int rocketTwoX, int rocketTwoY) {
    for (int i = 0; i < STR; i++) {  // Перебираем строки
        printf("\n");
        for (int k = 0; k < ROW; k++) {  // Перебираем ряды в строке
            if (i == 0 || i == STR - 1 || k == 0 || k == ROW - 1) {  // Рисуем границы
                printf("░");
            } else if (k == ROW / 2 - 1 && i > 1 && i < STR - 2 && i % 2 == 1)  // Рисуем середину
            {
                printf("|");
            } else if (i == ballY && k == ballX) {  // Рисуем шар если он в этой точке
                printf("◉");
            } else if ((i == rocketOneY && k == rocketOneX) || (i - 1 == rocketOneY && k == rocketOneX) ||
                       (i + 1 == rocketOneY && k == rocketOneX)) {
                printf("║");  // Рисуем ракетку 1 если она в этой точке + сверху и снизу
            } else if ((i == rocketTwoY && k == rocketTwoX) || (i - 1 == rocketTwoY && k == rocketTwoX) ||
                       (i + 1 == rocketTwoY && k == rocketTwoX)) {
                printf("║");  // Рисуем ракетку 2 если она в этой точке + сверху и снизу
            } else {
                printf(" ");  // Где ничего нету рисуем пробел
            }
        }
    }
}

void newScreen(int winner) {
    if (winner == 1) {
        for (int i = 0; i < STR; i++) {
            printf("\n");
            for (int k = 0; k < ROW; k++) {
                if (i == 0 || i == STR - 1) {
                    printf(".");
                } else if (i == STR / 2 && k == ROW / 2 - 2) {
                    printf(" Победил игрок 1 ");
                } else {
                    printf(" ");  // Где ничего нету рисуем пробел
                }
            }
        }
    } else {
        for (int i = 0; i < STR; i++) {
            printf("\n");
            for (int k = 0; k < ROW; k++) {
                if (i == 0 || i == STR - 1) {
                    printf(".");
                } else if (i == STR / 2 && k == ROW / 2 - 2) {
                    printf(" Победил игрок 2 ");
                } else {
                    printf(" ");  // Где ничего нету рисуем пробел
                }
            }
        }
    }
}

int main() {
    // Начальные координаты шарика
    int ballX = ROW / 2 - 1;
    int ballY = STR / 2;

    // Начальные координаты первой ракетки
    int rocketOneX = 4;
    int rocketOneY = STR / 2;

    // Начальные координаты второй ракетки
    int rocketTwoX = ROW - 5;
    int rocketTwoY = STR / 2;

    int vector_X = SPD;
    int vector_Y = SPD;

    int player1 = 0;
    int player2 = 0;

    while (1) {
        /* Отрисовка экрана */
        printf("\033[H\033[J");  // Чистим экран
        printf("\n// PLAYER 1 - КЛАВИШИ УПРАВЛЕНИЯ - PLAYER 2  //\n");
        printf("// a - ВВЕРХ * * * * * * * * * * * k - ВВЕРХ //\n");
        printf("// z - ВНИЗ  * * * * * * * * * * * m - ВНИЗ  //\n");
        drawScreen(ballX, ballY, rocketOneX, rocketOneY, rocketTwoX, rocketTwoY);  // Рисуем поле шар ракетки
        printf("\n%34d - SCORE - %d\n", player1, player2);                         // Выводим очки
        printf("\n >> ");

        /* Ввод пользователя */
        char ch;
        ch = getchar();
        switch (ch) {
            case 'a':
                if (rocketOneY > 2) {  //левая ракетка не улетит
                    rocketOneY -= 1;
                }
                break;
            case 'z':
                if (rocketOneY < STR - 3) {
                    rocketOneY += 1;
                }
                break;
            case 'k':
                if (rocketTwoY > 2) {  //правая ракетка тоже
                    rocketTwoY -= 1;
                }
                break;
            case 'm':
                if (rocketTwoY < STR - 3) {
                    rocketTwoY += 1;
                }
                break;
            default:
                printf("\n Instruction: a/z - 1p up/down : k/m - 2p up/down!");
                break;
        }

        if (ch != '\n') {
            /* Проверяем столкновение шара с границами, меняем вектор направления Y */
            if (ballY <= 1 || ballY >= STR - 2) {
                vector_Y *= -1;
            }

            /* Проверяем гол */
            if (ballX <= 1) {         // Если шар попал в правые ворота
                player2++;            // Увеличеваем счет игрока1
                ballX = ROW / 2 - 2;  // Возвращаем шар в исходное положение
                ballY = STR / 2 + 1;
                vector_Y *= -1;  // Запускаем шар в противоположном направлении
                vector_X *= -1;
            } else if (ballX >= ROW - 2) {  // Все тоже самое для игрока2
                player1++;
                ballX = ROW / 2;
                ballY = STR / 2 - 1;
                vector_Y *= -1;
                vector_X *= -1;
            }

            /* Запускаем шар, задаем ему вектор движения. */
            ballX -= -vector_X;
            ballY += -vector_Y;

            /* Придаем колизию ракетки с шаром */
            if (rocketOneY == ballY || rocketOneY + 1 == ballY || rocketOneY - 1 == ballY ||
                rocketOneY + 2 == ballY || rocketOneY - 2 == ballY) {
                if (rocketOneX == ballX - 1) {
                    vector_Y *= -1;
                    vector_X *= -1;
                }
            } else if ((rocketTwoY == ballY || rocketTwoY + 1 == ballY || rocketTwoY - 1 == ballY ||
                        rocketTwoY + 2 == ballY || rocketTwoY - 2 == ballY)) {
                if (rocketTwoX == ballX + 1) {
                    vector_Y *= -1;
                    vector_X *= -1;
                }
            }

            /* Проверяем счет, если игра окончена заканчиваем цикл. */
            if (player1 == STW || player2 == STW) {
                break;
            }
            printf("\n\nX: %d - Y: %d", ballX, ballY);
        }
    }

    printf("\033[H\033[J");
    if (player1 == STW) {
        newScreen(1);
    } else if (player2 == STW) {
        newScreen(2);
    }

    return 0;
}