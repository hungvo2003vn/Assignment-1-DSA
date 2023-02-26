#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h> // This library is only available in MSVC++ 
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
using namespace std;

// Do not modify the first 15 line, myAssert function and main function

/*                     WELCOME TO MY DSA DEBUG TESTING 
Please read this test's manual before testing so that the tester will run correctly
Each line of test is one instruction, the prototype of instruction and return result will be in following:
- CheckMemoryLeaks: returns the memory leaking's report 
By default, when you use it as the first instruction, the report will show you like this:
Detected memory leaks!
Dumping objects ->
{186} normal block at 0x014738F8, 32 bytes long.
 Data: <CheckMemoryLeaks> 43 68 65 63 6B 4D 65 6D 6F 72 79 4C 65 61 6B 73
{168} normal block at 0x014713D8, 8 bytes long.
 Data: <x       > 78 FD 0F 01 00 00 00 00
{167} normal block at 0x014711E0, 8 bytes long.
 Data: <        > 9C FD 0F 01 00 00 00 00
{166} normal block at 0x01471448, 8 bytes long.
 Data: <        > C0 FD 0F 01 00 00 00 00
{165} normal block at 0x01471D38, 400 bytes long.
 Data: <                > 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
{164} normal block at 0x01471480, 8 bytes long.
 Data: <        > E4 FD 0F 01 00 00 00 00
Object dump complete.
(For x86 debugging)

Or like this:
Detected memory leaks!
Dumping objects ->
{186} normal block at 0x000001BB0D3820B0, 32 bytes long.
 Data: <CheckMemoryLeaks> 43 68 65 63 6B 4D 65 6D 6F 72 79 4C 65 61 6B 73
{168} normal block at 0x000001BB0D384780, 16 bytes long.
 Data: <   ye           > 08 E2 8F 79 65 00 00 00 00 00 00 00 00 00 00 00
{167} normal block at 0x000001BB0D384F50, 16 bytes long.
 Data: <   ye           > C8 E1 8F 79 65 00 00 00 00 00 00 00 00 00 00 00
{166} normal block at 0x000001BB0D384AF0, 16 bytes long.
 Data: <   ye           > 88 E1 8F 79 65 00 00 00 00 00 00 00 00 00 00 00
{165} normal block at 0x000001BB0D3857C0, 800 bytes long.
 Data: <                > 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
{164} normal block at 0x000001BB0D384CD0, 16 bytes long.
 Data: <H  ye           > 48 E1 8F 79 65 00 00 00 00 00 00 00 00 00 00 00
Object dump complete.
(for x64 debugging)

 This is the memory leak in the stack of the main function because main function is not complete, don't need to care about that
 If you allocate memory without freeing, the report will be like this (I take one example using x86 debugging, x64 is the same):
Detected memory leaks!
Dumping objects ->
{187} normal block at 0x011B35D8, 32 bytes long.
 Data: <CheckMemoryLeaks> 43 68 65 63 6B 4D 65 6D 6F 72 79 4C 65 61 6B 73
C:\Users\VOSTRO 3490\source\repos\concat_string_Debug\concat_string_Debug\concat_string_Debug.cpp(803) : {169} normal block at 0x011B0AE8, 4 bytes long.
 Data: <    > CD CD CD CD // this two lines show the memory leak, at line 803 (the number in ())
{168} normal block at 0x011B1058, 8 bytes long.
 Data: <        > E8 F9 CF 00 00 00 00 00
{167} normal block at 0x011B1218, 8 bytes long.
 Data: <        > 0C FA CF 00 00 00 00 00
{166} normal block at 0x011B1560, 8 bytes long.
 Data: <0       > 30 FA CF 00 00 00 00 00
{165} normal block at 0x011B1D38, 400 bytes long.
 Data: <                > 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
{164} normal block at 0x011B1020, 8 bytes long.
 Data: <T       > 54 FA CF 00 00 00 00 00
Object dump complete.

- init x y: create a new ConcatStringList with variable y (as a string) and store it in the CSLVector at index x (x is an integer between 0 and 99)
By default, y does not contain double quotes "" and other function (single_concat, double_concat, subString, reverse), space is replaced by '_'
Except:
"empty string": pass the empty string into parameter constructor
"init_object": initialize the object with default constructor
+ Return result: "Success" if an object is created, "Failed to allocate memory" if an object cannot be created, "Memory will be leaked" if the object
at index x has been created with non_default constructor

- length var: calculate the length of variable (can be a number between 0 to 99 to get the length of CSLVector[var], refList, delStrList)
+ Return result: the length of the variable object

- get x idx: return the character at index idx of object number x in CSLVector
+ Return result: one character if index is valid, exception otherwise

- indexOf x c: return the first appearance of character c in object number x in CSLVector
+ Return result: one integer as the index of character c (-1 if not found)

- subString x y from to: take the substring from index (from) to index (to) of object y and store it in object x (new operator was being used)
+ Return result: "Success" if an object is created, "Failed to allocate memory" if an object cannot be created, "Memory will be leaked" if the object
at index x has been created with non_default constructor, exception if index if invalid

- reverse x y: reverse the object y and store it in object x (new operator was being used)
+ Return result: "Success" if an object is created, "Failed to allocate memory" if an object cannot be created, "Memory will be leaked" if the object
at index x has been created with non_default constructor

- single_concat x y z: concatenate y and z (y first, z next) and store the result in object x (new operator was being used)
+ Return result: "Success" if an object is created, "Failed to allocate memory" if an object cannot be created, "Memory will be leaked" if the object
at index x has been created with non_default constructor, "An object cannot appear twice in function concat() !" if y = z, "Object is not initialize"
if at least one object y or z is null

- double_concat: x y z t: concatenate y, z, t in format y->concat(*z).concat(*t) and store it in object x (new operator was being used)
+ + Return result: "Success" if an object is created, "Failed to allocate memory" if an object cannot be created, "Memory will be leaked" if the
object at index x has been created with non_default constructor, "An object cannot appear twice in function concat() !" if at least one pair in tuple
(y, z, t) has the same value (for example y = z is not valid), "Object is not initialize" if at least one object y, z or t is null

- delete x: delete object x and set it to null pointer
If you want to use static ConcatStringList variable and want to check for memory leaks, perform deletion in reverse order
For example:
init 0 Hello,
init 1 _world
single_concat 2 0 1
For static ConcatStringList variable, the deletion will be
delete 2
delete 1
delete 0
Since CSLVector is the vector of ConcatStringList*, you have to use 'delete' instruction of single object (if it was created)
+ Return result: the deletion does not print any result

- refCountAt x: return the number of references in refList at index x
+ Return result: one integer represents the number of references in refList at index x if x is valid, exception otherwise

- refCountsString: return the string represents the number of references of each nodes in refList
+ Return result: one string represents the number of references of each nodes in refList

- totalRefCountsString: return the string represents the total number of references of each nodes in delStrList
+ Return result: one string represents the total number of references of each nodes in refList
 */

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
    bool isEmptyList() { return this->head==nullptr;}

