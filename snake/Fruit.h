#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

#include <vector>

namespace sfSnake
{
// enum class Colors // 颜色Colors类，枚举类型：红绿蓝棕黑
// {
// 	Red,
// 	Blue,
// 	Green,
// 	Brown,
// 	Black
// };

class Fruit // Fruit类
{
public:
	Fruit(sf::Vector2f position = sf::Vector2f(0, 0), sf::Color color = sf::Color::Black); // 构造一个水果

	void render(sf::RenderWindow &window); // 渲染画布

	sf::FloatRect getBounds() const; // 获取水果的边界情况

	sf::Color getColor(); // 获取水果颜色

private:
	sf::CircleShape shape_; // 水果形状: 圆形

	sf::Color color_; // 水果颜色: Red、Green、Blue、Black、Brown

	static const float Radius; // 水果半径
};
} // namespace sfSnake

#endif