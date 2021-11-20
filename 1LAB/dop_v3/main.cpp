#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define DEALY 100

#define ALIVE true
#define DEAD false

const int WINDOW_SIZE = 1000;

Mat result;

/*Number of rows/cols of grid*/
const int GRID_NUMBER = 100;

const int SQUARE_WIDTH = (int)WINDOW_SIZE / GRID_NUMBER;

void print_rectangle(unsigned int row, unsigned int col, bool color);

void printGosperGun(bool arr[GRID_NUMBER][GRID_NUMBER]);

int aliveAround(bool arr[GRID_NUMBER][GRID_NUMBER], int x, int y);

void checkAndPrint(bool cur[GRID_NUMBER][GRID_NUMBER],
                   bool next[GRID_NUMBER][GRID_NUMBER]);

int main()
{
    result = cv::Mat::zeros(WINDOW_SIZE, WINDOW_SIZE, CV_32F);

    bool arr1[GRID_NUMBER][GRID_NUMBER] = {{DEAD}};
    bool arr2[GRID_NUMBER][GRID_NUMBER] = {{DEAD}};

    bool (*curptr)[GRID_NUMBER] = arr1;
    bool (*nextptr)[GRID_NUMBER] = arr2;
    bool (*tempptr)[GRID_NUMBER];

    printGosperGun(arr1);

    while (true)
    {
        checkAndPrint(curptr, nextptr);
        imshow("press ESC to stop", result);

        tempptr = curptr;
        curptr = nextptr;
        nextptr = tempptr;

        if (waitKey(DEALY) == 27)
            break;
    }
}

void checkAndPrint(bool cur[GRID_NUMBER][GRID_NUMBER],
                   bool next[GRID_NUMBER][GRID_NUMBER]) {
    for (int i = 0; i < GRID_NUMBER; i++) {
        for (int j = 0; j < GRID_NUMBER; j++) {
            next[i][j] = DEAD;
            if (cur[i][j] == ALIVE) {
                if (aliveAround(cur, i, j) == 2 || aliveAround(cur, i, j) == 3) {
                    next[i][j] = ALIVE;
                    print_rectangle(i, j, ALIVE);
                }
                else {
                    next[i][j] = DEAD;
                    print_rectangle(i, j, DEAD);
                }
            }
            if (cur[i][j] == DEAD) {
                if (aliveAround(cur, i, j) == 3)
                {
                    next[i][j] = ALIVE;
                    print_rectangle(i, j, ALIVE);
                }
            }
        }
    }
}

int aliveAround(bool arr[GRID_NUMBER][GRID_NUMBER], int x, int y) {
    int aliveCnt = 0;
    for (int i = x-1; i <= x+1; i++) {
        for (int j = y-1; j <= y+1; j++) {
            if ((i < 0) || (i > GRID_NUMBER-1) || (y < 0) || (i > GRID_NUMBER-1))
                continue;
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

void print_rectangle(unsigned int row, unsigned int col, bool color) {
    int colour = (int) color;
    rectangle(result,
        Point(SQUARE_WIDTH * col, SQUARE_WIDTH * row),
        Point(SQUARE_WIDTH * col +SQUARE_WIDTH - 1,
            SQUARE_WIDTH * row + SQUARE_WIDTH - 1),
        Scalar(255 * colour, 255 * colour, 255 * colour),
        FILLED);
}

void printGosperGun(bool arr[GRID_NUMBER][GRID_NUMBER])
{
    //Левый квадрат
    print_rectangle(4,0,true);
    print_rectangle(4,1,true);
    print_rectangle(5,0,true);
    print_rectangle(5,1,true);
    arr[4][0] = ALIVE;
    arr[4][1] = ALIVE;
    arr[5][0] = ALIVE;
    arr[5][1] = ALIVE;
    //Правый квадрат
    print_rectangle(2,34,true);
    print_rectangle(2,35,true);
    print_rectangle(3,34,true);
    print_rectangle(3,35,true);
    arr[2][34] = ALIVE;
    arr[2][35] = ALIVE;
    arr[3][34] = ALIVE;
    arr[3][35] = ALIVE;
    //Штука слева
    print_rectangle(2,12,true);
    arr[2][12] = ALIVE;
    print_rectangle(2,13,true);
    arr[2][13] = ALIVE;
    print_rectangle(3,11,true);
    arr[3][11] = ALIVE;
    print_rectangle(3,15,true);
    arr[3][15] = ALIVE;
    print_rectangle(4,10,true);
    arr[4][10] = ALIVE;
    print_rectangle(4,16,true);
    arr[4][16] = ALIVE;
    print_rectangle(5,10,true);
    arr[5][10] = ALIVE;
    print_rectangle(5,14,true);
    arr[5][14] = ALIVE;
    print_rectangle(5,16,true);
    arr[5][16] = ALIVE;
    print_rectangle(5,17,true);
    arr[5][17] = ALIVE;
    print_rectangle(6,10,true);
    arr[6][10] = ALIVE;
    print_rectangle(6,16,true);
    arr[6][16] = ALIVE;
    print_rectangle(7,11,true);
    arr[7][11] = ALIVE;
    print_rectangle(7,15,true);
    arr[7][15] = ALIVE;
    print_rectangle(8,12,true);
    arr[8][12] = ALIVE;
    print_rectangle(8,13,true);
    arr[8][13] = ALIVE;
    //Штука справа
    print_rectangle(0,24,true);
    arr[0][24] = ALIVE;
    print_rectangle(1,22,true);
    arr[1][22] = ALIVE;
    print_rectangle(1,24,true);
    arr[1][24] = ALIVE;
    print_rectangle(2,20,true);
    arr[2][20] = ALIVE;
    print_rectangle(2,21,true);
    arr[2][21] = ALIVE;
    print_rectangle(3,20,true);
    arr[3][20] = ALIVE;
    print_rectangle(3,21,true);
    arr[3][21] = ALIVE;
    print_rectangle(4,20,true);
    arr[4][20] = ALIVE;
    print_rectangle(4,21,true);
    arr[4][21] = ALIVE;
    print_rectangle(5,22,true);
    arr[5][22] = ALIVE;
    print_rectangle(5,24,true);
    arr[5][24] = ALIVE;
    print_rectangle(6,24,true);
    arr[5][24] = ALIVE;
    print_rectangle(6,24,true);
    arr[6][24] = ALIVE;
}
