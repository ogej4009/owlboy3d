#include "GameScene.h"
#include "GameActor.h"
#include "GameDevice.h"
#include "GameTransform.h"
#include "GameCamera.h"
#include "GameRenderer.h"
#include "GameCol.h"
#include "GameDebugPlus.h"
#include <GameInput.h>
#include <GameMovie.h>
#include "GameLight.h"
#include <GameTime.h>
#include "GameRenderTarget.h"


CPtr<GameScene> GameScene::m_CurScene = nullptr;
CPtr<GameScene> GameScene::m_NextScene = nullptr;


CVector GameScene::HeroPos = CVector::NONE;
CPtr<GameActor> GameScene::HeroActor = nullptr;


GameScene::GameScene() {}
GameScene::~GameScene() {}


bool GameScene::ZSort(CPtr<GameRenderer>& _Left, CPtr<GameRenderer>& _Right)
{
	CVector LeftZ = _Left->GetWPos();
	CVector RightZ = _Right->GetWPos();

	// 랜더러가 트랜스폼을 상속받은 이유는
	// 직접 비교를 할 수 있기 때문이다.  
	return _Left->GetWPos().Z > _Right->GetWPos().Z;
}

CPtr<GameCamera> GameScene::MainCam()
{
	return m_MainCam;
}

void GameScene::ChangeScene(const GameString& _Name)
{
	m_NextScene = Find(_Name);

	if (nullptr == m_NextScene)
	{
		MSG_ASSERT_CODE(L"존재하지 않는 씬을 체인지 하려고 했습니다.");
	}
}

CPtr<GameActor> GameScene::CreateActor(const GameString& _Name)
{
	CPtr<GameActor> Actor = GameObjListTFuncMgrProgress<GameActor>::CreateObj<GameActor>(_Name);
	Actor->m_Scene = this;
	Actor->CreateCom<GameTransform>();
	return Actor;
}

void GameScene::Progress()
{
	if (nullptr != m_NextScene)
	{
		if (nullptr == m_CurScene)
		{
			m_CurScene = m_NextScene;
			m_CurScene->SceneChangeStart();
			//m_NextScene = nullptr; 
			//GameTime::TimeReset();
		}
		else
		{
			m_CurScene->SceneChangeEnd();
			m_CurScene = m_NextScene;
			m_CurScene->SceneChangeStart();
			//m_NextScene = nullptr; 
			//GameTime::TimeReset();
		}
	}

	GameInput::Update();
	GameTime::Update();

	m_CurScene->UpdatePrev();
	m_CurScene->Update();
	m_CurScene->UpdateNext();
	m_CurScene->RenderPrev();
	m_CurScene->Render();
	m_CurScene->RenderNext();
	m_CurScene->CollisionPrev();
	m_CurScene->Collision();
	m_CurScene->CollisionNext();
	m_CurScene->Release();
}

///////////////////////////////////////////////////////////////////////////////// PUSH


void GameScene::PushCam(CPtr<GameCamera> _Cam)
{
	if (m_AllCam.end() != m_AllCam.find(_Cam->Order()))
	{
		MSG_ASSERT_CODE(L"카메라의 오더가 겹쳤습니다.");
	}

	for (int Value : _Cam->m_ViewRenders)
	{
		CreateRenderGroupLight(Value);
	}

	if (nullptr == m_MainCam)
	{
		m_MainCam = _Cam;
	}

	m_AllCam[_Cam->Order()] = _Cam;
}


void GameScene::PushRender(CPtr<GameRenderer> _Render)
{
	if (m_AllRender.end() == m_AllRender.find(_Render->Order()))
	{
		m_AllRender.insert(
			std::map<int, std::list<CPtr<GameRenderer>>>::value_type(_Render->Order(),
				std::list<CPtr<GameRenderer>>()));
	}

	m_AllRender[_Render->Order()].push_back(_Render);
}


