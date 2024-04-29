#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

// Структура для хранения данных о точке доступа
typedef struct AccessPoint {
    int x;
    int y;
    int radius;
} AccessPoint;

// Функция для расчета силы сигнала в заданной точке
int calculateSignalStrength(AccessPoint *accessPoints, int numAccessPoints, int x, int y) {
    int minDistance = INT_MAX;
    int nearestAccessPointIndex = -1;

    // Перебираем все точки доступа
    for (int i = 0; i < numAccessPoints; i++) {
        // Рассчитываем расстояние до точки доступа
        int distance = sqrt(pow(x - accessPoints[i].x, 2) + pow(y - accessPoints[i].y, 2));

        // Обновляем ближайшую точку доступа и минимальное расстояние
        if (distance < minDistance) {
            minDistance = distance;
            nearestAccessPointIndex = i;
        }
    }

    // Рассчитываем силу сигнала
    int signalStrength = fmin(100, (100 * accessPoints[nearestAccessPointIndex].radius) / minDistance);

    return signalStrength;
}

int main() {
    // Запрашиваем размеры холла
    int n, m;
    printf("Введите размеры холла (n x m): ");
    scanf("%d %d", &n, &m);

    // Запрашиваем количество точек доступа
    int numAccessPoints;
    printf("Введите количество точек доступа: ");
    scanf("%d", &numAccessPoints);

    // Запрашиваем координаты и радиусы точек доступа
    AccessPoint accessPoints[numAccessPoints];
    for (int i = 0; i < numAccessPoints; i++) {
        printf("Введите координаты точки доступа %d (x, y): ", i + 1);
        scanf("%d %d", &accessPoints[i].x, &accessPoints[i].y);

        printf("Введите радиус точки доступа %d: ", i + 1);
        scanf("%d", &accessPoints[i].radius);
    }

    // Запрашиваем координаты точки, в которой нужно рассчитать силу сигнала
    int x, y;
    printf("Введите координаты точки, в которой нужно рассчитать силу сигнала (x, y): ");
    scanf("%d %d", &x, &y);

    // Рассчитываем силу сигнала
    int signalStrength = calculateSignalStrength(accessPoints, numAccessPoints, x, y);

    // Выводим результат
    printf("Сила сигнала в точке (%d, %d): %d%%\n", x, y, signalStrength);

    return 0;
}