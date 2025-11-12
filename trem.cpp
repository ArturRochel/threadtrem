#include "trem.h"
#include <QtCore>
#include <QSemaphore>
#include <QDebug>
#include <QDateTime>

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 150;
}


void Trem::setVelocidade(int velocidadeDoTrem) {
    if (velocidadeDoTrem < 0) velocidadeDoTrem = 0; // Na lógica de inversão do slide, caso a "velocidade" venha a ser negativa ele trava em 0
    if (velocidadeDoTrem > 200) velocidadeDoTrem = 200;  // Na lógica de inversão do slide, caso a "velocidade" venha a ser maior que 200, ele trava em 200
    this->velocidade = velocidadeDoTrem;
}

// Faz a logística de inverter o valor do slide e controalr a velocidade
int Trem::getDelay() const {
    if (velocidade <= 0)
        return -1; 
    return std::max(1, 201 - velocidade); 
}

// Atuliza visualmente a posição do trem na UI
void Trem::fazAndar() {
    emit updateGUI(ID, x, y);

    int delay = getDelay();

    if (delay < 0) {
        while (velocidade <= 0) {
            msleep(10); 
        }
    } else {
        msleep(delay); 
    }
}

// Saber quando um trem pegou ou liberou um mutex
void Trem::logSemaforo(QSemaphore &semaforo, const QString &nome, const QString &acao) {
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    qDebug().noquote()
        << "[" + timestamp + "]"
        << "Trem" << ID
        << acao << "o" << nome
        << "| Espaços disponíveis:" << semaforo.available();
}

// 07 mutex para controlar 12 regiões críticas 
std::mutex Trem::mtxTrecho01;
std::mutex Trem::mtxTrecho02;
std::mutex Trem::mtxTrecho03;
std::mutex Trem::mtxTrecho04;
std::mutex Trem::mtxTrecho05;
std::mutex Trem::mtxTrecho06;
std::mutex Trem::mtxTrecho07;
std::mutex Trem::mtxTrecho08;
std::mutex Trem::mtxTrecho09;
std::mutex Trem::mtxTrecho10;
std::mutex Trem::mtxTrecho11;
std::mutex Trem::mtxTrecho12;
std::mutex Trem::mtxTrecho13;

// Semáforos para controlar a malha interna
QSemaphore Trem::sema01(2);
QSemaphore Trem::sema02(2);
 

