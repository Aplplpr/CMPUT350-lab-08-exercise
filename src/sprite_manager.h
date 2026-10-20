#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include "sprite.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <deque>
#include <string>
#include <utility>

using SpriteID = size_t;

class SpriteManager {
public:
    sf::Texture& registerTexture(const std::string& filepath) {
        auto it = mTextures.find(filepath);
        if (it != mTextures.end()) {
            return it->second;
        }
        auto result = mTextures.try_emplace(filepath, filepath);
        return result.first->second;
    }

    
    template <typename... Args> SpriteID createSprite(Args&&... args) {
        SpriteID id = mSprites.size();
        mSprites.emplace_back(std::forward<Args>(args)...);
        return id;
    }

    Sprite& getSprite(SpriteID id){
        return mSprites[id];
    }

private:
    std::map<std::string, sf::Texture> mTextures;
    std::deque<Sprite> mSprites;
};

#endif  // SPRITE_MANAGER_H
