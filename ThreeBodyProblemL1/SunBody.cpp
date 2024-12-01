#include "SunBody.hpp"
#define SUN_RADIUS 10.0F
void SunBody::draw(IRender* renderer)
{
	static Color mColor(255, 255, 127, 0);


	int screenW = renderer->getScreenWidth();
	int screenH = renderer->getScreenHeight();
	int transformX = screenW / 2 + (mOrigin.x / (MAX_ORIGIN_X * 2)) * screenW;
	int transformY = screenH / 2 + (mOrigin.y / (MAX_ORIGIN_X * 2)) * screenH;

	renderer->drawFilledCircle(mColor, { transformX,transformY }, SUN_RADIUS);
}
