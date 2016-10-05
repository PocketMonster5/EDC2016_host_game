/*
 * ��ͼ����Ϊ
 */

#pragma once

#include"Common.h"
#include"Target.hpp"


#include<iostream>
#include<fstream>
#include<vector>

class Map {
public:
    //constructor
    Map(std::string Filename) {
        // load file
        std::ifstream in(Filename);
        if (!in) {
            std::cout << "[Error] Cannot load file " << Filename << std::endl;
            system("pause");
            exit(1);
        }

        in >> _map_size;

        for (int i = 0; i < _map_size; ++i)
            for (int j = 0; j < _map_size; ++j)
                _map[i][j] = getNum(in);

        _targets_size = getNum(in);

        _targets.resize(_targets_size);
        for (int i = 0; i < _targets_size; ++i) {
            _targets[i].x = getNum(in); _targets[i].y = getNum(in);
        }

        in.close();

        // init
        _focus = _random.Rand() % (_targets_size);

        RefreshProp();
    }

    //��������reverse�����Ƿ���ΪBW����ǿ�ƻ�ɫ
    void RefreshTarget(bool reverse = false) {
        RefreshFocus(reverse);
        _target.Reset();
        IsTarget = true;
        TargetSuspend = 0;
    }
    //���µ��ߣ��޸�_prop��_prop_pos
    void RefreshProp() {
		//ѡ�ֺ������������ֵ���
        //TODO ��һ��ʱ�����ֵ���
        _prop = (Prop)(_random.Rand() % (PROP_SIZE - 1) + 1); // ����0��NULL����

        _prop_pos.x = _random.Rand() % _map_size;
        _prop_pos.y = _random.Rand() % _map_size;
    }
    //���ĵ���
    void ConsumeProp() {
        //TODO �Զ����ɵ���
        _prop = PropET;
        _prop_pos.y = _prop_pos.x = 0;
    }

    //������
    void ShortAttack() {
        _target.ShortAttack();
    }
    //��Զ��
    void LongAttack() {
        _target.LongAttack();
    }
    //������(Զ/��)
    void Attack(bool critical) {
        if (critical) ShortAttack(); else LongAttack();
    }

    inline unsigned char GetPointColor(const Point& p) const { return _map[int(p.x)][int(p.y)]; }//return 0 or 255 in the map
    inline Point GetFocus() const { return _targets[_focus]; }//return _focus
    inline double GetTargetHealth() const { return _target.GetHealth(); }//return ����Ѫ��
    inline Point Map::GetPropPos() const { return _prop_pos; }//return ����λ��
    inline Prop Map::GetProp() const { return _prop; }// return ��������

private:
    //������
    unsigned char getNum(std::ifstream& in) {
        int v;
        in >> v;
        return (unsigned char)v;
    }

    //���������㣬reverse�����Ƿ�ǿ�ƻ�ɫ
    void RefreshFocus(bool reverse = false) {
        std::vector<int> temp;
        if (reverse)
        {
            // select another target with a different color
            unsigned char color = GetPointColor(_targets[_focus]);//the color of current focus

            for (int i = 0; i < _targets_size; ++i)  
                if (i != _focus && GetPointColor(_targets[i]) != color)
                    temp.push_back(i);

            _focus = temp[_random.Rand() % temp.size()];
        }
        else
        {
            // select another target         
            int next_focus = _random.Rand() % (_targets_size - 1);

            if (next_focus < _focus) _focus = next_focus;
            else _focus = next_focus + 1;
        }
    }

    int _map_size;
    unsigned char _map[256][256];

    std::vector<Point> _targets; //Ŀ���
    int _targets_size; //Ŀ�������
    int _focus; //��ǰĿ���
    Target _target;//��

    Point _prop_pos;//��������λ��
    Prop _prop; // ��������

    Random _random;

	//����cd�ڼ���
	int _prop_cd;
};
