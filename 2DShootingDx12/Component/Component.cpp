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
	if (owner == nullptr)
	{
		return false;
	}
	owner_ = owner;
	return true;
}
