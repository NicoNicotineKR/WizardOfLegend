//	������ �̰� ��ӹ޾� �� ��

#pragma once



class enemy
{
private:

public:
	enemy();
	~enemy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

