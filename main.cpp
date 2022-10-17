#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Planetas:                Venus | Mercurio | Terra | Marte | Júpiter | Saturno | Urano | Netuno

// Raios dos Planetas
double raios[8] =           {1    , 1.5      , 2     , 1.75  , 2.1     , 2.2     , 2     , 1.1      };

// Velociodade de Translação dos Planetas
double velocidadesT[8] =    {1.8  , 0.64     , 0.44  , 0.23  , 13      , 5.46    , 1.95  , 1        };

// Velocidade de Rotação dos Planetas
double velocidadesR[8] =    {0.016, 0.004    , 1     , 0.97  , 2.4     , 2.34    , 1.41  , 1.5      };

// Especificação das cores em RGB dos Planetas
double rs[8] =              {1.0    , 0.4  , 0.0   , 1.0  , 1.0   , 0.8    ,0.4     , 0.8 };
double gs[8] =              {0.5    , 0.2  , 0.5   , 0.0  , 0.8   , 0.5    ,0.7    , 0.8 };
double bs[8] =              {0.0    , 0.0  , 1.0   , 0.0  , 0.0   , 0.0    ,0.2    , 1.0 };

// Especificação da quantidade de aneis e satelites de cada planeta
int aneis[8] =              {0    , 0        , 0     , 1     , 1       , 4       , 2     , 1        };
int satelites[8] =          {0    , 0        , 1     , 2     , 1       , 1       , 1     , 2        };

// Especificacao dos raios da elipse (Orbitas)
int raioMaior=2;
int raioMenor=1;

//---------------------------------------------- Control ---------------------------------------------------------
// Angulos dos Satelites e planetas
double angsSatelite[8] =    {0    , 0        , 0     , 0     , 0       , 0       , 0     , 0        };
double angsPlaneta[8] =     {0    , 0        , 0     , 0     , 0       , 0       , 0     , 0        };

// Exibicao de cada Planeta
bool show[8] =              {true , true     , true  , true  , true    , true    , true  , true     };

// Exibicao de todas as Orbitas
bool showOrbita = true;

// Ativar/Desativar efeito de animacao do sistema
bool animate = true;

// Calaculo e exibicao do tempo de transalacao da Terra
int tempoTerra = 0;
bool showedTempoTerra=false;


// Função callback chamada para fazer o desenho da orbita
void DesenhaOrbita(float raio)
{

     float angulo, incremento;
     int vertices = 100;

     // Especifica que a cor corrente é branca RGB
     glColor3f(1.0f, 1.0f, 1.0f);

	 // Especifica o tamanho do ponto
	 glPointSize(4.0f);

     incremento = (2 * M_PI) / vertices;

    // Desenha um círculo de linhas
     glBegin(GL_LINES);
     for(angulo=0; angulo<2*M_PI; angulo+=incremento){
        glVertex2f(raioMaior*raio*cos(angulo),raioMenor*raio*sin(angulo));
        glVertex2d(raioMaior*raio*cos(angulo+incremento), raioMenor*raio*sin(angulo+incremento));
     }
     glEnd();


}

// Funcao callback que desenha circunferencias estaticas
void DesenhaEstatico(float r,float g,float b, float raio){



     float angulo, incremento;
     int vertices = 50;

     // Especifica que a cor RGB
     glColor3f(r, g, b);

	 // Especifica o tamanho do ponto
	 glPointSize(1.0f);

     incremento = (2 * M_PI) / vertices;

    glBegin(GL_POLYGON);
     for(angulo=0; angulo<2*M_PI; angulo+=incremento){
        glVertex2f(raio*cos(angulo),raio*sin(angulo));
        glVertex2d(raio*cos(angulo+incremento), raio*sin(angulo+incremento));
     }
    glEnd();


}

// Função callback chamada para fazer o desenho do planeta
// E preciso informar o planeta e o raio da orbita que se encontra
void DesenhaPlaneta(int planeta, float raioOrbita){

    // Resgatando as propriedas do planeta e orbita referente
    float raio = raios[planeta];
    float r = rs[planeta];
    float g = gs[planeta];
    float b = bs[planeta];
    int qtdAnel = aneis[planeta];
    int qtdSatelite = satelites[planeta];


     float angulo, incremento;
     int vertices = 50;

     // Especifica que a cor RGB
     glColor3f(r, g, b);

	 // Especifica o tamanho do ponto
	 glPointSize(2.0f);

     incremento = (2 * M_PI) / vertices;


    glBegin(GL_POLYGON);
     for(angulo=0; angulo<2*M_PI; angulo+=incremento){
        glVertex2f(raio*cos(angulo),raio*sin(angulo));
        glVertex2d(raio*cos(angulo+incremento), raio*sin(angulo+incremento));
     }
    glEnd();

    for(int anel=1; anel<=qtdAnel; anel++){
        DesenhaOrbita(raio+anel*0.5);
    }

    switch(qtdSatelite){
    case 1: {
        glPushMatrix();
        //glRotatef(angSatelite[planeta],0.0f,0.0f,1.0f);
        glTranslated(raioMaior*(raio+0.5)*cos(angsSatelite[planeta]),raioMenor*(raio+0.5)*sin(angsSatelite[planeta]),0);
        DesenhaEstatico(0.8,0.8,0.8, 0.5);
        glPopMatrix();
        break;
    }
    case 2: {
        glPushMatrix();
        //glRotatef(angSatelite[planeta],0.0f,0.0f,1.0f);
        glTranslated(raioMaior*(raio+0.5)*cos(angsSatelite[planeta]),raioMenor*(raio+0.5)*sin(angsSatelite[planeta]),0);
        DesenhaEstatico(0.8,0.8,0.8, 0.5);
        glPopMatrix();
        glPushMatrix();
        //glRotatef(angSatelite[planeta],0.0f,0.0f,1.0f);
        glTranslated(-raioMaior*(raio+0.5)*cos(angsSatelite[planeta]),-raioMenor*(raio+0.5)*sin(angsSatelite[planeta]),0);
        DesenhaEstatico(0.8,0.8,0.8, 0.5);
        glPopMatrix();
        break;
    }

    }



}


