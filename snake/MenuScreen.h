#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"

namespace sfSnake
{
class MenuScreen : public Screen // 由Screen类派生的MenuScreen类
{
public:
	MenuScreen(); // 构造函数

	void handleInput(sf::RenderWindow &window) override; // 处理键盘鼠标操作
	void update(sf::Time delta) override; // 刷新每帧界面
	void render(sf::RenderWindow &window) override; // 窗口投影

private:
	sf::Font font_; // 字体
	sf::Text snakeText_; // 图标snake文字
	sf::Text text_; // 提示字符文字
};
} // namespace sfSnake

#endif