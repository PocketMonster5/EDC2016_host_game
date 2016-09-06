
#pragma once

#include"Common.h"

class Tower {
public:
    void Reset() { _health = TOWER_HEALTH; }//����ֵ����

    double GetHealth() const { return _health; }//����Ѫ��

    void ShortAttack() { _health -= SHORT_ATTACK; }//��ս��Ѫ
    void LongAttack() { _health -= LONG_ATTACK; }//Զս��Ѫ
private:
    double _health;//����ֵ
};