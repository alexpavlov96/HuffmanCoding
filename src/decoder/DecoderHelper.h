#pragma once

#include <memory>
#include <unordered_map>

class DecoderHelper
{
public:
    struct Node
    {
        char                  character;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
    };

    std::string getCodeFromNumber(unsigned char number, size_t maxSymbols);

    void buildTree(const std::unordered_map<char, std::string>& codes);
    void iterate(bool goLeft);
    bool currentIsLeaf() const { return !_currentNode->left && !_currentNode->right; }
    void setCurrentToRoot() { _currentNode = _rootNode; }
    char currentCharacter() const { return _currentNode->character; }

private:
    std::shared_ptr<Node> _rootNode;
    std::shared_ptr<Node> _currentNode;

    void buildNode(std::shared_ptr<Node>& node, const std::pair<char, std::string>& code, size_t currentIndex = 0) const;
};
