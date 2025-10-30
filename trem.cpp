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
            
            case 1: // Trem 1 - VERDE -(bloco superior esquerdo)
            if(x == 100 && y > 100) {
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho01); // Mutex que protege o trecho 01
                while(y > 100){
                    y -= 20; // movimenta para cima
                    fazAndar();
                }
                while(x < 300){
                    x += 20; // movimenta para direita
                    fazAndar();
                }
            } else if (x == 300 && y < 300) { // movimenta para baixo
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho03); // Mutex que protege o trecho 03
                while(y < 300){
                    y += 20;
                    fazAndar();
                }
            } else if (y == 300 && x > 100) { // movimenta para esquerda
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho02); // Mutex que protege o trecho 02
                while(x > 100){
                    x -= 20;
                    fazAndar();
                }
            }
            break;

        case 2: // Trem 2 - LARANJA - (bloco inferior esquerdo)
            if (y == 300 && x < 400) { // movimenta para a direita
                std::unique_lock<std::mutex> lock(Trem::mtxTrecho02, std::defer_lock); // Mutex para proteger primeiro o trecho 02 e depois o trecho 05
                lock.lock();
                while(x < 400){
                    x += 20;
                    fazAndar();

                    if(x == 300){
                        break;
                    }
                }
                lock.unlock();
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho05);

                while(x < 400){
                    x += 20;
                    fazAndar();
                }
            } else if (x == 400 && y < 500) { // movimenta para baixo
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho11); // Mutex para proteger trecho 11
                while(y < 500){
                    y += 20;
                    fazAndar();
                }
            } else if (y == 500 && x > 100) { // movimenta para esquerda
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho12); // Mutex para proteger trecho 12
                while(x > 100){
                    x -= 20;
                    fazAndar();
                }
                while(y > 300){
                    y -= 20;
                    fazAndar();
                }
            }
            break;

        case 3: // Trem 3 - ROXO - (bloco inferior direito)
            if (y == 300 && x < 700) { // movimenta para a direita
                std::unique_lock<std::mutex> lock(Trem::mtxTrecho06, std::defer_lock);  // Mutex para proteger primeiro o trecho 06 e depois o trecho 09. Ainda não guarda
                lock.lock();
                while(x < 700){
                    x += 20;
                    fazAndar();

                    if(x == 500){
                        break;
                    }
                }
                lock.unlock();
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho09);

                while(x < 700){
                    x += 20;
                    fazAndar();
                }
            } else if (x == 700 && y < 500) { // movimenta para baixo
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho10); // Mutex para proteger trecho 10
                while(y < 500){
                    y += 20;
                    fazAndar();
                }
                while(x > 400){
                    x -= 20;
                    fazAndar();
                }
            } else { // x == 400 && y > 300 // movimenta para cima
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho11); // Mutex para proteger trecho 11
                while(y > 300){
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

        case 4: // Trem 4 - AZUL -(bloco superior direito)
            static bool trecho07Reservado = false; 
            if (y == 100 && x < 700) { // movimenta para a direita
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
                    x -= 20
                    fazAndar();
                }
                mtxTrecho07.unlock();
                trecho7Reservado = false

            } else if (y == 300 && x > 500) { // movimenta para esquerda
                while(x > 540){ // BUFFER
                    x -= 20;
                    fazAndar();
                }
                mtxTrecho08.lock() 
                while(x < 500){
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
                if (!trecho7Reservado) {
                    mtxTrecho07.lock();
                    trecho7Reservado = true;
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
            if (y == 100 && x < 500) { //! CORRIGIR ISSO AQUI
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
                mtxTrecho08.lock()
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
                    fazAndar()
                }
                mtxTrecho08.unlock();
                
            } else if (y == 300 && x > 300) { // movimenta para esquerda
               while(x > 440) {
                    x -= 20;
                    fazAndar();
                }
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
                mtxTrecho03.lock
                while(x < 300) {
                    x -= 20;
                    fazAndar()
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
                while( y < 100) {
                    y -= 20;
                    fazAndar();
                }
            }
            break;

        case 6: // Trem 6 - PRETO - (bloco inteiro)
        static bool trecho07Reservado = false; 
            if (y == 100 && x > 100) { // movimenta para a esquerda
                if(!trecho07Reservado) {
                    mtxTrecho07.lock();
                    trecho07Reservado = true;
                }
                while(x > 540) {
                    x -= 20;
                    fazAndar();
                }
                mtxTrecho04.lock();
                while(x > 460) {
                    x -= 20;
                    fazAndar();
                }
                mtxTrecho07.unlock();
                trecho07Reservado = false;
                while(x > 340) {
                    x -= 20;
                    fazAndar();
                }
                mtxTrecho01.lock();
                while(x > 260) {
                    x -= 20;
                    fazAndar();
                }
                mtxTrecho04.unlock();
                while(x > 100) {
                    x -= 20;
                    fazAndar();
                }
            } else if (x == 100 && y < 500) { // movimenta para baixo
                while(y < 260){
                    y += 20;
                    fazAndar();
                }
                mtxTrecho02.lock();
                while(y < 340) {
                    y += 20;
                    fazAndar();
                }
                mtxTrecho01.unlock();
                while(y < 500) {
                    y += 20;
                    fazAndar();
                }
            } else if (y == 500 && x < 700) { // movimenta para direita
                while(x < 360){
                    x += 20;
                    fazAndar();
                }
                mtxTrecho10.lock();
                while(x < 440) {
                    x += 20;
                    fazAndar();
                }
                mtxTrecho02.unlock();
                while(x < 700) {
                    x += 20;
                    fazAndar();
                }
            } else { x == 700 && y > 100} // movimenta para cima
                while(y > 340){
                    y -= 20;
                    fazAndar();
                }
                if(!trecho07Reservado) {
                    mtxTrecho07.lock();
                    trecho07Reservado = true;
                }
                while(y > 260) {
                    y -= 20;
                    fazAndar();
                }
                mtxTrecho10.unlock();
                while(y > 100) {
                    y -= 20;
                    fazAndar();
                }
            }
            break;
            
        default:
            break;
        }
    }
}
