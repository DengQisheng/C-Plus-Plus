#include <SFML/Graphics.hpp>
#include<iostream>
#include <cmath>
#include <memory>
#include <random>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 5; // 初始化大小为5

Snake::Snake() : direction_(Direction::Up), hitSelf_(false) // 初始方向为上，自身碰撞为false
{
	initNodes(); // 创建一条初始化的蛇

	pickupBuffer_.loadFromFile("Sounds/pickup.wav"); // 打开捡起水果的音乐的文件
	pickupSound_.setBuffer(pickupBuffer_);			 // 捡起水果的声效设置
	pickupSound_.setVolume(30);						 // 声量控制

	dieBuffer_.loadFromFile("Sounds/die.wav"); // 死亡的音乐的文件
	dieSound_.setBuffer(dieBuffer_);		   // 死亡的声效设置
	dieSound_.setVolume(50);				   // 声量控制
}

void Snake::initNodes() // 蛇的初始形态
{
	nodes_.push_back(SnakeNode(
		head_,
		sf::Vector2f(Game::Width / 2 - SnakeNode::Width / 2,
					 Game::Height / 2 - SnakeNode::Height / 2))); // 创建蛇头

	for (int i = 0; i < Snake::InitialSize - 1; ++i) // 全蛇长度为InitialSize，位置为屏幕中央
	{
		nodes_.push_back(SnakeNode(
			sf::Vector2f(Game::Width / 2 - SnakeNode::Width / 2,
						 Game::Height / 2 + SnakeNode::Height / 2 + SnakeNode::Height * (i + 1)))); // 创建蛇身
	}
}

void Snake::handleInput(sf::RenderWindow &window) // 键盘和鼠标操作改变蛇的位置
{
	// 实现暂停功能
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) // 按下P键暂停，再次按下P键结束暂停
	{
		if (!pause_) // 处理运行状态
		{
			pause_ = true; // 处于暂停状态
		}
		else // 处理暂停状态
		{
			pause_ = false; // 结束暂停状态
		}
	}
	// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) // 按下R键结束暂停
	// {
	// 	pause_ = false; // 结束暂停状态
	// }

	if (!pause_) // 防止暂停时进行其他操作
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(window); // 鼠标光标的位置，注意要使用相对坐标
			sf::Vector2f snakePosition = nodes_.at(0).getPosition(); // 蛇头的位置
			sf::Vector2f length = mousePosition - snakePosition;	// 方向差向量

			if (fabs(length.x) > 5.f || fabs(length.y) > 5.f) // 若方向向量为0，操作无效，不更新positionDelta
			{
				float norm = sqrt(length.x * length.x + length.y * length.y);				// 方向差的模
				positionDelta = sf::Vector2f(10.f * length.x / norm, 10.f * length.y / norm); // 最终的方向向量，运动距离为1标准单位，即10.f

				update_ = true; // 操作有效时刷新画布
			}
			else
			{
				update_ = false; // 操作无效时不刷新画布
			}

			// mouseOpen_ = true; // 开启鼠标控制
			mouseControl_ = true; // 鼠标控制
		}
		else
		{
			update_ = true; // 操作有效时刷新画布
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			direction_ = Direction::Up; // 方向标记为up

			update_ = true;		  // 操作有效时刷新画布
			mouseControl_ = false; // 键盘控制
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			direction_ = Direction::Down; // 方向标记为Down

			update_ = true;		  // 操作有效时刷新画布
			mouseControl_ = false; // 键盘控制
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			direction_ = Direction::Left; // 方向标记为Left

			update_ = true;		  // 操作有效时刷新画布
			mouseControl_ = false; // 键盘控制
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			direction_ = Direction::Right; // 方向标记为Right

			update_ = true;		  // 操作有效时刷新画布
			mouseControl_ = false; // 键盘控制
		}
	}
}

void Snake::update(sf::Time delta) // 刷新每帧界面
{
	if (!pause_) // 处于不暂停状态时才刷新画面
	{
		move();				   // 刷新蛇的移动
		checkEdgeCollisions(); // 判断边界条件
		checkSelfCollisions(); // 判断自身碰撞条件
	}
}

