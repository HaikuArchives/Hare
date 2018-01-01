#ifndef __B_REF_ROW_H__
#define __B_REF_ROW_H__

#include <Entry.h>
#include <Node.h>

#include <ColumnListView.h>

class BRefRow : public BRow
{
public:
								BRefRow(entry_ref* entryRef,
									node_ref* nodeRef = 0);
	virtual						~BRefRow();
								
			entry_ref*			EntryRef();
			node_ref*			NodeRef();
			void				SetEntryRef(entry_ref* entryRef);
			void				SetNodeRef(node_ref* nodeRef);
private:
			entry_ref* 			fentry;
			node_ref* 			fnode;
};

#endif

