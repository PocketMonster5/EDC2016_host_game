// Created by cyx15 & ty15, 2016.9


#include"Game.h"

using namespace std;

int TargetSuspend = 0;  //TODO �ƶ������ʵ�λ��
bool IsTarget = false; //TODO

int test_Map() {
    Map map("./data/test.txt");

    // Refresh Target Test
    for (int i = 0; i < 20; ++i) {
        map.RefreshTarget();
        Point p = map.GetFocus();
        cout << "Focus (" << int(p.x) << ", " << int(p.y) << ")" << (int)map.GetPointColor(p) << endl;
    }

    // Refresh Prop Test
    for (int i = 0; i < 20; ++i)
    {
        map.RefreshProp();
        Point p = map.GetPropPos();
        Prop pr = map.GetProp();
        cout << "The prop is at: " << "(" << int(p.x) << ", " << int(p.y) << ") " << pr << endl;
    }

    system("pause");
    return 0;
}

int test_Plane()
{

    Point p1(30, 100);//����С��1
    Point p2(70, 200);//����С��2

    Plane plane_test;
    Point p_plane(30, 140);//����ɻ�λ��ƪp_plane
    Point p_plane2(50, 80); //�ɻ�λ��2

    //���Կ�ʼ
    plane_test.Refresh(p_plane, 0); cout << "��ǰλ�� 30��140" << endl;
    cout << "PlaneStatus is:" << plane_test.GetPlaneStatus() << endl;//�����趨�ɻ�״̬
    cout << "p1 is in the AttackRange ? " << plane_test.IsInAttackRange(p1) << endl;
    cout << "p2 is in the AttackRange ? " << plane_test.IsInAttackRange(p2) << endl;//���Թ�����Χ�ж�
    cout << "p1 is in the HealRange   ? " << plane_test.IsInHealRange(p1) << endl;
    cout << "p2 is in the HealRange   ? " << plane_test.IsInHealRange(p2) << endl;//�������Ʒ�Χ�ж�
    cout << endl << endl;

    plane_test.Refresh(p_plane2, 255); cout << "��ǰλ�� 70��200" << endl;
    cout << "PlaneStatus is:" << plane_test.GetPlaneStatus() << endl;//�����趨�ɻ�״̬
    cout << "p1 is in the AttackRange ? " << plane_test.IsInAttackRange(p1) << endl;
    cout << "p2 is in the AttackRange ? " << plane_test.IsInAttackRange(p2) << endl;//���Թ�����Χ�ж�
    cout << "p1 is in the HealRang    ? " << plane_test.IsInHealRange(p1) << endl;
    cout << "p2 is in the HealRang    ? " << plane_test.IsInHealRange(p2) << endl;//�������Ʒ�Χ�ж�
    system("pause");
    return 0;
}

int test_Car()
{
    Car car_test;
    Point p1(30, 100);//����С��λ��1
    Point p2(70, 200);//����С��λ��2
    car_test.ResetCar();//��ʼ��С��

    car_test.Refresh(p1, 0);//���õ�λ��1����ɫ
    car_test.LongAttackedByMap();//����ͼС����
    car_test.AttackedByPlane();//���ɻ�����
    cout << car_test.GetHealth() << " " << car_test.GetLongAttackMap() << " " << car_test.GetShortAttackMap() << " " << car_test.GetAttackPlane() << " " << car_test.GetHealPlane() << " " << car_test.CommandAir() << endl;//��ʾ״̬

    car_test.Refresh(p2, 255);//���õ�λ��2����ɫ
    car_test.ShortAttackedByMap();//����ͼ�󹥻�
    car_test.HealedByPlane();//���ɻ�����
    cout << car_test.GetHealth() << " " << car_test.GetLongAttackMap() << " " << car_test.GetShortAttackMap() << " " << car_test.GetAttackPlane() << " " << car_test.GetHealPlane() << " " << car_test.CommandAir() << endl;//��ʾ״̬

    car_test.Refresh(p1, 0);//�ص�λ��1����ɫ
    car_test.AcquireAirCommand();//��ȡ�ƿ�Ȩ
    cout << car_test.GetHealth() << " " << car_test.GetLongAttackMap() << " " << car_test.GetShortAttackMap() << " " << car_test.GetAttackPlane() << " " << car_test.GetHealPlane() << " " << car_test.CommandAir() << endl;//��ʾ״̬

    //ͣ����λ��1����ɫ
    for (int i = 0; i < 5; ++i) {
        car_test.Refresh(p1, 0);
        cout << car_test.GetHealth() << " " << car_test.GetLongAttackMap() << " " << car_test.GetShortAttackMap() << " " << car_test.GetAttackPlane() << " " << car_test.GetHealPlane() << " " << car_test.CommandAir() << endl;//��ʾ״̬
    }

    system("pause");
    return 0;
}

int test_Game()
{
    Game game;
    
    for (int i = 0; i < 15; ++i) {
        cout << "Round " << game.GetRoundCount() << endl;
        game.Refresh(Point(0, 0), Point(0, 0), Point(0, 0));
    }

    system("pause");
    return 0;
}

int main() {

    cout << "======= <test> Map =========" << endl;
    test_Map();

    cout << "======= <test> Plane =========" << endl;
    test_Plane();

    cout << "======= <test> Car =========" << endl;
    test_Car();

    cout << "======= <test> Game =========" << endl;
    test_Game();

    return 0;
}
