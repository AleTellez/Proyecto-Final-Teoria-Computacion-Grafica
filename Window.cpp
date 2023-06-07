#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	muevex = 2.0f;
	muevecofre = 0.0f;
	movcarro1 = 0.0f;
	movcarro2 = 0.0f;
	subebajaheli = 50.0f;
	avanzaretrocedeheli = 0.0f;
	izqderheli = 0.0f;
	luzdcarro1 = -150.0f;
	luzdcarro2 = -150.0f;
	luztcarro1 = -250.0f;
	luztcarro2 = -250.0f;
	movc1 = 1.0f;
	interruptor = 0;
	
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "PROYECTO FINAL", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}
GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}




void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_Y)
	{
		theWindow-> muevex += 1.0;
	}
	if (key == GLFW_KEY_U)
	{
		theWindow-> muevex -= 1.0;
	}
	if (key == GLFW_KEY_O)
	{
		if (theWindow->muevecofre <= 20.0)
		{
			theWindow->muevecofre += 1.0;
		}
		else
		{
			theWindow->muevecofre -= 20.0;
		}
	}

	if (key == GLFW_KEY_F)
	{
		theWindow->interruptor = 1;
	}
	if (key == GLFW_KEY_G)
	{
		theWindow->interruptor = 0;
	}
	if (key == GLFW_KEY_G)
	{
		theWindow->avanzaretrocedeheli += 2.0;
	}
	if (key == GLFW_KEY_B)
	{	
		theWindow->avanzaretrocedeheli -= 2.0;
	}
	if (key == GLFW_KEY_V)
	{
		theWindow->izqderheli += 2.0;
	}
	if (key == GLFW_KEY_N)
	{
		theWindow->izqderheli -= 2.0;
	}
	
	if (key == GLFW_KEY_1)
	{
		theWindow->movcarro1 += 2.0;
		theWindow->luzdcarro1 += 2.0;
		theWindow->luztcarro1 += 2.0;
		theWindow->movcarro2 += 2.0;
		theWindow->luzdcarro2 += 2.0;
		theWindow->luztcarro2 += 2.0;
		theWindow->movc1 = 1.0f;
	}
	if (key == GLFW_KEY_2)
	{
		theWindow->movcarro1 -= 2.0;
		theWindow->luzdcarro1 -= 2.0;
		theWindow->luztcarro1 -= 2.0;
		theWindow->movcarro2 -= 2.0;
		theWindow->luzdcarro2 -= 2.0;
		theWindow->luztcarro2 -= 2.0;
		theWindow->movc1 = 0.0f;
	}
	if (key == GLFW_KEY_3)
	{
		theWindow->movcarro2 += 2.0;	
		theWindow->luzdcarro2 += 2.0;
		theWindow->luztcarro2 += 2.0;
	}
	if (key == GLFW_KEY_4)
	{
		theWindow->movcarro2 -= 2.0;
		theWindow->luzdcarro2 -= 2.0;
		theWindow->luztcarro2 -= 2.0;
	}
	if (key == GLFW_KEY_Z)
	{
		theWindow->ruedaPanda = 1;
	}
	


	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
