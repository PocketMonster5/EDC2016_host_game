
#pragma once


#include <vector>

#include "Common.h"

class Prop {

public:

	Prop()
		: _waiting_count(0)
	{
	}

	// ���������Ҫˢ�£�����true�����򷵻�false
	bool Refresh() {
		if (PropET == _prop) {
			++_waiting_count;
			if (_waiting_count >= PROP_CD) {
				_waiting_count = 0;
				return true;
			}
		}

		return false;
	}

	void Generate(std::vector<Point> avoid_point_list, int _map_size, double distance = 50) {
		// ����һ�����ߣ����Ҳ��ܷǳ������������ļ�����(С��,Ŀ���ʲô��)
		for(int i=0;i<10;i++)
		{
			_point.x = _random.Rand() % _map_size;
			_point.y = _random.Rand() % _map_size;
			if (_point.getDistance(avoid_point_list[0]) >= distance && _point.getDistance(avoid_point_list[1]) >= distance && _point.getDistance(avoid_point_list[2]) >= distance)
				break;
		}

		// ��һ��ʱ�����ֵ���
		_prop = (PropType)(_random.Rand() % (PROP_SIZE - 1) + 1); // ����0��NULL����

		
	}

	bool CheckPoint(Point p) { //���˵��Ƿ���� _point �㹻��
		return p.getDistance(_point) < PROP_DISTANCE;
	}

	inline Point getPoint() const { return _point; }
	inline PropType getPropType() const { return _prop; }

private:

	Point _point;
	PropType _prop;

	Random _random;

	int _waiting_count;

};