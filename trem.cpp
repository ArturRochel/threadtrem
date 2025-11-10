#include "trem.h"
#include <QtCore>
#include <QSemaphore>
#include <QDebug>
#include <QDateTime>

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

// Faz a logística de inverter o valor do slide e controalr a velocidade
int Trem::getDelay() const {
    if (velocidade <= 0)
        return -1; 
    return std::max(1, 201 - velocidade); 
}

// Atuliza visualmente a posição do trem na UI
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

// Saber quando um trem pegou ou liberou um mutex
void Trem::logSemaforo(QSemaphore &semaforo, const QString &nome, const QString &acao) {
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    qDebug().noquote()
        << "[" + timestamp + "]"
        << "Trem" << ID
        << acao << "o" << nome
        << "| Espaços disponíveis:" << semaforo.available();
}

// 07 mutex para controlar 07 regiões críticas 
// Os mutexes estão na ordem de hierarquia que devem ser chamados
std::mutex Trem::mtxTrechoCima;
std::mutex Trem::mtxTrechoEsquerda;
std::mutex Trem::mtxTrechoBaixo;
std::mutex Trem::mtxTrechoDireita;
std::mutex Trem::mtxTrecho01;
std::mutex Trem::mtxTrecho02;
std::mutex Trem::mtxTrecho03;
std::mutex Trem::mtxTrecho04;
std::mutex Trem::mtxTrecho05;
std::mutex Trem::mtxTrecho06;
std::mutex Trem::mtxTrecho07;


 

