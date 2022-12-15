//
// Created by andre on 14.09.22.
//


#include <GLFWApplication.h>

#include <utility>



void GLFWErrorCallback(int code, const char* description);
void ivErrorMessage(GLuint type, const GLuint &ID);
void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam );



namespace glfwApp {

    GLFWApplication::GLFWApplication(std::string  name, std::string  version) :
                                                                m_name(std::move(name)),
                                                                m_version(std::move(version)){}

    GLFWApplication::~GLFWApplication()= default;

    /**
     * Handles parsing of command line arguments
     * @param argc
     * @param argv
     * @return - EXIT_SUCCESS or EXIT_FAILURE
     */
    unsigned GLFWApplication::parseArguments(const int &argc, char **argv) {
        try{
            TCLAP::CmdLine cmd("", ' ', "0.1", false);
            TCLAP::ValueArg<int> widthArg("w", "width", "width of window", false, 800, "int");
            TCLAP::ValueArg<int> heightArg("g", "height", "height of window", false, 800, "int");

            cmd.add(widthArg);
            cmd.add(heightArg);
            cmd.parse(argc, argv);

            m_width = widthArg.getValue();
            m_height = heightArg.getValue();

            return EXIT_SUCCESS;
        } catch(TCLAP::ArgException &e) {
            std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
            return EXIT_FAILURE;
        }
    }




    /**
     *
     * @return
     */
    unsigned GLFWApplication::initialize(){

        if(!glfwInit()) {
            std::cout << "GLFW failed to initialize" << std::endl;
            return EXIT_FAILURE;
        }

        glfwSetErrorCallback(GLFWErrorCallback);


        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


        m_window = glfwCreateWindow(m_width, m_height, (m_name + " " + m_version).data(), nullptr, nullptr);
        glfwMakeContextCurrent(m_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            glfwTerminate();
            return EXIT_FAILURE;
        }

        glEnable ( GL_DEBUG_OUTPUT );
        glEnable (GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(MessageCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

        return EXIT_SUCCESS;
    }

}



/**
 *
 * @param source
 * @param type
 * @param id
 * @param severity
 * @param length
 * @param message
 * @param userParam
 */
void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
    std::cerr << "\n\nGL CALLBACK:" << ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "") <<
              "type =0x" << type <<
              ", severity = 0x" << severity <<
              ", message =" << message << std::endl;
}



/**
 * Provided by teacher
 * @param code
 * @param description
 */
void GLFWErrorCallback(int code, const char* description)
{
    std::cerr << "Error " << "0x" << std::hex << code << ':' << description << "\n";
}