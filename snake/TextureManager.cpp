#include <SFML/Graphics.hpp>

#include "TextureManager.h"

using namespace sfSnake;

TextureManager *TextureManager::point_ = nullptr; // 初始化指针

TextureManager::TextureManager() // 构造函数
{
    point_ = this; // 指针指向自身
}

sf::Texture &TextureManager::getTexture(std::string const &filename)
{
    auto &shape_ = point_->textures_; // 指针指向存储容器
    auto &texture = shape_[filename]; // 创建图案空间
    texture.loadFromFile(filename); // 读取图案
    return texture; // 返回图案
}