public:
	
    class ReferencesList {
        // TODO: may provide some attributes
		public:
			CharRefNode *refHead;
			CharRefNode *refTail;
			int ref_list_len;
			int non_ref;
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
        	CharDelNode *find_pre(CharRefNode *node_head, CharRefNode *node_tail);
        	CharDelNode *find_curr(CharRefNode *node_head, CharRefNode *node_tail);
        	void deleteDelNode(CharRefNode *node_head, CharRefNode *node_tail);
			void addDelNode(CharRefNode *node_head, CharRefNode *node_tail);
			
            int size() const;
            std::string totalRefCountsString() const;
    };
};

ConcatStringList::ReferencesList ConcatStringList::refList = ConcatStringList::ReferencesList();
ConcatStringList::DeleteStringList ConcatStringList::delStrList = ConcatStringList::DeleteStringList();

ConcatStringList::ConcatStringList(){
	head=nullptr;
	tail=nullptr;
	list_len=0;
}

ConcatStringList::ConcatStringList(const char *s){
    CharALNode* tmp= new CharALNode;
    	
    while(s[tmp->len]!='\0') ++tmp->len; //Estimate length of s
	tmp->CharArraylist=new char[tmp->len+1]; //Declare pointer with s.length()	
    for(int i=0;i<tmp->len+1;i++) tmp->CharArraylist[i]=s[i]; //Deep copy s
    
    head=tmp;
    tail=tmp;
    	
    list_len+=tmp->len;
    //Add to References List
    refList.addRefNode2(head,1);
    refList.addRefNode2(tail,1);
}

int ConcatStringList::length() const{
	return list_len;
}

