/*
Semestre 2023-1
Práctica 7: ILUMINACIÓN
*/

#define STB_IMAGE_IMPLEMENTATION
#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <ctime>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"
//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture DadoTexture;
Texture octaTexture;
Texture AutoTexture;
Texture LampTexture;

Model Kitt_M;
Model Llanta_M;
Model Camino_M;
Model Blackhawk_M;
Model Dado_M;

Skybox skybox;
//materiales
Material Material_brillante;
Material Material_opaco;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";




//cálculo del promedio de las normales para sombreado de Phong
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}



void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	unsigned int vegetacionIndices[] = {
		0, 1, 2,
		0, 2, 3,
		4,5,6,
		4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,
	};
	calcAverageNormals(indices, 12, vertices, 32, 8, 5);



	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

void CrearDado()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,
		// back
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20,
	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
// average normals
	GLfloat cubo_vertices[] = {
		// front
		//x		y		z		S		T			NX		NY		NZ
		-0.5f, -0.5f,  0.5f,	0.0f,  0.5f,		0.0f,	0.0f,	-1.0f,	//0
		0.5f, -0.5f,  0.5f,		0.25f,	0.5f,		0.0f,	0.0f,	-1.0f,	//1
		0.5f,  0.5f,  0.5f,		0.2482642105915f,	0.2658323504421f,		0.0f,	0.0f,	-1.0f,	//2
		-0.5f,  0.5f,  0.5f,	0.0012703643674f,	0.2658323504421f,		0.0f,	0.0f,	-1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	    0.25f,  0.5f,		-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,	0.5f,	0.5f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	0.4980489477333f,	0.2658323504421f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	    0.2482642105915f,	0.2658323504421f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	0.5f,  0.5f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		0.7492542489275f,	0.4995752122814f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		0.7492542489275f,	0.2659941542272f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.4980489477333f,	0.2658323504421f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.5022352841099f,  0.7430746973834f,		1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	0.7478336848751f,	0.7430746973834f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	0.7492542489275f,	0.4995752122814f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.5f,	0.5f,		1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.4980489477333f,  0.2658323504421f,		0.0f,	1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	0.7492542489275f,	0.2659941542272f,		0.0f,	1.0f,	0.0f,
		 0.5f,  -0.5f,  -0.5f,	0.7500659415561f,	0.0064886029743f,		0.0f,	1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.4975210452302f,	0.0082951589347f,		0.0f,	1.0f,	0.0f,

		//UP
		 //x		y		z		S		T
		 -0.5f, 0.5f,  0.5f,	0.7492542489275f,  0.4995752122814f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f,	0.5f,		0.0f,	-1.0f,	0.0f,
		  0.5f, 0.5f,  -0.5f,	1.0f,	0.264843508621f,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 0.5f,  -0.5f,	0.7492542489275f,	0.2659941542272f,		0.0f,	-1.0f,	0.0f,

	};

	Mesh* dado = new Mesh();
	dado->CreateMesh(cubo_vertices, cubo_indices, 192, 36);
	meshList.push_back(dado);

}
/////////////////////////////////////////////////////////////////////////////
////////////////////////////// O C T A E D R O /////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void CrearOcta()
{
	unsigned int octa_indices[] = {
		0,1,2,
		3,4,5,
		6,7,8,
		9,10,11,
		12,13,14,
		15,16,17,
		18,19,20,
		21,22,23,

	};
	/////////////////////////
	/////////////////////////
	GLfloat octa_vertices[] = {
		//arriba
		//			x	y	 z            S		T		NX		NY		NZ
				-0.5f, 0.0f,-1.0f,		0.332748403138f, 0.2072888803659f,	 0.0f,	-1.0f,	0.0f,//0
				 0.5f, 0.0f,-1.0f,		0.0206327981747f, 0.394558243344f,	 0.0f,	-1.0f,	0.0f,//1
				 0.0f, 0.0f, 0.0f,		0.0194323535402f, 0.0236208512913f,	 0.0f,	-1.0f,	0.0f,//2

				 //abajo
		//			x	y	 z            S		T		NX		NY		NZ
				-0.5f, 1.0f,-0.5f,		0.332748403138f, 0.2072888803659f,	 0.0f,	1.0f,	0.0f,//3
				 0.0f, 1.0f,-1.5f,		0.0206327981747f, 0.394558243344f,	 0.0f,	1.0f,	0.0f,//4
				 0.5f, 1.0f,-0.5f,		0.3423519602138f, 0.5806271616875f,	 0.0f,	1.0f,	0.0f,//5

				 //lados
		//			x	y	 z            S		T		NX		NY		NZ
				 0.0f, 1.0f,-1.5f,		0.332748403138f, 0.2072888803659f,	 0.0f,	0.0f,	-1.0f,//4
				 0.5f, 0.0f,-1.0f,		0.6628706776185f, 0.3933577987095f,	 0.0f,	0.0f,	-1.0f,//1
				-0.5f, 0.0f,-1.0f,		0.3423519602138f, 0.5806271616875f,	 0.0f,	0.0f,	-1.0f,//0
				//			x	y	 z             S		T		NX		NY		NZ
						 0.5f, 1.0f,-0.5f,	0.332748403138f, 0.2072888803659f,	 0.0f,	0.0f,	-1.0f,//5
						 0.5f, 0.0f,-1.0f,	0.6628706776185f, 0.3933577987095f,	 0.0f,	0.0f,	-1.0f,//1
						 0.0f, 0.0f, 0.0f,	0.6628706776185f, 0.0200195173879f,	 0.0f,	0.0f,	-1.0f,//2
						 //			x	y	 z             S		T		NX		NY		NZ
								 -0.5f, 1.0f,-0.5f,	0.664071122253f, 0.7678965246655f,	 0.0f,	0.0f,	-1.0f,//3
								  0.0f, 0.0f, 0.0f,	0.6628706776185f, 0.3933577987095f,	 0.0f,	0.0f,	-1.0f,//2
								 -0.5f, 0.0f,-1.0f,	0.3423519602138f, 0.5806271616875f,	 0.0f,	0.0f,	-1.0f,//0

								 //lados 
						 //			x	y	 z             S		T		NX		NY		NZ
								  0.0f, 1.0f,-1.5f,	0.664071122253f, 0.7678965246655f,	 0.0f,	0.0f,	-1.0f,//4
								  0.5f, 1.0f,-0.5f,	0.3411515155794f, 0.9515645537401f,	 0.0f,	0.0f,	-1.0f,//5
								  0.5f, 0.0f,-1.0f,	0.3423519602138f, 0.5806271616875f,	 0.0f,	0.0f,	-1.0f,//1
								  //			x	y	 z             S		T		NX		NY		NZ
										  -0.5f, 1.0f,-0.5f,	0.664071122253f, 0.7678965246655f,	 0.0f,	0.0f,	-1.0f,//3
										   0.5f, 1.0f,-0.5f,	0.9833893950232f, 0.581827606322f,	 0.0f,	0.0f,	-1.0f,//5 7
										   0.0f, 0.0f, 0.0f,	0.6628706776185f, 0.3933577987095f,	 0.0f,	0.0f,	-1.0f,//2
										   //			x	y	 z             S		T		NX		NY		NZ
												   0.0f, 1.0f,-1.5f,	0.664071122253f, 0.7678965246655f,	 0.0f,	0.0f,	-1.0f,//0
												   -0.5f, 1.0f, -0.5f,	0.9833893950232f, 0.9539654430091f,	 0.0f,	0.0f,	-1.0f,//2
												   -0.5f, 0.0f,-1.0f,	0.9833893950232f, 0.581827606322f,	 0.0f,	0.0f,	-1.0f,//3

	};
	Mesh* octa = new Mesh();
	octa->CreateMesh(octa_vertices, octa_indices, 232, 46);
	meshList.push_back(octa);

}

