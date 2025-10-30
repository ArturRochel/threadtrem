#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->sliderTrem1->setStyleSheet( // Nome corrigido
        "QSlider::groove:horizontal {"
        "    border: 1px solid #bbb;"
        "    background: white;"
        "    height: 5px;"
        "    border-radius: 4px;"
        "}"
        "QSlider::sub-page:horizontal {" // Barra de progresso (antes do marcador)
        "    background: #5BC724; " // Cor verde
        "    border: 1px solid #5BC724;"
        "    height: 10px;"
        "    border-radius: 4px;"
        "}"
        "QSlider::handle:horizontal {" // O marcador (bolinha)
        "    background: #f0f0f0;"
        "    border: 1px solid #777;"
        "    width: 18px;"
        "    margin-top: -4px;"      // Centraliza o marcador verticalmente
        "    margin-bottom: -4px;"   // Centraliza o marcador verticalmente
        "    border-radius: 9px;"
        "}"
    );

    // --- Estilo para o Slider 2 (Azul) ---
    ui->sliderTrem2->setStyleSheet( // Nome corrigido
        "QSlider::groove:horizontal {"
        "    border: 1px solid #bbb;"
        "    background: white;"
        "    height: 5px;"
        "    border-radius: 4px;"
        "}"
        "QSlider::sub-page:horizontal {"
        "    background: #F0820A; " // Cor azul
        "    border: 1px solid #F0820A;"
        "    height: 10px;"
        "    border-radius: 4px;"
        "}"
        "QSlider::handle:horizontal {"
        "    background: #f0f0f0;"
        "    border: 1px solid #777;"
        "    width: 18px;"
        "    margin-top: -4px;"
        "    margin-bottom: -4px;"
        "    border-radius: 9px;"
        "}"
    );

    // --- Estilo para o Slider 3 (Vermelho) ---
    ui->sliderTrem3->setStyleSheet( // Nome corrigido
        "QSlider::groove:horizontal {"
        "    border: 1px solid #bbb;"
        "    background: white;"
        "    height: 5px;"
        "    border-radius: 4px;"
        "}"
        "QSlider::sub-page:horizontal {"
        "    background: #8B27F5; " // Cor vermelha
        "    border: 1px solid #8B27F5;"
        "    height: 10px;"
        "    border-radius: 4px;"
        "}"
        "QSlider::handle:horizontal {"
        "    background: #f0f0f0;"
        "    border: 1px solid #777;"
        "    width: 18px;"
        "    margin-top: -4px;"
        "    margin-bottom: -4px;"
        "    border-radius: 9px;"
        "}"
    );

    ui->sliderTrem4->setStyleSheet( // Nome corrigido
        "QSlider::groove:horizontal {"
        "    border: 1px solid #bbb;"
        "    background: white;"
        "    height: 5px;"
        "    border-radius: 4px;"
        "}"
        "QSlider::sub-page:horizontal {"
        "    background: #2779F5; " // Cor vermelha
        "    border: 1px solid #2779F5;"
        "    height: 10px;"
        "    border-radius: 4px;"
        "}"
        "QSlider::handle:horizontal {"
        "    background: #f0f0f0;"
        "    border: 1px solid #777;"
        "    width: 18px;"
        "    margin-top: -4px;"
        "    margin-bottom: -4px;"
        "    border-radius: 9px;"
        "}"
    );

    ui->sliderTrem5->setStyleSheet( // Nome corrigido
        "QSlider::groove:horizontal {"
        "    border: 1px solid #bbb;"
        "    background: white;"
        "    height: 5px;"
        "    border-radius: 4px;"
        "}"
        "QSlider::sub-page:horizontal {"
        "    background: #D60606; " // Cor vermelha
        "    border: 1px solid #D60606;"
        "    height: 10px;"
        "    border-radius: 4px;"
        "}"
        "QSlider::handle:horizontal {"
        "    background: #f0f0f0;"
        "    border: 1px solid #777;"
        "    width: 18px;"
        "    margin-top: -4px;"
        "    margin-bottom: -4px;"
        "    border-radius: 9px;"
        "}"
    );

    ui->sliderTrem6->setStyleSheet( 
        "QSlider::groove:horizontal {"
        "    border: 1px solid #bbb;"
        "    background: white;"
        "    height: 5px;"
        "    border-radius: 4px;"
        "}"
        "QSlider::sub-page:horizontal {"
        "    background: #000000; "
        "    border: 1px solid #000000;"
        "    height: 10px;"
        "    border-radius: 4px;"
        "}"
        "QSlider::handle:horizontal {"
        "    background: #f0f0f0;"
        "    border: 1px solid #777;"
        "    width: 18px;"
        "    margin-top: -4px;"
        "    margin-bottom: -4px;"
        "    border-radius: 9px;"
        "}"
    );

    //Cria o trem com seu (ID, posição X, posição Y)
    trem1 = new Trem(1,100,300);
    trem2 = new Trem(2,400,500);
    trem3 = new Trem(3,400,300);  // ADICIONANDO OS TRENS
    trem4 = new Trem(4,500,100);
    trem5 = new Trem(5,300,100);
    trem6 = new Trem(6,700,500);
    /*
     * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
     * Ou seja, sempre que o sinal UPDATEGUI foi chamado, será executada a função UPDATEINTERFACE.
     * Os 3 parâmetros INT do sinal serão utilizados na função.
     * Trem1 e Trem2 são os objetos que podem chamar o sinal.    trem2 = new Trem(2, 50, 150); // Posição inicial do T2
 Se um outro objeto chamar o
     * sinal UPDATEGUI, não haverá execução da função UPDATEINTERFACE
     */


    // ADICIONANDO OS TRENS PARA ATUALIZAR NA TELA
    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem5,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem6,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));

    // Sincroniza a velocidade inicial do trem em 50, o mesmo valor inicial do slide
    trem1->setVelocidade(ui->sliderTrem1->value());
    trem2->setVelocidade(ui->sliderTrem2->value());
    trem3->setVelocidade(ui->sliderTrem3->value());
    trem4->setVelocidade(ui->sliderTrem4->value());
    trem5->setVelocidade(ui->sliderTrem5->value());
    trem6->setVelocidade(ui->sliderTrem6->value());

    // Controle de velocidade dos trens em tempo de execução com controle por slide
    connect(ui->sliderTrem1, &QSlider::valueChanged, this, [=](int value){
    trem1->setVelocidade(value);
    });
    connect(ui->sliderTrem2, &QSlider::valueChanged, this, [=](int value){
    trem2->setVelocidade(value);
    });
    connect(ui->sliderTrem3, &QSlider::valueChanged, this, [=](int value){
    trem3->setVelocidade(value);
    });
    connect(ui->sliderTrem4, &QSlider::valueChanged, this, [=](int value){
    trem4->setVelocidade(value);
    });
    connect(ui->sliderTrem5, &QSlider::valueChanged, this, [=](int value){
    trem5->setVelocidade(value);
    });
    connect(ui->sliderTrem6, &QSlider::valueChanged, this, [=](int value){
    trem6->setVelocidade(value);
    });


    // colocando aqui para inicair os trens assim que o programa é iniciado
    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
    trem6->start();

}

//Função que será executada quando o sinal UPDATEGUI for emitido
void MainWindow::updateInterface(int id, int x, int y){
    switch(id){
    // ATUALIZANDO TAMANHO DOS LABELS (de 21,17 para 42,34)
    case 1: //Atualiza a posição do objeto da tela (quadrado) que representa o trem1
        ui->label_trem1->setGeometry(x,y,42,34);
        break;
    case 2: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem2->setGeometry(x,y,42,34);
        break;
    case 3:
        ui->label_trem3->setGeometry(x,y,42,34);
        break;
    case 4:
        ui->label_trem4->setGeometry(x,y,42,34);
        break;
    case 5:
        ui->label_trem5->setGeometry(x,y,42,34);
        break;
    case 6:
        ui->label_trem6->setGeometry(x,y,42,34);
         break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
