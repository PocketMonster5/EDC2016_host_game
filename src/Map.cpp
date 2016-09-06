


#include"Map.h"

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<sstream>
#include<string>


using namespace std;

static unsigned char getNum(ifstream& in) {
    int v;
    in >> v;
    return (unsigned char)v;
}

Map::Map(string Filename)
{
    // load file
    ifstream in(Filename);
    if (!in) {
        cout << "[Error] Cannot load file " << Filename << endl;
        system("pause");
        exit(1);
    }

    in >> _map_size;

    for (int i = 0; i < _map_size; ++i)
        for (int j = 0; j < _map_size; ++j)
            _map[i][j] = getNum(in);

    _targets_size = getNum(in);

    _targets.resize(_targets_size);
    for (int i = 0; i < _targets_size; ++i)
    {
        _targets[i].x = getNum(in); _targets[i].y = getNum(in);
    }

    in.close();

    // init
    _focus = _random.Rand() % (_targets_size);

    RefreshProp();
}

void Map::RefreshFocus(bool reverse /*=false*/)
{
    vector<int> temp;
    if (reverse)
    {
        // select another tower with a different color
        unsigned char color = GetPointColor(_targets[_focus]);//the color of current focus

        for (int i = 0; i < _targets_size; ++i)          //num用来记录备选target数目
            if (i != _focus && GetPointColor(_targets[i]) != color)
                temp.push_back(i);

        _focus = temp[_random.Rand() % temp.size()];
    }
    else
    {
        // select another tower         
        int next_focus = _random.Rand() % (_targets_size - 1);

        if (next_focus < _focus) _focus = next_focus;
        else _focus = next_focus + 1;
    }
}

void Map::RefreshTower(bool reverse /*= false*/) {
    RefreshFocus(reverse);
    _tower.Reset();
    IsTower = true;
    TowerSuspend = 0;
}

void Map::ShortAttack() {
    _tower.ShortAttack();
}
void Map::LongAttack() {
    _tower.LongAttack();
}
void Map::Attack(bool critical)
{
    if (critical) ShortAttack(); else LongAttack();
}
void Map::RefreshProp() {
    //TODO 部分区域(塔和玩家附近)不得出现道具
    _prop = (Prop)(_random.Rand() % (PROP_SIZE - 1) + 1); // 避免0号NULL道具
    
    _prop_pos.x = _random.Rand() % _map_size;
    _prop_pos.y = _random.Rand() % _map_size;
}

void Map::ConsumeProp()
{
    _prop = PropET;
    _prop_pos.y = _prop_pos.x = 0;
}

