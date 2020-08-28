/*! \file    main.c
 *  \brief   Processing queued jobs.
 *
 *  \details Задача об обедающих философах, вариант 2.
 *  Входные данные - длительность приёма пищи философами.
 *  Если ввести значение 1(длительность приёма пищи философом)
 *  то очередь будет убывать с оптимальной скоростью.
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
#include <stdbool.h>

#define COUNT_OF_FORKS 5
#define COUNT_OF_PHILOSOPHERS 5
#define MAX_LENGTH 20
#define ASCII_CONST 48
#define NS_IN_SEC 1000000000
#define NEXT_DIGIT 10
#define INFINITY_LOOP while(1)
#define ERROR -1
#define RANDOM_ERROR 322

// Инициализация мьютекса и объявление семафора.
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
sem_t g_freePlacesCount;
pthread_cond_t g_signal;

/*! \struct queue
 *  \brief Структура, с помощью которой формируется очередь.
 */
struct queue
        {
    /*! Ссылка на следующий элемент в очереди. */
    struct queue* next;
    /*! Номер философа данной позиции. */
    int number;
};


/*! \struct fork
 *  \brief Структура, отвечающая за вилки.
 */
struct fork
{
    /*! Состояние вилки. */
    int isUsing;
    /*! Номер вилки. */
    int number;
};

struct queue* currentQueue; // Очередь, в порядке которой обедают философы.

/*! \struct philosopher
 *  \brief Структура, с помощью которой передаются данные
 *  потокам-философам.
 */
struct philosopher
{
    /*! Длительность временного промежутка, за который обедают философы.*/
    int eatTime;
    /*! Номер философа, передающийся в поток.*/
    int number;
    /*! Естл ли философю*/
    bool isEatingPhilosopher;
    /*! Поле, отвечающее за левую вилку философа*/
    struct fork* left;
    /*! Поле, отвечающее за правую   вилку философа*/
    struct fork* right;
};

/*! \brief Функция, обрабатывающая ввод.
 *  @param parameters Строка считанная с клавиатуры.
 *  @return number Число, содержащееся в строке, либо ошибка.
 */
int InputChecker(char* strForCheck)
{
    int number = 0;

    for (unsigned long i = 0; i < strlen(strForCheck); i++)
    {
        if (strForCheck[i] == '0' || strForCheck[i] == '1' ||
        strForCheck[i] == '2' || strForCheck[i] == '3' ||
        strForCheck[i] == '4' || strForCheck[i] == '5' ||
        strForCheck[i] == '6' || strForCheck[i] == '7' ||
        strForCheck[i] == '8' || strForCheck[i] == '9') number =
                number * NEXT_DIGIT + (strForCheck[i] - ASCII_CONST);
        else
            return ERROR;
    }

    if (number == 0) return ERROR;

    return number;
}

/*! \brief Поток, описывающий поведение философов.
 *  @param parameters Параметр потока типа void*, в котором содержится
 *  структура, содержащая номер философа и длительность приёма им пищи.
 *  @return Нулевой указатель.
 */
void* CallPhilosopher(void* parameters)
{
    struct philosopher* currentPhilosopher =
            (struct philosopher *) parameters;

    struct timespec tw;
    struct timespec tr;
    tw.tv_sec = currentPhilosopher->eatTime;
    struct queue* temp;

    INFINITY_LOOP
    {
        pthread_mutex_lock(&mtx);

        if (currentQueue == NULL) // Проверяем на наличие очереди.
        {
            pthread_mutex_unlock(&mtx);
            continue;
        }

        /* Проверяем, совпадает ли номер философа(данного потока)
        с тем, что первый в очереди. */
        if (currentQueue->number == currentPhilosopher->number)
        {

            if(currentPhilosopher->left->isUsing == 1 ||
                currentPhilosopher->right->isUsing == 1)
                pthread_cond_wait(&g_signal, &mtx);
            sem_wait(&g_freePlacesCount); // Используя семафор для разделения
            sem_wait(&g_freePlacesCount); // вилок, отправляем философа кушать

            currentPhilosopher->left->isUsing = 1;
            printf("Философ %d взял вилку %d.\n", currentPhilosopher->number,
                    currentPhilosopher->left->number);
            currentPhilosopher->right->isUsing = 1;
            printf("Философ %d взял вилку %d.\n", currentPhilosopher->number,
                    currentPhilosopher->right->number);
            temp = currentQueue;

            /* Условие, которое удаляет
            текущего философа из очереди. */
            if (currentQueue->next != NULL)
            {
                currentQueue = currentQueue->next;
                free(temp);
            }
            else
            {
                currentQueue = NULL;
                free(temp);
            }

            pthread_mutex_unlock(&mtx);

            printf("Философ %d кушает.\n",
                    currentPhilosopher->number);

            nanosleep(&tw, &tr);

            printf("Философ %d поел.\n",
                    currentPhilosopher->number);

            pthread_mutex_lock(&mtx);
            currentPhilosopher->left->isUsing = 0;
            printf("Философ %d положил вилку %d.\n", currentPhilosopher->number,
                   currentPhilosopher->left->number);
            currentPhilosopher->right->isUsing = 0;
            printf("Философ %d положил вилку %d.\n", currentPhilosopher->number,
                   currentPhilosopher->right->number);
            pthread_mutex_unlock(&mtx);

            pthread_cond_signal(&g_signal);
            sem_post(&g_freePlacesCount); // Освобождаем вилки
            sem_post(&g_freePlacesCount);
        } else
            pthread_mutex_unlock(&mtx);
    }

    return NULL;

}

