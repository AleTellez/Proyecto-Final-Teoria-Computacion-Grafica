/*
Semestre 2023-2
Práctica : Iluminación
Cambios en el shader:
en lugar de enviar solo información de color e información de la textura en el shader de fragmentos,
enviaremos también información de iluminación almacenada en finalcolor.
Modelo de Iluminación de Lambert/Sombreado de Phong 3 componentes: Ambiental, Difusa, Especular
Archivos nuevos a utilizar:
CommonValues.h: Contiene banderas de número máximo de fuentes de iluminación puntual y spotlight
DirectionalLight: Luz direccional
PointLight Luces Puntuales
Spotlight Luces Spotlight
Material Información de intensidad especular y brillo, se puede modificar para agregar
componentes de color difuso, en el caso del laboratorio lo manejo por el color de la variable uniform
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION
#pragma warning(disable : 4996)
#include <ctime>
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
Texture carroTexture;
Texture pastoTexture;
Texture cementoTexture;
/*
Texture bamboo1;
Texture bamboo2;
Texture bamboo3;
Texture bamboo4;
Texture bamboo5;
Texture bamboo6;
Texture piedra1_pandaTexture;
Texture piedra2_pandaTexture;
Texture piedra3_pandaTexture;
Texture piedra4_pandaTexture;
Texture piedra5_pandaTexture;
Texture piedra6_pandaTexture;
Texture piedra7_pandaTexture;
Texture piedra8_pandaTexture;
Texture piedra9_pandaTexture;
Texture piedra10_pandaTexture;
Texture dona_pandaTexture;
*/
Texture pandabuenoTexture;
/*
Texture carro_simpson1;
Texture carro_simpson2;
Texture carro_simpson3;
Texture carro_simpson4;
Texture carro_simpson5;
Texture carro_simpson6;
Texture carro_simpson7;
*/
Texture faro1_Texture;

Texture puesto_Texture;

//Texture duffbuenaTexture;
//Texture puente_panda1;
//Texture puente_panda2;
//Texture puente_panda3;



Model faro;
Model habitat_panda;
Model piso_exterior;
/*
Model bamboo;
Model carro_simpson;
Model estanque_panda;
Model piedra1_panda;
Model piedra2_panda;
Model piedra3_panda;
Model piedra4_panda;
Model piedra5_panda;
Model piedra6_panda;
Model piedra7_panda;
Model piedra8_panda;
Model piedra9_panda;
Model piedra10_panda;
Model dona_panda;
*/
Model rejaenfrente_panda;
Model rejalateral_panda;
Model estatua_panda;
Model pandabueno;
Model homerobueno;
//Model duffbuena;
/*
Model arbol_panda;
Model puente_panda;*/
Model homero_s;
Model faro1;