char ConcatStringList::get(int index) const{
	if(index<0 || index>=list_len)
		throw out_of_range("Index of string is invalid!");
	
	CharALNode* start=head;
	int sum_len=start->len;
	while(sum_len<index+1){
		if(start->next==nullptr) break;
		else start=start->next;
		sum_len+=start->len;
	}
	sum_len-=start->len;
	index-=sum_len;
	return start->CharArraylist[index];
}

int ConcatStringList::indexOf(char c) const{
	CharALNode* start=head;
	int sum_len=0;
	
	for(int i=0;i<list_len;i++)
	{
		if(start->CharArraylist[i-sum_len]==c) return i;
		
		if(i-sum_len==start->len-1)
		{
			sum_len+=start->len;
			start=start->next;
		}
	}
	return -1;
}

std::string ConcatStringList::toString() const{
	CharALNode* start=head;
	string ans="";
	int sum_len=0;
	
	for(int i=0;i<list_len;i++)
	{
		
		ans+=start->CharArraylist[i-sum_len];
		
		if(i-sum_len==start->len-1)
		{
			sum_len+=start->len;
			start=start->next;
		}
	}
	return ans;
}

ConcatStringList ConcatStringList::concat(const ConcatStringList & otherS) const{
	ConcatStringList ans;
	ans.head=head;
	ans.tail=tail;
	
	ans.tail->next=otherS.head;
	ans.tail=otherS.tail;
	
	ans.list_len=list_len+otherS.list_len;
	
	//Add to References List
    refList.addRefNode2(ans.head,1);
    refList.addRefNode2(ans.tail,1);
	return ans;
}

ConcatStringList ConcatStringList::subString(int from, int to) const{
	if((from<0 || from>=list_len)||(to<0 || to>=list_len))
		throw out_of_range("Index of string is invalid");
	else if(from>=to) 
		throw logic_error("Invalid range");
	//else
	int sum_len=0;
	ConcatStringList ans;
	CharALNode *start= new CharALNode; //Deep copy Node 
	CharALNode *tmp=head; //traveling Node
	
	for(int i=0;i<to;i++){
		
		if(i<from){
			if(i-sum_len==tmp->len-1)
			{
				sum_len+=tmp->len;
				tmp=tmp->next;
			}
			else continue;
		}
		
		if(i==from)
		{
			start->len=tmp->len-(i-sum_len); //length of first node
			start->CharArraylist=new char[start->len+1]; //Declare size of first node
			start->CharArraylist[start->len]='\0';
			
			int j=0;
			while(j<start->len){
				start->CharArraylist[j]=tmp->CharArraylist[i-sum_len];
				
				if(i==to-1) //Special case
				{
					ans.head=start;
					ans.tail=start;
					ans.list_len=to-from;
					
					//Add to References List
    				refList.addRefNode2(ans.head,1);
    				refList.addRefNode2(ans.tail,1);
					return ans;
				}
				++j;
				++i;
			}
			
			ans.head=start;
			
			//next node
			sum_len+=tmp->len;
			start->next=new CharALNode;
			start=start->next;
			tmp=tmp->next;
			
			start->len=tmp->len;
			if(start->len+sum_len>to) start->len=to-sum_len;
			start->CharArraylist=new char[start->len+1];
			start->CharArraylist[start->len]='\0';
			
			--i;
		}
		else if(i-sum_len==tmp->len-1){
			start->CharArraylist[start->len-1]=tmp->CharArraylist[i-sum_len];
			
			//next node
			sum_len+=tmp->len;
			start->next=new CharALNode;
			start=start->next;
			tmp=tmp->next;
			
			start->len=tmp->len;
			if(start->len+sum_len>to) start->len=to-sum_len;
			start->CharArraylist=new char[start->len+1];
			start->CharArraylist[start->len]='\0';
		}
		else if(i>from){
			start->CharArraylist[i-sum_len]=tmp->CharArraylist[i-sum_len];
		}

		if(i==to-1) break;
	}
	
	ans.tail=start;
	ans.list_len+=to-from;
	
	//Add to References List
    refList.addRefNode2(ans.head,1);
    refList.addRefNode2(ans.tail,1);
	
	return ans;
}

