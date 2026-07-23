#include "BehaviorTree.h"

Sequence::Sequence()
{}

Sequence::~Sequence()
{}

NodeResult Sequence::Tick()
{
    for (auto child : children)
    {
        NodeResult result = child->Tick();

        if (result == NodeResult::FAILURE)return result;
        if (result == NodeResult::RUNNING)return result;
    }
    return NodeResult::SUCCESS;
}

void Sequence::AddChildren(Node* child)
{
    children.push_back(child);
}

Selector::Selector()
{}

Selector::~Selector()
{}

NodeResult Selector::Tick()
{
    for (auto child : children)
    {
        NodeResult result = child->Tick();

        if (result == NodeResult::SUCCESS)result;
        if (result == NodeResult::RUNNING)result;
    }
    return NodeResult::FAILURE;
}

void Selector::AddChildren(Node* child)
{
    children.push_back(child);
}
