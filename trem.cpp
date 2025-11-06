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
                    std::lock_guard<std::mutex> lock01(mtxTrecho01);
                    
                    while(y > 100) {
                        y -= 20;
                        fazAndar();
                    }
                    while(x < 260) {
                        x += 20;
                        fazAndar();
                    }
                }
                sema01.acquire(); // ! semáforo para entrar no trecho 3
                mtxTrecho03.lock();
                
                while (x < 300) {
                    x += 20;
                    fazAndar();
                }
                
                while (y < 140) {
                    y += 20;
                    fazAndar();
                }
                
            }
            else if (x == 300 && y < 300) {
                // Percorre o trecho03 até o buffer
               {
                std::lock_guard<std::mutex> lock03(mtxTrecho03);

                while(y < 260) {
                    y += 20;
                    fazAndar();
                }
               }

               // Chega no buffer e faz a curva em direção ao trecho2
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
                std::lock_guard<std::mutex> lock02(mtxTrecho02);

                while(x > 140) {
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
                sema01.release(); // ! semáforo para sair do trecho 2
                
            }

            break;
        }
            case 2: //. Trem 2 
                if (y == 500 && x > 100) { // movimenta para esquerda

                    //Percorre o trecho 12 até chegar no buffer com o trecho02
                    {
                        std::lock_guard<std::mutex> lock12(mtxTrecho12);

                        while(x > 100) {
                            x -= 20;
                            fazAndar();
                        }
                        while(y > 340) {
                            y -= 20;
                            fazAndar();
                        }
                    }
                    sema01.acquire(); // ! semáforo para entrar no trecho 2
                    mtxTrecho02.lock();

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
                    std::lock_guard<std::mutex> lock02(mtxTrecho02);

                    while(x < 260) {
                        x += 20;
                        fazAndar();
                    }
                    sema02.acquire(); // ? semáforo para entrar no trecho 5
                    mtxTrecho05.lock();

                    while(x < 340) {
                       x += 20;
                       fazAndar();
                    }
                   }

                   // Percorre o trecho05 até chegar ao buffer com o trecho11
                   {
                    std::lock_guard<std::mutex> lock05(mtxTrecho05);

                    while(x < 360) {
                        x += 20;
                        fazAndar();
                    }
                   }

                    // Faz a curva para o trecho11
                    {   
                        std::scoped_lock locks(mtxTrecho05, mtxTrecho11);

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
                    sema01.release(); // ! semáforo para sair do trecho 11 
                    sema02.release(); // ? semáforo para sair do trecho 11 
                }
            break;

        case 3: // Trem 3 - ROXO - (bloco inferior direito)
            if (y == 300 && x < 700) { // movimenta para a direita

                if (!trecho06Reservado) {
                    mtxTrecho06.lock();
                    trecho06Reservado = true;
                }

                while(x < 460){
                    x += 20;
                    fazAndar();
                }

                // Faz a transição entre trecho06 e trecho09
                {
                    std::scoped_lock locks(mtxTrecho06, mtxTrecho09);

                    while(x < 540) {
                        x += 20;
                        fazAndar();
                    }
                }
                
                // Controla apenas o trecho09 até o buffer x = 660
                {
                    std::lock_guard<std::mutex> lock09(mtxTrecho09);

                    while(x < 660){
                        x += 20;
                        fazAndar();
                    }
                }

                // Faz a transição entre trecho09 e trecho10
                {
                    std::scoped_lock locks(mtxTrecho09, mtxTrecho10);

                    while(x < 700){
                        x += 20;
                        fazAndar();
                    }
                    while(y < 340){
                        y += 20;
                        fazAndar();
                    }
                }

            } else if (x == 700 && y < 500) { // movimenta para baixo
                // Já dentro da região 10 após a curva, ele continua só com o trecho10
                {
                    std::lock_guard<std::mutex> lock10(mtxTrecho10);

                    while(y < 500){
                        y += 20;
                        fazAndar();
                    }
                    while(x > 440){
                        x -= 20;
                        fazAndar();
                    }
                }
                sema01.acquire(); // ! semáforo para entrar no trecho 11 
                sema02.acquire(); // ? semáforo para entrar no trecho 11 
                mtxTrecho11.lock();

                    while(x > 400){
                        x -= 20;
                        fazAndar();
                    }

                    while(y > 460){
                        y -= 20;
                        fazAndar();
                    }

                }
            } else { // x == 400 && y > 300 // movimenta para cima
                // Já dentro da região 11 ele apenas percorre em direção ao buffer y = 340
                {
                    std::lock_guard<std::mutex> lock11(mtxTrecho11);

                    while(y > 340){
                        y -= 20;
                        fazAndar();
                    }
                }

                // Agora ele faz a curva entre trecho11 e trecho06
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
                mtxTrecho11.unlock();
                sema01.release(); // ! semáforo para sair no trecho 11 
                sema02.release(); // ? semáforo para sair do trecho 11 
            }
            break;

        case 4: // Trem 4 - AZUL -(bloco superior direito)
            if (y == 100 && x < 700) { // movimenta para a direita
                // Percorre todo o trecho 07 até chegar no buffer com o trecho09
                {
                    std::lock_guard<std::mutex> lock07(mtxTrecho07);

                    while(x < 700) {
                        x += 20;
                        fazAndar();
                    }
                    while(y < 260) {
                        y += 20;
                        fazAndar();
                    }
                }
                sema02.acquire(); // ? semáforo para entrar no trecho 9 
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
            } else { // x == 500 && y > 100 // movimenta para cima
                // Percorre o trecho08 até o buffer com o trecho07
                {
                    std::lock_guard<std::mutex> lock08(mtxTrecho08);

                    while(y > 140) {
                        y -= 20;
                        fazAndar();
                    }
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
                sema02.release(); // ? semáforo para entrar no trecho 9 
            }
            break;

        case 5: // Trem 5 - VERMELHO -(bloco superior central)
            if (y == 100 && x < 700) { // movimenta para a direita
                if(!trecho04Reservado) {
                    mtxTrecho04.lock();
                    trecho04Reservado = true;
                }
                while(x < 460){ // BUFFER
                    x += 20;
                    fazAndar();
                }
                sema02.acquire(); // ? semáforo para entrar no trecho 8 
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
                sema01.acquire(); // ! semáforo para entrar no techo 6 
                mtxTrecho06.lock();

                while(y < 300) {
                    y += 20;
                    fazAndar();
                }
                while(x > 460) {
                    x -= 20;
                    fazAndar();
                }
                }

            } else if (y == 300 && x > 300) { // movimenta para esquerda
               
                {
                std::lock_guard<std::mutex> lock06(mtxTrecho06);

                while(x > 440) {
                    x -= 20;
                    fazAndar();
                }
                }

                mtxTrecho05.lock();
                
                while(x > 360) {
                    x -= 20;
                    fazAndar();
                }
                }
                
                {
                std::lock_guard<std::mutex> lock05(mtxTrecho05);

                
                while(x > 340) {
                    x -= 20;
                    fazAndar();
                }
                sema02.release(); // ? semáforo para sair do trecho 6 


                mtxTrecho03.lock();
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
                {
                std::lock_guard<std::mutex> lock05(mtxTrecho05);

                    while(y > 140){
                    y -= 20;
                    fazAndar();
                }
                }


                {
                std::scoped_lock locks(mtxTrecho05, mtxTrecho04);

                while( y > 100) {
                    y -= 20;
                    fazAndar();
                }
                
                while(x < 340){
                    x += 20;
                    fazAndar();
                }
                
                mtxTrecho03.unlock();
                sema01.release(); // ! semáforo para sair do trecho 3 
            }
            break;

        case 6: // Trem 6 - PRETO - (bloco inteiro)

            if (x == 700 && y > 100){// movimenta para cima
                {
                std::lock_guard<std::mutex> lock10(mtxTrecho10);

                while(y > 340){
                    y -= 20;
                    fazAndar();
                }
                }

                    
                {
                std::scoped_lock locks(mtxTrecho10, mtxTrecho07);
                
                while(y > 260){
                    y -= 20;
                    fazAndar();
                }
                while(y > 100){
                    y -= 20;
                    fazAndar();
                }
                }

            } else if (y == 100 && x > 100) { // movimenta para a esquerda
                {
                std::lock_guard<std::mutex> lock07(mtxTrecho07);

                while(x > 540) {
                    x -= 20;
                    fazAndar();
                }
                }
                
                {
                std::scoped_lock locks(mtxTrecho07, mtxTrecho04);

                while(x > 460){
                    x -= 20;
                    fazAndar();
                }
                }

                {
                std::lock_guard<std::mutex> lock04(mtxTrecho04); 

                while(x > 340){
                    x -= 20;
                    fazAndar();
                }
                }

                
                {
                std::scoped_lock locks(mtxTrecho04, mtxTrecho01);

                while(x > 260){
                    x -= 20;
                    fazAndar();
                }
                }

                {
                std::lock_guard<std::mutex> lock01(mtxTrecho01);
                while(x > 100){
                    x -= 20;
                    fazAndar();
                }

                while(y < 260){
                    y += 20;
                    fazAndar();
                }
                } 

            } else if (x == 100 && y < 500) { // movimenta para baixo
                
                
                {
                std::scoped_lock locks(mtxTrecho01, mtxTrecho12);
                
                while(y < 340){ 
                    y += 20;
                    fazAndar();
                }
                }


                {
                std::lock_guard<std::mutex> lock12(mtxTrecho12);
                
                while(y < 500){
                    y += 20;
                    fazAndar();
                }
                }
            }
            else if (y == 500 && x < 700) { // movimenta para direita
                {
                std::lock_guard<std::mutex> lock12(mtxTrecho12);

                while(x < 360){
                    x += 20;
                    fazAndar();
                }
                }


                {
                std::scoped_lock locks(mtxTrecho12, mtxTrecho10);

                while(x < 700){
                    x += 20;
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