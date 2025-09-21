// gcc chafariz_glut.c -lglut -lGL -lGLU -lm -o chafariz_glut
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h> 
#include <stdio.h>  

#define ESCAPE 27
#define NUM_PARTICLES 5000
#define GRAVITY 0.0008
#define PARTICLES_PER_FRAME 10

struct s_particle {
  float x, y, veloc_x, veloc_y;
  float r, g, b, a;
  unsigned lifetime;
  unsigned initial_lifetime;
} particles[NUM_PARTICLES];

int window;
int current_particle_index = 0;

void ResetParticle(int i)
{
    float velocity = (float)(rand() % 100) / 4000.0 + 0.02;
    int angle = rand() % 60 - 30;

    particles[i].veloc_x = sin( (M_PI * angle/180.0) ) * velocity;
    particles[i].veloc_y = cos( (M_PI * angle/180.0) ) * velocity * 2.5;

    particles[i].x = 0.0;
    particles[i].y = -1.0;

    particles[i].lifetime = rand() % 100 + 80;
    particles[i].initial_lifetime = particles[i].lifetime;

    particles[i].r = 0.7f;
    particles[i].g = 0.8f;
    particles[i].b = 1.0f;
    particles[i].a = 1.0f;
}

void InitParticles()
{
  int i;
  for(i=0; i<NUM_PARTICLES; i++) {
    particles[i].lifetime = 0;
  }
}

void InitGL(int Width, int Height)
{
  glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPointSize(3.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
  InitParticles();
}

void ReSizeGLScene(int Width, int Height)
{
  if (Height==0) Height=1;
  glViewport(0, 0, Width, Height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
}

void DrawGLScene()
{
  int i;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  // ***** LINHA ALTERADA AQUI *****
  // O segundo valor (-1.5f) move a cena inteira para baixo
  glTranslatef(0.0f, -3.0f, -10.0f);

  for(i=0; i<PARTICLES_PER_FRAME; i++) {
    while(particles[current_particle_index].lifetime > 0) {
        current_particle_index = (current_particle_index + 1) % NUM_PARTICLES;
    }
    ResetParticle(current_particle_index);
    current_particle_index = (current_particle_index + 1) % NUM_PARTICLES;
  }

  glBegin(GL_POINTS);
  for(i=0; i<NUM_PARTICLES; i++) {
    if(particles[i].lifetime > 0) {
      particles[i].veloc_y -= GRAVITY;
      particles[i].x += particles[i].veloc_x;
      particles[i].y += particles[i].veloc_y;
      particles[i].lifetime--;

      float life_ratio = (float)particles[i].lifetime / (float)particles[i].initial_lifetime;
      particles[i].a = life_ratio;

      glColor4f(particles[i].r, particles[i].g, particles[i].b, particles[i].a);
      glVertex3f( particles[i].x, particles[i].y, 0.0f);
    }
  }
  glEnd();

  glutSwapBuffers();
  usleep(15000);
}

void keyPressed(unsigned char key, int x, int y)
{
  if (key == ESCAPE)
  {
    glutDestroyWindow(window);
    exit(0);
  }
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutInitWindowPosition(100, 100);
  window = glutCreateWindow("Chafariz - Estilo do Professor");
  glutDisplayFunc(&DrawGLScene);
  glutIdleFunc(&DrawGLScene);
  glutReshapeFunc(&ReSizeGLScene);
  glutKeyboardFunc(&keyPressed);
  InitGL(800, 600);
  glutMainLoop();

  return 0;
}