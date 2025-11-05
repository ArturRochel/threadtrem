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
QSemaphore Trem::sema03(1);
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
            if (x == 100 && y > 100) {
                // Ele começa na ponta de baixo. sobe, faz a curva e vai até o buffer em x = 260
                {
                    std::scoped_lock locks(mtxTrecho01, mtxTrecho03);
                    
                    while(y > 100) {
                        y -= 20;
                        fazAndar();
                    }
                    while(x < 300) {
                        x += 20;
                        fazAndar();
                    }
                    while(y < 140) {
                        y += 20;
                        fazAndar();
                    }
                }
            }
            else if (x == 300 && y < 300) {
                // Percorre o trecho03 até o buffer
               {
                std::scoped_lock locks(mtxTrecho03, mtxTrecho02);

                while(y < 300) {
                    y += 20;
                    fazAndar();
                }
                while(x > 260) {
                    x -= 20;
                    fazAndar();
                }
               }
            }

            else if (y == 300 && x > 100) {
                // Vai até o buffer da região antes do 01
               {
                std::scoped_lock locks(mtxTrecho02, mtxTrecho01);

                while(x > 100) {
                    x -= 20;
                    fazAndar();
                }  
                while(y > 260) {
                    y -= 20;
                    fazAndar();
                } 
               }
            }

            break;
        }
            case 2: //. Trem 2 
                if (y == 500 && x > 100) { // movimenta para esquerda

                    //Percorre o trecho 12 até chegar no buffer com o trecho02
                    {
                        std::scoped_lock locks(mtxTrecho12, mtxTrecho02);

                        while(x > 100) {
                            x -= 20;
                            fazAndar();
                        }
                        while(y > 300) {
                            y -= 20;
                            fazAndar();
                        }

                        while(x < 140) {
                            x += 20;
                            fazAndar();
                        }
                    }

                } else if(y == 300 && x < 400) { // movimenta para a direita
                   // Percorre o trecho02 até chegar ao buffer antes do trecho05
                   {
                        std::scoped_lock locks(mtxTrecho02, mtxTrecho05, mtxTrecho11);

                        // Agora executa a manobra inteira com segurança
                        
                        // Parte 1: Reta do Trecho 02
                        while(x < 260) {
                            x += 20;
                            fazAndar();
                        }
                        
                        // Parte 2: Interseção 02-05
                        while(x < 340) {
                            x += 20;
                            fazAndar();
                        }

                        // Parte 3: Reta 05 e Interseção 05-11
                        while(x < 360) {
                            x += 20;
                            fazAndar();
                        }
                        while(x < 400){
                            x += 20;
                            fazAndar();
                        }
                        while(y < 340){
                            y += 20;
                            fazAndar();
                        }
                    }

                } else if (x == 400 && y < 500) { // movimenta para baixo
                    // Percorre o trecho11 até o buffer com o trecho12
                    {
                        std::scoped_lock locks( mtxTrecho11, mtxTrecho12);

                        while(y < 500){
                            y += 20;
                            fazAndar();
                        }

                        while(x > 360){
                            x -= 20;
                            fazAndar();
                        }
                    }
                }
            break;

        case 3: // Trem 3 - ROXO - (bloco inferior direito)
            if (y == 300 && x < 700) { // movimenta para a direita
                // Controla até o primeiro buffer que é x = 540
                {
                    std::scoped_lock locks(mtxTrecho06, mtxTrecho09, mtxTrecho10);

                    while(x < 540) {
                        x += 20;
                        fazAndar();
                    }
                     while(x < 700) {
                        x += 20;
                        fazAndar();
                    }
                    while(y < 340) {
                        y += 20;
                        fazAndar();
                    }
                }

            } else if (x == 700 && y < 500) { // movimenta para baixo
                // Já dentro da região 10 após a curva, ele continua só com o trecho10
                {
                    std::scoped_lock locks(mtxTrecho10, mtxTrecho11);

                    while(y < 500){
                        y += 20;
                        fazAndar();
                    }
                    while(x > 400){
                        x -= 20;
                        fazAndar();
                    }
                    while(y > 460) {
                        y -= 20;
                        fazAndar();
                    }
                }
            } else { // x == 400 && y > 300 // movimenta para cima
                // Já dentro da região 11 ele apenas percorre em direção ao buffer y = 340
                {
                    std::scoped_lock locks(mtxTrecho11, mtxTrecho06);

                    while(y > 300){
                        y -= 20;
                        fazAndar();
                    }

                    while(x < 440){
                        x += 20;
                        fazAndar();
                    }
                }
            }
            break;

        case 4: // Trem 4 - AZUL -(bloco superior direito)
            if (y == 100 && x < 700) { // movimenta para a direita
                // Percorre todo o trecho 07 até chegar no buffer com o trecho09
                {
                    std::scoped_lock locks(mtxTrecho07, mtxTrecho09);

                    while(x < 700) {
                        x += 20;
                        fazAndar();
                    }
                    while(y < 300) {
                        y += 20;
                        fazAndar();
                    }
                    while(x > 660) {
                        x -= 20;
                        fazAndar();
                    }
                }
            } else if (y == 300 && x > 500) { // movimenta para esquerda
                // Percorre o trecho09 até o buffer com o trecho08
                {
                    std::scoped_lock locks(mtxTrecho09, mtxTrecho08);

                    while(x > 500) {
                        x -= 20;
                        fazAndar();
                    }
                    while(y > 260) {
                        y -= 20;
                        fazAndar();
                    }
                }
            } else { // x == 500 && y > 100 // movimenta para cima
                // Percorre o trecho08 até o buffer com o trecho07
                {
                    std::scoped_lock locks(mtxTrecho08, mtxTrecho07);

                    while(y > 100) {
                        y -= 20;
                        fazAndar();
                    }
                    while(x < 540) {
                        x += 20;
                        fazAndar();
                    }
                }
            }
            break;

        case 5: // Trem 5 - VERMELHO -(bloco superior central)
            if (y == 100 && x < 500) {
                // Movimenta o trem no trecho04 e desce para o trecho08
                {
                    std::scoped_lock locks(mtxTrecho04, mtxTrecho08);
                    
                    while(x < 500){ // BUFFER
                        x += 20;
                        fazAndar();
                    }
                    while(y < 140){
                        y += 20;
                        fazAndar();
                    }
                }
            } else if (x == 500 && y < 300) { 
                // Trecho08 e parte do trecho06
                {
                    std::scoped_lock locks(mtxTrecho08, mtxTrecho06);
                
                    while(y < 300){
                        y += 20;
                        fazAndar();
                    }
                    while(x > 440){
                        x -= 20;
                        fazAndar();
                    }
                }

            } else if (y == 300 && x > 300) { // movimenta para esquerda
                {
                std::scoped_lock locks(mtxTrecho06, mtxTrecho05, mtxTrecho03);

                while(x > 300) {
                    x -= 20;
                    fazAndar();
                }
                while(y > 260) {
                    y -= 20;
                    fazAndar();
                }
                }
            } else {
                {
                    std::scoped_lock locks(mtxTrecho03, mtxTrecho04);

                    while(y > 100) {
                        y -= 20;
                        fazAndar();
                    }
                    while(x < 340) {
                        x += 20;
                        fazAndar();
                    }
                }
            }
            break;

        case 6: // Trem 6 - PRETO - (bloco inteiro)
            if (x == 700 && y > 100) {// Movimenta para cima       
                {
                    std::scoped_lock locks(mtxTrecho10, mtxTrecho07);

                    while(y > 100) {
                        y -= 20;
                        fazAndar();
                    }
                    while(x > 660) {
                        x -= 20;
                        fazAndar();
                    }
                }
            } else if (y == 100 && x > 100) { // Movimenta para a esquerda
                {
                    std::scoped_lock locks(mtxTrecho07, mtxTrecho04, mtxTrecho01);

                    while(x > 100) {
                        x -= 20;
                        fazAndar();
                    }
                    while(y < 260) {
                        y += 20;
                        fazAndar();
                    }
                }
            }
            else if (x == 100 && y < 500) { // Movimenta para baixo
                {
                    std::scoped_lock locks(mtxTrecho01, mtxTrecho12);

                    while(y < 500) {
                        y += 20;
                        fazAndar();
                    }
                    while(x < 360) {
                        x += 20;
                        fazAndar();
                    }
                }
            } else if (y == 500 && x < 700) {
                {
                    std::scoped_lock locks(mtxTrecho12, mtxTrecho10);

                    while(x < 700) {
                        x += 20;
                        fazAndar();
                    }
                    while(y > 460) {
                        y -= 20;
                        fazAndar();
                    }
                }
            }
            break;

        default:
            break;
        }
    }
}