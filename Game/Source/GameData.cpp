#include "GameData.h"

namespace GameData
{
	const std::vector<Vector2>shipPoints
	{
		{ 0, 0 },

		{ -1.0f, 0.5f },
		{ -1, 1 },
		{ 0, 1 },
		{ 0.0f, 0.5f },
		{ -1.0f, 0.5f },

		{ -2, 1 },

		{ -3, 1 },
		{ -3.0f, 0.5f },
		{ -2.0f, 0.5f },
		{ -2, 1 },

		{ -2.0f, -0.5f },
		{ -3.0f, -0.5f },
		{ -3, -1 },
		{ -2, -1 },
		{ -2.0f, -0.5f },

		{ -2, -1 },

		{ -1.0f, -0.5f },
		{ -1, -1 },
		{ 0, -1 },
		{ 0.0f, -0.5f },
		{ -1.0f, -0.5f },

		{ 0, 0 }
	};

	const std::vector<Vector2>asteroidPoints
	{
		{ 0, 0 },

		{ 1 , 0 },
		{ 2, -1 },
		{ 1 , -2 },
		{ 2 , -3 },
		{ 0, -3 },
		{ -1, -2 },
		{ -1 , -1 },
		{ 0, -1 },

		{ 0, 0 }
	};

	const std::vector<Vector2>pickupPoints
	{
		{ 0, 0 },

		{ 1, -1 },
		{ 0, -2 },
		{ -1, -1},

		{0 , 0 }
	};

	const std::vector<Vector2>enemyPoints
	{
		{ 0, 0 },

		{ 1, 0 },
		{ 2, -1 },
		{ 1, -1 },
		{ 1, -2 },
		{ 0, -2 },
		{ 0, -1 },
		{ -1 , -1 },

		{ 0, 0 }
	};

	const std::vector<Vector2>plusPoints
	{
		{ 0, 0 },

		{ 1, 0 },
		{ 1, -1 },
		{ 2, -1 },
		{ 2, -2 },
		{ 1, -2 },
		{ 1, -3 },
		{ 0, -3 },
		{ 0, -2 },
		{ -1, -2 },
		{ -1, -1 },
		{ 0, -1 },

		{ 0, 0 }
	};

	const std::vector<Vector2>doublePoints
	{
		{ 0, 0 },

		{ 0, 2 },
		{ 1, 2 },
		{ -0.5f, 4.0f },
		{ -2, 2 },
		{ -1, 2 },
		{ -1 , 0 },

		{ 0, 0 }
	};
}