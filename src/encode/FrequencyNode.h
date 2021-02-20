/*********************************************************
 *
 * FrequencyNode
 *
 * Node, storing character and its frequency
 *
 *********************************************************/

#pragma once

#include <memory>

class FrequencyNode
{
public:
    using node_ptr = std::shared_ptr<FrequencyNode>;

    FrequencyNode();
    FrequencyNode(char character, double freq);
    FrequencyNode(char character, double freq, node_ptr left, node_ptr right);

    node_ptr left() const { return _left; }
    node_ptr right() const { return _right; }
    char     character() const { return _character; }
    double   freq() const { return _freq; }

    class NodesComparator
    {
    public:
        bool operator()(node_ptr left, node_ptr right)
        {
            return left->freq() > right->freq();
        }
    };

private:
    node_ptr _left;
    node_ptr _right;

    char   _character;
    double _freq;
};
