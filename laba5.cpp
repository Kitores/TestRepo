#include <graphics.h>     // Библиотека для работы с графикой
#include <stdlib.h>       // Для функций задержки
#include <time.h>         // Для генерации случайных чисел
#include <dos.h>          // Для функции delay

#define DELAY_TIME 200    // Время задержки в миллисекундах

// Прототип функции delay
void delay(unsigned int milliseconds);

int main() {
    int gd = DETECT, gm;  // Режим графики и драйвер
    int xCenter = 320;    // Координаты центра эллипса
    int yCenter = 240;
    int xRadius = 150;    // Радиусы эллипса
    int yRadius = 75;

    // Инициализируем графику
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI"); 

    srand((unsigned) time(NULL));    // Инициализация генератора случайных чисел

    while (1) {
        // Генерируем случайный цвет
        int color = rand() % 15 + 1;  // От 1 до 16 (цвета BGI)
        
        // Рисуем эллипс заданным цветом
        setcolor(color);
        ellipse(xCenter, yCenter, 0, 360, xRadius, yRadius);

        // Ожидаем некоторое время
        delay(DELAY_TIME);

        // Стереть предыдущий эллипс черным цветом
        setcolor(BLACK);
        ellipse(xCenter, yCenter, 0, 360, xRadius, yRadius);
    }

    // Закрываем графический режим
    closegraph();

    return 0;
}

// Реализация функции delay
void delay(unsigned int milliseconds) {
    clock_t start_time = clock();
    while ((clock() - start_time) * 1000 / CLOCKS_PER_SEC < milliseconds);
}