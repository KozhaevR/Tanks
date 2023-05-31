#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>

using namespace sf;

const int H = 18;
const int W = 32;
String TileMap[H] = {
    "BBBBBBBBBBBBBB0BB0BBBBBBBBBBBBBB",
    "B    B                  B      B",
    "B    B                  B      B",
    "B    B                         B",
    "B              B               B",
    "B              B               B",
    "B        B     B   BBBB        B",
    "B        B            B        B",
    "B        B            B        B",
    "B        B            B        B",
    "B        B            B        B",
    "B        BBBB    B    B        B",
    "B                B             B",
    "B                B             B",
    "B                         B    B",
    "B      B                  B    B",
    "B      B                  B    B",
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
};



/////////////////////////////////////////////// players collision   
bool collXL(int dx, int dy, int w) {
    for (int i = (dy + 1) / 50; i < (dy + w - 2) / 50; i++) {
        if (TileMap[i][dx / 50] == 'B') return(1);
        else {
            if (TileMap[i + 1][dx / 50] == 'B') return(1);
            else {
                if (TileMap[i + 2][dx / 50] == 'B') return(1);
                else return(0);
            }
        }

    }
}
bool collXR(int dx, int dy, int w) {
    for (int i = (dy + 1) / 50; i < (dy + w - 2) / 50; i++) {
        if (TileMap[i][(dx + 100) / 50] == 'B') return(1);
        else {
            if (TileMap[i + 1][(dx + 100) / 50] == 'B') return(1);
            else {
                if (TileMap[i + 2][(dx + 100) / 50] == 'B') return(1);
                else return(0);
            }
        }

    }
}
bool collYU(int dx, int dy, int w) {
    for (int j = (dx + 1) / 50; j < (dx + w) / 50; j++) {
        if (TileMap[dy / 50][j] == 'B') return(1);
        else {
            if (TileMap[dy / 50][j + 1] == 'B') return(1);
            else {
                if (TileMap[dy / 50][j + 2] == 'B') return(1);
                else return(0);
            }
        }

    }
}
bool collYD(int dx, int dy, int w) {
    for (int j = (dx + 1) / 50; j < (dx + w) / 50; j++) {
        if (TileMap[(dy + 100) / 50][j] == 'B') return(1);
        else {
            if (TileMap[(dy + 100) / 50][j + 1] == 'B') return(1);
            else {
                if (TileMap[(dy + 100) / 50][j + 2] == 'B') return(1);
                else return(0);
            }
        }

    }
}
/////////////////////////////////////////////// pkayers collision
/////////////////////////////////////////////// Bullets
class Bullet {
public:
    float x, y, dx, dy, w, h, pl;
    bool life, p1life, p2life;
    Texture bl;
    Sprite bul;
    Bullet(int X, int Y, int dir, int player) {
        x = X;
        y = Y;
        pl = player;
        if (dir == 1) dx = -0.3;
        else if (dir == 2) dx = 0.3;
        else dx = 0;

        if (dir == 3) dy = -0.3;
        else if (dir == 4) dy = 0.3;
        else dy = 0;

        w = h = 15;
        p1life = true;
        p2life = true;
        life = true;
        bl.loadFromFile("bullet.png");
        bul.setTexture(bl);
    }
    void update(float time, int x1, int y1, int x2, int y2) {
        x += dx * time;
        y += dy * time;


        for (int i = y / 50; i < (y + h) / 50; i++)
            for (int j = x / 50; j < (x + w) / 50; j++)
                if (TileMap[i][j] == 'B') {
                    dx = 0; dy = 0; life = false;
                }
        if (pl == 1)
            if (x > x1 && y > y1 && x < (x1 + 100) && y < (y1 + 100)) { life = false; p1life = false; }
        if (pl == 2)
            if (x > x2 && y > y2 && x < (x2 + 100) && y < (y2 + 100)) { life = false; p2life = false; }
        bul.setPosition(x, y);

    }
    void drawb(RenderWindow& window) {
        window.draw(bul);
    }
};

