/*
 * 地图的行为
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

    //更换塔，reverse代表是否因为BW道具强制换色
    void RefreshTarget(bool reverse = false) {
        RefreshFocus(reverse);
        _target.Reset();
        IsTarget = true;
        TargetSuspend = 0;
    }
    //更新道具，修改_prop和_prop_pos
    void RefreshProp() {
		//选手和塔附近不出现道具
        //TODO 隔一段时间会出现道具
        _prop = (Prop)(_random.Rand() % (PROP_SIZE - 1) + 1); // 避免0号NULL道具

        _prop_pos.x = _random.Rand() % _map_size;
        _prop_pos.y = _random.Rand() % _map_size;
    }
    //消耗道具
    void ConsumeProp() {
        //TODO 自动生成道具
        _prop = PropET;
        _prop_pos.y = _prop_pos.x = 0;
    }

    //塔近攻
    void ShortAttack() {
        _target.ShortAttack();
    }
    //塔远攻
    void LongAttack() {
        _target.LongAttack();
    }
    //塔攻击(远/近)
    void Attack(bool critical) {
        if (critical) ShortAttack(); else LongAttack();
    }

    inline unsigned char GetPointColor(const Point& p) const { return _map[int(p.x)][int(p.y)]; }//return 0 or 255 in the map
    inline Point GetFocus() const { return _targets[_focus]; }//return _focus
    inline double GetTargetHealth() const { return _target.GetHealth(); }//return 塔的血量
    inline Point Map::GetPropPos() const { return _prop_pos; }//return 道具位置
    inline Prop Map::GetProp() const { return _prop; }// return 道具类型

private:
    //读数字
    unsigned char getNum(std::ifstream& in) {
        int v;
        in >> v;
        return (unsigned char)v;
    }

    //更换争抢点，reverse代表是否强制换色
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

    std::vector<Point> _targets; //目标点
    int _targets_size; //目标点总数
    int _focus; //当前目标点
    Target _target;//塔

    Point _prop_pos;//道具所在位置
    Prop _prop; // 道具类型

    Random _random;

	//道具cd期计数
	int _prop_cd;
};
