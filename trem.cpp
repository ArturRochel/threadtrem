#include "trem.h"
#include <QtCore>
#include <QSemaphore>

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

QSemaphore Trem::sema01(2);
QSemaphore Trem::sema02(2);
QSemaphore Trem::sema03(2);
QSemaphore Trem::sema04(2);
QSemaphore Trem::sema05(2);
QSemaphore Trem::sema06(2);
QSemaphore Trem::sema07(2);
QSemaphore Trem::sema08(1);

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
                
                sema01.acquire();
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
                sema01.release();
                
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
                        sema08.acquire();
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
                    sema01.acquire();
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
                    sema08.release();
                } else if(y == 300 && x < 400) { // movimenta para a direita
                    while(x < 260){
                        x += 20;
                        fazAndar();
                    }

                    mtxTrecho05.lock();
                    sema01.release();

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
                        sema08.acquire();
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
                sema05.acquire();
                if (!trecho06Reservado) {
                    mtxTrecho06.lock();
                    trecho06Reservado = true;
                }

                while(x < 460){
                    x += 20;
                    fazAndar();
                }

                sema06.acquire();
                mtxTrecho09.lock();

                while(x < 540){
                    x += 20;
                    fazAndar();
                }

                mtxTrecho06.unlock(); 
                trecho06Reservado = false;
                sema05.release();

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
                sema06.release();

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
            static bool trecho07Reservado = false; 
            if (y == 100 && x < 700) { // movimenta para a direita
                sema06.acquire();
                if(!trecho07Reservado) {
                    mtxTrecho07.lock();
                    trecho07Reservado = true;
                }
                
                while(x < 700){
                    x += 20;
                    fazAndar();
                }
                while(y < 260){ // BUFFER
                    y += 20;
                    fazAndar();
                }
                mtxTrecho09.lock();
                while(y < 300) {
                    y += 20;
                    fazAndar();
                }
                while(x > 660) { // BUFFER
                    x -= 20;
                    fazAndar();
                }
                mtxTrecho07.unlock();
                trecho07Reservado = false;
                sema06.release();

            } else if (y == 300 && x > 500) { // movimenta para esquerda
                while(x > 540){ // BUFFER
                    x -= 20;
                    fazAndar();
                }
                mtxTrecho08.lock();
                while(x > 500){
                    x -= 20;
                    fazAndar();
                }
                while(y < 260) {
                    y -= 20;
                    fazAndar();
                }
                mtxTrecho09.unlock();
            } else { // x == 500 && y > 100 // movimenta para cima
                while(y > 140){
                    y -= 20;
                    fazAndar();
                }
                if (!trecho07Reservado) {
                    mtxTrecho07.lock();
                    trecho07Reservado = true;
                }
                
                while(y > 100) {
                    y -= 20;
                    fazAndar();
                }
                while(x < 540) {
                    x += 20;
                    fazAndar();
                }
                mtxTrecho08.unlock();
            }
            break;

        case 5: // Trem 5 - VERMELHO -(bloco superior central)
            
        static bool trecho04Reservado = false; 
            if (y == 100 && x < 700) { // movimenta para a direita
                if(!trecho04Reservado) {
                    mtxTrecho04.lock();
                    trecho04Reservado = true;
                }
                while(x < 460){ // BUFFER
                    x += 20;
                    fazAndar();
                }

                sema05.acquire();
                mtxTrecho08.lock();

                while(x < 500){
                    x += 20;
                    fazAndar();
                }
                while(y < 140){
                    y += 20;
                    fazAndar();
                }
                mtxTrecho04.unlock();
                trecho04Reservado = false;

            } else if (x == 500 && y < 300) { // movimenta para baixo
                while(y < 260){
                    y += 20;
                    fazAndar();
                }
                mtxTrecho06.lock();
                while(y < 300) {
                    y += 20;
                    fazAndar();
                }
                while(x > 460) {
                    x -= 20;
                    fazAndar();
                }
                mtxTrecho08.unlock();
                sema05.release();

            } else if (y == 300 && x > 300) { // movimenta para esquerda
               while(x > 440) {
                    x -= 20;
                    fazAndar();
                }
                sema01.acquire();
                mtxTrecho05.lock();

                while(x > 360) {
                    x -= 20;
                    fazAndar();
                }
                mtxTrecho06.unlock();
                while(x > 340) {
                    x -= 20;
                    fazAndar();
                }
                mtxTrecho03.lock();
                sema01.release();
                while(x > 300) {
                    x -= 20;
                    fazAndar();
                }
                while(y < 260) {
                    y -= 20;
                    fazAndar();
                }
                
                mtxTrecho05.unlock();

            } else { // x == 300 && y > 100 // movimenta para cima
                while(y > 140){
                    y -= 20;
                    fazAndar();
                }
                if(!trecho04Reservado) {
                    mtxTrecho04.lock();
                    trecho04Reservado = true;
                }
                while( y > 100) {
                    y -= 20;
                    fazAndar();
                }

                while(x < 340){
                    x += 20;
                    fazAndar();
                }

                mtxTrecho03.unlock();
            }
            break;

        case 6: // Trem 6 - PRETO - (bloco inteiro)
        
            static bool trecho10Reservado = false; 
            if (x == 700 && y > 100){// movimenta para cima
                
                sema06.acquire();
                if(!trecho10Reservado) {
                    mtxTrecho10.lock();
                    trecho10Reservado = true;
                }
                
                while(y > 340){
                    y -= 20;
                    fazAndar();
                }

                mtxTrecho07.lock();

                while(y > 260){
                    y -= 20;
                    fazAndar();
                }
                sema06.release();
                mtxTrecho10.unlock();
                trecho10Reservado = false;

                while(y > 100){
                    y -= 20;
                    fazAndar();
                }

            } else if (y == 100 && x > 100) { // movimenta para a esquerda
                while(x > 540) {
                    x -= 20;
                    fazAndar();
                }

                mtxTrecho04.lock();

                while(x > 460){
                    x -= 20;
                    fazAndar();
                }

                mtxTrecho07.unlock();

                while(x > 340){
                    x -= 20;
                    fazAndar();
                }
                sema08.acquire();
                mtxTrecho01.lock();

                while(x > 260){
                    x -= 20;
                    fazAndar();
                }

                mtxTrecho04.unlock();

                while(x > 100){
                    x -= 20;
                    fazAndar();
                }
                
            } else if (x == 100 && y < 500) { // movimenta para baixo
                while(x > 100){
                    x -= 20;
                    fazAndar();
                }
                
                while(y < 260){
                    y += 20;
                    fazAndar();
                }

                mtxTrecho12.lock();

                while(y < 340){
                    y += 20;
                    fazAndar();
                }

                mtxTrecho01.unlock();
                sema08.release();
                while(y < 500){
                    y += 20;
                    fazAndar();
                }

            }
            else if (y == 500 && x < 700) { // movimenta para direita
                while(x < 360){
                    x += 20;
                    fazAndar();
                }

                if(!trecho10Reservado) {
                    mtxTrecho10.lock();
                    trecho10Reservado = true;
                }

                while(x < 440){
                    x += 20;
                    fazAndar();
                }

                mtxTrecho12.unlock();

                while(x < 700){
                    x += 20;
                    fazAndar();
                }
            }
            break;

        default:
            break;
        }
    }
}
