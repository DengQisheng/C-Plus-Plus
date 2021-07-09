#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

#include "Game.h"
#include "GameScreen.h"
#include "GameOverScreen.h"

using namespace sfSnake;

GameOverScreen::GameOverScreen(std::size_t score) : score_(score) // 构造函数，输入参数为分数，实现结束界面的设置
{
	font_.loadFromFile("Fonts/game_over.ttf");
	text_.setFont(font_);
	text_.setString("Your score: " + std::to_string(score) + "!" + "\n\nPress [SPACE] to retry" + "\n\nPress [ESC] to quit");
	text_.setFillColor(sf::Color::Red);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 2);
}

void GameOverScreen::handleInput(sf::RenderWindow &window) // 退出或重新开始游戏
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		Game::Screen = std::make_shared<GameScreen>(); // 返回至GameScreen界面
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
}

void GameOverScreen::update(sf::Time delta) // 无刷新操作，预留游戏升级的位置
{
}

void GameOverScreen::render(sf::RenderWindow &window) // 窗口投影
{
	window.draw(text_);
}