#include <iostream>
#include <windows.h>
#include <string>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void start() {
    std::cout << "ИГРА - КУБИЧЕСКИЙ ЛАБИРИНТ.\n\nPress\n'W' - to move up,\n'A' - to move left,\n'S' - to move down,\n'D' - to move right.\n\n";
    std::cout << "/ - лестница вверх, при нажатии клавиши 'E' поднимает вас на этаж выше.\n";
    std::cout << "\\ - лестница вниз, при нажатии клавиши'Q' спускает вас на этаж ниже.\n";
    std::cout << "? - кнопка, при нажатии клавиши 'F' активирует проход\n\n";
    std::cout << "Нажмите 1, чтобы перезапустить игру.\n\n";

    system("pause");
    Sleep(500);
    system("cls");
}

int game_over() {
    system("cls");
    std::cout << "YOU LOST. GAME OVER!!!\nDO YOU WANT TO RESTART THE GAME?\n1 - YES.\n2 - NO, I WANT TO EXIT.\n";
    Sleep(1000);
    while (true) {
        if (GetAsyncKeyState(0x31) & 0x8000) {
            return true;
        }
        else if (GetAsyncKeyState(0x32) & 0x8000) {
            return false;
        }
    }
}

int vicrory() {
    system("cls");
    char str[] = { "MY CONGRATULATIONS!!! YOU WIN!!!" };
    for (int i = 0; i < strlen(str); i++) {
        std::cout << str[i];
        Sleep(30);
    }
    Sleep(100);
    for (int i = 0; i < 3; i++) {
        system("cls");
        Sleep(300);
        std::cout << str;
        Sleep(700);
    }
    std::cout << std::endl << "DO YOU WANT TO RESTART THE GAME?\n1 - YES.\n2 - NO, I WANT TO EXIT.\n";
    Sleep(1000);
    while (true) {
        if (GetAsyncKeyState(0x31) & 0x8000) {
            return true;
        }
        else if (GetAsyncKeyState(0x32) & 0x8000) {
            return false;
        }
    }
}

