#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"

namespace sfSnake
{
class GameScreen : public Screen // 由Screen类派生的GameScreen类
{
public:
	GameScreen(); // 构造函数

	void handleInput(sf::RenderWindow &window) override; // 处理键盘鼠标操作
	void update(sf::Time delta) override; // 刷新每帧界面
	void render(sf::RenderWindow &window) override; // 窗口投影

	void generateFruit(sf::Color color); // 生成水果

	void constructGrid(); // 绘制网格线

private:
	Snake snake_; // 创建snake对象
	std::vector<Fruit> fruit_; // 创建存储fruit对象的vector

	bool Initial = true; // 初始化指示变量
	static const int InitialQuantity; // 初始水果数量

	bool displayGrid_ = false; // 显示网格线指示变量
	std::vector<sf::RectangleShape> rowGrid_; // 水平网格线
	std::vector<sf::RectangleShape> colGrid_; // 垂直网格线
};
} // namespace sfSnake

#endif