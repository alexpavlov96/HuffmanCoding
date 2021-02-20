/*********************************************************
 *
 * EncoderHelper
 *
 * Class, helping with internal encoding proccess
 *
 *********************************************************/

#include "EncoderHelper.h"

#include <queue>

using namespace std;

/*********************************************************
 *  filling codes of symbols by given map of frequencies of symbols
 */
codesMap_t EncoderHelper::fillCodes(const frequencyMap_t& frequencyMap)
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

/*********************************************************
 *  - iterating the tree and accumulating current code (0 - left, 1 - right)
 *  - assigning code value to the character stored in the leaf node
 */
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

/*********************************************************
 *  - building the heap sorted by frequencies
 */
EncoderHelper::node_ptr EncoderHelper::buildNodesHeap(const frequencyMap_t& frequencyMap)
{
    nodesHeap_t nodesHeap;
    for (const auto& f : frequencyMap)
        nodesHeap.push(make_shared<FrequencyNode>(f.first, f.second));

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