void Snake::checkFruitCollisions(std::vector<Fruit> &fruits) // 检查水果的情况
{
	decltype(fruits.begin()) toRemove = fruits.end(); // 标记水果队列的最后一个元素为remove

	for (auto it = fruits.begin(); it != fruits.end(); ++it) // 检查所有水果队列中所有水果
	{
		if (it->getBounds().intersects(nodes_[0].getBounds()))
			toRemove = it; // 当蛇头碰上水果后，将水果标记为remove
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();				   // 播放捡起水果的声音
		pickUpColor_ = (*toRemove).getColor(); // 存储颜色
		grow(pickUpColor_);					   // 实现蛇的生长
		fruits.erase(toRemove);				   // 吃掉的水果消失在界面中
	}
}

sf::Color Snake::getColorFromPickUpColor() // 根据吃掉水果的颜色随机生成同种类水果的颜色
{
	sf::Color generateColor; // 待生成的水果颜色

	std::vector<sf::Color> colors_{sf::Color::Red, sf::Color::Blue,
								   sf::Color::Green, sf::Color(128, 42, 42), sf::Color(128, 128, 128)}; // 红色0，蓝色1，绿色2，棕色3，灰色4

	static std::default_random_engine engine_(time(NULL)); // 随机数引擎

	if (pickUpColor_ == sf::Color::Red || pickUpColor_ == sf::Color::Blue || pickUpColor_ == sf::Color::Green)
	{
		static std::uniform_int_distribution<int> rgbDistribution(0, 2); // 红蓝绿随机数
		generateColor = colors_.at(rgbDistribution(engine_));
	}
	else
	{
		static std::uniform_int_distribution<int> bbDistribution(3, 4); // 棕灰随机数
		generateColor = colors_.at(bbDistribution(engine_));
	}

	return generateColor;
}

void Snake::grow(sf::Color fruitColor) // 控制蛇的生长
{
	if (fruitColor == sf::Color::Red)
	{
		for (int i = 0; i != 3; ++i)
		{
			nodes_.push_back(SnakeNode(sf::Vector2f(
				2 * nodes_[nodes_.size() - 1].getPosition().x - nodes_[nodes_.size() - 2].getPosition().x,
				2 * nodes_[nodes_.size() - 1].getPosition().y - nodes_[nodes_.size() - 2].getPosition().y)));
		}
	}
	else if (fruitColor == sf::Color::Blue)
	{
		for (int i = 0; i != 2; ++i)
		{
			nodes_.push_back(SnakeNode(sf::Vector2f(
				2 * nodes_[nodes_.size() - 1].getPosition().x - nodes_[nodes_.size() - 2].getPosition().x,
				2 * nodes_[nodes_.size() - 1].getPosition().y - nodes_[nodes_.size() - 2].getPosition().y)));
		}
	}
	else if (fruitColor == sf::Color::Green)
	{
		nodes_.push_back(SnakeNode(sf::Vector2f(
			2 * nodes_[nodes_.size() - 1].getPosition().x - nodes_[nodes_.size() - 2].getPosition().x,
			2 * nodes_[nodes_.size() - 1].getPosition().y - nodes_[nodes_.size() - 2].getPosition().y)));
	}
}

unsigned Snake::getSize() const // 返回蛇的长度
{
	return nodes_.size();
}

bool Snake::hitSelf() const // 判断蛇是否与自身碰撞
{
	return hitSelf_;
}

