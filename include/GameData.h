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
        char buffer[512];
        sprintf(buffer, " [ HP %.1lf pos (%d,%d) color %d A L%d S%d PA%d PH%d AC%d(%d) ] ",
            _health, _pos.x, _pos.y, _color, 
            _long_attack_map, _short_attack_map, 
            _attack_plane, _heal_plane, 
            _air_command, _count_air_command);
        return buffer;
        // return all data
    }

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


    //Ŀ�����Ϣ
    double targetHealth;//����ֵ
    Point target_pos; //Ŀ���λ��

    //��ͼ��̬��Ϣ
    Point _prop_pos;//��������λ��
    PropType _prop; // ��������

    std::string getString() {

        char buffer[512];
        sprintf(buffer, " round %d : target (%d,%d) %.1lf ; plane (%d,%d) %d ; prop (%d,%d) %d ; ",
            _round,
            target_pos.x, target_pos.y, targetHealth,
            planePos.x, planePos.y, planeStatus,
            _prop_pos.x, _prop_pos.y, _prop);
        return (buffer + carData[Red].getString() + carData[Blue].getString());
        // ( call carData.getString()) and return all data 
    }

	MyString getComunicationString() {
		char s[20] = "TEST COMMUNICATION";
		return MyString(s, 20);
		// TODO IT LATER
	}
};

