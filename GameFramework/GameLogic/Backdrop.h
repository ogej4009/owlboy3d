#pragma once
#include "GameUnity.h"


class Backdrop : public ActorComponent
{
protected: 
public:
	GameString Name;
	/*
		::::::::::::::CREATE NEW BACKDROP	
		FLIP X		FLIP Y
		ANGLE :
		ID :
		REPEAT X :	REPEAT Y :
		ANIM FRAMES :
		ANIM DELAY :
	*/
	CVector Flip;
	float Angle;
	int Id;
	CVector Repeat;
	UINT AnimFrame;
	UINT AnimDelay;
	/*
		:::::::::::::: UPDATE ::::::::::::::
		- OFFSET		X :		Y :
		- SOURCE SIZE	X :		Y :
		- DISPLAY SIZE	X :		Y :
		- POSITION		X :		Y :
	*/
	CVector Offset;
	CVector Source_Size;
	CVector Display_Size;
	CVector Pos;


	/*
		::::::::::::::BATCH::::::::::::::
		SPACING
		X :
		Y :
	*/

	CVector Batch_Spacing;
	/*
		bool HIDE_SPRITE_LAYER; // 알파 값 으로 하이드 
		bool SNAP_TO_GRID; // 간격에 맞춰서 그리드를 배치 
	*/

protected:
	Backdrop() {} 
	virtual ~Backdrop() {}
};






/* 

////////////////////////////////////////////////////////

FLIP X: Y:
ANGLE
ID
REPEAT X: Y:
ANIM FRAME
ANIM DELAY

OFFSET X: Y:
SOURCESIZE W: H:
DISPLAYSIZE W: H:
POSITION X: Y:

BATCH	SPACING X: Y:

VIEW LAYER

HIDE SPRITE LAYER ?
SNAP TO GRID ?
POSITION

////////////////////////////////////////////////////////



/*
::::::::::::::BATCH::::::::::::::
SPACING
X :
Y :
*/

/*
::::::::::::::CREATE NEW BACKDROP

FLIP X		FLIP Y
ANGLE :
ID :
REPEAT X :	REPEAT Y :
ANIM FRAMES :
ANIM DELAY :
*/

/*
:::::::::::::: UPDATE ::::::::::::::
- OFFSET		X :		Y :
- SOURCE SIZE	X :		Y :
- DISPLAY SIZE	X :		Y :
- POSITION		X :		Y :
*/








// 캡쳐 스크린샷 MFC 기능 

// 타일만 
// 레이어를 만들자 
// 애니메이션 
// 몬스터 

// Properties 속성 : 색, 모양, 왜곡, UV 설정등 특이한것들

/*
{
	이거지 프로펄티

}



backdrops ? >> 레이어


// 이건 툴 안에서의 뷰 설정 
// 모양에 맞추기 
// 숨김 안보임
snap to grid
hide sprite layer


batch 일괄처리
묶어서 처리하는 것에 동의 하는가 ?
spacing x y 간격



============== = anime ============== =
offset
source size
display size
position



Flip x, y, check
angle
id
repeat x, y 체크하는 것


anime frame					애니메이션 바꾼다.
anime delay



enum 에서 낮과 밤 설정

	sprites
	layers						레이어 만드는 것
	collision					카메라 충돌체


	Backagroud
	디폴트
	ForeGround

	layer order
	sorting


	door 설정
	출돌체 설정


	스프라이트 폭발 설정
	혹은 색변형에 대해  //////////////////////////////// 


	이벤트 트리거






*/