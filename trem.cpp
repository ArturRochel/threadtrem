#include "trem.h"
#include <QtCore>

//Construtor da classe trem
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1: //Trem 1 - Sentido Horário OK
            if (x == 0 && y <100) // Trecho 01 
                y+=10;
            else if (x < 150 && y == 100) // Trecho 06 e Trecho 08
                x+=10;
            else if (x == 150 && y > 0) // Trecho 12
                y-=10;
            else
                x-=10; // Trecho 01 de novo
            emit updateGUI(ID, x,y);
            break;
        case 2: //Trem 2 - Sentido Horário OK
            if (x == 0 && y < 200) // Trecho 02
                y+=10;
            else if (x < 100 && y == 200) // Trecho 02
                x+=10;
            else if (x == 100 && y > 100) // Trecho 07
                y-=10;
            else
                x-=10; // Trecho 06
            emit updateGUI(ID, x,y);
            break;
        case 3: //Trem 3 - Sentindo Horário OK
            if (x == 100 && y < 200) // Trecho 07
                y+=10;
            else if (x < 200 && y == 200) // Trecho 03
                x+=10;
            else if (x == 200 && y > 100) // Trecho 10
                y-=10;
            else
                x-=10; // Trecho 09 e Trecho 08
            emit updateGUI(ID, x,y);
            break;
        case 4: //Trem 4 - Sentindo Horário OK
            if (x == 200 && y < 200) // Trecho 10
                y+=10;
            else if (x < 300 && y == 200) // Trecho 04
                x+=10;
            else if (x == 300 && y > 100) // Trecho 04
                y-=10;
            else
                x-=10; // Trecho 11
            emit updateGUI(ID, x,y);
            break;
        case 5: //Trem 5 - Sentindo Horário OK
            if (x == 150 && y < 100) // Trecho 12
                y+=10;
            else if (x < 300 && y == 100) // Trecho 09 e Trecho 11
                x+=10;
            else if (x == 300 && y > 0) // Trecho 05
                y-=10;
            else
                x-=10; // Trecho 05
            emit updateGUI(ID, x,y);
            break;
        case 6: //Trem 6 - Sentindo ANTI-HORÁRIO OK
            if (x < 300 && y == 0 ) // Trecho 01 e Trecho 05
                x+=10;
            else if (x == 300 && y < 200) // Trecho 05 e Trecho 04
                y+=10;
            else if (x > 0 &&  == 200) // Trecho 04, Trecho 03 e Trecho 02
                x-=10;
            else
                y-=10; // Trecho 02 e Trecho 01
            emit updateGUI(ID, x,y);
            break;
        default:
            break;
        }
        msleep(velocidade);
    }
}

// Trem Amarelo - ID = 1
// Trem Verde - ID = 2
// Trem Vermelho - ID = 3
// Trem Azul - ID = 4
// Trem Roxo - ID = 5
// Trem Preto - ID = 6

// Trecho 01: Utilizado pelo trem laranja e trem preto
// Trecho 02: Utilizado pelo trem verde e trem preto
// Trecho 03: Utilizado pelo trem vermelho e trem preto
// Trecho 04: Utilizado pelo trem azul e trem preto
// Trecho 05: Utilizado pelo trem roxo e preto
// Trecho 06: Utilizado pelo trem laranja e trem verde
// Trecho 07: Utilizado pelo trem verde e vermelho
// Trecho 08: Utilizado pelo trem laranja e vermelho
// Trecho 09: Utilizado pelo trem vermelho e roxo
// Trecho 10: Utilizado pelo trem vermelho e azul
// Trecho 11: Utilizado pelo trem azul e trem roxo
// Trecho 12: Utilizado pelo trem laranja e trem roxo
