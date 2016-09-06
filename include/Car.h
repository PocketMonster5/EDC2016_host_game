
#pragma once

#include"Common.h"
class Car {
public:

    void Refresh(Point p, unsigned char c);//�޸ĵ�ǰλ�ã�����Ѫ����ص�����������״̬��Ϊfalse������ƿ�Ȩ�غ���

    void LongAttackedByMap();//��ͼС��������Ѫ+��״̬
    void ShortAttackedByMap();//��ͼ�󹥻�
    void AttackedByMap(bool critical); 

    void AttackedByPlane();//�ɻ�����

    void HealedByPlane();//�ɻ���Ѫ
    void HealByProp();//���߼�Ѫ

    void AcquireAirCommand();//����ƿ�Ȩ������һ���غ���
    void DismissAirCommand();//����ƿ�Ȩ�����count

    inline bool IsAlive() { return (_health >= DEATH_BlOOD); }//�Ƿ���
    inline bool CommandAir() const { return _air_command; }//�Ƿ����ƿ�Ȩ

    inline Point GetPoint() const { return this->_pos; }//����С��λ��
    inline double GetHealth() const { return _health; }//����Ѫ��(���䣩
    inline bool GetLongAttackMap() const { return _long_attack_map; }//�����Ƿ񱻵�ͼС����(���䣩
    inline bool GetShortAttackMap() const { return _short_attack_map; }//�����Ƿ񱻵�ͼС����(���䣩
    inline bool GetAttackMap() const {  return _long_attack_map || _short_attack_map; } //�����Ƿ񱻵�ͼ����
    inline bool GetAttackPlane() const { return _attack_plane; }//�����Ƿ񱻷ɻ�����(���䣩
    inline bool GetHealPlane() const { return _heal_plane; }//�����Ƿ񱻷ɻ���Ѫ(���䣩

    void ResetCar();//��ʼ��С�����������ƿջغϣ����䣩

private:
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
