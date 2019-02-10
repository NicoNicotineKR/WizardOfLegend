//	적들은 이거 상속받아 쓸 것

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

