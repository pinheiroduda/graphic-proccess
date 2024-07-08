#include "Sprite.h"
#include <glm/gtx/string_cast.hpp>


Sprite::~Sprite()
{
	// Pede pra OpenGL desalocar os buffers
	glDeleteVertexArrays(1, &VAO);
}

void Sprite::inicializar(GLuint texID, int nAnimations, int nFrames, glm::vec3 pos, glm::vec3 escala, float angulo, glm::vec3 cor)
{
	this->texID = texID;
	this->pos = pos;
	//this->escala = escala;
	this->angulo = angulo;
	this->nFrames = nFrames;
	this->nAnimations = nAnimations;
	//this->iFrame = 0;
	//this->iAnimation = 0;
	//this->pastTime;
	this->escala.x = escala.x / (float)nFrames;
	this->escala.y = escala.y / (float)nAnimations;

	FPS = 12.0;
	pastTime = 0.0;
	frameDuration = 1.0f / FPS;

	offsetTex.s = 1.0 / (float)nFrames;
	offsetTex.t = 1.0 / (float)nAnimations;

	//Especificação da geometria da sprite (quadrado, 2 triangulos)
	GLfloat vertices[] = {
		//x   y    z    r      g      b      s    t
		-0.5, 0.5, 0.0, cor.r, cor.g, cor.b, 0.0, offsetTex.t, //v0
		-0.5,-0.5, 0.0, cor.r, cor.g, cor.b, 0.0, 0.0, //v1
		 0.5, 0.5, 0.0, cor.r, cor.g, cor.b, offsetTex.s, offsetTex.t, //v2
		-0.5,-0.5, 0.0, cor.r, cor.g, cor.b, 0.0, 0.0, //v1
		 0.5,-0.5, 0.0, cor.r, cor.g, cor.b, offsetTex.s, 0.0, //v3
		 0.5, 0.5, 0.0, cor.r, cor.g, cor.b, offsetTex.s, offsetTex.t  //v2
	};

	GLuint VBO;
	//Geração do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conexão (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//                                              vertices.data()  
	//Geração do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localização no shader * (a localização dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se está normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 

	//Atributo 0 - posição
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Atributo 1 - cor
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Atributo 2 - coordenadas de textura
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice 
	// atualmente vinculado - para que depois possamos desvincular com segurança
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);

}

void Sprite::desenhar()
{
	atualizar();

	glBindTexture(GL_TEXTURE_2D, texID);
	glBindVertexArray(VAO); //Conectando ao buffer de geometria
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindTexture(GL_TEXTURE_2D, 0); //unbind
	glBindVertexArray(0); //unbind
}


void Sprite::moverParaDireita()
{
	if (escala.x < 0.0)
		escala.x = -escala.x;
}

void Sprite::moverParaEsquerda()
{
	if (escala.x > 0.0)
		escala.x = -escala.x;
}

void Sprite::atualizar()
{
	float now = (float) glfwGetTime();

	float dt = now - pastTime;

	if (dt >= frameDuration) {
		int prevFrame = iFrame;
		iFrame = (iFrame + 1) % nFrames;

		pastTime = now;
	}

	float offsetTexFrameS = iFrame * offsetTex.s;
	float offsetTexFrameT = iAnimation * offsetTex.t;
	shader->setVec2("offsetTex", offsetTexFrameS, offsetTexFrameT);

	glm::mat4 model = glm::mat4(1); //matriz identidade
	model = glm::translate(model, pos);
	model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0, 0.0, 1.0));
	model = glm::scale(model, escala);
	shader->setMat4("model", glm::value_ptr(model));

}