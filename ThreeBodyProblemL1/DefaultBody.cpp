#include "DefaultBody.hpp"
#include "UniverseCmd.hpp"
#include "IRender.h"
#define DEFAULT_RADIUS 5.0F
#define DEFAULT_HISTORY_TICKS 512u
void DefaultBody::update(float elapsedTimeFromPrevUpdate)
{
    std::vector<DefaultBody*> bodies = mCmdPtr->mBodies;
    if (bodies.empty()) {
        return;
    }
    double Fx = 0, Fy = 0, Fz = 0;
    for (DefaultBody* otherBody : bodies) {
        if (this == otherBody) {
            continue;
        }
       
        Vector3D sOrigin = otherBody->mOrigin - this->mOrigin;
        double dstBtwBodies = this->mOrigin.distance(otherBody->mOrigin);
        if (dstBtwBodies == 0.0) continue;

        // Сила гравитации (F = G * m1 * m2 / r^2)
        double force = mCmdPtr->uGravity * (mass * otherBody->mass) / (pow(dstBtwBodies, 2));

        // Разложение силы на компоненты по осям
        Fx += force * sOrigin.x / dstBtwBodies ;
        Fy += force * sOrigin.y /dstBtwBodies;
        Fz += force * sOrigin.z;
    }

    //a = F/m, ускорение по осям
    mA.x = Fx / this->mass;
    mA.y = Fy / this->mass;
    mA.z = Fz / this->mass;

    //v =  v0 + a*dt;
    mV += mA * elapsedTimeFromPrevUpdate;
   

    /*альтернативная запись :
    mV.x += mA.x * elapsedTimeFromPrevUpdate;
    mV.y += mA.y * elapsedTimeFromPrevUpdate;
    mV.z += mA.z * elapsedTimeFromPrevUpdate;
    */


    //x = x0 + v * dt;
    mOrigin += mV * elapsedTimeFromPrevUpdate;

}

void DefaultBody::draw(IRender* renderer)
{
    if (mOrigin.x < -MAX_ORIGIN_X - 1 || mOrigin.x > MAX_ORIGIN_X + 1) {
        return;
    }
    if (mOrigin.y < -MAX_ORIGIN_X - 1 || mOrigin.y > MAX_ORIGIN_X + 1) {
        return;
    }
    static Color mColor(255, 255, 255, 255);
    static const uintptr_t ticksToTake = DEFAULT_HISTORY_TICKS;
    uintptr_t screenW = renderer->getScreenWidth();
    uintptr_t screenH = renderer->getScreenHeight();
    uintptr_t screenCenterW = screenW / 2;
    uintptr_t screenCenterH = screenH / 2;
    int transformX = screenCenterW + (mOrigin.x / (MAX_ORIGIN_X * 2)) * screenW;
    int transformY = screenCenterH + (mOrigin.y / (MAX_ORIGIN_X * 2)) * screenH;


    POINT arrPoints[ticksToTake]{};
    std::vector<Vector3D> positionsPrev = mCmdPtr->getLastNPrevTicksPosition(id, ticksToTake);
    uintptr_t i = 0u;
    for (auto& position : positionsPrev) {
        if (i >= ticksToTake)break;
        position.x = screenCenterW + (position.x / (MAX_ORIGIN_X * 2)) * screenW;
        position.y = screenCenterH + (position.y / (MAX_ORIGIN_X * 2)) * screenH;
        arrPoints[i] = { (int)position.x, (int)position.y };
        i++;
    }
    renderer->drawPolygon(mColor, arrPoints, i, false);
  

    renderer->drawFilledCircle(mColor, { transformX,transformY},(1 + (mass/MAX_MASS_DEFAULT_BODY)) *(DEFAULT_RADIUS-1));
}
