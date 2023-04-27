#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include <math.h>


//Cristhian Ocola
//Carlos Morales

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//----------------------SHADER TRIANGULOS----------------------------------------

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";


//----------------------SHADER LINEAS----------------------------------------

const char *vertexShaderSourceLine = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "}\0";
const char *fragmentShaderSourceLine = "#version 330 core\n"
    "out vec4 FragColor;\n"
	"in vec4 vertexColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
    "}\n\0";


//----------------------SHADER PUNTOS----------------------------------------
    
const char *vertexShaderSourcePoint = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "}\0";
const char *fragmentShaderSourcePoint = "#version 330 core\n"
    "out vec4 FragColor;\n"
	"in vec4 vertexColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
    "}\n\0";    
	

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    gladLoadGL(glfwGetProcAddress);


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
	
	// vertex shader
    unsigned int vertexShaderLine = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderLine, 1, &vertexShaderSourceLine, NULL);
    glCompileShader(vertexShaderLine);
    // check for shader compile errors
    glGetShaderiv(vertexShaderLine, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShaderLine, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShaderLine = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderLine, 1, &fragmentShaderSourceLine, NULL);
    glCompileShader(fragmentShaderLine);
    // check for shader compile errors
    glGetShaderiv(fragmentShaderLine, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderLine, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgramLine = glCreateProgram();
    glAttachShader(shaderProgramLine, vertexShaderLine);
    glAttachShader(shaderProgramLine, fragmentShaderLine);
    glLinkProgram(shaderProgramLine);
    // check for linking errors
    glGetProgramiv(shaderProgramLine, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramLine, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShaderLine);
	glDeleteShader(fragmentShaderLine);




    //------------------------------------------------------------------------------------------------------

    
	// vertex shader
    unsigned int vertexShaderPoint = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderPoint, 1, &vertexShaderSourcePoint, NULL);
    glCompileShader(vertexShaderPoint);
    // check for shader compile errors
    glGetShaderiv(vertexShaderPoint, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShaderPoint, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShaderPoint = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderPoint, 1, &fragmentShaderSourcePoint, NULL);
    glCompileShader(fragmentShaderPoint);
    // check for shader compile errors
    glGetShaderiv(fragmentShaderPoint, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderPoint, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgramPoint = glCreateProgram();
    glAttachShader(shaderProgramPoint, vertexShaderPoint);
    glAttachShader(shaderProgramPoint, fragmentShaderPoint);
    glLinkProgram(shaderProgramPoint);
    // check for linking errors
    glGetProgramiv(shaderProgramPoint, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramPoint, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShaderPoint);
	glDeleteShader(fragmentShaderPoint);
	
	//---------------------------------------------------------------------------
    // set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
const int num_segments = 18; // 360 grados dividido por 20 grados por segmento

std::vector<unsigned int> indices;
for (int i = 0; i < num_segments; i++) {
    indices.push_back(i);
    indices.push_back((i + 1) % num_segments);
    indices.push_back(num_segments);
}

float radius = 0.5f;
float theta = 2.0f * M_PI / num_segments; // convertir a radianes
float x = radius; // comenzamos en el borde del círculo
float y = 0;
std::vector<float> vertices;
for (int i = 0; i < num_segments; i++) {
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(0.0f);
    // aplicamos una rotación para obtener el siguiente vértice en el borde del círculo
    float t = x;
    x = cosf(theta) * x - sinf(theta) * y;
    y = sinf(theta) * t + cosf(theta) * y;
}
vertices.push_back(0.0f); // añadimos el centro del círculo
vertices.push_back(0.0f);
vertices.push_back(0.0f);

std::vector<unsigned int> indicesLine;
for (int i = 0; i < num_segments; i++) {
    indicesLine.push_back(i);
    indicesLine.push_back((i + 1) % num_segments);
}

std::vector<float> verticesLine;
x = radius; // comenzamos en el borde del círculo
y = 0;
for (int i = 0; i < num_segments; i++) {
    verticesLine.push_back(x);
    verticesLine.push_back(y);
    verticesLine.push_back(0.0f);
    // aplicamos una rotación para obtener el siguiente vértice en el borde del círculo
    float t = x;
    x = cosf(theta) * x - sinf(theta) * y;
    y = sinf(theta) * t + cosf(theta) * y;
}



    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		// draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        
        unsigned int VBOLine, VAOLine, EBOLine;

        glGenVertexArrays(1, &VAOLine);
        glGenBuffers(1, &VBOLine);
        glGenBuffers(1, &EBOLine);
        glBindVertexArray(VAOLine);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBOLine);
        glBufferData(GL_ARRAY_BUFFER, verticesLine.size() * sizeof(float), verticesLine.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOLine);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLine.size() * sizeof(unsigned int), indicesLine.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0); 

    
		// draw our first triangle
        glUseProgram(shaderProgramLine);
        glBindVertexArray(VAOLine);
		glDrawElements(GL_LINE_LOOP, indicesLine.size(), GL_UNSIGNED_INT, 0);


        glPointSize(4);

        	// draw our first triangle
        glUseProgram(shaderProgramPoint);
        glBindVertexArray(VAOLine);
		glDrawElements(GL_POINTS, indicesLine.size(), GL_UNSIGNED_INT, 0);


       

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