void Trem::run(){
    while(true){
        switch(ID){
            case 1: 
            {   
                std::unique_lock<std::mutex> lock01(mtxTrecho01, std::defer_lock);
                std::unique_lock<std::mutex> lock03(mtxTrecho03, std::defer_lock);
                std::unique_lock<std::mutex> lock02(mtxTrecho02, std::defer_lock);

                int contadorTrem01 = 0;
                while(y > 100) { // Está subindo o trecho01 em direção (100,100)
                    if(contadorTrem01 == 0){
                        lock01.lock();
                    }
                    y -= 20;
                    fazAndar();

                }

                while(x < 300) { // Está indo para a direita em direção (300, 100)
                    if(x == 260) {
                        lock03.lock();
                    }

                    x += 20;
                    fazAndar();
                }

                while(y < 300) { // Está indo para baixo em direção (300, 300)
                    if(y == 140) {
                        lock01.unlock();
                    }

                    if(y == 260) {
                        lock02.lock();
                    }

                    y += 20;
                    fazAndar();
                }

                while(x > 100) { // Está indo para esquerda em direção (100, 300)
                    if(x == 260) {
                        lock03.unlock();
                    }

                    if(x == 140) {
                        lock01.lock();
                        if(contadorTrem01 == 0) {
                            contadorTrem01++;
                        }
                    }
                    x -= 20;
                    fazAndar();
                }
                lock02.unlock();
                }
            break;
            case 2: //. Trem 2 
                {
                std::unique_lock<std::mutex> lock13(mtxTrecho13, std::defer_lock);
                std::unique_lock<std::mutex> lock02(mtxTrecho02, std::defer_lock);
                std::unique_lock<std::mutex> lock05(mtxTrecho05, std::defer_lock);
                std::unique_lock<std::mutex> lock11(mtxTrecho11, std::defer_lock); 
                std::unique_lock<std::mutex> lock12(mtxTrecho12, std::defer_lock);
                  
                int contatorTrem02 = 0;

                while(y > 300) { // Esta subindo em direção (100, 300)
                    if(contatorTrem02 == 0) {
                        lock13.lock();
                    }
                    if(y == 340) {
                        lock02.lock();
                    }

                    y -= 20;
                    fazAndar();
                }

                while(x < 300) { // Esta indo para a direita em direção a (300, 300) - Percorre apenas o trecho02
                    if(x == 140) {
                        lock13.unlock();
                    }

                    if(x == 260) {
                        lock05.lock();
                    }

                    x += 20;
                    fazAndar();
                }

                while(x < 400) { // Esta indo para a direita em direção a (400, 300) - Percorre apenas o trecho05
                    if(x == 340) {
                        lock02.unlock();
                    }

                    if(x == 360) {
                        lock11.lock();
                    }

                    x += 20;
                    fazAndar();
                }

                while(y < 500) { // Esta indo para baixo em direção a (400, 500)
                    if(y == 340) {
                        lock05.unlock();
                    }

                    if(y == 460) {
                        lock12.lock();
                    }

                    y += 20;
                    fazAndar();
                }

                while(x > 100) { // Esta indo para a esquerda em direção a (100, 500)
                    if(x == 360) {
                        lock11.unlock();
                    }

                    if(x == 140) {
                        if(contatorTrem02 == 0) {
                            contatorTrem02 ++;
                        }
                        lock13.lock();
                    }

                    x -= 20;
                    fazAndar();
                }
                }
            break;

        case 3: // Trem 3 - ROXO - (bloco inferior direito)
            {
                std::unique_lock<std::mutex> lock10(mtxTrecho10, std::defer_lock);
                std::unique_lock<std::mutex> lock11(mtxTrecho11, std::defer_lock);
                std::unique_lock<std::mutex> lock06(mtxTrecho06, std::defer_lock);
                std::unique_lock<std::mutex> lock09(mtxTrecho09, std::defer_lock);

                int contadorTrem03 = 0;
                
                while(y < 500) { // Esta indo para baixo em direção a (700, 500)
                    if(contadorTrem03 == 0) {
                        lock10.lock();
                    }
                    y += 20;
                    fazAndar();
                }

                while(x > 400) { // Esta indo para a esquerda em direção a (400, 500)
                    if( x == 440) {
                        lock11.lock();
                    }

                    x -= 20;
                    fazAndar();
                }

                while(y > 300) { // Esta indo para cima em direção a (400, 300)
                    if(y == 460) {
                        lock10.unlock();
                    }

                    if(y == 340) {
                        std::lock(lock06, lock09); // Bloquei o trecho06 e trecho09 para percorrê-lo de uma única vez
                    }

                    y -= 20;
                    fazAndar();
                }

                whilex(x < 500) { // Esta indo para a direita em direção a (500, 300) - Percorre apenas o trecho06
                    if(x == 440) {
                        lock11.unlock();
                    }

                    x += 20;
                    fazAndar();
                }

                while(x < 700) { // Esta indo para a direita em direção a (700, 300) - Percorre apenas o trecho09
                    if(x == 540) {
                        lock06.unlock();
                    }

                    if(x == 660) {
                        lock10.lock();
                        if(contadorTrem03 == 0) {
                            contadorTrem03++;
                        }
                    }

                    x += 20;
                    fazAndar();
                }
                lock09.unloack();
            }
        break;
        case 4: // Trem 4 - AZUL -(bloco superior direito)
            {   
                std::unique_lock<std::mutex> lock07(mtxTrecho07, std::defer_lock);
                std::unique_lock<std::mutex> lock09(mtxTrecho09, std::defer_lock);
                std::unique_lock<std::mutex> lock08(mtxTrecho08, std::defer_lock);

                int contadorTrem04 = 0;

                // O TREM NÃO COMEÇA AQUI
                while(x < 700) { // Está indo para a direita para (700, 100)
                    x += 20;
                    fazAndar();
                }
                
                // O TREM COMEÇA NESSE
                while(y < 300) { // Esta descendo em direção a (700, 300)
                    if(contadorTrem04 == 0) {
                        lock07.lock();
                    }
                    if(y == 260) {
                        lock09.lock();
                    }

                    y += 20;
                    fazAndar();
                }

                while(x > 500) { // Esta indo para a esquerda em direção a (500, 300)
                    if(x == 660) {
                        lock07.unlock();
                    }

                    if(x == 540) {
                        lock08.lock();
                    }

                    x -= 20;
                    fazAndar();
                }

                while(y > 100) { // Esta indo para cima em direção a (500, 100)
                    if(y == 260) {
                        lock09.unlock();
                    }

                    if(y == 140) {
                        if(contadorTrem04 == 0) {
                            contadorTrem04++;
                        }
                        lock07.lock();
                    }

                    y -= 20;
                    fazAndar();
                } 
                lock08.unlock();
            }
        break;
        case 5: // Trem 5 - VERMELHO -(bloco superior central)
            {
                std::unique_lock<std::mutex> lock04(mtxTrecho04, std::defer_lock);
                std::unique_lock<std::mutex> lock08(mtxTrecho08, std::defer_lock);
                std::unique_lock<std::mutex> lock06(mtxTrecho06, std::defer_lock);
                std::unique_lock<std::mutex> lock05(mtxTrecho05, std::defer_lock);
                std::unique_lock<std::mutex> lock03(mtxTrecho03, std::defer_lock);

                int contadorTrem05 = 0;

                while(x < 500) { // Esta indo para a direita em direção a (500, 100)
                    if(contadorTrem05 == 0) {
                        lock04.lock();
                    }
                    if(x == 460) {
                        lock08.lock();
                    }

                    x += 20;
                    fazAndar();
                }

                while(y < 300) { // Esta indo para baixo em direção a (500, 300)
                    if(y == 140) {
                        lock04.unlock();
                    }

                    if(y == 260) {
                        std::lock(lock06, lock05);
                    }

                    y += 20;
                    fazAndar();
                }

                while(x > 400) { // Esta indo para a esquerda em direção a (400, 300) - Percorre apenas o trecho06
                    if(x == 460) {
                        lock08.unlock();
                    }

                    x -= 20;
                    fazAndar();
                }

                while(x > 300) { // Esta indo para a esquerda em direção a (300, 300) - Percorre apenas o trecho05
                    if(x == 340) {
                        lock03.lock();
                    }

                    x -= 20;
                    fazAndar();
                }

                while(y > 100) { // Esta indo para cima em direção a (300, 100)
                    if(y == 260) {
                        lock05.unlock();
                    }

                    if(y == 140) {
                        lock04.lock();
                        if(contadorTrem05 == 0) {
                            contadorTrem05++;
                        }
                    }

                    y -= 20;
                    fazAndar();
                }
                lock03.unlock();
            }
        break;
       
case 6: // Trem 6 - PRETO (Anti-horário, conforme PDF )
    {
        // Declarações (os 4 trilhos externos)
        std::unique_lock<std::mutex> lockCima(mtxTrechoCima, std::defer_lock);
        std::unique_lock<std::mutex> lockDireita(mtxTrechoDireita, std::defer_lock);
        std::unique_lock<std::mutex> lockBaixo(mtxTrechoBaixo, std::defer_lock);
        std::unique_lock<std::mutex> lockEsquerda(mtxTrechoEsquerda, std::defer_lock);

        lockBaixo.lock();
        while(x < 700) {
            if(x == 660) {
                lockDireita.lock();
            }

            x += 20;
            fazAndar();
        }

        while(y > 100) {
            if(y == 460) {
                lockBaixo.unlock();
            }

            if(y == 140) {
                lockCima.lock();
            }

            y -= 20;
            fazAndar();
        }

        while(x > 100) {
            if(x == 660) {
                lockDireita.unlock();
            }

            if(x == 140) {
                lockEsquerda.lock();
            }

            x -= 20;
            fazAndar();
        }

        while(y < 500) {
            if(y == 140) {
                lockCima.unlock();
            }

            if(y == 460) {
                lockBaixo.lock();
            }

            y += 20;
            fazAndar();
        }
        lockEsquerda.unlock();
    }
    break;
        default:
            break;
        }
    }
}
