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
        switch(ID){

        case 1: // T1 (Loop Top-Left) - LÓGICA CORRIGIDA
            if (y == 50 && x < 150) {
                x += 10;
            } else if (x == 150 && y < 150) {
                y += 10;
            } else if (y == 150 && x > 50) {
                x -= 10;
            } else { // x == 50 && y > 50
                y -= 10;
            }
            emit updateGUI(ID, x,y);
            msleep(velocidade);
            break;

        case 2: // T2 (Loop Bot-Left) - LÓGICA CORRIGIDA
            if (y == 150 && x < 200) {
                x += 10;
            } else if (x == 200 && y < 250) {
                y += 10;
            } else if (y == 250 && x > 50) {
                x -= 10;
            } else { // x == 50 && y > 150
                y -= 10;
            }
            emit updateGUI(ID, x,y);
            msleep(velocidade);
            break;

        case 3: // T3 (Loop Bot-Right) - SINTAXE CORRIGIDA
            if (y == 150 && x < 350) {
                x += 10;
            } else if (x == 350 && y < 250) {
                y += 10;
            } else if (y == 250 && x > 200) {
                x -= 10;
            } else { // x == 200 && y > 150
                y -= 10;
            }
            emit updateGUI(ID, x,y);
            msleep(velocidade);
            break;

        case 4: // T4 (Loop Top-Right)
            if (y == 50 && x < 350) {
                x += 10;
            } else if (x == 350 && y < 150) {
                y += 10;
            } else if (y == 150 && x > 250) {
                x -= 10;
            } else { // x == 250 && y > 50
                y -= 10;
            }
            emit updateGUI(ID, x,y);
            msleep(velocidade);
            break;

        case 5: // T5 (Loop Top-Mid)
            if (y == 50 && x < 250) {
                x += 10;
            } else if (x == 250 && y < 150) {
                y += 10;
            } else if (y == 150 && x > 150) {
                x -= 10;
            } else { // x == 150 && y > 50
                y -= 10;
            }
            emit updateGUI(ID, x,y);
            msleep(velocidade);
            break;

        case 6: // T6 (Perímetro) - LÓGICA CORRIGIDA (Sentido Anti-Horário)
            if (y == 50 && x > 50) {
                x -= 10;
            } else if (x == 50 && y < 250) {
                y += 10;
            } else if (y == 250 && x < 350) {
                x += 10;
            } else { // x == 350 && y > 50
                y -= 10;
            }
            emit updateGUI(ID, x,y);
            msleep(velocidade);
            break;

        default:
            break;
        }
    }
}