void GameScene::PushCol(CPtr<GameCol> _Col)
{
	if (m_AllCol.end() == m_AllCol.find(_Col->Order()))
	{
		m_AllCol.insert(std::map<int, std::list<CPtr<GameCol>>>::value_type(_Col->Order(),
			std::list<CPtr<GameCol>>()));
	}
	m_AllCol[_Col->Order()].push_back(_Col);
}



void GameScene::PushLight(CPtr<GameLight> _Light)
{

	for (int Value : _Light->m_ViewRenderers)
	{
		CreateRenderGroupLight(Value);
	}

	for (int Value : _Light->m_ViewRenderers)
	{
		m_AllLight[Value].push_back(_Light);
		LightData& LightData = m_AllLightData[Value].ArrLightData[m_AllLightData[Value].LightCount[0]];
		_Light->DataList.push_back(&LightData);
		++m_AllLightData[Value].LightCount[0];
	}
}


void GameScene::CreateRenderGroupLight(int _Index)
{
	if (m_AllRender.end() != m_AllRender.find(_Index))
	{
		return;
	}

	m_AllRender.insert(
		std::map<int, std::list<CPtr<GameRenderer>>>::value_type(_Index,
			std::list<CPtr<GameRenderer>>()));

	m_AllLight.insert(
		std::map<int, std::vector<CPtr<GameLight>>>::value_type(_Index,
			std::vector<CPtr<GameLight>>()));

	m_AllLightData.insert(std::map<int, ObjectLightData>::value_type(_Index, ObjectLightData()));
}


ObjectLightData* GameScene::GetLightData(int _Index)
{
	return &(m_AllLightData[_Index]);
}


void GameScene::LightCheck()
{
	for (auto& LightDataGroup : m_AllLightData)
	{
		LightDataGroup.second.LightCount[0] = 0;
	}

	for (auto& _LightGroup : m_AllLight)
	{
		for (auto& _Light : _LightGroup.second)
		{
			for (int Value : _Light->m_ViewRenderers)
			{
				LightData& LightData = m_AllLightData[Value].ArrLightData[m_AllLightData[Value].LightCount[0]];
				_Light->DataList.push_back(&LightData);
				++m_AllLightData[Value].LightCount[0];
			}
		}
	}
}




////////////////////////////////////////////////////////////////////////// Progress

void GameScene::UpdatePrev()
{
	GameObjListTFuncMgrProgress<SceneComponent>::UpdatePrev();
	GameObjListTFuncMgrProgress<GameActor>::UpdatePrev();
}

void GameScene::Update()
{
	GameObjListTFuncMgrProgress<SceneComponent>::Update();
	GameObjListTFuncMgrProgress<GameActor>::Update();
}

void GameScene::UpdateNext()
{
	GameObjListTFuncMgrProgress<SceneComponent>::UpdateNext();
	GameObjListTFuncMgrProgress<GameActor>::UpdateNext();
}

void GameScene::RenderPrev()
{
	GameObjListTFuncMgrProgress<SceneComponent>::RenderPrev();
	GameObjListTFuncMgrProgress<GameActor>::RenderPrev();

	// 부모가없다==가장최상의트랜스폼을 모아놓은 자료구조
	for (auto& _TransForm : m_AllTrans)
	{
		_TransForm->TransformUpdate();
	}

}


