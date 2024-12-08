#include "Utils.hpp"


bool Utils::isPointInBB(const Vector2& obj, const Vector2& bbBox, const Vector2& bbBoxSize)
{
    auto max = bbBox + bbBoxSize;
    return (obj.x >= bbBox.x && obj.x <= max.x) && (obj.y >= bbBox.y && obj.y <= max.y);

}
