

#pragma once

#include"Common.h"

class Target {
public:

    void Reset() { //����ֵ����
		_health = TARGET_HEALTH; 
		_waiting_count = 0;
		_alive = true;
	}

	bool Refresh() { 
		if (!_alive) {
			++_waiting_count;
			if (_waiting_count >= TARGET_CD) {
				_waiting_count = 0;
				return true;
			}
		}
		return false;
	} //refresh

    void ShortAttack() { _health -= SHORT_ATTACK; }//��ս��Ѫ
    void LongAttack() { _health -= LONG_ATTACK; }//Զս��Ѫ
    void Attack(bool critical) { if (critical) ShortAttack(); else LongAttack(); } //Զ/����Ѫ

	inline double GetHealth() const { return _health; }//����Ѫ��
	inline bool isAlive() const { return _alive;  }

private:

	
    double _health;//����ֵ

	bool _alive;

	int _waiting_count;

};