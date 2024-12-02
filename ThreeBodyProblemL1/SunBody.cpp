#include "SunBody.hpp"
#include "UniverseCmd.hpp"
#define SUN_RADIUS 10.0F
void SunBody::draw(IRender* renderer)
{
	static Color mColor(255, 255, 127, 0);


	int screenW = renderer->getScreenWidth();
	int screenH = renderer->getScreenHeight();
	int screenCenterW = screenW / 2;
	int screenCenterH = screenH / 2;
	int transformX = screenW / 2 + (mOrigin.x / (MAX_ORIGIN_X * 2)) * screenW;
	int transformY = screenH / 2 + (mOrigin.y / (MAX_ORIGIN_X * 2)) * screenH;



	auto positionsPrev = mCmdPtr->getAllPrevTicksPosition(id);
	unsigned int positionsSize = (positionsPrev.size());
	POINT* arrPoints = new POINT[positionsSize];
	int i = 0;
	for (auto& position : positionsPrev) {
		if (i >= positionsSize)continue;
		position.x = screenCenterW + (position.x / (MAX_ORIGIN_X * 2)) * screenW;
		position.y = screenCenterH + (position.y / (MAX_ORIGIN_X * 2)) * screenH;
		arrPoints[i] = { (int)position.x, (int)position.y };
		i++;
	}
	renderer->drawPolygon(mColor, arrPoints, positionsSize, false);
	delete[] arrPoints;
	renderer->drawFilledCircle(mColor, { transformX,transformY }, SUN_RADIUS);
	Vector2 size = renderer->getTextSize("the sun");
	RECT rc = { transformX - SUN_RADIUS/2  - size.x/2, transformY + SUN_RADIUS/2, transformX + SUN_RADIUS/2 + size.x/2, transformY + SUN_RADIUS/2 + size.y};
	
	renderer->drawText("The Sun", &rc);
}
