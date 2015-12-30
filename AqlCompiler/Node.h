#pragma once

// 负责记录当前节点属于源文本的第几行，方便输出错误信息。
class Node 
{
public:
    int lexline = 0;
    Node() { }
};

