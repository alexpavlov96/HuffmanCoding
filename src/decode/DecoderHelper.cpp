/*********************************************************
 *
 * DecoderHelper
 *
 * Class, helping with internal decoding proccess
 *
 *********************************************************/

#include "DecoderHelper.h"

#include "../common/common.h"

using namespace std;

/*********************************************************
 *  move left or right from current node
 */
void DecoderHelper::iterate(bool goLeft)
{
    _currentNode = goLeft ? _currentNode->left : _currentNode->right;
}

/*********************************************************
 *  building a node recursively by reading next bit of code
 */
void DecoderHelper::buildNode(std::shared_ptr<Node>& node, const codePair_t& code, size_t currentIndex) const
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

/*********************************************************
 *  building a tree from symbols codes
 */
void DecoderHelper::buildTree(const codesMap_t& codes)
{
    _rootNode = std::make_shared<Node>();

    for (const auto& code : codes)
    {
        buildNode(_rootNode, code);
    }

    _currentNode = _rootNode;
}

/*********************************************************
 *  building a code
 *
 *  - building a string of bits from a 8-bit number, taking no more than maxSymbols bits
 */
std::string DecoderHelper::getCodeFromNumber(encodedData_t number, size_t maxSymbols)
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

/*********************************************************
 *  - checks is current node is a leaf
 *  - throws an exception if called while current node is nullptr
 */
bool DecoderHelper::currentIsLeaf() const
{
    if (!_currentNode)
        throw std::logic_error("unexpected nullptr current leaf");

    return !_currentNode->left && !_currentNode->right;
}
