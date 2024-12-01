#include "DefaultBody.hpp"
#include "UniverseCmd.hpp"
#include "IRender.h"
#define DEFAULT_RADIUS 6.0F
void DefaultBody::update(float elapsedTimeFromPrevUpdate)
{
    std::optional<std::vector<DefaultBody>> bodies = mCmdPtr->lastLogicInstance;
    if (!bodies.has_value()) {
        return;
    }
    double Fx = 0, Fy = 0, Fz = 0;
    for (DefaultBody& otherBody : bodies.value()) {
        if (this == otherBody) {
            continue;
        }
       
        Vector3D sOrigin = otherBody.mOrigin - this->mOrigin;
        double dstBtwBodies = this->mOrigin.distance(otherBody.mOrigin);
        if (dstBtwBodies == 0.0) continue;

        // Сила гравитации (F = G * m1 * m2 / r^2)
        double force = mCmdPtr->uGravity * (mass * otherBody.mass) / (pow(dstBtwBodies, 2));

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
    static Color mColor(255, 255, 255, 255);

 
    int screenW = renderer->getScreenWidth();
    int screenH = renderer->getScreenHeight();
    int transformX = screenW / 2 + (mOrigin.x / (MAX_ORIGIN_X * 2)) * screenW;
    int transformY = screenH / 2 + (mOrigin.y / (MAX_ORIGIN_X * 2)) * screenH;

    renderer->drawFilledCircle(mColor, { transformX,transformY},DEFAULT_RADIUS);
}
