#include "Group.h"

Group::Group()
{
	//
}


Group::~Group()
{
	for (std::vector<Node*>::iterator it = childNodes.begin(); it != childNodes.end(); ++it) {
		delete *it;
	}
}

void Group::draw(Matrix4 C)
{
	for (std::vector<Node*>::iterator it = childNodes.begin(); it != childNodes.end(); ++it)
		(*it)->draw(C);
}

void Group::drawBoundary(Matrix4 C)
{
	for (std::vector<Node*>::iterator it = childNodes.begin(); it != childNodes.end(); ++it)
		(*it)->drawBoundary(C);
}

void Group::update()
{
	//
}
void Group::addChild(Node* child)
{
	childNodes.push_back(child);
}

void Group::removeChild(Node* child)
{
	for (std::vector<Node*>::iterator it = childNodes.begin(); it != childNodes.end(); ++it) {
		if (*it == child) {
			childNodes.erase(it);
			//break;
		}
	}
}