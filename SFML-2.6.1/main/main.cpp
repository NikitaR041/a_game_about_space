#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

const int WIDHT = 1200;
const int HEIGHT = 800;

//Класс, который представляет в себе объекты звезд и планет
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
        if (wx <= 50 || wx + 50 >= WIDHT) {
            speed.x = -speed.x;
        }
        //Проверяем, что если объект улетает за край карты по Оy
        if (wy <= 50 || wy + 50 >= HEIGHT) {
            speed.y = -speed.y;
        }

        sprite.setPosition(wx, wy);
    }

};

//Функции по отображению заднего фона - ленточный конвейер
void DrawBackground(const std::string& File, sf::Texture& texture, sf::Sprite& sprite1, sf::Sprite& sprite2) {
    //Загружаем изображение в текстуру через условие
    if (!texture.loadFromFile(File)) {
        std::cout << "Mistake. The background is not loaded!" << '\n';
        return;
    }
    //Объявляем спрайты и загружаем текстуры
    sprite1.setTexture(texture);
    sprite2.setTexture(texture);
    
    //Задаем позицию
    sprite1.setPosition(0, 0);
    sprite2.setPosition(WIDHT, 0);

    //Масштабируем спрайты для заполнения его окна
    sprite1.setScale(WIDHT / sprite1.getGlobalBounds().width, HEIGHT / sprite1.getGlobalBounds().height);
    sprite2.setScale(WIDHT / sprite2.getGlobalBounds().width, HEIGHT / sprite2.getGlobalBounds().height);
}
void UpdateDrawBackground(sf::Sprite& sprite1, sf::Sprite& sprite2, float time) {
    const float backgroundSpeed = -0.05;

    sprite1.move(backgroundSpeed * time, 0);
    sprite2.move(backgroundSpeed * time, 0);

    if (sprite1.getPosition().x + sprite1.getGlobalBounds().width < 0) {
        sprite1.setPosition(sprite2.getPosition().x + sprite2.getGlobalBounds().width, 0);
    }

    if (sprite2.getPosition().x + sprite2.getGlobalBounds().width < 0) {
        sprite2.setPosition(sprite1.getPosition().x + sprite1.getGlobalBounds().width, 0);
    }
}

//Функции по отображению кнопок и взаимодействия с ними
void DrawButton(const std::string& File, sf::Texture& texture, sf::Sprite& sprite, int x, int y) {;
    //Загружаем изображение в текстуру через условие
    if (!texture.loadFromFile(File)) {
        std::cout << "Mistake. The background is not loaded!" << '\n';
        return;
    }
    //Объявляем спрайты и загружаем текстуры
    sprite.setTexture(texture);

    //Задаем позицию
    sprite.setPosition(x, y);
 }

//Взаимодействие с конпками
void ButtonCliclProcessing(sf::RenderWindow& window, sf::Sprite& spriteStart, sf::Sprite& spriteLevel, sf::Sprite& spriteAuthor, int x, int y) {
    //Возращаем белый цвет оригинальной картинке
    spriteStart.setColor(sf::Color::White);
    spriteLevel.setColor(sf::Color::White);
    spriteAuthor.setColor(sf::Color::White);

    //Если пользователь наводится курсором мыши на определенную часть кнопки, то срабатывет смена цвета в золотистый цвет
    if (sf::IntRect(530, 370, 140, 60).contains(sf::Mouse::getPosition(window))) {
        spriteStart.setColor(sf::Color(255, 199, 7));
    }
    if (sf::IntRect(530, 450, 140, 60).contains(sf::Mouse::getPosition(window))) {
        spriteLevel.setColor(sf::Color(255, 199, 7));
    }
    if (sf::IntRect(530, 530, 140, 60).contains(sf::Mouse::getPosition(window))) {
        spriteAuthor.setColor(sf::Color(255, 199, 7));
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDHT, HEIGHT), "My window");

    //Создание заднего фона
    sf::Texture texturebackground;
    sf::Sprite sprite1, sprite2;
    DrawBackground("image/MilkiWay.png", texturebackground, sprite1, sprite2);

    //Создание надписей для кнопок
    sf::Texture textureStart, textureLevel, textureAuthor;
    sf::Sprite spriteStart, spriteLevel, spriteAuthor;
    DrawButton("image/game.png", textureStart, spriteStart, 530, 370);
    DrawButton("image/level.png", textureLevel, spriteLevel, 530, 450);
    DrawButton("image/Author.png", textureAuthor, spriteAuthor, 530, 530);


    //Создание переменных - планет
    ObjectatMenu planet1(120, 120, 100, 100, 0.1, 0.1, "planet1.png");
    ObjectatMenu planet2(300, 300, 100, 100, 0.4, 0.2, "planet2.png");
    ObjectatMenu planet3(600, 600, 120, 100, 0.3, 0.2, "planet3.png");

    //Создание переменных - звезд
    ObjectatMenu star1(120, 120, 50, 50, 0.2, 0.2, "star1.png");
    ObjectatMenu star2(300, 300, 50, 50, 0.2, 0.2, "star2.png");
    ObjectatMenu star3(600, 600, 52, 50, 0.2, 0.2, "star3.png");

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

        window.clear();

        UpdateDrawBackground(sprite1, sprite2, time);
        window.draw(sprite1);
        window.draw(sprite2);

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

        //Объвление название кнопок
        ButtonCliclProcessing(window, spriteStart, spriteLevel, spriteAuthor, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        window.draw(spriteStart);

        //ButtonCliclProcessing(window, spriteLevel, 530, 450);
        window.draw(spriteLevel);
        
        //ButtonCliclProcessing(window, spriteAuthor, 530, 530);
        window.draw(spriteAuthor);
        //Объвление название кнопок

        window.display();
    }

    return 0;
}

/*
    Может быть позже отделить загрузки различных объектов в отдельную функцию, а позже все различные функции положить в отдельный файл и загружать их здесь
*/