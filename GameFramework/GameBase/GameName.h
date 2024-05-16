#pragma once
#include "GameString.h"

class GameName
{
private:
	GameString m_Name;

public:
	//get
	GameString Name()
	{
		return m_Name;
	}

	//set
	void Name(const GameString& _Name)
	{
		m_Name = _Name;
	}

public:
	GameName() {}
	virtual ~GameName() {}
};