ConcatStringList ConcatStringList::reverse() const{
	//Edge case
	if(head==nullptr || list_len==0) return NULL;
	
	//Declare answer and deep copy the old object
	ConcatStringList *ans=new ConcatStringList;
	ans->list_len=list_len; //copy length
	CharALNode *new_node=new CharALNode; //deep copy node
	ans->head=new_node;
	CharALNode *travel=head; //Travel node

	while(travel!=tail->next){

		//Deep copy data from the travel
		new_node->len=travel->len;
		new_node->CharArraylist=new char[new_node->len+1];
		new_node->CharArraylist[new_node->len]='\0';
		for(int i=0;i<new_node->len;i++) new_node->CharArraylist[i]=travel->CharArraylist[i];
		
		if(travel==tail){
			ans->tail=new_node;
			ans->tail->next=nullptr;
			break;
		}
		new_node->next=new CharALNode;
		new_node=new_node->next;
		travel=travel->next;
	}

	//Reverse Node
	CharALNode *curr=ans->head;
	CharALNode *pre=nullptr;
	CharALNode *next=nullptr;
	while(curr!=nullptr){
		
		next=curr->next;//Store next node to move
		
		curr->next=pre;
		pre=curr;
		curr=next;

	}
	ans->head=pre;

	//Reverse Character in each node
	CharALNode *start=ans->head;
	while(start!=nullptr){
		for(int i=0;i<start->len/2;i++)
		{
			char temp=start->CharArraylist[i];
			start->CharArraylist[i]=start->CharArraylist[start->len-1-i];
			start->CharArraylist[start->len-1-i]=temp;
		}
		if(start->next==nullptr) ans->tail=start;
		start=start->next;
	}
	//Add to References List
    refList.addRefNode2(ans->head,1);
    refList.addRefNode2(ans->tail,1);
	
	return *ans;
}

ConcatStringList::~ConcatStringList(){
	
	refList.addRefNode2(head,-1);
	refList.addRefNode2(tail,-1);
	
	//update reference list
	CharRefNode *find_head=refList.find_curr(head);
	CharRefNode *find_tail=refList.find_curr(tail);
	delStrList.addDelNode(find_head,find_tail); //add to delete string list
	
	if(find_head->num_ref + find_tail->num_ref==0)
	{
		
		delStrList.deleteDelNode(find_head,find_tail);
		CharALNode *curr=head;
		CharALNode *next=nullptr;
		
		while(curr!=tail->next)
		{
			next=curr->next;
			delete[] curr->CharArraylist;
			delete curr;
			curr=next;
		}
	}
	//Check if all node is 0
	//check to delete all in references list
	if(refList.non_ref==refList.size())
	{
		CharRefNode *current=refList.refHead;
		CharRefNode *after=nullptr;
		while(current!=nullptr)
		{
			after=current->next;
			delete current;
			current=after;
		}
		refList.refHead=nullptr;
		refList.refTail=nullptr;
		refList.ref_list_len=0;
		refList.non_ref=0;
	}
}
///////////////////////REFERENCES-LIST CLASS/////////////////////
ConcatStringList::ReferencesList::ReferencesList(){
	refHead=nullptr;
	refTail=nullptr;
	ref_list_len=0;
	non_ref=0;
}

ConcatStringList::CharRefNode* ConcatStringList::ReferencesList::find_curr(CharALNode *target){
	
	CharRefNode *curr=refHead;
	
	while(curr!=nullptr)
	{
		if(curr->word==target) return curr;
		curr=curr->next;
	}
	return nullptr;
}

ConcatStringList::CharRefNode* ConcatStringList::ReferencesList::find_pre(CharALNode *target){
	
	CharRefNode *pre=nullptr;
	CharRefNode *curr=refHead;
	
	while(curr!=nullptr)
	{
		if(curr->word==target) return pre;
		pre=curr;
		curr=curr->next;
	}
	return nullptr;
}

void ConcatStringList::ReferencesList::addRefNode1(CharRefNode *New, bool found=false){
	
	if(New->num_ref==0) ++non_ref; //Estimate numbers of zero reference in References List
	
	//Case: Add the node to index 0 
	if(refHead==nullptr || refHead->num_ref==0  || (refHead->num_ref>=New->num_ref && New->num_ref!=0))
	{
		New->next=refHead;
		refHead=New;
		
		if(refTail==nullptr)
		{
			refTail=New;
			refTail->next=nullptr;
		}
	}
	//The new node has 0 references
	else if(New->num_ref==0)
	{
		refTail->next=New;
		refTail=New;
		refTail->next=nullptr;
	}	
	else
	{
		//Normal case
		CharRefNode *pre=nullptr;
		CharRefNode *curr=refHead;
		
		while(curr!=nullptr && curr->num_ref!=0 && curr->num_ref < New->num_ref)
		{
			pre=curr;
			curr=curr->next;
		}
		//Add the node to the References List
		New->next=pre->next;
		pre->next=New;
		if(curr==nullptr)
		{
			refTail=New;
			refTail->next=nullptr;
		}
	}
	
	if(!found) ref_list_len++; //update length of node
	
}

