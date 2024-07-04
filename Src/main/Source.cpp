/* Hello Triangle - c�digo adaptado de https://learnopengl.com/#!Getting-started/Hello-Triangle
 *
 * Adaptado por Rossana Baptista Queiroz
 * para a disciplina de Processamento Gr�fico - Unisinos
 * Vers�o inicial: 7/4/2017
 * �ltima atualiza��o em 14/08/2023
 *
 */

#include <iostream>
#include <string>
#include <assert.h>

// STB IMAGE
#include <stb_image.h>

using namespace std;
// using namespace glm; //para n�o usar glm::

// Classe para manipula��o dos shaders
#include "Shader.h"

// Classe para manipula��o das sprites
#include "Sprite.h"

#include <vector>
#include <glm/glm.hpp>

// Prot�tipos das fun��es
GLuint loadTexture(string texturePath);

// Dimens�es da janela (pode ser alterado em tempo de execu��o)
const GLuint WIDTH = 800, HEIGHT = 600;

// Variaveis globais
Sprite spr;

struct SpriteInfo {
	GLuint textureID;
	glm::vec3 position;
	glm::vec3 size;
};

static void startSprite(Sprite& sprite, Shader& shader, SpriteInfo& info) {
	std::cout << "Logging value" << std::endl;
	sprite.setShader(&shader);
	sprite.inicializar(info.textureID, info.position, info.size);
}


