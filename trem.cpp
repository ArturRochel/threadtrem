#include "trem.h"
#include <QtCore>

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
}

std::mutex Trem::mutex mtxTrecho01;
std::mutex Trem::mutex mtxTrecho02;
std::mutex Trem::mutex mtxTrecho03;
std::mutex Trem::mutex mtxTrecho04;
std::mutex Trem::mutex mtxTrecho05;
std::mutex Trem::mutex mtxTrecho06;
std::mutex Trem::mutex mtxTrecho07;
std::mutex Trem::mutex mtxTrecho08;
std::mutex Trem::mutex mtxTrecho09;
std::mutex Trem::mutex mtxTrecho10;
std::mutex Trem::mutex mtxTrecho11;
std::mutex Trem::mutex mtxTrecho12;


void Trem::run(){
    while(true){
        switch(ID){

        case 1: // Trem 1 (bloco superior esquerdo)
            if (y == 100 && x < 300) { // movimenta para a direita
                x += 20;
            } else if (x == 300 && y < 300) { // movimenta para baixo
                y += 20;
            } else if (y == 300 && x > 100) { // movimenta para esquerda
                x -= 20;
            } else { // x == 100 && y > 100 // movimenta para cima
                y -= 20;
            }
            emit updateGUI(ID, x,y);
            msleep(velocidade);
            break;

        case 2: // Trem 2 (bloco inferior esquerdo)
            if (y == 300 && x < 400) { // movimenta para a direita
                x += 20;
            } else if (x == 400 && y < 500) { // movimenta para baixo
                y += 20;
            } else if (y == 500 && x > 100) { // movimenta para esquerda
                x -= 20;
            } else { // x == 100 && y > 300 // movimenta para cima
                y -= 20;
            }
            emit updateGUI(ID, x,y);
            msleep(velocidade);
            break;

        case 3: // Trem 3 (bloco inferior direito)
            if (y == 300 && x < 700) { // movimenta para a direita
                x += 20;
            } else if (x == 700 && y < 500) { // movimenta para baixo
                y += 20;
            } else if (y == 500 && x > 400) { // movimenta para esquerda
                x -= 20;
            } else { // x == 400 && y > 300 // movimenta para cima
                y -= 20;
            }
            emit updateGUI(ID, x,y);
            msleep(velocidade);
            break;

        case 4: // Trem 4 (bloco superior direito)
            if (y == 100 && x < 700) { // movimenta para a direita
                x += 20;
            } else if (x == 700 && y < 300) { // movimenta para baixo
                y += 20;
            } else if (y == 300 && x > 500) { // movimenta para esquerda
                x -= 20;
            } else { // x == 500 && y > 100 // movimenta para cima
                y -= 20;
            }
            emit updateGUI(ID, x,y);
            msleep(velocidade);
            break;

        case 5: // Trem 5 (bloco superior central)
            if (y == 100 && x < 500) { // movimenta para a direita
                x += 20;
            } else if (x == 500 && y < 300) { // movimenta para baixo
                y += 20;
            } else if (y == 300 && x > 300) { // movimenta para esquerda
                x -= 20;
            } else { // x == 300 && y > 100 // movimenta para cima
                y -= 20;
            }
            emit updateGUI(ID, x,y);
            msleep(velocidade);
            break;

        case 6: // Trem 6 (bloco inteiro)
            if (y == 100 && x > 100) { // movimenta para a esquerda
                x -= 20;
            } else if (x == 100 && y < 500) { // movimenta para baixo
                y += 20;
            } else if (y == 500 && x < 700) { // movimenta para direita
                x += 20;
            } else { // x == 700 && y > 100 // movimenta para cima
                y -= 20;
            }
            emit updateGUI(ID, x,y);
            msleep(velocidade);
            break;

        default:
            break;
        }
    }
}
