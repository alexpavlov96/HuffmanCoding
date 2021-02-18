#include "EncoderHelper.h"

#include <queue>

using namespace std;

EncoderHelper::codesMap_t EncoderHelper::fillCodes(const frequencyMap_t& frequencyMap)
{
    _codes.clear();

    if (frequencyMap.size() == 1)
    {
        _codes[frequencyMap.begin()->first] = "0";
        return _codes;
    }

    fillCodesRecursively(buildNodesHeap(frequencyMap));
    return _codes;
}

void EncoderHelper::fillCodesRecursively(node_ptr root, const std::string& currentCode)
{
    if (root->left())
        fillCodesRecursively(root->left(), currentCode + "0");
    if (root->right())
        fillCodesRecursively(root->right(), currentCode + "1");

    if (!root->left() && !root->right())
    {
        _codes[root->character()] = currentCode;
    }
}

// Построение очереди с приоритетом
EncoderHelper::node_ptr EncoderHelper::buildNodesHeap(const frequencyMap_t& frequencyMap)
{
    vector<node_ptr> nodes;
    nodes.reserve(frequencyMap.size());

    for (const auto& f : frequencyMap)
        nodes.push_back(make_shared<FrequencyNode>(f.first, f.second));

    using mv_iterator_t = std::move_iterator<decltype(nodes.begin())>;
    nodesHeap_t nodesHeap(mv_iterator_t(nodes.begin()), mv_iterator_t(nodes.end()));

    while (nodesHeap.size() > 1)
    {
        auto left = nodesHeap.top();
        nodesHeap.pop();

        auto right = nodesHeap.top();
        nodesHeap.pop();

        auto sum = std::make_shared<FrequencyNode>('-', left->freq() + right->freq(), left, right);
        nodesHeap.push(move(sum));
    }
    return nodesHeap.top();
}
