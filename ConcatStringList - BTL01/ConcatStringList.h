#ifndef __CONCAT_STRING_LIST_H__
#define __CONCAT_STRING_LIST_H__

#include "main.h"

class ConcatStringList {
public:
    class ReferencesList; // forward declaration
    class DeleteStringList; // forward declaration

public:
    static ReferencesList refList;
    static DeleteStringList delStrList;

    // TODO: may provide some attributes
    
public:
	
	//Using for ConcatStringList Class
	struct CharALNode{
		char* CharArraylist=nullptr;
		int len=0; //Length of each node
		CharALNode* next=nullptr;
	};
	CharALNode* head;
	CharALNode* tail;
	int list_len=0; //List Length
	
	//Using for ReferencesList Class
	struct CharRefNode{
		CharALNode *word=nullptr;
		int num_ref=0;
		CharRefNode *next=nullptr;
	};
	
	//Using for DeleteStringList Class
	struct CharDelNode{
		CharRefNode *Phead=nullptr;
		CharRefNode *Ptail=nullptr;
		CharDelNode *next=nullptr;
	};
	
public:
	ConcatStringList();
    ConcatStringList(const char *s);
    int length() const;
    char get(int index) const;
    int indexOf(char c) const;
    std::string toString() const;
    ConcatStringList concat(const ConcatStringList & otherS) const;
    ConcatStringList subString(int from, int to) const;
    ConcatStringList reverse() const;
    ~ConcatStringList();

public:
	
    class ReferencesList {
        // TODO: may provide some attributes
		public:
			CharRefNode *refHead;
			CharRefNode *refTail;
			int ref_list_len;
        public:
        	
        	ReferencesList();
        	CharRefNode *find_curr(CharALNode *target);
        	CharRefNode *find_pre(CharALNode *target);
        	void addRefNode1(CharRefNode *New, bool found);
			void addRefNode2(CharALNode *New, int update_value);
			
            int size() const;
            int refCountAt(int index) const;
            std::string refCountsString() const;
    };

    class DeleteStringList {
        // TODO: may provide some attributes
		public:
			CharDelNode *delHead;
			CharDelNode *delTail;
			int del_list_len;
        public:
        	
        	DeleteStringList();
        	void deleteDelNode(CharDelNode *pre, CharDelNode *curr);
			void addDelNode(CharDelNode *del_curr);
			
            int size() const;
            std::string totalRefCountsString() const;
    };
};

#endif // __CONCAT_STRING_LIST_H__
