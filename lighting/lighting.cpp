
#include <gl/glew.h>

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>


// ���������� � ����������������� ID
// ID ��������� ���������
GLuint Program;
// ID �������� �����
GLint Attrib_color;
// ID ��������
GLint Attrib_vertex;
// ID �������
GLuint Attrib_normal;
GLuint Unif_e;
GLuint Unif_l;
// ID ������� ���������� �����
GLint Unif_color;
GLint Unif_x;
GLint Unif_y;
// ID Vertex Buffer Object
GLuint VBO;
GLuint normalsVBO; 
// ID VBO �����
GLuint VBO_color;
// �������
struct Vertex
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};


// �������� ��� ���������� �������
const char* VertexShaderSource = R"(
    #version 330 core
   //
// Blinn vertex shader
//

varying	vec3 l;
varying	vec3 h;
varying	vec3 n;
varying vec3 v;
// ����������� ���� ��������
         float x_angle =xa  ;
         float y_angle = ya ;
          float z_angle = 1;

uniform	vec4	lightPos ;
uniform	vec4	eyePos;

void main(void)
{
	vec3	p = vec3 (  gl_Vertex * mat3(
            1, 0, 0,
            0, cos(x_angle), -sin(x_angle),
            0, sin(x_angle), cos(x_angle)
        ) * mat3(
            cos(y_angle), 0, sin(y_angle),
            0, 1, 0,
            -sin(y_angle), 0, cos(y_angle)
        )   * mat3(
            cos(z_angle), -sin(z_angle), 0,
            sin(z_angle), cos(z_angle), 0,
            0, 0, 1
        ); );			// transformed point to world space

	l = normalize ( vec3 ( lightPos ) - p );					// vector to light source
	v = normalize ( vec3 ( eyePos )   - p );					// vector to the eye
	h = normalize ( l + v );
	n = normalize ( gl_NormalMatrix * gl_Normal );							// transformed n

	gl_Position =vec4(p, 1.0); ;



)";

// �������� ��� ������������ �������
const char* FragShaderSource = R"(
    #version 330 core
    varying	vec3 l;
varying	vec3 h;
varying vec3 v;
varying vec3 n;

void main (void)
{
    const vec4  diffColor = vec4 ( 0.5, 0.0, 0.0, 1.0 );
    const vec4  specColor = vec4 ( 0.7, 0.7, 0.0, 1.0 );
    const float specPower = 30.0;

    vec3 n2   = normalize ( n );
    vec3 l2   = normalize ( l );
    vec3 h2   = normalize ( h );
    vec4 diff = diffColor * max ( dot ( n2, l2 ), 0.0 );
    vec4 spec = specColor * pow ( max ( dot ( n2, h2 ), 0.0 ), specPower );

    gl_FragColor = diff + spec;
}
)";


void Init();
void Draw();
void Release();

float xa, ya = 1;

float eye[3] ={7, 5, 7};			// camera position
float light[3] = { 5, 0, 4 };		// light position

int main() {
   
    
    
    sf::Window window(sf::VideoMode(600, 600), "My OpenGL window", sf::Style::Default, sf::ContextSettings(24));
    window.setVerticalSyncEnabled(true);

    window.setActive(true);



    // ������������� glew
    glewInit();

    Init();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::Resized) {
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))) { xa -= 0.1f; }
        else
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))) { xa += 0.1f; }
            else
                if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))) { ya += 0.1f; }
                else
                    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))) { ya -= 0.1f; }


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Draw();

        window.display();
    }

    Release();
    return 0;
}


// �������� ������ OpenGL, ���� ���� �� ����� � ������� ��� ������
void checkOpenGLerror() {
    GLenum errCode;
    // ���� ������ ����� �������� ���
    // https://www.khronos.org/opengl/wiki/OpenGL_Error
    if ((errCode = glGetError()) != GL_NO_ERROR)
        std::cout << "OpenGl error!: " << errCode << std::endl;
}

// ������� ������ ���� �������
void ShaderLog(unsigned int shader)
{
    int infologLen = 0;
    int charsWritten = 0;
    char* infoLog;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLen);
    if (infologLen > 1)
    {
        infoLog = new char[infologLen];
        if (infoLog == NULL)
        {
            std::cout << "ERROR: Could not allocate InfoLog buffer" << std::endl;
            exit(1);
        }
        glGetShaderInfoLog(shader, infologLen, &charsWritten, infoLog);
        std::cout << "InfoLog: " << infoLog << "\n\n\n";
        delete[] infoLog;
    }
}


int vertex_count;

