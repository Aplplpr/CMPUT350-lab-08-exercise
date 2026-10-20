#ifndef BASIC_TRANSFORM_H
#define BASIC_TRANSFORM_H

#include <cassert>

#include "vector_util.h"
#include <SFML/System/Vector2.hpp>

struct BasicTransform {
    // TODO: Determine if possible in general, else provide counterexample:
    // compose(f, g) is equivalent to first applying g, then applying f.
    static BasicTransform compose(const BasicTransform& f, const BasicTransform& g) {
        sf::Vector2f newScale = f.scale * g.scale;
        sf::Vector2f newTranslation = g.translation * f.scale + f.translation;
        return BasicTransform(newScale, newTranslation);
    };

    // TODO: Determine if possible in general, else provide counterexample:
    static BasicTransform inverse(const BasicTransform& f) {
        assert (f.scale.x != 0 && f.scale.y != 0); //all non 0 component
        sf::Vector2f inverseScale = sf::Vector2f(1.f, 1.f) / f.scale;
        sf::Vector2f inverseTranslation = -f.translation / f.scale;

        return BasicTransform(inverseScale, inverseTranslation);
    };

    constexpr BasicTransform(const sf::Vector2f& scale = {1.f, 1.f},
                             const sf::Vector2f& translation = {0.f, 0.f})
        : scale{scale}, translation{translation} {}

    constexpr sf::Vector2f applyPoint(const sf::Vector2f& p) const {
        // first scale, then translate -- if you do the reverse, the translation gets messed up.
        return {p.x * scale.x + translation.x, p.y * scale.y + translation.y};
    }

    constexpr sf::Vector2f applyVector(const sf::Vector2f& p) const {
        // vectors are not translated by transformations
        return {p.x * scale.x, p.y * scale.y};
    }

    constexpr bool operator==(const BasicTransform& other) const {
        return scale == other.scale && translation == other.translation;
    }

    sf::Vector2f scale;
    sf::Vector2f translation;
};

#endif