#include "DecoderHelper.h"

#include "../common/common.h"

using namespace std;

void DecoderHelper::iterate(bool goLeft)
{
    _currentNode = goLeft ? _currentNode->left : _currentNode->right;
}

void DecoderHelper::buildNode(std::shared_ptr<Node>& node, const std::pair<char, std::string>& code, size_t currentIndex) const
{
    if (currentIndex >= code.second.size())
    {
        node->character = code.first;
        return;
    }
    const auto& nextCodedNumber = code.second[currentIndex];
    if (nextCodedNumber == '0')
    {
        if (!node->left)
            node->left = std::make_shared<Node>();
        buildNode(node->left, code, ++currentIndex);
    }
    else if (nextCodedNumber == '1')
    {
        if (!node->right)
            node->right = std::make_shared<Node>();
        buildNode(node->right, code, ++currentIndex);
    }
}

void DecoderHelper::buildTree(const std::unordered_map<char, std::string>& codes)
{
    _rootNode = std::make_shared<Node>();

    for (const auto& code : codes)
    {
        buildNode(_rootNode, code);
    }

    _currentNode = _rootNode;
}

std::string DecoderHelper::getCodeFromNumber(unsigned char number, size_t maxSymbols)
{
    string code;
    size_t symbolsToRead = min(maxSymbols, bitsInByte);

    code.reserve(symbolsToRead);

    for (size_t i = 0; i < symbolsToRead; i++)
    {
        if ((number >> i) & 1)
            code.push_back('1');
        else
            code.push_back('0');
    }
    return code;
}
