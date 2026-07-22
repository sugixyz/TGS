#pragma once
#include"Node.h"

class ActionNode : public Node
{
	ActionNode();
	~ActionNode();
	NodeResult Tick(const bool& context) override;
};

class ConditionNode : public Node
{
	ConditionNode();
	~ConditionNode();
	NodeResult Tick(const bool& context) override;
};

class Sequence : public Node
{
	Sequence();
	~Sequence();
	NodeResult Tick(const bool& context) override;
};

class Selector : public Node
{
	Selector();
	~Selector();
	
};