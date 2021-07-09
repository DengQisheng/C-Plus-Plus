#include <SFML/Graphics.hpp>

#include <cmath>
#include <random>
#include <vector>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"

using namespace sfSnake;

const int GameScreen::InitialQuantity = 12; // 初始水果数量

GameScreen::GameScreen() : snake_() // 构造函数，使用Snake类的构造函数创建一条蛇
{
	constructGrid(); // 绘制网格线
}

void GameScreen::handleInput(sf::RenderWindow &window) // 对蛇进行键盘鼠标操作
{
	snake_.handleInput(window); // 转移至Snake类的handleInput方法

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) // 实现退出功能
	{
		sf::sleep(sf::seconds(0.5f));									   // 画面暂停
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize()); // 退出游戏，切换至GameOverScreen界面
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) // 实现网格功能
	{
		if (!displayGrid_) // 未显示网格状态
		{
			displayGrid_ = true; // 显示网格
		}
		else // 显示网格状态
		{
			displayGrid_ = false; // 取消显示网格
		}
	}
}

void GameScreen::update(sf::Time delta) // 刷新每帧界面
{
	if (GameScreen::Initial) // 初始化水果界面
	{
		std::vector<sf::Color> colors_{sf::Color::Red, sf::Color::Blue,
									   sf::Color::Green, sf::Color(128, 42, 42), sf::Color(128, 128, 128)}; // 红色0，蓝色1，绿色2，棕色3，灰色4

		static std::default_random_engine engine_(time(NULL));			 // 随机数引擎
		static std::uniform_int_distribution<int> rgbDistribution(0, 2); // 红蓝绿随机数
		static std::uniform_int_distribution<int> bbDistribution(3, 4);  // 棕灰随机数

		for (int i = 0; i != (int)(GameScreen::InitialQuantity * 0.75) - 1; ++i)
		{
			generateFruit(colors_.at(rgbDistribution(engine_))); // 初始化红蓝绿水果
		}

		for (int i = (int)(GameScreen::InitialQuantity * 0.75) - 1; i != GameScreen::InitialQuantity; ++i)
		{
			generateFruit(colors_.at(bbDistribution(engine_))); // 初始化棕灰水果
		}

		GameScreen::Initial = false;
	}

	snake_.update(delta);				 // 更新蛇snake的状态，转移至Snake类的update方法
	snake_.checkFruitCollisions(fruit_); // 检查水果的情况并储存吃掉水果的颜色

	if (fruit_.size() < GameScreen::InitialQuantity) // 当水果数小于初始水果数量时刷出新的水果
		generateFruit(snake_.getColorFromPickUpColor());

	if (snake_.hitSelf()) // 判断有没有碰上自己，碰上则游戏结束，跳转至GameOver界面
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}

void GameScreen::render(sf::RenderWindow &window) // 渲染画布
{
	if (displayGrid_) // 渲染网格
	{
		for (auto rowGrid : rowGrid_) // 渲染横向网格
			window.draw(rowGrid);
		for (auto colGrid : colGrid_) // 渲染纵向网格
			window.draw(colGrid);
	}

	snake_.render(window); // 渲染蛇

	for (auto fruit : fruit_) // 渲染水果
		fruit.render(window);
}

void GameScreen::generateFruit(sf::Color color) // 修改: 生成随机颜色的水果
{
	static std::default_random_engine engine_(time(NULL));										  // 使用随机引擎生成水果，time(NULL)为随机数种子
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Width);   // 水果的水平坐标
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Height); // 水果的垂直坐标

	fruit_.push_back(Fruit(sf::Vector2f(10 * trunc(xDistribution(engine_) / 10) + 5, 10 * trunc(yDistribution(engine_) / 10) + 5), color)); // 保存在存储fruit的vector中
}

void GameScreen::constructGrid() // 绘制网格线
{
	sf::RectangleShape rowGrid; // 水平直线
	rowGrid.setSize(sf::Vector2f(Game::Width - SnakeNode::Width, 1.f));  // 水平直线大小
	rowGrid.setFillColor(sf::Color(105, 105, 105));  // 水平直线颜色

	sf::RectangleShape colGrid; // 垂直直线
	colGrid.setSize(sf::Vector2f(1.f, Game::Height - SnakeNode::Height));  // 垂直直线大小
	colGrid.setFillColor(sf::Color(105, 105, 105));  // 垂直直线颜色

	for (int rowOffset = 0; rowOffset != Game::Height; rowOffset += SnakeNode::Height)
	{
		rowGrid.setPosition(sf::Vector2f(SnakeNode::Height / 2, rowOffset + SnakeNode::Height / 2)); // 水平直线位置
		rowGrid_.push_back(rowGrid); // 水平网格线
	}

	for (int colOffset = 0; colOffset != Game::Width; colOffset += SnakeNode::Width)
	{
		colGrid.setPosition(sf::Vector2f(colOffset + SnakeNode::Width / 2, SnakeNode::Width / 2)); // 垂直直线位置
		colGrid_.push_back(colGrid); // 垂直网格线
	}

	// sf::RectangleShape rowGrid; // 水平直线
	// rowGrid.setSize(sf::Vector2f(Game::Width - 10, 1.f));  // 水平直线大小
	// rowGrid.setFillColor(sf::Color(105, 105, 105));  // 水平直线颜色

	// sf::RectangleShape colGrid; // 垂直直线
	// colGrid.setSize(sf::Vector2f(1.f, Game::Height - 10));  // 垂直直线大小
	// colGrid.setFillColor(sf::Color(105, 105, 105));  // 垂直直线颜色

	// for (int rowOffset = 0; rowOffset != Game::Height; rowOffset += 10)
	// {
	// 	rowGrid.setPosition(sf::Vector2f(5, rowOffset + 5)); // 水平直线位置
	// 	rowGrid_.push_back(rowGrid); // 水平网格线
	// }

	// for (int colOffset = 0; colOffset != Game::Width; colOffset += 10)
	// {
	// 	colGrid.setPosition(sf::Vector2f(colOffset + 5, 5)); // 垂直直线位置
	// 	colGrid_.push_back(colGrid); // 垂直网格线
	// }
}