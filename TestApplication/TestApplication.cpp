/**
 * EXAM 2022
 */

// SphynxEngine / project headers
#include <TestApplication.h>
#include <GeometricTools.h>
#include "gamegrid.h"
#include <rendering.h>
#include <inputhandling.h>

// External
#include <glm/glm.hpp>

// STD
#include <memory>
#include <random>




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
    : Sphynx::Application(name, version)
{ };


/**
 * MAIN PROGRAM
 */
int TestApplication::run() {
    {
        /**
         * SETTING UP KEYBINDS AND BEHAVIOUR
         */

        Input::Keyboard::setKeyBehaviour(Input::Key::SPACE, Input::KeyMode::CONTINUOUS);
        glfwSetKeyCallback(m_window, Input::Keyboard::callback);
        Input::Key left = Input::Key::A;
        Input::Key right = Input::Key::D;
        Input::Key zoomIn = Input::Key::W;
        Input::Key zoomOut = Input::Key::S;
        Input::Key up = Input::Key::C;
        Input::Key forwards = Input::Key::X;
        Input::Key forwardsFast = Input::Key::SPACE;
        Input::Key down = Input::Key::L_SHIFT;
        Input::Key exit = Input::Key::ESCAPE;
        Input::Key wireframeToggle = Input::Key::T;

        Input::Mouse mouse(m_window);


        Input::Keyboard::setKeyBehaviour(forwardsFast, Input::KeyMode::CONTINUOUS);
        Input::Keyboard::setKeyBehaviour(down, Input::KeyMode::CONTINUOUS);
        Input::Keyboard::setKeyBehaviour(zoomIn, Input::KeyMode::CONTINUOUS);
        Input::Keyboard::setKeyBehaviour(zoomOut, Input::KeyMode::CONTINUOUS);
        Input::Keyboard::setKeyBehaviour(left, Input::KeyMode::CONTINUOUS);
        Input::Keyboard::setKeyBehaviour(right, Input::KeyMode::CONTINUOUS);

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

        PerspectiveCamera::Frustum frustrum{};
        frustrum.angle = 70.0f;
        frustrum.far = 100.0f;
        frustrum.near = 0.01f;
        frustrum.height = windowHeight;
        frustrum.width = windowWidth;
        float cameraDistance = 70.0f;
        float cameraHeight = 20.0f;
        float maxDistance = 85.0f;
        float minDistance = 2.0f;
        float zoomRate = 30.0f;
        float rotation = 0.0f;
        float rotationRate = 2.0f;






        glm::vec3 cameraPosition(0.0f,
                                 0.0f,
                                 -5);

        PerspectiveCamera camera(frustrum, cameraPosition);


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
        bool flyCam = false;
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
            } else if(Input::Keyboard::isKeyActive(Input::Key::X) && !dropping) {
                gameGrid.moveForward();
                movementTimer = timerMax;
                secondaryTimer = secondaryTimerMax;
            } else if (Input::Keyboard::isKeyActive(Input::Key::J) && !dropping) {
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

            if(Input::Keyboard::isKeyActive(Input::Key::C)) {
                flyCam = !flyCam;
                if(flyCam) {
                    mouse.captureMouse();
                    mouse.resetDelta();
                } else {
                    camera.SetLookAt({0.0f, 0.0f, 0.0f});
                    mouse.releaseMouse();
                }
            }

            if(Input::Keyboard::isKeyActive(Input::Key::K)) {
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



            if( !flyCam ) {
                if(Input::Keyboard::isKeyActive( left )) {
                    rotation += rotationRate * dt;
                }
                if(Input::Keyboard::isKeyActive( right )) {
                    rotation -= rotationRate * dt;
                }
                if(Input::Keyboard::isKeyActive( zoomIn )) {
                    cameraDistance = std::max(minDistance, cameraDistance - zoomRate * dt);
                }
                if(Input::Keyboard::isKeyActive( zoomOut )) {
                    cameraDistance = std::min(maxDistance, cameraDistance + zoomRate * dt);
                }
                if(Input::Keyboard::isKeyActive( down )) {
                    cameraHeight -= zoomRate * dt;
                }
                if(Input::Keyboard::isKeyActive( Input::Key::SPACE )) {
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
                if(Input::Keyboard::isKeyActive(Input::Key::A)) {
                    direction +=  glm::vec3(-1.0f, 0.0f, 0.0f);
                }
                if(Input::Keyboard::isKeyActive(Input::Key::D)) {
                    direction +=  glm::vec3(1.0f, 0.0f, 0.0f);
                }
                if(Input::Keyboard::isKeyActive(Input::Key::W)) {
                    direction +=  glm::vec3(0.0f, 0.0f, 1.0f);
                }
                if(Input::Keyboard::isKeyActive(Input::Key::S)) {
                    direction +=  glm::vec3(0.0f, 0.0f, -1.0f);
                }
                if(Input::Keyboard::isKeyActive(Input::Key::L_SHIFT)) {
                    direction +=  glm::vec3(0.0f, -1.0f, 0.0f);
                }
                if(Input::Keyboard::isKeyActive(Input::Key::SPACE)) {
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
            if(Input::Keyboard::isKeyActive(Input::Key::LEFT)){
                gameGrid.move(Direction::RIGHT);
            }
            if(Input::Keyboard::isKeyActive(Input::Key::RIGHT)){
                gameGrid.move(Direction::LEFT);
            }
            if(Input::Keyboard::isKeyActive(Input::Key::UP)){
                gameGrid.move(Direction::UP);
            }
            if(Input::Keyboard::isKeyActive(Input::Key::DOWN)){
                gameGrid.move(Direction::DOWN);
            }

            // Toggles texturing
            if(Input::Keyboard::isKeyActive(Input::Key::T)) {
                generalShader.uploadUniformInt("u_texturing", !texturing);
                texturing = !texturing;
            }

            // Toggles lighting
            if(Input::Keyboard::isKeyActive(Input::Key::L)) {
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

            // Reset for new frame
            glfwSwapBuffers(m_window);
            RenderCommands::clear();
            glfwPollEvents();

            if(Input::Keyboard::isKeyActive( Input::Key::ESCAPE )) {
                glfwSetWindowShouldClose(m_window, GL_TRUE);
            }
        }
    }
    glfwTerminate(); //TODO: Some memory leak apparently associated with x11. Check for bug free version if time permits.
    return EXIT_SUCCESS;
}