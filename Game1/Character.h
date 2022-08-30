#pragma once

enum DirState
{
	Dir_L,
	Dir_R,
	Dir_T,
	Dir_B,
	Dir_LT,
	Dir_LB,
	Dir_RT,
	Dir_RB,
	Dir_N
};

class Character
{
protected:
	ObRect* col;
	Vector2 moveDir;

	int dirState;
	int frameY[8];

	Vector2 target;
	vector<Vector2> foot;

public:
	void LookTarget(Vector2 target, ObImage* img);

	void SetTarget(Vector2 target)
	{
		this->target = target;
	}
	Vector2 GetPos()
	{
		return col->GetWorldPos();
	}
	void SetPos(Vector2 pos)
	{
		col->SetWorldPos(pos);
	}


	vector<Vector2>& GetFoot()
	{
		foot.resize(4);

		foot[0] = col->GetWorldPos() + Vector2(0.0f, -30.0f) + Vector2(-10.0f, -10.0f);
		foot[1] = col->GetWorldPos() + Vector2(0.0f, -30.0f) + Vector2(10.0f, -10.0f);
		foot[2] = col->GetWorldPos() + Vector2(0.0f, -30.0f) + Vector2(-10.0f, 10.0f);
		foot[3] = col->GetWorldPos() + Vector2(0.0f, -30.0f) + Vector2(10.0f, 10.0f);

		return foot;
	}
};

