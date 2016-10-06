#pragma once

#include <string>


#include "Common.h"
#include "my_string.hpp"

struct CarData
{
    //С����Ϣ
    double _health;//Ѫ��
    Point _pos;//λ��
    unsigned char _color;//С�����ڵ����ɫ�����ڰ�
    bool _long_attack_map;//�Ƿ񱻵�ͼС����
    bool _short_attack_map;//�Ƿ񱻵�ͼ�󹥻�
    bool _attack_plane;//�Ƿ񱻷ɻ�����
    bool _heal_plane;//�Ƿ񱻷ɻ���Ѫ
    bool _air_command;//�Ƿ����ƿ�Ȩ
    int _count_air_command;//��¼�ƿ�Ȩ�غ���

	std::string getString() {
		char Out[50];
		sprintf(Out, "%f (%d,%d) %c %d %d %d %d %d %d", _health,_pos.x,_pos.y,_color,_long_attack_map,_short_attack_map,_attack_plane,_heal_plane,_air_command,_count_air_command);
		return Out;
		// return all data
	};

};


struct GameData
{
    //�غ���
    int _round;
    //С����Ϣ
    CarData carData[2];//�������camel����

    //�ɻ���Ϣ
    Point planePos;
    PlaneStatus planeStatus;


    //����Ϣ
    double targetHealth;//����ֵ

    //��ͼ��̬��Ϣ
    Point _prop_pos;//��������λ��
    PropType _prop; // ��������

	std::string getString() {

		char Out[50];
		sprintf(Out, "%d (%d,%d) %d %f (%d,%d) %d ", _round, planePos.x, planePos.y, planeStatus, targetHealth, _prop_pos.x, _prop_pos.y, _prop);
		return (Out + carData[Red].getString() + carData[Blue].getString()+'\n');
		// ( call carData.getString()) and return all data 
	}

	MyString getComunicationString() {
		char s[20] = "TEST COMMUNICATION";
		return MyString(s, 20);
		// TODO IT LATER
	}
};