void Snake::checkSelfCollisions() // 检查是否与自身碰撞，暂时修改为无敌状态
{
	// SnakeNode &headNode = nodes_[0];
	// if (!mouseOpen_)
	// {
	// 	for (decltype(nodes_.size()) i = 1; i < nodes_.size(); ++i) // 检查所有节点
	// 	{
	// 		if (headNode.getBounds().intersects(nodes_[i].getBounds())) // 检查蛇头是否与身体其余节点碰撞
	// 		{
	// 			dieSound_.play(); // 碰撞了发出死亡音效
	// 			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds())); // 画面暂停
	// 			hitSelf_ = true; // 标记自身碰撞参数为true
	//
	// 			std::cout << headNode.getBounds().left << " " << headNode.getBounds().top << " " <<
	// 			headNode.getBounds().width << " " << headNode.getBounds().height << std::endl; // 调试
	//
	// 			std::cout << nodes_[i].getBounds().left << " " << nodes_[i].getBounds().top << " " <<
	// 			nodes_[i].getBounds().width << " " << nodes_[i].getBounds().height << std::endl; // 调试
	// 		}
	// 	}
	// }
	// else
	// {
	hitSelf_ = false;
	// }

	// 由于旋转sprite时存在一些bug，导致不能成功判断自身碰撞，故取消了碰撞的判定
	// 原来打算设置一个mouseOpen变量，在开始使用鼠标前可以判定自身碰撞，一旦使用鼠标则取消，因为鼠标控制会导致边界部分重合
}

void Snake::checkEdgeCollisions() // 边界条件，从屏幕另外一边出现，修改为碰到边界死亡
{
	SnakeNode &headNode = nodes_[0];

	// 碰到边界：从另一边出现
	// if (headNode.getPosition().x <= 0) // 从窗口左侧越界
	// 	headNode.setPosition(Game::Width, headNode.getPosition().y);
	// else if (headNode.getPosition().x >= Game::Width) // 从窗口右侧越界
	// 	headNode.setPosition(0, headNode.getPosition().y);
	// else if (headNode.getPosition().y <= 0) // 从窗口上侧越界
	// 	headNode.setPosition(headNode.getPosition().x, Game::Height);
	// else if (headNode.getPosition().y >= Game::Height) // 从窗口下侧越界
	// 	headNode.setPosition(headNode.getPosition().x, 0);

	// 碰到边界：死亡
	if (headNode.getPosition().x <= 0 || headNode.getPosition().x >= Game::Width ||
		headNode.getPosition().y <= 0 || headNode.getPosition().y >= Game::Height)
	{
		dieSound_.play();												// 碰撞了发出死亡音效
		sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));   // 画面暂停
		Game::Screen = std::make_shared<GameOverScreen>(nodes_.size()); // 碰到边界死亡，游戏结束
	}
}

void Snake::move() // 修改: 添加鼠标控制
{
	if (update_) // 仅操作有效时移动
	{
		for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
		{
			nodes_[i].setDirection(nodes_.at(i - 1).getPosition(), nodes_.at(i).getPosition()); // 设置节点的方向
			nodes_[i].setPosition(nodes_.at(i - 1).getPosition()); // 往snake的前进方向update
		}

		if (mouseControl_)
		{
			nodes_[0].setDirection(positionDelta.x, positionDelta.y); // 向移动方向旋转
			nodes_[0].move(positionDelta.x, positionDelta.y); // 向移动方向移动10.f
		}
		else
		{
			switch (direction_)
			{
			case Direction::Up:
				nodes_[0].setDirection(0, -SnakeNode::Height); // 向移动方向旋转
				nodes_[0].move(0, -SnakeNode::Height); // 向上移动10.f
				break;
			case Direction::Down:
				nodes_[0].setDirection(0, SnakeNode::Height); // 向移动方向旋转
				nodes_[0].move(0, SnakeNode::Height); // 向下移动10.f
				break;
			case Direction::Left:
				nodes_[0].setDirection(-SnakeNode::Width, 0); // 向移动方向旋转
				nodes_[0].move(-SnakeNode::Width, 0); // 向左移动10.f
				break;
			case Direction::Right:
				nodes_[0].setDirection(SnakeNode::Width, 0); // 向移动方向旋转
				nodes_[0].move(SnakeNode::Width, 0); // 向右移动10.f
				break;
			}
		}
	}
}

void Snake::render(sf::RenderWindow &window) // 渲染画布
{
	for (auto node : nodes_)
		node.render(window);
}