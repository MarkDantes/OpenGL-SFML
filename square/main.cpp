#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


void SetIcon(sf::Window& wnd);
void Init();
void Square();
void Line(float x, float y);

int main() {
    // Создаём окно
    sf::Window window(sf::VideoMode(600, 600), "My OpenGL window", sf::Style::Default, sf::ContextSettings(32));
    // Ставим иконку (окна с дефолтной картинкой это некрасиво)
    SetIcon(window);
    // Включаем вертикальную синхронизацию (синхронизация частоты отрисовки с частотой кадров монитора, что бы картинка не фризила, делать это не обязательно)
    window.setVerticalSyncEnabled(true);

    // Активируем окно
    window.setActive(true);

    // Инициализация
    Init();

    // Главный цикл окна
    while (window.isOpen()) {
        sf::Event event;
        // Цикл обработки событий окна, тут можно ловить нажатия клавиш, движения мышки и всякое такое
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // Окно закрыто, выходим из цикла
                window.close();
            }
            else if (event.type == sf::Event::Resized) {
                // Изменён размер окна, надо поменять и размер области Opengl отрисовки
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // Очистка буферов
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Рисуем квадрат
        Square();
        //Рисуем линии на нём
        for (float i = 0; i < 1; i += 0.1f)
        {
            Line(-0.5f+i, 0.5f);

        }

        // Отрисовывает кадр - меняет передний и задний буфер местами
        window.display();
    }

    // -- тут надо не забыть очистить все выделенные ресурсы --

    return 0;
}

// В момент инициализации разумно произвести загрузку текстур, моделей и других вещей
void Init() {
    // Очистка буфера тёмно жёлтым цветом
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}



// Функция отрисовки квадрата
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