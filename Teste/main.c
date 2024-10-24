#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <freeglut.h>  
#include <stdio.h>
#include <string.h>

// Função para fazer o texto usando GLUT
void renderText(const char* text, float x, float y) {
    glRasterPos2f(x, y); 
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c); 
    }
}


// Função para fazer o bloco na tela
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


    renderText("SENHA: 1234", -0.8f, 0.5f);

    
    renderText("GUICHE: 5", -0.8f, 0.2f);


    renderText("PRIORIDADE:", -0.8f, -0.1f);


    renderBlock(-0.8f, -0.5f, 0.8f, -0.2f, 1.0f, 0.0f, 0.0f);
}

int main(int argc, char** argv) {
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