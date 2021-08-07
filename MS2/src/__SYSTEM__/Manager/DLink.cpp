#include "DLink.h"

DLink::DLink()
	:
	pNext(nullptr),
	pPrev(nullptr)
{
}

DLink::~DLink()
{
    this->ClearLink();
}

void DLink::ClearLink()
{
	this->pNext = nullptr;
	this->pPrev = nullptr;
}

//Add to the front of the given head node.
void DLink::AddAtFront(DLink*& pHead, DLink* pNewData)
{
    //Check if data to add is not null.
    assert(pNewData != nullptr);

    //If head is null.
    if (pHead == nullptr)
    {
        pNewData->pNext = nullptr;
        pNewData->pPrev = nullptr;
    }
    else        //If head is not null.
    {
        pNewData->pNext = pHead;
        pNewData->pPrev = nullptr;
        pHead->pPrev = pNewData;
    }

    //Assign head as the added data.
    pHead = pNewData;
}

//Delete a node from the given head node.
void DLink::DeleteByNode(DLink*& pHead, DLink* pNewData)
{
    //Check if node to delete has a next or prev links.
    if (pNewData->pNext == nullptr && pNewData->pPrev == nullptr)
    {
        pHead = nullptr;
    }
    else if (pNewData->pPrev == nullptr)    //Check if there is a prev link. 
    {
        pHead = pHead->pNext;
        pHead->pPrev = nullptr;
    }
    else if (pNewData->pNext == nullptr)    //Check if there is a next link.
    {
        pNewData->pPrev->pNext = nullptr;
    }
    else                    //If no next or prev links are present.
    {
        pNewData->pPrev->pNext = pNewData->pNext;
        pNewData->pNext->pPrev = pNewData->pPrev;
    }

    //Clear links of deleted node.
    pNewData->ClearLink();
}

//Delete from the front of the given head node.
DLink* DLink::DeleteAtFront(DLink*& pHead)
{
    //Temporary data in place of head.
    DLink* pTmp = pHead;

    //If head is null, no data to delete.
    if (pTmp == nullptr)
    {
        return (pTmp);
    }
    else if (pHead->pNext == nullptr)   //If only one data is present.
    {
        pHead = nullptr;
    }
    else if (pHead != nullptr)     //else traverse the list.
    {
        pHead = pHead->pNext;
        pHead->pPrev = nullptr;
    }

    //Clear links of deleted node.
    pTmp->ClearLink();

    //Return deleted node.
    return (pTmp);
}