int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CrearDado();
	CreateShaders();
	CrearOcta();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 1.0f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();

	DadoTexture = Texture("Textures/Dado_abc.tga");
	DadoTexture.LoadTextureA();

	LampTexture = Texture("Textures/LampJpText.tga");
	LampTexture.LoadTextureA();

	AutoTexture = Texture("Textures/OctaTextura.tga");
	AutoTexture.LoadTextureA();

	Kitt_M = Model();
	Kitt_M.LoadModel("Models/audi r8.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/k_rueda.3ds");
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");
	Camino_M = Model();
	Camino_M.LoadModel("Models/lampara_jp.obj");

	Dado_M = Model();
	Dado_M.LoadModel("Models/DadoOBJ.obj");

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);
	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//
	glm::vec3 Lampara = glm::vec3(2.0f, 10.5f, 1.5f);
	//Declaración de primer luz puntual////////////ROJA
	pointLights[0] = PointLight(255.0f / 255, 227.0f / 255, 46.0f / 255,
		0.5f, 1.0f,
		Lampara.x, Lampara.y, Lampara.z,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	//LUZ CARRO
	spotLights[1] = SpotLight(0.0f, 0.6f, 0.0f,
		0.4f, 0.4f,//AMBIENTAL//DIFUSA
		-30.0f, 10.0f, 0.0f,//POSICION
		-1.0f, 0.0f, 0.0f,//DIRECCION
		1.0f, 0.0f, 0.0f,//ECUACION
		15.0f);//ANGULO
	spotLightCount++;

	//LUZ CARRO2
	
	spotLights[2] = SpotLight(0.0f, 0.0f, 1.0f ,
		1.0f, 1.0f,//AMBIENTAL//DIFUSA
		-30.0f, 10.0f, 0.0f,//POSICION
		-1.0f, 0.0f, 0.0f,//DIRECCION
		1.0f, 0.0f, 0.0f,//ECUACION
		25.0f);//ANGULO
	spotLightCount++;
	

	//LUZ HELICOPTER
	spotLights[3] = SpotLight(80.0f / 255, 70.0f / 255, 10.0f / 255,
		1.0f, 2.0f,//AMBIENTAL//DIFUSA
		-30.0f, 10.0f, 0.0f,//POSICION
		-1.0f, 0.0f, 0.0f,//DIRECCION
		1.0f, 0.0f, 0.0f,//ECUACION
		15.0f);//ANGULO
	spotLightCount++;




	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);
		//////////////////
		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		glm::vec3 lowerLight = camera.getCameraPosition();
		glm::vec3 PosicionLuzCarro = glm::vec3(mainWindow.getCmx(), -3.0f, 0.0f);
		glm::vec3 PosicionLuzHeli = glm::vec3(mainWindow.getHmx(), 5.0f, mainWindow.getHmy());



		glm::vec3 Auxluz = glm::vec3(-1.0f, 0.0f, 0.0f);

		glm::vec3 Carluz = glm::vec3(-1.0f, 0.0f, 0.0f);



		(lowerLight.y -= 0.3f);
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());
		spotLights[1].SetFlash(PosicionLuzCarro + glm::vec3(-10.0f, 10.0f, 0.0f), glm::vec3(-1.0f, -1.0f, 0.0f));//adelante
		//spotLights[2].SetFlash(PosicionLuzCarro + glm::vec3(-10.0f, 10.0f, 0.0f), glm::vec3(1.0f, -1.0f, -0.0f));//atras
		spotLights[2].SetFlash(PosicionLuzHeli + glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)); 
		


		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		time_t currentTime;
		struct tm* localTime;
		time(&currentTime); // Get the current time
		localTime = localtime(&currentTime);
		int Sec = localTime->tm_sec;
		//std::cout << "This program was exectued at: " << Sec << std::endl;
		if (Sec % 2 == 0)
			//if (mainWindow.getdestructor() == 0)
		{
			spotLightCount = 4;
		}
		else if (Sec % 3 == 0) {
			spotLightCount = 3;
		}

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();


		//////////////AUTO
		model = glm::mat4(1.0);
		model = glm::translate(model, PosicionLuzCarro);
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Kitt_M.RenderModel();

		//////////HELICOPTERO

		model = glm::mat4(1.0);
		model = glm::translate(model, (PosicionLuzHeli));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Blackhawk_M.RenderModel();
		///
		///
		/// 
		/// 
		model = glm::mat4(1.0);
		model = glm::translate(model, Lampara + glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Camino_M.RenderModel();


		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