void GameScene::Render()
{
	//////// 백버퍼 세팅
	GameDevice::MainObj()->RenderStart();

	////// 라이트 세팅
	for (auto& _LightGroup : m_AllLight)
	{
		for (auto& _Light : _LightGroup.second)
		{
			_Light->LightUpdate();
		}
	}

	for (auto& _Cam : m_AllCam)
	{
		///////// 포워드방식일 경우 
		_Cam.second->ForwardCamTarget()->Clear(false);
		_Cam.second->ForwardCamTarget()->Setting();

		for (int RenderOrder : _Cam.second->m_ViewRenders)
		{
			ObjectLightData* LightGroup = GetLightData(RenderOrder);

			for (size_t i = 0; i < LightGroup->LightCount[0]; i++)
			{

				LightGroup->ArrLightData[i].LightDirInv = _Cam.second->m_View.MulZero(LightGroup->ArrLightData[i].LightDirInv);
				LightGroup->ArrLightData[i].LightDirInv.Normalize3d();
				LightGroup->ArrLightData[i].CamPos = _Cam.second->m_View.MulOne(_Cam.second->GetTrans()->GetWPos());
			}

			std::map<int, std::list<CPtr<GameRenderer>>>::iterator RenderGroup = m_AllRender.find(RenderOrder);

			if (m_AllRender.end() == RenderGroup)
			{
				continue;
			}

			for (auto& _Render : RenderGroup->second)
			{
				if (false == _Render->IsUpdateObj())
				{
					continue;
				}

				_Render->ForwardRender(_Cam.second);
				//_Render->Render(_Cam.second);
			}
		}
		
		////// 디퍼드방식일 경우 
		_Cam.second->GbufferTarget()->Clear(false);
		_Cam.second->GbufferTarget()->Setting();
		_Cam.second->DeferredLightTarget()->Clear(false);
	
		for (int RenderOrder : _Cam.second->m_ViewRenders)
		{
			ObjectLightData* LightGroup = GetLightData(RenderOrder);
	
			for (size_t i = 0; i < LightGroup->LightCount[0]; i++)
			{
				// LightGroup->ArrLightData[i].CamPos = _Cam.second->m_VIEW.MulOne(_Cam.second->TRANS()->WPOS());
			}
	
			std::map<int, std::list<CPtr<GameRenderer>>>::iterator RenderGroup = m_AllRender.find(RenderOrder);
	
			if (m_AllRender.end() == RenderGroup)
			{
				continue;
			}
	
			for (auto& _Render : RenderGroup->second)
			{
				if (false == _Render->IsUpdateObj())
				{
					continue;
				}
	
				_Render->DeferredRender(_Cam.second);
			}
	
			for (size_t i = 0; i < LightGroup->LightCount[0]; i++)
			{
				m_AllLight[RenderOrder][i]->ShadowTarget()->Setting();
	
				for (auto& _Render : RenderGroup->second)
				{
					_Render->ShadowRender(LightGroup->ArrLightData[i]);
				}
				LightGroup->ArrLightData[i].m_CamViewInverse = _Cam.second->m_View.InverseReturn();
	
	
				_Cam.second->CalDeferredLight(LightGroup->ArrLightData[i], m_AllLight[RenderOrder][i]->ShadowTarget()->Texture(0));
			}
		}
	}
	
	/////// 후처리 
	for (auto& _Cam : m_AllCam)
	{
		_Cam.second->DeferredMergePrevEffect();
	}

	for (auto& _Cam : m_AllCam)
	{
		_Cam.second->DeferredMerge();
	}

	for (auto& _Cam : m_AllCam)
	{
		_Cam.second->DeferredMergeNextEffect();
	}

	GameDevice::MainObj()->BackBufferRenderTarget()->Clear(true);

	for (auto& _Cam : m_AllCam)
	{
		_Cam.second->CamMergePrevEffect();
		_Cam.second->CamTargetMerge();
		_Cam.second->CamMergeNextEffect();

		GameDevice::MainObj()->BackBufferRenderTarget()->Merge(_Cam.second->CamTarget());
	}

	{
		GameDebugPlus::DebugRender();
	}

	GameDevice::MainObj()->DataRenderTarget()->Clear(false);
	GameDevice::MainObj()->RenderEnd();

}

void GameScene::RenderNext()
{
	GameObjListTFuncMgrProgress<SceneComponent>::RenderNext();
	GameObjListTFuncMgrProgress<GameActor>::RenderNext();
}

void GameScene::CollisionPrev()
{
	GameObjListTFuncMgrProgress<SceneComponent>::CollisionPrev();
	GameObjListTFuncMgrProgress<GameActor>::CollisionPrev();
}

