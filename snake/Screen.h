#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>

class Screen // Screen类，提供三种基本操作
{
public:
	virtual void handleInput(sf::RenderWindow &window) = 0; // 处理键盘鼠标操作
	virtual void update(sf::Time delta) = 0;				// 刷新每帧界面
	virtual void render(sf::RenderWindow &window) = 0;		// 渲染画布
};

#endif