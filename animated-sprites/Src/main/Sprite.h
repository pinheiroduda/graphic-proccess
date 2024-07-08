#pragma once

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

class Sprite
{
public:
	Sprite() {}
	~Sprite();
	void inicializar(GLuint texID, int nAnimations = 1, int nFrames = 1, glm::vec3 pos = glm::vec3(0), glm::vec3 escala = glm::vec3(1), float angulo = 0.0, glm::vec3 cor = glm::vec3(1.0, 1.0, 0.0));
	void desenhar();
	void finalizar();
	void moverParaDireita();
	void moverParaEsquerda();

	inline void setShader(Shader* shader) { this->shader = shader; }
	//glm::vec3 getPosition() const { return pos; }
	//inline void setPosition(const glm::vec3& newPos) { this->pos = newPos; }
	inline void setAngulo(float angulo) { this->angulo = angulo; }
protected:
	void atualizar();
	GLuint VAO; //identificador do buffer de geometria, indicando os atributos dos v�rtices
	GLuint texID; //identificador do buffer de textura

	//Vari�veis com as infos para aplicar as transforma��es no objeto
	glm::vec3 pos, escala;
	float angulo;

	//Uma refer�ncia ao programa de shader que a sprite ir� usar para seu desenho
	Shader* shader;

	float pastTime, FPS, frameDuration;

	glm::vec2 offsetTex; // Deslocamento de textura para a anima��o de frames
	int nFrames, nAnimations, iFrame, iAnimation;
};


