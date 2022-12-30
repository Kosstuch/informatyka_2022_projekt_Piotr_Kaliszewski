#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int main()
{
    srand(time(0));
    RenderWindow app(VideoMode(520, 450), "Arkanoid!");
    app.setFramerateLimit(60);
    // �aduj tekstury
    Texture t1, t2, t3, t4;
    t1.loadFromFile("images/block01.png");
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/ball.png");
    t4.loadFromFile("images/paddle.png");

    // Ustaw sprite
    Sprite sBackground(t2), sBall(t3), sPaddle(t4);
    sPaddle.setPosition(300, 440);

    // �aduj tekstury przycisk�w menu
    Texture tPlayButton, tExitButton;
    tPlayButton.loadFromFile("images/play_button.png");
    tExitButton.loadFromFile("images/exit_button.png");

    // Ustaw sprite przycisk�w menu
    Sprite sPlayButton(tPlayButton), sExitButton(tExitButton);
    sPlayButton.setPosition(200, 200);
    sExitButton.setPosition(200, 300);

    // Ustaw sprite klock�w
    Sprite block[1000];
    int n = 0;
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
        {
            block[n].setTexture(t1);
            block[n].setPosition(i * 43, j * 20);
            n++;
        }

    // Ustaw zmienne kulki
    float dx = 6, dy = 5;
    float x = 300, y = 300;
    float speed = 0.5;
    x += dx * speed;
    y += dy * speed;

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();

            // Sprawd�, czy zosta� naci�ni�ty przycisk myszy
            if (e.type == Event::MouseButtonPressed)
            {
                // Sprawd�, czy zosta� naci�ni�ty przycisk Play
                if (sPlayButton.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y))
                {
                    // Gra zaczyna si�, wi�c ustaw zmienn� gameStarted na true
                    bool gameStarted = true;
                    // Uruchom p�tl� gry
                    while (gameStarted)
                    {
                        Event e;
                        while (app.pollEvent(e))
                        {
                            if (e.type == Event::Closed)
                            {
                                app.close();
                                gameStarted = false;
                            }
                        }

                        // Poruszaj kulk�
                        x += dx * speed;
                        y += dy * speed;

                        // Sprawd� kolizje z klockami
                        for (int i = 0; i < n; i++)
                            if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
                            {
                                block[i].setPosition(-100, 0); dx = -dx;
                            }

                        // Sprawd� kolizje z ramk�
                        if (x < 0 || x>520)  dx = -dx;
                        if (y < 0 || y>450)  dy = -dy;

                        // Steruj paletk� gracza
                        if (Keyboard::isKeyPressed(Keyboard::Right)) sPaddle.move(6, 0);
                        if (Keyboard::isKeyPressed(Keyboard::Left)) sPaddle.move(-6, 0);
                        // Sprawd� kolizj� z paletk� gracza
                        if (FloatRect(x, y, 12, 12).intersects(sPaddle.getGlobalBounds())) dy = -(rand() % 5 + 2);

                        // Wyjd� z gry, je�li gracz naci�nie klawisz Escape
                        if (Keyboard::isKeyPressed(Keyboard::Escape))
                        {
                            app.close();
                            gameStarted = false;
                        }

                        // Zmniejsz lub zwi�ksz pr�dko�� gry, je�li gracz naci�nie klawisz S
                        if (Keyboard::isKeyPressed(Keyboard::S)) speed = 0.5;
                        if (Keyboard::isKeyPressed(Keyboard::S) && speed < 1) speed = 1;

                        sBall.setPosition(x, y);

                        // Wy�wietl elementy na ekranie
                        app.clear();
                        app.draw(sBackground);
                        app.draw(sBall);
                        app.draw(sPaddle);
                        for (int i = 0; i < n; i++)
                            app.draw(block[i]);
                        app.display();
                    }
                }
                // Sprawd�, czy zosta� naci�ni�ty przycisk Exit
                else if (sExitButton.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y))
                {
                    // Zako�cz program
                    app.close();
                }
            }
        }

        // Wy�wietl elementy na ekranie
        app.clear();
        app.draw(sBackground);
        app.draw(sPlayButton);
        app.draw(sExitButton);
        app.display();
    }
    return 0;
}
