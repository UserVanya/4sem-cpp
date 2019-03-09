#pragma once
#include <SFML/Graphics.hpp>
enum Action
{
	Stay,
	Right,
	Left,
	LeapForward,
	LeapBack,
	fall
};
const int AMOUNT_OF_LINES_ON_PICTURE = 3;
const int AMOUNT_OF_FRAMES_IN_LINE = 3;
const sf::Vector2f SHIFT(12, 24);
const float RADIUS = 36;
const int MAX_ANGEL = 150;
const float TIME_K = 800;
class Worm
{
private:
	int _lastDirection;
	bool _fall;
	bool _readyToGo;
	std::vector<sf::Vector2f> _variantsToGo;
	const float _VELOCITY = 1;
	sf::Vector2f _dir;
	sf::Image _image;
	sf::Texture _texture;
	std::vector<sf::Sprite> _sprite;
	sf::CircleShape _toRecognize;
	void _maskFromWhite();
	bool _isJumping;
	void _jumpBack(sf::RenderWindow& window, const float& time, const sf::Image& map);
	void _jumpForward(sf::RenderWindow& window, const float& time, const sf::Image& map);
	void _goOneSide(sf::RenderWindow& window, const float& time, const sf::Image& map, const int& reverse);
	void _stay(sf::RenderWindow& window, const float& time, const sf::Image& map);
	float _stayingFrame;
	float _runningFrame;
	void _setVariantsToGo();
	
public:
	Worm();
	~Worm();
	bool wormWillOnMap();
	Worm(std::string pathToImage, sf::Vector2f size);
	void update(sf::RenderWindow& window, int direction, const float& time, const sf::Image& map);
	void draw(sf::RenderWindow& window, sf::Sprite& toDraw);
	void draw(sf::RenderWindow& window);
};

