#pragma once

class Scene01 : public Scene
{
private:
	Player* pl;
	Monster* mon;

	ObTileMap* map;

	//��ã��� ����
	vector<Tile*> PlWay;

	//�̵���ų ��ġ
	Vector2 PlDest;
	Vector2 PlSour;

	//����
	float   g;

public:
	Scene01();
	~Scene01();

	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

