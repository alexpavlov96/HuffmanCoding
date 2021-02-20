/*********************************************************
 *
 * FrequencyNode
 *
 * Node, storing character and its frequency
 *
 *********************************************************/

#include "FrequencyNode.h"

FrequencyNode::FrequencyNode()
{
}

FrequencyNode::FrequencyNode(char character, double freq)
    : _character(character)
    , _freq(freq)
{
}

FrequencyNode::FrequencyNode(char character, double freq, std::shared_ptr<FrequencyNode> left, std::shared_ptr<FrequencyNode> right)
    : _left(left)
    , _right(right)
    , _character(character)
    , _freq(freq)
{
}
