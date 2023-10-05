#include "Aircraft.h"
#include "Settings.h"

Aircraft::Aircraft(float x, float y, float speed, float angle, std::string img)
{
    x_coordinate = x;
    y_coordinate = y;
    this->speed = speed;
    this->angle = angle;

    texture.loadFromFile(img);;
    sprite.setTexture(texture);
    sprite.setPosition(x_coordinate, y_coordinate);
    sprite.setOrigin(26, 32);
}

void Aircraft::Play(float x_cours, float y_cours, std::list<Bullet>& Bul_list, clock_t& t0)
{
    double rotation_angle, x_cursor_plane, y_cursor_plane, Arctan_rad;

    //������ �������������

    //���������� ���� ����� �������� � ���������
    x_cursor_plane = x_cours - sprite.getPosition().x;//���������� �� � ����� �������� � ��������� 
    y_cursor_plane = y_cours - sprite.getPosition().y;//���������� �� �
    Arctan_rad = x_cursor_plane / y_cursor_plane;
    Arctan_rad = abs(atan(Arctan_rad));
    Arctan_rad *= 57.2956;//���������� ���� � ��������


    /*���������� ���� ����� ����������(�� ������ ��������) � �������
    ���� ������ � 1 �������� �� ��������, �� ���� ��������� �� �����                                   ������������ ���������:     ---------   */
    if ((x_cursor_plane > 0) && (y_cursor_plane > 0))//���� ������ �� 2 ��������, �� ������ �� 180 ���� �� ������� � ��������      | 4 | 1 |
        Arctan_rad = 180 - Arctan_rad;                                                               //                            |-------|
    if ((x_cursor_plane < 0) && (y_cursor_plane > 0))//���� � 3, �� ��������� 180 ��������                                         | 3 | 2 |
        Arctan_rad += 180;                                                                           //                            ---------
    if ((x_cursor_plane < 0) && (y_cursor_plane < 0))//���� �� � 4 ��������, �� ������ ��� �� 360 ��������
        Arctan_rad = 360 - Arctan_rad;

    //��������� ����, �� ������� ���� ��������� �������
    rotation_angle = Arctan_rad - sprite.getRotation();
    if (rotation_angle < 0) { rotation_angle = 360 + rotation_angle; }//�� ������ ���� ���� ��������� �������������.


    if (rotation_angle < 1)
        angle += rotation_angle;
    else if (rotation_angle > 359)
        angle -= 360 - rotation_angle;
    else if (rotation_angle < 180) //���� ���� �������� ������ 180, �� ������� �� �����
        angle++;
    else if (rotation_angle > 180)//���� ������, �� �����
        angle--;
    //� ������ ������ ������� �� �����, ���� ����� 0

    if (angle > 360) { angle = 0.1; }
    if (angle < 0) { angle = 359.9; }

    //������� ����������� �� ���� ���� � ���������������
    /*if (sprite.getPosition().x > x_window_size) { sprite.setPosition(0, sprite.getPosition().y); }
    if (sprite.getPosition().x < 0) { sprite.setPosition(x_window_size, sprite.getPosition().y); }
    if (sprite.getPosition().y > y_window_size) { sprite.setPosition(sprite.getPosition().x, 0); }
    if (sprite.getPosition().y < 0) { sprite.setPosition(sprite.getPosition().x, y_window_size); }*/

    //������������ � ����� 100 100
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::R))) { sprite.setPosition(500, 500); }

    //��������
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Q)))
    {
        if ((double)(clock() - t0) / CLOCKS_PER_SEC > 0.1)
        {
            Bullet shot(sprite.getPosition().x + 40 * sin(angle * 0.0174532925), sprite.getPosition().y - 40 * cos(angle * 0.0174532925), angle);
            Bul_list.push_back(shot);
            t0 = clock();
            //std::cout << angle << "\t" << sin(angle * 0.0174532925) << "\t" << cos(angle * 0.0174532925) << std::endl;
        }
    }

    //���������� �������� �� � � �� �
    float x_move = speed * sin(angle * 0.0174532925);//������� �� �������� � �������
    float y_move = -speed * cos(angle * 0.0174532925);//������� �� �������� � �������

    //������� � �������� �������
    sprite.setRotation(angle);
    //sprite.move(x_move, y_move);
}
