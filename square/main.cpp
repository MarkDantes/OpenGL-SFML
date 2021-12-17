#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


void SetIcon(sf::Window& wnd);
void Init();
void Square();
void Line(float x, float y);

int main() {
    // ������ ����
    sf::Window window(sf::VideoMode(600, 600), "My OpenGL window", sf::Style::Default, sf::ContextSettings(32));
    // ������ ������ (���� � ��������� ��������� ��� ���������)
    SetIcon(window);
    // �������� ������������ ������������� (������������� ������� ��������� � �������� ������ ��������, ��� �� �������� �� �������, ������ ��� �� �����������)
    window.setVerticalSyncEnabled(true);

    // ���������� ����
    window.setActive(true);

    // �������������
    Init();

    // ������� ���� ����
    while (window.isOpen()) {
        sf::Event event;
        // ���� ��������� ������� ����, ��� ����� ������ ������� ������, �������� ����� � ������ �����
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // ���� �������, ������� �� �����
                window.close();
            }
            else if (event.type == sf::Event::Resized) {
                // ������ ������ ����, ���� �������� � ������ ������� Opengl ���������
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // ������� �������
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ������ �������
        Square();
        //������ ����� �� ��
        for (float i = 0; i < 1; i += 0.1f)
        {
            Line(-0.5f+i, 0.5f);

        }

        // ������������ ���� - ������ �������� � ������ ����� �������
        window.display();
    }

    // -- ��� ���� �� ������ �������� ��� ���������� ������� --

    return 0;
}

// � ������ ������������� ������� ���������� �������� �������, ������� � ������ �����
void Init() {
    // ������� ������ ���� ����� ������
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}



// ������� ��������� ��������
void Square() {

    glLoadIdentity();


    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f); glVertex2f(-0.5f, -0.5f);
    glColor3f(1.0f, 1.0f, 1.0f); glVertex2f(-0.5f, 0.5f);
    glColor3f(1.0f, 1.0f, 1.0f); glVertex2f(0.5f, 0.5f);
    glColor3f(1.0f, 1.0f, 1.0f); glVertex2f(0.5f, -0.5f);
    glEnd();

    glFlush();

    
}
void Line(float x, float y)
{
    glLoadIdentity();

    glBegin(GL_QUADS);
    glColor3f(0.4f, 1.0f, 0.9f); glVertex2f(x, y);
    glColor3f(0.4f, 1.0f, 0.9f); glVertex2f(x, -y);
    glColor3f(0.4f, 1.0f, 0.9f); glVertex2f(x+0.05f, -y);
    glColor3f(0.4f, 1.0f, 0.9f); glVertex2f(x+0.05f, y);
   
    glEnd();

    glFlush();
}


void SetIcon(sf::Window& wnd)
{
    sf::Image image;

    
}