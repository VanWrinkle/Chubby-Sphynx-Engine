//
// Created by andre on 14.09.22.
//

// Sphynx Engine
#include <SphynxApplication.h>
#include <log.h>

// STD
#include <sstream>



void GLFWErrorCallback(int code, const char* description);
void ivErrorMessage(GLuint type, const GLuint &ID);
void GLAPIENTRY MessageCallback( GLenum source, GLenum type, GLuint id, GLenum severity,
                                 GLsizei length, const GLchar* message, const void* userParam );


namespace Sphynx {

    /**
     * Handles parsing of command line arguments
     * @param argc
     * @param argv
     * @return - EXIT_SUCCESS or EXIT_FAILURE
     */
    int Application::parseArguments(const int &argc, char **argv) {
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
    int Application::initialize(){
        //Initialization of static Log class
        Sphynx::Log::Init();

        if( !glfwInit() ) {
            SE_CORE_CRITICAL("Failed to initialize glfw library");
            return EXIT_FAILURE;
        }

        glfwSetErrorCallback( GLFWErrorCallback );
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = glfwCreateWindow(m_width, m_height, (m_name + " " + m_version).data(), nullptr, nullptr);
        glfwMakeContextCurrent(m_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            SE_CORE_CRITICAL("Failed to initialize GLAD.");
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
MessageCallback( GLenum source, GLenum type, GLuint id, GLenum severity,
                 GLsizei length, const GLchar* message, const void* userParam )
{
    std::stringstream errorMessage;
    errorMessage << "[GL CALLBACK] Type: ";
    switch(type) {
        case GL_DEBUG_TYPE_ERROR: errorMessage << "ERROR";                   break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: errorMessage << "DEPRECATED";break;
        case GL_DEBUG_TYPE_OTHER: errorMessage << "OTHER";                   break;
        case GL_DEBUG_TYPE_PERFORMANCE: errorMessage << "PERFORMANCE";       break;
        case GL_DEBUG_TYPE_PORTABILITY: errorMessage << "PORTABILITY";       break;
        case GL_DEBUG_TYPE_MARKER: errorMessage << "MARKER";                 break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: errorMessage << "UNDEFINED";  break;
        default:                                                             break;
    }
    errorMessage << "   Severity: ";
    switch(severity) {
        case GL_DEBUG_SEVERITY_LOW: errorMessage << "LOW";                   break;
        case GL_DEBUG_SEVERITY_MEDIUM: errorMessage << "MEDIUM";             break;
        case GL_DEBUG_SEVERITY_HIGH: errorMessage << "HIGH";                 break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: errorMessage << "NOTIFICATION"; break;
        default: errorMessage << "Invalid Severity";                         break;
    }
    errorMessage << std::endl << "Message: " << message << std::endl;
    switch(severity) {
        case GL_DEBUG_SEVERITY_LOW: SE_CORE_WARN(errorMessage.str());        break;
        case GL_DEBUG_SEVERITY_MEDIUM: SE_CORE_ERROR(errorMessage.str());    break;
        case GL_DEBUG_SEVERITY_HIGH: SE_CORE_CRITICAL(errorMessage.str());   break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: SE_CORE_INFO(errorMessage.str()); break;
        default: std::cerr << "Invalid error type.";                         break;
    }
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