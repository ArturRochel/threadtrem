#include "trem.h"
#include <QtCore>
#include <mutex>
std::mutex mtx;
//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
}

void Trem::run(){
    while(true){
        // COORDENADAS E PASSOS DUPLICADOS (passo de 10 para 20)
        switch(ID){

        case 1: // T1 (Loop Top-Left) - LÓGICA CORRIGIDA E DUPLICADA
            if (y == 100 && x < 300) {
                x += 20;
            } else if (x == 300 && y < 300) {
                y += 20;
            } else if (y == 300 && x > 100) {
                x -= 20;
            } else { // x == 100 && y > 100
                y -= 20;
            }
            emit updateGUI(ID, x,y);
            msleep(velocidade);
            break;

        case 2: // T2 (Loop Bot-Left) - LÓGICA CORRIGIDA E DUPLICADA
            if (y == 300 && x < 400) {
                x += 20;
            } else if (x == 400 && y < 500) {
                y += 20;
            } else if (y == 500 && x > 100) {
                x -= 20;
            } else { // x == 100 && y > 300
                y -= 20;
            }
            emit updateGUI(ID, x,y);
            msleep(velocidade);
            break;

        case 3: // T3 (Loop Bot-Right) - SINTAXE CORRIGIDA E DUPLICADA
            if (y == 300 && x < 700) {
                x += 20;
            } else if (x == 700 && y < 500) {
                y += 20;
            } else if (y == 500 && x > 400) {
                x -= 20;
            } else { // x == 400 && y > 300
                y -= 20;
            }
            emit updateGUI(ID, x,y);
            msleep(velocidade);
            break;

        case 4: // T4 (Loop Top-Right) - DUPLICADA
            if (y == 100 && x < 700) {
                x += 20;
            } else if (x == 700 && y < 300) {
                y += 20;
            } else if (y == 300 && x > 500) {
                x -= 20;
            } else { // x == 500 && y > 100
                y -= 20;
            }
            emit updateGUI(ID, x,y);
            msleep(velocidade);
            break;

        case 5: // T5 (Loop Top-Mid) - DUPLICADA
            if (y == 100 && x < 500) {
                x += 20;
            } else if (x == 500 && y < 300) {
                y += 20;
            } else if (y == 300 && x > 300) {
                x -= 20;
            } else { // x == 300 && y > 100
                y -= 20;
            }
            emit updateGUI(ID, x,y);
            msleep(velocidade);
            break;

        case 6: // T6 (Perímetro) - LÓGICA CORRIGIDA E DUPLICADA
            if (y == 100 && x > 100) {
                x -= 20;
            } else if (x == 100 && y < 500) {
                y += 20;
            } else if (y == 500 && x < 700) {
                x += 20;
            } else { // x == 700 && y > 100
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