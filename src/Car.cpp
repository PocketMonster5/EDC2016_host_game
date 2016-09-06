#include"Common.h"
#include"Car.h"

void Car::Refresh(Point p, unsigned char c)
{
    _pos = p;
    _color = c;
    _long_attack_map = false;
    _short_attack_map = false;
    _attack_plane = false;
    _heal_plane = false;

    if (_count_air_command > AIR_COMMAND_TIME) {
        DismissAirCommand();
        _count_air_command = 0;
    }
    if (_air_command) _count_air_command++;

}

// Attack
void Car::LongAttackedByMap()
{
    _health -= MAP_LONG_ATTACK;
    _long_attack_map = true;
}
void Car::ShortAttackedByMap()
{
    _health -= MAP_SHORT_ATTACK;
    _short_attack_map = true;
}
void Car::AttackedByMap(bool critical)
{
    if (critical) ShortAttackedByMap(); else LongAttackedByMap();
}
void Car::AttackedByPlane()
{
    _health -= PLANE_ATTACK;
    _attack_plane = true;
}

// Heal
void Car::HealedByPlane()
{
    _health += PLANE_HEAL;
    _heal_plane = true;
}

void Car::HealByProp()
{
    _health += HEALTH_PROP;
}

// AirCommand
void Car::AcquireAirCommand()
{
    _air_command = true;
}
void Car::DismissAirCommand()
{
    _air_command = false;
    _count_air_command = 0;
}

// Reset
void Car::ResetCar()
{
    _health = INITIAL_BlOOD;
    _count_air_command = 0;
    _air_command = false;
    _long_attack_map = false;
    _short_attack_map = false;
    _attack_plane = false;
    _heal_plane = false;

}