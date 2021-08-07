#ifndef DLINK_H
#define DLINK_H


class DLink
{
public:

	//----------------------------------------------
	// DLINK STATIC FUNCTIONS.
	//----------------------------------------------

	// add at front of list.
	static void AddAtFront(DLink*& pHead, DLink* pNewData);

	// delete the given node from the list.
	static void DeleteByNode(DLink*& pHead, DLink* pNewData);

	// delete from the front of list and return deleted node.
	static DLink* DeleteAtFront(DLink*& pHead);

	//----------------------------------------------
	// DATA.
	//----------------------------------------------

	DLink* pNext;
	DLink* pPrev;

protected:

	//----------------------------------------------
	// BIG FOUR.
	//----------------------------------------------

	DLink();
	DLink(const DLink&) = delete;
	const DLink& operator = (const DLink&) = delete;
	virtual ~DLink();

	//----------------------------------------------
	// CLEAR LINK.
	//----------------------------------------------

	void ClearLink();
};

#endif