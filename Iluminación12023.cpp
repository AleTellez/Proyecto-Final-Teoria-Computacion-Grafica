/*
Semestre 2023-1
Práctica 7: Iluminación 1 
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

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


Model Kitt_M;
Model Llanta_M;
Model Camino_M;
Model Blackhawk_M;
Model Dado_M;
Model cofre_M;
Model micarro;
Model lampara;
Model faro;

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





void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = { //No tiene valores en la normal, apunta hacia -y
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

	GLfloat floorVertices[] = { //Si los pongo en cero, no sabemos a donde esta la normal, por lo que no se refleja
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	}; 
	//si se pone en 1 refleja pero hacia abajo 

	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);
}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	//mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow = Window(1600, 900); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();

	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/k_rueda.3ds");
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");
	Camino_M = Model();
	Camino_M.LoadModel("Models/railroad track.obj");
	cofre_M = Model();
	cofre_M.LoadModel("Models/cofre.obj");
	micarro = Model();
	micarro.LoadModel("Models/carroceria.obj");
	lampara = Model();
	lampara.LoadModel("Models/lamp.obj");
	faro = Model();
	faro.LoadModel("Models/street_lighr.obj");



	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	//DEclaracion de los materiales
	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.3f,//ambiental y difusa 
		0.0f, 0.0f, -1.0f); //este es un vector de direccion 
	//Es la translación del sol
	//Para que se vea pones la ambentral en 1 
	// Aqui va el ciclo de dia y noche 
	// 
	// 
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual roja
	pointLights[0] = PointLight(1.0f, 1.0f, 0.0f, //rojo es la que esta sobe el cofre del coche 
		20.0f, 20.0f, //el circulo se hace mas grande 
		20.0f, 100.0f, 150.0,
		//0.0f, 2.0f, 0.0f,
		0.1f, 0.1f, 0.1f); //Ecuacion de segundo grado
	//Nunca debe ser cero, estos valores es el alnce que tiene el ciruclo 
	//Mientras mas grande la atenuación el color se ve mas pequeño 
	pointLightCount++;
	pointLights[1] = PointLight(1.0f, 0.0f, 1.0f,
		10.0f, 10.0f, 
		-10.0f, 15.0f, 150.0,
		0.1f, 0.1f, 0.1f); 
	//Nunca debe ser cero, estos valores es el alnce que tiene el ciruclo 
	//Mientras mas grande la atenuación el color se ve mas pequeño 
	pointLightCount++;

	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(0.10f, 0.10f, 0.10f, //aqui cambiamos el color de la linterna 
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f); //Aqui ampliamos el radio
	spotLightCount++;

	//luz fija azul
	/*
	spotLights[3] = SpotLight(0.0f, 0.0f, 1.0f,
		1.0f, 2.0f,
		-100.0f, 10.0f, 150.0,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f); //angulo de 15, entre mas grande se amplia  el cono/circulo de ilumnicación 
	spotLightCount++;
	*/	
	//luz de helicóptero
	//luz de faro

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Debemos identifcar cuando meter las linterna o cuando no 
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
		
		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
			glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f; 
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection()); //Actulizo el tiempo de ejecucion y posicion
		//si la quito se va a quedar estatica en un solo lugar
		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f); //Apartir de aqui es el color blanco 
		glm::vec3 color2 = glm::vec3(0.5f, 0.0f, 0.5f);
		glm::vec3 rojo = glm::vec3(0.8f, 0.0f, 0.0f);
		glm::vec3 verde = glm::vec3(0.0f, 0.8f, 0.0f);
		glm::vec3 azul = glm::vec3(0.0f, 0.0f, 0.8f);
		glm::vec3 amarillo = glm::vec3(0.8f, 0.8f, 0.0f);
		glm::vec3 arenoso = glm::vec3(1.0f, 0.8f, 0.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//Se ve  como un puntito de luz por que como es el unico material es brillante 
		//se puede simular el solo , todo lo que esta a continuación recibe un solo material 
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0));
		model = glm::translate(model, glm::vec3(mainWindow.getizqderheli(), mainWindow.getsubebajaheli(), mainWindow.getavanzaretrocedeheli()));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Blackhawk_M.RenderModel();
		spotLights[1] = SpotLight(0.0f, 0.0f, 1.0f,
			1.0f, 2.0f,
			mainWindow.getizqderheli(), mainWindow.getsubebajaheli(), mainWindow.getavanzaretrocedeheli(),
			0.0f, -1.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			20.0f); //angulo de 15, entre mas grande se amplia  el cono/circulo de ilumnicación 
		spotLightCount++;
		//CARRO PROPIO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(75.0f, -1.53f, -200.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, mainWindow.getmovcarro1()));		
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(arenoso));
		micarro.RenderModel();
		//definir una visagra
		model = modelaux;
		model = glm::translate(model, glm::vec3(-34.0f, 0.0f, 14.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getmuevecofre()), glm::vec3(-1.0f, 0.0f, 0.0f));
		modelaux = model;
		//definir el cofre
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -66.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color2));
		cofre_M.RenderModel();		
		if (mainWindow.getmovc1() == 1.0f)
		{
			spotLights[2] = SpotLight(0.0f, 1.0f, 0.0f,
				1.0f, 2.0f,
				75.0f, 15.0f, mainWindow.getluzdcarro1(),
				0.0f, -1.0f, 1.0f,
				1.0f, 0.0f, 0.0f,
				45.0f); //angulo de 15, entre mas grande se amplia  el cono/circulo de ilumnicación 
			spotLightCount++;
		}
		else if(mainWindow.getmovc1() == 0.0f)
		{
			spotLights[2] = SpotLight(1.0f, 0.0f, 0.0f,
				1.0f, 2.0f,
				75.0f, 15.0f, mainWindow.getluztcarro1(),
				0.0f, -1.0f, -1.0f,
				1.0f, 0.0f, 0.0f,
				45.0f); //angulo de 15, entre mas grande se amplia  el cono/circulo de ilumnicación 
			spotLightCount++;
		}
		//CARRO PROFE
		//carroceria		
		model = glm::mat4(1.0);		
		model = glm::translate(model, glm::vec3(-75.0f, 11.0f, -120.0f));		
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, mainWindow.getmovcarro2()));		
		modelaux = model;		
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Kitt_M.RenderModel();
		//llanta frente izq
		model = modelaux;
		model = glm::translate(model, glm::vec3(12.0f, -4.5f, -57.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(rojo));
		Llanta_M.RenderModel();
		//llanta frente der
		model = modelaux;
		model = glm::translate(model, glm::vec3(63.5f, -4.5f, -57.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(verde));
		Llanta_M.RenderModel();
		//llanta tras izq
		model = modelaux;
		model = glm::translate(model, glm::vec3(12.0f, -4.5f, -126.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(azul));
		Llanta_M.RenderModel();
		//llanta frente der
		model = modelaux;
		model = glm::translate(model, glm::vec3(63.5f, -4.5f, -126.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(amarillo));
		Llanta_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 150.0));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		faro.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 150.0));
		model = glm::scale(model, glm::vec3(50.0f, 50.0f, 50.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		lampara.RenderModel();

		glUseProgram(0);
		mainWindow.swapBuffers();
	}

	return 0;
}
