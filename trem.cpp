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

// 07 mutex para controlar 07 regiões críticas 
// Os mutexes estão na ordem de hierarquia que devem ser chamados
std::mutex Trem::mtxTrechoCima;
std::mutex Trem::mtxTrechoEsquerda;
std::mutex Trem::mtxTrechoBaixo;
std::mutex Trem::mtxTrechoDireita;
std::mutex Trem::mtxTrecho01;
std::mutex Trem::mtxTrecho02;
std::mutex Trem::mtxTrecho03;
std::mutex Trem::mtxTrecho04;
std::mutex Trem::mtxTrecho05;
std::mutex Trem::mtxTrecho06;
std::mutex Trem::mtxTrecho07;


 

void Trem::run(){
    while(true){
        switch(ID){
            case 1: 
            {   
                std::unique_lock<std::mutex> lockCima(mtxTrechoCima, std::defer_lock);
                std::unique_lock<std::mutex> lock01(mtxTrecho01, std::defer_lock);
                std::unique_lock<std::mutex> lock04(mtxTrecho04, std::defer_lock);
                std::unique_lock<std::mutex> lock03(mtxTrecho03, std::defer_lock);
                std::unique_lock<std::mutex> lockEsquerda(mtxTrechoEsquerda, std::defer_lock);
                
                lockCima.lock();
                while(x < 300) {
                    if(x == 260) {
                        lock01.lock();
                    }

                    x += 20;
                    fazAndar();
                }
                lockCima.unlock();
                
                while(y < 300) 
                {   
                    if (y == 140) { 
                        lock01.unlock(); 
                    }

                    if (y == 260) { 
                        std::lock(lock03, lock04);
                    } 

                    y += 20;
                    fazAndar();

                } 
                
                while(x > 100) {
                    if(x == 140) {
                        lockEsquerda.lock();
                        lock04.unlock();
                    }
                    x -= 20;
                    fazAndar();
                }

                while(y > 100) {
                    if(y == 260) {
                        lock03.unlock();
                    }

                    y -= 20;
                    fazAndar();
                }

                lockEsquerda.unlock();

            }
            break;
            case 2: //. Trem 2 
                {
                    std::unique_lock<std::mutex> lockBaixo(mtxTrechoBaixo, std::defer_lock);
                    std::unique_lock<std::mutex> lockEsquerda(mtxTrechoEsquerda, std::defer_lock);
                    std::unique_lock<std::mutex> lock03(mtxTrecho03, std::defer_lock);
                    std::unique_lock<std::mutex> lock04(mtxTrecho04, std::defer_lock);
                    std::unique_lock<std::mutex> lock07(mtxTrecho07, std::defer_lock);

                    std::lock(lockEsquerda, lockBaixo);
                    while(x > 100) {
                        x -= 20;
                        fazAndar();
                    }

                    while(y > 300) {
                        if(y == 460) {
                            lockBaixo.unlock();
                        }

                        if(y == 340) {
                            std::lock(lock03, lock04);
                        }

                        y -= 20;
                        fazAndar();
                    }

                    while(x < 400) {
                        if(x == 140) {
                            lockEsquerda.unlock();
                        }

                        if(x == 360) {
                            lock07.lock();
                            lock03.unlock();
                        }

                        x += 20;
                        fazAndar();
                    }

                    while(y < 500) {
                        if(y == 340) {
                            lock04.unlock();
                        }

                        if(y == 460) {
                            lockBaixo.lock();
                        }

                        y += 20;
                        fazAndar();
                    }
                    lock07.unlock();
                }
            break;

        case 3: // Trem 3 - ROXO - (bloco inferior direito)
            {
                std::unique_lock<std::mutex> lockDireita(mtxTrechoDireita, std::defer_lock);
                std::unique_lock<std::mutex> lockBaixo(mtxTrechoBaixo, std::defer_lock);
                std::unique_lock<std::mutex> lock07(mtxTrecho07, std::defer_lock);
                std::unique_lock<std::mutex> lock05(mtxTrecho05, std::defer_lock);
                std::unique_lock<std::mutex> lock06(mtxTrecho06, std::defer_lock);

                lockDireita.lock();
                while(y < 500) {
                    if(y == 460) {
                        lockBaixo.lock();
                    }

                    y += 20;
                    fazAndar();
                }

                while(x > 400) {
                    if(x == 660) {
                        lockDireita.unlock();
                    }

                    if(x == 440) {
                        lock07.lock();
                    }

                    x -= 20;
                    fazAndar();
                }

                while(y > 300) {
                    if(y == 360) {
                        lockBaixo.unlock();
                    }

                    if(y == 340) {
                        std::lock(lock05, lock06);
                    }

                    y -= 20;
                    fazAndar();
                }

                while(x < 700) {
                    if(x == 440) {
                        lock07.unlock();
                    }

                    if(x == 660) {
                        lock05.unlock();
                        lockDireita.lock();
                    }

                    x += 20;
                    fazAndar();
                }
                lock06.unlock();
            }
        break;
        case 4: // Trem 4 - AZUL -(bloco superior direito)
            {   
                std::unique_lock<std::mutex> lock02(mtxTrecho02, std::defer_lock);
                std::unique_lock<std::mutex> lockCima(mtxTrechoCima, std::defer_lock);
                std::unique_lock<std::mutex> lockDireita(mtxTrechoDireita, std::defer_lock);
                std::unique_lock<std::mutex> lock06(mtxTrecho06, std::defer_lock);
                std::unique_lock<std::mutex> lock05(mtxTrecho05, std::defer_lock);
                
                std::lock(lock02, lock06, lock05);
                while(y > 100) {
                    if(y == 140) {
                        lockCima.lock();
                    }

                    y -= 20;
                    fazAndar();
                }

                while(x < 700)  {
                    if(x == 540) {
                        lock02.unlock();
                    }

                    if(x == 660) {
                        lockDireita.lock();
                    }

                    x += 20;
                    fazAndar();
                }

                while(y < 300) {
                    if(y == 140) {
                        lockCima.unlock();
                    }

                    y += 20;
                    fazAndar();
                }

                while(x > 500) {
                    if(x == 660) {
                        lockDireita.unlock();
                    }

                    if(x == 540) {
                        lock02.lock();
                        lock05.unlock();
                    }

                    x -= 20;
                    fazAndar();
                }
                lock06.unlock();
                lock02.unlock();
            }
        break;
        case 5: // Trem 5 - VERMELHO -(bloco superior central)
            {
                std::unique_lock<std::mutex> lockCima(mtxTrechoCima, std::defer_lock);
                std::unique_lock<std::mutex> lock01(mtxTrecho01, std::defer_lock);
                std::unique_lock<std::mutex> lock02(mtxTrecho02, std::defer_lock);
                std::unique_lock<std::mutex> lock04(mtxTrecho04, std::defer_lock);
                std::unique_lock<std::mutex> lock05(mtxTrecho05, std::defer_lock);
                std::unique_lock<std::mutex> lock06(mtxTrecho06, std::defer_lock);

                std::lock(lockCima, lock01, lock02, lock04, lock05, lock06);
                
                // (Começa em (300,100), vai para (500,100))
                // --- TRECHO 1: TRILHO Cima ---
                while(x < 500) {
                    x += 20;
                    fazAndar();
                }
                // (Chegou em (500,100))
                lockCima.unlock(); // Libera o Cima (não precisa mais)

                // --- TRECHO 2: Trilho 02 (vertical) ---
                // (Começa em (500,100), vai para (500,300))
                while(y < 300) { 
                    y += 20; 
                    fazAndar(); 
                } 

                // --- TRECHO 3: Trilho 06 (horizontal) ---
                // (Começa em (500,300), vai para (400,300))
                // CORREÇÃO: Este loop faltava no seu código
                while(x > 400) { 
                    x -= 20; 
                    fazAndar(); 
                } 

                // --- TRECHO 4: Trilho 05 (horizontal) ---
                // (Começa em (400,300), vai para (300,300))
                // CORREÇÃO: Este loop faltava no seu código
                while(x > 300) { 
                    x -= 20; 
                    fazAndar(); 
                } 

                // --- TRECHO 5: Trilho 01 (vertical) ---
                // (Começa em (300,300), vai para (300,100))
                while(y > 100) { 
                    y -= 20; 
                    fazAndar(); 
                } 
                lock01.unlock();
                lock02.unlock();
                lock04.unlock();
                lock05.unlock();
                lock06.unlock();
            }
        break;
       
case 6: // Trem 6 - PRETO (Anti-horário, conforme PDF )
    {
        // Declarações (os 4 trilhos externos)
                std::unique_lock<std::mutex> lockCima(mtxTrechoCima, std::defer_lock);
                std::unique_lock<std::mutex> lockDireita(mtxTrechoDireita, std::defer_lock);
                std::unique_lock<std::mutex> lockBaixo(mtxTrechoBaixo, std::defer_lock);
                std::unique_lock<std::mutex> lockEsquerda(mtxTrechoEsquerda, std::defer_lock);

                lockEsquerda.lock();
                while(y < 500) {
                    if( y == 460) {
                        lockBaixo.lock();
                    }
                    y += 20;
                    fazAndar();
                }

                while(x < 700) {
                    if(x == 660) {
                        lockDireita.lock();
                    }
                    x += 20;
                    fazAndar();
                }

                lockBaixo.unlock();

                while(y > 100) {
                    if(y == 140) {
                        lockCima.lock();
                    }
                    y -= 20;
                    fazAndar();
                }

                lockDireita.unlock();

                while(x > 100) {
                    x -= 20;
                    fazAndar();
                }

                lockCima.unlock();
    }
    break;
        default:
            break;
        }
    }
}
