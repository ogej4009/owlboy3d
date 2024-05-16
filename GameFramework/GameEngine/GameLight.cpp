#include "GameLight.h"

#include <GameDebug.h>
#include <GameWin.h>
#include "GameActor.h"
#include "GameTransform.h"
#include "GameScene.h"
#include "GameRenderTarget.h"

void GameLight::InitSetting(int _Order)
{
	Order(_Order);
	GetActor()->GetScene()->PushLight(this);

	LightPower.X = 1.0f;
	LightPower.Y = 1.0f;
	LightPower.Z = 1.0f;
	LightPower.W = 1.0f;

	SpecPow = CVector({ 10000.0f, 0.0f, 0.0f, 0.0f });
	AmbColor = CVector({ 0.033f, 0.033f, 0.033f, 1.0f });

	ShadowDepthTarget = new GameRenderTarget();
	ShadowDepthTarget->CreateTarget({ 4096, 4096 }, CVector::NONE, true, DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT);

	ShadowDepthTarget->CreateDepth();

	m_Near = 0.1f;
	m_Far = 10.0f;

	ViewSize = ShadowDepthTarget->Texture(0)->Size();

	Qulity = 400.0f;


}

void GameLight::LightUpdate()
{
	ShadowDepthTarget->Clear(true);
	for (LightData* Data : DataList)
	{
		Data->LightDir = GetTrans()->WForward();
		Data->LightDirInv = GetTrans()->WBack();
		Data->LightDir.W = Data->LightDirInv.W = 0.0f;
		Data->LightPower = LightPower;
		Data->SpecPow = SpecPow;
		Data->AmbColor = AmbColor;
		Data->DifColor = DifColor;
		Data->OnOff.X = IsUpdateObj() == true ? 1.0f : 0.0f;
		Data->m_View.VIEWLH(GetTrans()->GetWPos(), GetTrans()->WForward(), GetTrans()->WUp());
		Data->m_Proj.ORTHLH(ViewSize / Qulity, m_Near, m_Far);
		Data->m_ViewProj = Data->m_View * Data->m_Proj;

	}
}

void GameLight::madeRect()
{
	//CPtr<GameRenderer> NewRender = GetActor()->CreateCom<GameRenderer>(L"Cube", L"DBSHADER");
}

