#include "Bullet.h"

Bullet::Bullet(float x, float y, float angle)
{
    this->angle = angle;
    bullet.setRadius(1);
    bullet.setPosition(x, y);
}

void Bullet::Play(std::list<Bullet>& Bul_list, std::list<Bullet>::iterator& itErase, int bull_behavior)
{
    //Определение поведения пуль (отталкивание или удаление)
    if (bull_behavior == 1)
    {
        //Условия удаления пуль при касании края экрана.
        if ((bullet.getPosition().x >= x_window_size) || (bullet.getPosition().x <= 0) || (bullet.getPosition().y >= y_window_size) || (bullet.getPosition().y <= 0))
        {
            /* Создается новый итерратор и в него записывается тот, который подходит под условие.
             Старый итерратор указывает на следующий элемент. Далее из вектора удаляется элемент, на который
             указывает новый итератор.
             Итератор, переданный изначально уже увеличен на 1, поэтому в цикле main инкремент не используется
             (Так бы он увеличивался 2 раза, изза этого вылетали ошибки)

             если м не заходим в этот if, итератор увеличивается в else.*/
            auto deleted = itErase;
            ++itErase;
            Bul_list.erase(deleted);
        }
        else
            ++itErase;
    }
    else
    {
        //Условия отталкивания от края окна
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

    float x_move = 5 * sin(angle * 0.0174532925);//Перевод из градусов в радиан
    float y_move = -5 * cos(angle * 0.0174532925);//Перевод из градусов в радиан

    //Поворот и движение спрайта
    bullet.move(x_move, y_move);
}