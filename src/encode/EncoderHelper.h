/*********************************************************
 *
 * EncoderHelper
 *
 * Class, helping with internal encoding proccess
 *
 *********************************************************/

#pragma once

#include <unordered_map>

#include <queue>

#include "../common/common.h"
#include "FrequencyNode.h"

class EncoderHelper
{
public:
    using node_ptr    = std::shared_ptr<FrequencyNode>;
    using nodesHeap_t = std::priority_queue<node_ptr, std::vector<node_ptr>, FrequencyNode::NodesComparator>;

    codesMap_t fillCodes(const frequencyMap_t& frequencyMap);

private:
    codesMap_t _codes;

    node_ptr buildNodesHeap(const frequencyMap_t& frequencyMap);
    void     fillCodesRecursively(std::shared_ptr<FrequencyNode> root, const std::string& currentCode = "");
};
