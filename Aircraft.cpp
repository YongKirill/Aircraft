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

    //ЕБАНАЯ ТРИГОНОМЕТРИЯ

    //Вычисление угла между курсором и самолетом
    x_cursor_plane = x_cours - sprite.getPosition().x;//расстояние по х между курсором и самолетом 
    y_cursor_plane = y_cours - sprite.getPosition().y;//расстояние по у
    Arctan_rad = x_cursor_plane / y_cursor_plane;
    Arctan_rad = abs(atan(Arctan_rad));
    Arctan_rad *= 57.2956;//вычисление угла в градусах


    /*Вычисление угла между вертикалью(из центра самолета) и куросом
    Если курсор в 1 четверти от самолета, то угол вычислять не нужно                                   Расположение четвертей:     ---------   */
    if ((x_cursor_plane > 0) && (y_cursor_plane > 0))//если курсор во 2 четверти, то отнять от 180 угол от курсора и самолета      | 4 | 1 |
        Arctan_rad = 180 - Arctan_rad;                                                               //                            |-------|
    if ((x_cursor_plane < 0) && (y_cursor_plane > 0))//если в 3, то прибавить 180 градусов                                         | 3 | 2 |
        Arctan_rad += 180;                                                                           //                            ---------
    if ((x_cursor_plane < 0) && (y_cursor_plane < 0))//если он в 4 четверти, то отнять его от 360 градусов
        Arctan_rad = 360 - Arctan_rad;

    //Вычисляем угол, на который надо повернуть самолет
    rotation_angle = Arctan_rad - sprite.getRotation();
    if (rotation_angle < 0) { rotation_angle = 360 + rotation_angle; }//На случай если угол получился отрицательным.


    if (rotation_angle < 1)
        angle += rotation_angle;
    else if (rotation_angle > 359)
        angle -= 360 - rotation_angle;
    else if (rotation_angle < 180) //Если угол поворота меньше 180, то поворот на право
        angle++;
    else if (rotation_angle > 180)//Если больше, то влево
        angle--;
    //В других случях поворот не нужен, угол равен 0

    if (angle > 360) { angle = 0.1; }
    if (angle < 0) { angle = 359.9; }

    //Условия перемещения от края окна к противоположому
    /*if (sprite.getPosition().x > x_window_size) { sprite.setPosition(0, sprite.getPosition().y); }
    if (sprite.getPosition().x < 0) { sprite.setPosition(x_window_size, sprite.getPosition().y); }
    if (sprite.getPosition().y > y_window_size) { sprite.setPosition(sprite.getPosition().x, 0); }
    if (sprite.getPosition().y < 0) { sprite.setPosition(sprite.getPosition().x, y_window_size); }*/

    //Телепортация в точку 100 100
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::R))) { sprite.setPosition(500, 500); }

    //Стрельба
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

    //Вычисление скорости по х и по у
    float x_move = speed * sin(angle * 0.0174532925);//Перевод из градусов в радианы
    float y_move = -speed * cos(angle * 0.0174532925);//Перевод из градусов в радианы

    //Поворот и движение спрайта
    sprite.setRotation(angle);
    //sprite.move(x_move, y_move);
}
