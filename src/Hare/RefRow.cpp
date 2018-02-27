#include "RefRow.h"

#include <ColumnTypes.h>
#include <Debug.h>

BRefRow::BRefRow(entry_ref* entryRef, node_ref* nodeRef)
	:
	BRow()
{
	PRINT(("BRefRow::BRefRow(entry_ref*,node_ref*,height)\n"));

	fentry = 0;
	fnode = 0;

	if(entryRef)
	{
		fentry = new entry_ref(*entryRef);
	}

	if(nodeRef)
	{
		fnode = new node_ref(*nodeRef);
	}

	SetField(new BBitmapField(NULL), 0);
	for (int i=1; i <= 9; i++)
	SetField(new BStringField(B_EMPTY_STRING), i);
}

BRefRow::~BRefRow()
{
	PRINT(("BRefRow::~BRefRow()\n"));

	delete fentry;
	delete fnode;
}

entry_ref*
BRefRow::EntryRef()
{
	PRINT(("BRefRow::EntryRef()\n"));

	return fentry;
}

node_ref*
BRefRow::NodeRef()
{
	PRINT(("BRefRow::NodeRef()\n"));

	return fnode;
}

void
BRefRow::SetEntryRef(entry_ref* entryRef)
{
	PRINT(("BRefRow::SetEntryRef(entry_ref*)\n"));

	delete fentry;
	fentry = 0;

	if(entryRef)
	{
		fentry = new entry_ref(*entryRef);
	}
}

void
BRefRow::SetNodeRef(node_ref* nodeRef)
{
	PRINT(("BRefRow::SetNodeRef(node_ref*)\n"));

	delete fnode;
	fnode = 0;
	if(nodeRef)
	{
		fnode = new node_ref(*nodeRef);
	}
}
