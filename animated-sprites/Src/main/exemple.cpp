class Sprite {
protected:
    // Textura e buffer
    GLuint texID;  // Identificador da textura
    GLuint VAO;    // Identificador do buffer de geometria VAO
    Shader* shader;
    // Geometria
    glm::vec3 position, scale;
    float angle;
    // Animacao
    int nAnimations, nFrames, iAnimation, iFrame;
    glm::vec2 offsetTex;
    float lastTime;
    float FPS;

public:
    Sprite() {};
    Sprite(GLuint texID, int nAnimations, int nFrames, glm::vec3 position, glm::vec3 scale, float angle, glm::vec3 color) {
        this->texID = texID;
        this->nAnimations = nAnimations;
        this->position = position;
        this->nFrames = nFrames;
        this->scale.x = scale.x / (float)nFrames;
        this->scale.y = scale.y / (float)nAnimations;
        this->angle = angle;
        // Divide 1 pelo número de frames e animacoes para trabalhar com spritesheets
        offsetTex.s = 1.0 / (float)nFrames;
        offsetTex.t = 1.0 / (float)nAnimations;
        // define quantidade de FPS e inicializa o tempo
        FPS = 12.0;
        lastTime = 0.0;

        // Geeometria para quadrado com dois triangulos
        GLfloat vertices[] = {
            // x   y    z    r      g      b      s    t
            -0.5, 0.5,  0.0, color.r, color.g, color.b, 0.0,         offsetTex.t,  // v0
            -0.5, -0.5, 0.0, color.r, color.g, color.b, 0.0,         0.0,          // v1
            0.5,  0.5,  0.0, color.r, color.g, color.b, offsetTex.s, offsetTex.t,  // v2
            -0.5, -0.5, 0.0, color.r, color.g, color.b, 0.0,         0.0,          // v1
            0.5,  -0.5, 0.0, color.r, color.g, color.b, offsetTex.s, 0.0,          // v3
            0.5,  0.5,  0.0, color.r, color.g, color.b, offsetTex.s, offsetTex.t   // v2
        };
        GLuint VBO;

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }
    ~Sprite() {
        // Desaloca os buffers
        glDeleteVertexArrays(1, &VAO);
    }

    // Getters e setters para sprite
    glm::vec3 getPosition() const { return position; }
    void setPosition(const glm::vec3& newPos) { this->position = newPos; }
    void setShader(Shader* shader) { this->shader = shader; }
    void setAngulo(float angle) { this->angle = angle; }

    // Atualiza a animacao
    void update() {
        float now = glfwGetTime();

        float dt = now - lastTime;

        if (dt >= 1 / FPS) {
            int prevFrame = iFrame;
            iFrame = (iFrame + 1) % nFrames;

            // Alterna entre linhas do spritesheet (se houver, como na Flame)
            if (prevFrame > iFrame) {
                iAnimation = (iAnimation + 1) % nAnimations;
            }

            // Incrementa indice do Frame conforme ciclos
            lastTime = now;
        }

        // Calcula deslocamentos nas coordenadas da textura
        float offsetTexFrameS = iFrame * offsetTex.s;
        float offsetTexFrameT = iAnimation * offsetTex.t;
        shader->setVec2("offsetTex", offsetTexFrameS, offsetTexFrameT);

        glm::mat4 model = glm::mat4(1);
        model = glm::translate(model, position);
        // Efeito de espelho se sprite caminha em lado oposto ao anterior
        if (this->angle == 180.0f) {
            model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
        }
        else {
            model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0, 0.0, 1.0));
        }
        model = glm::scale(model, scale);
        shader->setMat4("model", glm::value_ptr(model));
    }

    // Desenha a textura
    void draw() {
        update();

        glBindTexture(GL_TEXTURE_2D, texID);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
};