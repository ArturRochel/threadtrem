#include "trem.h"
#include <QtCore>

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

int Trem::getDelay() const {
    if (velocidade <= 0)
        return -1; // valor especial que indica "trem parado"
    return std::max(1, 201 - velocidade); // inversão: quanto maior a velocidade, menor o delay
}

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
 

void Trem::run(){
    while(true){
        switch(ID){
            
            case 1: { // . Trem 1
            static bool trecho01Reservado = false;

            if (x == 100 && y > 100) {
                if (!trecho01Reservado) {
                    mtxTrecho01.lock();
                    trecho01Reservado = true;
                }

                while (y > 100) {
                    y -= 20;
                    fazAndar();
                }

                while (x < 260) {
                    x += 20;
                    fazAndar();
                }

                mtxTrecho03.lock();

                while (x < 300) {
                    x += 20;
                    fazAndar();
                }

                while (y < 140) {
                    y += 20;
                    fazAndar();
                }

                mtxTrecho01.unlock();
                trecho01Reservado = false;
            }
            else if (x == 300 && y < 300) {
                while (y < 260) {
                    y += 20;
                    fazAndar();
                }
                mtxTrecho02.lock(); 

                while (y < 300) {
                    y += 20;
                    fazAndar();
                }

                while (x > 280) {
                    x -= 20;
                    fazAndar();
                }

                mtxTrecho03.unlock();
            }

            else if (y == 300 && x > 100) {
                while (x > 140) {
                    x -= 20;
                    fazAndar();
                }

                if (!trecho01Reservado) {
                    mtxTrecho01.lock();
                    trecho01Reservado = true;
                }

                while (x > 100) {
                    x -= 20;
                    fazAndar();
                }

                while (y > 260) {
                    y -= 20;
                    fazAndar();
                }

                mtxTrecho02.unlock();
            }

            break;
        }



            case 2: //. Trem 2 
                static bool trecho12Reservado = false;
                if (y == 500 && x > 100) { // movimenta para esquerda
                    
                    if (!trecho12Reservado) {
                        mtxTrecho12.lock();
                        trecho12Reservado = true;
                    }

                    while(x > 100){
                        x -= 20;
                        fazAndar();
                    }
                    while(y > 340){
                        y -= 20;
                        fazAndar();
                    }

                    mtxTrecho02.lock();

                    while(y > 300){ // movimenta para cima
                        y -= 20;
                        fazAndar();
                    }

                    while(x < 140){
                        x += 20;
                        fazAndar();
                    }

                    mtxTrecho12.unlock();
                    trecho12Reservado = false;

                } else if(y == 300 && x < 400) { // movimenta para a direita
                    while(x < 260){
                        x += 20;
                        fazAndar();
                    }

                    mtxTrecho05.lock();

                    while(x < 340){
                        x += 20;
                        fazAndar();
                    }

                    mtxTrecho02.unlock();

                    while(x < 360){
                        x += 20;
                        fazAndar();
                    }

                    mtxTrecho11.lock();

                    while(x < 400){
                        x += 20;
                        fazAndar();
                    }
                    while(y < 340){
                        y += 20;
                        fazAndar();
                    }

                    mtxTrecho05.unlock();

                } else if (x == 400 && y < 500) { // movimenta para baixo
                    while(y < 460){
                        y += 20;
                        fazAndar();
                    }

                    if (!trecho12Reservado) {
                        mtxTrecho12.lock();
                        trecho12Reservado = true;
                    }


                    while(y < 500){
                        y += 20;
                        fazAndar();
                    }
                    while(x > 360){
                        x -= 20;
                        fazAndar();
                    }

                    mtxTrecho11.unlock();
                }
            break;

        case 3: // Trem 3 - ROXO - (bloco inferior direito)
            static bool trecho06Reservado = false;
            if (y == 300 && x < 700) { // movimenta para a direita

                if (!trecho06Reservado) {
                    mtxTrecho06.lock();
                    trecho06Reservado = true;
                }

                while(x < 460){
                    x += 20;
                    fazAndar();
                }

                mtxTrecho09.lock();

                while(x < 540){
                    x += 20;
                    fazAndar();
                }

                mtxTrecho06.unlock(); /////////////////////////////////////////
                trecho06Reservado = false;

                while(x < 660){
                    x += 20;
                    fazAndar();
                }

                mtxTrecho10.lock();

                while(x < 700){
                    x += 20;
                    fazAndar();
                }
                while(y < 340){
                    y += 20;
                    fazAndar();
                }

                mtxTrecho09.unlock();


            } else if (x == 700 && y < 500) { // movimenta para baixo
                while(y < 500){
                    y += 20;
                    fazAndar();
                }
                while(x > 440){
                    x -= 20;
                    fazAndar();
                }

                mtxTrecho11.lock();

                while(x > 400){
                    x -= 20;
                    fazAndar();
                }

                while(y > 460){
                    y -= 20;
                    fazAndar();
                }

                mtxTrecho10.unlock();

            } else { // x == 400 && y > 300 // movimenta para cima

                while(y > 340){
                    y -= 20;
                    fazAndar();
                }

                if (!trecho06Reservado) {
                    mtxTrecho06.lock();
                    trecho06Reservado = true;
                }

                while(y > 300){
                    y -= 20;
                    fazAndar();
                }

                while(x < 440){
                    x += 20;
                    fazAndar();
                }

                mtxTrecho11.unlock();
            }
            break;

        case 4: // Trem 4 - AZUL -(bloco superior direito)
            if (y == 100 && x < 700) { // movimenta para a direita
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho07); // Mutex para proteger trecho 07
                while(x < 700){
                    x += 20;
                    emit updateGUI(ID, x, y);
                    int delay = getDelay();
                    if (delay < 0) {
                        // Trem parado — congela mantendo posição e mutexes
                        while (velocidade <= 0) {
                            msleep(10); // dorme um pouquinho, só pra não travar a CPU
                        }
                    } else {
                        msleep(delay); // anda normalmente conforme a "velocidade"
                    }
                }
                while(y < 300){
                    y += 20; // movimenta para baixo
                    emit updateGUI(ID, x, y);
                    int delay = getDelay();
                    if (delay < 0) {
                        // Trem parado — congela mantendo posição e mutexes
                        while (velocidade <= 0) {
                            msleep(10); // dorme um pouquinho, só pra não travar a CPU
                        }
                    } else {
                        msleep(delay); // anda normalmente conforme a "velocidade"
                    }
                }
            } else if (y == 300 && x > 500) { // movimenta para esquerda
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho09); // Mutex para proteger trecho 09
                while(x > 500){
                    x -= 20;
                    emit updateGUI(ID, x, y);
                    int delay = getDelay();
                    if (delay < 0) {
                        // Trem parado — congela mantendo posição e mutexes
                        while (velocidade <= 0) {
                            msleep(10); // dorme um pouquinho, só pra não travar a CPU
                        }
                    } else {
                        msleep(delay); // anda normalmente conforme a "velocidade"
                    }
                }
            } else { // x == 500 && y > 100 // movimenta para cima
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho08); // Mutex para proteger trecho 08
                while(y > 100){
                    y -= 20;
                    emit updateGUI(ID, x, y);
                    int delay = getDelay();
                    if (delay < 0) {
                        // Trem parado — congela mantendo posição e mutexes
                        while (velocidade <= 0) {
                            msleep(10); // dorme um pouquinho, só pra não travar a CPU
                        }
                    } else {
                        msleep(delay); // anda normalmente conforme a "velocidade"
                    }
                }
            }
            break;

        case 5: // Trem 5 - VERMELHO -(bloco superior central)
            if (y == 100 && x < 500) { // movimenta para a direita
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho04); // Mutex para proteger trecho 04
                while(x < 500){
                    x += 20;
                    emit updateGUI(ID, x, y);
                    int delay = getDelay();
                    if (delay < 0) {
                        // Trem parado — congela mantendo posição e mutexes
                        while (velocidade <= 0) {
                            msleep(10); // dorme um pouquinho, só pra não travar a CPU
                        }
                    } else {
                        msleep(delay); // anda normalmente conforme a "velocidade"
                    }

                }
            } else if (x == 500 && y < 300) { // movimenta para baixo
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho08); // Mutex para proteger trecho 08
                while(y < 300){
                    y += 20;
                    emit updateGUI(ID, x, y);
                    int delay = getDelay();
                    if (delay < 0) {
                        // Trem parado — congela mantendo posição e mutexes
                        while (velocidade <= 0) {
                            msleep(10); // dorme um pouquinho, só pra não travar a CPU
                        }
                    } else {
                        msleep(delay); // anda normalmente conforme a "velocidade"
                    }

                }
            } else if (y == 300 && x > 300) { // movimenta para esquerda
               std::unique_lock<std::mutex> lock(Trem::mtxTrecho06, std::defer_lock); // Mutex para proteger trecho 06. Não trava ainda
               lock.lock();
                while(x > 300){
                    x -= 20;
                    emit updateGUI(ID, x, y);
                    int delay = getDelay();
                    if (delay < 0) {
                        // Trem parado — congela mantendo posição e mutexes
                        while (velocidade <= 0) {
                            msleep(10); // dorme um pouquinho, só pra não travar a CPU
                        }
                    } else {
                        msleep(delay); // anda normalmente conforme a "velocidade"
                    }

                    if(x == 400){
                        break;
                    }
                }
                lock.unlock();
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho05); // Mutex para proteger trecho 05

                while(x > 300){
                    x -= 20;
                    emit updateGUI(ID, x, y);
                    int delay = getDelay();
                    if (delay < 0) {
                        // Trem parado — congela mantendo posição e mutexes
                        while (velocidade <= 0) {
                            msleep(10); // dorme um pouquinho, só pra não travar a CPU
                        }
                    } else {
                        msleep(delay); // anda normalmente conforme a "velocidade"
                    }
                }
            } else { // x == 300 && y > 100 // movimenta para cima
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho03); // Mutex para proteger trecho 03
                while(y > 100){
                    y -= 20;
                    emit updateGUI(ID, x, y);
                    int delay = getDelay();
                    if (delay < 0) {
                        // Trem parado — congela mantendo posição e mutexes
                        while (velocidade <= 0) {
                            msleep(10); // dorme um pouquinho, só pra não travar a CPU
                        }
                    } else {
                        msleep(delay); // anda normalmente conforme a "velocidade"
                    }

                }
            }
            break;

        case 6: // Trem 6 - PRETO - (bloco inteiro)
            if (y == 100 && x > 100) { // movimenta para a esquerda
                { // Escopo 1: Protege Trecho07
                    std::unique_lock<std::mutex> lock(Trem::mtxTrecho07); // Bloqueia AQUI
                    while(x > 100) {
                        x -= 20;
                        emit updateGUI(ID, x, y);
                        int delay = getDelay();
                        if (delay < 0) {
                            // Trem parado — congela mantendo posição e mutexes
                            while (velocidade <= 0) {
                                msleep(10); // dorme um pouquinho, só pra não travar a CPU
                            }
                        } else {
                            msleep(delay); // anda normalmente conforme a "velocidade"
                        }
                        if(x == 500) {
                            break;
                        }
                    }
                }

                { // Escopo 2: Protege Trecho04
                    std::unique_lock<std::mutex> lock(Trem::mtxTrecho04); // Bloqueia AQUI
                    while(x > 100) {
                        x -= 20;
                        emit updateGUI(ID, x, y);
                        int delay = getDelay();
                        if (delay < 0) {
                            // Trem parado — congela mantendo posição e mutexes
                            while (velocidade <= 0) {
                                msleep(10); // dorme um pouquinho, só pra não travar a CPU
                            }
                        } else {
                            msleep(delay); // anda normalmente conforme a "velocidade"
                        }
                        if(x == 300) {
                            break;
                        }
                    }
                }

                { // Escopo 3: Protege Trecho01
                    std::unique_lock<std::mutex> lock(Trem::mtxTrecho01); // Bloqueia AQUI
                    while(x > 100) {
                        x -= 20;
                        emit updateGUI(ID, x, y);
                        int delay = getDelay();
                        if (delay < 0) {
                            // Trem parado — congela mantendo posição e mutexes
                            while (velocidade <= 0) {
                                msleep(10); // dorme um pouquinho, só pra não travar a CPU
                            }
                        } else {
                            msleep(delay); // anda normalmente conforme a "velocidade"
                        }
                    }
                }

            } else if (x == 100 && y < 500) { // movimenta para baixo
                { // Escopo 4: Protege Trecho01
                    std::unique_lock<std::mutex> lock(Trem::mtxTrecho01);
                    while(y < 500){
                        y += 20;
                        emit updateGUI(ID, x, y);
                        int delay = getDelay();
                        if (delay < 0) {
                            // Trem parado — congela mantendo posição e mutexes
                            while (velocidade <= 0) {
                                msleep(10); // dorme um pouquinho, só pra não travar a CPU
                            }
                        } else {
                            msleep(delay); // anda normalmente conforme a "velocidade"
                        }
                        if(y == 300) {
                            break;
                        }
                    }
                } 

                { // Escopo 5: Protege Trecho12
                    std::unique_lock<std::mutex> lock(Trem::mtxTrecho12);
                    while(y < 500) {
                        y += 20;
                        emit updateGUI(ID, x, y);
                        int delay = getDelay();
                        if (delay < 0) {
                            // Trem parado — congela mantendo posição e mutexes
                            while (velocidade <= 0) {
                                msleep(10); // dorme um pouquinho, só pra não travar a CPU
                            }
                        } else {
                            msleep(delay); // anda normalmente conforme a "velocidade"
                        }
                        if(y == 500) {
                            break;
                        }
                    }
                } 

            } else if (y == 500 && x < 700) { // movimenta para direita
                { // Escopo 6: Protege Trecho12
                    std::unique_lock<std::mutex> lock(Trem::mtxTrecho12);
                    while(x < 700){
                        x += 20;
                        emit updateGUI(ID, x, y);
                        int delay = getDelay();
                        if (delay < 0) {
                            // Trem parado — congela mantendo posição e mutexes
                            while (velocidade <= 0) {
                                msleep(10); // dorme um pouquinho, só pra não travar a CPU
                            }
                        } else {
                            msleep(delay); // anda normalmente conforme a "velocidade"
                        }
                        if(x == 400) {
                            break;
                        }
                    }
                } 

                { // Escopo 7: Protege Trecho10
                    std::unique_lock<std::mutex> lock(Trem::mtxTrecho10); // Ponto e vírgula corrigido
                    while(x < 700) {
                        x += 20;
                        emit updateGUI(ID, x, y);
                        int delay = getDelay();
                        if (delay < 0) {
                            // Trem parado — congela mantendo posição e mutexes
                            while (velocidade <= 0) {
                                msleep(10); // dorme um pouquinho, só pra não travar a CPU
                            }
                        } else {
                            msleep(delay); // anda normalmente conforme a "velocidade"
                        }
                        if(x == 700) {
                            break;
                        }
                    }
                } 

            } else { //x == 700 && y > 100 // movimenta para cima

                {
                    // CORREÇÃO: Usar o mutex correto para o Trecho 10
                    std::unique_lock<std::mutex> lock(Trem::mtxTrecho10); 
                    while(y > 100){
                        y -= 20;
                        emit updateGUI(ID, x, y);
                        int delay = getDelay();
                        if (delay < 0) {
                            // Trem parado — congela mantendo posição e mutexes
                            while (velocidade <= 0) {
                                msleep(10); // dorme um pouquinho, só pra não travar a CPU
                            }
                        } else {
                            msleep(delay); // anda normalmente conforme a "velocidade"
                        }
                        if(y == 300) {
                            break;
                        }
                    }
                } // Libera mtxTrecho10

                { // Escopo 9: Protege Trecho07 (CORRIGIDO)
                    // Esta é a seção que causaria o erro em tempo de execução
                    std::unique_lock<std::mutex> lock(Trem::mtxTrecho07); // Bloqueia AQUI
                    while(y > 100) {
                        y -= 20;
                        emit updateGUI(ID, x, y);
                        int delay = getDelay();
                        if (delay < 0) {
                            // Trem parado — congela mantendo posição e mutexes
                            while (velocidade <= 0) {
                                msleep(10); // dorme um pouquinho, só pra não travar a CPU
                            }
                        } else {
                            msleep(delay); // anda normalmente conforme a "velocidade"
                        }
                        if(y == 100) {
                            break;
                        }
                    }
                } 
            }
            break;
            
        default:
            break;
        }
    }
}
