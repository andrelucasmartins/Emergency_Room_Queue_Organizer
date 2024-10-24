#include <GL/glut.h>
#include <iostream>
#include <string.h>

// Variáveis para armazenar a senha, seleção de checkbox, e prioridade
char senha[256] = "";
bool checkbox = false;
int prioridade = 0; // 0: Azul, 1: Verde, 2: Amarelo, 3: Vermelho

void desenharTexto(const char *texto, float x, float y)
{
  glRasterPos2f(x, y);
  while (*texto)
  {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *texto);
    texto++;
  }
}

// Função para desenhar o campo de senha
void desenharCampoSenha()
{
  glColor3f(1, 1, 1);               // Cor branca
  glRectf(-0.8f, 0.6f, 0.8f, 0.4f); // Retângulo do campo

  glColor3f(0, 0, 0); // Cor preta para o texto
  desenharTexto("Senha:", -0.75f, 0.55f);

  // Desenha a senha como asteriscos (por segurança)
  desenharTexto(senha, -0.3f, 0.55f);
}

// Função para desenhar o checkbox
void desenharCheckbox()
{
  glColor3f(1, 1, 1);                // Cor branca
  glRectf(-0.8f, 0.2f, -0.6f, 0.0f); // Caixa de checkbox

  // Se o checkbox estiver marcado, desenhar um "X"
  if (checkbox)
  {
    glColor3f(0, 0, 0); // Preto para o "X"
    desenharTexto("X", -0.75f, 0.1f);
  }

  glColor3f(0, 0, 0); // Texto preto
  desenharTexto("Concordo com os termos", -0.55f, 0.1f);
}

// Função para desenhar os botões de prioridade com cores
void desenharPrioridade()
{
  // Azul
  glColor3f(0, 0, 1);
  glRectf(-0.8f, -0.2f, -0.6f, -0.4f);
  desenharTexto("Baixa", -0.75f, -0.25f);

  // Verde
  glColor3f(0, 1, 0);
  glRectf(-0.4f, -0.2f, -0.2f, -0.4f);
  desenharTexto("Normal", -0.35f, -0.25f);

  // Amarelo
  glColor3f(1, 1, 0);
  glRectf(0.0f, -0.2f, 0.2f, -0.4f);
  desenharTexto("Alta", 0.05f, -0.25f);

  // Vermelho
  glColor3f(1, 0, 0);
  glRectf(0.4f, -0.2f, 0.6f, -0.4f);
  desenharTexto("Urgente", 0.45f, -0.25f);
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  desenharCampoSenha();
  desenharCheckbox();
  desenharPrioridade();

  glutSwapBuffers();
}

// Função para lidar com o teclado
void keyboard(unsigned char key, int x, int y)
{
  printf("Tecla pressionada: %c\n", key);
  printf("Posicao: %d, %d\n", x, y);

  if (key == 27) // Tecla ESC para sair
    exit(0);

  if (key >= 32 && key <= 126)
  {
    int len = strlen(senha);
    if (len < 255)
    {
      senha[len] = key;
      senha[len + 1] = '\0';
    }
  }
  if (key == 8 && strlen(senha) > 0)
  { // Tecla BACKSPACE
    senha[strlen(senha) - 1] = '\0';
  }

  glutPostRedisplay();
}

// Função para lidar com cliques do mouse
void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    float posX = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 2.0f - 1.0f;
    float posY = 1.0f - (float)y / glutGet(GLUT_WINDOW_HEIGHT) * 2.0f;

    // Verifica se clicou na checkbox
    if (posX >= -0.8f && posX <= -0.6f && posY >= 0.0f && posY <= 0.2f)
    {
      checkbox = !checkbox;
    }

    // Verifica se clicou em uma das áreas de prioridade
    if (posY >= -0.4f && posY <= -0.2f)
    {
      if (posX >= -0.8f && posX <= -0.6f)
        prioridade = 0; // Azul
      if (posX >= -0.4f && posX <= -0.2f)
        prioridade = 1; // Verde
      if (posX >= 0.0f && posX <= 0.2f)
        prioridade = 2; // Amarelo
      if (posX >= 0.4f && posX <= 0.6f)
        prioridade = 3; // Vermelho
    }

    glutPostRedisplay();
  }
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Sistema de Prioridade do Pronto Socorro");

  glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Fundo cinza

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);

  glutMainLoop();
  return 0;
}
