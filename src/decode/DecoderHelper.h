/*********************************************************
 *
 * DecoderHelper
 *
 * Class, helping with internal decoding proccess
 *
 *********************************************************/

#pragma once

#include <memory>
#include <unordered_map>

#include "../common/common.h"

class DecoderHelper
{
public:
    // Simple tree implementation
    struct Node
    {
        char                  character;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
    };

    std::string getCodeFromNumber(encodedData_t number, size_t maxSymbols); // building a code

    void buildTree(const codesMap_t& codes); // building a tree from symbols codes
    void iterate(bool goLeft);               // move left or right from current node
    bool currentIsLeaf() const;
    void setCurrentToRoot() { _currentNode = _rootNode; }
    char currentCharacter() const { return _currentNode->character; }

private:
    std::shared_ptr<Node> _rootNode;
    std::shared_ptr<Node> _currentNode;

    void buildNode(std::shared_ptr<Node>& node, const codePair_t& code, size_t currentIndex = 0) const;
};
