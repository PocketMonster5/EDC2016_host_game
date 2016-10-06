#include "Game.h"
#include <iostream>
#include <vector>

using namespace std;

Game::Game(string filename)
    : _map(filename)
    , _game_status(Running)
    , _round_count(0)
{

}

void Game::Refresh(const Point & p1, const Point & p2, const Point & pp)
{
    //刷新所有位置
    _car[0].Refresh(p1, _map.GetPointColor(p1));
    _car[1].Refresh(p2, _map.GetPointColor(p2));
    _plane.Refresh(pp, _map.GetPointColor(_map.GetTargetPoint()));


	//更新 .. . ..
	if (_prop.Refresh()) GenerateProp();
	if (_map.RefreshTarget()) _map.GenerateTarget();

    //道具
    CheckProp(_car[Red]); CheckProp(_car[Blue]);

    //血量计算
    SettleDamage();


    //判断游戏是否结束
    Judge();	

}

GameData Game::getGameData()
{
	GameData g;
	g._round=_round_count;
	g.planePos = _plane.GetPlanePos();
	g.planeStatus = _plane.GetPlaneStatus();
	g.targetHealth = _map.GetTargetHealth();
	g._prop_pos = _prop.getPoint();
	g._prop = _prop.getPropType();
	for (int i = 0; i < 2; i++)
	{
		g.carData[i]._health = _car[i].GetHealth();
		g.carData[i]._pos = _car[i].GetPoint();
		g.carData[i]._color = _map.GetPointColor(_car[i].GetPoint());
		g.carData[i]._short_attack_map = _car[i].GetShortAttackMap();
		g.carData[i]._long_attack_map = _car[i].GetLongAttackMap();
		g.carData[i]._attack_plane = _car[i].GetAttackPlane();
		g.carData[i]._heal_plane = _car[i].GetHealPlane();
		g.carData[i]._air_command = _car[i].CommandAir();
		g.carData[i]._count_air_command = _car[i].GetCountAirCommand();
	}
	return g;
}

void Game::CheckProp(Car& c) 
{

    if (_prop.CheckPoint(c.GetPoint()))
    {
		switch (_prop.getPropType())
		{
		case PropET: //道具0： Empty
			break;
		case PropHP: //道具1：（+HP)
			c.HealByProp();
			break;
		case PropBW: //道具2：（BlackWhite）
			_map.GenerateTarget(true);
			_plane.SetPlaneStatus(_map.GetPointColor(_map.GetTargetPoint()));
			break;
		case PropAC: //道具3： （AC）
			c.AcquireAirCommand();
			break;
		}
		
		GenerateProp();
    }
}
void Game::ShortAttack(CarName car_name) {
    _car[car_name].ShortAttackedByMap();
    _map.ShortAttack();
}
void Game::LongAttack(CarName car_name) {
    _car[car_name].LongAttackedByMap();
    _map.LongAttack();
}

void Game::Attack(CarName car_name, bool critical)
{
    _car[car_name].AttackedByMap(critical);
}

void Game::SettleDamage() {
    Point r_pos = _car[Red].GetPoint();
    Point b_pos = _car[Blue].GetPoint();

    if (_map.HaveTarget()) {

        Point tid_pos = _map.GetTargetPoint();
        unsigned char tower_color = _map.GetPointColor(tid_pos)
            , r_color = _map.GetPointColor(r_pos)
            , b_color = _map.GetPointColor(b_pos);
        double r_distance = r_pos.getDistance(tid_pos)
            , b_distance = b_pos.getDistance(tid_pos);
        bool critical = (r_color == tower_color && r_distance <= CRITICAL_DISTANCE)
            || (b_color == tower_color && b_distance <= CRITICAL_DISTANCE);

        if (r_color == tower_color && b_color == tower_color) { //都位于正确颜色
            if (r_distance == b_distance) { //都位于正确颜色，且两者距离相等
                Attack(Red, critical);
                Attack(Blue, critical);
            }
            else { //都位于正确颜色，且两者距离不相等
                if (r_distance < b_distance) Attack(Blue, critical);
                else  Attack(Red, critical);
            }
        }
        else if (r_color != tower_color && b_color != tower_color) { //都位于错误颜色
            Attack(Red, critical);
            Attack(Blue, critical);
        }
        else {
            if (r_color == tower_color) Attack(Blue, critical); //只有红方位于正确色区
            else Attack(Red, critical); //只有蓝方位于正确色区
        }
    }

    switch (_plane.GetPlaneStatus()) {
    case PlaneNone:
        break;
    case PlaneAttack:
        if (_plane.IsInAttackRange(r_pos)) _car[Red].AttackedByPlane();
        if (_plane.IsInAttackRange(b_pos)) _car[Blue].AttackedByPlane();
        break;
    case PlaneHeal:
        if (_plane.IsInHealRange(r_pos)) _car[Red].HealedByPlane();
        if (_plane.IsInHealRange(b_pos)) _car[Blue].HealedByPlane();
        break;
    default:
        cout << "[Error] Unknown Plane Status!" << _plane.GetPlaneStatus() << endl;
        system("pause");
    }


}

void Game::GenerateProp()
{
	vector<Point> point_list;
	point_list.push_back(_car[Red].GetPoint());
	point_list.push_back(_car[Blue].GetPoint());
	point_list.push_back(_map.GetTargetPoint());
	_prop.Generate(point_list, _map.GetMapSize()); 
}

void Game::Judge()
{
    if (_round_count < MAX_ROUND) //当比赛还有剩余时间
    {
		cout << getGameData().getString();//显示本回合信息。
		if (_car[Red].IsAlive() && _car[Blue].IsAlive()) //比赛继续
        {
            _round_count++;
            _game_status = Running;
        }
		else if (!_car[Red].IsAlive() && !_car[Blue].IsAlive()) //同时死亡，平局
		{
			_game_status = Tie; 
			std::cout << "[Game] No survior!" << endl;
		}
        else if ( _car[Red].IsAlive() && !_car[Blue].IsAlive())
			_game_status = RedWin;
        else if (!_car[Red].IsAlive() &&  _car[Blue].IsAlive())
            _game_status = BlueWin;

    }
    else //比赛时间到
    {
		cout << "[Game] Time out!" << endl;

        if (_car[Red].GetHealth() == _car[Blue].GetHealth())
            _game_status = Tie;
        else if (_car[Red].GetHealth() > _car[Blue].GetHealth())
            _game_status = RedWin;
        else
            _game_status = BlueWin;
    }

    switch (_game_status)
    {
    case Tie:
        cout << "[Game] Game Over: Tie!" << endl;
        break;
    case RedWin:
        cout << "[Game] Game Over: Red Win!" << endl;
        break;
    case BlueWin:
        cout << "[Game] Game Over: Blue Win!" << endl;
        break;
    default:
        break;
    }
}



