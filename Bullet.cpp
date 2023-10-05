#include "Bullet.h"

Bullet::Bullet(float x, float y, float angle)
{
    this->angle = angle;
    bullet.setRadius(1);
    bullet.setPosition(x, y);
}

void Bullet::Play(std::list<Bullet>& Bul_list, std::list<Bullet>::iterator& itErase, int bull_behavior)
{
    //����������� ��������� ���� (������������ ��� ��������)
    if (bull_behavior == 1)
    {
        //������� �������� ���� ��� ������� ���� ������.
        if ((bullet.getPosition().x >= x_window_size) || (bullet.getPosition().x <= 0) || (bullet.getPosition().y >= y_window_size) || (bullet.getPosition().y <= 0))
        {
            /* ��������� ����� ��������� � � ���� ������������ ���, ������� �������� ��� �������.
             ������ ��������� ��������� �� ��������� �������. ����� �� ������� ��������� �������, �� �������
             ��������� ����� ��������.
             ��������, ���������� ���������� ��� �������� �� 1, ������� � ����� main ��������� �� ������������
             (��� �� �� ������������ 2 ����, ���� ����� �������� ������)

             ���� � �� ������� � ���� if, �������� ������������� � else.*/
            auto deleted = itErase;
            ++itErase;
            Bul_list.erase(deleted);
        }
        else
            ++itErase;
    }
    else
    {
        //������� ������������ �� ���� ����
        if ((bullet.getPosition().x >= x_window_size) || (bullet.getPosition().x <= 0))
        {
            angle *= -1;
        }
        if (bullet.getPosition().y >= y_window_size)
        {
            float a = 270 - angle;
            angle = angle + 2 * a;
        }
        if (bullet.getPosition().y <= 0)
        {
            angle = 180 - angle;
        }
        ++itErase;
    }

    float x_move = 5 * sin(angle * 0.0174532925);//������� �� �������� � ������
    float y_move = -5 * cos(angle * 0.0174532925);//������� �� �������� � ������

    //������� � �������� �������
    bullet.move(x_move, y_move);
}