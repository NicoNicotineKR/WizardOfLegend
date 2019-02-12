#include "stdafx.h"
#include "skillCooldownUI.h"


skillCooldownUI::skillCooldownUI()
{
}


skillCooldownUI::~skillCooldownUI()
{
}

HRESULT skillCooldownUI::init()
{
	_iconList = new skillIconList;
	_iconList->init();



	return S_OK;
}

void skillCooldownUI::release()
{
}

void skillCooldownUI::update()
{
	
}

void skillCooldownUI::render()
{
}


