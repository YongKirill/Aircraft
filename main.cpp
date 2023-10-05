#include <SFML/Graphics.hpp>
#include <iostream>
#include "Aircraft.h"

using namespace sf;

//void Collision(Aircraft sam, std::list<Bullet>& Bul_list)
//{
//    for (auto it_bull = Bul_list.begin(); it_bull != Bul_list.end();)
//    {
//        double distance_air_bull = sqrt(pow(sam.sprite.getPosition().x - (*it_bull).sprite.getPosition().x, 2) + pow(sam.sprite.getPosition().y - (*it_bull).sprite.getPosition().y, 2));
//        if (distance_air_bull < 30)
//        {
//            auto deleted = it_bull;
//            ++it_bull;
//            Bul_list.erase(deleted);
//        }
//        else
//            ++it_bull;
//    }
//}

void Play(std::list<Bullet>& Bul_list, std::list<Aircraft>& Air_list, float mouse_x, float mouse_y, int bull_behavior, clock_t& t0)
{
    for (auto it_sam = Air_list.begin(); it_sam != Air_list.end(); ++it_sam)
    {
        (*it_sam).Play(mouse_x, mouse_y, Bul_list, t0);
        //Collision(*it_sam, Bul_list);
    }
    if (Bul_list.size() > 0)
    {
        for (auto it_bul = Bul_list.begin(); it_bul != Bul_list.end();)
        {
            (*it_bul).Play(Bul_list, it_bul, bull_behavior);
        }
    }
}


//class Menu {
//public:
//    Menu() {
//        rectangle.setSize(sf::Vector2f(522, 564));
//        rectangle.setPosition(60,50);
//        rectangle.setFillColor(sf::Color::Red);
//
//        // Создание объекта текста
//        sf::Font font;
//        if (!font.loadFromFile("arial.ttf")) 
//        {
//            std::cout << "TEXT ERROR!\n";
//            exit(1);
//        }
//        sf::Text text("Пример текста", font, 24);
//        text.setPosition(141, 70);
//        text.setFillColor(sf::Color::Black);
//
//        for (int i = 0; i < 3; i++)
//        {
//            sf::RectangleShape rectangle;
//            rectangle.setSize(sf::Vector2f(406, 94));
//            rectangle.setPosition(116, (4 + i * 3) * 47);
//            rectangle.setFillColor(sf::Color::Green);
//
//            list_butt.push_back(rectangle);
//        }
//
//
//    }
//
//    void draw(sf::RenderWindow& window) {
//        window.draw(rectangle);
//        for (const auto& elm : list_butt) 
//        {
//            window.draw(elm);
//        }
//        window.draw(text); // Отрисовка текста
//    }
//
//private:
//    sf::RectangleShape rectangle;
//    
//    std::list <RectangleShape> list_butt;
//    sf::Text text;
//
//};
//
//int main() {
//    sf::RenderWindow window(sf::VideoMode(x_window_size, y_window_size), "Прямоугольник SFML");
//
//    Menu menu;
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        menu.draw(window);
//        window.display();
//    }
//
//    return 0;
//}


int main()
{
    clock_t t0 = clock();
    setlocale(LC_ALL, "rus");

    sf::Font font;
    if (!font.loadFromFile("ofont.ru_Unbounded.ttf"))
    {
        std::cout << "Ошибка загрузки шрифта!\n";
        return 0;
    }
    std::cout << "Шрифт загружен\n";
    sf::Text text_fps;
    text_fps.setFont(font);

    text_fps.setCharacterSize(24);

    text_fps.setFillColor(sf::Color::Red);

    text_fps.setStyle(sf::Text::Bold | sf::Text::Underlined);
    
    int bull_behavior = 0;
    std::cout << "Выберите настройки:\nПоведение пуль: \n\t1) Удаление при касании экрана\n\t2) Отталкивание от края\n";
    std::cin >> bull_behavior;
    while ((bull_behavior > 2) || (bull_behavior < 1))
    {
        system("cls");
        std::cout << "Вы ввели неправильную цифру попробуйте снова!\nВыберите настройки:\nПоведение пуль: \n\t1) Удаление при касании экрана\n\t2) Отталкивание от края\n";
        std::cin >> bull_behavior;
    }

    RenderWindow window(VideoMode(x_window_size, y_window_size), "Version_1.8!");
    Aircraft Airbus(200, 200, 1, 0, "Images/airplane.png");

    std::list <Aircraft> Samoletu;
    Samoletu.push_back(Airbus);

    std::list <Bullet> bullets;

    clock_t fps_start = clock();
    float fps_min = 100;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        Play(bullets, Samoletu, Mouse::getPosition(window).x, Mouse::getPosition(window).y, bull_behavior, t0);
        
        window.clear();
        window.setFramerateLimit(fps);

        for (auto it_sam = Samoletu.begin(); it_sam != Samoletu.end(); ++it_sam)
        {
            window.draw((*it_sam).sprite);
        }
        if (bullets.size() > 0)
        {
            for (auto it_bul = bullets.begin(); it_bul != bullets.end(); ++it_bul)
            {
                window.draw((*it_bul).bullet);
            }
        }       
        float currentTime = clock();
        float fps = 1/ ((currentTime - fps_start)/1000);
        fps_start = currentTime; 
        text_fps.setString(std::to_string(fps));
        window.draw(text_fps);

        if (fps < fps_min)
        {
            fps_min = fps;
        }

        window.display();
    }
    std::cout << fps_min;
    return 0;
}