void InitVBO()
{
    glGenBuffers(1, &normalsVBO);
    glGenBuffers(1, &VBO_color);
    // ������� ������
    Vertex cube[] = {
        { 0.500000, -0.500000, 0.500000},
    {0.500000, -0.500000, 0.500000},
    {-0.500000, 0.500000, 0.500000},
        {0.500000, 0.500000, 0.500000},
    {-0.500000, 0.500000, -0.500000},
    {0.500000, 0.500000, -0.500000},
    {-0.500000, -0.500000, -0.500000},
    {0.500000, -0.500000, -0.500000 }
    };
    float n[4][2] = {
        { 0.000000, 0.000000},
    {1.000000, 0.000000},
    {0.000000, 1.000000},
    {1.000000, 1.000000},
    };

    vertex_count = sizeof(cube) / sizeof(Vertex);
    // �������� ������� � �����
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(n), n, GL_STATIC_DRAW);
    checkOpenGLerror();
}


void InitShader() {
    // ������� ��������� ������
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    // �������� �������� ���
    glShaderSource(vShader, 1, &VertexShaderSource, NULL);
    // ����������� ������
    glCompileShader(vShader);
    std::cout << "vertex shader \n";
    ShaderLog(vShader);

    // ������� ����������� ������
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    // �������� �������� ���
    glShaderSource(fShader, 1, &FragShaderSource, NULL);
    // ����������� ������
    glCompileShader(fShader);
    std::cout << "fragment shader \n";
    ShaderLog(fShader);

    // ������� ��������� � ����������� ������� � ���
    Program = glCreateProgram();
    glAttachShader(Program, vShader);
    glAttachShader(Program, fShader);

    // ������� ��������� ���������
    glLinkProgram(Program);
    // ��������� ������ ������
    int link_ok;
    glGetProgramiv(Program, GL_LINK_STATUS, &link_ok);
    if (!link_ok)
    {
        std::cout << "error attach shaders \n";
        return;
    }

    // ���������� ID �������� �� ��������� ���������
    const char* attr_name = "vertexPosition";
    Attrib_vertex = glGetAttribLocation(Program, attr_name);
    if (Attrib_vertex == -1)
    {
        std::cout << "could not bind attrib " << attr_name << std::endl;
        return;
    }
    // ���������� ID �������� �����
    Attrib_color = glGetAttribLocation(Program, "color");
    if (Attrib_color == -1)
    {
        std::cout << "could not bind attrib color" << std::endl;
        return;
    }

    Attrib_normal = glGetAttribLocation(Program, "n");
    if (Attrib_normal == -1)
    {
        std::cout << "could not bind attrib normal" << std::endl;
        return;
    }
    Unif_e = glGetAttribLocation(Program, "eyePos");
    if (Unif_e == -1)
    {
        std::cout << "could not bind attrib color" << std::endl;
        return;
    }
    Unif_l = glGetAttribLocation(Program, "lightPos");
    if (Unif_l == -1)
    {
        std::cout << "could not bind attrib color" << std::endl;
        return;
    }
    // ���������� ID �������
    const char* unif_name1 = "xa";
    Unif_x = glGetUniformLocation(Program, unif_name1);
    if (Unif_x == -1)
    {
        std::cout << "could not bind uniform " << unif_name1 << std::endl;
        return;
    }
    // ���������� ID �������
    const char* unif_name2 = "ya";
    Unif_y = glGetUniformLocation(Program, unif_name2);
    if (Unif_y == -1)
    {
        std::cout << "could not bind uniform " << unif_name2 << std::endl;
        return;
    }

    checkOpenGLerror();
}

void Init() {
    InitShader();
    InitVBO();
    // �������� �������� �������
    glEnable(GL_DEPTH_TEST);
}


void Draw() {
    // ������������� ��������� ��������� �������
    glUseProgram(Program);
    // �������� ������� � �������
    glUniform1f(Unif_x, xa);
    glUniform1f(Unif_y, ya);
    glUniform3fv(Unif_l,1, light);
    glUniform3fv(Unif_e,1,  eye);
    // �������� ������ ���������

    glEnableVertexAttribArray(Attrib_vertex);
    glEnableVertexAttribArray(Attrib_color);
    glEnableVertexAttribArray(Attrib_normal);
    // ���������� VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // �������� pointer 0 ��� ������������ ������, �� ��������� ��� ������ � VBO
    glVertexAttribPointer(Attrib_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
    // ���������� VBO_color
    glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
    glVertexAttribPointer(Attrib_normal, 3, GL_FLOAT, GL_FALSE, 0, 0);


    // ��������� VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // �������� ������ �� ����������(������)
    glDrawArrays(GL_QUADS, 0, vertex_count);
    // ��������� ������ ���������
    glDisableVertexAttribArray(Attrib_vertex);
    glDisableVertexAttribArray(Attrib_color);
    glDisableVertexAttribArray(Attrib_normal);
    // ��������� ��������� ���������
    glUseProgram(0);
    checkOpenGLerror();
}


// ������������ ��������
void ReleaseShader() {
    // ��������� ����, �� ��������� �������� ���������
    glUseProgram(0);
    // ������� ��������� ���������
    glDeleteProgram(Program);
}

// ������������ ������
void ReleaseVBO()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &normalsVBO);
}

void Release() {
    ReleaseShader();
    ReleaseVBO();
}
