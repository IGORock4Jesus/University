#include "rect.h"

bool containsRect(rect * r, rect * d)
{
	return !(d->position.x > r->position.x + r->size.x ||
		d->position.x + d->size.x < r->position.x ||
		d->position.y > r->position.y + r->size.y ||
		d->position.y + d->size.y < r->position.y);
}
