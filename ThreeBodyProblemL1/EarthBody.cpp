#include "EarthBody.hpp"
#include "UniverseCmd.hpp"
#define EARTH_RADIUS 8.0F
EarthBody::EarthBody(UniverseCmd* cmdPtr, SunBody* sun, const Vector3D& mOrigin) : DefaultBody(EARTH_ID, sun->getMass() / EARTH_MASS_LESS, mOrigin, Vector3D(), cmdPtr) {
	Vector3D diff = sun->getOrigin() - this->mOrigin;
	double dstToSun = diff.length();
	double earthSpeed = sqrt(cmdPtr->uGravity * sun->getMass() / dstToSun);
	diff.normalize();
	//u = sqrt(gm/r)
	//немного линейной алгебры: поворот на 90
	this->mV.x = -diff.y *  earthSpeed;
	this->mV.y = diff.x * earthSpeed;
	this->mV.z = 0;
	std::cout << "EarthBody inited, mass :" << this->mass << std::format("\torigin: x,y,z {} {} {} \t", mOrigin.x, mOrigin.y, mOrigin.z)
		<< "Earth orbital speed(x,y,z) : " << mV.x << " " << mV.y << " " << mV.z << "\n";
}

void EarthBody::draw(IRender* renderer)
{
	static Color mColor(255, 0, 255, 0);
	int screenW = renderer->getScreenWidth();
	int screenH = renderer->getScreenHeight();

	int screenCenterW = screenW / 2;
	int screenCenterH = screenH / 2;
	int transformX = screenCenterW + (mOrigin.x / (MAX_ORIGIN_X * 2)) * screenW;
	int transformY = screenCenterH + (mOrigin.y / (MAX_ORIGIN_X * 2)) * screenH;
	
	auto positionsPrev = mCmdPtr->getAllPrevTicksPosition(id);
	unsigned int positionsSize = (positionsPrev.size());
	POINT* arrPoints = new POINT[positionsSize];
	uintptr_t i = 0u;
	for (auto& position : positionsPrev) {
		position.x = screenCenterW + (position.x/ (MAX_ORIGIN_X * 2)) * screenW;
		position.y = screenCenterH + (position.y / (MAX_ORIGIN_X * 2)) * screenH;
		arrPoints[i] = { (int)position.x, (int)position.y };
		i++;
	}
	renderer->drawFilledCircle(mColor, { transformX,transformY }, EARTH_RADIUS);
	renderer->drawPolygon(mColor, arrPoints, positionsSize, false);
	delete[] arrPoints;
	const auto text = "The Earth";
	Vector2 size = renderer->getTextSize(text);
	RECT rc = { transformX - EARTH_RADIUS / 2 - size.x / 2, transformY + EARTH_RADIUS / 2, transformX + EARTH_RADIUS / 2 + size.x / 2, transformY + EARTH_RADIUS / 2 + size.y };
	renderer->drawText(text,mColor, &rc);
}

