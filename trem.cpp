#include "trem.h"
#include <QtCore>

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 150;
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
                    emit updateGUI(ID, x,y);
                    msleep(velocidade);
                }
                while(x < 300){
                    x += 20; // movimenta para direita
                    emit updateGUI(ID, x,y);
                    msleep(velocidade);
                }
            } else if (x == 300 && y < 300) { // movimenta para baixo
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho03); // Mutex que protege o trecho 03
                while(y < 300){
                    y += 20;
                    emit updateGUI(ID, x,y);
                    msleep(velocidade);
                }
            } else if (y == 300 && x > 100) { // movimenta para esquerda
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho02); // Mutex que protege o trecho 02
                while(x > 100){
                    x -= 20;
                    emit updateGUI(ID, x,y);
                    msleep(velocidade);
                }
            }
            break;

        case 2: // Trem 2 - LARANJA - (bloco inferior esquerdo)
            if (y == 300 && x < 400) { // movimenta para a direita
                std::unique_lock<std::mutex> lock(Trem::mtxTrecho02, std::defer_lock); // Mutex para proteger primeiro o trecho 02 e depois o trecho 05
                lock.lock();
                while(x < 400){
                    x += 20;
                    emit updateGUI(ID, x, y);
                    msleep(velocidade);
                    if(x == 300){
                        break;
                    }
                }
                lock.unlock();
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho05);
                while(x < 400){
                    x += 20;
                    emit updateGUI(ID, x, y);
                    msleep(velocidade);
                }
            } else if (x == 400 && y < 500) { // movimenta para baixo
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho11); // Mutex para proteger trecho 11
                while(y < 500){
                    y += 20;
                    emit updateGUI(ID, x, y);
                    msleep(velocidade);
                }
            } else if (y == 500 && x > 100) { // movimenta para esquerda
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho12); // Mutex para proteger trecho 12
                while(x > 100){
                    x -= 20;
                    emit updateGUI(ID, x, y);
                    msleep(velocidade);
                }
                while(y > 300){
                    y -= 20;
                    emit updateGUI(ID, x, y);
                    msleep(velocidade);
                }
            }
            break;

        case 3: // Trem 3 - ROXO - (bloco inferior direito)
            if (y == 300 && x < 700) { // movimenta para a direita
                std::unique_lock<std::mutex> lock(Trem::mtxTrecho06, std::defer_lock);  // Mutex para proteger primeiro o trecho 06 e depois o trecho 09. Ainda não guarda
                lock.lock();
                while(x < 700){
                    x += 20;
                    emit updateGUI(ID, x, y);
                    msleep(velocidade);
                    if(x == 500){
                        break;
                    }
                }
                lock.unlock();
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho09);
                while(x < 700){
                    x += 20;
                    emit updateGUI(ID, x, y);
                    msleep(velocidade);
                }
            } else if (x == 700 && y < 500) { // movimenta para baixo
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho10); // Mutex para proteger trecho 10
                while(y < 500){
                    y += 20;
                    emit updateGUI(ID, x, y);
                    msleep(velocidade);
                }
                while(x > 400){
                    x -= 20;
                    emit updateGUI(ID, x, y);
                    msleep(velocidade);
                }
            } else { // x == 400 && y > 300 // movimenta para cima
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho11); // Mutex para proteger trecho 11
                while(y > 300){
                    y -= 20;
                    emit updateGUI(ID, x, y);
                    msleep(velocidade);
                }
            }
            break;

        case 4: // Trem 4 - AZUL -(bloco superior direito)
            if (y == 100 && x < 700) { // movimenta para a direita
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho07); // Mutex para proteger trecho 07
                while(x < 700){
                    x += 20;
                    emit updateGUI(ID, x, y);
                    msleep(50);
                }
                while(y < 300){
                    y += 20; // movimenta para baixo
                    emit updateGUI(ID, x, y);
                    msleep(50);
                }
            } else if (y == 300 && x > 500) { // movimenta para esquerda
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho09); // Mutex para proteger trecho 09
                while(x > 500){
                    x -= 20;
                    emit updateGUI(ID, x, y);
                    msleep(50);
                }
            } else { // x == 500 && y > 100 // movimenta para cima
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho08); // Mutex para proteger trecho 08
                while(y > 100){
                    y -= 20;
                    emit updateGUI(ID, x, y);
                    msleep(50);
                }
            }
            break;

        case 5: // Trem 5 - VERMELHO -(bloco superior central)
            if (y == 100 && x < 500) { // movimenta para a direita
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho04); // Mutex para proteger trecho 04
                while(x < 500){
                    x += 20;
                    emit updateGUI(ID, x, y);
                    msleep(velocidade);
                }
            } else if (x == 500 && y < 300) { // movimenta para baixo
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho08); // Mutex para proteger trecho 08
                while(y < 300){
                    y += 20;
                    emit updateGUI(ID, x, y);
                    msleep(velocidade);
                }
            } else if (y == 300 && x > 300) { // movimenta para esquerda
               std::unique_lock<std::mutex> lock(Trem::mtxTrecho06, std::defer_lock); // Mutex para proteger trecho 06. Não trava ainda
               lock.lock();
                while(x > 300){
                    x -= 20;
                    emit updateGUI(ID, x, y);
                    msleep(velocidade);
                    if(x == 400){
                        break;
                    }
                }
                lock.unlock();
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho05); // Mutex para proteger trecho 05
                while(x > 300){
                    x -= 20;
                    emit updateGUI(ID, x, y);
                    msleep(velocidade);
                }
            } else { // x == 300 && y > 100 // movimenta para cima
                std::lock_guard<std::mutex> guard(Trem::mtxTrecho03); // Mutex para proteger trecho 03
                while(y > 100){
                    y -= 20;
                    emit updateGUI(ID, x, y);
                    msleep(velocidade);
                }
            }
            break;

        case 6: // Trem 6 - PRETO - (bloco inteiro)
            if (y == 100 && x > 100) { // movimenta para a esquerda
                std::scoped_lock locks(Trem::mtxTrecho07, Trem::mtxTrecho04, Trem::mtxTrecho01); // Mutex para 07 04 01
                while(x > 100){
                    x -= 20;
                    emit updateGUI(ID, x, y);
                    msleep(velocidade);
                }
            } else if (x == 100 && y < 500) { // movimenta para baixo
                std::scoped_lock locks(Trem::mtxTrecho01, Trem::mtxTrecho12);  // Mutex para 01 e 12
                while(y < 500){
                    y += 20;
                    emit updateGUI(ID, x, y);
                    msleep(velocidade);
                }
            } else if (y == 500 && x < 700) { // movimenta para direita
                std::scoped_lock locks(Trem::mtxTrecho12, Trem::mtxTrecho10);  // Mutex para 12 e 10
                while(x < 700){
                    x += 20;
                    emit updateGUI(ID, x, y);
                    msleep(velocidade);
                }
            } else { // x == 700 && y > 100 // movimenta para cima
                std::scoped_lock locks(Trem::mtxTrecho10, Trem::mtxTrecho07); // Mutex para 10 e 07
                while(y > 100){
                    y -= 20;
                    emit updateGUI(ID, x, y);
                    msleep(velocidade);
                }
            }
            break;

        default:
            break;
        }
    }
}
