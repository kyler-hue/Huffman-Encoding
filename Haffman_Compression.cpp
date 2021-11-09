#include <iostream> 
#include <cstdlib> 
#include<vector>
#include <iterator> 
#include <map> 
#include <queue>

using namespace std;

map<char, string> codesMap;
map<char, int> frequencyMap;

struct MinHeapNode
{
    char data;
    int frequency;
    MinHeapNode *left;
    MinHeapNode *right;

    MinHeapNode(char data, int frequency)
    {
        left = right = NULL;
        this->data = data;
        this->frequency = frequency;
    }
};

struct compare
{
    bool operator()(MinHeapNode* left, MinHeapNode* right)
    {
        return (left->frequency > right->frequency);
    }
};

void printCodes(struct MinHeapNode* root, string inputString)
{
    if (!root)
    {
        return;
    }
    if (root->data != '$')
    {
        cout << root->data << ": " << inputString << "\n";
    }
    printCodes(root->left, inputString + "0");
    printCodes(root->right, inputString + "1");
}

void storeCodes(struct MinHeapNode* root, string inputString)
{
    if (root == NULL)
    {
        return;
    }

    if (root->data != '$')
    {
        codesMap[root->data] = inputString;
    }

    storeCodes(root->left, inputString + "0");
    storeCodes(root->right, inputString + "1");
}

priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

void HuffmanCodes(int size)
{
    struct MinHeapNode *left, *right, *top;
    for (map<char, int>::iterator v = frequencyMap.begin(); v != frequencyMap.end(); v++)
    {
        minHeap.push(new MinHeapNode(v->first, v->second));
    }

    while (minHeap.size() != 1)
    {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        top = new MinHeapNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    storeCodes(minHeap.top(), "");

    cout << "Characters and their Codes:\n";
    printCodes(minHeap.top(), "");
}

void calculateFrequency(string inputString)
{
    for (int i = 0; i < inputString.size(); i++)
    {
        frequencyMap[inputString[i]]++;
    }
}

string decodeString(struct MinHeapNode* root, string inputString)
{
    string answer = "";
    struct MinHeapNode* current = root;
    for (int i = 0; i < inputString.size(); i++)
    {
        if (inputString[i] == '0')
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }

        if (current->left == NULL && current->right == NULL)
        {
            answer += current->data;
            current = root;
        }
    }
    return answer + '\0';
}

string encodeHuffman(string inputString)
{
    string encodedString;
    calculateFrequency(inputString);
    HuffmanCodes(inputString.length());

    for (auto i: inputString)
    {
        encodedString += codesMap[i];
    }
    return encodedString;
}

int main()
{
    string inputString = "All falls into place";
    string encodedString;
    string decodedString;

    encodedString = encodeHuffman(inputString);
    cout << "\nEncoded String:\n" << encodedString << endl;

    decodedString = decodeString(minHeap.top(), encodedString);
    cout << "\nDecoded String:\n" << decodedString << endl;
    return 0;
}
