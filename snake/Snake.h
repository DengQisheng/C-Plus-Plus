#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "SnakeNode.h"
#include "Fruit.h"

namespace sfSnake
{
enum class Direction // 方向Direction类，枚举类型：上下左右
{
	Left,
	Right,
	Up,
	Down
};

class Snake // Snake类
{
public:
	Snake(); // 构造函数，构造一条蛇

	void handleInput(sf::RenderWindow &window); // 处理键盘鼠标操作
	void update(sf::Time delta); // 刷新每帧界面
	void render(sf::RenderWindow &window); // 投影窗口

	void checkFruitCollisions(std::vector<Fruit> &fruits); // 检查水果的情况

	bool hitSelf() const; // 判断有没有与自己相撞，游戏结束的判断

	unsigned getSize() const; // 获得蛇的长度

	sf::Color getColorFromPickUpColor(); // 根据吃掉水果的颜色随机生成同种类水果的颜色

private:
	void move(); // 控制蛇的移动
	void grow(sf::Color fruitColor); // 控制蛇的生长
	void checkEdgeCollisions(); // 检查边界情况
	void checkSelfCollisions(); // 检查自身碰撞情况
	void initNodes(); // 控制蛇的初始状态

	bool hitSelf_; // 判断自身碰撞的变量

	sf::Vector2f position_; // 表明蛇的位置的变量
	Direction direction_; // 方向: 上下左右

	sf::Vector2f positionDelta = sf::Vector2f(0, 0); // 鼠标控制的方向差的变量，初始值为0

	bool update_ = true; // 是否更新画布，用于处理鼠标操作无效的情况
	bool mouseControl_ = false; // 是否由鼠标控制: 鼠标或键盘，对应true或false，初始为键盘控制
	// bool mouseOpen_ = false; // 是否开启鼠标控制，一旦开启不能关闭，考虑到蛇的位置已经错乱，会出现重叠情况
	bool pause_; // 设定暂停变量

	sf::Color pickUpColor_; // 吃掉水果的颜色变量

	sf::SoundBuffer pickupBuffer_; // 捡起水果时的声音设置
	sf::Sound pickupSound_; // 捡起水果时的声效

	sf::SoundBuffer dieBuffer_; // 死亡时的声音设置
	sf::Sound dieSound_; // 死亡时的音效

	std::vector<SnakeNode> nodes_; // 存储蛇的节点的vector

	static const int InitialSize; // 蛇的初始大小

	static const bool head_ = true; // 蛇头指示变量
};
} // namespace sfSnake

#endif