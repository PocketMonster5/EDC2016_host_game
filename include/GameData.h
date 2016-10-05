
#ifndef GAMEDATA_H
#define GAMEDATA_H
#include "Common.h"
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
    Prop _prop; // ��������
};

#endif#pragma once
