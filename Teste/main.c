#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <freeglut.h>  // Inclua GLUT para renderizar texto
#include <stdio.h>
#include <string.h>

// Função para desenhar texto usando GLUT
void renderText(const char* text, float x, float y) {
    glRasterPos2f(x, y); // Define a posição do texto
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c); // Renderiza caractere por caractere
    }
}

// Função para desenhar um retângulo (bloco colorido) na tela
void renderBlock(float x1, float y1, float x2, float y2, float r, float g, float b) {
    glColor3f(r, g, b); // Define a cor do bloco
    glBegin(GL_QUADS);  // Começa a desenhar o quadrilátero
    glVertex2f(x1, y1);  // Canto inferior esquerdo
    glVertex2f(x2, y1);  // Canto inferior direito
    glVertex2f(x2, y2);  // Canto superior direito
    glVertex2f(x1, y2);  // Canto superior esquerdo
    glEnd();
}

// Função para desenhar a tela com as informações
void drawScreen() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Cor de fundo
    glClear(GL_COLOR_BUFFER_BIT);

    // Definir cor preta para os textos
    glColor3f(0.0f, 0.0f, 0.0f); // Cor preta

    // Exibir SENHA
    renderText("SENHA: 1234", -0.8f, 0.5f);

    // Exibir GUICHÊ
    renderText("GUICHE: 5", -0.8f, 0.2f);

    // Exibir PRIORIDADE
    renderText("PRIORIDADE:", -0.8f, -0.1f);

    // Desenhar o bloco de prioridade (metade da tela, abaixo do texto "PRIORIDADE")
    renderBlock(-0.8f, -0.5f, 0.8f, -0.2f, 1.0f, 0.0f, 0.0f); // Bloco vermelho
}

int main(int argc, char** argv) {
    // Inicializa GLUT
    glutInit(&argc, argv);

    // Inicializa GLFW
    if (!glfwInit()) {
        printf("Erro ao inicializar GLFW\n");
        return -1;
    }

    // Cria uma janela OpenGL
    GLFWwindow* window = glfwCreateWindow(800, 600, "Sistema de Senhas", NULL, NULL);
    if (!window) {
        printf("Erro ao criar janela\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    // Loop da aplicação
    while (!glfwWindowShouldClose(window)) {
        drawScreen(); // Desenhar a tela

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
