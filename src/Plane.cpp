
#include"Plane.h"

#include<iostream>
using namespace std;
void Plane::Refresh(Point p, unsigned char color) {
    _pos.x = p.x;
    _pos.y = p.y;
    SetPlaneStatus(color);
}
bool Plane::IsInAttackRange(Point p) {
    return(_pos.getDistance(p) <= ATTACK_RADIUS);

}//判断p是否在攻击范围内

bool Plane::IsInHealRange(Point p) {
    return(_pos.getDistance(p) <= HEAL_RADUIS);

}//判断p是否在治疗范围内

void Plane::Command() {
    //以后再实现
}

PlaneStatus Plane::GetPlaneStatus()
{
    return _status;
};//返回飞机状态

void Plane::SetPlaneStatus(unsigned char color)
{
    if (color == 0)
        _status = PlaneAttack;
    else if (color == 255)
        _status = PlaneHeal;

};//设置飞机状态