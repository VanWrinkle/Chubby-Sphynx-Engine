/**
 * EXAM 2022
 */

// SphynxEngine / project headers
#include <TestApplication.h>
#include <GeometricTools.h>
#include "gamegrid.h"
#include <SphynxRendering.h>
#include <SphynxCore.h>
#include <sphynxmath.h>
#include <gui_core.h>

// STD
#include <memory>
#include <random>

class AxisIndicator {
private:
    inline static Shader *m_shader = nullptr;
    inline static unsigned m_vertexArray = 0;

private:
    AxisIndicator() = default;
    static void SetupVertexArray () {
        glGenVertexArrays(1, &m_vertexArray);
        if (m_vertexArray == 0) {
            throw std::runtime_error(
                    "No vertexArray generated when attempting to draw Axis Indicator"
            );
        }
        glBindVertexArray(m_vertexArray);

        std::array<float, 6 * 6> AxisIndicatorLineTopology = {
                0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,
        };
        unsigned vertexBufferID = 0;
        glGenBuffers(1, &vertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
        if (m_vertexArray == 0) {
            throw std::runtime_error(
                    "No vertex buffer generated when attempting to draw Axis Indicator"
            );
        }
        glBufferData(
                GL_ARRAY_BUFFER,
                AxisIndicatorLineTopology.size()*4,
                AxisIndicatorLineTopology.data(),
                GL_DYNAMIC_DRAW
        );
        bool normalized = false;
        glVertexAttribPointer(0, 3, GL_FLOAT, normalized, 6*sizeof(float), nullptr);
        glVertexAttribPointer(1, 3, GL_FLOAT, normalized, 6*sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    }

    static void SetupShaderProgram () {

        std::string vertexShaderSource =
                "#version 460 core\n"
                "layout (location = 0) in vec3 aPos;\n"
                "layout (location = 1) in vec3 color;\n"
                "out vec4 vertexColor;\n"
                "uniform mat4 u_projection;\n"
                "uniform mat4 u_modelMatrix;\n"
                "uniform mat4 u_view;\n"
                "void main()\n"
                "{\n"
                "    gl_Position = u_projection * u_view * u_modelMatrix * vec4(aPos, 1.0);\n"
                "    vertexColor = vec4(color, 1.0);\n"
                "}";

        std::string fragmentShaderSource =
                "#version 460 core\n"
                "out vec4 FragColor;\n"
                "in vec4 vertexColor;\n"
                "\n"
                "void main()\n"
                "{\n"
                "    FragColor = vertexColor;\n"
                "} ";

        m_shader = new Shader(vertexShaderSource, fragmentShaderSource);
    }


public:
    static void Draw(ModelMatrix matrix, Camera &camera) {
        if (m_shader == nullptr) {
            AxisIndicator::SetupShaderProgram();
        }
        if (m_vertexArray == 0) {
            AxisIndicator::SetupVertexArray();
        }
        glBindVertexArray(m_vertexArray);
        //glUseProgram(m_shaderProgram);
        m_shader->use();
        m_shader->uploadUniformMat4("u_modelMatrix", matrix.getMatrix());
        m_shader->uploadUniformMat4("u_projection", camera.getProjectionMatrix());
        m_shader->uploadUniformMat4("u_view", camera.getViewMatrix());
        glDrawArrays(GL_LINES, 0, 6);
    }
};




const int gridY = 10;
const int gridX = 5;
const BufferLayout standardLayout{{shaderDataType::Float3, "position"},    {shaderDataType::Float3, "color"},
                                  {shaderDataType::Float2, "texturecoord"},{shaderDataType::Float3, "normal"},
                                  {shaderDataType::Float3, "tangent"}, {shaderDataType::Float3, "bitangent"}};

const std::vector<glm::vec3> colors {
        {1.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 0.0f},
        {1.0f, 0.0f, 1.0f},
        {1.0f, 1.0f, 0.0f},
        {0.5f, 1.0f, 1.0f},
        {1.0f, 1.0f, 0.5f},
        {1.0f, 0.5f, 1.0f},
        {0.5f, 0.5f, 1.0f},
        {0.5f, 1.0f, 0.5f},
        {1.0f, 0.5f, 0.5f}
};

/**
 * Constructor
 * @param name
 * @param version
 */
TestApplication::TestApplication(const std::string& name, const std::string& version)
    : Sphynx::Application(name, version){}

/**
 * MAIN PROGRAM
 */
int TestApplication::run() {
    {
        /**
         * SETTING UP KEYBINDS AND BEHAVIOUR
         */
        const auto guiOpenGLVersion = std::string("#version 130");
        sphynx::guiCreateContext(m_window, guiOpenGLVersion);


        Sphynx::Keyboard::setKeyBehaviour(Sphynx::Key::Space, Sphynx::KeyMode::CONTINUOUS);
        glfwSetKeyCallback(m_window, Sphynx::Keyboard::callback);
        Sphynx::KeyCode left = Sphynx::KeyCode::A;
        Sphynx::KeyCode right = Sphynx::KeyCode::D;
        Sphynx::KeyCode zoomIn = Sphynx::KeyCode::W;
        Sphynx::KeyCode zoomOut = Sphynx::KeyCode::S;
        Sphynx::KeyCode up = Sphynx::KeyCode::C;
        Sphynx::KeyCode forwards = Sphynx::KeyCode::X;
        Sphynx::KeyCode forwardsFast = Sphynx::KeyCode::Space;
        Sphynx::KeyCode down = Sphynx::KeyCode::LeftShift;
        Sphynx::KeyCode exit = Sphynx::KeyCode::Escape;
        Sphynx::KeyCode wireframeToggle = Sphynx::KeyCode::T;

        Sphynx::Mouse mouse(m_window);

        Sphynx::Keyboard::setKeyBehaviour(forwardsFast, Sphynx::KeyMode::CONTINUOUS);
        Sphynx::Keyboard::setKeyBehaviour(down, Sphynx::KeyMode::CONTINUOUS);
        Sphynx::Keyboard::setKeyBehaviour(zoomIn, Sphynx::KeyMode::CONTINUOUS);
        Sphynx::Keyboard::setKeyBehaviour(zoomOut, Sphynx::KeyMode::CONTINUOUS);
        Sphynx::Keyboard::setKeyBehaviour(left, Sphynx::KeyMode::CONTINUOUS);
        Sphynx::Keyboard::setKeyBehaviour(right, Sphynx::KeyMode::CONTINUOUS);

        /**
         * SHADER COMPILATION
         */

        Shader borderShader(SHADERS_DIR, "bordervertex.glsl", SHADERS_DIR, "borderfragment.glsl");
        Shader generalShader(SHADERS_DIR, "vertex.glsl", SHADERS_DIR, "fragment.glsl");
        generalShader.use();

        /**
         * CAMERA SETUP
         */

        int windowWidth;
        int windowHeight;
        glfwGetWindowSize(m_window, &windowWidth, &windowHeight);

        PerspectiveCamera::Frustum frustum{};
        frustum.angle = 70.0f;
        frustum.far = 100.0f;
        frustum.near = 0.01f;
        frustum.height = windowHeight;
        frustum.width = windowWidth;
        float cameraDistance = 70.0f;
        float cameraHeight = 20.0f;
        float maxDistance = 85.0f;
        float minDistance = 2.0f;
        float zoomRate = 30.0f;
        float rotation = 0.0f;
        float rotationRate = 2.0f;


        sem::vec3 cameraPosition(0.0f, 0.0f, -5);
        PerspectiveCamera camera(frustum, cameraPosition);


        generalShader.uploadUniformVec3("u_viewPos", camera.getPosition());
        generalShader.uploadUniformMat4("u_view", camera.getViewMatrix());
        generalShader.uploadUniformMat4("u_projection", camera.getProjectionMatrix());

        borderShader.use();
        borderShader.uploadUniformMat4("u_view", camera.getViewMatrix());
        borderShader.uploadUniformMat4("u_projection", camera.getProjectionMatrix());

        generalShader.use();


        /**
         * SETUP OF TEXTURES / MODELS
         */
        auto textureManager = TextureManager::GetInstance();
        ModelManager modelManager;

        // Different index buffers for line and triangle drawing
        auto wallLinesEBO = std::make_shared<IndexBuffer>(
                GeoTools::UnitGridLineIndices<gridX, gridY>().data(),
                sizeof(GeoTools::UnitGridLineIndices<gridX, gridY>()) / 4);

        auto wallTrianglesEBO = std::make_shared<IndexBuffer>(
                GeoTools::UnitGridIndices<gridX, gridY>().data(),
                sizeof(GeoTools::UnitGridIndices<gridX, gridY>()) / 4);

        auto boxLinesEBO = std::make_shared<IndexBuffer>(
                GeoTools::UnitCubeLineTopology.data(),
                sizeof(GeoTools::UnitCubeLineTopology)/4);

        auto boxTrianglesEBO = std::make_shared<IndexBuffer>(
                GeoTools::UnitCubeTopology.data(),
                sizeof(GeoTools::UnitCubeTopology)/4);

        // Model names
        std::string leftWall = "leftWall";
        std::string rightWall = "rightWall";
        std::string roof = "roof";
        std::string floor = "floor";
        std::string endWall = "endWall";
        std::string box = "box";

        // WALLS
        modelManager.addModel(floor, {GeoTools::UnitGrid3DVerticesNorm<gridX, gridY>(),
                                      GeoTools::UnitGridIndices<gridX, gridY>(),
                                      standardLayout} );

        float tunnelWidth = gridX;
        float tunnelLength = gridY;
        float tunnelHalf = tunnelWidth / 2.0f;


        modelManager[floor].materials[0] = {"box.png",{0.5,0.6,0.7},
                                            "box_specular.png", {1.0f, 1.0f, 1.0f},"boxnormal.png", 64.0f};
        modelManager[floor].setScale({tunnelWidth, 1.0f, tunnelLength});
        modelManager.addModel(leftWall, modelManager[floor]);
        modelManager.addModel(rightWall, modelManager[floor]);
        modelManager.addModel(roof, modelManager[floor]);
        modelManager[floor].setPosition({0.0f, -tunnelHalf, 0.0f});
        modelManager[leftWall].setRotation(-90.0f, {0.0f, 0.0f, 1.0f});
        modelManager[leftWall].setPosition({-tunnelHalf, 0.0f, 0.0f});
        modelManager[rightWall].setRotation(90.0f, {0.0f, 0.0f, 1.0f});
        modelManager[rightWall].setPosition({tunnelHalf, 0.0f, 0.0f});
        modelManager[roof].setRotation(180.0f, {0.0f, 0.0f, 1.0f});
        modelManager[roof].setPosition({0.0f, tunnelHalf, 0.0f});

        modelManager.addModel(endWall, {GeoTools::UnitGrid3DVerticesNorm<gridX, gridX>(),
                                        GeoTools::UnitGridIndices<gridX, gridX>(),
                                        standardLayout} );
        modelManager[endWall].materials[0] = {"box.png",          {0.5,0.6,0.7},
                                              "box_specular.png", {1.0f, 1.0f, 1.0f},"boxnormal.png", 128.0f};
        modelManager[endWall].setScale({tunnelWidth, 1.0f, tunnelWidth});
        modelManager[endWall].setPosition({0.0f, 0.0f, tunnelLength/2});
        modelManager[endWall].setRotation(-90.0f, {1.0f, 0.0f, 0.0f});
        modelManager.addModel(box, {GeoTools::UnitCubeVerticesNorm,
                                    GeoTools::UnitCubeTopology,
                                    standardLayout});
        // Unit cube


        modelManager[box].materials[0] = {"ironpatterndiffuse.png",          {1.0f, 1.0f, 1.0f},
                                          "ironpatternspecular.png", {1.0f, 1.0f, 1.0f}, "ironpatternnormal.png", 128.0f};
        // Prop pickaxe
        modelManager.loadModelsFromObjWNormals(OBJECTS_DIR, "untitled.obj");
        modelManager["pickaxe"].setScale(glm::vec3(.3));
        modelManager["pickaxe"].setRotation(45.0f, {0.0f, 1.0f, 0.0f});

        modelManager["Cube"].setPosition({3.0f, 0.0f, 3.0f});


        // Upload of textures
        for(auto & model : modelManager) {
            textureManager->LoadModelTextures(model.second, TEXTURES_DIR);
        }


        /**
         * SETTING UP LIGHTING
         */
        generalShader.uploadUniformVec3("u_ambientLighting", glm::vec3(0.5, 0.5, 0.5));

        LightsManager lightsManager("u_lights");


        std::string light1 = "light1";
        std::string light2 = "light2";
        std::string activeLight = "activeLight";


        lightsManager.addLight(light1, PointLight());
        lightsManager[light1].isActive = true;
        lightsManager[light1].diffuse = glm::vec3(.5f, 0.8f, 0.8f);
        lightsManager[light1].specular = glm::vec3(.5f, 0.8f, 0.8f);

        lightsManager.addLight(light2, PointLight());
        lightsManager[light2].isActive = true;
        lightsManager[light2].diffuse = {1.f, 0.5, 0.5};
        lightsManager[light2].specular = {1.f, 0.5, 0.5};

        lightsManager.addLight(activeLight, PointLight());
        lightsManager[activeLight].isActive = true;
        lightsManager[activeLight].setAttenuationByDistance(3);
        lightsManager[activeLight].diffuse = {1.f, .5, 0.0};
        lightsManager[activeLight].specular = {1.f, .5, 0.0};

        lightsManager.addLight("cameraLight", PointLight());
        lightsManager["cameraLight"].position = {0.0f, -100.0f, 0.0f};

        lightsManager.upload(generalShader);

        /************************************************************************************
        // GAME VARIABLES / RENDER SETUP
        ************************************************************************************/


        glfwSetTime(0.0);
        float dt = 0;
        float currentFrame = 0;
        float previousFrame = 0;
        bool dropping = false;
        float timerMax = 1.3f;
        float movementTimer = 1.5f;
        float secondaryTimer = 0.0;
        float secondaryTimerMax = 0.01;
        bool texturing = false;
        bool lighting = false;
        bool flycamActive = false;
        bool camLight = false;

        GameGrid<gridX, gridY> gameGrid({gridX, gridX, gridY});
        glm::vec3 lightPosition(0);
            // Calculating the average position of the active blocks to get activeLight position.
        int activeBlocks = 0;
        for(auto & activePosition : gameGrid.getActivePositions()) {
            lightPosition += activePosition;
            activeBlocks++;
        }
        lightPosition /= activeBlocks;
        lightsManager[activeLight].position = lightPosition;

        RenderCommands::enableDepthTest();
        RenderCommands::enableFaceCulling();
        RenderCommands::setClearColor({0.0f, 0.0, 0.0f});

        /************************************************************************************
        // GAME LOOP
        ************************************************************************************/

        while(!glfwWindowShouldClose(m_window)) {

            sphynx::guiLoopStart();

            sphynx::guiDemo(true);

            generalShader.use();
            // Updating time
            previousFrame = currentFrame;
            currentFrame = glfwGetTime();
            dt = currentFrame - previousFrame;
            mouse.update(dt);

            /**
             * CONTROLLER INPUT/UPDATES
             */

            // Handling forward movement / dropping
            movementTimer -= dt;
            if( movementTimer < 0 && !dropping) {
                gameGrid.moveForward();
                movementTimer = timerMax;
            } else if(Sphynx::Keyboard::isKeyActive(Sphynx::KeyCode::X) && !dropping) {
                gameGrid.moveForward();
                movementTimer = timerMax;
                secondaryTimer = secondaryTimerMax;
            } else if (Sphynx::Keyboard::isKeyActive(Sphynx::KeyCode::J) && !dropping) {
                dropping = true;
            }
            if(dropping) {
                secondaryTimer -= dt;
                if(secondaryTimer < 0) {
                    movementTimer = timerMax;
                    secondaryTimer = secondaryTimerMax;
                    if(!gameGrid.moveForward()) {
                        dropping = false;
                    }
                }
            }

            if(Sphynx::Keyboard::isKeyActive(Sphynx::KeyCode::C)) {
                flycamActive = !flycamActive;
                if(flycamActive) {
                    mouse.captureMouse();
                    mouse.resetDelta();
                } else {
                    camera.SetLookAt({0.0f, 0.0f, 0.0f});
                    mouse.releaseMouse();
                }
            }

            if(Sphynx::Keyboard::isKeyActive(Sphynx::KeyCode::K)) {
                camLight = !camLight;
                if(camLight) {
                    lightsManager["cameraLight"].isActive = true;
                } else {
                    lightsManager["cameraLight"].isActive = false;
                    lightsManager.upload(generalShader, "cameraLight",0);
                }
            }
            if(camLight) {
                lightsManager["cameraLight"].position = camera.getPosition();
                lightsManager.upload(generalShader, "cameraLight", POS);
            }



            if( !flycamActive ) {
                if(Sphynx::Keyboard::isKeyActive(left )) {
                    rotation += rotationRate * dt;
                }
                if(Sphynx::Keyboard::isKeyActive(right )) {
                    rotation -= rotationRate * dt;
                }
                if(Sphynx::Keyboard::isKeyActive(zoomIn )) {
                    cameraDistance = std::max(minDistance, cameraDistance - zoomRate * dt);
                }
                if(Sphynx::Keyboard::isKeyActive(zoomOut )) {
                    cameraDistance = std::min(maxDistance, cameraDistance + zoomRate * dt);
                }
                if(Sphynx::Keyboard::isKeyActive(down )) {
                    cameraHeight -= zoomRate * dt;
                }
                if(Sphynx::Keyboard::isKeyActive(Sphynx::KeyCode::Space )) {
                    cameraHeight += zoomRate * dt;
                }

                cameraPosition.x = cosf(rotation)*cameraDistance;
                cameraPosition.y = cameraHeight;
                cameraPosition.z = sinf(rotation)*cameraDistance;
                camera.setPosition(cameraPosition);

                generalShader.uploadUniformVec3("u_viewPos", camera.getPosition());
                generalShader.uploadUniformMat4("u_view", camera.getViewMatrix());
                generalShader.uploadUniformMat4("u_projection", camera.getProjectionMatrix());

                borderShader.use();
                borderShader.uploadUniformMat4("u_view", camera.getViewMatrix());
                borderShader.uploadUniformMat4("u_projection", camera.getProjectionMatrix());
                generalShader.use();
            } else {
                camera.mouseInput(mouse.getMouseDelta()*0.05f);
                glm::vec3 direction {};
                if(Sphynx::Keyboard::isKeyActive(Sphynx::KeyCode::A)) {
                    direction +=  glm::vec3(-1.0f, 0.0f, 0.0f);
                }
                if(Sphynx::Keyboard::isKeyActive(Sphynx::KeyCode::D)) {
                    direction +=  glm::vec3(1.0f, 0.0f, 0.0f);
                }
                if(Sphynx::Keyboard::isKeyActive(Sphynx::KeyCode::W)) {
                    direction +=  glm::vec3(0.0f, 0.0f, 1.0f);
                }
                if(Sphynx::Keyboard::isKeyActive(Sphynx::KeyCode::S)) {
                    direction +=  glm::vec3(0.0f, 0.0f, -1.0f);
                }
                if(Sphynx::Keyboard::isKeyActive(Sphynx::KeyCode::LeftShift)) {
                    direction +=  glm::vec3(0.0f, -1.0f, 0.0f);
                }
                if(Sphynx::Keyboard::isKeyActive(Sphynx::KeyCode::Space)) {
                    direction +=  glm::vec3(0.0f, 1.0f, 0.0f);
                }
                if(direction.x || direction.y || direction.z) {
                    camera.move(direction, dt*10.f);
                }

                generalShader.uploadUniformVec3("u_viewPos", camera.getPosition());
                generalShader.uploadUniformMat4("u_view", camera.getViewMatrix());
                generalShader.uploadUniformMat4("u_projection", camera.getProjectionMatrix());

                borderShader.use();
                borderShader.uploadUniformMat4("u_view", camera.getViewMatrix());
                borderShader.uploadUniformMat4("u_projection", camera.getProjectionMatrix());
                generalShader.use();
            }


            // Handling directional movement
            if(Sphynx::Keyboard::isKeyActive(Sphynx::KeyCode::Left)){
                gameGrid.move(Direction::RIGHT);
            }
            if(Sphynx::Keyboard::isKeyActive(Sphynx::KeyCode::Right)){
                gameGrid.move(Direction::LEFT);
            }
            if(Sphynx::Keyboard::isKeyActive(Sphynx::KeyCode::Up)){
                gameGrid.move(Direction::UP);
            }
            if(Sphynx::Keyboard::isKeyActive(Sphynx::KeyCode::Down)){
                gameGrid.move(Direction::DOWN);
            }

            // Toggles texturing
            if(Sphynx::Keyboard::isKeyActive(Sphynx::KeyCode::T)) {
                generalShader.uploadUniformInt("u_texturing", !texturing);
                texturing = !texturing;
            }

            // Toggles lighting
            if(Sphynx::Keyboard::isKeyActive(Sphynx::KeyCode::L)) {
                generalShader.uploadUniformInt("u_lighting", !lighting);
                lighting = !lighting;
            }

            /************************************************************************************
            // Lighting updates/movement
            ************************************************************************************/

            lightsManager[light1].position = {sin(currentFrame), cos(currentFrame), cos(currentFrame)*4};
            lightsManager.upload(generalShader, light1, POS);
            lightsManager[light2].position = {cos(currentFrame + 1), sin(currentFrame + 1), 4.0f};
            lightsManager.upload(generalShader, light2, POS);

            lightsManager[activeLight].position = glm::mix(lightsManager[activeLight].position, lightPosition, dt*3.0f);
            lightsManager.upload(generalShader, activeLight, POS);
            generalShader.uploadUniformVec3("u_ambientLighting",  glm::vec3(0.3f*pow(sin(currentFrame*0.3), 2.0f)));

            /************************************************************************************
            // Rendering Walls
            ************************************************************************************/
            generalShader.use();
            // Rendering of surfaces
            modelManager[roof].upload(generalShader);
            RenderCommands::drawIndex(modelManager[roof].vao, GL_TRIANGLES);
            modelManager[leftWall].upload(generalShader);
            RenderCommands::drawIndex(modelManager[leftWall].vao, GL_TRIANGLES);
            modelManager[rightWall].upload(generalShader);
            RenderCommands::drawIndex(modelManager[rightWall].vao, GL_TRIANGLES);
            modelManager[floor].upload(generalShader);
            RenderCommands::drawIndex(modelManager[floor].vao, GL_TRIANGLES);
            modelManager[endWall].upload(generalShader);
            RenderCommands::drawIndex(modelManager[endWall].vao, GL_TRIANGLES);
            modelManager["pickaxe"].upload(generalShader);
            RenderCommands::drawIndex(modelManager["pickaxe"].vao, GL_TRIANGLES);
            modelManager["Cube"].upload(generalShader);
            RenderCommands::drawIndex(modelManager["Cube"].vao, GL_TRIANGLES);




            /************************************************************************************
            // Rendering Stopped Cubes
            ************************************************************************************/
            // Drawing of lines
            if(!texturing) {
                borderShader.use();
                borderShader.uploadUniformVec3("u_borderColor", {0.0, 0.0, 0.0});
                modelManager[box].vao->setIndexBuffer(boxLinesEBO);
                for(int i = 0; i < gridY; i++) {
                    for(auto & stoppedPosition : gameGrid.stoppedPositions[i]) {
                        modelManager[box].setPosition(stoppedPosition);
                        borderShader.uploadUniformMat4("u_modelMatrix", modelManager[box].getMatrix());
                        RenderCommands::drawIndex(modelManager[box].vao, GL_LINES);
                    }
                }
                modelManager[box].vao->setIndexBuffer(boxTrianglesEBO);
                generalShader.use();
            }
            // Drawing of faces
            for(int i = 0; i < gridY; i++) {
                for(auto & stoppedPosition : gameGrid.stoppedPositions[i]) {
                    modelManager[box].materials[0].diffuseColor = colors[i];
                    modelManager[box].setPosition(stoppedPosition);
                    modelManager[box].upload(generalShader);
                    RenderCommands::drawIndex(modelManager[box].vao, GL_TRIANGLES);
                }
            }


            /************************************************************************************
            // Rendering Active Cubes
            ************************************************************************************/

            // Drawing of lines
            borderShader.use();
            borderShader.uploadUniformVec3("u_borderColor", {0.5, 0.5, 0.5});
            modelManager[box].vao->setIndexBuffer(boxLinesEBO);
            for(auto & activePosition : gameGrid.getActivePositions()) {
                modelManager[box].setPosition(activePosition);
                borderShader.uploadUniformMat4("u_modelMatrix", modelManager[box].getMatrix());
                RenderCommands::drawIndex(modelManager[box].vao, GL_LINES);
            }
            modelManager[box].vao->setIndexBuffer(boxTrianglesEBO);

            // Drawing of faces
            generalShader.use();
            generalShader.uploadUniformFloat("u_opaqueness", 0.5f);
            RenderCommands::enableAlphaMode();
            activeBlocks = 0;
            lightPosition = {};
            modelManager[box].materials[0].diffuseColor = {0.7, 1.0, 1.0};
            for(auto & activePosition : gameGrid.getActivePositions()) {
                lightPosition += activePosition;
                activeBlocks++;
                modelManager[box].setPosition(activePosition);
                modelManager[box].upload(generalShader);
                RenderCommands::drawIndex(modelManager[box].vao, GL_TRIANGLES);
            }
            lightPosition /= activeBlocks;
            RenderCommands::disableAlphaMode();
            generalShader.uploadUniformFloat("u_opaqueness", 1.0f);


            sphynx::guiRender(m_window);
            // Reset for new frame
            glfwSwapBuffers(m_window);
            RenderCommands::clear();
            glfwPollEvents();

            if(Sphynx::Keyboard::isKeyActive(Sphynx::KeyCode::Escape )) {
                glfwSetWindowShouldClose(m_window, GL_TRUE);
            }
            ModelMatrix gizmoMatrix = ModelMatrix();
            gizmoMatrix.setScale(glm::vec3(3.0f));
            AxisIndicator::Draw(gizmoMatrix, camera);

        }
    }
    sphynx::guiCleanup();
    glfwTerminate(); //TODO: Some memory leak apparently associated with x11. Check for bug free version if time permits.
    return EXIT_SUCCESS;
}