#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>

using namespace std;

bool gameOver;
const int ancho = 20;
const int alto = 20;
int x, y, frutaX, frutaY, score;
vector<int> tailX;
vector<int> tailY;

enum eDireccion { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDireccion dir;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = ancho / 2;
    y = alto / 2;
    frutaX = rand() % ancho;
    frutaY = rand() % alto;
    score = 0;
    tailX.clear();
    tailY.clear();
}

void Draw() {
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    for (int i = 0; i < ancho + 2; i++) cout << "#";
    cout << endl;

    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            if (j == 0) cout << "#";

            if (i == y && j == x) {
                cout << "O";
            } else if (i == frutaY && j == frutaX) {
                cout << "*";
            } else {
                bool printTail = false;
                for (size_t k = 0; k < tailX.size(); k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        printTail = true;
                        break;
                    }
                }
                if (!printTail) cout << " ";
            }

            if (j == ancho - 1) cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < ancho + 2; i++) cout << "#";
    cout << endl;

    cout << "PUNTUACION: " << score << "   " << endl;
}

// (Esto es lo de Kevin)
void Input() {

}


void Logic() {
    if (dir == STOP) return;

    switch (dir) {
        case LEFT:  x--; break;
        case RIGHT: x++; break;
        case UP:    y--; break;
        case DOWN:  y++; break;
        default: break;
    }

    if (x == frutaX && y == frutaY) {
        score += 10;
        frutaX = rand() % ancho;
        frutaY = rand() % alto;
        tailX.push_back(x);
        tailY.push_back(y);
    }

    // (Eso es lo de Sebastian)
}

int main() {
    Setup();
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);

    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(80);
    }

    cout << "GAME OVER - Puntaje: " << score << endl;
    return 0;
}
