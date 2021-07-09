#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>

#include "Screen.h"

namespace sfSnake
{
class Game // Game类
{
public:
	Game(); // 构造函数

	void run(); // 游戏运行

	void handleInput(); // 处理键盘鼠标操作
	void update(sf::Time delta); // 刷新每帧界面
	void render(); // 渲染画布

	static const int Width = 640; // 窗口宽
	static const int Height = 480; // 窗口高

	static std::shared_ptr<Screen> Screen; // 界面切换变量

private:
	sf::RenderWindow window_; // 窗口
	sf::Music bgMusic_; // 背景音乐
	sf::RectangleShape background_; // 背景图案

	static const sf::Time TimePerFrame; // 帧速
};
} // namespace sfSnake

#endif