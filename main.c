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

    if (nearestAccessPointIndex == -1) {
        printf("Не удалось найти ближайшую точку доступа.\n");
        return -1;
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

    // Проверяем корректность ввода размеров холла
    if (n <= 0 || m <= 0) {
        printf("Размеры холла должны быть положительными.\n");
        return 1;
    }

    // Запрашиваем количество точек доступа
    int numAccessPoints;
    printf("Введите количество точек доступа: ");
    scanf("%d", &numAccessPoints);

    // Проверяем корректность ввода
    if (numAccessPoints <= 0) {
        printf("Количество точек доступа должно быть положительным.\n");
        return 1;
    }

    // Запрашиваем координаты и радиусы точек доступа
    AccessPoint accessPoints[numAccessPoints];
    for (int i = 0; i < numAccessPoints; i++) {
        printf("Введите координаты точки доступа %d (x, y): ", i + 1);
        scanf("%d %d", &accessPoints[i].x, &accessPoints[i].y);

        // Проверяем корректность ввода координат точек доступа
        if (accessPoints[i].x < 0 || accessPoints[i].x > n || accessPoints[i].y < 0 || accessPoints[i].y > m) {
            printf("Координаты точки доступа %d должны находиться в пределах холла.\n", i + 1);
            return 1;
        }

        printf("Введите радиус точки доступа %d: ", i + 1);
        scanf("%d", &accessPoints[i].radius);

        // Проверяем корректность ввода
        if (accessPoints[i].radius <= 0) {
            printf("Радиус точки доступа должен быть положительным.\n");
            return 1;
        }
    }

    // Запрашиваем координаты точки, в которой нужно рассчитать силу сигнала
    int x, y;
    printf("Введите координаты точки, в которой нужно рассчитать силу сигнала (x, y): ");
    scanf("%d %d", &x, &y);

    // Проверяем корректность ввода
    if (x < 0 || x > n || y < 0 || y > m) {
        printf("Координаты точки должны находиться в пределах холла.\n");
        return 1;
    }

    // Рассчитываем силу сигнала
    int signalStrength = calculateSignalStrength(accessPoints, numAccessPoints, x, y);

    if (signalStrength == -1) {
        return 1;
    }

    // Выводим результат
    printf("Сила сигнала в точке (%d, %d): %d%%\n", x, y, signalStrength);

    return 0;
}
