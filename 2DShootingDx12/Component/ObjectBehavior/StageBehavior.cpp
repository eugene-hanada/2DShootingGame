#include "StageBehavior.h"
#include "../../Application.h"

StageBehavior::StageBehavior()
{
}

void StageBehavior::Update(ObjectManager& objectManager)
{
	timer_ += Time.GetDeltaTime<float>();
	if (timer_ >= 5.0f)
	{

	}
}

void StageBehavior::Begin(void)
{
	timer_ = 0.0f;
}
