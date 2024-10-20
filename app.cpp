//This is just a simple OpenGL app that
//is only used to display the rendered images.
//The rendered image is displayed as an unfiltered texture on a quad

#include <glew.h>
#include <GL/gl.h>
#include <glfw3.h>
#include <vector>
#include <ppm.h>
#include <rendering.cpp>

void error_callback(int error, const char* description)
{
    std::cerr << "error: " << description << std::endl; 
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

class App
{
    public:
        void start(int w, int h)
        {
            renderScene(w,h);
            
            std::cout << "Reading ppm..." << std::endl;
            std::vector<unsigned char> imageBuffer;
            const char* fileName = "output.ppm";
            readPpm(fileName, imageBuffer, imageWidth, imageHeight);

            window = initGLFW();

            setupShaders();

            setupDisplay();

            setupDisplayTexture(imageBuffer);

            renderLoop();

            cleanup();
        }

        int imageWidth, imageHeight;

    private:
        GLFWwindow* window;

        GLuint displayTexture;

        GLuint shaderProgram;

        GLuint VBO;
        GLuint VAO;
        GLuint EBO;

        float vertices[20] = 
        {   //Position              //TexCoord //Image is a ppm so 0,0 is top-left
            -1.0f, -1.0f, 0.0f,     0.0f, 1.0f, //bottom left
            -1.0f, 1.0f, 0.0f,      0.0f, 0.0f, //top left
            1.0f, 1.0f, 0.0f,       1.0f, 0.0f, //top right
            1.0f, -1.0f, 0.0f,      1.0f, 1.0f //bottom right
        };

        unsigned int indices[6] = 
        {
            0,1,3,
            1,2,3,
        };

        const char *vertexShaderSrc = 
        "#version 330 core \n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec2 aTexCoord;\n"
        "out vec2 TexCoord;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "   TexCoord = aTexCoord;\n"
        "}\0";

        const char *fragmentShaderSrc =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec2 TexCoord;\n"
        "uniform sampler2D tex;\n"
        "void main()\n"
        "{\n"
        "   FragColor = texture(tex, TexCoord);\n"
        "}\0";

        GLFWwindow* initGLFW()
        {
            glfwSetErrorCallback(error_callback);

            std::cout << "GLFW init" << std::endl;
            if(!glfwInit()) {
                std::cerr << "failed to init GLFW" << std::endl;   
                return nullptr;
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            std::cout << "Creating window..." << std::endl;
            GLFWwindow* w = glfwCreateWindow(imageWidth, imageHeight, "Naive Renderer", NULL, NULL);

            if(!w)
            {
                std::cerr << "Window failed to create, terminating" << std::endl;
                glfwTerminate();
                return nullptr;
            }

            glfwMakeContextCurrent(w);

            GLenum err = glewInit();
            if(err != GLEW_OK)
            {
                std::cerr << "Failed to init glew" << std::endl;
                glfwTerminate();
                return nullptr;
            }

            return w;
        }

        void renderLoop()
        {
            while(!glfwWindowShouldClose(window))
            {
                glClear(GL_COLOR_BUFFER_BIT);

                glUseProgram(shaderProgram);
                glBindVertexArray(VAO);

                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                glfwSwapBuffers(window);
                glfwPollEvents();
            }
        }

        void setupDisplay()
        {
            glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
            glViewport(0, 0, imageWidth, imageHeight);

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        void setupDisplayTexture(std::vector<unsigned char> &imageData)
        {
            glGenTextures(1, &displayTexture);
            glBindTexture(GL_TEXTURE_2D, displayTexture);

            //I just want to display the actual ppm file unfiltered
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData.data());
        }

        void setupShaders()
        {
            int success;
            char infoLog[512];

            unsigned int vertexShader;
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
            glCompileShader(vertexShader);
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
                std::cout << "Vertex shader compilation failed" << std::endl
                << infoLog << std::endl;
            }

            unsigned int fragmentShader;
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
            glCompileShader(fragmentShader);
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
                std::cout << "Fragment shader compilation failed" << std::endl
                << infoLog << std::endl;
            }

            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
                std::cout << "Shader program failed to create" << std::endl
                << infoLog << std::endl;
            }

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
        }

        void cleanup()
        {
            glfwDestroyWindow(window);
            glfwTerminate();
        }
};