Model puesto;
Model focosPuesto;




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

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);
	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main()
{
	mainWindow = Window(1600, 900); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 1.0f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	carroTexture = Texture("Textures/Lamborginhi_Aventador_diffuse.jpeg");
	carroTexture.LoadTextureA();
	pastoTexture = Texture("Textures/pasto.jpg");
	pastoTexture.LoadTextureA();
	/*
	bamboo1 = Texture("Textures/AS01_Bark01_dif_su.png");
	bamboo1.LoadTextureA();
	bamboo2 = Texture("Textures/AS01_Branch01_dif_su.png");
	bamboo2.LoadTextureA();
	bamboo3 = Texture("Textures/AS01_Leaf01Back_dif_su.png");
	bamboo3.LoadTextureA();
	bamboo4 = Texture("Textures/AS01_Leaf01Front_dif_su.png");
	bamboo4.LoadTextureA();
	bamboo5 = Texture("Textures/AS01_Leaf02Back_dif_su.png");
	bamboo5.LoadTextureA();
	bamboo6 = Texture("Textures/AS01_Leaf02Front_dif_su.png");
	bamboo6.LoadTextureA();
	piedra1_pandaTexture = Texture("Textures/stone_small_c_albedo.png");
	piedra1_pandaTexture.LoadTextureA();
	piedra2_pandaTexture = Texture("Textures/stone_small_c_albedo.png");
	piedra2_pandaTexture.LoadTextureA();
	piedra3_pandaTexture = Texture("Textures/stone_small_b_albedo.png");
	piedra3_pandaTexture.LoadTextureA();
	piedra4_pandaTexture = Texture("Textures/stone_small_a_albedo.png");
	piedra4_pandaTexture.LoadTextureA();
	piedra5_pandaTexture = Texture("Textures/stone_small_c_albedo.png");
	piedra5_pandaTexture.LoadTextureA();
	piedra6_pandaTexture = Texture("Textures/stone_small_c_albedo.png");
	piedra6_pandaTexture.LoadTextureA();
	piedra7_pandaTexture = Texture("Textures/stone_small_a_albedo.png");
	piedra7_pandaTexture.LoadTextureA();
	piedra8_pandaTexture = Texture("Textures/stone_small_b_albedo.png");
	piedra8_pandaTexture.LoadTextureA();
	piedra9_pandaTexture = Texture("Textures/stone_small_c_albedo.png");
	piedra9_pandaTexture.LoadTextureA();
	piedra10_pandaTexture = Texture("Textures/stone_small_c_albedo.png");
	piedra10_pandaTexture.LoadTextureA();
	dona_pandaTexture = Texture("Textures/Tekstur_donat.png");
	dona_pandaTexture.LoadTextureA();
	*/
	pandabuenoTexture = Texture("Textures/bear_Base_Color.png");
	pandabuenoTexture.LoadTextureA();
	/*
	carro_simpson1 = Texture("Textures/cable.png");
	carro_simpson1.LoadTextureA();
	carro_simpson2 = Texture("Textures/vitres.png");
	carro_simpson2.LoadTextureA();
	carro_simpson3 = Texture("Textures/rosa.png");
	carro_simpson3.LoadTextureA();
	carro_simpson4 = Texture("Textures/Metal.png");
	carro_simpson4.LoadTextureA();
	carro_simpson5 = Texture("Textures/phare.png");
	carro_simpson5.LoadTextureA();
	carro_simpson6 = Texture("Textures/vitres.png");
	carro_simpson6.LoadTextureA();
	carro_simpson7 = Texture("Textures/pneus.png");
	carro_simpson7.LoadTextureA();
	*/
	faro1_Texture = Texture("Textures/lampara.jpg");
	faro1_Texture.LoadTextureA();
	
	puesto_Texture = Texture("Textures/city_stall_d.tga");
	puesto_Texture.LoadTextureA();



	//duffbuenaTexture = Texture("Textures/Duff_Label.jpg");
	//duffbuenaTexture.LoadTextureA();
	//puente_panda1 = Texture("Textures/DirtyWoodPlanks.jpg");
	//pastoTexture.LoadTextureA();
	//puente_panda2 = Texture("Textures/DSC_4477.jpg");
	//pastoTexture.LoadTextureA();
	//puente_panda3 = Texture("Textures/DSC_4643.jpg");
	//pastoTexture.LoadTextureA();




	faro = Model();
	faro.LoadModel("Models/street_lighr.obj");
	habitat_panda = Model();
	habitat_panda.LoadModel("Models/habitat_panda.obj");
	piso_exterior = Model();
	piso_exterior.LoadModel("Models/piso_exterior.obj");
	/*
	bamboo = Model();
	bamboo.LoadModel("Models/bamboo.obj");
	carro_simpson = Model();
	carro_simpson.LoadModel("Models/carroS.obj");
	estanque_panda = Model();
	estanque_panda.LoadModel("Models/estanque_panda.obj");
	piedra1_panda = Model();
	piedra1_panda.LoadModel("Models/piedra1_panda.obj");
	piedra2_panda = Model();
	piedra2_panda.LoadModel("Models/piedra2_panda.obj");
	piedra3_panda = Model();
	piedra3_panda.LoadModel("Models/piedra3_panda.obj");
	piedra4_panda = Model();
	piedra4_panda.LoadModel("Models/piedra4_panda.obj");
	piedra5_panda = Model();
	piedra5_panda.LoadModel("Models/piedra5_panda.obj");
	piedra6_panda = Model();
	piedra6_panda.LoadModel("Models/piedra6_panda.obj");
	piedra7_panda = Model();
	piedra7_panda.LoadModel("Models/piedra7_panda.obj");
	piedra8_panda = Model();
	piedra8_panda.LoadModel("Models/piedra8_panda.obj");
	piedra9_panda = Model();
	piedra9_panda.LoadModel("Models/piedra9_panda.obj");
	piedra10_panda = Model();
	piedra10_panda.LoadModel("Models/piedra10_panda.obj");
	dona_panda = Model();
	dona_panda.LoadModel("Models/dona_panda.obj");
	*/
	rejaenfrente_panda = Model();
	rejaenfrente_panda.LoadModel("Models/rejaenfrente_panda.obj");
	rejalateral_panda = Model();
	rejalateral_panda.LoadModel("Models/rejalateral_panda.obj");
	pandabueno = Model();
	pandabueno.LoadModel("Models/panda2bueno.obj");
	/*
	homero_s = Model();
	homero_s.LoadModel("Models/homero_s.obj");*/
	faro1 = Model();
	faro1.LoadModel("Models/faro.obj");
	
	puesto = Model();
	puesto.LoadModel("Models/puesto.obj");
	focosPuesto = Model();
	focosPuesto.LoadModel("Models/focosPuesto.obj");







	//estatua_panda = Model();
	//estatua_panda.LoadModel("Models/pandabueno.obj");

	//estatua_panda = Model();
	//estatua_panda.LoadModel("Models/estatua_panda.obj");

	//duffbuena = Model();
	//duffbuena.LoadModel("Models/duffbuena.obj");
	/*
	arbol_panda = Model();
	arbol_panda.LoadModel("Models/AlanTree.obj");
	puente_panda = Model();
	puente_panda.LoadModel("Models/Bridge.obj");
	*/

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
		0.5f, 0.3f,
		1.0f, 0.0f, -1.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;


	//Luz Faro1
	pointLights[0] = PointLight(0.8f, 0.8f, 0.0f,
		10.0f, 10.0f,
		57.0f, 30.0f, 50.0,
		0.1f, 0.1f, 0.1f);
	//Nunca debe ser cero, estos valores es el alnce que tiene el ciruclo 
	//Mientras mas grande la atenuación el color se ve mas pequeño 
	pointLightCount++;

	//Luz faro2
	pointLights[1] = PointLight(0.8f, 0.8f, 0.0f,
		10.0f, 10.0f,
		57.0f, 30.0f, -60.0,
		0.1f, 0.1f, 0.1f);
	//Nunca debe ser cero, estos valores es el alnce que tiene el ciruclo 
	//Mientras mas grande la atenuación el color se ve mas pequeño 
	pointLightCount++;

	//Luz faro3
	pointLights[2] = PointLight(0.8f, 0.8f, 0.0f,
		10.0f, 10.0f,
		-57.0f, 30.0f, -60.0,
		0.1f, 0.1f, 0.1f);
	//Nunca debe ser cero, estos valores es el alnce que tiene el ciruclo 
	//Mientras mas grande la atenuación el color se ve mas pequeño 
	pointLightCount++;

	//Luz foco1
	pointLights[3] = PointLight(0.0f, 0.0f, 0.0f,
		10.0f, 10.0f,
		-57.0f, 30.0f, -60.0,
		0.1f, 0.1f, 0.1f);
	//Nunca debe ser cero, estos valores es el alnce que tiene el ciruclo 
	//Mientras mas grande la atenuación el color se ve mas pequeño 
	pointLightCount++;

	//Luz foco2
	pointLights[4] = PointLight(0.8f, 0.8f, 0.0f,
		10.0f, 10.0f,
		-57.0f, 30.0f, -60.0,
		0.1f, 0.1f, 0.1f);
	//Nunca debe ser cero, estos valores es el alnce que tiene el ciruclo 
	//Mientras mas grande la atenuación el color se ve mas pequeño 
	pointLightCount++;

	//Luz foco3
	pointLights[5] = PointLight(0.8f, 0.8f, 0.0f,
		10.0f, 10.0f,
		-57.0f, 30.0f, -60.0,
		0.1f, 0.1f, 0.1f);
	//Nunca debe ser cero, estos valores es el alnce que tiene el ciruclo 
	//Mientras mas grande la atenuación el color se ve mas pequeño 
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
	//luz carro azul
	spotLights[1] = SpotLight(0.0f, 0.0f, 1.0f,
		0.1f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		25.0f);
	spotLightCount++;
	//luz carro roja
	spotLights[2] = SpotLight(1.0f, 0.0f, 0.0f,
		0.1f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, -1.0f,
		1.0f, 0.0f, 0.0f,
		25.0f);
	spotLightCount++;
	//luz de helicóptero
	spotLights[3] = SpotLight(0.8f, 0.8f, 0.0f,
		0.1f, 1.0f,
		180.0f, 10.0f, 10.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;


	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0, uniformSpecularIntensity = 0, uniformShininess = 0;
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

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		glm::vec3 lowerLight = camera.getCameraPosition();
		//estos valores de la pòsicion del heli deben estar en windows.cpp y windows.h
		glm::vec3 PosicionLuzHeli = glm::vec3(mainWindow.getizqderheli(), mainWindow.getsubebajaheli(), mainWindow.getavanzaretrocedeheli());
		glm::vec3 PosicionLuzCarro = glm::vec3(0.0f, 0.0f, mainWindow.getmovcarro2());
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());
		spotLights[3].SetFlash(PosicionLuzHeli + glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));

		if (mainWindow.getmovc1() == 1.0)
		{
			spotLights[1].SetPos(PosicionLuzCarro + glm::vec3(-112.0f, 50.0f, -150.0f));
			spotLights[2].SetPos(PosicionLuzCarro + glm::vec3(-112.0f, -50.0f, -250.0f));
		}
		else if (mainWindow.getmovc1() == 0.0)
		{
			spotLights[1].SetPos(PosicionLuzCarro + glm::vec3(-112.0f, -50.0f, -150.0f));
			spotLights[2].SetPos(PosicionLuzCarro + glm::vec3(-112.0f, 50.0f, -250.0f));
		}

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);

		//prender y apagar luz de heli		
		time_t currentTime;
		struct tm* localTime;
		time(&currentTime); // Get the current time
		localTime = localtime(&currentTime);
		int Sec = localTime->tm_sec;
		if (Sec % 2 == 0)

		{
			spotLightCount = 4;
		}
		else if (Sec % 3 == 0) {
			spotLightCount = 3;
		}

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
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


		//Habitat Oso
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pastoTexture.UseTexture();
		habitat_panda.RenderModel();

		//Piso Exterior
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cementoTexture.UseTexture();
		piso_exterior.RenderModel();

		/*
		//Arbol Panda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//cementoTexture.UseTexture();
		arbol_panda.RenderModel();

		//Puente Panda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//puente_panda1.UseTexture();
		//puente_panda2.UseTexture();
		//puente_panda3.UseTexture();
		puente_panda.RenderModel();


		//bamboo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		bamboo1.UseTexture();
		bamboo2.UseTexture();
		bamboo3.UseTexture();
		bamboo4.UseTexture();
		bamboo5.UseTexture();
		bamboo6.UseTexture();
		bamboo.RenderModel();

		//bamboo2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(15.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		bamboo1.UseTexture();
		bamboo2.UseTexture();
		bamboo3.UseTexture();
		bamboo4.UseTexture();
		bamboo5.UseTexture();
		bamboo6.UseTexture();
		bamboo.RenderModel();

		//Carro Simpson
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		carro_simpson1.UseTexture();
		carro_simpson2.UseTexture();
		carro_simpson3.UseTexture();
		carro_simpson4.UseTexture();
		carro_simpson5.UseTexture();
		carro_simpson6.UseTexture();
		carro_simpson7.UseTexture();
		carro_simpson.RenderModel();
		*/

		//Reja enfrente
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		rejaenfrente_panda.RenderModel();

		//Reja trasera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 104.65f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		rejaenfrente_panda.RenderModel();

		//Reja izquierda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		rejalateral_panda.RenderModel();

		//Reja derecha
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-120.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		rejalateral_panda.RenderModel();

		/*
		//estatua
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-120.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//estatua_panda.RenderModel();
		*/
		//panda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pandabuenoTexture.UseTexture();
		pandabueno.RenderModel();



		//Duff
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//duffbuenaTexture.UseTexture();
		//duffbuena.RenderModel();

		/*
		//Piedra 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piedra1_pandaTexture.UseTexture();
		piedra1_panda.RenderModel();

		//Piedra2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piedra2_pandaTexture.UseTexture();
		piedra2_panda.RenderModel();

		//Piedra3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piedra3_pandaTexture.UseTexture();
		piedra3_panda.RenderModel();

		//Piedra4
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piedra4_pandaTexture.UseTexture();
		piedra4_panda.RenderModel();

		//Piedra5
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piedra5_pandaTexture.UseTexture();
		piedra5_panda.RenderModel();

		//Piedra6
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piedra6_pandaTexture.UseTexture();
		piedra6_panda.RenderModel();

		//Piedra7
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piedra7_pandaTexture.UseTexture();
		piedra7_panda.RenderModel();

		//Piedra8
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piedra8_pandaTexture.UseTexture();
		piedra8_panda.RenderModel();

		//Piedra9
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piedra9_pandaTexture.UseTexture();
		piedra9_panda.RenderModel();

		//Piedra10
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piedra10_pandaTexture.UseTexture();
		piedra10_panda.RenderModel();

		//Estanque
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(azul));
		estanque_panda.RenderModel();

		//Dona1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(amarillo));
		dona_pandaTexture.UseTexture();
		dona_panda.RenderModel();	
		
		//Dona2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 5.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(amarillo));
		dona_pandaTexture.UseTexture();
		dona_panda.RenderModel();
		*/
		//faro1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 5.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(amarillo));
		faro1_Texture.UseTexture();
		faro1.RenderModel();

		//faro2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, -105.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(amarillo));
		faro1_Texture.UseTexture();
		faro1.RenderModel();

		//faro3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-110.0f, 0.0f, -105.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(amarillo));
		faro1_Texture.UseTexture();
		faro1.RenderModel();
		
		//puesto
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(amarillo));
		puesto_Texture.UseTexture();
		puesto.RenderModel();

		//focos puesto
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(amarillo));
		//puesto_Texture.UseTexture();
		focosPuesto.RenderModel();







		//CARRO PROPIO





		//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



		glDisable(GL_BLEND);
		glUseProgram(0);
		mainWindow.swapBuffers();
	}

	return 0;
}
