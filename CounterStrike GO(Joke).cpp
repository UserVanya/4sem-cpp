#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <map>
using namespace sf;
bool TextureInWindow(Texture& texture, Sprite& sprite, RenderWindow& window)
{
	const float Pi = 3.14159f;
	Vector2f s = sprite.getPosition();
	Vector2u w = window.getSize();
	Vector2u t = texture.getSize();
	t.x *= sprite.getScale().x;
	t.y *= sprite.getScale().y;
	float angle = sprite.getRotation() / 180 * Pi;
	Vector2f ul = s, ur(s.x + t.x * cos(angle), s.y + t.x * sin(angle));
	Vector2f dl(s.x - t.y * sin(angle), s.y + t.y * cos(angle)), dr(dl.x + t.x * cos(angle), dl.y + t.y * sin(angle));
	bool left = (dl.x < 0) || (ul.x < 0) || (ur.x < 0) || (dr.x < 0);
	bool up = (dl.y < 0) || (ul.y < 0) || (ur.y < 0) || (dr.y < 0);
	bool right = (dl.x > w.x) || (ul.x > w.x) || (ur.x > w.x) || (dr.x > w.x);
	bool down = (dl.y > w.y) || (ul.y > w.y) || (ur.y > w.y) || (dr.y > w.y);
	if (left || right || up || down) return false;
	else return true;
}
class Auxillary
{
public:
	bool inWindow;
	Sprite x;
	Vector2f v;
	Texture Tbullet;
	Auxillary()
	{
		Tbullet.loadFromFile("bullet.jpg");
		x.setScale(0.1, 0.1);
		inWindow = false;
		v.x = 0;
		v.y = 0;
	}
};
int findFree(std::vector<Auxillary>& bullet)
{
	int i;
	for (i = 0; i < bullet.size(); i++) if (!bullet[i].inWindow) break;
	return i;
}

int main()
{
	const float gunLevel = 0.3;
	const int MaxBullets = 1000;
	Texture Tterrorist;
	Texture Tbullet;
	Tterrorist.loadFromFile("terrorist.jpg");
	Sprite terrorist(Tterrorist);
	terrorist.setPosition(600, 200);
	Tbullet.loadFromFile("bullet.jpg");
	Sprite bullet;
	bullet.setTexture(Tbullet);
	bullet.setScale(0.1, 0.1);
	RenderWindow window(VideoMode(1350, 600), "SFMLworks");
	const float Pi = 3.14159f;
	Sprite savePos = terrorist;
	std::vector <Auxillary> isBullet;
	while (window.isOpen())
	{
		Event event;
		Vector2i m = Mouse::getPosition(window);
		Vector2f t = terrorist.getPosition();
		Vector2f d = (Vector2f)m - t;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			if (Keyboard::isKeyPressed(Keyboard::Left)) terrorist.move(-5, 0);
			if (Keyboard::isKeyPressed(Keyboard::Right)) terrorist.move(5, 0);
			if (Keyboard::isKeyPressed(Keyboard::Up)) terrorist.move(0, -5);
			if (Keyboard::isKeyPressed(Keyboard::Down)) terrorist.move(0, 5);
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				if (isBullet.size() < MaxBullets) isBullet.push_back(Auxillary());
				int number = findFree(isBullet);
				float norm = sqrt(d.x * d.x + d.y * d.y);
				isBullet[number].x.setTexture(Tbullet);
				float x = terrorist.getPosition().x + Tterrorist.getSize().x * cos(Pi * terrorist.getRotation() / 180);
				float y = terrorist.getPosition().y + Tterrorist.getSize().x * sin(Pi * terrorist.getRotation() / 180)
					+ Tterrorist.getSize().y * gunLevel;
				isBullet[number].x.setPosition(x, y);
				isBullet[number].x.setScale(0.05, 0.05);
				isBullet[number].v = d / (norm);
				isBullet[number].inWindow = true;
				isBullet[number].x.setRotation(90 + terrorist.getRotation());
			}
		} 
		terrorist.setRotation(90 - atan2f(d.x, d.y) * 180 / Pi);
		if(TextureInWindow(Tterrorist, terrorist, window)) savePos = terrorist;
		else terrorist = savePos;
		window.clear(Color::White);
		for (int i = 0; i < (int)isBullet.size(); i++)
		{
			isBullet[i].inWindow = TextureInWindow(isBullet[i].Tbullet, isBullet[i].x, window);
			if (isBullet[i].inWindow)
			{
				isBullet[i].x.move(isBullet[i].v);
				window.draw(isBullet[i].x);
			}
			else isBullet[i].inWindow = false;
		}
		window.draw(terrorist);
		window.display();
	}
	return 0;
}
