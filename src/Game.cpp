#include "Game.h"
#include <iostream>

Game::Game(std::string filename)
    : _map(filename)
    , _game_status(Running)
    , _round_count(0)
{

}

void Game::Refresh(const Point & p1, const Point & p2, const Point & pp)
{
    //ˢ������λ��
    _car[0].Refresh(p1, _map.GetPointColor(p1));
    _car[1].Refresh(p2, _map.GetPointColor(p2));
    _plane.Refresh(pp, _map.GetPointColor(_map.GetFocus()));

    //����
    CheckProp(_car[Red]);
    CheckProp(_car[Blue]);
    //TODO ���ߵĲ����͸���


    //Ѫ������
    SettleDamage();

    //����ͼ
    RefreshTarget();

    //�ж���Ϸ�Ƿ����
    Judge();	
	
	//�޸�gameData��λ����Ϣ
}

void Game::CheckProp(Car& car_prop)
{
    if (car_prop.GetPoint() == _map.GetPropPos())
    {
        switch (_map.GetProp())
        {
        case PropET: //����0�� Empty
            break;
        case PropHP: //����1����+HP)
            car_prop.HealByProp();
            break;
        case PropBW: //����2����BlackWhite��
            _map.RefreshTarget(true);
            _plane.SetPlaneStatus(_map.GetPointColor(_map.GetFocus()));
            break;
        case PropAC: //����3�� ��AC��
            car_prop.AcquireAirCommand();
            break;
        }
        _map.RefreshProp();
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

    if (IsTarget) {

        Point focus_pos = _map.GetFocus();
        unsigned char tower_color = _map.GetPointColor(focus_pos)
            , r_color = _map.GetPointColor(r_pos)
            , b_color = _map.GetPointColor(b_pos);
        double r_distance = r_pos.getDistance(focus_pos)
            , b_distance = b_pos.getDistance(focus_pos);
        bool critical = (r_color == tower_color && r_distance <= CRITICAL_DISTANCE)
            || (b_color == tower_color && b_distance <= CRITICAL_DISTANCE);

        if (r_color == tower_color && b_color == tower_color) { //��λ����ȷ��ɫ
            if (r_distance == b_distance) { //��λ����ȷ��ɫ�������߾������
                Attack(Red, critical);
                Attack(Blue, critical);
            }
            else { //��λ����ȷ��ɫ�������߾��벻���
                if (r_distance < b_distance) Attack(Blue, critical);
                else  Attack(Red, critical);
            }
        }
        else if (r_color != tower_color && b_color != tower_color) { //��λ�ڴ�����ɫ
            Attack(Red, critical);
            Attack(Blue, critical);
        }
        else {
            if (r_color == tower_color) Attack(Blue, critical); //ֻ�к췽λ����ȷɫ��
            else Attack(Red, critical); //ֻ������λ����ȷɫ��
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
        std::cout << "[Error] Unknown Plane Status!" << _plane.GetPlaneStatus() << std::endl;
        system("pause");
    }


}
void Game::RefreshTarget() {
    if (!IsTarget) {
        TargetSuspend++;
        if (TargetSuspend == TARGET_SUSPEND) _map.RefreshTarget();
    }
    else {
        if (_map.GetTargetHealth() < 0) {
            IsTarget = false;
            TargetSuspend = 0;
        }
    }
}

void Game::Judge()
{
    if (_round_count < MAX_ROUND)//����������ʣ��ʱ��
    {
        if (_car[Red].IsAlive() && _car[Blue].IsAlive()) //��������
        {
            _round_count++;
            _game_status = Running;
        }
        else if (!_car[Red].IsAlive() && !_car[Blue].IsAlive()) //ͬʱ������ƽ��
            _game_status = Tie;
        else if ( _car[Red].IsAlive() && !_car[Blue].IsAlive())
            _game_status = RedWin;
        else if (!_car[Red].IsAlive() &&  _car[Blue].IsAlive())
            _game_status = BlueWin;

    }
    else //����ʱ�䵽
    {
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
        std::cout << "[Game] Game Over: Tie!" << std::endl;
        break;
    case RedWin:
        std::cout << "[Game] Game Over: Red Win!" << std::endl;
        break;
    case BlueWin:
        std::cout << "[Game] Game Over: Blue Win!" << std::endl;
        break;
    default:
        break;
    }
}