void Trem::run(){
    while(true){
        switch(ID){
            case 1: 
            {
               {
                std::lock_guard<std::mutex> lockCima(mtxTrechoCima);
               std::lock_guard<std::mutex> lockEsquerda(mtxTrechoEsquerda);
               std::lock_guard<std::mutex> lock01(mtxTrecho01);
               std::lock_guard<std::mutex> lock03(mtxTrecho03);
                while(y > 100) {
                    y -= 20;
                    fazAndar();
                }
                
                while(x < 300) {
                    x += 20;
                    fazAndar();
                }

                while(y < 300) {
                    y += 20;
                    fazAndar();
                }

                while(x > 100) {
                    x -= 20;
                    fazAndar();
                }
               }
               msleep(10);
            }
            break;
            case 2: //. Trem 2 
                {
                    while(x > 100) {
                        x -= 20;
                        fazAndar();
                    }

                    while(y > 300) {
                        y -= 20;
                        fazAndar();
                    }

                    {
                        std::lock_guard<std::mutex> lock03(mtxTrecho03);
                        std::lock_guard<std::mutex> lock04(mtxTrecho04);
                        std::lock_guard<std::mutex> lock07(mtxTrecho07);

                        //! Percorre o trecho03
                        while(x < 300) {
                            x += 20;
                            fazAndar();
                        }

                        //! Percorre o trecho04
                        while(x < 400) {
                            x += 20;
                            fazAndar();
                        }

                        //! Percorre o trecho07
                        while(y < 500) {
                            y += 20;
                            fazAndar();
                        }
                    }
                }
            break;

        case 3: // Trem 3 - ROXO - (bloco inferior direito)
            {
                while(x > 400) {
                    x -= 20;
                    fazAndar();
                }

                {
                    std::lock_guard<std::mutex> lock05(mtxTrecho05);
                    std::lock_guard<std::mutex> lock06(mtxTrecho06);
                    std::lock_guard<std::mutex> lock07(mtxTrecho07);

                    //! Percorre o trecho07
                    while(y > 300) {
                        y -= 20;
                        fazAndar();
                    }

                    //! Percorre o trecho05
                    while(x < 500) {
                        x += 20;
                        fazAndar();
                    }

                    //! Percorre o trecho06
                    while(x < 700) {
                        x += 20;
                        fazAndar();
                    }
                }

                while(y < 500) {
                    y += 20;
                    fazAndar();
                }
            }
        break;
        case 4: // Trem 4 - AZUL -(bloco superior direito)
            {   
                while(x < 700) {
                    x += 20;
                    fazAndar();
                }

                while(y < 300) {
                    y += 20;
                    fazAndar();
                }

                {
                    std::lock_guard<std::mutex> lock02(mtxTrecho02);
                    std::lock_guard<std::mutex> lock06(mtxTrecho06);

                    //! Percorre o trecho06
                    while(x > 500) {
                        x -= 20;
                        fazAndar();
                    }

                    //! Percorre o trecho02
                    while(y > 100) {
                        y -= 20;
                        fazAndar();
                    }
                }
            }
        break;
        case 5: // Trem 5 - VERMELHO -(bloco superior central)
            {
                {
                    std::lock_guard<std::mutex> lockCima(mtxTrechoCima);
                    while(x < 500) {
                        x += 20;
                        fazAndar();
                    }
                }

                {
                    std::lock_guard<std::mutex> lock01(mtxTrecho01);
                    std::lock_guard<std::mutex> lock02(mtxTrecho02);
                    std::lock_guard<std::mutex> lock04(mtxTrecho04);
                    std::lock_guard<std::mutex> lock05(mtxTrecho05);

                    //! Percorre o trecho02
                    while(y < 300) {
                        y += 20;
                        fazAndar();
                    }

                    //! Percorre o trecho05
                    while(x > 400) {
                        x -= 20;
                        fazAndar();
                    }

                    //! Percorre o trecho06
                    while(x > 300) {
                        x -= 20;
                        fazAndar();
                    }

                    //! Percorre o trecho01
                    while(y > 100) {
                        y -= 20;
                        fazAndar();
                    }
                }
            }
        break;
       
case 6: // Trem 6 - PRETO (Anti-horário, conforme PDF )
    {
        // ETAPA 1: Mover Lado Inferior (100, 500) -> (700, 500)
        // Move no trecho exclusivo até o cruzamento com Trecho 07
        while (x < 400) {
            x += 20;
            fazAndar();
        }
        // Trava APENAS o cruzamento 07 para passar
        {
            std::lock_guard<std::mutex> lock07(mtxTrecho07);
            x += 20; // Avança UM passo para cruzar o trilho (ex: para x=420)
            fazAndar();
        }
        // Continua no trecho exclusivo até o fim
        while (x < 700) {
            x += 20;
            fazAndar();
        }

        // ETAPA 2: Mover Lado Direito (700, 500) -> (700, 100)
        // Move no trecho exclusivo até o cruzamento com Trecho 06
        while (y > 300) {
            y -= 20;
            fazAndar();
        }
        // Trava APENAS o cruzamento 06 para passar
        {
            // ATENÇÃO: Verifique se este é o mutex correto para (700,300)
            std::lock_guard<std::mutex> lock06(mtxTrecho06); 
            y -= 20; // Avança UM passo para cruzar
            fazAndar();
        }
        // Continua no trecho exclusivo
        while (y > 100) {
            y -= 20;
            fazAndar();
        }

        // ETAPA 3: Mover Lado Superior (700, 100) -> (100, 100)
        // Move até o cruzamento com Trecho 02
        while (x > 500) {
            x -= 20;
            fazAndar();
        }
        // Trava APENAS o cruzamento 02
        {
            std::lock_guard<std::mutex> lock02(mtxTrecho02);
            x -= 20; // Avança UM passo
            fazAndar();
        }
        // Move até o cruzamento com Trecho 01
        while (x > 300) {
            x -= 20;
            fazAndar();
        }
        // Trava APENAS o cruzamento 01
        {
            std::lock_guard<std::mutex> lock01(mtxTrecho01);
            x -= 20; // Avança UM passo
            fazAndar();
        }
        // Continua no trecho exclusivo
        while (x > 100) {
            x -= 20;
            fazAndar();
        }

        // ETAPA 4: Mover Lado Esquerdo (100, 100) -> (100, 500)
        // Move até o cruzamento com Trecho 03
        while (y < 300) {
            y += 20;
            fazAndar();
        }
        // Trava APENAS o cruzamento 03
        {
            std::lock_guard<std::mutex> lock03(mtxTrecho03);
            y += 20; // Avança UM passo
            fazAndar();
        }
        // Continua no trecho exclusivo até o início
        while (y < 500) {
            y += 20;
            fazAndar();
        }
    }
    break;
        default:
            break;
        }
    }
}