template <size_t rows, size_t cols>
void drawing(int(&mas)[rows][cols], int lives) {
    for (int i = 0; i < 24; i++)
    {
        for (int g = 0; g < 24; g++)
        {
            if (mas[i][g] == 1)
            {
                std::cout << " * ";
            }
            else if (mas[i][g] == 0)
            {
                std::cout << "   ";
            }
            else if (mas[i][g] == 2) {
                std::cout << " / ";
            }
            else if (mas[i][g] == 3) {
                std::cout << " \\ ";
            }
            else if (mas[i][g] == 4) {
                std::cout << " ? ";
            }
            else {
                std::cout << " ! ";
            }
        }
        std::cout << std::endl;
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    std::cout << "\n\n\t\tLIVES: " << lives;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void delete_person(int posy, int posx) {
    COORD coord;
    coord.X = posx;
    coord.Y = posy;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    std::cout << "   ";

}

void drawing_person(int posy, int posx) {
    COORD coord;
    coord.X = posx;
    coord.Y = posy;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    std::cout << " # ";
    coord.X = 100;
    coord.Y = 25;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

template <size_t rows, size_t cols>
int verification(int(&mas)[rows][cols], int posx, int posy) {
    if (mas[posy][posx] == 1)
    {
        return 0;
    }
    return 1;
}

template <size_t rows, size_t cols>
int ladder_check(int(&mas)[rows][cols], int posx, int posy) {
    if (mas[posy][posx] == 2)
    {
        return 2;
    }
    if (mas[posy][posx] == 3) {
        return 3;
    }
    if (mas[posy][posx] == 4) {
        return 4;
    }
    if (mas[posy][posx] == 5) {
        return 5;
    }
    return 0;
}

void restart() {
    system("cls");
    Sleep(500);
    std::cout << "RESTART.";
    Sleep(500);
    system("cls");
    std::cout << "RESTART..";
    Sleep(500);
    system("cls");
    std::cout << "RESTART...";
    Sleep(500);
    system("cls");
}



int main() {
    bool main_game_check = true;
    setlocale(LC_ALL, "Russian");

    int a = 1;
    int stage = 1;
    int lives = 3;
    start();

    int wait = 0;
    COORD coordz;
    int temp = 0;

    int posy = 1;
    int posx = 3;

    const int y1 = 24;
    int mas1[y1][y1] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,1,0,0,1,0,1,0,0,0,1,1,1,1,0,0,0,1,1},
        {1,0,1,1,0,1,0,1,0,1,0,0,0,0,1,0,1,0,0,1},
        {1,0,0,0,0,0,0,1,0,1,1,1,1,0,1,0,0,1,0,1},
        {1,1,1,1,1,1,0,1,0,1,0,0,1,0,1,1,0,1,0,1},
        {1,0,4,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,1},
        {1,0,1,1,0,1,1,1,1,1,0,0,1,0,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,1,1,1,1,0,1,0,0,0,0,1},
        {1,1,1,1,1,1,0,1,1,1,0,0,0,0,1,0,1,1,1,1},
        {1,1,0,0,0,1,0,0,1,1,0,1,1,1,1,0,0,0,0,1},
        {1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,1,1,1,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1},
        {1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1},
        {1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,1,0,1},
        {1,0,1,1,0,1,1,0,1,0,1,1,1,0,1,0,0,0,0,1},
        {1,0,1,0,0,0,1,0,1,0,0,0,1,1,1,1,1,1,1,1},
        {1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,0,1},
        {1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,0,1,0,0,0,1,0,1,1,1,1,1,1,0,1,0,1},
        {1,0,1,0,1,1,1,1,1,0,0,0,1,0,1,0,0,1,0,1},
        {1,0,1,0,0,0,0,0,1,1,1,0,0,0,1,0,1,1,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };
    int mas2[y1][y1] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1 },
        {1,0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,1,1},
        {1,0,1,1,1,1,0,1,0,1,0,1,1,0,1,1,1,0,1,1},
        {1,0,0,0,0,0,0,1,0,1,0,1,4,0,1,1,1,0,0,1},
        {1,0,1,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,0,1},
        {1,0,1,1,0,1,1,1,0,1,0,0,0,1,1,1,1,1,0,1},
        {1,1,1,0,0,0,0,1,0,1,0,1,0,1,1,1,1,0,0,1},
        {1,1,0,0,1,1,0,1,0,1,0,1,0,0,0,0,1,0,1,1},
        {1,1,0,1,1,1,0,1,0,1,0,1,1,1,1,0,1,0,1,1},
        {1,1,0,1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,1,1},
        {1,1,0,1,1,1,0,1,1,1,1,1,0,0,1,1,1,1,1,1},
        {1,1,0,0,0,1,0,0,1,1,0,1,0,1,1,0,0,0,0,1},
        {1,1,1,1,0,1,1,1,1,0,0,0,0,1,1,0,1,1,0,1},
        {1,0,1,1,0,1,1,0,0,0,1,1,0,0,1,0,1,1,1,1},
        {1,0,0,0,0,1,1,1,1,0,1,1,1,1,1,0,0,0,1,1},
        {1,1,1,1,0,1,1,0,1,0,0,0,0,0,0,0,1,0,0,1},
        {1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,0,1},
        {1,1,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,1},
        {1,1,0,1,1,0,0,0,1,0,1,0,0,0,0,0,1,1,0,1},
        {1,1,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,0,1},
        {1,1,1,1,1,0,1,1,1,0,1,1,0,0,0,0,0,1,0,1},
        {1,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,1,3,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };
    int mas3[y1][y1] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,2,1,2,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1},
        {1,0,1,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1},
        {1,0,1,1,1,1,1,1,1,1,0,1,0,1,1,0,0,0,0,1},
        {1,0,0,1,1,0,0,0,0,1,0,1,0,1,1,0,1,1,0,1},
        {1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,1},
        {1,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
        {1,1,0,1,0,1,1,1,0,0,0,0,1,1,1,1,1,1,0,1},
        {1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1},
        {1,0,1,1,1,0,1,0,0,1,0,0,1,0,1,0,1,1,1,1},
        {1,0,1,0,0,0,1,1,0,1,1,0,1,0,1,0,0,0,1,1},
        {1,0,1,0,1,1,1,1,0,1,1,0,0,0,1,1,1,0,1,1},
        {1,0,1,0,1,0,0,0,0,1,1,1,1,0,1,0,1,0,1,1},
        {1,0,1,0,1,1,0,1,1,1,1,1,0,0,0,0,1,0,1,1},
        {1,0,0,0,1,1,0,0,0,1,1,1,0,1,1,1,1,0,1,1},
        {1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1},
        {1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,0,1},
        {1,1,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1},
        {1,1,0,1,1,1,1,1,1,1,0,1,1,0,0,0,0,1,0,1},
        {1,1,0,0,0,0,0,1,1,1,0,1,1,0,1,1,0,1,0,1},
        {1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,1,0,1,0,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,3,1,2,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };
    int mas4[y1][y1] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,3,1,3,0,0,0,0,0,1,1,1,0,0,1,1,1,1,1,1},
        {1,0,1,1,1,1,1,1,0,1,1,1,0,1,1,0,0,0,0,1},
        {1,0,1,0,1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,1},
        {1,0,1,0,1,0,1,1,1,1,1,1,0,1,1,0,1,1,0,1},
        {1,0,1,0,0,0,1,0,0,0,0,0,0,1,1,0,1,1,0,1},
        {1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,0,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,0,1},
        {1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,1,0,1},
        {1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,0,0,1},
        {1,0,0,0,0,0,0,1,0,0,1,1,0,1,0,1,0,1,0,1},
        {1,1,1,1,1,1,0,1,1,0,1,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,1,0,0,0,0,1,1,0,1,0,1,0,1,1,1},
        {1,0,1,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,1,1},
        {1,0,1,1,0,1,1,1,1,1,1,1,0,1,0,1,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,1},
        {1,0,1,1,1,1,0,1,0,1,1,1,1,1,0,0,0,1,0,1},
        {1,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,0,0,0,1},
        {1,1,1,1,0,1,0,1,1,0,0,0,0,0,0,1,0,1,0,1},
        {1,0,0,0,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1},
        {1,0,1,1,1,1,0,1,1,0,1,0,1,1,1,1,0,1,0,1},
        {1,1,1,1,1,1,0,1,1,0,1,0,1,1,0,0,0,1,0,1},
        {1,2,0,0,0,0,0,1,0,0,1,0,0,0,0,1,1,1,3,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };
    int mas5[y1][y1] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,1},
        {1,0,0,1,0,1,1,1,1,0,0,1,0,1,0,1,1,1,1,1},
        {1,0,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1},
        {1,0,1,1,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,1},
        {1,0,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1},
        {1,0,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1},
        {1,0,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1},
        {1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
        {1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
        {1,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,0,0,1},
        {1,1,0,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1},
        {1,4,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,1},
        {1,1,0,1,0,1,0,1,1,1,1,1,0,0,0,1,0,1,0,1},
        {1,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,0,1,0,1},
        {1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,0,0,0,1},
        {1,0,1,1,0,0,1,0,1,0,1,0,0,0,0,1,0,1,0,1},
        {1,0,1,1,0,1,1,0,1,0,1,1,1,1,0,1,0,1,0,1},
        {1,0,1,1,0,1,1,0,1,0,1,1,1,1,0,1,0,1,0,1},
        {1,0,1,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1,1,1},
        {1,0,1,0,0,1,1,0,1,0,1,1,0,1,1,1,0,1,1,1},
        {1,0,1,0,1,1,1,0,1,0,1,1,0,0,0,0,0,1,1,1},
        {1,3,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };
    int stages[5][y1][y1];

    for (int i = 0; i < y1; i++) {
        for (int j = 0; j < y1; j++) {
            stages[0][i][j] = mas1[i][j];
        }
    }
    for (int i = 0; i < y1; i++) {
        for (int j = 0; j < y1; j++) {
            stages[1][i][j] = mas2[i][j];
        }
    }
    for (int i = 0; i < y1; i++) {
        for (int j = 0; j < y1; j++) {
            stages[2][i][j] = mas3[i][j];
        }
    }
    for (int i = 0; i < y1; i++) {
        for (int j = 0; j < y1; j++) {
            stages[3][i][j] = mas4[i][j];
        }
    }
    for (int i = 0; i < y1; i++) {
        for (int j = 0; j < y1; j++) {
            stages[4][i][j] = mas5[i][j];
        }
    }

    drawing(mas1, lives);
    drawing_person(posy, posx);

    while (main_game_check) {
        if ((GetAsyncKeyState(0x57) & 0x8000) || (GetAsyncKeyState(VK_UP) & 0x8000)) {
            delete_person(posy, posx);
            posy--;
            drawing_person(posy, posx);
            if (!verification(stages[stage - 1], (posx / 3), posy)) {
                if (lives == 1) {
                    a = 0;
                    lives--;
                }
                else {
                    Sleep(200);
                    lives--;
                    system("cls");
                    posy++;
                    drawing(stages[stage - 1], lives);
                    drawing_person(posy, posx);
                }
            }
            Sleep(200);
        }
        if ((GetAsyncKeyState(0x41) & 0x8000) || (GetAsyncKeyState(VK_LEFT) & 0x8000)) {
            delete_person(posy, posx);
            posx -= 3;
            drawing_person(posy, posx);
            if (!verification(stages[stage - 1], (posx / 3), posy)) {
                if (lives == 1) {
                    a = 0;
                    lives--;
                }
                else {
                    Sleep(200);
                    lives--;
                    system("cls");
                    posx += 3;
                    drawing(stages[stage - 1], lives);
                    drawing_person(posy, posx);
                }
            }
            Sleep(200);
        }
        if ((GetAsyncKeyState(0x53) & 0x8000) || (GetAsyncKeyState(VK_DOWN) & 0x8000)) {
            delete_person(posy, posx);
            posy++;
            drawing_person(posy, posx);
            if (!verification(stages[stage - 1], (posx / 3), posy)) {
                if (lives == 1) {
                    a = 0;
                    lives--;
                }
                else {
                    Sleep(200);
                    lives--;
                    system("cls");
                    posy--;
                    drawing(stages[stage - 1], lives);
                    drawing_person(posy, posx);
                }
            }
            Sleep(200);
        }
        if ((GetAsyncKeyState(0x44) & 0x8000) || (GetAsyncKeyState(VK_RIGHT) & 0x8000)) {
            delete_person(posy, posx);
            posx += 3;
            drawing_person(posy, posx);
            if (!verification(stages[stage - 1], (posx / 3), posy)) {
                if (lives == 1) {
                    a = 0;
                    lives--;
                }
                else {
                    Sleep(200);
                    lives--;
                    system("cls");
                    posx -= 3;
                    drawing(stages[stage - 1], lives);
                    drawing_person(posy, posx);
                }
            }            Sleep(200);
        }


        if (GetAsyncKeyState(0x31) & 0x8000) {
            posx = 3;
            posy = 1;
            stage = 1;
            restart();
            drawing(mas1, lives);
            drawing_person(posy, posx);
        }
        if (ladder_check(stages[stage - 1], (posx / 3), posy) == 2) {
            if (GetAsyncKeyState('E') & 0x8000) {
                stage++;
                system("cls");
                Sleep(500);
                drawing(stages[stage - 1], lives);
                drawing_person(posy, posx);
                temp = 3;
            }
        }
        else if (ladder_check(stages[stage - 1], (posx / 3), posy) == 3) {
            if (GetAsyncKeyState('Q') & 0x8000) {
                stage--;
                system("cls");
                Sleep(500);
                drawing(stages[stage - 1], lives);
                drawing_person(posy, posx);
                temp = 2;
            }
        }
        else if (ladder_check(stages[stage - 1], (posx / 3), posy) == 4) {

            if (GetAsyncKeyState('F') & 0x8000) {
                switch (stage) {
                case 1: {
                    stages[0][22][18] = 2;
                    break;
                }
                case 2: {
                    stages[1][22][16] = 2;
                    break;
                }
                case 5: {
                    stages[4][1][19] = 5;
                    break;
                }
                }
                system("cls");
                stages[stage - 1][posy][posx / 3] = 0;
                Sleep(500);
                drawing(stages[stage - 1], lives);
                drawing_person(posy, posx);
            }

        }
        else if (ladder_check(mas5, (posx / 3), posy) == 5) {
            main_game_check = vicrory();
            stage = 1;
            a = 1;
            posx = 3;
            posy = 1;
        }

        if ((stages[stage - 1][posy][posx / 3] == 2 || stages[stage - 1][posy][posx / 3] == 3 || stages[stage - 1][posy][posx / 3] == 4) && wait == 0) {
            wait = 1;
            coordz.X = posx;
            coordz.Y = posy;
            if (stages[stage - 1][posy][posx / 3] == 2) temp = 2;
            else if ((stages[stage - 1][posy][posx / 3] == 3)) temp = 3;
            else if ((stages[stage - 1][posy][posx / 3] == 4)) temp = 4;
        }
        else if (wait == 1 && coordz.X == posx && coordz.Y == posy && stages[stage - 1][posy][posx / 3] == 0) wait = 0;
        else if (wait == 1 && stages[stage - 1][posy][posx / 3] == 0) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordz);
            if (temp == 2) std::cout << " / ";
            else if (temp == 3) std::cout << " \\ ";
            else if (temp == 4) std::cout << " ? ";
            wait = 0;
        }

        if (a == 0) {

            system("cls");
            for (size_t i = 0; i < 3; i++)
            {
                Sleep(200);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                drawing(stages[stage - 1], lives);
                drawing_person(posy, posx);
                Sleep(200);
                system("cls");
            }
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

            main_game_check = game_over();
            stage = 1;
            a = 1;
            posx = 3;
            posy = 1;
            lives = 3;
        }
    }
    system("pause");
    return 0;
}









