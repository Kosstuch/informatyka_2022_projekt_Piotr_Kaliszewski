#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

class Player
{
private:
    int score;

public:
    Player() : score(0) {}

    void addScore(int points) { score += points; }
    int getScore() const { return score; }
};

int main()
{
    srand(time(0));
    RenderWindow app(VideoMode(1366, 768), "Arkanoid!");
    app.setFramerateLimit(60);
    // �aduj tekstury
    Texture t1, t2, t3, t4;
    t1.loadFromFile("images/block01.png");
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/ball.png");
    t4.loadFromFile("images/paddle.png");

    // Ustaw sprite
    Sprite sBackground(t2), sBall(t3), sPaddle(t4);

    Vector2u windowSize = app.getSize();
    FloatRect paddleBounds = sPaddle.getLocalBounds();
    float paddleY = windowSize.y - paddleBounds.height;
    sPaddle.setPosition(300, paddleY-20);

    // �aduj tekstury przycisk�w menu
    Texture tPlayButton, tExitButton;
    tPlayButton.loadFromFile("images/play_button.png");
    tExitButton.loadFromFile("images/exit_button.png");

    // Ustaw sprite przycisk�w menu
    Sprite sPlayButton(tPlayButton), sExitButton(tExitButton);
    sPlayButton.setPosition(730, 300);
    sExitButton.setPosition(730, 400);

    // Ustaw sprite klock�w
    Sprite block[1000];
    int n = 0;
    for (int i = 1; i <= 30; i++)
        for (int j = 1; j <= 10; j++)
        {
            block[n].setTexture(t1);
            block[n].setPosition(i * 43, j * 20);
            n++;
        }

    // Ustaw zmienne kulki
    float dx = 8, dy = 6;
    float x = 500, y = 500;
    float speed = 0.5;
    x += dx * speed;
    y += dy * speed;

    Player player;
    Font font;
    font.loadFromFile("images/arial.ttf"); // �aduj czcionk� z pliku
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(Color::Black);
    scoreText.setPosition(100, 700);

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
                            if (FloatRect(x + 10, y + 10, 20, 20).intersects(block[i].getGlobalBounds()))
                            {
                                block[i].setPosition(-100, 0); dx = -dx;
                                player.addScore(1); // Dodaj 1 punkt do wyniku gracza po zniszczeniu bloku
                            }
                        scoreText.setString("Score: " + std::to_string(player.getScore()));

                        // Sprawd� kolizje z ramk�
                        if (x < 0 || x>1366)  dx = -dx;
                        if (y < 0 || y>768)  dy = -dy;

                        // Steruj paletk� gracza
                        if (Keyboard::isKeyPressed(Keyboard::Right)) sPaddle.move(18, 0);
                        if (Keyboard::isKeyPressed(Keyboard::Left)) sPaddle.move(-18, 0);
                        // Sprawd� kolizj� z paletk� gracza
                        if (FloatRect(x, y, 40, 40).intersects(sPaddle.getGlobalBounds())) dy = -(rand() % 5 + 2);

                        // Wyjd� z gry, je�li gracz naci�nie klawisz Escape
                        if (Keyboard::isKeyPressed(Keyboard::Escape))
                        {
                            app.close();
                            gameStarted = false;
                        }

                        // Zmniejsz lub zwi�ksz pr�dko�� gry, je�li gracz naci�nie klawisz S
                        if (Keyboard::isKeyPressed(Keyboard::W) && speed < 2) speed += 0.1;
                        if (Keyboard::isKeyPressed(Keyboard::S) && speed > 0.2) speed -= 0.1;

                        sBall.setPosition(x, y);

                        // Wy�wietl elementy na ekranie
                        app.clear();
                        app.draw(sBackground);
                        app.draw(sBall);
                        app.draw(scoreText);
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
