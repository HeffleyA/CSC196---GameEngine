#include "Pickup.h"
#include "Player.h"

void Pickup::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Player")
	{
		Player* player = dynamic_cast<Player*>(actor);
		if (player)
		{
			player->SetFireModifier(0.2f);
			m_destroyed = true;
		}
	}
}
