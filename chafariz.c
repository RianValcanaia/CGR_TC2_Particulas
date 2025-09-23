// gcc chafariz.c -lglut -lGL -lGLU -lm -o chafariz
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h> 
#include <stdio.h>  

#define ESC 27
#define NUM_PARTICULAS 5000
#define GRAVIDADE 0.0008
#define PARTICULAS_POR_FRAME 10

struct s_particulas {
    float x, y, veloc_x, veloc_y;
    float r, g, b, a;  //a = transparencia
    unsigned tempo_vida;  // tempo de vida para fadeout
    unsigned tempo_vida_inicial;
} particulas[NUM_PARTICULAS];

int janela;  
int index_atual_particula = 0;

void reseta_Particulas(int i){
    float velocidade = (float)(rand() % 100) / 4000.0 + 0.02;
    int angulo = rand() % 91 - 45;  // entre -45 a 45 graus

    // velocidade em x e y apartir do angulo
    particulas[i].veloc_x = sin( (M_PI * angulo/180.0) ) * velocidade;
    particulas[i].veloc_y = cos( (M_PI * angulo/180.0) ) * velocidade * 2.5;

    // posicao inicial
    particulas[i].x = 0.0;
    particulas[i].y = -1.0;

    // tempo de vida aleatorio
    particulas[i].tempo_vida = rand() % 100 + 80;
    particulas[i].tempo_vida_inicial = particulas[i].tempo_vida;

    // cor
    particulas[i].r = 0.7f;
    particulas[i].g = 0.8f;
    particulas[i].b = 1.0f;
    particulas[i].a = 1.0f;
}

void inicia_Particulas(){
    int i;
    for(i = 0; i < NUM_PARTICULAS; i++) {
        particulas[i].tempo_vida = 0;  // inicia todas as particulas como mortas
    }
}

void inicia_GL(int largura, int altura){
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    
    glEnable(GL_BLEND);  // habilita transparencia
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  // alpha blending
    glPointSize(3.0f);  // tamanho dos pontos
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)largura/(GLfloat)altura,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
    inicia_Particulas();
}

void refaz_tamanho(int largura, int altura){  // ajusta o viewport quando a janea eh redimensionada
    if (altura == 0) altura = 1;  // evita divisao por zero
    glViewport(0, 0, largura, altura);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(45.0f,(GLfloat)largura/(GLfloat)altura,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void desenha_cena(){  // funcao que desenha cada frame
    int i;

    // limpa a tela e o buffer de profuncidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, -3.0f, -10.0f);

    // cria novas particulas a cada frame
    for(i = 0; i < PARTICULAS_POR_FRAME; i++) {
        // procura uma particula morta
        while(particulas[index_atual_particula].tempo_vida > 0) {
            index_atual_particula = (index_atual_particula + 1) % NUM_PARTICULAS;
        }

        // renasce a particula
        reseta_Particulas(index_atual_particula);
        // avanca para a proxima
        index_atual_particula = (index_atual_particula + 1) % NUM_PARTICULAS;
    }

    // desenha todas as particulas vivas
    glBegin(GL_POINTS);
    for(i = 0; i < NUM_PARTICULAS; i++) {
        if(particulas[i].tempo_vida > 0) {
            // atualiza a fisica da particula
            particulas[i].veloc_y -= GRAVIDADE;  // aplica a gravidade
            particulas[i].x += particulas[i].veloc_x;  // move em x
            particulas[i].y += particulas[i].veloc_y;  // move em y
            particulas[i].tempo_vida--;  // reduz o tempo de vida

            // ajusta transparencia conforme vida restante
            float life_ratio = (float)particulas[i].tempo_vida / (float)particulas[i].tempo_vida_inicial;
            particulas[i].a = life_ratio;
            
            // define a cor e desenha o ponto
            glColor4f(particulas[i].r, particulas[i].g, particulas[i].b, particulas[i].a);
            glVertex3f( particulas[i].x, particulas[i].y, 0.0f);
        }
    }
    glEnd();

    glutSwapBuffers();

    // pausa de 15ms
    usleep(15000);
}

void tecla_pressionada(unsigned char key, int x, int y){
    if (key == ESC){
        glutDestroyWindow(janela);
        exit(0);
    }
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    janela = glutCreateWindow("Chafariz");
    glutDisplayFunc(&desenha_cena);
    glutIdleFunc(&desenha_cena);
    glutReshapeFunc(&refaz_tamanho);
    glutKeyboardFunc(&tecla_pressionada);
    inicia_GL(800, 600);
    glutMainLoop();

    return 0;
}