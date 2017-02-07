#include <be/support/Debug.h>
#include "CLVRefListItem.h"

CLVRefListItem::CLVRefListItem(entry_ref* entryRef, node_ref* nodeRef,
		uint32 level, bool superitem, bool expanded,
		float minheight) : CLVEasyItem(level,superitem,expanded,minheight)
{
	PRINT(("CLVRefListItem::CLVRefListItem(entry_ref*,node_ref*)\n"));

	entry = 0;
	node = 0;

	if(entryRef)
	{
		entry = new entry_ref(*entryRef);
	}

	if(nodeRef)
	{
		node = new node_ref(*nodeRef);
	}
}

CLVRefListItem::~CLVRefListItem()
{
	PRINT(("CLVRefListItem::~CLVRefListItem()\n"));

	delete entry;
	delete node;
}

entry_ref*
CLVRefListItem::EntryRef()
{
	PRINT(("CLVRefListItem::EntryRef()\n"));

	return entry;
}

node_ref*
CLVRefListItem::NodeRef()
{
	PRINT(("CLVRefListItem::NodeRef()\n"));

	return node;
}

void
CLVRefListItem::SetEntryRef(entry_ref* entryRef)
{
	PRINT(("CLVRefListItem::SetEntryRef(entry_ref*)\n"));

	delete entry;
	entry = 0;

	if(entryRef)
	{
		entry = new entry_ref(*entryRef);
	}
}

void
CLVRefListItem::SetNodeRef(node_ref* nodeRef)
{
	PRINT(("CLVRefListItem::SetNodeRef(node_ref*)\n"));

	delete node;
	node = 0;
	if(nodeRef)
	{
		node = new node_ref(*nodeRef);
	}
}

