#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

const int WIDHT = 1200;
const int HEIGHT = 800;

class ObjectatMenu {
public:
    //Координаты объекта, размеры (ширина и высота), скорость
    float wx, wy, width, height;
    sf::Vector2f speed; //Вектор скорости(направления) - при помощи него будем изменять направление движения
    sf::String File; // Название изображения с расширением
    sf::Image image; //Загрузка изображения
    sf::Texture texture; //Добавление в объект 'Текстуры'
    sf::Sprite sprite; //Добавление в объект 'спрайта'

    ObjectatMenu(float X, float Y, float Widht, float Height, float Speed_X, float Speed_Y, sf::String F) {
        wx = X;
        wy = Y;
        width = Widht;
        height = Height;
        speed = sf::Vector2f(Speed_X, Speed_Y);
        File = F;
        //---
        image.loadFromFile("image/" + File);
        image.createMaskFromColor(sf::Color(0,0,0));
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setPosition(wx, wy);

        // Устанавливаем центр спрайта в центр изображения
        sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

        
    }

    void MovePlanet(sf::RenderWindow& window, float time) {
        //Планируется, чтобы планеты и звезды не вылетали за пределы окна
        //Постоянно меняются координаты одного объекта 
        wx += speed.x * time;
        wy += speed.y * time;
        sprite.rotate(0.05);

        //Проверяем, что если объект улетает за край карты по Ох
        if (wx <= 100 || wx + 100 >= WIDHT) {
            speed.x = -speed.x;
        }
        //Проверяем, что если объект улетает за край карты по Оy
        if (wy <= 100 || wy + 100 >= HEIGHT) {
            speed.y = -speed.y;
        }

        sprite.setPosition(wx, wy);
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDHT, HEIGHT), "My window");


    //Создание переменных - планет
    ObjectatMenu planet1(120, 120, 200, 200, 0.1, 0.1, "planet1.png");
    ObjectatMenu planet2(300, 300, 200, 200, 0.4, 0.2, "planet2.png");
    ObjectatMenu planet3(600, 600, 220, 200, 0.3, 0.2, "planet3.png");

    //Создание переменных - звезд
    ObjectatMenu star1(120, 120, 200, 200, 0.2, 0.2, "star1.png");
    ObjectatMenu star2(300, 300, 200, 200, 0.2, 0.2, "star2.png");
    ObjectatMenu star3(600, 600, 220, 200, 0.2, 0.2, "star3.png");
    
    sf::Clock clock; //Объект класса Clock для обеспечения плавности игры (передвижения разных объектов)

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds(); //Дать прошедшее время в микросекундах
        clock.restart(); //Перезагружаем время
        time = time / 800; //Скорость игры (можно делить на что-то другое число) 

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        //Объявление объектов
        planet1.MovePlanet(window, time);
        window.draw(planet1.sprite);

        planet2.MovePlanet(window, time);
        window.draw(planet2.sprite);

        planet3.MovePlanet(window, time);
        window.draw(planet3.sprite);

        star1.MovePlanet(window, time);
        window.draw(star1.sprite);

        star2.MovePlanet(window, time);
        window.draw(star2.sprite);

        star3.MovePlanet(window, time);
        window.draw(star3.sprite);
        //Объявление объектов

        window.display();
    }

    return 0;
}