// Duncao responsavel por desenhar o sistema solar
void Desenha()
{

    // Muda para o sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa a matriz de transformacao corrente
	glLoadIdentity();

    // Limpa a janela de visualização com a cor
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Desenha o Sol
    DesenhaEstatico(1, 1, 0, 3);

    // Desenha os 8 planetas
    // e 8 orbitas
    // satelites e aneis
	for(int planeta = 1; planeta <= 8; planeta++){
        glPushMatrix();

        if(showOrbita)DesenhaOrbita(5*planeta);
        //glRotatef(angs[planeta-1],0.0f,0.0f,1.0f);
        glTranslated(10*planeta*cos(angsPlaneta[planeta-1]),5*planeta*sin(angsPlaneta[planeta-1]),0);
        if(show[planeta-1]) DesenhaPlaneta(planeta-1, 5*planeta);
        glPopMatrix();
	}

	// Executa os comandos OpenGL
	glutSwapBuffers();

}

// Funcao callback chamada pela GLUT a cada intervalo de tempo
void Anima(int value)
{

    /*
    * Alterar os angulos respectivos dos satelites e planetas
    * A cada chamada do metodo `Anima'
    */
    double base = 0.00104;

    for(int planeta = 0; planeta<8; planeta++){
        angsSatelite[planeta] += base * velocidadesR[planeta];
    }

    for(int planeta = 0; planeta<8; planeta++){
        angsPlaneta[planeta] += base * velocidadesT[planeta];
    }

    /*
    * Calculo da Translacao do planeta Terra
    */
    tempoTerra+=10;

    if(angsPlaneta[2]>6.28 && !showedTempoTerra){
        showedTempoTerra=true;
        printf("A Terra levou %5d segundos para dar uma volta no sol", tempoTerra/100);
    }

	glutPostRedisplay();
    if(animate) glutTimerFunc(10,Anima, 1);
}


// Funcao callback chamada quando tiver algum evento de teclado
void Teclado (unsigned char key, int x, int y){

    /*
    * Controle de visualizacao dos Planetas
    * Para as teclas alfa-numericas de 1 a 8
    */
    show[key - 49] = !show[key - 49];

    /*
    * Controle de visualizacao das Orbitas
    * Para as teclas `o' ou `O'
    */
    if(key == 79 || key == 111){
        showOrbita = ! showOrbita;
    }

    /*
    * Controle de animacao do sistema solar
    * Para as teclas `p' ou `P'
    */
    if(key == 80 || key == 112){
        animate = !animate;
        if(animate){
            glutTimerFunc(100,Anima, 1);
        }

    }

    glutPostRedisplay();


}



// Inicializa parâmetros de rendering
void Inicializa (void)
{
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{

    GLsizei largura, altura;

    // Evita a divisao por zero
    if(h == 0) h = 1;

    // Atualiza as variáveis
    largura = w;
    altura = h;

    glViewport(0, 0, largura, altura);

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Estabelece a janela de seleção (esquerda, direita, inferior,
    // superior) mantendo a proporção com a janela de visualização
    if (largura <= altura)
        gluOrtho2D (-40.0f, 40.0f, -40.0f*altura/largura, 40.0f*altura/largura);
    else
        gluOrtho2D (-40.0f*largura/altura, 40.0f*largura/altura, -40.0f, 40.0f);

}
// Programa Principal
int main(int argc, char *argv[])
{
    // Utilizada para inicializar a biblioteca GLUT
    glutInit(&argc, argv);
    // Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // Especifica o tamanho e localização inicial em pixels da janela GLUT
	glutInitWindowSize(1000,1000);
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Sistema Solar");
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);
	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);
    // Registra a função callback de captura das teclas do Teclado
    glutKeyboardFunc(Teclado);
	// Registra a fun��o callback que ser� chamada a cada intervalo de tempo
	glutTimerFunc(100, Anima, 1);
	// Chama a função responsável por fazer as inicializações
	Inicializa();
	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();
}


