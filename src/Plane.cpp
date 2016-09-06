
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

}//�ж�p�Ƿ��ڹ�����Χ��

bool Plane::IsInHealRange(Point p) {
    return(_pos.getDistance(p) <= HEAL_RADUIS);

}//�ж�p�Ƿ������Ʒ�Χ��

void Plane::Command() {
    //�Ժ���ʵ��
}

PlaneStatus Plane::GetPlaneStatus()
{
    return _status;
};//���طɻ�״̬

void Plane::SetPlaneStatus(unsigned char color)
{
    if (color == 0)
        _status = PlaneAttack;
    else if (color == 255)
        _status = PlaneHeal;

};//���÷ɻ�״̬