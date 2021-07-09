#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SFML/Graphics.hpp>

#include <map>

namespace sfSnake
{
class TextureManager
{
public:
    TextureManager(); // 构造函数
    static sf::Texture &getTexture(const std::string &filename); // 获取图案

private:
    std::map<std::string, sf::Texture> textures_; // 存储texture
    static TextureManager *point_; // 静态指针，用于读取texture
};
} // namespace sfSnake

#endif