int main()
{
    std::list<Bullet*> bullets;
    std::list<Bullet*>::iterator it;
    RenderWindow window(VideoMode(1600, 900), "Pocket tanks!"); // Игровое окно

    Font font;
    if (!font.loadFromFile("Arial.ttf"))
    {
        // Обработка ошибки загрузки шрифта
        return -1;
    }
    Text scoreText;
    Text scoreText1;
    scoreText.setFont(font);
    scoreText1.setFont(font);
    scoreText.setCharacterSize(45);
    scoreText1.setCharacterSize(45);
    scoreText.setFillColor(sf::Color::Green);
    scoreText1.setFillColor(sf::Color::Red);
    int ws = 100;
    Texture t;
    t.loadFromFile("tank.png");
    Sprite s;
    s.setTexture(t);
    s.setTextureRect(IntRect(300, 0, 100, 100));
    s.setPosition(1400, 400);                        // начальная позиция второго игрока

    Texture t2;
    t2.loadFromFile("tank2.png");
    Sprite s2;
    s2.setTexture(t2);
    s2.setTextureRect(IntRect(100, 0, 100, 100));
    s2.setPosition(100, 400);                       // начальная позиция первого игрока


    Texture wall;                                   //Окружение
    wall.loadFromFile("briq.png");
    Sprite rectangle;
    rectangle.setTexture(wall);
    Texture ground;
    ground.loadFromFile("ground.png");
    Sprite rectangle2;
    rectangle2.setTexture(ground);
    Texture tp1won;
    tp1won.loadFromFile("p1won.png");
    Sprite sp1won;
    sp1won.setTexture(tp1won);
    sp1won.setPosition(0, 0);
    Texture tp2won;
    tp2won.loadFromFile("p2won.png");
    Sprite sp2won;
    sp2won.setTexture(tp2won);
    sp2won.setPosition(0, 0);
    int state1 = 1;
    int state2 = 2;
    bool endgame = false;
    int p1score = 0;
    int p2score = 0;
    Clock clock;
    while (window.isOpen() && endgame == false)
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 500;

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
                if (event.key.code == Keyboard::L)
                    bullets.push_back(new Bullet(s.getPosition().x + 43, s.getPosition().y + 43, state1, 2));  /////// Стрельба игрок 2
            if (event.type == Event::KeyPressed)
                if (event.key.code == Keyboard::V)
                    bullets.push_back(new Bullet(s2.getPosition().x + 43, s2.getPosition().y + 43, state2, 1));/////// Стрельба игрок 1
        }


        /////////////////////////////////////////////// Управление игрок 2
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            if (collXL(s.getPosition().x, s.getPosition().y, ws) == 0) s.move(-0.1 * time, 0);
            s.setTextureRect(IntRect(301, 0, 100, 100));
            state1 = 1;
        }
        else {
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                if (collXR(s.getPosition().x, s.getPosition().y, ws) == 0) s.move(0.1 * time, 0);
                s.setTextureRect(IntRect(100, 0, 100, 100));
                state1 = 2;
            }
            else {
                if (Keyboard::isKeyPressed(Keyboard::Up)) {
                    if (collYU(s.getPosition().x, s.getPosition().y, ws) == 0) s.move(0, -0.1 * time);
                    s.setTextureRect(IntRect(0, 0, 100, 100));
                    state1 = 3;
                }
                else {
                    if (Keyboard::isKeyPressed(Keyboard::Down)) {
                        if (collYD(s.getPosition().x, s.getPosition().y, ws) == 0) s.move(0, 0.1 * time);
                        s.setTextureRect(IntRect(200, 0, 100, 100));
                        state1 = 4;
                    }
                }
            }
        }
        /////////////////////////////////////////////// Управление игрок 1
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            if (collXL(s2.getPosition().x, s2.getPosition().y, ws) == 0) s2.move(-0.1 * time, 0);
            s2.setTextureRect(IntRect(301, 0, 100, 100));
            state2 = 1;
        }
        else {
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                if (collXR(s2.getPosition().x, s2.getPosition().y, ws) == 0) s2.move(0.1 * time, 0);
                s2.setTextureRect(IntRect(100, 0, 100, 100));
                state2 = 2;
            }
            else {
                if (Keyboard::isKeyPressed(Keyboard::W)) {
                    if (collYU(s2.getPosition().x, s2.getPosition().y, ws) == 0) s2.move(0, -0.1 * time);
                    s2.setTextureRect(IntRect(0, 0, 100, 100));
                    state2 = 3;
                }
                else {
                    if (Keyboard::isKeyPressed(Keyboard::S)) {
                        if (collYD(s2.getPosition().x, s2.getPosition().y, ws) == 0) s2.move(0, 0.1 * time);
                        s2.setTextureRect(IntRect(200, 0, 100, 100));
                        state2 = 4;
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
        for (it = bullets.begin(); it != bullets.end(); it++)
            (*it)->update(time, s.getPosition().x, s.getPosition().y, s2.getPosition().x, s2.getPosition().y);////////update пуль

        for (it = bullets.begin(); it != bullets.end();) {//Проверка жизни игрока 1
            Bullet* b = *it;
            if (b->p1life == false) {
                p2score++;
                if (p2score > 4) endgame = true;
                it = bullets.erase(it);
                s.setPosition(1400, 400);                 //возвращение на позиции после смерти
                s2.setPosition(100, 400);
                delete b;
            }
            else it++;
        }
        for (it = bullets.begin(); it != bullets.end();) {//Проверка жизни игрока 2
            Bullet* b = *it;
            if (b->p2life == false) {
                p1score++;
                if (p1score > 4) endgame = true;
                it = bullets.erase(it);
                s.setPosition(1400, 400);                 //возвращение на позиции после смерти
                s2.setPosition(100, 400);
                delete b;
            }
            else it++;
        }
        for (it = bullets.begin(); it != bullets.end();) {//Проверка жизни пули
            Bullet* b = *it;
            if (b->life == false) {
                it = bullets.erase(it);
                delete b;
            }
            else  it++;
        }
        std::string scoreString = std::to_string(p1score);
        std::string scoreString1 = std::to_string(p2score);
        scoreText.setString(scoreString);
        scoreText1.setString(scoreString1);
        scoreText.setPosition(862, 0);
        scoreText1.setPosition(712, 0);
        window.clear();
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (TileMap[i][j] == 'B') {
                    rectangle.setPosition(j * 50, i * 50);
                    window.draw(rectangle);
                }
                if (TileMap[i][j] == ' ') {
                    rectangle2.setPosition(j * 50, i * 50);
                    window.draw(rectangle2);
                }
            }
        }
        for (it = bullets.begin(); it != bullets.end(); it++) {
            (*it)->drawb(window);
        }
        window.draw(s);
        window.draw(s2);
        window.draw(scoreText);
        window.draw(scoreText1);
        window.display();
    }
    window.close();
    RenderWindow window2(VideoMode(1600, 900), "Results!");
    while (window2.isOpen()) {
        Event event2;
        while (window2.pollEvent(event2)) {
            if (event2.type == Event::Closed)
                window2.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) window2.close();
        window2.clear();
        if (p1score > p2score) {
            window2.draw(sp2won);
        }
        else window2.draw(sp1won);
        window2.display();
    }

    return 0;
}