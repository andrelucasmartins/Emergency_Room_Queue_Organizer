#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <freeglut.h>  
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SENHA_MAX 100

// Variáveis para armazenar os dados de entrada
int senha;
int guiche;
int prioridade;
float r = 1.0f, g = 0.0f, b = 0.0f; // Cor padrão do retângulo

// Função para definir a cor com base na prioridade
void defineColor(int prioridade) {
    switch (prioridade) {
    case 1: r = 1.0f; g = 0.0f; b = 0.0f; break; // Vermelho
    case 2: r = 1.0f; g = 0.5f; b = 0.0f; break; // Laranja
    case 3: r = 1.0f; g = 1.0f; b = 0.0f; break; // Amarelo
    case 4: r = 0.0f; g = 1.0f; b = 0.0f; break; // Verde
    case 5: r = 0.0f; g = 0.0f; b = 1.0f; break; // Azul
    default: r = 1.0f; g = 0.0f; b = 0.0f; break; // Padrão vermelho
    }
}

// Função para ler a senha armazenada em um arquivo
int loadSenha() {
    FILE* file = fopen("senha.txt", "r");
    int senha = 0; 

    if (file) {
        fscanf_s(file, "%d", &senha);
        fclose(file);
    }

    return senha;
}

// Função para salvar a senha atual em um arquivo
void saveSenha(int senha) {
    FILE* file = fopen("senha.txt", "w");

    if (file) {
        fprintf(file, "%d", senha);
        fclose(file);
    }
}

// Função para fazer o texto usando GLUT
void renderText(const char* text, float x, float y) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

// Função para renderizar o bloco na tela
void renderBlock(float x1, float y1, float x2, float y2, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

// Função para imprimir os textos na tela, senha, guiche e prioridade
void drawScreen() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 0.0f);

    char buffer[50];
    snprintf(buffer, sizeof(buffer), "SENHA: %d", senha);
    renderText(buffer, -0.8f, 0.5f);

    snprintf(buffer, sizeof(buffer), "GUICHE: %d", guiche);
    renderText(buffer, -0.8f, 0.2f);

    snprintf(buffer, sizeof(buffer), "PRIORIDADE:", prioridade);
    renderText(buffer, -0.8f, -0.1f);

    // Retângulo com cor da prioridade
    renderBlock(-0.8f, -0.5f, 0.8f, -0.2f, r, g, b); 
}

int main(int argc, char** argv) {
    
    srand(time(NULL));

    senha = loadSenha();
    senha = (senha % SENHA_MAX) + 1;
    
    saveSenha(senha);

    guiche = (rand() % 3) + 1;

    printf("Digite a prioridade (1 a 5): ");
    scanf_s("%d", &prioridade);

  
    defineColor(prioridade);

    // Inicia o GLUT e o GLFW
    glutInit(&argc, argv);

    if (!glfwInit()) {
        printf("Erro ao inicializar GLFW\n");
        return -1;
    }

    // Cria uma janela com OpenGL
    GLFWwindow* window = glfwCreateWindow(800, 600, "Queue Organizer", NULL, NULL);
    if (!window) {
        printf("Erro ao criar janela\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    while (!glfwWindowShouldClose(window)) {
        drawScreen();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
