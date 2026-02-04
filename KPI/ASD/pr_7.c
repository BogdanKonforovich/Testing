#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>

#define min 0
#define max 15

// Структура вузла
typedef struct Node {
    char data;
    struct Node* next;
} Node;

// Структура черги
typedef struct Queue {
    Node* front;
    Node* rear;
}Queue;

void initQueue(Queue* q);

int Per(Queue* q);

void enqueue (Queue* q, char sign);

void dequeue (Queue* q);

void print(Queue* q);

void Zav(Queue* q, Queue* n);

int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Queue q, n;
    initQueue(&q);
    initQueue(&n);
    int N, M;
    char el;
    printf("Введіть кількість елементів, які додаються до черги (від %d до %d)\n", min , max);
    scanf("%d", &N);
    printf("Введіть %d елементів, які додаються (використавши !)\n", N);
    for (int i = 0; i < N; i++){
        scanf(" %c", &el);
        enqueue (&q, el);
    }
    printf("Вигляд черги\n");
    print(&q);
    printf("Введіть кількість елементів, які віднімаються від черги (від %d до %d)\n", min , max);
    scanf("%d", &M);
    for(int i = 0; i < M; i++){
        dequeue(&q);
    }
    printf("Оновлений вигляд черги\n");
    print(&q);

    printf("Нова черга:\n");
    Zav(&q, &n);
    
    system("pause");
    return 0;
}

// Ініціалізація черги
void initQueue(Queue* q){
    q->front = NULL;
    q->rear = NULL;
}

// Перевірка на порожність
int Per(Queue* q){
    if (q->front == NULL){
        return 1;
    }else
    return 0;
}

// Додавання елемента
void enqueue (Queue* q, char sign){
    Node* now = (Node*)malloc(sizeof(Node));
    now->data = sign;
    now->next = NULL;

    if(Per(q)){
        q->front = q->rear = now;
    }else{
        q->rear->next = now;
        q->rear = now;
    }
}

// Видалення елемента
void dequeue (Queue* q){
    if(Per(q)){
        printf("Черга порожня, видалення неможливе!");
    } else{
        Node* temp = q->front;
        q->front = q->front->next;
        free(temp);
        if (q->front == NULL)
            q->rear = NULL;
    }
}

// Виведення всіх елементів черги
void print(Queue* q){
    Node* temp = q->front;
    int i = 0;
    while(temp){
        printf("%d символ: %c \n", i+1, temp->data);
        i++;
        temp = temp->next;
    }
}

void Zav(Queue* q, Queue* n){
    Node* temp = q->front;
    int j = 0;
    while (temp != NULL && temp->data != '!'){
        enqueue (n, temp->data);
        temp = temp->next;
        j++;
    }
    print(n);
    printf("Кількість знаків: %d\n", j);
}