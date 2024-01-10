#ifndef VALUE_NODE_H
#define VALUE_NODE_H

class ValueNode {
public:
	// Constructors/Destructor
	ValueNode();
	ValueNode(int newValue);
	~ValueNode();

	// Sets the value of this node.
	void SetValue(int newValue);

	// Returns the value of this node.
	int GetValue();

private:
	int value;	// Value
};

#endif
