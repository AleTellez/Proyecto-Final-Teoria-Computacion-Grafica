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


float reproduciranimacion, habilitaranimacion,
guardoFrame, reinicioFrame, ciclo, ciclo2, contador = 0;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

//variables para animación
float movCoche;
float movOffset;
float rotllanta;
float rotllantaOffset;
bool avanza;
float movBrazos;

//variables ciclo de dia y noche
float movySun;
float movSun;
float movSunOffset;
float luz;
bool dia;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture carroTexture;
Texture pastoTexture;
Texture cementoTexture;
Texture bamboo1;
Texture bamboo2;
Texture bamboo3;
Texture bamboo4;
Texture bamboo5;
Texture bamboo6;
Texture piedra4_pandaTexture;
Texture piedrasEst_pandaTexture;
Texture dona_pandaTexture;
Texture pandabuenoTexture;
Texture carro_simpson1;
Texture carro_simpson2;
Texture carro_simpson3;
Texture carro_simpson4;
Texture carro_simpson5;
Texture carro_simpson6;
Texture carro_simpson7;
Texture faro1_Texture;
Texture puesto_Texture;
Texture duffbuenaTexture;
Texture aveTexture;
Texture amarillo;
Texture iglu_Texture;
Texture piedrapinguino_Texture;
Texture habitatpinguino_Texture;
Texture habitattigre_Texture;
Texture puesto2_1;
Texture puesto2_2;
Texture puesto2_3;

Texture puesto4_1;
Texture puesto4_2;
Texture puesto4_3;
Texture puesto4_4;
Texture puesto4_5;
Texture puesto4_6;

Texture muro;

//pingu
Texture pingu;


//cerveza
Texture duffbeer1_Texture;
Texture duffbeer2_Texture;

//Texture puente_panda1;
//Texture puente_panda2;
//Texture puente_panda3;

//PANDA PUENTE
Model PC;
Model PP;
Model PB;

Model habitattigre;
Model piedratigre;
Model estanquetigre;
Model arbol_panda;
Model piso_exterior;
Model fuente;
Model piedrasEst_tigre;
Model piedrasEst_panda;

Model faro;
Model habitat_panda;
Model bamboo;
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
Model estatua_panda;
Model pandabueno;
Model duffbuena;
Model puente_panda;
Model homero_s;
Model faro1;
Model focosPuesto;
Model homerobueno;
Model iglu;
Model piedrapinguino;
Model habitatpinguino;
Model muroenfrenteder;



Model rejaenfrente_panda;
Model rejalateral_panda;


Model puerta;
Model puesto;
Model puesto2;
Model puesto4;
Model banca1;
Model banca2;

Model carro_simpson;
Model carro2;
Model carro3;
Model Llanta_M;
Model Llantas_AM;


//PINGUINO
Model brazoIzqpingu;
Model brazoDerpingu;
Model cuerpopingu;
Model piederpingu;
Model pieizqpingu;



//MONO
Model brazosmono;
Model cuerpomono;
Model piernamono;
Model colamono;


//TIGRE
Model TCAB;
Model TCUER;
Model TCOLA;
Model TBD;
Model TBI;
Model TPD;
Model TPI;
Model TIGMIMIDO;



//PANDA
//PANDA
Model Panda_Cabeza2;
Model Panda_Torso2;
Model Panda_Patas2;


//base
Model BaseEstatua;

//AVE
Model CuerpoAve;
Model AlaDerF;
Model AlaDerP;
Model AlaIzqF;
Model AlaIzqP;

//HOMERO
Model HomeroCuerpo;
Model HomeroBraDer;
Model HomeroBraIzq;
Model HomeroPierDer;
Model HomeroPierIzq;

//MARGE
Model piernaDerMarge;
Model piernaIzqMarge;
Model brazoIzqMarge;
Model brazoDerMarge;
Model Marge;

//LISA
Model LisaCuerpo;
Model LisaBraDer;
Model LisaBraIzq;
Model LisaPierDer;
Model LisaPierIzq;

//cerveza
Model duffbeer;
Model duffbeer2;
Model duffbeer3;

//Mauina
Model MaquinaEx;



//estatua
Model EST_DER;
Model EST_IZQ;
Model EST_CUER;
Model EST_BASE;

//variables para animación
//LISA
//Variables para lisa
bool caminaizquierda_LI = true;
bool caminaadelante_LI = false;
bool caminaderecha_LI = false;
bool caminaatras_LI = false;
bool regresa_LI = false;
float caminaizquierdaX_LI = 0.0f;
float caminaizquierdaZ_LI = 0.0f;
float caminadelanteX_LI = 0.0;
float caminadelanteZ_LI = 0.0;
float caminaderechaX_LI = 0.0;
float caminaderechaZ_LI = 0.0;
float caminaatrasX_LI = 0.0;
float caminaatrasZ_LI = 0.0;
float regresaX_LI = 0.0;
float regresaZ_LI = 0.0;
float movLISAOffset = 0.1f;

float anguloLISAOffset = 0.2f;
float angulobraLISAOffset = 0.1f;
float movalaLISAY = 0.0f;
float movalaLISAX = 0.0f;
float movalaLISAOffset = 0.1f;;

bool incrementando_LI = false;
bool incrementando2_LI = false;
bool incrementando3_LI = false;

float anguloLI = 0.0f;
float angulobraDLI = 0.0f;
float angulobraILI = 0.0f;
float angulopieDLI = 0.0f;
float angulocuerpoLI = 0.0f;
float angulopieILI = 0.0f;
float angulopieLISAOffset = 0.07f;


//Variables para Pinguino
bool incrementando = true;
bool incrementando2 = true;
bool incrementando3 = true;
bool caminaizquierda_p = true;
bool caminaadelante_p = false;
bool caminaderecha_p = false;
bool caminaatras_p = false;
bool regresa_p = false;
float caminaizquierdaX_p = 0.0f;
float caminaizquierdaZ_p = 0.0f;
float caminadelanteX_p = 0.0;
float caminadelanteZ_p = 0.0;
float caminaderechaX_p = 0.0;
float caminaderechaZ_p = 0.0;
float caminaatrasX_p = 0.0;
float caminaatrasZ_p = 0.0;
float regresaX_p = 0.0;
float regresaZ_p = 0.0;
float movPinguOffset = 0.02f;

float movAlaPinguY = 0.0f;
float movAlaPinguX = 0.0f;
float movAlaOffset = 0.1f;;


float anguloP = 0.0f;
float angulobraDP = 0.0f;
float angulobraIP = 0.0f;
float angulopieDP = 0.0f;
float angulocuerpopin = 0.0f;
float angulopieIP = 0.0f;
float anguloPinguOffset = 0.1f;
float angulobraPinguOffset = 0.1f;
float angulopiePinguOffset = 0.1f;

//Variables para MARGE
bool caminaizquierda_MA = true;
bool caminaadelante_MA = false;
bool caminaderecha_MA = false;
bool caminaatras_MA = false;
bool regresa_MA = false;
float caminaizquierdaX_MA = 0.0f;
float caminaizquierdaZ_MA = 0.0f;
float caminadelanteX_MA = 0.0;
float caminadelanteZ_MA = 0.0;
float caminaderechaX_MA = 0.0;
float caminaderechaZ_MA = 0.0;
float caminaatrasX_MA = 0.0;
float caminaatrasZ_MA = 0.0;
float regresaX_MA = 0.0;
float regresaZ_MA = 0.0;
float movMargeOffset = 0.3f;

float anguloMargeOffset = 0.15f;
float angulobraMargeOffset = 0.1f;
float movalaMargeY = 0.0f;
float movalaMargeX = 0.0f;
float movalaMOffset = 0.1f;;

bool incrementando_MA = false;
bool incrementando2_MA = false;
bool incrementando3_MA = false;

float anguloMA = 0.0f;
float angulobraDMA = 0.0f;
float angulobraIMA = 0.0f;
float angulopieDMA = 0.0f;
float angulocuerpoMA = 0.0f;
float angulopieIMA = 0.0f;
float angulopieMargeOffset = 0.07f;


//variables para mono
//MONO
bool caminasub_m = true;
bool caminabaj_m = false;
float monoregresa = false;

float caminasubY_m = 0.0f;
float caminabajY_m = 0.0f;
float monoregresaY = 0.0f;
float movMonoOffset = 0.02f;

float anguloBM = 0.0f;
float anguloBMOffset = 0.1f;
float anguloPM = 0.0f;
float anguloPMOffset = 0.1f;

float anguloCOM = 0.0f;
float anguloCOMffset = 0.1f;

bool rotateClockwise = true;
float anguloActual = -10.0f;
float anguloMinimo = -35.0f;
float anguloMaximo = 15.0f;
float anguloRotacion = 1.0f; // Incremento/decremento del ángulo

//----
//ESTATUA
bool EST_AVA = true;
bool EST_RET = false;
float EST_REGRESA = false;

float EST_AVA_Z = 0.0f;
float EST_RET_Z = 0.0f;
float EST_REGRESA_Z = 0.0f;
float movESTOffset = 0.02f;


bool rotateClockwise_EST = true;
float anguloActual_EST = 0.0f;
float anguloMinimo_EST = -55.0f;
float anguloMaximo_EST = 55.0f;
float anguloRotacion_EST = 0.4f; // Incremento/decremento del ángulo


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

void inputKeyframes(bool* keys);


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

bool animacion = false;

//NEW// Keyframes PANDA PUENTE
float posXpanda = 0.0, posYpanda = 0.0, posZpanda = 0.0;
float movPanda_x = 0.0f;
float movPanda_y = 0.0f;
float giroPanda = 0.0f;
float giroPanda2 = 0.0f;
float posxPPD = 0.0f, posyPPD = 0.0f;
float posxPPT = 0.0f, posyPPT = 0.0f;
float angPatas = 0.0f;

//TIGRE
float posYtig = 0.0f;
float posZtig = 0.0f;
float movtig_y = 0.0f;
float movtig_z = 0.0f;
float giroCabTig = 0.0f;
float giroBDTig = 0.0f;
float giroBITig = 0.0f;
float giroPDTig = 0.0f;
float giroPITig = 0.0f;
float giroColTig = 0.0f;
float posxBDTig = 0.0f, posyBDTig = 0.0f;
float posxBITig = 0.0f, posyBITig = 0.0f;
float posxPDTig = 0.0f, posyPDTig = 0.0f;
float posxPITig = 0.0f, posyPITig = 0.0f;
float posxColTig = 0.0f, posyColTig = 0.0f;



#define MAX_FRAMES 40
int i_max_steps = 75;
int i_curr_steps = 39;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames PANDA PUENTE
	float movPanda_x;
	float movPanda_y;
	float movPanda_xInc;
	float movPanda_yInc;
	float giroPanda;
	float giroPandaInc;
	float giroPanda2;
	float giroPanda2Inc;
	float posxPPD;
	float posxPPDInc;
	float posyPPD;
	float posyPPDInc;
	float posxPPT;
	float posxPPTInc;
	float posyPPT;
	float posyPPTInc;
	float angPatas;
	float angPatasInc;

	//TIGRE
	float posYtig = 0.0f;
	float posYtigInc = 0.0f;
	float posZtig = 0.0f;
	float posZtigInc = 0.0f;
	float movtig_y = 0.0f;
	float movtig_yInc = 0.0f;
	float movtig_z = 0.0f;
	float movtig_zInc = 0.0f;
	float giroCabTig = 0.0f;
	float giroCabTigInc = 0.0f;
	float giroBDTig = 0.0f;
	float giroBDTigInc = 0.0f;
	float giroBITig = 0.0f;
	float giroBITigInc = 0.0f;
	float giroPDTig = 0.0f;
	float giroPDTigInc = 0.0f;
	float giroPITig = 0.0f;
	float giroPITigInc = 0.0f;
	float giroColTig = 0.0f;
	float giroColTigInc = 0.0f;

	float posxBDTig = 0.0f;
	float posxBDTigInc = 0.0f;
	float posyBDTig = 0.0f;
	float posyBDTigInc = 0.0f;
	float posxBITig = 0.0f;
	float posxBITigInc = 0.0f;
	float posyBITig = 0.0f;
	float posyBITigInc = 0.0f;
	float posxPDTig = 0.0f;
	float posxPDTigInc = 0.0f;
	float posyPDTig = 0.0f;
	float posyPDTigInc = 0.0f;
	float posxPITig = 0.0f;
	float posxPITigInc = 0.0f;
	float posyPITig = 0.0f;
	float posyPITigInc = 0.0f;
	float posxColTig = 0.0f;
	float posxColTigInc = 0.0f;
	float posyColTig = 0.0f;
	float posyColTigInc = 0.0f;

}FRAME;



FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 40;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);

	//PUENTE
	KeyFrame[FrameIndex].movPanda_x = movPanda_x;
	KeyFrame[FrameIndex].movPanda_y = movPanda_y;
	KeyFrame[FrameIndex].giroPanda = giroPanda;
	KeyFrame[FrameIndex].giroPanda2 = giroPanda2;
	KeyFrame[FrameIndex].posxPPD = posxPPD;
	KeyFrame[FrameIndex].posyPPD = posyPPD;
	KeyFrame[FrameIndex].posxPPT = posxPPT;
	KeyFrame[FrameIndex].posyPPT = posyPPT;
	KeyFrame[FrameIndex].angPatas = angPatas;

	//TIGRE
	KeyFrame[FrameIndex].posYtig = posYtig;
	KeyFrame[FrameIndex].posZtig = posZtig;
	KeyFrame[FrameIndex].movtig_y = movtig_y;
	KeyFrame[FrameIndex].movtig_z = movtig_z;
	KeyFrame[FrameIndex].giroCabTig = giroCabTig;
	KeyFrame[FrameIndex].giroBDTig = giroBDTig;
	KeyFrame[FrameIndex].giroBITig = giroBITig;
	KeyFrame[FrameIndex].giroPDTig = giroPDTig;
	KeyFrame[FrameIndex].giroPITig = giroPITig;
	KeyFrame[FrameIndex].giroColTig = giroColTig;
	KeyFrame[FrameIndex].posxBDTig = posxBDTig;
	KeyFrame[FrameIndex].posyBDTig = posyBDTig;
	KeyFrame[FrameIndex].posxBITig = posxBITig;
	KeyFrame[FrameIndex].posyBITig = posyBITig;
	KeyFrame[FrameIndex].posxPDTig = posxPDTig;
	KeyFrame[FrameIndex].posyPDTig = posyPDTig;
	KeyFrame[FrameIndex].posxPITig = posxPITig;
	KeyFrame[FrameIndex].posyPITig = posyPITig;
	KeyFrame[FrameIndex].posxColTig = posxColTig;
	KeyFrame[FrameIndex].posyColTig = posyColTig;

	
	FrameIndex++;
}

void resetElements(void)
{
	//PUENTE PANDA
	movPanda_x = KeyFrame[0].movPanda_x;
	movPanda_y = KeyFrame[0].movPanda_y;
	giroPanda = KeyFrame[0].giroPanda;
	giroPanda2 = KeyFrame[0].giroPanda2;
	posxPPD = KeyFrame[0].posxPPD;
	posyPPD = KeyFrame[0].posyPPD;
	posxPPT = KeyFrame[0].posxPPT;
	posyPPT = KeyFrame[0].posyPPT;
	angPatas = KeyFrame[0].angPatas;

	//TIGRE
	posYtig = KeyFrame[0].posYtig;
	posZtig = KeyFrame[0].posZtig;
	movtig_y = KeyFrame[0].movtig_y;
	movtig_z = KeyFrame[0].movtig_z;
	giroCabTig = KeyFrame[0].giroCabTig;
	giroBDTig = KeyFrame[0].giroBDTig;
	giroBITig = KeyFrame[0].giroBITig;
	giroPDTig = KeyFrame[0].giroPDTig;
	giroPITig = KeyFrame[0].giroPITig;
	giroColTig = KeyFrame[0].giroColTig;
	posxBDTig = KeyFrame[0].posxBDTig;
	posyBDTig = KeyFrame[0].posyBDTig;
	posxBITig = KeyFrame[0].posxBITig;
	posyBITig = KeyFrame[0].posyBITig;
	posxPDTig = KeyFrame[0].posxPDTig;
	posyPDTig = KeyFrame[0].posyPDTig;
	posxPITig = KeyFrame[0].posxPITig;
	posyPITig = KeyFrame[0].posyPITig;
	posxColTig = KeyFrame[0].posxColTig;
	posyColTig = KeyFrame[0].posyColTig;


}

void interpolation(void)
{
	//panda
	KeyFrame[playIndex].movPanda_xInc = (KeyFrame[playIndex + 1].movPanda_x - KeyFrame[playIndex].movPanda_x) / i_max_steps;
	KeyFrame[playIndex].movPanda_yInc = (KeyFrame[playIndex + 1].movPanda_y - KeyFrame[playIndex].movPanda_y) / i_max_steps;
	KeyFrame[playIndex].giroPandaInc = (KeyFrame[playIndex + 1].giroPanda - KeyFrame[playIndex].giroPanda) / i_max_steps;
	KeyFrame[playIndex].giroPanda2Inc = (KeyFrame[playIndex + 1].giroPanda2 - KeyFrame[playIndex].giroPanda2) / i_max_steps;
	KeyFrame[playIndex].posxPPDInc = (KeyFrame[playIndex + 1].posxPPD - KeyFrame[playIndex].posxPPD) / i_max_steps;
	KeyFrame[playIndex].posyPPDInc = (KeyFrame[playIndex + 1].posyPPD - KeyFrame[playIndex].posyPPD) / i_max_steps;
	KeyFrame[playIndex].posxPPTInc = (KeyFrame[playIndex + 1].posxPPT - KeyFrame[playIndex].posxPPT) / i_max_steps;
	KeyFrame[playIndex].posyPPTInc = (KeyFrame[playIndex + 1].posyPPT - KeyFrame[playIndex].posyPPT) / i_max_steps;
	KeyFrame[playIndex].angPatasInc = (KeyFrame[playIndex + 1].angPatas - KeyFrame[playIndex].angPatas) / i_max_steps;

	//tigre
	KeyFrame[playIndex].posYtigInc = (KeyFrame[playIndex + 1].posYtig - KeyFrame[playIndex].posYtig) / i_max_steps;
	KeyFrame[playIndex].posZtigInc = (KeyFrame[playIndex + 1].posZtig - KeyFrame[playIndex].posZtig) / i_max_steps;
	KeyFrame[playIndex].movtig_yInc = (KeyFrame[playIndex + 1].movtig_y - KeyFrame[playIndex].movtig_y) / i_max_steps;
	KeyFrame[playIndex].movtig_zInc = (KeyFrame[playIndex + 1].movtig_z - KeyFrame[playIndex].movtig_z) / i_max_steps;
	KeyFrame[playIndex].giroCabTigInc = (KeyFrame[playIndex + 1].giroCabTig - KeyFrame[playIndex].giroCabTig) / i_max_steps;
	KeyFrame[playIndex].giroBDTigInc = (KeyFrame[playIndex + 1].giroBDTig - KeyFrame[playIndex].giroBDTig) / i_max_steps;
	KeyFrame[playIndex].giroBITigInc = (KeyFrame[playIndex + 1].giroBITig - KeyFrame[playIndex].giroBITig) / i_max_steps;
	KeyFrame[playIndex].giroPITigInc = (KeyFrame[playIndex + 1].giroPITig - KeyFrame[playIndex].giroPITig) / i_max_steps;
	KeyFrame[playIndex].giroColTigInc = (KeyFrame[playIndex + 1].giroColTig - KeyFrame[playIndex].giroColTig) / i_max_steps;
	KeyFrame[playIndex].posxBDTigInc = (KeyFrame[playIndex + 1].posxBDTig - KeyFrame[playIndex].posxBDTig) / i_max_steps;
	KeyFrame[playIndex].posyBDTigInc = (KeyFrame[playIndex + 1].posyBDTig - KeyFrame[playIndex].posyBDTig) / i_max_steps;
	KeyFrame[playIndex].posxBITigInc = (KeyFrame[playIndex + 1].posxBITig - KeyFrame[playIndex].posxBITig) / i_max_steps;
	KeyFrame[playIndex].posyBITigInc = (KeyFrame[playIndex + 1].posyBITig - KeyFrame[playIndex].posyBITig) / i_max_steps;
	KeyFrame[playIndex].posxPDTigInc = (KeyFrame[playIndex + 1].posxPDTig - KeyFrame[playIndex].posxPDTig) / i_max_steps;
	KeyFrame[playIndex].posyPDTigInc = (KeyFrame[playIndex + 1].posyPDTig - KeyFrame[playIndex].posyPDTig) / i_max_steps;
	KeyFrame[playIndex].posxPITigInc = (KeyFrame[playIndex + 1].posxPITig - KeyFrame[playIndex].posxPITig) / i_max_steps;
	KeyFrame[playIndex].posyPITigInc = (KeyFrame[playIndex + 1].posyPITig - KeyFrame[playIndex].posyPITig) / i_max_steps;
	KeyFrame[playIndex].posxColTigInc = (KeyFrame[playIndex + 1].posxColTig - KeyFrame[playIndex].posxColTig) / i_max_steps;
	KeyFrame[playIndex].posyColTigInc = (KeyFrame[playIndex + 1].posyColTig - KeyFrame[playIndex].posyColTig) / i_max_steps;


}


