#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>

#include <cmath>

#include "SnakeNode.h"
#include "TextureManager.h"

using namespace sfSnake;

const float SnakeNode::Width = 10.f;  // 水平单位长度
const float SnakeNode::Height = 10.f; // 垂直单位长度

SnakeNode::SnakeNode(sf::Vector2f position) : position_(position) // 构造函数，构造一个蛇的蛇身
{
	sprite_ = sf::Sprite(TextureManager::getTexture("snakeNode.png")); // 渲染蛇身
	sprite_.setScale(0.086f, 0.086f); // 蛇身比例，使其大小变为11*11，原图大小128*128
	sprite_.setPosition(position_); // 蛇身位置
}

SnakeNode::SnakeNode(bool head, sf::Vector2f position) : position_(position) // 重载构造函数，构造一个蛇的蛇头
{
	sprite_ = sf::Sprite(TextureManager::getTexture("snakeHead.png")); // 渲染蛇头
	sprite_.setScale(0.089f, 0.087f); // 蛇头比例，使其大小变为11*11，原图大小123*127
	sprite_.setPosition(position_); // 蛇头位置
}

void SnakeNode::setPosition(sf::Vector2f position) // 设置节点的位置
{
	position_ = position;
	sprite_.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y) // 同上，setPosition函数的重载
{
	position_.x = x;
	position_.y = y;
	sprite_.setPosition(position_);
}

void SnakeNode::setDirection(sf::Vector2f newPosition, sf::Vector2f oldPosition) // 设置节点的方向
{
	sf::Vector2f length = newPosition - oldPosition;
	float norm = sqrt(length.x * length.x + length.y * length.y);
	direction_ = M_PI - atan2(length.x / norm, length.y / norm);

	sprite_.setOrigin(sf::Vector2f(SnakeNode::Width / 2, SnakeNode::Height / 2));
	sprite_.setRotation(direction_ / M_PI * 180.f);
	sprite_.setOrigin(sf::Vector2f(0.f, 0.f));
}

void SnakeNode::setDirection(float x, float y) // 同上，setDirection函数的重载
{
	float norm = sqrt(x * x + y * y);
	direction_ = M_PI - atan2(x / norm, y / norm);

	sprite_.setOrigin(sf::Vector2f(SnakeNode::Width / 2, SnakeNode::Height / 2));
	sprite_.setRotation(direction_ / M_PI * 180.f);
	sprite_.setOrigin(sf::Vector2f(0.f, 0.f));
}

void SnakeNode::move(float xOffset, float yOffset) // 实现节点的移动
{
	position_.x += xOffset;
	position_.y += yOffset;
	sprite_.setPosition(position_);
}

sf::FloatRect SnakeNode::getBounds() const // 用于碰撞检测，返回当前形状的全局范围，不可更改
{
	return sprite_.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const // 返回当前节点的位置，不可更改
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow &window) // 渲染画布
{
	window.draw(sprite_);
}