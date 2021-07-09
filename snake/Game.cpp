#include <SFML/Graphics.hpp>

#include <memory>

#include "MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 10.f); // 刷新每帧的时间

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>(); // 初始界面为Menu界面

Game::Game() : window_(sf::VideoMode(Game::Width, Game::Height), "sfSnake")
{
	bgMusic_.openFromFile("Music/bg_music.wav"); // 打开音乐文件
	bgMusic_.setLoop(true);						 // 循环播放
	bgMusic_.play();							 // 播放音乐

	background_.setPosition(sf::Vector2f(0, 0));				  // 设定背景位置
	background_.setFillColor(sf::Color(211, 211, 211));			  // 设定背景颜色
	background_.setSize(sf::Vector2f(Game::Width, Game::Height)); // 设定背景大小
}

void Game::handleInput()
{
	sf::Event event;

	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window_.close(); // 关闭窗口的操作
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		background_.setFillColor(sf::Color(211, 211, 211)); // 白色背景
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		background_.setFillColor(sf::Color(20, 20, 20)); // 黑色背景
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		background_.setFillColor(sf::Color(210, 180, 140)); // 褐色背景

	Game::Screen->handleInput(window_); // 转移至其他Screen的handleInput方法
}

void Game::update(sf::Time delta)
{
	Game::Screen->update(delta); // 转移至其他Screen的update方法
}

void Game::render()
{
	window_.clear();
	window_.draw(background_);	 // 绘制背景
	Game::Screen->render(window_); // 转移至其他Screen的render方法
	window_.display();
}

void Game::run() // 主程序运行入口，由main函数调用
{
	sf::Clock clock;							   // 计时对象
	sf::Time timeSinceLastUpdate = sf::Time::Zero; // 更新时间差，初始值为0

	while (window_.isOpen()) // 窗口打开时
	{
		sf::Time delta = clock.restart(); // 返回操作时间差
		timeSinceLastUpdate += delta;

		while (timeSinceLastUpdate > Game::TimePerFrame) // 当更新时间差大于更新每帧的时间
		{
			timeSinceLastUpdate -= TimePerFrame;
			handleInput();		  // 处理键盘或鼠标的操作
			update(TimePerFrame); // 更新每帧
		}

		render(); // 渲染画布
	}
}