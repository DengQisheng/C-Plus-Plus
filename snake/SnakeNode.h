#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

#include "TextureManager.h"

namespace sfSnake
{
class SnakeNode // Snake类
{
public:
	SnakeNode(sf::Vector2f position); // = sf::Vector2f(0, 0)); // 构造蛇身节点
	SnakeNode(bool head, sf::Vector2f position); // 重载构造函数，构造蛇头节点

	void setPosition(sf::Vector2f position); // 设置节点的位置
	void setPosition(float x, float y); // 上一行的重载函数

	void setDirection(sf::Vector2f newPosition, sf::Vector2f oldPosition); // 设置节点的方向
	void setDirection(float x, float y); // 上一行的重载函数

	void move(float xOffset, float yOffset); // 蛇snake节点的移动

	void render(sf::RenderWindow &window); // 渲染节点

	sf::Vector2f getPosition() const; // 返回蛇某个节点的位置
	sf::FloatRect getBounds() const; // 用于碰撞检测，返回当前形状的全局范围

	static const float Width; // 水平单位长度常量
	static const float Height; // 垂直单位长度常量

private:
	sf::Sprite sprite_; // 节点精灵
	sf::Vector2f position_; // 节点位置
	float direction_; // 节点方向 

	TextureManager manager_; // 存储texture的容器
};
} // namespace sfSnake

#endif