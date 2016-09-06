

#pragma once

#include"Common.h"

class Tower {
public:
    void Reset() { _health = TOWER_HEALTH; }//����ֵ����

    double GetHealth() const { return _health; }//����Ѫ��

    void ShortAttack() { _health -= SHORT_ATTACK; }//��ս��Ѫ
    void LongAttack() { _health -= LONG_ATTACK; }//Զս��Ѫ
    void Attack(bool critical) { //Զ/����Ѫ
        if (critical) ShortAttack(); else LongAttack();
    }
private:
    double _health;//����ֵ
};