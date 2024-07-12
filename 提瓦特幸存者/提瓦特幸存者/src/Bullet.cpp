#include "Bullet.h"

void Bullet::Draw() const
{
	setlinecolor(RGB(255, 150, 50));
	setfillcolor(RGB(200, 75, 10));
	fillcircle(position.x, position.y, RADIUS);
}
