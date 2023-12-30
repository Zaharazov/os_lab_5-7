#include <iostream>

#include "ServerNode.h"
#include <sys/wait.h>
#include "SpringBootApplication.h"

void child(int sig) 
{
    pid_t pid;
    pid = wait(nullptr); // Ждем завершение дочернего процесса
}

int main() 
{
    signal(SIGCHLD, child); // Перехват неожиданных сигналов или событий (номер сигнала, функция обработки сигнала)
    SpringBootApplication app; 
    app.run(); // Запуск приложения
}
