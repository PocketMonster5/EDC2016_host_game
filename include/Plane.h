
#pragma once

#include "Common.h"

class Plane {
public:
    void Refresh(Point p, unsigned char color);//ˢ�·ɻ�λ��,����Tower����ɫ�������ɻ�״̬

    bool IsInAttackRange(Point p);
    bool IsInHealRange(Point p);

    PlaneStatus GetPlaneStatus();
    void Plane::SetPlaneStatus(unsigned char color);

    void Command();//�Ժ���ʵ��

private:
    Point _pos;
    PlaneStatus _status;
};