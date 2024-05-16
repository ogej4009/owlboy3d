
#include "LevelDesignView.h"

void LevelDesignView::FileCreate()
{

	{
		GameDirectory Dic;
		Dic.MoveParent(L"GameFramework");
		Dic.Move(L"resource");
		Dic.Move(L"tex");
		Dic.Move(L"Global");
		auto FileList = Dic.DirAllFile();
		for (auto& _File : FileList)
		{
			GameTexture::Load(_File);
		}
		//GameSprite::Create(L"ColLevel1.png", 10, 5);
		GameSprite::Create(L"TestGrid.png", 1, 1);
		//GameSprite::Create(L"ERROR.png", 1, 1);
		//for (auto& _File : FileList)
		//{
		//	GameSprite::Create(_File.FileName(), 1, 1);
		//}
	}

}

void LevelDesignView::FileDelete()
{
	{
		GameDirectory Dic;
		Dic.MoveParent(L"GameFramework");
		Dic.Move(L"resource");
		Dic.Move(L"tex");
		Dic.Move(L"Global");
		auto FileList = Dic.DirAllFile();
		for (auto& _File : FileList)
		{
			GameTexture::Delete(_File.FileName());
		}
		//for (auto& _File : FileList)
		//{
		//	GameSprite::Delete(_File.FileName(), 1, 1);
		//}
	}
}

// SetRenderTarget