void GameScene::Collision()
{
	for (auto& LeftIndex : m_ColLink)
	{
		// std::map<	int,			std::set<int>		>				m_ColLink;
		//			플레이어그룹	    몬스터 그룹, 골드그룹

		std::map<int, std::list<CPtr<GameCol>>>::iterator LeftGroup = m_AllCol.find(LeftIndex.first);

		if (LeftGroup == m_AllCol.end())
		{
			continue;
		}

		if (true == LeftGroup->second.empty())
		{
			continue;
		}

		for (int RightIndex : LeftIndex.second)
		{
			std::map<int, std::list<CPtr<GameCol>>>::iterator RightGroup = m_AllCol.find(RightIndex);

			if (RightGroup == m_AllCol.end())
			{
				continue;
			}

			if (true == RightGroup->second.empty())
			{
				continue;
			}

			if (LeftIndex.first == RightIndex)
			{
				std::list<CPtr<GameCol>>::iterator LeftStart = LeftGroup->second.begin();

				if (false == (*LeftStart)->IsUpdateObj())
				{
					continue;
				}

				std::list<CPtr<GameCol>>::iterator LeftEnd = RightGroup->second.end();
				--LeftEnd;

				// 0 1 2 
				for (; LeftStart != LeftEnd; ++LeftStart)
				{
					std::list<CPtr<GameCol>>::iterator RightStart = LeftStart;
					std::list<CPtr<GameCol>>::iterator RightEnd = RightGroup->second.end();
					++RightStart;

					for (; RightStart != RightEnd; ++RightStart)
					{
						if (false == (*RightStart)->IsUpdateObj())
						{
							continue;
						}

						(*LeftStart)->ColCheck(*RightStart);
					}
				}

			}
			else
			{
				// 내가속한그룹과의 충돌은 배제
				for (auto& LeftCol : LeftGroup->second)
				{

					if (false == LeftCol->IsUpdateObj())
					{
						continue;
					}

					for (auto& RightCol : RightGroup->second)
					{

						if (false == RightCol->IsUpdateObj())
						{
							continue;
						}

						LeftCol->ColCheck(RightCol);
					}
				}
			}
		}
	}

}



void GameScene::CollisionNext()
{
	GameObjListTFuncMgrProgress<SceneComponent>::CollisionNext();
	GameObjListTFuncMgrProgress<GameActor>::CollisionNext();
}

void GameScene::SceneChangeEnd()
{
	GameObjListTFuncMgrProgress<SceneComponent>::SceneChangeEnd();
	GameObjListTFuncMgrProgress<GameActor>::SceneChangeEnd();
}

void GameScene::SceneChangeStart()
{
	GameObjListTFuncMgrProgress<SceneComponent>::SceneChangeStart();
	GameObjListTFuncMgrProgress<GameActor>::SceneChangeStart();
}




///////////////////////////////////////////////////// LISTDATA
typedef std::list<GameObjListTFuncMgrProgress<SceneComponent>::CListData>::iterator SceneComIter;
typedef std::list<GameObjListTFuncMgrProgress<GameActor>::CListData>::iterator ActorIter;




