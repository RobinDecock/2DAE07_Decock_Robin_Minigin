#pragma once
#include "InputHandler.h"
class Bub;

class BubState
{
public:
	BubState(Bub* pBub) :m_pBub(pBub)
	{}

	virtual ~BubState(){}
	virtual BubState* Execute(float elapsedSec) { return nullptr; }
	virtual void StartState() {}
	virtual void EndState() {}
protected:
	Bub* m_pBub = nullptr;

};

class RespawnState:public BubState
{
public:
	RespawnState(Bub* pBub) :BubState(pBub) {}
	void StartState() override;
	BubState* Execute(float elapsedSec)override ;
	void EndState() override;
	~RespawnState() override = default;
};

class NormalState:public BubState
{
public:
	NormalState(Bub* pBub) :BubState(pBub) {}
	void StartState() override;
	BubState* Execute(float elapsedSec) override;
	void EndState() override;
	~NormalState() override = default;
private:
	InputHandler m_InputHandler;
};

class HitState: public BubState
{
public:
	HitState(Bub* pBub) :BubState(pBub) {}
	BubState* Execute(float elapsedSec) override;
	void EndState() override;
	~HitState() override = default;
};


class AerialState: public BubState
{
public:
	AerialState(Bub* pBub) :BubState(pBub) {}
	void StartState() override;
	BubState* Execute(float elapsedSec) override;
	~AerialState() override = default;
private:
	InputHandler m_InputHandler;
};

