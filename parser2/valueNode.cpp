#include <stdlib.h>

#include "valueNode.h"

// Constructors/Destructor
ValueNode::ValueNode() {
	value = 0;
}
ValueNode::ValueNode(int newValue) : ValueNode() {
	SetValue(newValue);
}
ValueNode::~ValueNode() {
}

// Sets the value of this node.
void ValueNode::SetValue(int newValue) {
	value = newValue;
}

// Returns the value of this node.
int ValueNode::GetValue() {
	// If there is no node, return a default value.
	if (this == NULL)
		return 0;
	return value;
}
