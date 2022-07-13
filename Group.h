#ifndef GROUP_H
#define GROUP_H

#include "Node.h"
#include <vector>

class Group : public Node
{
public:
	std::vector<Node*> childNodes;

	Group();
	~Group();

	virtual void draw(Matrix4);
	virtual void drawBoundary(Matrix4);
	virtual void update(void);

	void addChild(Node*);
	void removeChild(Node*);
};

#endif
