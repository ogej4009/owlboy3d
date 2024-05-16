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
		bool HIDE_SPRITE_LAYER; // ���� �� ���� ���̵� 
		bool SNAP_TO_GRID; // ���ݿ� ���缭 �׸��带 ��ġ 
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








// ĸ�� ��ũ���� MFC ��� 

// Ÿ�ϸ� 
// ���̾ ������ 
// �ִϸ��̼� 
// ���� 

// Properties �Ӽ� : ��, ���, �ְ�, UV ������ Ư���Ѱ͵�

/*
{
	�̰��� ������Ƽ

}



backdrops ? >> ���̾�


// �̰� �� �ȿ����� �� ���� 
// ��翡 ���߱� 
// ���� �Ⱥ���
snap to grid
hide sprite layer


batch �ϰ�ó��
��� ó���ϴ� �Ϳ� ���� �ϴ°� ?
spacing x y ����



============== = anime ============== =
offset
source size
display size
position



Flip x, y, check
angle
id
repeat x, y üũ�ϴ� ��


anime frame					�ִϸ��̼� �ٲ۴�.
anime delay



enum ���� ���� �� ����

	sprites
	layers						���̾� ����� ��
	collision					ī�޶� �浹ü


	Backagroud
	����Ʈ
	ForeGround

	layer order
	sorting


	door ����
	�⵹ü ����


	��������Ʈ ���� ����
	Ȥ�� �������� ����  //////////////////////////////// 


	�̺�Ʈ Ʈ����






*/