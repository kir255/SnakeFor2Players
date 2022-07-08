#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <string>
using namespace sf;

const int N = 40, M = 30;
const int size = 16;
int w = size * (1+N);
int h = size * (1+M);
int close = 0;
int dir, num = 4, num2 = 4, dir2=4;
bool Ismenu = true;
std::string wholose = "Никто не выиграл";

struct Snake_one
{
    int x, y;
}  s[1000];

struct Snake_two
{
    int x2, y2;
}  s2[1000];

struct Fruit_1
{
    int x, y;
} f;

struct Fruit_2
{
    int x, y;
} f2;


void New_Game() {
    num = 4, num2 = 4; dir2 = 4; dir = 0;
    for (int i = num; i >= 0; --i) {
        s2[i].x2 = N;
        s2[i].y2 = M;
        s[i].x = 0;
        s[i].y = 0;
    }
}

void Tick()
{

    //хвост передвигается
    for (int i = num; i > 0; --i)
    {
        s[i].x = s[i - 1].x; s[i].y = s[i - 1].y;
    }
    for (int i = num2; i > 0; --i)
    {
        s2[i].x2 = s2[i - 1].x2; s2[i].y2 = s2[i - 1].y2;
    }

    //изменение движения
    if (dir == 0) s[0].y += 1;
    if (dir == 1) s[0].x -= 1;
    if (dir == 2) s[0].x += 1;
    if (dir == 3) s[0].y -= 1;

    if (dir2 == 7) s2[0].y2 += 1;
    if (dir2 == 5) s2[0].x2 -= 1;
    if (dir2 == 6) s2[0].x2 += 1;
    if (dir2 == 4) s2[0].y2 -= 1;

    //фруктики
    if ((s[0].x == f.x) && (s[0].y == f.y))
    {
        num++; f.x = rand() % N; f.y = rand() % M;
    }
    if ((s2[0].x2 == f.x) && (s2[0].y2 == f.y))
    {
        num2++; f.x = rand() % N; f.y = rand() % M;
    }

    if ((s[0].x == f2.x) && (s[0].y == f2.y))
    {
        num++; f2.x = rand() % N; f2.y = rand() % M;
    }
    if ((s2[0].x2 == f2.x) && (s2[0].y2 == f2.y))
    {
        num2++; f2.x = rand() % N; f2.y = rand() % M;
    }

    //заход за стены
    if (s[0].x > N) s[0].x = 0;  if (s[0].x < 0) s[0].x = N;
    if (s[0].y > M) s[0].y = 0;  if (s[0].y < 0) s[0].y = M;

    if (s2[0].x2 > N) s2[0].x2 = 0;  if (s2[0].x2 < 0) s2[0].x2 = N;
    if (s2[0].y2 > M) s2[0].y2 = 0;  if (s2[0].y2 < 0) s2[0].y2 = M;

    //победитель кто?
    if (s[0].x == s2[0].x2 && s[0].y == s2[0].y2) {
        close = 1; wholose = "Никто не выиграл("; return;
    }
    for (int i = 0; i < num2; i++)
        if (s[0].x == s2[i].x2 && s[0].y == s2[i].y2) {
            close = 1; wholose = "Второй выиграл!!!";
        }
    for (int i = 0; i < num; i++)
        if (s2[0].x2 == s[i].x && s2[0].y2 == s[i].y) {
            close = 1; wholose = "Первый выиграл!!!";
        }
}

void Menu() {
    RenderWindow menu(sf::VideoMode(800, 600), "Snakesss");

    Texture menu1, menu2;
    menu1.loadFromFile("images/menu_play.png");
    menu2.loadFromFile("images/menu_exit.png");

    Sprite menu_play(menu1);
    Sprite menu_exit(menu2);

    menu_play.setPosition(200, 230);
    menu_exit.setPosition(200, 330);
    menu_play.setColor(Color(255, 226, 142, 255));
    menu_exit.setColor(Color(255, 226, 142, 255));
    while (menu.isOpen()) {

        Event e;
        while (menu.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                menu.close();
            }
        }

        menu.clear(Color(129, 181, 221));
        if (IntRect(200, 230, 400, 110).contains(Mouse::getPosition(menu))) menu_play.setColor(Color(255, 226, 100, 200));
        else menu_play.setColor(Color(255, 226, 142, 255));
        if (IntRect(200, 330, 400, 110).contains(Mouse::getPosition(menu))) menu_exit.setColor(Color(255, 226, 100, 200));
        else menu_exit.setColor(Color(255, 226, 142, 255));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) menu.close();
       // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { Ismenu = false; menu.close(); }


        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (IntRect(200, 230, 400, 110).contains(Mouse::getPosition(menu))) { menu.close(); }
            if (IntRect(200, 330, 400, 110).contains(Mouse::getPosition(menu))) { Ismenu = false; menu.close(); }
        }

        menu.draw(menu_play);
        menu.draw(menu_exit);

        menu.display();
    }
    return;
}

