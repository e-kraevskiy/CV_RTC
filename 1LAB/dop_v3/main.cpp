#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define DEALY 50

#define ALIVE true
#define DEAD false

//Размер исходного изображения в пикселях
const int IMAGE_SIZE = 1000;

//Размер сетки (игрового поля)
const int GRID_SIZE = 100;

const int IMAGE_WIDTH = IMAGE_SIZE / GRID_SIZE;

//Отрисовка необходимого
void printRectangle(unsigned int row, unsigned int col, bool color);

//Начальное поколение ружья Госпера
void printGosperGun(bool arr[GRID_SIZE][GRID_SIZE]);
//Количество живих клеток (не считая данную клетку)
int aliveAround(bool arr[GRID_SIZE][GRID_SIZE], int x, int y);
//Заносим состояние текущего кадра в массив состояния следующего кадра
void checkAndPrint(bool cur[GRID_SIZE][GRID_SIZE],
                   bool next[GRID_SIZE][GRID_SIZE]);
Mat result;

int main()
{
    result = cv::Mat::zeros(IMAGE_SIZE, IMAGE_SIZE, CV_32F);
    result = cv::Scalar(255,255,255);

    bool arr1[GRID_SIZE][GRID_SIZE] = {{DEAD}};
    bool arr2[GRID_SIZE][GRID_SIZE] = {{DEAD}};

    bool (*current)[GRID_SIZE] = arr1;
    bool (*next)[GRID_SIZE] = arr2;
    bool (*temp)[GRID_SIZE];

    // Первое поколение
    printGosperGun(arr1);

    while (true)
    {
        //Идем по массиву текущего состояния
        //Но при этом заносим изменение в массив следующего состояния
        checkAndPrint(current, next);
        imshow("press ESC to stop", result);
        //Меняем массивы местами
        temp = current;
        current = next;
        next = temp;

        if (waitKey(DEALY) == 27)
            break;
    }
    return 0;
}

void checkAndPrint(bool cur[GRID_SIZE][GRID_SIZE],
                   bool next[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            next[i][j] = DEAD;
            if (cur[i][j] == ALIVE) {
                //Первое правило игры "Жизнь":
                //Если у живой клетки есть две или три живые соседки,
                //то эта клетка продолжает жить
                if (aliveAround(cur, i, j) == 2 || aliveAround(cur, i, j) == 3) {
                    next[i][j] = ALIVE;
                    printRectangle(i, j, ALIVE);
                }
                //Иначе она умирает
                else {
                    next[i][j] = DEAD;
                    printRectangle(i, j, DEAD);
                }
            }
            if (cur[i][j] == DEAD) {
                //Второе правило игры "Жизнь":
                //Если у мертвой клекти есть ровно три живых соседа,
                //то в ней зарождается жизнь:
                if (aliveAround(cur, i, j) == 3)
                {
                    next[i][j] = ALIVE;
                    printRectangle(i, j, ALIVE);
                }
            }
        }
    }
}

int aliveAround(bool arr[GRID_SIZE][GRID_SIZE], int x, int y) {
    int aliveCnt = 0;
    for (int i = x-1; i <= x+1; i++) {
        for (int j = y-1; j <= y+1; j++) {
            //Вохды за пределы массива
            if ((i < 0) || (i > GRID_SIZE-1) || (y < 0) || (i > GRID_SIZE-1))
                continue;
            //Не учитываем собсвенную клетку
            if ((i == x) && j == y)
                continue;
            if (arr[i][j] == DEAD)
                continue;
            if (arr[i][j] == ALIVE)
                aliveCnt++;
        }
    }
    return aliveCnt;
}

void printRectangle(unsigned int row, unsigned int col, bool color) {
    bool tmp = !color;
    int colour = (int) tmp;
    rectangle(result,
        Point(IMAGE_WIDTH * col, IMAGE_WIDTH * row),
        Point(IMAGE_WIDTH * col + IMAGE_WIDTH - 1,
              IMAGE_WIDTH * row + IMAGE_WIDTH - 1),
        Scalar(255 * colour, 255 * colour, 255 * colour),
        FILLED);
}

//По хорошему нужно было брать данные о первом поколении из массива. Но
//Как сделано, так сделано.
void printGosperGun(bool arr[GRID_SIZE][GRID_SIZE])
{
    //Левый квадрат
    printRectangle(4,0,true);
    printRectangle(4,1,true);
    printRectangle(5,0,true);
    printRectangle(5,1,true);
    arr[4][0] = ALIVE;
    arr[4][1] = ALIVE;
    arr[5][0] = ALIVE;
    arr[5][1] = ALIVE;
    //Правый квадрат
    printRectangle(2,34,true);
    printRectangle(2,35,true);
    printRectangle(3,34,true);
    printRectangle(3,35,true);
    arr[2][34] = ALIVE;
    arr[2][35] = ALIVE;
    arr[3][34] = ALIVE;
    arr[3][35] = ALIVE;
    //Штука слева
    printRectangle(2,12,true);
    arr[2][12] = ALIVE;
    printRectangle(2,13,true);
    arr[2][13] = ALIVE;
    printRectangle(3,11,true);
    arr[3][11] = ALIVE;
    printRectangle(3,15,true);
    arr[3][15] = ALIVE;
    printRectangle(4,10,true);
    arr[4][10] = ALIVE;
    printRectangle(4,16,true);
    arr[4][16] = ALIVE;
    printRectangle(5,10,true);
    arr[5][10] = ALIVE;
    printRectangle(5,14,true);
    arr[5][14] = ALIVE;
    printRectangle(5,16,true);
    arr[5][16] = ALIVE;
    printRectangle(5,17,true);
    arr[5][17] = ALIVE;
    printRectangle(6,10,true);
    arr[6][10] = ALIVE;
    printRectangle(6,16,true);
    arr[6][16] = ALIVE;
    printRectangle(7,11,true);
    arr[7][11] = ALIVE;
    printRectangle(7,15,true);
    arr[7][15] = ALIVE;
    printRectangle(8,12,true);
    arr[8][12] = ALIVE;
    printRectangle(8,13,true);
    arr[8][13] = ALIVE;
    //Штука справа
    printRectangle(0,24,true);
    arr[0][24] = ALIVE;
    printRectangle(1,22,true);
    arr[1][22] = ALIVE;
    printRectangle(1,24,true);
    arr[1][24] = ALIVE;
    printRectangle(2,20,true);
    arr[2][20] = ALIVE;
    printRectangle(2,21,true);
    arr[2][21] = ALIVE;
    printRectangle(3,20,true);
    arr[3][20] = ALIVE;
    printRectangle(3,21,true);
    arr[3][21] = ALIVE;
    printRectangle(4,20,true);
    arr[4][20] = ALIVE;
    printRectangle(4,21,true);
    arr[4][21] = ALIVE;
    printRectangle(5,22,true);
    arr[5][22] = ALIVE;
    printRectangle(5,24,true);
    arr[5][24] = ALIVE;
    printRectangle(6,24,true);
    arr[5][24] = ALIVE;
    printRectangle(6,24,true);
    arr[6][24] = ALIVE;
}
