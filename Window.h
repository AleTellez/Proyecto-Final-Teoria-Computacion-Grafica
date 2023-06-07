#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();
	GLfloat getmuevex() { return muevex; }
	GLfloat getmuevecofre() { return muevecofre; }
	GLfloat getmovcarro1() { return movcarro1; }
	GLfloat getmovcarro2() { return movcarro2; }
	GLfloat getsubebajaheli() { return subebajaheli; }
	GLfloat getavanzaretrocedeheli() { return avanzaretrocedeheli; }
	GLfloat getizqderheli() { return izqderheli; }
	GLfloat getluzdcarro1() { return luzdcarro1; }
	GLfloat getluztcarro1() { return luztcarro1; }
	GLfloat getluzdcarro2() { return luzdcarro2; }
	GLfloat getluztcarro2() { return luztcarro2; }
	GLfloat getmovc1() { return movc1; }
	GLfloat getinterruptor() { return interruptor; }
	GLfloat getRuedaPanda() { return ruedaPanda; }
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	
	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat muevex;
	GLfloat muevecofre;
	GLfloat movcarro1;
	GLfloat movcarro2;
	GLfloat subebajaheli;
	GLfloat avanzaretrocedeheli;
	GLfloat izqderheli;
	GLfloat luzdcarro1;
	GLfloat luztcarro1;
	GLfloat luzdcarro2;
	GLfloat luztcarro2;
	GLfloat movc1;
	GLfloat ruedaPanda;
	GLint interruptor;
	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};

