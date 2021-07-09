#include <SFML/Graphics.hpp>

#include <random>

#include "Fruit.h"

using namespace sfSnake;

const float Fruit::Radius = 5.f; // 水果半径为5.f，与蛇的节点一样大

Fruit::Fruit(sf::Vector2f position, sf::Color color) : color_(color) // 构造函数
{
	shape_.setPosition(position);	// 设定水果位置
	shape_.setRadius(Fruit::Radius); // 设定水果半径
	shape_.setFillColor(color_); // 设定水果颜色
	// shape_.setOutlineColor(sf::Color::White); // 设定水果边界颜色
	// shape_.setOutlineThickness(-1.f); // 设定水果边界宽度
}

void Fruit::render(sf::RenderWindow &window) // 渲染水果
{
	window.draw(shape_);
}

sf::FloatRect Fruit::getBounds() const // 返回水果的边界位置，不可更改
{
	return shape_.getGlobalBounds();
}

sf::Color Fruit::getColor() // 获取水果颜色
{
	return color_;
}

// void Fruit::generateColor() // 按概率随机生成每一种水果
// {
	// static std::default_random_engine engine_(time(NULL)); // 使用随机引擎生成水果颜色
	// static std::uniform_real_distribution<float> distribution(0, 1); // 水果的颜色

	// float colorInterval = distribution(engine_); // 水果颜色的生成概率

	// 生成5种颜色水果
	// if (colorInterval >= 0.f && colorInterval < 0.25f)
	// {
	// 	color_ = sf::Color::Red; // 25%的概率为红色
	// }
	// else if (colorInterval >= 0.25f && colorInterval < 0.5f)
	// {
	// 	color_ = sf::Color::Blue; // 25%的概率为蓝色
	// }
	// else if (colorInterval >= 0.5f && colorInterval < 0.75f)
	// {
	// 	color_ = sf::Color::Green; // 25%的概率为绿色
	// }
	// else if (colorInterval >= 0.75f && colorInterval < 0.875f)
	// {
	// 	color_ = sf::Color(128, 42, 42); // 12.5%的概率为棕色
	// }
	// else if (colorInterval >= 0.875f && colorInterval < 1.f)
	// {
	// 	color_ = sf::Color(128, 128, 128); // 12.5%的概率为灰色
	// }
// }