void ConcatStringList::ReferencesList::addRefNode2(CharALNode *New, int update_value){
	
	CharRefNode *pre=find_pre(New);
	CharRefNode *curr=find_curr(New);
	
	if(curr==nullptr)
	{
		//Create new node for CharALNode* New
		CharRefNode *new_ele=new CharRefNode;
		new_ele->word=New;
		new_ele->num_ref=1;
		new_ele->next=nullptr;
		
		//Inserting Node in RefList
		addRefNode1(new_ele,false);
	}
	//case: node are found!
	else
	{
		CharRefNode *new_ele=curr;
		new_ele->num_ref+=update_value;
		
		//Deleting the old node's pointer
		if(pre!=nullptr)
		{
			pre->next=curr->next;
			if(refTail==curr) refTail=pre;
		}
		else
		{
			refHead=curr->next;
			if(ref_list_len==2) refTail=refHead;
		}
		
		curr=nullptr;
		addRefNode1(new_ele,true);
	}
}

int ConcatStringList::ReferencesList::size() const{
	return ref_list_len;
}

int ConcatStringList::ReferencesList::refCountAt(int index) const{
	
	if(index<0 || index>=ref_list_len)
		throw out_of_range("Index of references list is invalid!");
	
	CharRefNode *curr=refHead;
	int i=0;
	while(i!=index){
		i++;
		curr=curr->next;
	}
	return curr->num_ref;
}

std::string ConcatStringList::ReferencesList::refCountsString() const{
	
	string ans="RefCounts[";
	CharRefNode *curr=refHead;
	while(curr!=nullptr){
		string num=to_string(curr->num_ref);
		ans+=num+",";
		curr=curr->next;
	}
	if(refHead!=nullptr) ans.pop_back(); //non-null list 
	ans+="]";
	return ans;
}
	
//////////////////////DELETE-STRING CLASS////////////////////////
ConcatStringList::DeleteStringList::DeleteStringList(){
	delHead=nullptr;
	delTail=nullptr;
	del_list_len=0;
}

ConcatStringList::CharDelNode* ConcatStringList::DeleteStringList::find_pre(CharRefNode *node_head, CharRefNode *node_tail){
	
	CharDelNode *pre=nullptr;
	CharDelNode *curr=delHead;
	while(curr!=nullptr){
		if(curr->Phead==node_head && curr->Ptail==node_tail) return pre;
		pre=curr;
		curr=curr->next;
	}
	return nullptr;
}

ConcatStringList::CharDelNode* ConcatStringList::DeleteStringList::find_curr(CharRefNode *node_head, CharRefNode *node_tail){
	
	CharDelNode *curr=delHead;
	while(curr!=nullptr){
		if(curr->Phead==node_head && curr->Ptail==node_tail) return curr;
		curr=curr->next;
	}
	return nullptr;
}

void ConcatStringList::DeleteStringList::deleteDelNode(CharRefNode *node_head, CharRefNode *node_tail){
	
	//Find the node to delete
	CharDelNode *pre=find_pre(node_head, node_tail);
	CharDelNode *curr=find_curr(node_head, node_tail);
	
	if(curr==nullptr) return; //Cannot find the node to delete
	
	if(pre==nullptr) //Delete at index 0
	{
		delHead=curr->next;
		if(del_list_len==2) delTail=delHead;
	}
	else 
	{
		pre->next=curr->next;
		if(curr==delTail) delTail=pre;
	}
	delete curr;
	
	del_list_len--;
}

void ConcatStringList::DeleteStringList::addDelNode(CharRefNode *node_head, CharRefNode *node_tail){
	
	//Find new node
	CharDelNode *pre=find_pre(node_head, node_tail);
	CharDelNode *curr=find_curr(node_head, node_tail);
	
	if(curr==nullptr)
	{
		//Create new node
		CharDelNode *new_ele=new CharDelNode;
		new_ele->Phead=node_head;
		new_ele->Ptail=node_tail;
		
		if(pre==nullptr) delHead=delTail=new_ele;
		else
		{
			delTail->next=new_ele;
			delTail=new_ele;
		}
		++del_list_len;
	}
}

