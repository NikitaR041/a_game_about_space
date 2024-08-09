﻿#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

const int WIDHT = 1200;
const int HEIGHT = 800;

int isClickAgainTwo = 0; //isClickAgainTwo определяет нажата ли одна и та же кнопка два раза
int isClickAuthor = 0; //isClickAuthor определяет этап переключения между меню и автором
int isClickLevel = 0; //isClickLevel определяет этап переключения между меню и уровнями
int isEsc = 0; //isEsc определяет надата ли кнопка esc (по умолчанию, что нет)

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
        image.createMaskFromColor(sf::Color(0, 0, 0));
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
        sprite.rotate(0.05f);

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

//Класс, который представляет в себе объекты кнопок в меню(или в любых загрузочных моментах) 
//Возможно нужно будет использовать дочерние классы от этого класса - необходимо получить знания!
class Button {
private:
    int x, y, widht, height; //Координаты и размеры кнопок
    sf::Image image; //Загрузка изображения
    sf::Texture texture; //Добавление в объект 'Текстуры'
    sf::Sprite sprite; //Добавление в объект 'спрайта'

public:
    //Конструктор для кнопки
    Button(int x, int y, int widht, int height, sf::String File) : x(x), y(y), widht(widht), height(height) {
        //Выгружать картинку
        if (!image.loadFromFile("image/" + File)) {
            std::cout << "Error: Failed to load image from file" << '\n';
        }
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
    }

    void ButtonClickProcessing(sf::RenderWindow& window) {
        static bool wasMousePressed = false; // Сохраняет состояние кнопки мыши в прошлом кадре
        
        int isClick = 0;//isClick определяет какая кнопка будет нажата в меню игры
    
        //Возращаем белый цвет оригинальной объекту
        sprite.setColor(sf::Color::White);

        
        //Если пользователь наводится курсором мыши на определенную часть кнопки, то срабатывет смена цвета в золотистый цвет
        if (sf::IntRect(530, 370, 140, 60).contains(sf::Mouse::getPosition(window))) {
            sprite.setColor(sf::Color(255, 199, 7)); //spriteStart / 255,199,7
            isClick = 1;
        //    std::cout << isClick << '\n';
        }
        else if (sf::IntRect(530, 450, 140, 60).contains(sf::Mouse::getPosition(window))) {
            sprite.setColor(sf::Color(255, 199, 7)); //spriteLevel
            isClick = 2;
        //    std::cout << isClick << '\n';
        }
        else if (sf::IntRect(530, 530, 140, 60).contains(sf::Mouse::getPosition(window))) {
            sprite.setColor(sf::Color(255, 199, 7)); // spriteAuthor
            isClick = 3;
        //    std::cout << isClick << '\n';
        }
        
        //Обработка нажатия на кнопку 
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (wasMousePressed == 0) {
                if (isClick == 1) {
                    std::cout << "Game!" << '\n';
                    isClickAuthor = 0;
                    isClickLevel = 0;
                }
                if (isClick == 2) {
                    std::cout << "Level!" << '\n';
                    isClickAuthor = 0;
                    isClickLevel = 1;
                }
                if (isClick == 3) {
                    std::cout << "Author!" << '\n';
                    isClickLevel = 0;
                    //Далее тернарное условие - нужно для проверки повторного нажатия на од
                    isClickAgainTwo = (isClickAgainTwo == 0) ? 1 : 0;
                    isClickAuthor = isClickAgainTwo;
                    
                }
            }
            wasMousePressed = true; //Устанавливаем флаг на нажатие
        }
        else {
            wasMousePressed = false; //Сбрасываем флаг, когда кнопка не нажата
        }
        
        //Отображение каждого объекта кнопки
        window.draw(sprite);
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
//Функция по обновлению размера картинки при изменении окна
void UpdateDrawBackground(sf::Sprite& sprite1, sf::Sprite& sprite2, float time) {
    const float backgroundSpeed = -0.05f;

    sprite1.move(backgroundSpeed * time, 0);
    sprite2.move(backgroundSpeed * time, 0);

    if (sprite1.getPosition().x + sprite1.getGlobalBounds().width < 0) {
        sprite1.setPosition(sprite2.getPosition().x + sprite2.getGlobalBounds().width, 0);
    }

    if (sprite2.getPosition().x + sprite2.getGlobalBounds().width < 0) {
        sprite2.setPosition(sprite1.getPosition().x + sprite1.getGlobalBounds().width, 0);
    }
}


//Выгрузка картинки об авторе - название файла, текстура, спрайт и координаты картинки
void DrawAuthor(const std::string& File, sf::Texture& textureAboutAuthor, sf::Sprite& spriteAboutAuthor, int x, int y) {
    if (!textureAboutAuthor.loadFromFile(File)) {
        std::cout << "Mistake. The picture AboutAthot is not load!" << '\n';
        return;
    }
    //Объявляем спрайты и загружаем текстуры
    spriteAboutAuthor.setTexture(textureAboutAuthor);

    //Задаем позицию
    spriteAboutAuthor.setPosition(x, y);
}

//Выгрузка картинки с выбором уровня 
void DrawLevel(const std::string& File, sf::Texture& textureLevel, sf::Sprite& spriteLevel, int x, int y) {
    if (!textureLevel.loadFromFile(File)) {
        std::cout << "Mistake. The picture Level is not load!" << '\n';
        return;
    }
    //Объявляем спрайты и загружаем текстуры
    spriteLevel.setTexture(textureLevel);

    //Задаем позицию
    spriteLevel.setPosition(x, y);

}

//Функция по обновлению состояния - выбора уровня
void ProcessingLevel(sf::RenderWindow& window, sf::Sprite& spriteLevel) {
    //Здесь нужно прописать 
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDHT, HEIGHT), "My window");

    //Создание заднего фона
    sf::Texture texturebackground;
    sf::Sprite sprite1, sprite2;
    DrawBackground("image/MilkiWay.png", texturebackground, sprite1, sprite2);

    
    //Создание надписей для кнопок
    sf::Texture textureLevel, textureAboutAuthor;
    sf::Sprite spriteLevel, spriteAboutAuthor;
    DrawLevel("image/tabletLevel.png", textureLevel, spriteLevel, 0, 0);
    DrawAuthor("image/AboutAuthor.png", textureAboutAuthor, spriteAboutAuthor, 10, 370);
    

    //Создание надписей для кнопок
    Button button1(530, 370, 140, 60, "game.png");
    Button button2(530, 450, 140, 60, "level.png");
    Button button3(530, 530, 140, 60, "Author.png");

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

        //Отображение заднего фона - ленточный конвейер
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

        button1.ButtonClickProcessing(window);
        button2.ButtonClickProcessing(window);
        button3.ButtonClickProcessing(window);

        //Вывод автора или очистка
        if (isClickAuthor == 1) {
            window.draw(spriteAboutAuthor);
        }

        //Вывод уровней или очистка
        if (isClickLevel == 1) {
            window.draw(spriteLevel);
            //Тернарная проврека нужна для закрытия окна-уровней
            isClickLevel = (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) ? 1 : 0;
        }
        //Объвление название кнопок
        

        window.display();
    }

    return 0;
}

/*
    Может быть позже отделить загрузки различных объектов в отдельную функцию, а позже все различные функции положить в отдельный файл и загружать их здесь
*/