int main()
{
    // Инициализация семафора.
    sem_init(&g_freePlacesCount, 0, COUNT_OF_FORKS);

    int eatTime = -1;
    printf("Задайте временной промежуток в секундах, "
           "в течении которого философы будут обедать: ");

    //Считывание временного интервала для поедания еды.
    char input[MAX_LENGTH];
    while (1)
    {
        scanf("%s", input);
        eatTime = InputChecker(input);
        if (eatTime == -1)
            printf("Введены некорректные данные, исправьте, "
                   "пожалуйста: ");
        else break;
    }

    pthread_t philosopher1Id;
    pthread_t philosopher2Id;
    pthread_t philosopher3Id;
    pthread_t philosopher4Id;
    pthread_t philosopher5Id;

    struct fork fork1 = {0, 1};
    struct fork fork2 = {0, 2};
    struct fork fork3 = {0, 3};
    struct fork fork4 = {0, 4};
    struct fork fork5 = {0, 5};

    struct philosopher args1 = {eatTime, 1, 0,
            &fork5, &fork1};
    struct philosopher args2 = {eatTime, 2, 0,
            &fork1, &fork2};
    struct philosopher args3 = {eatTime, 3, 0,
            &fork2, &fork3};
    struct philosopher args4 = {eatTime, 4, 0,
            &fork3, &fork4};
    struct philosopher args5 = {eatTime, 5, 0,
            &fork4, &fork5};

    pthread_create(&philosopher1Id, NULL, &CallPhilosopher,
                   &args1);
    pthread_create(&philosopher2Id, NULL, &CallPhilosopher,
                   &args2);
    pthread_create(&philosopher3Id, NULL, &CallPhilosopher,
                   &args3);
    pthread_create(&philosopher4Id, NULL, &CallPhilosopher,
                   &args4);
    pthread_create(&philosopher5Id, NULL, &CallPhilosopher,
                   &args5);

    srand(time(0));
    struct timespec tw;
    tw.tv_sec = 0;
    struct timespec tr;

    INFINITY_LOOP // Цикл, который формирует очередь случайным образом.
    { // Интервал добавления философов: 0-1 с.

        if (currentQueue != NULL)
        {

            pthread_mutex_lock(&mtx);
            struct queue* temp;
            struct queue* temp2 = currentQueue;
            temp = (struct queue*) malloc(sizeof (struct queue));

            temp->number = rand() % COUNT_OF_PHILOSOPHERS + 1;

            if (temp2 == NULL)
            {
                printf("Текущая очередь пуста!\n");
                pthread_mutex_unlock(&mtx);
                continue;
            }

            while (temp2->next != NULL)
                temp2 = temp2->next;
            temp2->next = temp;

            temp2 = currentQueue;

            printf("Текущая очередь(->): ");
            while (temp2->next != NULL)
            {
                printf("%d ", temp2->number);
                temp2 = temp2->next;
            }
            printf("%d\n", temp2->number); // Пометка начала очереди.
            pthread_mutex_unlock(&mtx);

            tw.tv_nsec = rand() % NS_IN_SEC; // Случайный временной
            // промежуток(0-1с), отвечающий за задержку перед появлением
            // следующего элемента в очереди.
            nanosleep(&tw, &tr);

        }
        else
        {
            pthread_mutex_lock(&mtx);
            currentQueue = (struct queue*) malloc(sizeof (struct queue));
            currentQueue->number = rand() % COUNT_OF_PHILOSOPHERS + 1;
            pthread_mutex_unlock(&mtx);
        }

        if(eatTime == RANDOM_ERROR) break;

    }

    pthread_join(philosopher1Id, NULL);
    pthread_join(philosopher2Id, NULL);
    pthread_join(philosopher3Id, NULL);
    pthread_join(philosopher4Id, NULL);
    pthread_join(philosopher5Id, NULL);

    struct queue* temp;
    if (currentQueue != NULL)
    {
        if(currentQueue->next != NULL)
        {
            while(currentQueue->next != NULL)
            {
                temp = currentQueue;
                currentQueue = currentQueue->next;
                free(temp);
            }
        }
    }
    free(currentQueue);

    return 0;
}
