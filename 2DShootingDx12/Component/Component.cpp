#include <cassert>
#include "Component.h"

Component::Component() noexcept
{
}

Component::~Component()
{
}

bool Component::SetOwner(Object* owner)
{
	owner_ = owner;
	return true;
}