void Lose() {
    RenderWindow window2(sf::VideoMode(800, 600), "win");
    while (window2.isOpen()) {

        Event e;
        while (window2.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window2.close();
        }

        Font font;
        font.loadFromFile("font/CyrilicOld.TTF");
        Text text("", font, 48);
        text.setStyle(Text::Bold);
        text.setFillColor(sf::Color::Red);
        text.setString(wholose);
        text.setPosition(24 * size, 24 * size);
        window2.draw(text);

        window2.display();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window2.close();
    }
    Menu();
}

int Game() {
    New_Game();

    srand(time(0));

    RenderWindow window(VideoMode(w, h), "Snake fight!");

    window.setFramerateLimit(120);


    Texture t1, t2, t3, t4, t5, t6, t7;
    t1.loadFromFile("images/white.png");
    t2.loadFromFile("images/red.png");
    t3.loadFromFile("images/green.png");
    t4.loadFromFile("images/банан.png");
    t5.loadFromFile("images/cherry.png");
    t6.loadFromFile("images/red_head.png");
    t7.loadFromFile("images/green_head.png");

    Sprite sprite1(t1);
    Sprite sprite2(t2);
    Sprite sprite3(t3);
    Sprite sprite4(t4);
    Sprite sprite5(t5);
    Sprite sprite6(t6);
    Sprite sprite7(t7);

    Clock clock;
    float timer = 0, delay = 0.1;
    //музыка
    SoundBuffer buffer;
    if (!buffer.loadFromFile("music/8_bit_first_sound.wav"))
        return -1;
    Sound sound;
    sound.setBuffer(buffer);
    Music music;
    if (!music.openFromFile("music/8_bit_main_music.wav"))
        return -1;
    music.setLoop(true); //зацикливание музыки
    sound.play();

    f.x = rand() % N;
    f.y = rand() % M;
    f2.x = rand() % N;
    f2.y = rand() % M;

    while (window.isOpen())
    {
        if (close == 1) { music.stop(); window.close(); Lose(); }
        window.clear();

        

        if (sound.getStatus()) music.play(); //музыка
        //поле
        for (int i = 0; i < N + 1; i++)
            for (int j = 0; j < M + 1; j++)
            {
                sprite1.setPosition(i * size, j * size);  window.draw(sprite1);
            }

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                window.close(); Ismenu = false;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Left) && (dir2 != 6)) dir2 = 5;
        if (Keyboard::isKeyPressed(Keyboard::Right) && (dir2 != 5)) dir2 = 6;
        if (Keyboard::isKeyPressed(Keyboard::Up) && (dir2 != 7)) dir2 = 4;
        if (Keyboard::isKeyPressed(Keyboard::Down) && (dir2 != 4)) dir2 = 7;

        if (Keyboard::isKeyPressed(Keyboard::A) && (dir != 2)) dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::D) && (dir != 1)) dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::W) && (dir != 0)) dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::S) && (dir != 3)) dir = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close(); Menu();
        }

        if (timer > delay) { timer = 0; Tick(); }

        //рисовка

        sprite5.setPosition(f.x * size, f.y * size);  window.draw(sprite5);
        sprite4.setPosition(f2.x * size, f2.y * size);  window.draw(sprite4);


        for (int i = 1; i < num2; i++)
        {
            sprite3.setPosition((s2[i].x2) * (size), (s2[i].y2) * (size));  window.draw(sprite3);
        }
        sprite7.setPosition(s2[0].x2 * size, s2[0].y2 * size);  window.draw(sprite7);
        for (int i = 1; i < num; i++)
        {
            sprite2.setPosition(s[i].x * size, s[i].y * size);  window.draw(sprite2);
        }
        sprite6.setPosition(s[0].x * size, s[0].y * size);  window.draw(sprite6);


        window.display();
    }
    return 0;
}

int main()
{
    Menu();
    while (Ismenu) {
        Game(); close = 0;
    }
    return 0;
}
