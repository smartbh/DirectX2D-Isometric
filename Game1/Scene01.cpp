#include "stdafx.h"

Scene01::Scene01()
{
    LIGHT->light.radius = 2000.0f;
    pl = new Player();
    mon = new Monster();
    map = new ObTileMap();
    map->file = "map1.txt";
    map->Load();
    map->CreateTileCost();
}

Scene01::~Scene01()
{
    SafeDelete(pl);
    SafeDelete(mon);
    SafeDelete(map);
}

void Scene01::Init()
{
}

void Scene01::Release()
{
}

void Scene01::Update()
{
    ImGui::SliderFloat2("Scale", (float*)&map->scale, 0.0f, 100.0f);

    //��Ŭ��������
    if (INPUT->KeyDown(VK_RBUTTON))
    {
        //   �����, ������
        Int2 sour, dest;
        //ã�Ҵ°�?
        bool isFind;

        isFind = map->WorldPosToTileIdx(pl->GetPos(), sour);
        isFind &= map->WorldPosToTileIdx(INPUT->GetMouseWorldPos(), dest);

        //�Ѵ� Ÿ�ϸ� ����������
        if (isFind)
        {
            //���� �����Ѵٸ�
            if (map->PathFinding(sour, dest, PlWay))
            {
                //�� �����ŭ �ݺ�
                for (int i = 0; i < PlWay.size(); i++)
                {
                    cout << "Way" << i << ":" << PlWay[i]->idx.x <<
                        "," << PlWay[i]->idx.y << endl;
                }
                g = 0.0f;
                PlSour = pl->GetPos();
                PlWay.pop_back(); //����� ����
                PlDest = PlWay.back()->Pos;
            }

        }

    }

    //���ߵ� ���� ������ ��
    if (!PlWay.empty())
    {
        //PlSour = pl->GetPos();
        pl->SetPos(Utility::Lerp(PlSour, PlDest, g));
        g += DELTA * 3.0f;

        //�������� ��������
        if (g > 1.0f)
        {
            g = 0.0f;
            PlSour = PlDest;
            PlWay.pop_back(); //�ǵޱ� ����
            if (!PlWay.empty())
                PlDest = PlWay.back()->Pos;
        }
    }

    pl->Update();
    mon->SetTarget(pl->GetPos());
    mon->Update();
    map->Update();
    CAM->position = pl->GetPos();
}

void Scene01::LateUpdate()
{
    Int2 on;

    if (map->WorldPosToTileIdx(pl->GetPos(), on))
    {
        ImGui::Text("TileState %d", map->GetTileState(on));
    }

    vector<Vector2>& Foot = pl->GetFoot();

    for (int i = 0; i < 4; i++)
    {
        Int2 on;
        if (map->WorldPosToTileIdx(Foot[i], on))
        {
            if (map->GetTileState(on) == TILE_WALL)
            {
                pl->StepBack();
            }
        }
    }


}

void Scene01::Render()
{
    //                               L  T   R   B
    DWRITE->RenderText(L"�ȳ�\n�ȳ�", RECT{ 300,100,(long)app.GetWidth(),(long)app.GetHalfHeight() },
        30.0f, L"�޸ո���ü", Color(1, 0, 0, 1), DWRITE_FONT_WEIGHT_BOLD);
    map->Render();
    pl->Render();
    mon->Render();
}

void Scene01::ResizeScreen()
{
}
