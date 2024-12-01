#include "DefaultBody.hpp"
#include "UniverseCmd.hpp"
#include "IRender.h"
void DefaultBody::update(float elapsedTimeFromPrevUpdate)
{
    std::optional<std::vector<DefaultBody>> bodies = mCmdPtr->getPrevDataTick();
    if (!bodies.has_value()) {
        return;
    }
    double Fx = 0, Fy = 0, Fz = 0;
    for (auto& otherBody : bodies.value()) {
        if (&otherBody == this) continue;
        Vector3D sOrigin = mOrigin - otherBody.mOrigin;
        double dstBtwBodies = this->mOrigin.distance(otherBody.mOrigin);
        if (dstBtwBodies == 0.0) continue;

        // Сила гравитации (F = G * m1 * m2 / r^2), при этом вычисляем силу как вектор
        double force = mCmdPtr->uGravity * (mass * otherBody.mass) / (pow(dstBtwBodies, 3));

        // Разложение силы на компоненты по осям
        Fx += force * sOrigin.x;
        Fy += force * sOrigin.y;
        Fz += force * sOrigin.z;
    }

    //a = F/m, ускорение по осям
    mA.x = Fx / this->mass;
    mA.y = Fy / this->mass;
    mA.z = Fz / this->mass;

    //v =  v0 + a*dt;
    mV = mA * elapsedTimeFromPrevUpdate;


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
    static Color mColor(255, 255, 0, 0);
    renderer->drawFilledRect(mColor, { (int)mOrigin.x,(int)mOrigin.y }, { 5,5 });
}