void animate(void)
{	//Movimiento del objeto
	if (play) {
		if (i_curr_steps >= i_max_steps) {//end of animation between frames?		
			playIndex++;
			printf("playindex : %d\n", playIndex);
			if (playIndex > FrameIndex - 2) {//end of total animation?
				printf("Frame index= %d\n", FrameIndex);
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else {//Next frame interpolations
				i_curr_steps = 0; //Reset counter
				interpolation();
			}
		}
		else {
			//PUENTE
			movPanda_x += KeyFrame[playIndex].movPanda_xInc;
			movPanda_y += KeyFrame[playIndex].movPanda_yInc;
			giroPanda += KeyFrame[playIndex].giroPandaInc;
			giroPanda2 += KeyFrame[playIndex].giroPanda2Inc;
			posxPPD += KeyFrame[playIndex].posxPPDInc;
			posyPPD += KeyFrame[playIndex].posyPPDInc;
			posxPPT += KeyFrame[playIndex].posxPPTInc;
			posyPPT += KeyFrame[playIndex].posyPPTInc;
			angPatas += KeyFrame[playIndex].angPatasInc;

			//TIGRE
			posYtig += KeyFrame[playIndex].posYtigInc;
			posZtig += KeyFrame[playIndex].posZtigInc;
			movtig_y += KeyFrame[playIndex].movtig_yInc;
			movtig_z += KeyFrame[playIndex].movtig_zInc;
			giroCabTig += KeyFrame[playIndex].giroCabTig;
			giroBDTig += KeyFrame[playIndex].giroBDTig;
			giroBITig += KeyFrame[playIndex].giroBITig;
			giroPDTig += KeyFrame[playIndex].giroPDTig;
			giroPITig += KeyFrame[playIndex].giroPITig;
			giroColTig += KeyFrame[playIndex].giroColTig;
			posxBDTig += KeyFrame[playIndex].posxBDTig;
			posyBDTig += KeyFrame[playIndex].posyBDTig;
			posxBITig += KeyFrame[playIndex].posxBITig;
			posyBITig += KeyFrame[playIndex].posyBITig;
			posxPDTig += KeyFrame[playIndex].posxPDTig;
			posyPDTig += KeyFrame[playIndex].posyPDTig;
			posxPITig += KeyFrame[playIndex].posxPITig;
			posyPITig += KeyFrame[playIndex].posyPITig;
			posxColTig += KeyFrame[playIndex].posxColTig;
			posyColTig += KeyFrame[playIndex].posyColTig;

			i_curr_steps++;
		}
	}
}

/* FIN KEYFRAMES*/


int main()
{
	mainWindow = Window(1600, 900); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	//blending: transparencia o traslucidez
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	CreateShaders();

	//ciclo dia y noche
	movySun = -1.0f;
	movSun = -1.0f;
	movSunOffset = 0.0002f;
	luz = 1.0f;
	dia = true;

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
	piedra4_pandaTexture = Texture("Textures/stone_small_a_albedo.png");
	piedra4_pandaTexture.LoadTextureA();
	piedrasEst_pandaTexture = Texture("Textures/stone_small_c_albedo.png");
	piedrasEst_pandaTexture.LoadTextureA();
	dona_pandaTexture = Texture("Textures/Tekstur_donat.png");
	dona_pandaTexture.LoadTextureA();
	pandabuenoTexture = Texture("Textures/bear_Base_Color.png");
	pandabuenoTexture.LoadTextureA();
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
	faro1_Texture = Texture("Textures/lampara.jpg");
	faro1_Texture.LoadTextureA();
	puesto_Texture = Texture("Textures/city_stall_d.tga");
	puesto_Texture.LoadTextureA();
	aveTexture = Texture("Textures/DOVE.jpg");
	aveTexture.LoadTextureA();
	duffbeer1_Texture = Texture("Textures/Duff_Beer_2120x1080.jpg");
	duffbeer1_Texture.LoadTextureA();
	duffbeer2_Texture = Texture("Textures/Material.001_Diffuse_Color.png");
	duffbeer2_Texture.LoadTextureA();
	amarillo = Texture("Textures/amarillo.png");
	amarillo.LoadTextureA();
	iglu_Texture = Texture("Textures/m_igloo_Roughness.png");
	iglu_Texture.LoadTextureA();
	piedrapinguino_Texture = Texture("Textures/coral_fort_wall_01_disp_4k.png");
	piedrapinguino_Texture.LoadTextureA();
	habitatpinguino_Texture = Texture("Textures/coral_fort_wall_01_disp_4k.png");
	habitatpinguino_Texture.LoadTextureA();
	habitattigre_Texture = Texture("Textures/pasto2.jpg");
	habitattigre_Texture.LoadTextureA();

	pingu = Texture("Textures/Penguin Diffuse Color.png");
	pingu.LoadTextureA();

	puesto2_1 = Texture("Textures/T_Yatai-Props_D.jpg");
	puesto2_1.LoadTextureA();
	puesto2_2 = Texture("Textures/T_Yatai-bench_D.jpeg");
	puesto2_2.LoadTextureA();
	puesto2_3 = Texture("Textures/T_Yatai4096_D.jpeg");
	puesto2_3.LoadTextureA();
	puesto4_1 = Texture("Textures/grinding_Base_color.png");
	puesto4_1.LoadTextureA();
	puesto4_2 = Texture("Textures/coffee-props_Base_Color.png");
	puesto4_2.LoadTextureA();
	puesto4_3 = Texture("Textures/coffee-machine_Base_color.png");
	puesto4_3.LoadTextureA();
	puesto4_4 = Texture("Textures/vehicle_Base_Color.png");
	puesto4_4.LoadTextureA();
	puesto4_5 = Texture("Textures/chair_Base_Color.png");
	puesto4_5.LoadTextureA();
	puesto4_6 = Texture("Textures/coffee-stand_Base_color.png");
	puesto4_6.LoadTextureA();

	Texture puesto4_1;
	Texture puesto4_2;
	Texture puesto4_3;
	Texture puesto4_4;
	Texture puesto4_5;
	Texture puesto4_6;
	

	muro = Texture("Textures/wall2.jpeg");
	muro.LoadTextureA();
	

	//duffbuenaTexture = Texture("Textures/Duff_Label.jpg");
	//duffbuenaTexture.LoadTextureA();
	//puente_panda1 = Texture("Textures/DirtyWoodPlanks.jpg");
	//pastoTexture.LoadTextureA();
	//puente_panda2 = Texture("Textures/DSC_4477.jpg");
	//pastoTexture.LoadTextureA();
	//puente_panda3 = Texture("Textures/DSC_4643.jpg");
	//pastoTexture.LoadTextureA();
	
	
	rejaenfrente_panda = Model();
	rejaenfrente_panda.LoadModel("Models/rejaenfrente_panda.obj");
	rejalateral_panda = Model();
	rejalateral_panda.LoadModel("Models/rejalateral_panda.obj");

	habitattigre = Model();
	habitattigre.LoadModel("Models/habitattigre.obj");
	piedratigre = Model();
	piedratigre.LoadModel("Models/piedratigre.obj");
	estanquetigre = Model();
	estanquetigre.LoadModel("Models/estanquetigre.obj");

	piedrasEst_panda = Model();
	piedrasEst_panda.LoadModel("Models/piedrasEst.obj");
	piedrasEst_tigre = Model();
	piedrasEst_tigre.LoadModel("Models/piedrasEst.obj");

	//TIGRE
	TCAB = Model();
	TCAB.LoadModel("Models/TCAB.obj");
	TCUER = Model();
	TCUER.LoadModel("Models/TCUER1.obj");
	TCOLA = Model();
	TCOLA.LoadModel("Models/TCOLA.obj");
	TBD = Model();
	TBD.LoadModel("Models/TBD1.obj");
	TBI = Model();
	TBI.LoadModel("Models/TBI1.obj");
	TPD = Model();
	TPD.LoadModel("Models/TPD1.obj");
	TPI = Model();
	TPI.LoadModel("Models/TPI1.obj");

	TIGMIMIDO = Model();
	TIGMIMIDO.LoadModel("Models/TIGREMIMIDO1.obj");

	
	//MONO
	brazosmono = Model();
	brazosmono.LoadModel("Models/MOMAN.obj");
	cuerpomono = Model();
	cuerpomono.LoadModel("Models/MOCUER.obj");
	piernamono = Model();
	piernamono.LoadModel("Models/MOPAT.obj");
	colamono = Model();
	colamono.LoadModel("Models/MOCOL.obj");

	//muro y puerta
	muroenfrenteder = Model();
	muroenfrenteder.LoadModel("Models/muroenfrenteder.obj");
	
	
	
	puerta = Model();
	puerta.LoadModel("Models/puerta.obj");
	piso_exterior = Model();
	piso_exterior.LoadModel("Models/piso.obj");
	fuente = Model();
	fuente.LoadModel("Models/fuentecorrecta.obj");
	banca1 = Model();
	banca1.LoadModel("Models/banca1.obj");
	banca2 = Model();
	banca2.LoadModel("Models/banca2.obj");

	carro_simpson = Model();
	carro_simpson.LoadModel("Models/carroS.obj");

	
	faro = Model();
	faro.LoadModel("Models/street_lighr.obj");
	habitat_panda = Model();
	habitat_panda.LoadModel("Models/habitat_panda.obj");
	bamboo = Model();
	bamboo.LoadModel("Models/bamboo1.obj");
	estanque_panda = Model();
	estanque_panda.LoadModel("Models/estanque_panda.obj");
	piedra4_panda = Model();
	piedra4_panda.LoadModel("Models/piedra4_panda.obj");
	dona_panda = Model();
	dona_panda.LoadModel("Models/dona_panda2.obj");
	pandabueno = Model();
	pandabueno.LoadModel("Models/panda2bueno.obj");
	homero_s = Model();
	homero_s.LoadModel("Models/Homer.obj");
	faro1 = Model();
	faro1.LoadModel("Models/faro.obj");
	focosPuesto = Model();
	focosPuesto.LoadModel("Models/focosPuesto.obj");
	iglu = Model();
	iglu.LoadModel("Models/iglu.obj");
	piedrapinguino = Model();
	piedrapinguino.LoadModel("Models/piedraspinguino.obj");
	habitatpinguino = Model();
	habitatpinguino.LoadModel("Models/habitatpinguino.obj");
	
	
	//PANDA PUENTE
	PC = Model();
	PC.LoadModel("Models/pandacuerpo.obj");
	PB = Model();
	PB.LoadModel("Models/pandapatasD.obj");
	PP = Model();
	PP.LoadModel("Models/pandapatasT.obj");

	//HOMERO
	HomeroCuerpo = Model();
	HomeroCuerpo.LoadModel("Models/HOMEROCUERPO.obj");
	HomeroBraDer = Model();
	HomeroBraDer.LoadModel("Models/HOMEROBRAZODERECHO1.obj");
	HomeroBraIzq = Model();
	HomeroBraIzq.LoadModel("Models/HOMEROBRAZOIZQUIERDO.obj");
	HomeroPierDer = Model();
	HomeroPierDer.LoadModel("Models/HOMEROPIERNADERECHA.obj");
	HomeroPierIzq = Model();
	HomeroPierIzq.LoadModel("Models/HOMEROPIERNAIZQUIERDA1.obj");


	//MARGE
	piernaIzqMarge = Model();
	piernaIzqMarge.LoadModel("Models/MARGEPIERDERN1.obj");
	piernaDerMarge = Model();
	piernaDerMarge.LoadModel("Models/MARGEPIERIZQN1.obj");
	brazoIzqMarge = Model();
	brazoIzqMarge.LoadModel("Models/MARGEBRAIZQN2.obj");
	brazoDerMarge = Model();
	brazoDerMarge.LoadModel("Models/MARGEBRADERN1.obj");
	Marge = Model();
	Marge.LoadModel("Models/MARGECUERPON.obj");

	//LISA
	LisaCuerpo = Model();
	LisaCuerpo.LoadModel("Models/LISACUERPO1N.obj");
	LisaBraDer = Model();
	LisaBraDer.LoadModel("Models/LISABRADERN.obj");
	LisaBraIzq = Model();
	LisaBraIzq.LoadModel("Models/LISABRAIZQN.obj");
	LisaPierDer = Model();
	LisaPierDer.LoadModel("Models/LISAPIERDERN.obj");
	LisaPierIzq = Model();
	LisaPierIzq.LoadModel("Models/LISAPIERIZQN.obj");


	//CERVEZA
	duffbeer = Model();
	duffbeer.LoadModel("Models/duffbeer1.obj");
	duffbeer2 = Model();
	duffbeer2.LoadModel("Models/duffbeer2.obj");
	duffbeer3 = Model();
	duffbeer3.LoadModel("Models/duffmaqui.obj");

	

	//MAQUINA
	MaquinaEx = Model();
	MaquinaEx.LoadModel("Models/maquinaexp2.obj");

	

	////////AVE
	CuerpoAve = Model();
	CuerpoAve.LoadModel("Models/cuerpoAve.obj");
	AlaDerF = Model();
	AlaDerF.LoadModel("Models/AlaDerFIN.obj");
	AlaDerP = Model();
	AlaDerP.LoadModel("Models/AlaDerPri.obj");
	AlaIzqF = Model();
	AlaIzqF.LoadModel("Models/AlaIzqFIN.obj");
	AlaIzqP = Model();
	AlaIzqP.LoadModel("Models/AlaIzqPri.obj");

	



	puente_panda = Model();
	puente_panda.LoadModel("Models/Bridge.obj");
	
	puesto = Model();
	puesto.LoadModel("Models/puesto.obj");

	//PANDA
	Panda_Cabeza2 = Model();
	Panda_Cabeza2.LoadModel("Models/P_CAB.obj");
	Panda_Torso2.LoadModel("Models/P_TOR.obj");
	Panda_Patas2 = Model();
	Panda_Patas2.LoadModel("Models/P_PAN.obj");

	//PINGUINO
	brazoIzqpingu = Model();
	brazoIzqpingu.LoadModel("Models/PiBI1.obj");
	brazoDerpingu = Model();
	brazoDerpingu.LoadModel("Models/PiBD1.obj");
	cuerpopingu = Model();
	cuerpopingu.LoadModel("Models/cuerpopingu.obj");
	piederpingu = Model();
	piederpingu.LoadModel("Models/PPD.obj");
	pieizqpingu = Model();
	pieizqpingu.LoadModel("Models/PPI.obj");

	carro2 = Model();
	carro2.LoadModel("Models/10609_toy_race_car_SG_v1_Iterations-2.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_1.obj");
	Llantas_AM = Model();
	Llantas_AM.LoadModel("Models/llanta_22a.obj");
	carro3 = Model();
	carro3.LoadModel("Models/carroAle.obj");
	
	puesto2 = Model();
	puesto2.LoadModel("Models/puesto2.obj");
	puesto4 = Model();
	puesto4.LoadModel("Models/puesto4.obj");
	arbol_panda = Model();
	arbol_panda.LoadModel("Models/AlanTree.obj");
	
	//ESTATUA
	EST_DER = Model();
	EST_DER.LoadModel("Models/ESTATDER1.obj");
	EST_IZQ = Model();
	EST_IZQ.LoadModel("Models/ESTATIZQ1.obj");
	EST_CUER = Model();
	EST_CUER.LoadModel("Models/ESTATCUERPO1.obj");
	EST_BASE = Model();
	EST_BASE.LoadModel("Models/ESTATBASE.obj");
	


	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/fondort.tga");
	skyboxFaces.push_back("Textures/Skybox/fondolf.tga");
	skyboxFaces.push_back("Textures/Skybox/fondodn.tga");
	skyboxFaces.push_back("Textures/Skybox/fondoup.tga");
	skyboxFaces.push_back("Textures/Skybox/fondobk.tga");
	skyboxFaces.push_back("Textures/Skybox/fondoft.tga");

	std::vector<std::string> skyboxFaces2;
	skyboxFaces2.push_back("Textures/Skybox/fondort_n.tga");
	skyboxFaces2.push_back("Textures/Skybox/fondolf_n.tga");
	skyboxFaces2.push_back("Textures/Skybox/fondodn_n.tga");
	skyboxFaces2.push_back("Textures/Skybox/fondoup_n.tga");
	skyboxFaces2.push_back("Textures/Skybox/fondobk_n.tga");
	skyboxFaces2.push_back("Textures/Skybox/fondoft_n.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.3f,
		1.0f, 0.0f, -1.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	unsigned int spotLightCount = 0;


	//Luz foco1
	pointLights[0] = PointLight(0.8f, 0.8f, 0.0f,
		0.1f, 0.1f,
		57.0f, 30.0f, 50.0,
		//-18.0f, 15.0f, -75.0,
		0.003f, 0.003f, 0.003f);
	//Nunca debe ser cero, estos valores es el alnce que tiene el ciruclo 
	//Mientras mas grande la atenuación el color se ve mas pequeño 
	pointLightCount++;

	//Luz foco2
	pointLights[1] = PointLight(0.8f, 0.8f, 0.0f,
		0.1f, 0.1f,
		57.0f, 30.0f, -60.0,
		//-25.0f, 15.0f, -75.0,
		0.003f, 0.003f, 0.003f);
	//Nunca debe ser cero, estos valores es el alnce que tiene el ciruclo 
	//Mientras mas grande la atenuación el color se ve mas pequeño 
	pointLightCount++;

	//Luz foco3
	pointLights[2] = PointLight(0.8f, 0.8f, 0.0f,
		0.1f, 0.1f,
		-57.0f, 30.0f, -60.0,
		//-32.0f, 15.0f, -75.0,
		0.003f, 0.003f, 0.003f);
	//Nunca debe ser cero, estos valores es el alnce que tiene el ciruclo 
	//Mientras mas grande la atenuación el color se ve mas pequeño 
	pointLightCount++;

	//Luz foco tigre 1
	pointLights[3] = PointLight(0.8f, 0.8f, 0.0f,
		0.1f, 0.1f,
		57.0f, 30.0f, 247.0,
		//-32.0f, 15.0f, -75.0,
		0.003f, 0.003f, 0.003f);
	//Nunca debe ser cero, estos valores es el alnce que tiene el ciruclo 
	//Mientras mas grande la atenuación el color se ve mas pequeño 
	pointLightCount++;


	//Luz foco tigre 2
	pointLights[4] = PointLight(0.8f, 0.8f, 0.0f,
		0.1f, 0.1f,
		-57.0f, 30.0f, 247.0,
		//-32.0f, 15.0f, -75.0,
		0.003f, 0.003f, 0.003f);
	//Nunca debe ser cero, estos valores es el alnce que tiene el ciruclo 
	//Mientras mas grande la atenuación el color se ve mas pequeño 
	pointLightCount++;


	//Luz foco pinguino 1
	pointLights[5] = PointLight(0.8f, 0.8f, 0.0f,
		0.1f, 0.1f,
		-57.0f, 30.0f, -245.0,
		//-32.0f, 15.0f, -75.0,
		0.003f, 0.003f, 0.003f);
	//Nunca debe ser cero, estos valores es el alnce que tiene el ciruclo 
	//Mientras mas grande la atenuación el color se ve mas pequeño 
	pointLightCount++;

	//Luz foco pinguino 2
	pointLights[6] = PointLight(0.8f, 0.8f, 0.0f,
		0.1f, 0.1f,
		57.0f, 30.0f, -240.0,
		//-32.0f, 15.0f, -75.0,
		0.003f, 0.003f, 0.003f);
	//Nunca debe ser cero, estos valores es el alnce que tiene el ciruclo 
	//Mientras mas grande la atenuación el color se ve mas pequeño 
	pointLightCount++;
		
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	spotLights[1] = SpotLight(1.0f, 0.0f, 0.0f,
		0.0f, 2.0f,
		143.0f, 45.0f, -143.0,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	spotLights[2] = SpotLight(1.0f, 0.0f, 0.0f,
		0.0f, 2.0f,
		136.0f, 50.0f, -143.0,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	spotLights[3] = SpotLight(1.0f, 0.0f, 0.0f,
		0.0f, 2.0f,
		129.0f, 50.0f, -143.0,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	pointLightCount = 0;
	spotLightCount = 0;

	//GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0, uniformSpecularIntensity = 0, uniformShininess = 0;
	//GLuint uniformColor = 0;
	//glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);


	movCoche = 0.0f;
	movOffset = 0.1f;
	rotllanta = 0.0f;
	rotllantaOffset = 1.0f;
	avanza = true;

	glm::vec3 pospanda = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 postigre = glm::vec3(0.0f, 0.0f, 0.0f);

	//KEYFRAMES DECLARADOS INICIALES PANDA PUENTE
//PUENTE
	KeyFrame[0].movPanda_x = -3.0f;
	KeyFrame[0].movPanda_y = -0.5f;
	KeyFrame[0].giroPanda = 35.0f;
	KeyFrame[0].giroPanda2 = 5.0f;
	KeyFrame[0].posxPPD = 0.15f;
	KeyFrame[0].posyPPD = -0.1f;
	KeyFrame[0].posxPPT = -0.1;
	KeyFrame[0].posyPPT = -0.02f;
	KeyFrame[0].angPatas = 0;

	//TIGRE
	KeyFrame[0].posZtig = 1.10f;
	KeyFrame[0].posYtig = 0.0f;
	KeyFrame[0].movtig_z = 0.10f;
	KeyFrame[0].movtig_y = 0.2f;
	KeyFrame[0].giroCabTig = 0.0f;
	KeyFrame[0].giroBDTig = 0.070f;
	KeyFrame[0].giroBITig = 10.0f;
	KeyFrame[0].giroPDTig = 0.0f;
	KeyFrame[0].giroPITig = 0.0f;
	KeyFrame[0].giroColTig = 0.0f;

	KeyFrame[0].posxBDTig = 0.0f;
	KeyFrame[0].posyBDTig = 0.0f;
	KeyFrame[0].posxBITig = 0.0f;
	KeyFrame[0].posyBITig = 0.0f;
	KeyFrame[0].posxPDTig = 0.0f;
	KeyFrame[0].posyPDTig = 0.0f;
	KeyFrame[0].posxPITig = 0.0f;
	KeyFrame[0].posyPITig = 0.0f;
	KeyFrame[0].posxColTig = 0.0f;
	KeyFrame[0].posyColTig = 0.0f;



	
	//panda
	KeyFrame[1].movPanda_x = -6.0f;
	KeyFrame[1].movPanda_y = -1.0f;
	KeyFrame[1].giroPanda = 70.0f;
	KeyFrame[1].giroPanda2 = 10.0f;
	KeyFrame[1].posxPPD = 0.3f;
	KeyFrame[1].posyPPD = -0.2f;
	KeyFrame[1].posxPPT = -0.2;
	KeyFrame[1].posyPPT = -0.04f;
	KeyFrame[1].angPatas = 0;

	//TIGRE
	KeyFrame[1].posZtig = 1.10f;
	KeyFrame[1].posYtig = 0.0f;
	KeyFrame[1].movtig_z = 0.20f;
	KeyFrame[1].movtig_y = 0.0f;
	KeyFrame[1].giroCabTig = 0.0f;
	KeyFrame[1].giroBDTig = 0.070f;
	KeyFrame[1].giroBITig = 0.20f;
	KeyFrame[1].giroPDTig = -.10f;
	KeyFrame[1].giroPITig = 0.0f;
	KeyFrame[1].giroColTig = 0.0f;

	KeyFrame[1].posxBDTig = 2.0f;
	KeyFrame[1].posyBDTig = 0.0f;
	KeyFrame[1].posxBITig = 0.0f;
	KeyFrame[1].posyBITig = 0.0f;
	KeyFrame[1].posxPDTig = 0.0f;
	KeyFrame[1].posyPDTig = 0.0f;
	KeyFrame[1].posxPITig = 2.0f;
	KeyFrame[1].posyPITig = 0.0f;
	KeyFrame[1].posxColTig = 0.0f;
	KeyFrame[1].posyColTig = 0.0f;

	//panda
	KeyFrame[2].movPanda_x = -9.0f;
	KeyFrame[2].movPanda_y = -1.0f;
	KeyFrame[2].giroPanda = 70.0f;
	KeyFrame[2].giroPanda2 = 10.0f;
	KeyFrame[2].posxPPD = 0.3f;
	KeyFrame[2].posyPPD = -0.2f;
	KeyFrame[2].posxPPT = -0.2;
	KeyFrame[2].posyPPT = -0.04f;
	KeyFrame[2].angPatas = 0;

	//TIGRE
	KeyFrame[2].posZtig = 1.10f;
	KeyFrame[2].posYtig = 0.0f;
	KeyFrame[2].movtig_z = 0.30f;
	KeyFrame[2].movtig_y = 0.2f;
	KeyFrame[2].giroCabTig = 0.0f;
	KeyFrame[2].giroBDTig = 0.069f;
	KeyFrame[2].giroBITig = 30.0f;
	KeyFrame[2].giroPDTig = -0.2f;;
	KeyFrame[2].giroPITig = 0.0f;
	KeyFrame[2].giroColTig = 0.0f;
	KeyFrame[2].posxBDTig = 4.0f;
	KeyFrame[2].posyBDTig = 0.0f;
	KeyFrame[2].posxBITig = 0.0f;
	KeyFrame[2].posyBITig = 0.0f;
	KeyFrame[2].posxPDTig = 0.0f;
	KeyFrame[2].posyPDTig = 0.0f;
	KeyFrame[2].posxPITig = 4.0f;
	KeyFrame[2].posyPITig = 0.0f;
	KeyFrame[2].posxColTig = 0.0f;
	KeyFrame[2].posyColTig = 0.0f;

	//panda
	KeyFrame[3].movPanda_x = -12.0f;
	KeyFrame[3].movPanda_y = -1.0f;
	KeyFrame[3].giroPanda = 70.0f;
	KeyFrame[3].giroPanda2 = 10.0f;
	KeyFrame[3].posxPPD = 0.3f;
	KeyFrame[3].posyPPD = -0.2f;
	KeyFrame[3].posxPPT = -0.2f;
	KeyFrame[3].posyPPT = -0.04f;
	KeyFrame[3].angPatas = 0;

	//TIGRE
	KeyFrame[3].posZtig = 1.10f;
	KeyFrame[3].posYtig = 0.0f;
	KeyFrame[3].movtig_z = 0.40f;
	KeyFrame[3].movtig_y = 0.0f;
	KeyFrame[3].giroCabTig = 0.0f;
	KeyFrame[3].giroBDTig = 0.068f;
	KeyFrame[3].giroBITig = 40.0f;
	KeyFrame[3].giroPDTig = -.30f;
	KeyFrame[3].giroPITig = 0.0f;
	KeyFrame[3].giroColTig = 0.0f;
	KeyFrame[3].posxBDTig = 6.0f;
	KeyFrame[3].posyBDTig = 0.0f;
	KeyFrame[3].posxBITig = 0.0f;
	KeyFrame[3].posyBITig = 0.0f;
	KeyFrame[3].posxPDTig = 0.0f;
	KeyFrame[3].posyPDTig = 0.0f;
	KeyFrame[3].posxPITig = 6.0f;
	KeyFrame[3].posyPITig = 0.0f;
	KeyFrame[3].posxColTig = 0.0f;
	KeyFrame[3].posyColTig = 0.0f;

	//panda
	KeyFrame[4].movPanda_x = -15.0f;
	KeyFrame[4].movPanda_y = -1.0f;
	KeyFrame[4].giroPanda = 70.0f;
	KeyFrame[4].giroPanda2 = 10.0f;
	KeyFrame[4].posxPPD = 0.3f;
	KeyFrame[4].posyPPD = -0.2f;
	KeyFrame[4].posxPPT = -0.2f;
	KeyFrame[4].posyPPT = -0.04f;
	KeyFrame[4].angPatas = 0;

	//TIGRE
	KeyFrame[4].posZtig = 1.10f;
	KeyFrame[4].posYtig = 0.0f;
	KeyFrame[4].movtig_z = 0.50f;
	KeyFrame[4].movtig_y = 0.2f;
	KeyFrame[4].giroCabTig = 0.0f;
	KeyFrame[4].giroBDTig = 0.069f;
	KeyFrame[4].giroBITig = 50.0f;
	KeyFrame[4].giroPDTig = -.50f;
	KeyFrame[4].giroPITig = 0.0f;
	KeyFrame[4].giroColTig = 0.0f;
	KeyFrame[4].posxBDTig = 8.0f;
	KeyFrame[4].posyBDTig = 0.0f;
	KeyFrame[4].posxBITig = 0.0f;
	KeyFrame[4].posyBITig = 0.0f;
	KeyFrame[4].posxPDTig = 0.0f;
	KeyFrame[4].posyPDTig = 0.0f;
	KeyFrame[4].posxPITig = 8.0f;
	KeyFrame[4].posyPITig = 0.0f;
	KeyFrame[4].posxColTig = 0.0f;
	KeyFrame[4].posyColTig = 0.0f;

	//panda
	KeyFrame[5].movPanda_x = -18.0f;
	KeyFrame[5].movPanda_y = -1.0f;
	KeyFrame[5].giroPanda = 70.0f;
	KeyFrame[5].giroPanda2 = 10.0f;
	KeyFrame[5].posxPPD = 0.3f;
	KeyFrame[5].posyPPD = -0.2f;
	KeyFrame[5].posxPPT = -0.2;
	KeyFrame[5].posyPPT = -0.04f;
	KeyFrame[5].angPatas = 0;

	//TIGRE
	KeyFrame[5].posZtig = 1.10f;
	KeyFrame[5].posYtig = 0.0f;
	KeyFrame[5].movtig_z = 0.60f;
	KeyFrame[5].movtig_y = 0.0f;
	KeyFrame[5].giroCabTig = 0.0f;
	KeyFrame[5].giroBDTig = 0.070f;
	KeyFrame[5].giroBITig = 60.0f;
	KeyFrame[5].giroPDTig = -.4f;
	KeyFrame[5].giroPITig = 0.0f;
	KeyFrame[5].giroColTig = 0.0f;
	KeyFrame[5].posxBDTig = 10.0f;
	KeyFrame[5].posyBDTig = 0.0f;
	KeyFrame[5].posxBITig = 0.0f;
	KeyFrame[5].posyBITig = 0.0f;
	KeyFrame[5].posxPDTig = 0.0f;
	KeyFrame[5].posyPDTig = 0.0f;
	KeyFrame[5].posxPITig = 10.0f;
	KeyFrame[5].posyPITig = 0.0f;
	KeyFrame[5].posxColTig = 0.0f;
	KeyFrame[5].posyColTig = 0.0f;

	//panda
	KeyFrame[6].movPanda_x = -21.0f;
	KeyFrame[6].movPanda_y = -1.0f;
	KeyFrame[6].giroPanda = 70.0f;
	KeyFrame[6].giroPanda2 = 10.0f;
	KeyFrame[6].posxPPD = 0.3f;
	KeyFrame[6].posyPPD = -0.2f;
	KeyFrame[6].posxPPT = -0.2;
	KeyFrame[6].posyPPT = -0.04f;
	KeyFrame[6].angPatas = 0;

	//TIGRE
	KeyFrame[6].posZtig = 1.10f;
	KeyFrame[6].posYtig = 0.0f;
	KeyFrame[6].movtig_z = 0.80f;
	KeyFrame[6].movtig_y = 0.2f;
	KeyFrame[6].giroCabTig = 0.0f;
	KeyFrame[6].giroBDTig = 0.071f;
	KeyFrame[6].giroBITig = 70.0f;
	KeyFrame[6].giroPDTig = -.30f;
	KeyFrame[6].giroPITig = 0.0f;
	KeyFrame[6].giroColTig = 0.0f;
	KeyFrame[6].posxBDTig = 0.0f;
	KeyFrame[6].posyBDTig = 0.0f;
	KeyFrame[6].posxBITig = 0.0f;
	KeyFrame[6].posyBITig = 0.0f;
	KeyFrame[6].posxPDTig = 0.0f;
	KeyFrame[6].posyPDTig = 0.0f;
	KeyFrame[6].posxPITig = 0.0f;
	KeyFrame[6].posyPITig = 0.0f;
	KeyFrame[6].posxColTig = 0.0f;
	KeyFrame[6].posyColTig = 0.0f;

	//panda
	KeyFrame[7].movPanda_x = -24.0f;
	KeyFrame[7].movPanda_y = -1.0f;
	KeyFrame[7].giroPanda = 70.0f;
	KeyFrame[7].giroPanda2 = 10.0f;
	KeyFrame[7].posxPPD = 0.3f;
	KeyFrame[7].posyPPD = -0.2f;
	KeyFrame[7].posxPPT = -0.2;
	KeyFrame[7].posyPPT = -0.04f;
	KeyFrame[7].angPatas = 0;

	//TIGRE
	KeyFrame[7].posZtig = 1.10f;
	KeyFrame[7].posYtig = 0.0f;
	KeyFrame[7].movtig_z = 1.0f;
	KeyFrame[7].movtig_y = 0.0f;
	KeyFrame[7].giroCabTig = 0.0f;
	KeyFrame[7].giroBDTig = 0.072f;
	KeyFrame[7].giroBITig = 80.0f;
	KeyFrame[7].giroPDTig = -.20f;
	KeyFrame[7].giroPITig = 0.0f;
	KeyFrame[7].giroColTig = 0.0f;
	KeyFrame[7].posxBDTig = 0.0f;
	KeyFrame[7].posyBDTig = 0.0f;
	KeyFrame[7].posxBITig = 0.0f;
	KeyFrame[7].posyBITig = 0.0f;
	KeyFrame[7].posxPDTig = 0.0f;
	KeyFrame[7].posyPDTig = 0.0f;
	KeyFrame[7].posxPITig = 0.0f;
	KeyFrame[7].posyPITig = 0.0f;
	KeyFrame[7].posxColTig = 0.0f;
	KeyFrame[7].posyColTig = 0.0f;

	//panda
	KeyFrame[8].movPanda_x = -27.0f;
	KeyFrame[8].movPanda_y = -1.0f;
	KeyFrame[8].giroPanda = 70.0f;
	KeyFrame[8].giroPanda2 = 10.0f;
	KeyFrame[8].posxPPD = 0.3f;
	KeyFrame[8].posyPPD = -0.2f;
	KeyFrame[8].posxPPT = -0.2;
	KeyFrame[8].posyPPT = -0.04f;
	KeyFrame[8].angPatas = 0;

	//TIGRE
	KeyFrame[8].posZtig = 1.10f;
	KeyFrame[8].posYtig = 0.0f;
	KeyFrame[8].movtig_z = 1.2f;
	KeyFrame[8].movtig_y = 0.2f;
	KeyFrame[8].giroCabTig = 0.0f;
	KeyFrame[8].giroBDTig = 0.071f;
	KeyFrame[8].giroBITig = 90.0f;
	KeyFrame[8].giroPDTig = -0.10f;
	KeyFrame[8].giroPITig = 0.0f;
	KeyFrame[8].giroColTig = 0.0f;
	KeyFrame[8].posxBDTig = 0.0f;
	KeyFrame[8].posyBDTig = 0.0f;
	KeyFrame[8].posxBITig = 0.0f;
	KeyFrame[8].posyBITig = 0.0f;
	KeyFrame[8].posxPDTig = 0.0f;
	KeyFrame[8].posyPDTig = 0.0f;
	KeyFrame[8].posxPITig = 0.0f;
	KeyFrame[8].posyPITig = 0.0f;
	KeyFrame[8].posxColTig = 0.0f;
	KeyFrame[8].posyColTig = 0.0f;

	//panda
	KeyFrame[9].movPanda_x = -30.0f;
	KeyFrame[9].movPanda_y = -1.0f;
	KeyFrame[9].giroPanda = 70.0f;
	KeyFrame[9].giroPanda2 = 10.0f;
	KeyFrame[9].posxPPD = 0.3f;
	KeyFrame[9].posyPPD = -0.2f;
	KeyFrame[9].posxPPT = -0.2;
	KeyFrame[9].posyPPT = -0.04f;
	KeyFrame[9].angPatas = 0;

	//TIGRE
	KeyFrame[9].posZtig = 1.10f;
	KeyFrame[9].posYtig = 0.0f;
	KeyFrame[9].movtig_z = 1.4f;
	KeyFrame[9].movtig_y = 0.4f;
	KeyFrame[9].giroCabTig = 0.0f;
	KeyFrame[9].giroBDTig = 0.070f;
	KeyFrame[9].giroBITig = 100.0f;
	KeyFrame[9].giroPDTig = 0.0f;
	KeyFrame[9].giroPITig = 0.0f;
	KeyFrame[9].giroColTig = 0.0f;
	KeyFrame[9].posxBDTig = 0.0f;
	KeyFrame[9].posyBDTig = 0.0f;
	KeyFrame[9].posxBITig = 0.0f;
	KeyFrame[9].posyBITig = 0.0f;
	KeyFrame[9].posxPDTig = 0.0f;
	KeyFrame[9].posyPDTig = 0.0f;
	KeyFrame[9].posxPITig = 0.0f;
	KeyFrame[9].posyPITig = 0.0f;
	KeyFrame[9].posxColTig = 0.0f;
	KeyFrame[9].posyColTig = 0.0f;

	//panda
	KeyFrame[10].movPanda_x = -30.0f;
	KeyFrame[10].movPanda_y = -0.5f;
	KeyFrame[10].giroPanda = 35.0f;
	KeyFrame[10].giroPanda2 = 5.0f;
	KeyFrame[10].posxPPD = 0.15f;
	KeyFrame[10].posyPPD = -0.1f;
	KeyFrame[10].posxPPT = -0.1;
	KeyFrame[10].posyPPT = -0.02f;
	KeyFrame[10].angPatas = 0.0f;

	//TIGRE
	KeyFrame[10].posZtig = 1.10f;
	KeyFrame[10].posYtig = 0.0f;
	KeyFrame[10].movtig_z = 1.6f;
	KeyFrame[10].movtig_y = 0.6f;
	KeyFrame[10].giroCabTig = 0.0f;
	KeyFrame[10].giroBDTig = 0.069f;
	KeyFrame[10].giroBITig = 110.0f;
	KeyFrame[10].giroPDTig = .10f;
	KeyFrame[10].giroPITig = 0.0f;
	KeyFrame[10].giroColTig = 0.0f;
	KeyFrame[10].posxBDTig = 0.0f;
	KeyFrame[10].posyBDTig = 0.0f;
	KeyFrame[10].posxBITig = 0.0f;
	KeyFrame[10].posyBITig = 0.0f;
	KeyFrame[10].posxPDTig = 0.0f;
	KeyFrame[10].posyPDTig = 0.0f;
	KeyFrame[10].posxPITig = 0.0f;
	KeyFrame[10].posyPITig = 0.0f;
	KeyFrame[10].posxColTig = 0.0f;
	KeyFrame[10].posyColTig = 0.0f;

	//panda
	KeyFrame[11].movPanda_x = -30.0f;
	KeyFrame[11].movPanda_y = 0.0f;
	KeyFrame[11].giroPanda = 0.0f;
	KeyFrame[11].giroPanda2 = 0.0f;
	KeyFrame[11].posxPPD = 0.0f;
	KeyFrame[11].posyPPD = 0.0f;
	KeyFrame[11].posxPPT = 0.0f;
	KeyFrame[11].posyPPT = 0.0f;
	KeyFrame[11].angPatas = 90;

	//TIGRE
	KeyFrame[11].posZtig = 1.10f;
	KeyFrame[11].posYtig = 0.0f;
	KeyFrame[11].movtig_z = 1.8f;
	KeyFrame[11].movtig_y = 0.8f;
	KeyFrame[11].giroCabTig = 0.0f;
	KeyFrame[11].giroBDTig = 0.068f;
	KeyFrame[11].giroBITig = 120.0f;
	KeyFrame[11].giroPDTig = 0.20f;
	KeyFrame[11].giroPITig = 0.0f;
	KeyFrame[11].giroColTig = 0.0f;
	KeyFrame[11].posxBDTig = 0.0f;
	KeyFrame[11].posyBDTig = 0.0f;
	KeyFrame[11].posxBITig = 0.0f;
	KeyFrame[11].posyBITig = 0.0f;
	KeyFrame[11].posxPDTig = 0.0f;
	KeyFrame[11].posyPDTig = 0.0f;
	KeyFrame[11].posxPITig = 0.0f;
	KeyFrame[11].posyPITig = 0.0f;
	KeyFrame[11].posxColTig = 0.0f;
	KeyFrame[11].posyColTig = 0.0f;

	//panda
	KeyFrame[12].movPanda_x = -30.0f;
	KeyFrame[12].movPanda_y = 0.0f;
	KeyFrame[12].giroPanda = 0.0f;
	KeyFrame[12].giroPanda2 = 0.0f;
	KeyFrame[12].posxPPD = 0.0f;
	KeyFrame[12].posyPPD = 0.0f;
	KeyFrame[12].posxPPT = 0.0;
	KeyFrame[12].posyPPT = 0.0f;
	KeyFrame[12].angPatas = 180;

	//TIGRE
	KeyFrame[12].posZtig = 1.10f;
	KeyFrame[12].posYtig = 0.0f;
	KeyFrame[12].movtig_z = 2.0f;
	KeyFrame[12].movtig_y = 1.0f;
	KeyFrame[12].giroCabTig = 0.0f;
	KeyFrame[12].giroBDTig = 0.069f;
	KeyFrame[12].giroBITig = 110.0f;
	KeyFrame[12].giroPDTig = .30f;
	KeyFrame[12].giroPITig = 0.0f;
	KeyFrame[12].giroColTig = 0.0f;
	KeyFrame[12].posxBDTig = 0.0f;
	KeyFrame[12].posyBDTig = 0.0f;
	KeyFrame[12].posxBITig = 0.0f;
	KeyFrame[12].posyBITig = 0.0f;
	KeyFrame[12].posxPDTig = 0.0f;
	KeyFrame[12].posyPDTig = 0.0f;
	KeyFrame[12].posxPITig = 0.0f;
	KeyFrame[12].posyPITig = 0.0f;
	KeyFrame[12].posxColTig = 0.0f;
	KeyFrame[12].posyColTig = 0.0f;

	//panda Vuelta
	KeyFrame[13].movPanda_x = -27.0f;
	KeyFrame[13].movPanda_y = -0.5f;
	KeyFrame[13].giroPanda = 35.0f;
	KeyFrame[13].giroPanda2 = -5.0f;
	KeyFrame[13].posxPPD = 0.15f;
	KeyFrame[13].posyPPD = -0.1f;
	KeyFrame[13].posxPPT = -0.1;
	KeyFrame[13].posyPPT = -0.02f;
	KeyFrame[13].angPatas = 180.0f;

	//TIGRE
	KeyFrame[13].posZtig = 1.10f;
	KeyFrame[13].posYtig = 0.0f;
	KeyFrame[13].movtig_z = 2.2f;
	KeyFrame[13].movtig_y = 1.0f;
	KeyFrame[13].giroCabTig = 0.0f;
	KeyFrame[13].giroBDTig = 0.070f;
	KeyFrame[13].giroBITig = 100.0f;
	KeyFrame[13].giroPDTig = .40f;
	KeyFrame[13].giroPITig = 0.0f;
	KeyFrame[13].giroColTig = 0.0f;
	KeyFrame[13].posxBDTig = 0.0f;
	KeyFrame[13].posyBDTig = 0.0f;
	KeyFrame[13].posxBITig = 0.0f;
	KeyFrame[13].posyBITig = 0.0f;
	KeyFrame[13].posxPDTig = 0.0f;
	KeyFrame[13].posyPDTig = 0.0f;
	KeyFrame[13].posxPITig = 0.0f;
	KeyFrame[13].posyPITig = 0.0f;
	KeyFrame[13].posxColTig = 0.0f;
	KeyFrame[13].posyColTig = 0.0f;

	//Panda
	KeyFrame[14].movPanda_x = -24.0f;
	KeyFrame[14].movPanda_y = -1.0f;
	KeyFrame[14].giroPanda = 70.0f;
	KeyFrame[14].giroPanda2 = -10.0f;
	KeyFrame[14].posxPPD = 0.3f;
	KeyFrame[14].posyPPD = -0.2f;
	KeyFrame[14].posxPPT = -0.2;
	KeyFrame[14].posyPPT = -0.04f;
	KeyFrame[14].angPatas = 180;

	//TIGRE
	KeyFrame[14].posZtig = 1.10f;
	KeyFrame[14].posYtig = 0.0f;
	KeyFrame[14].movtig_z = 2.4f;
	KeyFrame[14].movtig_y = 0.8f;
	KeyFrame[14].giroCabTig = 0.0f;
	KeyFrame[14].giroBDTig = 0.071f;
	KeyFrame[14].giroBITig = 90.0f;
	KeyFrame[14].giroPDTig = .50f;
	KeyFrame[14].giroPITig = 0.0f;
	KeyFrame[14].giroColTig = 0.0f;
	KeyFrame[14].posxBDTig = 0.0f;
	KeyFrame[14].posyBDTig = 0.0f;
	KeyFrame[14].posxBITig = 0.0f;
	KeyFrame[14].posyBITig = 0.0f;
	KeyFrame[14].posxPDTig = 0.0f;
	KeyFrame[14].posyPDTig = 0.0f;
	KeyFrame[14].posxPITig = 0.0f;
	KeyFrame[14].posyPITig = 0.0f;
	KeyFrame[14].posxColTig = 0.0f;
	KeyFrame[14].posyColTig = 0.0f;

	//panda
	KeyFrame[15].movPanda_x = -21.0f;
	KeyFrame[15].movPanda_y = -1.0f;
	KeyFrame[15].giroPanda = 70.0f;
	KeyFrame[15].giroPanda2 = -10.0f;
	KeyFrame[15].posxPPD = 0.3f;
	KeyFrame[15].posyPPD = -0.2f;
	KeyFrame[15].posxPPT = -0.2;
	KeyFrame[15].posyPPT = -0.04f;
	KeyFrame[15].angPatas = 180;

	//TIGRE
	KeyFrame[15].posZtig = 1.10f;
	KeyFrame[15].posYtig = 0.0f;
	KeyFrame[15].movtig_z = 2.6f;
	KeyFrame[15].movtig_y = 0.6f;
	KeyFrame[15].giroCabTig = 0.0f;
	KeyFrame[15].giroBDTig = 0.072f;
	KeyFrame[15].giroBITig = 80.0f;
	KeyFrame[15].giroPDTig = 0.40f;
	KeyFrame[15].giroPITig = 0.0f;
	KeyFrame[15].giroColTig = 0.0f;
	KeyFrame[15].posxBDTig = 0.0f;
	KeyFrame[15].posyBDTig = 0.0f;
	KeyFrame[15].posxBITig = 0.0f;
	KeyFrame[15].posyBITig = 0.0f;
	KeyFrame[15].posxPDTig = 0.0f;
	KeyFrame[15].posyPDTig = 0.0f;
	KeyFrame[15].posxPITig = 0.0f;
	KeyFrame[15].posyPITig = 0.0f;
	KeyFrame[15].posxColTig = 0.0f;
	KeyFrame[15].posyColTig = 0.0f;

	//panda
	KeyFrame[16].movPanda_x = -18.0f;
	KeyFrame[16].movPanda_y = -1.0f;
	KeyFrame[16].giroPanda = 70.0f;
	KeyFrame[16].giroPanda2 = -10.0f;
	KeyFrame[16].posxPPD = 0.3f;
	KeyFrame[16].posyPPD = -0.2f;
	KeyFrame[16].posxPPT = -0.2;
	KeyFrame[16].posyPPT = -0.04f;
	KeyFrame[16].angPatas = 180;

	//TIGRE
	KeyFrame[16].posZtig = 1.10f;
	KeyFrame[16].posYtig = 0.0f;
	KeyFrame[16].movtig_z = 2.8f;
	KeyFrame[16].movtig_y = 0.4f;
	KeyFrame[16].giroCabTig = 0.0f;
	KeyFrame[16].giroBDTig = 0.071f;
	KeyFrame[16].giroBITig = 70.0f;
	KeyFrame[16].giroPDTig = .30f;
	KeyFrame[16].giroPITig = 0.0f;
	KeyFrame[16].giroColTig = 0.0f;
	KeyFrame[16].posxBDTig = 0.0f;
	KeyFrame[16].posyBDTig = 0.0f;
	KeyFrame[16].posxBITig = 0.0f;
	KeyFrame[16].posyBITig = 0.0f;
	KeyFrame[16].posxPDTig = 0.0f;
	KeyFrame[16].posyPDTig = 0.0f;
	KeyFrame[16].posxPITig = 0.0f;
	KeyFrame[16].posyPITig = 0.0f;
	KeyFrame[16].posxColTig = 0.0f;
	KeyFrame[16].posyColTig = 0.0f;

	//panda
	KeyFrame[17].movPanda_x = -15.0f;
	KeyFrame[17].movPanda_y = -1.0f;
	KeyFrame[17].giroPanda = 70.0f;
	KeyFrame[17].giroPanda2 = -10.0f;
	KeyFrame[17].posxPPD = 0.3f;
	KeyFrame[17].posyPPD = -0.2f;
	KeyFrame[17].posxPPT = -0.2;
	KeyFrame[17].posyPPT = -0.04f;
	KeyFrame[17].angPatas = 180;

	//TIGRE
	KeyFrame[17].posZtig = 1.10f;
	KeyFrame[17].posYtig = 0.0f;
	KeyFrame[17].movtig_z = 3.0f;
	KeyFrame[17].movtig_y = 0.2f;
	KeyFrame[17].giroCabTig = 0.0f;
	KeyFrame[17].giroBDTig = 0.070f;
	KeyFrame[17].giroBITig = 60.0f;
	KeyFrame[17].giroPDTig = 0.20f;
	KeyFrame[17].giroPITig = 0.0f;
	KeyFrame[17].giroColTig = 0.0f;
	KeyFrame[17].posxBDTig = 0.0f;
	KeyFrame[17].posyBDTig = 0.0f;
	KeyFrame[17].posxBITig = 0.0f;
	KeyFrame[17].posyBITig = 0.0f;
	KeyFrame[17].posxPDTig = 0.0f;
	KeyFrame[17].posyPDTig = 0.0f;
	KeyFrame[17].posxPITig = 0.0f;
	KeyFrame[17].posyPITig = 0.0f;
	KeyFrame[17].posxColTig = 0.0f;
	KeyFrame[17].posyColTig = 0.0f;

	//panda
	KeyFrame[18].movPanda_x = -12.0f;
	KeyFrame[18].movPanda_y = -1.0f;
	KeyFrame[18].giroPanda = 70.0f;
	KeyFrame[18].giroPanda2 = -10.0f;
	KeyFrame[18].posxPPD = 0.3f;
	KeyFrame[18].posyPPD = -0.2f;
	KeyFrame[18].posxPPT = -0.2;
	KeyFrame[18].posyPPT = -0.04f;
	KeyFrame[18].angPatas = 180;

	//TIGRE
	KeyFrame[18].posZtig = 1.10f;
	KeyFrame[18].posYtig = 0.0f;
	KeyFrame[18].movtig_z = 3.2f;
	KeyFrame[18].movtig_y = 0.0f;
	KeyFrame[18].giroCabTig = 0.0f;
	KeyFrame[18].giroBDTig = 0.069f;
	KeyFrame[18].giroBITig = 50.0f;
	KeyFrame[18].giroPDTig = .10f;
	KeyFrame[18].giroPITig = 0.0f;
	KeyFrame[18].giroColTig = 0.0f;
	KeyFrame[18].posxBDTig = 0.0f;
	KeyFrame[18].posyBDTig = 0.0f;
	KeyFrame[18].posxBITig = 0.0f;
	KeyFrame[18].posyBITig = 0.0f;
	KeyFrame[18].posxPDTig = 0.0f;
	KeyFrame[18].posyPDTig = 0.0f;
	KeyFrame[18].posxPITig = 0.0f;
	KeyFrame[18].posyPITig = 0.0f;
	KeyFrame[18].posxColTig = 0.0f;
	KeyFrame[18].posyColTig = 0.0f;

	//panda
	KeyFrame[19].movPanda_x = -9.0f;
	KeyFrame[19].movPanda_y = -1.0f;
	KeyFrame[19].giroPanda = 70.0f;
	KeyFrame[19].giroPanda2 = -10.0f;
	KeyFrame[19].posxPPD = 0.3f;
	KeyFrame[19].posyPPD = -0.2f;
	KeyFrame[19].posxPPT = -0.2;
	KeyFrame[19].posyPPT = -0.04f;
	KeyFrame[19].angPatas = 180;

	//TIGRE
	KeyFrame[19].posZtig = 1.10f;
	KeyFrame[19].posYtig = 0.0f;
	KeyFrame[19].movtig_z = 3.4f;
	KeyFrame[19].movtig_y = 0.0f;
	KeyFrame[19].giroCabTig = 0.0f;
	KeyFrame[19].giroBDTig = 0.068f;
	KeyFrame[19].giroBITig = 40.0f;
	KeyFrame[19].giroPDTig = 0.0f;
	KeyFrame[19].giroPITig = 0.0f;
	KeyFrame[19].giroColTig = 0.0f;
	KeyFrame[19].posxBDTig = 0.0f;
	KeyFrame[19].posyBDTig = 0.0f;
	KeyFrame[19].posxBITig = 0.0f;
	KeyFrame[19].posyBITig = 0.0f;
	KeyFrame[19].posxPDTig = 0.0f;
	KeyFrame[19].posyPDTig = 0.0f;
	KeyFrame[19].posxPITig = 0.0f;
	KeyFrame[19].posyPITig = 0.0f;
	KeyFrame[19].posxColTig = 0.0f;
	KeyFrame[19].posyColTig = 0.0f;


	//panda
	KeyFrame[20].movPanda_x = -6.0f;
	KeyFrame[20].movPanda_y = -1.0f;
	KeyFrame[20].giroPanda = 70.0f;
	KeyFrame[20].giroPanda2 = -10.0f;
	KeyFrame[20].posxPPD = 0.3f;
	KeyFrame[20].posyPPD = -0.2f;
	KeyFrame[20].posxPPT = -0.2;
	KeyFrame[20].posyPPT = -0.04f;
	KeyFrame[20].angPatas = 180;

	//TIGRE
	KeyFrame[20].posZtig = 1.10f;
	KeyFrame[20].posYtig = 0.0f;
	KeyFrame[20].movtig_z = 3.6f;
	KeyFrame[20].movtig_y = 0.0f;
	KeyFrame[20].giroCabTig = 0.0f;
	KeyFrame[20].giroBDTig = 0.069f;
	KeyFrame[20].giroBITig = 30.0f;
	KeyFrame[20].giroPDTig = 0.0f;
	KeyFrame[20].giroPITig = 0.0f;
	KeyFrame[20].giroColTig = 0.0f;
	KeyFrame[20].posxBDTig = 0.0f;
	KeyFrame[20].posyBDTig = 0.0f;
	KeyFrame[20].posxBITig = 0.0f;
	KeyFrame[20].posyBITig = 0.0f;
	KeyFrame[20].posxPDTig = 0.0f;
	KeyFrame[20].posyPDTig = 0.0f;
	KeyFrame[20].posxPITig = 0.0f;
	KeyFrame[20].posyPITig = 0.0f;
	KeyFrame[20].posxColTig = 0.0f;
	KeyFrame[20].posyColTig = 0.0f;

	//panda
	KeyFrame[21].movPanda_x = -3.0f;
	KeyFrame[21].movPanda_y = -1.0f;
	KeyFrame[21].giroPanda = 70.0f;
	KeyFrame[21].giroPanda2 = -10.0f;
	KeyFrame[21].posxPPD = 0.3f;
	KeyFrame[21].posyPPD = -0.2f;
	KeyFrame[21].posxPPT = -0.2;
	KeyFrame[21].posyPPT = -0.04f;
	KeyFrame[21].angPatas = 180;

	//TIGRE
	KeyFrame[21].posZtig = 1.10f;
	KeyFrame[21].posYtig = 0.0f;
	KeyFrame[21].movtig_z = 3.8f;
	KeyFrame[21].movtig_y = 0.0f;
	KeyFrame[21].giroCabTig = 0.0f;
	KeyFrame[21].giroBDTig = 0.070f;
	KeyFrame[21].giroBITig = 20.0f;
	KeyFrame[21].giroPDTig = 0.0f;
	KeyFrame[21].giroPITig = 0.0f;
	KeyFrame[21].giroColTig = 0.0f;
	KeyFrame[21].posxBDTig = 0.0f;
	KeyFrame[21].posyBDTig = 0.0f;
	KeyFrame[21].posxBITig = 0.0f;
	KeyFrame[21].posyBITig = 0.0f;
	KeyFrame[21].posxPDTig = 0.0f;
	KeyFrame[21].posyPDTig = 0.0f;
	KeyFrame[21].posxPITig = 0.0f;
	KeyFrame[21].posyPITig = 0.0f;
	KeyFrame[21].posxColTig = 0.0f;
	KeyFrame[21].posyColTig = 0.0f;

	//panda
	KeyFrame[22].movPanda_x = 0.0f;
	KeyFrame[22].movPanda_y = -1.0f;
	KeyFrame[22].giroPanda = 70.0f;
	KeyFrame[22].giroPanda2 = -10.0f;
	KeyFrame[22].posxPPD = 0.3f;
	KeyFrame[22].posyPPD = -0.2f;
	KeyFrame[22].posxPPT = -0.2;
	KeyFrame[22].posyPPT = -0.04f;
	KeyFrame[22].angPatas = 180;

	//TIGRE
	KeyFrame[22].posZtig = 1.10f;
	KeyFrame[22].posYtig = 0.0f;
	KeyFrame[22].movtig_z = 4.0f;
	KeyFrame[22].movtig_y = 0.0f;
	KeyFrame[22].giroCabTig = 0.0f;
	KeyFrame[22].giroBDTig = 0.071f;
	KeyFrame[22].giroBITig = 10.0f;
	KeyFrame[22].giroPDTig = 0.0f;
	KeyFrame[22].giroPITig = 0.0f;
	KeyFrame[22].giroColTig = 0.0f;
	KeyFrame[22].posxBDTig = 0.0f;
	KeyFrame[22].posyBDTig = 0.0f;
	KeyFrame[22].posxBITig = 0.0f;
	KeyFrame[22].posyBITig = 0.0f;
	KeyFrame[22].posxPDTig = 0.0f;
	KeyFrame[22].posyPDTig = 0.0f;
	KeyFrame[22].posxPITig = 0.0f;
	KeyFrame[22].posyPITig = 0.0f;
	KeyFrame[22].posxColTig = 0.0f;
	KeyFrame[22].posyColTig = 0.0f;


	//panda
	KeyFrame[23].movPanda_x = 0.0f;
	KeyFrame[23].movPanda_y = -0.5f;
	KeyFrame[23].giroPanda = 35.0f;
	KeyFrame[23].giroPanda2 = -5.0f;
	KeyFrame[23].posxPPD = 0.15f;
	KeyFrame[23].posyPPD = -0.1f;
	KeyFrame[23].posxPPT = -0.1;
	KeyFrame[23].posyPPT = -0.02f;
	KeyFrame[23].angPatas = 180;

	//TIGRE
	KeyFrame[23].posZtig = 1.10f;
	KeyFrame[23].posYtig = 0.0f;
	KeyFrame[23].movtig_z = 4.2f;
	KeyFrame[23].movtig_y = 0.0f;
	KeyFrame[23].giroCabTig = 0.0f;
	KeyFrame[23].giroBDTig = 0.072f;
	KeyFrame[23].giroBITig = 0.0f;
	KeyFrame[23].giroPDTig = 0.0f;
	KeyFrame[23].giroPITig = 0.0f;
	KeyFrame[23].giroColTig = 0.0f;
	KeyFrame[23].posxBDTig = 0.0f;
	KeyFrame[23].posyBDTig = 0.0f;
	KeyFrame[23].posxBITig = 0.0f;
	KeyFrame[23].posyBITig = 0.0f;
	KeyFrame[23].posxPDTig = 0.0f;
	KeyFrame[23].posyPDTig = 0.0f;
	KeyFrame[23].posxPITig = 0.0f;
	KeyFrame[23].posyPITig = 0.0f;
	KeyFrame[23].posxColTig = 0.0f;
	KeyFrame[23].posyColTig = 0.0f;

	//panda
	KeyFrame[24].movPanda_x = 0.0f;
	KeyFrame[24].movPanda_y = 0.0f;
	KeyFrame[24].giroPanda = 0.0f;
	KeyFrame[24].giroPanda2 = 0.0f;
	KeyFrame[24].posxPPD = 0.0f;
	KeyFrame[24].posyPPD = 0.0f;
	KeyFrame[24].posxPPT = 0.0f;
	KeyFrame[24].posyPPT = 0.0f;
	KeyFrame[24].angPatas = 270;

	//TIGRE
	KeyFrame[24].posZtig = 1.10f;
	KeyFrame[24].posYtig = 0.0f;
	KeyFrame[24].movtig_z = 4.4f;
	KeyFrame[24].movtig_y = 0.0f;
	KeyFrame[24].giroCabTig = 0.0f;
	KeyFrame[24].giroBDTig = 0.071f;
	KeyFrame[24].giroBITig = 0.0f;
	KeyFrame[24].giroPDTig = 0.0f;
	KeyFrame[24].giroPITig = 0.0f;
	KeyFrame[24].giroColTig = 0.0f;
	KeyFrame[24].posxBDTig = 0.0f;
	KeyFrame[24].posyBDTig = 0.0f;
	KeyFrame[24].posxBITig = 0.0f;
	KeyFrame[24].posyBITig = 0.0f;
	KeyFrame[24].posxPDTig = 0.0f;
	KeyFrame[24].posyPDTig = 0.0f;
	KeyFrame[24].posxPITig = 0.0f;
	KeyFrame[24].posyPITig = 0.0f;
	KeyFrame[24].posxColTig = 0.0f;
	KeyFrame[24].posyColTig = 0.0f;

	//panda
	KeyFrame[25].movPanda_x = 0.0f;
	KeyFrame[25].movPanda_y = 0.0f;
	KeyFrame[25].giroPanda = 0.0f;
	KeyFrame[25].giroPanda2 = 0.0f;
	KeyFrame[25].posxPPD = 0.0f;
	KeyFrame[25].posyPPD = 0.0f;
	KeyFrame[25].posxPPT = 0.0;
	KeyFrame[25].posyPPT = 0.0f;
	KeyFrame[25].angPatas = 360;

	//TIGRE
	KeyFrame[25].posZtig = 1.10f;
	KeyFrame[25].posYtig = 0.0f;
	KeyFrame[25].movtig_z = 4.6f;
	KeyFrame[25].movtig_y = 0.0f;
	KeyFrame[25].giroCabTig = 0.0f;
	KeyFrame[25].giroBDTig = 0.070f;
	KeyFrame[25].giroBITig = 0.0f;
	KeyFrame[25].giroPDTig = 0.0f;
	KeyFrame[25].giroPITig = 0.0f;
	KeyFrame[25].giroColTig = 0.0f;
	KeyFrame[25].posxBDTig = 0.0f;
	KeyFrame[25].posyBDTig = 0.0f;
	KeyFrame[25].posxBITig = 0.0f;
	KeyFrame[25].posyBITig = 0.0f;
	KeyFrame[25].posxPDTig = 0.0f;
	KeyFrame[25].posyPDTig = 0.0f;
	KeyFrame[25].posxPITig = 0.0f;
	KeyFrame[25].posyPITig = 0.0f;
	KeyFrame[25].posxColTig = 0.0f;
	KeyFrame[25].posyColTig = 0.0f;

	//TIGRE
	KeyFrame[26].posZtig = 1.10f;
	KeyFrame[26].posYtig = 0.0f;
	KeyFrame[26].movtig_z = 4.4f;
	KeyFrame[26].movtig_y = 0.0f;
	KeyFrame[26].giroCabTig = 0.0f;
	KeyFrame[26].giroBDTig = 0.069f;
	KeyFrame[26].giroBITig = 0.0f;
	KeyFrame[26].giroPDTig = 0.0f;
	KeyFrame[26].giroPITig = 0.0f;
	KeyFrame[26].giroColTig = 0.0f;
	KeyFrame[26].posxBDTig = 0.0f;
	KeyFrame[26].posyBDTig = 0.0f;
	KeyFrame[26].posxBITig = 0.0f;
	KeyFrame[26].posyBITig = 0.0f;
	KeyFrame[26].posxPDTig = 0.0f;
	KeyFrame[26].posyPDTig = 0.0f;
	KeyFrame[26].posxPITig = 0.0f;
	KeyFrame[26].posyPITig = 0.0f;
	KeyFrame[26].posxColTig = 0.0f;
	KeyFrame[26].posyColTig = 0.0f;

	//TIGRE
	KeyFrame[27].posZtig = 1.10f;
	KeyFrame[27].posYtig = 0.0f;
	KeyFrame[27].movtig_z = 4.8f;
	KeyFrame[27].movtig_y = 0.0f;
	KeyFrame[27].giroCabTig = 0.0f;
	KeyFrame[27].giroBDTig = 0.068f;
	KeyFrame[27].giroBITig = 0.0f;
	KeyFrame[27].giroPDTig = 0.0f;
	KeyFrame[27].giroPITig = 0.0f;
	KeyFrame[27].giroColTig = 0.0f;
	KeyFrame[27].posxBDTig = 0.0f;
	KeyFrame[27].posyBDTig = 0.0f;
	KeyFrame[27].posxBITig = 0.0f;
	KeyFrame[27].posyBITig = 0.0f;
	KeyFrame[27].posxPDTig = 0.0f;
	KeyFrame[27].posyPDTig = 0.0f;
	KeyFrame[27].posxPITig = 0.0f;
	KeyFrame[27].posyPITig = 0.0f;
	KeyFrame[27].posxColTig = 0.0f;
	KeyFrame[27].posyColTig = 0.0f;

	//TIGRE
	KeyFrame[28].posZtig = 1.10f;
	KeyFrame[28].posYtig = 0.0f;
	KeyFrame[28].movtig_z = 5.0f;
	KeyFrame[28].movtig_y = 0.0f;
	KeyFrame[28].giroCabTig = 0.0f;
	KeyFrame[28].giroBDTig = 0.069f;
	KeyFrame[28].giroBITig = 0.0f;
	KeyFrame[28].giroPDTig = 0.0f;
	KeyFrame[28].giroPITig = 0.0f;
	KeyFrame[28].giroColTig = 0.0f;
	KeyFrame[28].posxBDTig = 0.0f;
	KeyFrame[28].posyBDTig = 0.0f;
	KeyFrame[28].posxBITig = 0.0f;
	KeyFrame[28].posyBITig = 0.0f;
	KeyFrame[28].posxPDTig = 0.0f;
	KeyFrame[28].posyPDTig = 0.0f;
	KeyFrame[28].posxPITig = 0.0f;
	KeyFrame[28].posyPITig = 0.0f;
	KeyFrame[28].posxColTig = 0.0f;
	KeyFrame[28].posyColTig = 0.0f;

	//TIGRE
	KeyFrame[29].posZtig = 1.10f;
	KeyFrame[29].posYtig = 0.0f;
	KeyFrame[29].movtig_z = 5.2f;
	KeyFrame[29].movtig_y = 0.0f;
	KeyFrame[29].giroCabTig = 0.0f;
	KeyFrame[29].giroBDTig = 0.070f;
	KeyFrame[29].giroBITig = 0.0f;
	KeyFrame[29].giroPDTig = 0.0f;
	KeyFrame[29].giroPITig = 0.0f;
	KeyFrame[29].giroColTig = 0.0f;
	KeyFrame[29].posxBDTig = 0.0f;
	KeyFrame[29].posyBDTig = 0.0f;
	KeyFrame[29].posxBITig = 0.0f;
	KeyFrame[29].posyBITig = 0.0f;
	KeyFrame[29].posxPDTig = 0.0f;
	KeyFrame[29].posyPDTig = 0.0f;
	KeyFrame[29].posxPITig = 0.0f;
	KeyFrame[29].posyPITig = 0.0f;
	KeyFrame[29].posxColTig = 0.0f;
	KeyFrame[29].posyColTig = 0.0f;

	//TIGRE
	KeyFrame[30].posZtig = 1.10f;
	KeyFrame[30].posYtig = 0.0f;
	KeyFrame[30].movtig_z = 5.4f;
	KeyFrame[30].movtig_y = 0.0f;
	KeyFrame[30].giroCabTig = 0.0f;
	KeyFrame[30].giroBDTig = 0.071f;
	KeyFrame[30].giroBITig = 0.0f;
	KeyFrame[30].giroPDTig = 0.0f;
	KeyFrame[30].giroPITig = 0.0f;
	KeyFrame[30].giroColTig = 0.0f;
	KeyFrame[30].posxBDTig = 0.0f;
	KeyFrame[30].posyBDTig = 0.0f;
	KeyFrame[30].posxBITig = 0.0f;
	KeyFrame[30].posyBITig = 0.0f;
	KeyFrame[30].posxPDTig = 0.0f;
	KeyFrame[30].posyPDTig = 0.0f;
	KeyFrame[30].posxPITig = 0.0f;
	KeyFrame[30].posyPITig = 0.0f;
	KeyFrame[30].posxColTig = 0.0f;
	KeyFrame[30].posyColTig = 0.0f;

	//TIGRE
	KeyFrame[31].posZtig = 1.10f;
	KeyFrame[31].posYtig = 0.0f;
	KeyFrame[31].movtig_z = 5.6f;
	KeyFrame[31].movtig_y = 0.0f;
	KeyFrame[31].giroCabTig = 0.0f;
	KeyFrame[31].giroBDTig = 0.072f;
	KeyFrame[31].giroBITig = 0.0f;
	KeyFrame[31].giroPDTig = 0.0f;
	KeyFrame[31].giroPITig = 0.0f;
	KeyFrame[31].giroColTig = 0.0f;
	KeyFrame[31].posxBDTig = 0.0f;
	KeyFrame[31].posyBDTig = 0.0f;
	KeyFrame[31].posxBITig = 0.0f;
	KeyFrame[31].posyBITig = 0.0f;
	KeyFrame[31].posxPDTig = 0.0f;
	KeyFrame[31].posyPDTig = 0.0f;
	KeyFrame[31].posxPITig = 0.0f;
	KeyFrame[31].posyPITig = 0.0f;
	KeyFrame[31].posxColTig = 0.0f;
	KeyFrame[31].posyColTig = 0.0f;

	//TIGRE
	KeyFrame[32].posZtig = 1.10f;
	KeyFrame[32].posYtig = 0.0f;
	KeyFrame[32].movtig_z = 5.8f;
	KeyFrame[32].movtig_y = 0.0f;
	KeyFrame[32].giroCabTig = 0.0f;
	KeyFrame[32].giroBDTig = 0.071f;
	KeyFrame[32].giroBITig = 0.0f;
	KeyFrame[32].giroPDTig = 0.0f;
	KeyFrame[32].giroPITig = 0.0f;
	KeyFrame[32].giroColTig = 0.0f;
	KeyFrame[32].posxBDTig = 0.0f;
	KeyFrame[32].posyBDTig = 0.0f;
	KeyFrame[32].posxBITig = 0.0f;
	KeyFrame[32].posyBITig = 0.0f;
	KeyFrame[32].posxPDTig = 0.0f;
	KeyFrame[32].posyPDTig = 0.0f;
	KeyFrame[32].posxPITig = 0.0f;
	KeyFrame[32].posyPITig = 0.0f;
	KeyFrame[32].posxColTig = 0.0f;
	KeyFrame[32].posyColTig = 0.0f;

	//TIGRE
	KeyFrame[33].posZtig = 1.10f;
	KeyFrame[33].posYtig = 0.0f;
	KeyFrame[33].movtig_z = 6.0f;
	KeyFrame[33].movtig_y = 0.0f;
	KeyFrame[33].giroCabTig = 0.0f;
	KeyFrame[33].giroBDTig = 0.070f;
	KeyFrame[33].giroBITig = 0.0f;
	KeyFrame[33].giroPDTig = 0.0f;
	KeyFrame[33].giroPITig = 0.0f;
	KeyFrame[33].giroColTig = 0.0f;
	KeyFrame[33].posxBDTig = 0.0f;
	KeyFrame[33].posyBDTig = 0.0f;
	KeyFrame[33].posxBITig = 0.0f;
	KeyFrame[33].posyBITig = 0.0f;
	KeyFrame[33].posxPDTig = 0.0f;
	KeyFrame[33].posyPDTig = 0.0f;
	KeyFrame[33].posxPITig = 0.0f;
	KeyFrame[33].posyPITig = 0.0f;
	KeyFrame[33].posxColTig = 0.0f;
	KeyFrame[33].posyColTig = 0.0f;

	//TIGRE
	KeyFrame[34].posZtig = 1.10f;
	KeyFrame[34].posYtig = 0.0f;
	KeyFrame[34].movtig_z = 6.2f;
	KeyFrame[34].movtig_y = 0.0f;
	KeyFrame[34].giroCabTig = 0.0f;
	KeyFrame[34].giroBDTig = 0.069f;
	KeyFrame[34].giroBITig = 0.0f;
	KeyFrame[34].giroPDTig = 0.0f;
	KeyFrame[34].giroPITig = 0.0f;
	KeyFrame[34].giroColTig = 0.0f;
	KeyFrame[34].posxBDTig = 0.0f;
	KeyFrame[34].posyBDTig = 0.0f;
	KeyFrame[34].posxBITig = 0.0f;
	KeyFrame[34].posyBITig = 0.0f;
	KeyFrame[34].posxPDTig = 0.0f;
	KeyFrame[34].posyPDTig = 0.0f;
	KeyFrame[34].posxPITig = 0.0f;
	KeyFrame[34].posyPITig = 0.0f;
	KeyFrame[34].posxColTig = 0.0f;
	KeyFrame[34].posyColTig = 0.0f;

	//TIGRE
	KeyFrame[35].posZtig = 1.10f;
	KeyFrame[35].posYtig = 0.0f;
	KeyFrame[35].movtig_z = 6.4f;
	KeyFrame[35].movtig_y = 0.0f;
	KeyFrame[35].giroCabTig = 0.0f;
	KeyFrame[35].giroBDTig = 0.068f;
	KeyFrame[35].giroBITig = 0.0f;
	KeyFrame[35].giroPDTig = 0.0f;
	KeyFrame[35].giroPITig = 0.0f;
	KeyFrame[35].giroColTig = 0.0f;
	KeyFrame[35].posxBDTig = 0.0f;
	KeyFrame[35].posyBDTig = 0.0f;
	KeyFrame[35].posxBITig = 0.0f;
	KeyFrame[35].posyBITig = 0.0f;
	KeyFrame[35].posxPDTig = 0.0f;
	KeyFrame[35].posyPDTig = 0.0f;
	KeyFrame[35].posxPITig = 0.0f;
	KeyFrame[35].posyPITig = 0.0f;
	KeyFrame[35].posxColTig = 0.0f;
	KeyFrame[35].posyColTig = 0.0f;

	float movLisaX = 0.0f;  // Posición inicial en el eje X
	float movLisaZ = 0.0f;
	//float movLisaOffset = 1.2f;  // Cuánto se desplaza el coche en cada paso
	/*
	bool AvanzaLisa = true;;
	bool RegresaLisa = false;
	bool derLisa = false;
	bool izqLisa = false;
	float anguloLisa = 0.0;
	bool Avanza_p = true;;
	bool Regresa_p = false;
	bool der_p = false;
	bool izqLisa = false;
	float anguloP = 0.0;
	*/

	
	//////////
	float movMargeX = 0.0f;  // Posición inicial en el eje X
	float movMargeZ = 0.0f;
	float movMargeOffset = 1.2f;  // Cuánto se desplaza Marge en cada paso

	bool AvanzaMarge = true;
	bool RegresaMarge = false;
	bool derMarge = false;
	bool izqMarge = false;
	float anguloMarge = 0.0;

	///segunda parte
			//angulos
	float anguloCarro = 0.0f;
	float anguloMaqExp = 0.0f;
	float anguloDona = 0.0f;
	float anguloDonaRueda = 0.0f;
	//traslado
	float movXcarro = 0.0f;
	float movYcarro = 0.0f;
	float movZcarro = 0.0f;
	float movYmaqexp = 0.0f;
	float movXdona = 0.0f;
	float movYdona = 0.0f;
	float movZdona = 0.0f;
	//offset
	float movCarroOffset = 0.015f;
	float anguloCarroOffset = 0.15f;
	float movMaqExpOffset = 0.15f;
	float angulomaqoffset = 0.15f;
	float movDonaOffset = 0.15f;
	float anguloDonaOffset = 0.15f;
	//banderas
	bool entracarro = true;
	bool giraCarro = false;
	bool avanzaCarro = false;
	bool estacionaCarro = false;
	bool regresaCarro = false;
	bool retornaCarro = false;
	bool saleCarro = false;
	bool tiraMaq = true;
	bool escondeCarro = false;
	bool carroinicial = false;
	//variables panda con pivote
	bool sentarpanda = true;
	float anguloPandaPatas = 0.0f;
	float anguloPandaTorso = 0.0f;
	float anguloPandaCabeza = 0.0f;
	float movTorsoPandaX = 0.0f;
	float movTorsoPandaY = 0.0f;
	float movTorsoPandaZ = 0.0f;
	float movCabezaPandaX = 0.0f;
	float movCabezaPandaY = 0.0f;
	float movCabezaPandaZ = 0.0f;
	float movPatasPandaX = 0.0f;
	float movPatasPandaY = 0.0f;
	float movPatasPandaZ = 0.0f;
	float movCuerpoPandaX = 0.0f;
	float movCuerpoPandaY = 0.0f;
	float movCuerpoPandaZ = 0.0f;
	float angCuerpoPanda = 0.0f;
	float pandaangOffset = 0.1f;
	float pandamovOffset = 0.1f;
	bool bolitapanda = false;
	bool bolitapanda2 = false;
	bool bolitapanda3 = false;
	bool bolitapanda4 = false;
	bool bolitapanda5 = false;
	bool bolitapanda6 = false;
	bool bolitapanda7 = false;
	bool bolitapanda8 = false;
	bool bolitapanda9 = false;
	bool bolitapanda10 = false;
	bool bolitapanda11 = false;
	bool bolitapanda12 = false;
	bool bolitapanda13 = false;
	bool bolitapanda14 = false;
	bool donaVoltea = true;
	bool donaCae = false;
	bool donaRueda = false;
	bool donaCae2 = false;


	
	////Loop mientras no se cierra la ventana
///
	GLfloat lastTime = glfwGetTime();
	GLfloat deltaTime = 0.0f;
	const GLfloat limitFPS = 1.0f / 60.0f;

	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		if (dia == true)
		{
			if (movSun < 1.0f)
			{
				movSun += movSunOffset * 3;
				mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
					1.0f, 1.0f,
					//0.5f, 0.3f,
					1.0f, 0.0f, -1.0f);
				pointLightCount = 0;
				spotLightCount = 0;
			}
			else
			{
				dia = false;
				mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
					0.5f, 0.3f,
					0.0f, -1.0f, -1.0f);
				movySun = 1.0f;
				luz = 0.2f;
				skybox = Skybox(skyboxFaces2);
			}
		}
		else
		{
			if (movSun > -1.0f)
			{
				movSun -= movSunOffset;
				if (mainWindow.getinterruptor() == 1)
				{
					pointLightCount = 7;
					spotLightCount = 4;

				}
				else if (mainWindow.getinterruptor() == 0)
				{
					pointLightCount = 7;
					spotLightCount = 0;
				}
			}
			else
			{
				dia = true;
				movySun = -1.0f;
				luz = 1.0f;
				skybox = Skybox(skyboxFaces);
			}
		}

		if (avanza)
		{
			if (movCoche > -50.0f)
			{
				movCoche -= movOffset * deltaTime;
				//movCoche -= movOffset;
				rotllanta += rotllantaOffset * deltaTime;
				//printf("%f\n ",movCoche);
			}
			else
				avanza = false;
		}
		else
		{
			if (movCoche < 50.0f)
			{
				movCoche += movOffset * deltaTime;
				//movCoche += movOffset;
				rotllanta -= rotllantaOffset * deltaTime;
				//printf("%f\n ",movCoche);
			}
			else
				avanza = true;
		}

		//if (mainWindow.getRuedaPanda() == 1)
		//{
			//sentarpanda = true;
		//
		// }

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		//para keyframes
		inputKeyframes(mainWindow.getsKeys());
		animate();

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
		//spotLights[3].SetFlash(PosicionLuzHeli + glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		
		

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);
		

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::mat4 modelaux1(1.0);
		glm::mat4 modelaux2(1.0);
		glm::mat4 modelaux3(1.0);
		glm::mat4 modelaux4(1.0);
		glm::mat4 modelaux5(1.0);
		glm::mat4 modelaux6(1.0);
		glm::mat4 modelaux7(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f); 
		glm::vec3 color2 = glm::vec3(0.5f, 0.0f, 0.5f);
		glm::vec3 rojo = glm::vec3(0.8f, 0.0f, 0.0f);
		glm::vec3 verde = glm::vec3(0.0f, 0.8f, 0.0f);
		glm::vec3 azul = glm::vec3(0.0f, 0.0f, 0.8f);
		glm::vec3 amarillo = glm::vec3(0.8f, 0.8f, 0.0f);
		glm::vec3 arenoso = glm::vec3(1.0f, 0.8f, 0.0f);
		glm::vec3 blanco = glm::vec3(0.0f, 0.0f, 0.0f);

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

		//Fuente
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		fuente.RenderModel();

		//Banca1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		banca1.RenderModel();

		//Banca2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		banca2.RenderModel();

		//Puesto2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(170.0f, 3.0f, -170.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, -135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		puesto2_1.UseTexture();
		puesto2_2.UseTexture();
		puesto2_3.UseTexture();
		puesto2.RenderModel();

		//Puesto4
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(130.0f, 10.0f, -200.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//puesto2_1.UseTexture();
		//puesto2_2.UseTexture();
		//puesto2_3.UseTexture();
		puesto4.RenderModel();

		
		//Piso Exterior
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.0f));
		model = glm::scale(model, glm::vec3(6.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cementoTexture.UseTexture();
		piso_exterior.RenderModel();
		
		//PINGUINO
		if (incrementando) {
			angulobraDP += anguloPinguOffset * 2 * deltaTime;
			angulobraIP -= anguloPinguOffset * 2 * deltaTime;
			if (angulobraDP >= 20.0) {
				incrementando = false;
			}
		}
		else {
			angulobraDP -= anguloPinguOffset * 2 * deltaTime;
			angulobraIP += anguloPinguOffset * 2 * deltaTime;
			if (angulobraDP <= 0.0) {
				incrementando = true;
			}
		}
		if (incrementando2) {
			angulopieDP += anguloPinguOffset * 3 * deltaTime;
			angulopieIP -= anguloPinguOffset * 3 * deltaTime;
			if (angulopieDP >= 20.0) {
				incrementando2 = false;
			}
		}
		else {
			angulopieDP -= anguloPinguOffset * 3 * deltaTime;
			angulopieIP += anguloPinguOffset * 3 * deltaTime;
			if (angulopieDP <= 0.0) {
				incrementando2 = true;
			}
		}
		if (incrementando3) {
			angulocuerpopin += anguloPinguOffset * deltaTime;
			if (angulocuerpopin >= 5.0) {
				incrementando3 = false;
			}
		}
		else {
			angulocuerpopin -= anguloPinguOffset * 3 * deltaTime;
			if (angulocuerpopin <= 0.0) {
				incrementando3 = true;
			}
		}
		if (caminaizquierda_p) {
			if (caminaizquierdaX_p >= 35) {
				caminaizquierda_p = false;
				caminaadelante_p = true;
			}
			else {
				caminaizquierdaX_p += movPinguOffset * 3 * deltaTime;
				anguloP -= anguloPinguOffset * deltaTime;
			}
		}
		else if (caminaadelante_p) {
			if (caminadelanteZ_p >= 35) {
				caminaadelante_p = false;
				caminaderecha_p = true;
			}
			else {
				caminadelanteZ_p += movPinguOffset * 3 * deltaTime;
				anguloP -= anguloPinguOffset * deltaTime;
			}
		}
		else if (caminaderecha_p) {
			if (caminaderechaX_p <= -45) {
				caminaderecha_p = false;
				caminaatras_p = true;
			}
			else {
				caminaderechaX_p -= movPinguOffset * 3 * deltaTime;
				anguloP -= anguloPinguOffset * deltaTime;
			}
		}
		else if (caminaatras_p) {
			if (caminaatrasZ_p <= -40) {
				caminaatras_p = false;
				regresa_p = true;
			}
			else {
				caminaatrasZ_p -= movPinguOffset * 3 * deltaTime;
				anguloP -= anguloPinguOffset * deltaTime;
			}
		}
		else if (regresa_p) {
			if (regresaX_p >= -5) {
				regresa_p = false;
				caminaizquierda_p = true;
				// Reiniciar las posiciones o valores necesarios para el reinicio del recorrido
				caminaizquierdaX_p = 0;
				caminadelanteZ_p = 0;
				caminaderechaX_p = 0;
				caminaatrasZ_p = 0;
				regresaX_p = 0;
				anguloP = 0;
			}
			else {
				regresaX_p += movPinguOffset * 3 * deltaTime;
			}
		}
		else {
			caminaizquierda_p = true;
		}
		//cuerpoPingu
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 7.0f, -210.0f));
		model = glm::translate(model, glm::vec3(caminaatrasX_p + caminadelanteX_p + caminaizquierdaX_p + caminaderechaX_p + regresaX_p, 0.0f, caminaatrasZ_p + caminadelanteZ_p + caminaizquierdaZ_p + caminaderechaZ_p + regresaZ_p));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, anguloP * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, angulocuerpopin * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modelaux = model;
		modelaux1 = model;
		modelaux2 = model;
		modelaux3 = model;
		pingu.UseTexture();
		cuerpopingu.RenderModel();

		//brazosPingu
		//izquierdo
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.2f, 0.0f, -0.15f));
		model = glm::translate(model, glm::vec3(0.0f, movAlaPinguY, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, angulobraDP * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modelaux = model;
		model = modelaux;
		pingu.UseTexture();
		brazoIzqpingu.RenderModel();
		//derecho
		model = modelaux1;
		model = glm::translate(model, glm::vec3(-0.2f, 0.0f, -0.15f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, angulobraIP * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modelaux1 = model;
		model = modelaux1;
		pingu.UseTexture();
		brazoDerpingu.RenderModel();

		//patas
		//piederPingu
		model = modelaux2;
		model = glm::translate(model, glm::vec3(-0.09f, -0.7f, -0.03f));
		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		model = glm::rotate(model, angulopieDP * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modelaux2 = model;
		model = modelaux2;
		pingu.UseTexture();
		piederpingu.RenderModel();

		//pieizqPingu
		model = modelaux3;
		model = glm::translate(model, glm::vec3(0.09f, -0.7f, -0.03f));
		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		model = glm::rotate(model, angulopieIP * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modelaux3 = model;
		model = modelaux3;
		pingu.UseTexture();
		pieizqpingu.RenderModel();

		///PINGUINO 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 7.0f, -210.0f));
		model = glm::translate(model, glm::vec3(caminaatrasX_p + caminadelanteX_p + caminaizquierdaX_p + caminaderechaX_p + regresaX_p - 10.0, 0.0f, caminaatrasZ_p + caminadelanteZ_p + caminaizquierdaZ_p + caminaderechaZ_p + regresaZ_p + 10.0));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, anguloP * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, angulocuerpopin * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modelaux = model;
		modelaux1 = model;
		modelaux2 = model;
		modelaux3 = model;
		pingu.UseTexture();
		cuerpopingu.RenderModel();

		//brazosPingu
		//izquierdo
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.2f, 0.0f, -0.15f));
		model = glm::translate(model, glm::vec3(0.0f, movAlaPinguY, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, angulobraDP * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modelaux = model;
		model = modelaux;
		pingu.UseTexture();
		brazoIzqpingu.RenderModel();
		//derecho
		model = modelaux1;
		model = glm::translate(model, glm::vec3(-0.2f, 0.0f, -0.15f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, angulobraIP * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modelaux1 = model;
		model = modelaux1;
		pingu.UseTexture();
		brazoDerpingu.RenderModel();

		//patas
		//piederPingu
		model = modelaux2;
		model = glm::translate(model, glm::vec3(-0.09f, -0.7f, -0.03f));
		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		model = glm::rotate(model, angulopieDP * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modelaux2 = model;
		model = modelaux2;
		pingu.UseTexture();
		piederpingu.RenderModel();

		//pieizqPingu
		model = modelaux3;
		model = glm::translate(model, glm::vec3(0.09f, -0.7f, -0.03f));
		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		model = glm::rotate(model, angulopieIP * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modelaux3 = model;
		model = modelaux3;
		pingu.UseTexture();
		pieizqpingu.RenderModel();

		//puerta
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//cementoTexture.UseTexture();
		puerta.RenderModel();

		//MONO//////////////////////////////////////////////////
		//MONO MOVIMIENTO
		if (caminasub_m) {
			if (caminasubY_m >= 30.0f) {
				caminasub_m = false;
				caminabaj_m = true;
				anguloBM += anguloBMOffset;
			}
			else {
				caminasubY_m += movMonoOffset;
			}
		}
		else if (caminabaj_m) {
			if (caminabajY_m <= -32.0f) {
				caminabaj_m = false;
				caminasub_m = false;
				monoregresa = true;
			}
			else {
				caminabajY_m -= movMonoOffset;
			}
		}
		else if (monoregresa) {
			if (monoregresaY <= 30.0f) {
				monoregresa = false;
				caminasub_m = true;
				// Reiniciar las posiciones o valores necesarios para el reinicio del recorrido
				caminasubY_m = 0.0f;
				caminabajY_m = 0.0f;
				monoregresaY = 0.0f;
			}
			else {
				monoregresaY += movMonoOffset;
			}
			anguloBM += anguloBMOffset; // Agregar rotación de arriba hacia anguloBM durante todo el ciclo
		}

		// Rotación constante entre los ángulos 
		if (rotateClockwise) {
			anguloActual += anguloRotacion;
			if (anguloActual >= anguloMaximo) {
				anguloActual = anguloMaximo;
				rotateClockwise = false;
			}
		}
		else {
			anguloActual -= anguloRotacion;
			if (anguloActual <= anguloMinimo) {
				anguloActual = anguloMinimo;
				rotateClockwise = true;
			}
		}

		//CUERPOMONO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(50.0f, 6.8f, 223.0f)); //CAMBIAR
		model = glm::translate(model, glm::vec3(0.0f, caminasubY_m + caminabajY_m, 0.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modelaux = model;
		modelaux2 = model;
		modelaux1 = model;
		modelaux2 = model;
		modelaux3 = model;
		cuerpomono.RenderModel();

		//BRAZOS MONO
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.01f, -3.5f, -11.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, anguloActual * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modelaux = model;
		model = modelaux;
		brazosmono.RenderModel();

		//PIERNAS MONO
		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.0f, 24.5f, -4.5f));
		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		model = glm::rotate(model, anguloActual * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modelaux2 = model;
		model = modelaux2;
		piernamono.RenderModel();

		//COLA MONO
		model = modelaux3;
		model = glm::translate(model, glm::vec3(0.0f, 28.5f, 5.5f));
		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		model = glm::rotate(model, anguloActual * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modelaux3 = model;
		model = modelaux3;
		colamono.RenderModel();
		/////////////////////////

		//TIGRE CUERPO
		model = glm::mat4(1.0);
		postigre = glm::vec3(posZtig - movtig_z, posYtig + movtig_y, 0.0f);
		model = glm::translate(model, postigre);
		model = glm::translate(model, glm::vec3(40.0f, 6.5f, 195.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, giroTig * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		modelaux = model;
		modelaux2 = model;
		modelaux3 = model;
		modelaux4 = model;
		modelaux5 = model;
		modelaux6 = model;
		modelaux7 = model;
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//TCUER.RenderModel();

		//CABEZA NUEVO CUERPO
		model = modelaux;
		postigre = glm::vec3(0.0f, posYtig + movtig_y, posZtig + movtig_z);
		model = glm::translate(model, postigre);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, giro * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		modelaux = model;
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		TCUER.RenderModel();

		//CABEZA
		model = modelaux2;
		model = glm::translate(model, postigre);
		model = glm::translate(model, glm::vec3(0.0f, 0.3f, 0.8f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, giroCabTig * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux2 = model;
		model = modelaux2;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		TCAB.RenderModel();


		//BRAZO DERECHO
		model = modelaux3;
		model = glm::translate(model, postigre);
		postigre = glm::vec3(0.0f, posYtig + movtig_y, posZtig + movtig_z);
		//model = glm::translate(model, glm::vec3(-0.2f , 0.05f + posyBDTig, 0.4f + posxBDTig));
		model = glm::translate(model, glm::vec3(-0.2f, 0.05f , 0.4f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//model = glm::rotate(model, 7 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, giroBDTig * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -giroPDTig * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux3 = model;
		model = modelaux3;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		TBD.RenderModel();

		
		//BRAZO IZQUIERDO
		model = modelaux4;
		model = glm::translate(model, postigre);
		postigre = glm::vec3(0.0f, posYtig + movtig_y, posZtig + movtig_z);
		model = glm::translate(model, glm::vec3(0.2f, 0.05f , 0.55f));
		//model = glm::translate(model, glm::vec3(0.2f , 0.05f + posyBITig, 0.55f + posxBITig));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//model = glm::rotate(model, giroBDTig * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -giroPDTig * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux4 = model;
		model = modelaux4;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		TBI.RenderModel();


		//PATA DERECHA
		model = modelaux5;
		model = glm::translate(model, postigre);
		postigre = glm::vec3(0.0f, posYtig + movtig_y, posZtig + movtig_z);
		model = glm::translate(model, glm::vec3(-0.14f, -0.2f , -0.5f ));
		//model = glm::translate(model, glm::vec3(-0.14f , -0.2f + posyPDTig, -0.5f + posxPDTig));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, giroPDTig * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux5 = model;
		model = modelaux5;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		TPD.RenderModel();


		//PATA IZQUIERDA
		model = modelaux6;
		model = glm::translate(model, postigre);
		postigre = glm::vec3(0.0f, posYtig + movtig_y, posZtig + movtig_z);
		model = glm::translate(model, glm::vec3(0.16f, -0.2f, -0.5f));
		//model = glm::translate(model, glm::vec3(0.16f , -0.2f + posyPITig, -0.5f + posxPITig));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, giroPDTig * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux6 = model;
		model = modelaux6;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		TPI.RenderModel();



		//COLA
		model = modelaux7;
		model = glm::translate(model, postigre);
		postigre = glm::vec3(0.0f, posYtig + movtig_y, posZtig + movtig_z);
		//model = glm::translate(model, glm::vec3(0.0f , -0.0f + posyColTig, -1.1f + posxColTig));
		model = glm::translate(model, glm::vec3(0.0f, -0.0f , -1.1f ));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, giroColTig * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux7 = model;
		model = modelaux7;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		TCOLA.RenderModel();


		//Habitat tigre
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		habitattigre_Texture.UseTexture();
		habitattigre.RenderModel();

		//piedra1tigre
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, 0.0f, 13.0f));
		model = glm::scale(model, glm::vec3(4.5f, 4.5f, 4.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piedra4_pandaTexture.UseTexture();
		piedratigre.RenderModel();
	
		//Arbol1 Tigre
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, 0.0f, 190.0f));
		model = glm::scale(model, glm::vec3(2.0f, 5.0f, 2.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cementoTexture.UseTexture();
		arbol_panda.RenderModel();

		//Arbol1 Tigre2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, 0.0f, 140.0f));
		model = glm::scale(model, glm::vec3(2.0f, 3.0f, 2.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cementoTexture.UseTexture();
		arbol_panda.RenderModel();

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
		model = glm::scale(model, glm::vec3(1.25f, 1.0f, 1.0f));
		model = glm::rotate(model, 53 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//puente_panda1.UseTexture();
		//puente_panda2.UseTexture();
		//puente_panda3.UseTexture();
		puente_panda.RenderModel();

		//Maquina
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(200.0f, 0.0f, -180.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MaquinaEx.RenderModel();

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
		
	
		//CARRO
		if (entracarro) {
			movZcarro -= movCarroOffset * 15 * deltaTime;
			if (movZcarro <= -100) {
				entracarro = false;
				giraCarro = true;
			}
		}
		if (giraCarro) {
			anguloCarro += anguloCarroOffset * deltaTime;
			movZcarro -= movCarroOffset * 4 * deltaTime;
			movXcarro -= movCarroOffset * 5 * deltaTime;
			if (anguloCarro >= 90) {
				entracarro = false;
				giraCarro = false;
				avanzaCarro = true;
			}
		}

		if (avanzaCarro) {
			movXcarro -= movCarroOffset * 15 * deltaTime;
			if (movXcarro <= -50) {
				entracarro = false;
				giraCarro = false;
				avanzaCarro = false;
				regresaCarro = true;
			}

		}
		if (regresaCarro) {
			movXcarro += movCarroOffset * 15 * deltaTime;
			if (movXcarro >= -40) {
				entracarro = false;
				giraCarro = false;
				avanzaCarro = false;
				regresaCarro = false;
				retornaCarro = true;
			}
		}
		if (retornaCarro) {
			anguloCarro -= anguloCarroOffset * deltaTime;
			movXcarro += movCarroOffset * 4 * deltaTime;
			movZcarro += movCarroOffset * 5 * deltaTime;
			if (anguloCarro <= 0) {
				entracarro = false;
				giraCarro = false;
				avanzaCarro = false;
				regresaCarro = false;
				retornaCarro = false;
				saleCarro = true;
			}
		}
		if (saleCarro) {
			movZcarro += movCarroOffset * 15 * deltaTime;
			if (movZcarro >= 0) {
				entracarro = true;
				giraCarro = false;
				avanzaCarro = false;
				regresaCarro = false;
				retornaCarro = false;
				saleCarro = false;
			}
		}

		//Carro Simpson
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(190.0f, 5.0f, 245.0f));
		model = glm::translate(model, glm::vec3(movXcarro, movYcarro, movZcarro));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, anguloCarro * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		carro_simpson.RenderModel();
		

		//Reja enfrente panda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		rejaenfrente_panda.RenderModel();

		//Reja enfrente pinguino
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -79.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		rejaenfrente_panda.RenderModel();

		//Reja enfrente tigre
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 188.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		rejaenfrente_panda.RenderModel();

		//Duff1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.1f, 2.1f, 2.1f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		duffbeer1_Texture.UseTexture();
		duffbeer2_Texture.UseTexture();
		duffbeer.RenderModel();

		//Duff2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.1f, 2.1f, 2.1f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		duffbeer1_Texture.UseTexture();
		duffbeer2_Texture.UseTexture();
		duffbeer2.RenderModel();

		//Duff3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.1f, 2.1f, 2.1f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		duffbeer1_Texture.UseTexture();
		duffbeer2_Texture.UseTexture();
		duffbeer3.RenderModel();

		//TIGRE MIMIDO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-40.0f, 7.0f, 220.0f));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		model = glm::rotate(model, -50 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		TIGMIMIDO.RenderModel();

		//Reja trasera panda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 104.65f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		rejaenfrente_panda.RenderModel();

		//Reja trasera pinguino
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -184.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		rejaenfrente_panda.RenderModel();

		//Reja trasera tigre
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 292.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		rejaenfrente_panda.RenderModel();

		//Reja izquierda panda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		rejalateral_panda.RenderModel();

		//Reja izquierda pinguino
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -183.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		rejalateral_panda.RenderModel();

		//Reja izquierda tigre
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 189.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		rejalateral_panda.RenderModel();

		//Reja derecha panda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-120.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		rejalateral_panda.RenderModel();

		//Reja derecha pinguino
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-120.0f, 0.0f, -184.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		rejalateral_panda.RenderModel();

		//Reja derecha tigre
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-120.0f, 0.0f, 189.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		rejalateral_panda.RenderModel();

		//HOMERO
		//CUERPO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(220.0f, 0.0f, -180.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		HomeroCuerpo.RenderModel();
		//BRAZO DERECHO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(220.0f, 0.0f, -180.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		HomeroBraDer.RenderModel();
		//BRAZO IZQUIERDO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(220.0f, 0.0f, -180.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		HomeroBraIzq.RenderModel();
		//PIERNA DERECHA
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(220.0f, 0.0f, -180.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		HomeroPierDer.RenderModel();
		//PIERNA IZQUIERDA
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(220.0f, 0.0f, -180.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		HomeroPierIzq.RenderModel();


		//PIEDRAS
		//Piedras estanque panda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piedrasEst_pandaTexture.UseTexture();
		piedrasEst_tigre.RenderModel();
		//piedras estanque tigre
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-113.0f, 0.0f, -25.0f));//posicionamiento
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f)); //posicionamiento
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piedrasEst_pandaTexture.UseTexture();
		piedrasEst_tigre.RenderModel();


		//////////////////////////
		//////////// NUESTRAS ANIMACIONES
		////////
			
		///AVE
		model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-2.0 + movCoche * 0.5f, 30.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 30.5f + sin(glm::radians(rotllanta * 12.0)), -80.0 + movCoche * 5.5));
		if (avanza == false)
		{
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		aveTexture.UseTexture();
		CuerpoAve.RenderModel();

		model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 30.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 30.5f + sin(glm::radians(rotllanta * 12.08)), -80.0 + movCoche * 5.5));
		if (avanza == false)
		{
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		aveTexture.UseTexture();
		AlaDerF.RenderModel();

		model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 30.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 30.5f + sin(glm::radians(rotllanta * 12.06)), -80.0 + movCoche * 5.5));
		if (avanza == false)
		{
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		aveTexture.UseTexture();
		AlaDerP.RenderModel();

		model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 30.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 30.5f + sin(glm::radians(rotllanta * 12.08)), -80.0 + movCoche * 5.5));
		if (avanza == false)
		{
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		aveTexture.UseTexture();
		AlaIzqF.RenderModel();

		model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 30.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 30.5f + sin(glm::radians(rotllanta * 12.06)), -80.0 + movCoche * 5.5));
		if (avanza == false)
		{
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		aveTexture.UseTexture();
		AlaIzqP.RenderModel();
		
		//ESTATUA
		//MOVIMIENTO///////////////////////////////////////
		if (EST_AVA) {
			if (EST_AVA_Z >= 3.0f) {
				EST_AVA = false;
				EST_RET = true;
			}
			else {
				EST_AVA_Z += movESTOffset;
			}
		}
		else if (EST_RET) {
			if (EST_RET_Z <= -3.0f) {
				EST_RET = false;
				EST_AVA = false;
				EST_REGRESA_Z = true;
			}
			else {
				EST_RET_Z -= movESTOffset;
			}
		}
		else if (EST_REGRESA) {
			if (EST_REGRESA_Z <= 3.0f) {
				EST_REGRESA = false;
				EST_AVA = true;
				// Reiniciar las posiciones o valores necesarios para el reinicio del recorrido
				EST_AVA_Z = 0.0f;
				EST_REGRESA_Z = 0.0f;
				EST_REGRESA_Z = 0.0f;
			}
			else {
				EST_REGRESA_Z += movESTOffset;
			}
			anguloBM += anguloBMOffset; // Agregar rotación de arriba hacia anguloBM durante todo el ciclo
		}

		// Rotación constante entre los ángulos 
		if (rotateClockwise_EST) {
			anguloActual_EST += anguloRotacion_EST;
			if (anguloActual_EST >= anguloMaximo_EST) {
				anguloActual_EST = anguloMaximo_EST;
				rotateClockwise_EST = false;
			}
		}
		else {
			anguloActual_EST -= anguloRotacion_EST;
			if (anguloActual_EST <= anguloMinimo_EST) {
				anguloActual_EST = anguloMinimo_EST;
				rotateClockwise_EST = true;
			}
		}

		//ESTATUA CUERPO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-49.0f, 19.0f, -70.0f));
		model = glm::translate(model, glm::vec3(EST_AVA_Z + EST_RET_Z, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.5f, 5.5f, 5.5f));
		model = glm::rotate(model, 1 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, anguloActual * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		modelaux1 = model;
		modelaux2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		EST_CUER.RenderModel();

		//ESTATUA DERECHA
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.5f, -0.45f, -0.45f)); //SI SON + atrás, arriba, izquierda 
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); //VIENDO LOS HABITATS DESDE LATERAL
		model = glm::rotate(model, anguloActual * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux = model;
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		EST_DER.RenderModel();

		//ESTATUA IZQUIERDA
		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.4f, -0.4f, 0.55f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, anguloActual * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux2 = model;
		model = modelaux2;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		EST_IZQ.RenderModel();

		//BASE ESTATUA
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-47.0f, 7.0f, -70.0f));
		model = glm::scale(model, glm::vec3(5.5f, 5.5f, 5.5f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		EST_BASE.RenderModel();

		
		/////////////////////
		////LISA
		if (incrementando_LI) {
			angulobraDLI += anguloLISAOffset * 2 * deltaTime;
			angulobraILI -= anguloLISAOffset * 2 * deltaTime;
			if (angulobraDLI >= 50.0) {
				incrementando_LI = false;
			}
		}
		else {
			angulobraDLI -= anguloLISAOffset * 2 * deltaTime;
			angulobraILI += anguloLISAOffset * 2 * deltaTime;
			if (angulobraDLI <= 0.0) {
				incrementando_LI = true;
			}
		}

		if (incrementando2_LI) {
			angulopieDLI += anguloLISAOffset * 3 * deltaTime;
			angulopieILI -= anguloLISAOffset * 3 * deltaTime;
			if (angulopieDLI >= 20.0) {
				incrementando2_LI = false;
			}
		}
		else {
			angulopieDLI -= anguloLISAOffset * 3 * deltaTime;
			angulopieILI += anguloLISAOffset * 3 * deltaTime;
			if (angulopieDLI <= 0.0) {
				incrementando2_LI = true;
			}
		}

		if (incrementando3_LI) {
			angulocuerpoLI += anguloLISAOffset * deltaTime;
			if (angulocuerpoLI >= 5.0) {
				incrementando3_LI = false;
			}
		}
		else {
			angulocuerpoLI -= anguloLISAOffset * 3 * deltaTime;
			if (angulocuerpoLI <= 0.0) {
				incrementando3_LI = true;
			}
		}
		/////////////

		if (caminaizquierda_LI) {
			if (caminaizquierdaX_LI >= 115) {
				caminaizquierda_LI = false;
				caminaadelante_LI = true;
			}
			else {
				caminaizquierdaX_LI += movLISAOffset * 3 * deltaTime;
				anguloLI -= anguloLISAOffset * deltaTime;
			}
		}

		else if (caminaadelante_LI) {
			if (caminadelanteZ_LI >= 2.5) {
				caminaadelante_LI = false;
				caminaderecha_LI = true;
			}
			else {
				caminadelanteZ_LI += movLISAOffset * 3 * deltaTime;
				anguloLI -= anguloLISAOffset * deltaTime;
			}
		}

		else if (caminaderecha_LI) {
			if (caminaderechaX_LI <= -115) {
				caminaderecha_LI = false;
				caminaatras_LI = true;
			}
			else {
				caminaderechaX_LI -= movLISAOffset * 3 * deltaTime;
				anguloLI -= anguloLISAOffset * deltaTime;
			}
		}

		else if (caminaatras_LI) {
			if (caminaatrasZ_LI <= -2.5) {
				caminaatras_LI = false;
				regresa_LI = true;
			}
			else {
				caminaatrasZ_LI -= movMargeOffset * 3 * deltaTime;
				anguloLI -= anguloMargeOffset * deltaTime;
			}
		}

		else if (regresa_LI) {
			if (regresaX_LI >= -5) {
				regresa_LI = false;
				caminaizquierda_LI = true;
				// Reiniciar las posiciones o valores necesarios para el reinicio del recorrido
				caminaizquierdaX_LI = 0.0f;
				caminadelanteZ_LI = 0.0f;
				caminaderechaX_LI = 0.0f;
				caminaatrasZ_LI = 0.0f;
				regresaX_LI = 0.0f;
				anguloLI = 0.0f;
			}
			else {
				regresaX_LI += movLISAOffset * 3 * deltaTime;
			}
		}
		else {
			caminaizquierda_LI = true;
		}


		//CUERPO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 8.0f, 90.0f)); // Traslación en el eje X
		model = glm::translate(model, glm::vec3(caminaatrasX_LI + caminadelanteX_LI + caminaizquierdaX_LI + caminaderechaX_LI + regresaX_LI, 0.0f, caminaatrasZ_LI + caminadelanteZ_LI + caminaizquierdaZ_LI + caminaderechaZ_LI + regresaZ_LI));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, anguloLI * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, angulocuerpoLI * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux1 = model;
		modelaux2 = model;
		modelaux3 = model;
		modelaux4 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LisaCuerpo.RenderModel();

		// BRAZO DERECHO
		model = modelaux1;
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, -0.4f)); // Traslación en el eje X
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, angulobraDLI * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux1 = model;
		model = modelaux1;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LisaBraDer.RenderModel();

		//BRAZO IZQUIERDO
		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.3f)); // Traslación en el eje X
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, angulobraILI * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux2 = model;
		model = modelaux2;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LisaBraIzq.RenderModel();

		//PIERNA DERECHA
		model = modelaux3;
		model = glm::translate(model, glm::vec3(0.1f, -0.95f, -0.15f)); // Traslación en el eje X
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, angulopieDLI * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux3 = model;
		model = modelaux3;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LisaPierDer.RenderModel();

		//PIERNA IZQUIERDA
		model = modelaux4;
		model = glm::translate(model, glm::vec3(0.1f, -0.95f, 0.15f)); // Traslación en el eje X
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, angulopieILI * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux4 = model;
		model = modelaux4;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LisaPierIzq.RenderModel();

		//MARGE
		if (incrementando_MA) {
			angulobraDMA += anguloMargeOffset * 2 * deltaTime;
			angulobraIMA -= anguloMargeOffset * 2 * deltaTime;
			if (angulobraDMA >= 50.0) {
				incrementando_MA = false;
			}
		}
		else {
			angulobraDMA -= anguloMargeOffset * 2 * deltaTime;
			angulobraIMA += anguloMargeOffset * 2 * deltaTime;
			if (angulobraDMA <= 0.0) {
				incrementando_MA = true;
			}
		}

		if (incrementando2_MA) {
			angulopieDMA += anguloMargeOffset * 3 * deltaTime;
			angulopieIMA -= anguloMargeOffset * 3 * deltaTime;
			if (angulopieDMA >= 20.0) {
				incrementando2_MA = false;
			}
		}
		else {
			angulopieDMA -= anguloMargeOffset * 3 * deltaTime;
			angulopieIMA += anguloMargeOffset * 3 * deltaTime;
			if (angulopieDMA <= 0.0) {
				incrementando2_MA = true;
			}
		}

		if (incrementando3_MA) {
			angulocuerpoMA += anguloMargeOffset * deltaTime;
			if (angulocuerpoMA >= 5.0) {
				incrementando3_MA = false;
			}
		}
		else {
			angulocuerpoMA -= anguloMargeOffset * 3 * deltaTime;
			if (angulocuerpoMA <= 0.0) {
				incrementando3_MA = true;
			}
		}

		if (caminaizquierda_MA) {
			if (caminaizquierdaX_MA >= 150) {
				caminaizquierda_MA = false;
				caminaadelante_MA = true;
			}
			else {
				caminaizquierdaX_MA += movMargeOffset * 3 * deltaTime;
				anguloMA -= anguloMargeOffset * deltaTime;
			}
		}

		else if (caminaadelante_MA) {
			if (caminadelanteZ_MA >= 520) {
				caminaadelante_MA = false;
				caminaderecha_MA = true;
			}
			else {
				caminadelanteZ_MA += movMargeOffset * 3 * deltaTime;
				anguloMA -= anguloMargeOffset * deltaTime;
			}
		}

		else if (caminaderecha_MA) {
			if (caminaderechaX_MA <= -145) {
				caminaderecha_MA = false;
				caminaatras_MA = true;
			}
			else {
				caminaderechaX_MA -= movMargeOffset * 3 * deltaTime;
				anguloMA -= anguloMargeOffset * deltaTime;
			}
		}

		else if (caminaatras_MA) {
			if (caminaatrasZ_MA <= -520) {
				caminaatras_MA = false;
				regresa_MA = true;
			}
			else {
				caminaatrasZ_MA -= movMargeOffset * 3 * deltaTime;
				anguloMA -= anguloMargeOffset * deltaTime;
			}
		}

		else if (regresa_MA) {
			if (regresaX_MA >= -5) {
				regresa_MA = false;
				caminaizquierda_MA = true;
				// Reiniciar las posiciones o valores necesarios para el reinicio del recorrido
				caminaizquierdaX_MA = 0.0f;
				caminadelanteZ_MA = 0.0f;
				caminaderechaX_MA = 0.0f;
				caminaatrasZ_MA = 0.0f;
				regresaX_MA = 0.0f;
				anguloMA = 0.0f;
			}
			else {
				regresaX_MA += movMargeOffset * 3 * deltaTime;
			}
		}
		else {
			caminaizquierda_MA = true;
		}


		//MARGE
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-80.0f, 9.5f, -260.0f));
		model = glm::translate(model, glm::vec3(caminaatrasX_MA + caminadelanteX_MA + caminaizquierdaX_MA + caminaderechaX_MA + regresaX_MA, 0.0f, caminaatrasZ_MA + caminadelanteZ_MA + caminaizquierdaZ_MA + caminaderechaZ_MA + regresaZ_MA));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, anguloMA * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, angulocuerpoMA * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux1 = model;
		modelaux2 = model;
		modelaux3 = model;
		modelaux4 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Marge.RenderModel();

		//BRAZO IZQUIERDO
		model = modelaux1;
		model = glm::translate(model, glm::vec3(-0.01f, -0.41f, 0.15f)); //SI SON + atrás, arriba, izquierda 
		model = glm::rotate(model, angulobraIMA * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux1 = model;
		model = modelaux1;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazoIzqMarge.RenderModel();

		//BRAZO DERECHO
		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.1f, -0.41f, -0.15f));
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, angulobraDMA * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux2 = model;
		model = modelaux2;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazoDerMarge.RenderModel();

		//PIERNA DERECHA
		model = modelaux3;
		model = glm::translate(model, glm::vec3(0.03f, -0.9f, -0.08f));
		model = glm::rotate(model, angulopieIMA * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux3 = model;
		model = modelaux3;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piernaIzqMarge.RenderModel();

		//PIERNA IZQUIERDA
		model = modelaux4;
		model = glm::translate(model, glm::vec3(0.03f, -0.9f, 0.08f));
		model = glm::rotate(model, angulopieDMA * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux4 = model;
		model = modelaux4;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piernaDerMarge.RenderModel();

		//////

		if (sentarpanda) {
			anguloPandaPatas += pandaangOffset * deltaTime;
			anguloPandaTorso -= pandaangOffset * deltaTime * 0.3;
			movTorsoPandaY -= pandamovOffset * deltaTime * 0.001;
			anguloPandaCabeza -= pandaangOffset * deltaTime * 0.4;
			movCabezaPandaY -= pandamovOffset * deltaTime * 0.002;
			if (anguloPandaPatas >= 90) {
				sentarpanda = false;
				bolitapanda = true;
			}
		}
		if (bolitapanda) {
			anguloPandaPatas -= pandaangOffset * deltaTime * 5;
			if (anguloPandaPatas <= 20) {
				sentarpanda = false;
				bolitapanda = false;
				bolitapanda2 = true;
			}
		}
		if (bolitapanda2) {
			anguloPandaPatas -= pandaangOffset * deltaTime * 5;
			movCuerpoPandaY += pandamovOffset * deltaTime * .2;
			if (anguloPandaPatas <= -5) {
				sentarpanda = false;
				bolitapanda = false;
				bolitapanda2 = false;
				bolitapanda3 = true;
			}
		}
		if (bolitapanda3) {
			anguloPandaPatas -= pandaangOffset * deltaTime * 5;
			movCuerpoPandaY += pandamovOffset * deltaTime * .2;
			if (anguloPandaPatas <= -5) {
				sentarpanda = false;
				bolitapanda = false;
				bolitapanda2 = false;
				bolitapanda3 = false;
				bolitapanda4 = true;
			}
		}
		if (bolitapanda4) {
			anguloPandaPatas -= pandaangOffset * deltaTime * 5;
			movCuerpoPandaY += pandamovOffset * deltaTime * .2;
			if (anguloPandaPatas <= -20) {
				sentarpanda = false;
				bolitapanda = false;
				bolitapanda2 = false;
				bolitapanda3 = false;
				bolitapanda4 = false;
				bolitapanda5 = true;
			}
		}
		if (bolitapanda5) {
			anguloPandaPatas -= pandaangOffset * deltaTime * 5;
			movCuerpoPandaX += pandamovOffset * deltaTime * 0.05;
			movCuerpoPandaY += pandamovOffset * deltaTime * .4;
			movCuerpoPandaZ -= pandamovOffset * deltaTime * 0.05;
			if (anguloPandaPatas <= -40) {
				sentarpanda = false;
				bolitapanda = false;
				bolitapanda2 = false;
				bolitapanda3 = false;
				bolitapanda4 = false;
				bolitapanda5 = false;
				bolitapanda6 = true;
			}
		}
		if (bolitapanda6) {
			anguloPandaPatas -= pandaangOffset * deltaTime * 5;
			movCuerpoPandaY += pandamovOffset * deltaTime * .4;
			if (anguloPandaPatas <= -60) {
				sentarpanda = false;
				bolitapanda = false;
				bolitapanda2 = false;
				bolitapanda3 = false;
				bolitapanda4 = false;
				bolitapanda5 = false;
				bolitapanda6 = false;
				bolitapanda7 = true;
			}
		}
		if (bolitapanda7) {
			anguloPandaPatas -= pandaangOffset * deltaTime * 5;
			movCuerpoPandaY += pandamovOffset * deltaTime * .3;
			movCuerpoPandaX -= pandamovOffset * deltaTime * 0.09;
			movCuerpoPandaZ += pandamovOffset * deltaTime * 0.09;
			if (anguloPandaPatas <= -70) {
				sentarpanda = false;
				bolitapanda = false;
				bolitapanda2 = false;
				bolitapanda3 = false;
				bolitapanda4 = false;
				bolitapanda5 = false;
				bolitapanda6 = false;
				bolitapanda7 = false;
				bolitapanda8 = true;
			}
		}
		if (bolitapanda8) {
			anguloPandaPatas -= pandaangOffset * deltaTime * 10;
			movCuerpoPandaX -= pandamovOffset * deltaTime * .6;
			movCuerpoPandaY -= pandamovOffset * deltaTime * .6;
			movCuerpoPandaZ += pandamovOffset * deltaTime * .6;
			if (anguloPandaPatas <= -100) {
				sentarpanda = false;
				bolitapanda = false;
				bolitapanda2 = false;
				bolitapanda3 = false;
				bolitapanda4 = false;
				bolitapanda5 = false;
				bolitapanda6 = false;
				bolitapanda7 = false;
				bolitapanda8 = false;
				bolitapanda9 = true;
			}
		}
		if (bolitapanda9) {
			anguloPandaPatas -= pandaangOffset * deltaTime * 10;
			movCuerpoPandaX -= pandamovOffset * deltaTime * .6;
			movCuerpoPandaY -= pandamovOffset * deltaTime * .2;
			movCuerpoPandaZ += pandamovOffset * deltaTime * .6;
			if (anguloPandaPatas <= -150) {
				sentarpanda = false;
				bolitapanda = false;
				bolitapanda2 = false;
				bolitapanda3 = false;
				bolitapanda4 = false;
				bolitapanda5 = false;
				bolitapanda6 = false;
				bolitapanda7 = false;
				bolitapanda8 = false;
				bolitapanda9 = false;
				bolitapanda10 = true;
			}
		}
		if (bolitapanda10) {
			anguloPandaPatas -= pandaangOffset * deltaTime * 10;
			movCuerpoPandaY -= pandamovOffset * deltaTime;
			if (anguloPandaPatas <= -200) {
				sentarpanda = false;
				bolitapanda = false;
				bolitapanda2 = false;
				bolitapanda3 = false;
				bolitapanda4 = false;
				bolitapanda5 = false;
				bolitapanda6 = false;
				bolitapanda7 = false;
				bolitapanda8 = false;
				bolitapanda9 = false;
				bolitapanda10 = false;
				bolitapanda11 = true;
			}
		}
		if (bolitapanda11) {
			anguloPandaPatas -= pandaangOffset * deltaTime * 10;
			movCuerpoPandaY -= pandamovOffset * deltaTime;
			movCuerpoPandaX += pandamovOffset * deltaTime * 0.5;
			movCuerpoPandaZ -= pandamovOffset * deltaTime * 0.5;
			if (anguloPandaPatas <= -230) {
				sentarpanda = false;
				bolitapanda = false;
				bolitapanda2 = false;
				bolitapanda3 = false;
				bolitapanda4 = false;
				bolitapanda5 = false;
				bolitapanda6 = false;
				bolitapanda7 = false;
				bolitapanda8 = false;
				bolitapanda9 = false;
				bolitapanda10 = false;
				bolitapanda11 = false;
				bolitapanda12 = true;
			}
		}
		if (bolitapanda12) {
			anguloPandaPatas -= pandaangOffset * deltaTime * 10;
			movCuerpoPandaX += pandamovOffset * deltaTime * 0.8;
			movCuerpoPandaZ -= pandamovOffset * deltaTime * 0.8;
			if (anguloPandaPatas <= -280) {
				sentarpanda = false;
				bolitapanda = false;
				bolitapanda2 = false;
				bolitapanda3 = false;
				bolitapanda4 = false;
				bolitapanda5 = false;
				bolitapanda6 = false;
				bolitapanda7 = false;
				bolitapanda8 = false;
				bolitapanda9 = false;
				bolitapanda10 = false;
				bolitapanda11 = false;
				bolitapanda12 = false;
			}
		}
		//ESTE PANDA YA FUNCIONA. pero no se detiene
		model = glm::mat4(1.0);
		//condiciones iniciales
		model = glm::translate(model, glm::vec3(10.0f, 7.0f, 15.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, anguloPandaPatas * toRadians, glm::vec3(0.8f, 0.0f, 0.9f));//para que se siente
		model = glm::translate(model, glm::vec3(movPatasPandaX, movPatasPandaY, movPatasPandaZ));
		model = glm::translate(model, glm::vec3(movCuerpoPandaX, movCuerpoPandaY, movCuerpoPandaZ));
		//
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pandabuenoTexture.UseTexture();
		Panda_Patas2.RenderModel();

		model = modelaux;
		//aquí instrucciones de pivote
		model = glm::translate(model, glm::vec3(1.15f, 0.03f, -1.15f));
		model = glm::rotate(model, anguloPandaTorso * toRadians, glm::vec3(0.8f, 0.0f, 0.9f));//para que se siente
		model = glm::translate(model, glm::vec3(movTorsoPandaX, movTorsoPandaY, movTorsoPandaZ));
		modelaux = model;
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pandabuenoTexture.UseTexture();
		Panda_Torso2.RenderModel();

		model = modelaux;
		//pivote
		model = glm::translate(model, glm::vec3(0.65f, 0.45, -0.65f));
		model = glm::rotate(model, anguloPandaCabeza * toRadians, glm::vec3(0.8f, 0.0f, 0.9f));//para que se siente
		model = glm::translate(model, glm::vec3(movCabezaPandaX, movCabezaPandaY, movCabezaPandaZ));
		modelaux = model;
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pandabuenoTexture.UseTexture();
		Panda_Cabeza2.RenderModel();

		//muro enfrente
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		muro.UseTexture();
		muroenfrenteder.RenderModel();

		//muro enfrente izq
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 325.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		muro.UseTexture();
		muroenfrenteder.RenderModel();

		//muro der
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(282.0f, 0.0f, -70.0f));
		model = glm::scale(model, glm::vec3(7.5f, 5.0f, 5.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		muro.UseTexture();
		muroenfrenteder.RenderModel();

		//muro izq
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(282.0f, 0.0f, 485.0f));
		model = glm::scale(model, glm::vec3(7.5f, 5.0f, 5.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		muro.UseTexture();
		muroenfrenteder.RenderModel();

		//muro atras
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-354.0f, 0.0f, 408.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 12.3f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		muro.UseTexture();
		muroenfrenteder.RenderModel();


		//dona
		if (donaVoltea) {
			anguloDona -= anguloDonaOffset * 2;
			if (anguloDona <= -90) {
				donaVoltea = false;
				donaCae = true;
			}
		}
		if (donaCae) {
			movYdona -= movDonaOffset * 3;
			if (movYdona <= -7.0) {
				donaVoltea = false;
				donaCae = false;
				donaRueda = true;
			}
		}
		if (donaRueda) {
			anguloDona += anguloDonaOffset * 2;
			if (anguloDona >= 0) {
				donaVoltea = false;
				donaCae = false;
				donaRueda = false;
			}
		}
		//Dona
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, 9.0f, -74.0f));
		model = glm::translate(model, glm::vec3(movXdona, movYdona, movZdona));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, anguloDona * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, anguloDonaRueda * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(amarillo));
		dona_pandaTexture.UseTexture();
		dona_panda.RenderModel();

		
		///////////////
		//Estanque
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(azul));
		estanque_panda.RenderModel();

		
		/////PANDA PUENTE
		model = glm::mat4(1.0);
		pospanda = glm::vec3(posXpanda + movPanda_x, posYpanda + movPanda_y, posZpanda);
		//Este translate es para localizar el panda, pero no alterar que su animacion sera sobre X
		model = glm::translate(model, glm::vec3(9.0f, 11.0f, -40.0f));
		model = glm::translate(model, pospanda);
		model = glm::rotate(model, giroPanda2 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, angPatas * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		modelaux2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		PC.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.6f + posxPPD, 0.2f + posyPPD, 0.0f));
		model = glm::rotate(model, giroPanda * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		modelaux = model;
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		PB.RenderModel();

		model = modelaux2;
		model = glm::translate(model, glm::vec3(1.36f + posxPPT, -0.38f + posyPPT, 0.0f));
		model = glm::rotate(model, giroPanda * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux2 = model;
		model = modelaux2;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		PP.RenderModel();

		//faro1 panda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 5.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		faro1_Texture.UseTexture();
		faro1.RenderModel();

		//faro1 tigre
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 200.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		faro1_Texture.UseTexture();
		faro1.RenderModel();

		//faro1 pinguino
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, -287.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		faro1_Texture.UseTexture();
		faro1.RenderModel();

		//faro2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, -105.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		faro1_Texture.UseTexture();
		faro1.RenderModel();

		//faro3 panda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-110.0f, 0.0f, -105.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		faro1_Texture.UseTexture();
		faro1.RenderModel();

		//faro3 tigre
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-110.0f, 0.0f, 200.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		faro1_Texture.UseTexture();
		faro1.RenderModel();

		//faro3 pinguino
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-110.0f, 0.0f, -290.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		faro1_Texture.UseTexture();
		faro1.RenderModel();

		//puesto
		model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(160.0f, 0.0f, -70.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		puesto_Texture.UseTexture();
		puesto.RenderModel();

		//focos puesto
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(160.0f, 0.0f, -70.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		focosPuesto.RenderModel();
		
		//carro2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(150.0f, 2.0f, 80.0f));
		model = glm::scale(model, glm::vec3(4.0, 4.0, 6.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		carro2.RenderModel();

		//Agregar llantas con jerarquía y rotación propia 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(150.0f, 2.0f, 80.0f));
		model = glm::scale(model, glm::vec3(4.0, 4.0, 6.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Agregar llantas con jerarquía y rotación propia 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(150.0f, 2.0f, 80.0f));
		model = glm::scale(model, glm::vec3(4.0, 4.0, 6.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llantas_AM.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(150.0f, 5.0f, 160.0f));
		model = glm::scale(model, glm::vec3(.25, .25, .25));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		carroTexture.UseTexture();
		carro3.RenderModel();


		//Habitat pinguino
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		habitatpinguino_Texture.UseTexture();
		habitatpinguino.RenderModel();

		//iglu
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		iglu_Texture.UseTexture();
		iglu.RenderModel();

		//piedras pinguino
		/*model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(blanco));
		//piedrapinguino_Texture.UseTexture();
		habitatpinguino_Texture.UseTexture();
		piedrapinguino.RenderModel();

		//Habitat pinguino
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		habitatpinguino_Texture.UseTexture();
		habitatpinguino.RenderModel();*/

		//Estanque tigre
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(azul));
		estanquetigre.RenderModel();


		glDisable(GL_BLEND);
		glUseProgram(0);
		mainWindow.swapBuffers();
	}

	return 0;
}

void inputKeyframes(bool* keys)
{
	if (keys[GLFW_KEY_SPACE])
	{
		if (reproduciranimacion < 1)
		{
			if (play == false && (FrameIndex > 1))
			{
				resetElements();
				//First Interpolation				
				interpolation();
				play = true;
				playIndex = 0;
				i_curr_steps = 0;
				reproduciranimacion++;
				printf("\n presiona 0 para habilitar reproducir de nuevo la animación'\n");
				habilitaranimacion = 0;

			}
			else
			{
				play = false;
			}
		}
	}
	if (keys[GLFW_KEY_0])
	{
		if (habilitaranimacion < 1)
		{
			reproduciranimacion = 0;
		}
	}

	if (keys[GLFW_KEY_L])
	{
		if (guardoFrame < 1)
		{
			saveFrame();
			printf("movAvion_x es: %f\n", movPanda_x);
			//printf("movAvion_y es: %f\n", movAvion_y);
			printf(" \npresiona P para habilitar guardar otro frame'\n");
			guardoFrame++;
			reinicioFrame = 0;
		}
	}
	if (keys[GLFW_KEY_P])
	{
		if (reinicioFrame < 1)
		{
			guardoFrame = 0;
		}
	}


	if (keys[GLFW_KEY_1])
	{
		if (ciclo < 1)
		{
			//printf("movAvion_x es: %f\n", movAvion_x);
			movPanda_x += 1.0f;
			printf("\n movAvion_x es: %f\n", movPanda_x);
			ciclo++;
			ciclo2 = 0;
			printf("\n reinicia con 2\n");
		}

	}
	if (keys[GLFW_KEY_2])
	{
		if (ciclo2 < 1)
		{
			ciclo = 0;
		}
	}

}