int ConcatStringList::DeleteStringList::size() const{
	return del_list_len;
}

std::string ConcatStringList::DeleteStringList::totalRefCountsString() const{
	
	CharDelNode *curr=delHead;
	string ans="";
	while(curr!=nullptr){
		
		int count=curr->Phead->num_ref+curr->Ptail->num_ref;
		if(curr->Phead==curr->Ptail) count-=curr->Phead->num_ref;
		ans+=to_string(count)+",";
		curr=curr->next;
	}
	if(ans.back()==',') ans.pop_back();
	return "TotalRefCounts["+ans+"]";
}

void myAssert(bool val, string msg)
{
    if (val == false)
    {
        cout << msg << '\n';
        abort();
    }
}

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector<ConcatStringList*> CSLVector(100, nullptr);
    //Adding list
    ConcatStringList * s1 = new ConcatStringList("Hello");
    ConcatStringList * s2 = new ConcatStringList("_world");
    ConcatStringList * s3 = new ConcatStringList(s1->concat(*s2));
    CSLVector[0]=s1;
    CSLVector[1]=s2;
    CSLVector[2]=s3;
    
    string key, variable, instruction;
    do
    {
        cin >> key;
        //cin.ignore();
        if (key == "toString")
        {
            cin >> variable;
            int index = stoi(variable);
            myAssert((index >= 0 && index < 100), "Index is out of bound!");
            cout << CSLVector[index]->toString() << '\n';
        }
        else if (key == "length")
        {
            cin >> variable;
            if (variable == "refList")
            {
                cout << ConcatStringList::refList.size() << '\n';
            }
            else if (variable == "delStrList")
            {
                cout << ConcatStringList::delStrList.size() << '\n';
            }
            else
            {
                int index = stoi(variable);
                myAssert((index >= 0 && index < 100), "Index is out of bound!");
                cout << "length of object number " << index << ": " << CSLVector[index]->length() << '\n';
            }
        }
        else if (key == "refCountAt")
        {
            int idx;
            cin >> idx;
            try
            {
                cout << ConcatStringList::refList.refCountAt(idx) << '\n';
            }
            catch (exception& e)
            {
                cout << e.what() << '\n';
            }
        }
        else if (key == "refCountsString")
        {
            cout << ConcatStringList::refList.refCountsString() << '\n';
        }
        else if (key == "totalRefCountsString")
        {
            cout << ConcatStringList::delStrList.totalRefCountsString() << '\n';
        }
        else if (key == "get")
        {
            cin >> variable;
            int idx;
            cin >> idx;
            int index = stoi(variable);
            myAssert((index >= 0 && index < 100), "Index is out of bound!");
            try
            {
                cout << CSLVector[index]->get(idx) << '\n';
            }
            catch (exception& e)
            {
                cout << e.what() << '\n';
            }
        }
        else if (key == "indexOf")
        {
            char c;
            cin >> variable >> c;
            int index = stoi(variable);
            myAssert((index >= 0 && index < 100), "Index is out of bound!");
            cout << CSLVector[index]->indexOf(c) << '\n';
        }
        else if (key == "subString")
        {
            cin >> variable >> instruction;
            int index1 = stoi(variable);
            int index2 = stoi(instruction);
            myAssert((index1 >= 0 && index1 < 100), "Index is out of bound!");
            myAssert((index2 >= 0 && index2 < 100), "Index is out of bound!");
            myAssert(CSLVector[index1] == nullptr || CSLVector[index1]->isEmptyList() == true, "Memory will be leaked!");
            int from, to;
            cin >> from >> to;
            try
            {
                CSLVector[index1] = new ConcatStringList(CSLVector[index2]->subString(from, to));
                cout << (CSLVector[index1] == nullptr ? "Failed to allocate memory\n" : "Success\n");
            }
            catch (exception& e)
            {
                cout << e.what() << '\n';
            }
        }
        else if (key == "reverse")
        {
            cin >> variable >> instruction;
            int index1 = stoi(variable);
            int index2 = stoi(instruction);
            int index = stoi(variable);
            myAssert((index1 >= 0 && index1 < 100), "Index is out of bound!");
            myAssert((index2 >= 0 && index2 < 100), "Index is out of bound!");
            myAssert(CSLVector[index1] == nullptr || CSLVector[index1]->isEmptyList() == true, "Memory will be leaked!");
            CSLVector[index1] = new ConcatStringList(CSLVector[index2]->reverse());
            cout << (CSLVector[index1] == nullptr ? "Failed to allocate memory\n" : "Success\n");
        }
        else if (key == "single_concat")
        {
            string safe_object;
            cin >> variable >> instruction >> safe_object;
            myAssert(instruction != safe_object, "An object cannot appear twice in function concat() !");
            int index1 = stoi(variable);
            int index2 = stoi(instruction);
            int index3 = stoi(safe_object);
            myAssert((index1 >= 0 && index1 < 100), "Index is out of bound!");
            myAssert((index2 >= 0 && index2 < 100), "Index is out of bound!");
            myAssert((index3 >= 0 && index3 < 100), "Index is out of bound!");
            myAssert((CSLVector[index2] != nullptr) || (CSLVector[index3] != nullptr), "Object is not initialize!");
            myAssert((variable != safe_object) || (variable != instruction), "Memory will be leaked!");
            myAssert(CSLVector[index1] == nullptr || CSLVector[index1]->isEmptyList() == true, "Memory will be leaked!");
            CSLVector[index1] = new ConcatStringList(CSLVector[index2]->concat(*CSLVector[index3]));
            cout << (CSLVector[index1] == nullptr ? "Failed to allocate memory\n" : "Success\n");
        }
        else if (key == "double_concat")
        {
            string safe_object1, safe_object2;
            cin >> variable >> instruction >> safe_object1 >> safe_object2;
            myAssert((instruction != safe_object1) && (instruction != safe_object2) && (safe_object1 != safe_object2) , "An object cannot appear twice in function concat() !");
            int index1 = stoi(variable);
            int index2 = stoi(instruction);
            int index3 = stoi(safe_object1);
            int index4 = stoi(safe_object2);
            myAssert((index1 >= 0 && index1 < 100), "Index is out of bound!");
            myAssert((index2 >= 0 && index2 < 100), "Index is out of bound!");
            myAssert((index3 >= 0 && index3 < 100), "Index is out of bound!");
            myAssert((index4 >= 0 && index4 < 100), "Index is out of bound!");
            myAssert((CSLVector[index2] != nullptr) || (CSLVector[index3] != nullptr) || (CSLVector[index4] != nullptr), "Object is not initialize!");
            myAssert((variable != safe_object1) || (variable != instruction) || (variable != safe_object2), "Memory will be leaked!");
            myAssert(CSLVector[index1] == nullptr || CSLVector[index1]->isEmptyList() == true, "Memory will be leaked!");
            CSLVector[index1] = new ConcatStringList(CSLVector[index2]->concat(*CSLVector[index3]).concat(*CSLVector[index4]));
            cout << (CSLVector[index1] == nullptr ? "Failed to allocate memory\n" : "Success\n");
        }
        else if (key == "init")
        {
            cin >> variable >> instruction;
            int index1 = stoi(variable);
            myAssert((index1 >= 0 && index1 < 100), "Index is out of bound!");
            myAssert(CSLVector[index1] == nullptr || CSLVector[index1]->isEmptyList() == true, "Memory will be leaked!");
            if (instruction == "\"empty_string\"")
            {
                CSLVector[index1] = new ConcatStringList("");
            }
            else if (instruction == "\"init_object\"")
            {
                CSLVector[index1] = new ConcatStringList();
            }
            else
            {
                CSLVector[index1] = new ConcatStringList(instruction.c_str());
            }
            cout << (CSLVector[index1] == nullptr ? "Failed to allocate memory!\n" : "Success\n");
        }
        else if (key == "CheckMemoryLeaks")
        {
            if(_CrtDumpMemoryLeaks()) cout<<"Memory is Leaked!\n";
            else cout<<"Memory is Protected!\n";
        }
        else if (key == "delete")
        {
            cin >> variable;
            int index1 = stoi(variable);
            myAssert((index1 >= 0 && index1 < 100), "Index is out of bound!");
            delete CSLVector[index1];
            CSLVector[index1] = nullptr;
        }
        else if (key == "end_process")
        {
            cout << "Testing is done!\n";
        }
        else
        {
            cout << "Invalid instruction\n";
            return 0;
        }
    } while (key != "end_process");
}

