#pragma once

enum class NodeResult
{
	SUCCESS,
	FAILURE,
	RUNNING
};

class Node
{
	virtual ~Node() = default;
	virtual NodeResult Tick(const bool& context) = 0;
};