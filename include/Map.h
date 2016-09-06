
#pragma once

#include"Common.h"
#include"Tower.hpp"

class Map {
public:
    Map(std::string Filename);//constructor

    void RefreshTower(bool reverse = false);//��������reverse�����Ƿ���ΪBW����ǿ�ƻ�ɫ
    void RefreshProp(); //���µ��ߣ��޸�_prop��_prop_pos
    void ConsumeProp(); //���ĵ���

    void ShortAttack();//������
    void LongAttack();//��Զ��
    void Attack(bool critical);

    inline unsigned char GetPointColor(const Point& p) const { return _map[int(p.x)][int(p.y)]; }//return 0 or 255 in the map
    inline Point GetFocus() const { return _targets[_focus]; }//return _focus
    inline double GetTowerHealth() const { return _tower.GetHealth(); }//return ����Ѫ��
    inline Point Map::GetPropPos() const { return _prop_pos; }//return ����λ��
    inline Prop Map::GetProp() const { return _prop; }// return ��������

private:

    void RefreshFocus(bool reverse = false);//���������㣬reverse�����Ƿ�ǿ�ƻ�ɫ

    int _map_size;
    unsigned char _map[256][256];

    std::vector<Point> _targets; //Ŀ���
    int _targets_size; //Ŀ�������
    int _focus; //��ǰĿ���
    Tower _tower;//��

    Point _prop_pos;//��������λ��
    Prop _prop; // ��������

    Random _random;


};
