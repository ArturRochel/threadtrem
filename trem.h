#ifndef TREM_H
#define TREM_H

#include <QThread>
#include <mutex>
/*
 * Classe Trem herda QThread
 * Classe Trem passa a ser uma thread.
 * A função START inicializa a thread. Após inicializada, a thread irá executar a função RUN.
 * Para parar a execução da função RUN da thread, basta executar a função TERMINATE.
 *
*/
class Trem: public QThread{
 Q_OBJECT
public:
    Trem(int,int,int);  //construtor
    void run(); // Método para os trens andarem
    void setVelocidade(int velocidadeDoTrem); // Método para alterar a velocidade em tempo de execução
    int getDelay() const; // Devolve a conversão de velocidade em tempo de espera

    // Mutexes para controlar cada um dos pontos críticos
    static std::mutex mtxTrecho01;
    static std::mutex mtxTrecho02;
    static std::mutex mtxTrecho03;
    static std::mutex mtxTrecho04;
    static std::mutex mtxTrecho05;
    static std::mutex mtxTrecho06;
    static std::mutex mtxTrecho07;
    static std::mutex mtxTrecho08;
    static std::mutex mtxTrecho09;
    static std::mutex mtxTrecho10;
    static std::mutex mtxTrecho11;
    static std::mutex mtxTrecho12;

//Cria um sinal
signals:
    void updateGUI(int,int,int);

private:
   int x;           //posição X do trem na tela
   int y;           //posição Y do trem na tela
   int ID;          //ID do trem
   int velocidade;  //Velocidade. É o tempo de dormir em milisegundos entre a mudança de posição do trem
   void fazAndar(); //Método para atualizar a posição do trem com base na valocidade
};



#endif // TREM_H
