#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"

namespace sfSnake
{
class GameOverScreen : public Screen // 由Screen类派生的GameOverScreen类
{
public:
	GameOverScreen(std::size_t score); // 构造函数，输入参数为分数score

	void handleInput(sf::RenderWindow &window) override; // 处理键盘鼠标操作
	void update(sf::Time delta) override; // 刷新每帧界面
	void render(sf::RenderWindow &window) override; // 窗口投影

private:
	sf::Font font_; // 字体
	sf::Text text_; // 文字

	unsigned score_; // 分数
};
} // namespace sfSnake

#endif