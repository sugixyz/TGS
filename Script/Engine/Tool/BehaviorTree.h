#pragma once
#include"Node.h"
#include<vector>

class ActionNode : public Node
{
public:
	ActionNode();
	~ActionNode();
	NodeResult Tick() override;
};

class ConditionNode : public Node
{
public:
	ConditionNode();
	~ConditionNode();
	NodeResult Tick() override;
};

class Sequence : public Node
{
public:
	Sequence();
	~Sequence();
	NodeResult Tick() override;
	void AddChildren(Node* child);
private:
	std::vector<Node*> children;
};

class Selector : public Node
{
public:
	Selector();
	~Selector();
	NodeResult Tick() override;
	void AddChildren(Node* child);
private:
	std::vector<Node*> children;
};