// Fun��o MAIN
int main()
{

	// Inicializa��o da GLFW
	glfwInit();

	// Inicializa��o da semente para gera��o de nros aleat�rios
	srand((int)glfwGetTime());

	// Muita aten��o aqui: alguns ambientes n�o aceitam essas configura��es
	// Voc� deve adaptar para a vers�o do OpenGL suportada por sua placa
	// Sugest�o: comente essas linhas de c�digo para desobrir a vers�o e
	// depois atualize (por exemplo: 4.5 com 4 e 5)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Essencial para computadores da Apple
	// #ifdef __APPLE__
	//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// #endif
	
	// Cria��o da janela GLFW
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Ocean view", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// GLAD: carrega todos os ponteiros d fun��es da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
	}

	// Obtendo as informa��es de vers�o
	const GLubyte *renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte *version = glGetString(GL_VERSION);		/* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	// Habilitar teste de profundidade
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS); // a cada ciclo

	// Habilitar o modo de transpar�ncia (blend - mistura de cores)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Compilando e buildando o programa de shader
	// Shader shader("../shaders/helloTriangle.vs", "../shaders/helloTriangle.fs");
	Shader shader("C:\\Users\\eduar\\source\\repos\\m4\\graphic-proccess-sprites\\Src\\shaders\\tex.vs", "C:\\Users\\eduar\\source\\repos\\m4\\graphic-proccess-sprites\\Src\\shaders\\tex.fs");

	// Ocean background
	GLuint texID1 = loadTexture("C:\\Users\\eduar\\source\\repos\\m4\\graphic-proccess-sprites\\Assets\\ocean-backgrounds\\Ocean_4\\1.png");
	GLuint texID2 = loadTexture("C:\\Users\\eduar\\source\\repos\\m4\\graphic-proccess-sprites\\Assets\\ocean-backgrounds\\Ocean_4\\2.png");
	GLuint texID3 = loadTexture("C:\\Users\\eduar\\source\\repos\\m4\\graphic-proccess-sprites\\Assets\\ocean-backgrounds\\Ocean_4\\3.png");
	GLuint texID4 = loadTexture("C:\\Users\\eduar\\source\\repos\\m4\\graphic-proccess-sprites\\Assets\\ocean-backgrounds\\Ocean_4\\4.png");

	// Nature elements
	GLuint texID5 = loadTexture("C:\\Users\\eduar\\source\\repos\\m4\\graphic-proccess-sprites\\Assets\\nature-objects\\PNG\\Bushes3\\Bush3_3.png");
	GLuint texID6 = loadTexture("C:\\Users\\eduar\\source\\repos\\m4\\graphic-proccess-sprites\\Assets\\rocks-objects\\PNG\\Objects_separately\\Rock5_1.png");
	GLuint texID7 = loadTexture("C:\\Users\\eduar\\source\\repos\\m4\\graphic-proccess-sprites\\Assets\\seabed-objects\\PNG\\Objects_separately\\Ship2_shadow1.png");
	GLuint texID8 = loadTexture("C:\\Users\\eduar\\source\\repos\\m4\\graphic-proccess-sprites\\Assets\\seabed-objects\\PNG\\Objects_separately\\Anchor_shadow1.png");
	GLuint texID9 = loadTexture("C:\\Users\\eduar\\source\\repos\\m4\\graphic-proccess-sprites\\Assets\\seabed-objects\\PNG\\Objects_separately\\Sea_urchin2_shadow1.png");
	GLuint texID10 = loadTexture("C:\\Users\\eduar\\source\\repos\\m4\\graphic-proccess-sprites\\Assets\\seabed-objects\\PNG\\Objects_separately\\Starfish2_shadow1.png");
	GLuint texID11 = loadTexture("C:\\Users\\eduar\\source\\repos\\m4\\graphic-proccess-sprites\\Assets\\seabed-objects\\PNG\\Objects_separately\\Beige-violet_coral2_shadow2.png");
	GLuint texID12 = loadTexture("C:\\Users\\eduar\\source\\repos\\m4\\graphic-proccess-sprites\\Assets\\seabed-objects\\PNG\\Objects_separately\\Monster_fish_bones_shadow1.png");
	GLuint texID13 = loadTexture("C:\\Users\\eduar\\source\\repos\\m4\\graphic-proccess-sprites\\Assets\\rocks-objects\\PNG\\Objects_separately\\Rock5_3.png");
	GLuint texID14 = loadTexture("C:\\Users\\eduar\\source\\repos\\m4\\graphic-proccess-sprites\\Assets\\seabed-objects\\PNG\\Objects_separately\\Crab_shadow1.png");
	GLuint texID15 = loadTexture("C:\\Users\\eduar\\source\\repos\\m4\\graphic-proccess-sprites\\Assets\\seabed-objects\\PNG\\Objects_separately\\Brown-white_shell1_shadow1.png");

	// Cria��o de uma sprite
	spr.setShader(&shader);

	std::vector<SpriteInfo> spriteInfos = {
		{ texID1, glm::vec3(400.0, 300.0, 0.0), glm::vec3(1920.0 / 2.0, 1080.0 / 2.0, 1.0) },
		{ texID2, glm::vec3(400.0, 300.0, 0.0), glm::vec3(1920.0 / 2.0, 1080.0 / 2.0, 1.0) },
		{ texID3, glm::vec3(400.0, 300.0, 0.0), glm::vec3(1920.0 / 2.0, 1080.0 / 2.0, 1.0) },
		{ texID4, glm::vec3(400.0, 300.0, 0.0), glm::vec3(1920.0 / 2.0, 1080.0 / 2.0, 1.0) },
		{ texID5, glm::vec3(740.0, 64.0, 0.0), glm::vec3(960.0 / 10.0, 540.0 / 8.0, 1.0) },
		{ texID6, glm::vec3(440.0, 60.0, 0.0), glm::vec3(54.0 / 1.0, 54.0 / 1.0, 1.0) },
		{ texID7, glm::vec3(120, 60.0, 0.0), glm::vec3(1920.0 / 8.0, 1080.0 / 8.0, 1.0) },
		{ texID8, glm::vec3(425, 60.0, 0.0), glm::vec3(54.0 / 1.0, 54.0 / 1.0, 1.0) },
		{ texID9, glm::vec3(440, 40.0, 0.0), glm::vec3(54.0 / 2.0, 54.0 / 2.0, 1.0) },
		{ texID10, glm::vec3(560, 40.0, 0.0), glm::vec3(54.0 / 2.0, 54.0 / 2.0, 1.0) },
		{ texID11, glm::vec3(300.0, 60.0, 0.0), glm::vec3(1920.0 / 40.0, 1080.0 / 24.0, 1.0) },
		{ texID12, glm::vec3(200.0, 42.0, 0.0), glm::vec3(1920.0 / 40.0, 1080.0 / 24.0, 1.0) },
		{ texID13, glm::vec3(116.0, 48.0, 0.0), glm::vec3(480.0 / 20.0, 270.0 / 10.0, 1.0) },
		{ texID14, glm::vec3(640.0, 48.0, 0.0), glm::vec3(1920.0 / 40.0, 1080.0 / 24.0, 1.0) },
		{ texID15, glm::vec3(380.0, 42.0, 0.0), glm::vec3(1920.0 / 40.0, 1080.0 / 24.0, 1.0) }
	};

	// Vetor que armazena os sprites
	std::vector<Sprite> sprites(spriteInfos.size());

	// Inicializando os sprites
	for (size_t i = 0; i < sprites.size(); ++i) {
		startSprite(sprites[i], shader, spriteInfos[i]);
	}

	// Ativando o buffer de textura 0 da opengl
	glActiveTexture(GL_TEXTURE0);

	shader.Use();

	// Matriz de proje��o paralela ortogr�fica
	glm::mat4 projection = glm::ortho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	// Enviando para o shader a matriz como uma var uniform
	shader.setMat4("projection", glm::value_ptr(projection));

	// Matriz de transforma��o do objeto (matriz de modelo)
	shader.setInt("texBuffer", 0);

	// Loop da aplica��o - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as fun��es de callback correspondentes
		glfwPollEvents();

		// Definindo as dimens�es da viewport com as mesmas dimens�es da janela da aplica��o
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height); // unidades de tela: pixel

		// Limpa o buffer de cor
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f); // cor de fundo
		glClear(GL_COLOR_BUFFER_BIT);

		for (Sprite& sprite : sprites) {
			sprite.desenhar();
		}

		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}

	// Finaliza a execu��o da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

GLuint loadTexture(string texturePath)
{
	GLuint texID;

	// Gera o identificador da textura na mem�ria
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	// Configura��o do par�metro WRAPPING nas coords s e t
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Confiruga��o do par�metro FILTERING na minifica��o e magnifica��o da textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3) // jpg, bmp
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else // png
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
}