void GameScene::Release()
{
	//////////////////////////////// SceneCom-Release
	{
		SceneComIter Start = GameObjListTFuncMgrProgress<SceneComponent>::m_ObjList.begin();
		SceneComIter End = GameObjListTFuncMgrProgress<SceneComponent>::m_ObjList.end();

		for (; Start != End; )
		{
			if (true == Start->Obj->IsDeathObj())
			{
				Start = GameObjListTFuncMgrProgress<SceneComponent>::m_ObjList.erase(Start);
			}
			else
			{
				++Start;
			}
		}
	}

	////////////////////// ActorCom-Release
	{
		// Trans
		{
			std::list<CPtr<GameTransform>>::iterator Start = m_AllTrans.begin();
			std::list<CPtr<GameTransform>>::iterator End = m_AllTrans.end();

			for (; Start != End; )
			{
				if (true == (*Start)->IsDeathObj())
				{
					Start = m_AllTrans.erase(Start);
				}
				else
				{
					++Start;
				}
			}
		}

		// Col
		{
			std::map<int, std::list<CPtr<GameCol>>>::iterator Start = m_AllCol.begin();
			std::map<int, std::list<CPtr<GameCol>>>::iterator End = m_AllCol.end();

			for (; Start != End; ++Start)
			{
				std::list<CPtr<GameCol>>::iterator StartCol = Start->second.begin();
				std::list<CPtr<GameCol>>::iterator EndCol = Start->second.end();

				for (; StartCol != EndCol; )
				{
					if (true == (*StartCol)->IsDeathObj())
					{
						StartCol = Start->second.erase(StartCol);
					}
					else
					{
						++StartCol;
					}
				}
			}
		}

		// Cam
		{
			std::map<int, CPtr<GameCamera>>::iterator Start = m_AllCam.begin();
			std::map<int, CPtr<GameCamera>>::iterator End = m_AllCam.end();

			for (; Start != End; )
			{
				if (true == Start->second->IsDeathObj())
				{
					if (m_MainCam == Start->second)
					{
						m_MainCam = nullptr;
					}
					Start = m_AllCam.erase(Start);
				}
				else
				{
					++Start;
				}
			}
		}

		// Renderer
		{
			std::map<int, std::list<CPtr<GameRenderer>>>::iterator Start = m_AllRender.begin();
			std::map<int, std::list<CPtr<GameRenderer>>>::iterator End = m_AllRender.end();

			for (; Start != End; ++Start)
			{
				std::list<CPtr<GameRenderer>>::iterator StartRender = Start->second.begin();
				std::list<CPtr<GameRenderer>>::iterator EndRender = Start->second.end();

				for (; StartRender != EndRender; )
				{
					if (true == (*StartRender)->IsDeathObj())
					{
						StartRender = Start->second.erase(StartRender);
					}
					else
					{
						++StartRender;
					}
				}
			}
		}

		///////  Light
		{
			bool LightReCheck = false;

			std::map<int, std::vector<CPtr<GameLight>>>::iterator Start = m_AllLight.begin();
			std::map<int, std::vector<CPtr<GameLight>>>::iterator End = m_AllLight.end();

			for (; Start != End; ++Start)
			{
				std::vector<CPtr<GameLight>>::iterator StartRender = Start->second.begin();
				std::vector<CPtr<GameLight>>::iterator EndRender = Start->second.end();

				for (; StartRender != EndRender; )
				{
					if (true == (*StartRender)->IsDeathObj())
					{
						LightReCheck = true;
						// 라이트는 라이트 구조가 있기 때문에 이게 삭제된 순간.
						// 데이터에 대해서 재정리를 해줘야 한다.
						StartRender = Start->second.erase(StartRender);
					}
					else
					{
						++StartRender;
					}

				}

			}

			if (true == LightReCheck)
			{
				LightCheck();
			}
			// LightReCheck = true;
		}


		// Actor
		{
			ActorIter Start = GameObjListTFuncMgrProgress<GameActor>::m_ObjList.begin();
			ActorIter End = GameObjListTFuncMgrProgress<GameActor>::m_ObjList.end();

			for (; Start != End; )
			{
				if (true == Start->Obj->IsDeathObj())
				{
					Start->Obj->Release();
					Start = GameObjListTFuncMgrProgress<GameActor>::m_ObjList.erase(Start);
				}
				else
				{
					++Start;
				}
			}
		}
	}
}

//void GameScene::ActorClear()
//{
//	// 상속에서 최상위에있는개념이 가장 마지막에 지워지는 것이 중요.
//	m_AllCol.clear();
//	m_AllCam.clear();
//	m_AllRender.clear();
//	m_AllTrans.clear();
//	GameObjListTFuncMgrProgress<GameActor>::m_ObjList.clear();
//	m_MainCam = nullptr;
//}

