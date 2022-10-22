#include<Windows.h>
#include<iostream>
#include<ctime>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
COORD pos = { 0, 0 };

const int size = 50;

int Snake[size * size][2];
int Berry[2];

std::string Buffer;
std::string ResetBuffer;

int x;
int y;

void reset()
{
    Snake[0][0] = std::rand() % size;
    Snake[0][1] = std::rand() % size;;
    Snake[3][0] = -1;

    Berry[0] = std::rand() % size;
    Berry[1] = std::rand() % size;

    ResetBuffer = "\n";
    for (int i = 0; i < size; i++) {
        for (int i2 = 0; i2 < size; i2++) {
            ResetBuffer += "--";
        }
        ResetBuffer += "\n";
    }
}

void input()
{
    x = 0;
    y = 0;

    if (GetKeyState(0x57) == -127 || GetKeyState(0x57) == -128) { y--; } //W
    if (GetKeyState(0x41) == -127 || GetKeyState(0x41) == -128) { x--; } //A
    if (GetKeyState(0x53) == -127 || GetKeyState(0x53) == -128) { y++; } //S
    if (GetKeyState(0x44) == -127 || GetKeyState(0x44) == -128) { x++; } //D

    if (GetKeyState(0x52) == -127 || GetKeyState(0x52) == -128) { reset(); } //R

    if (GetKeyState(0x51) == 1) { // Q
        if (Snake[0][0] < Berry[0]) {
            if (Berry[0] - Snake[0][0] < Snake[0][0] + size - Berry[0])x++;
            else x--;
        }
        else if (Berry[0] < Snake[0][0]) {
            if (Snake[0][0] - Berry[0] < Berry[0] + size - Snake[0][0])x--;
            else x++;
        }

        if (Snake[0][1] < Berry[1]) {
            if (Berry[1] - Snake[0][1] < Snake[0][1] + size - Berry[1])y++;
            else y--;
        }
        else if (Berry[1] < Snake[0][1]) {
            if (Snake[0][1] - Berry[1] < Berry[1] + size - Snake[0][1])y--;
            else y++;
        }
    }
}

void Draw()
{
    Buffer = ResetBuffer;

    int index = ((Berry[0] + 1) * 2) + (Berry[1] * size * 2) + (Berry[1] - 1);
    Buffer[index] = '%';
    Buffer[index += 1] = '%';

    for (int i = 0; i < size * size; i++) {
        if (Snake[i][0] == -1)break;

        index = ((Snake[i][0] + 1) * 2) + (Snake[i][1] * size * 2) + (Snake[i][1] - 1);
        Buffer[index] = '#';
        Buffer[index += 1] = '#';
    }

    std::cout << Buffer;
    SetConsoleCursorPosition(hConsole, pos);
}

void clac()
{
    int old[2] = { 0,0 };

    bool berry = true;
    if (Snake[0][0] == Berry[0] && Snake[0][1] == Berry[1])berry = false;

    old[0] = Snake[0][0];
    old[1] = Snake[0][1];

    Snake[0][0] += x;
    Snake[0][1] += y;

    if (Snake[0][0] < 0)Snake[0][0] += size;
    if (Snake[0][1] < 0)Snake[0][1] += size;
    if (Snake[0][0] >= size)Snake[0][0] = Snake[0][0] % size;
    if (Snake[0][1] >= size)Snake[0][1] = Snake[0][1] % size;

    for (int i = 1; i < (size * size); i++) {
        if (Snake[i][0] == -1) {
            if (berry)break;
            else {
                Snake[i][0] = old[0];
                Snake[i][1] = old[1];
                Snake[i += 1][0] = -1;

                Berry[0] = std::rand() % size;
                Berry[1] = std::rand() % size;

                break;
            }
        }
        else {
            std::swap(Snake[i][0], old[0]);
            std::swap(Snake[i][1], old[1]);
        }
    }
}

int main()
{
    std::srand(std::time(nullptr));
    reset();
    while (true) {
        input();

        clac();

        Draw();
    }
}