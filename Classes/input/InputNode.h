#ifndef _INPUT_NODE_H
#define _INPUT_NODE_H

#include "cocos2d.h"

USING_NS_CC;

class InputNode : public Node
{
public:
	virtual void* getData() = 0;
};


#endif