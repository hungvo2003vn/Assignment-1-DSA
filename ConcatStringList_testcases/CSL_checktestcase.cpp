#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

using namespace std;

const string dir = "D:\\CODE C++\\ConcatStringList_testcases\\input\\";
const string dir2 = "D:\\CODE C++\\ConcatStringList_testcases\\result\\";

// Replace '_' with your ConcatStringList_testcases's directory
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
    for(int i=0;i<tmp->len;i++) tmp->CharArraylist[i]=s[i]; //Deep copy s
    tmp->CharArraylist[tmp->len]='\0';
    
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
    
	while(start && start!=tail->next)
	{
		for(int i=0;i<start->len;i++) ans+=start->CharArraylist[i];
		start=start->next;
	}
	return ans;
}

ConcatStringList ConcatStringList::concat(const ConcatStringList & otherS) const{
	
	union S
    {
        ConcatStringList ans;
        S()
        {
            ans = ConcatStringList();
        }
        ~S()
        {

        }
    } uni;
	
	uni.ans.head=head;
	uni.ans.tail=tail;
	
	uni.ans.tail->next=otherS.head;
	uni.ans.tail=otherS.tail;
	
	uni.ans.list_len=list_len+otherS.list_len;
	
	//Add to References List
    refList.addRefNode2(uni.ans.head,1);
    refList.addRefNode2(uni.ans.tail,1);
	return uni.ans;
}

ConcatStringList ConcatStringList::subString(int from, int to) const{
	if((from<0 || from>=list_len)||(to<0 || to>list_len))
		throw out_of_range("Index of string is invalid");
	else if(from>=to) 
		throw logic_error("Invalid range");
	//else
	int sum_len=0;
	union S
    {
        ConcatStringList ans;
        S()
        {
            ans = ConcatStringList();
        }
        ~S()
        {

        }
    } uni;
	uni.ans.list_len=to-from;
	
	CharALNode *start= new CharALNode; //Deep copy Node 
	CharALNode *tmp=head; //traveling Node
	
	for(int i=0;i<to;i++){
		
		if(i<from)
		{
			if(i-sum_len==tmp->len-1)
			{
				sum_len+=tmp->len;
				tmp=tmp->next;
			}
			else continue;
		}
		
		else if(i==from)
		{
			start->len=min(tmp->len-(i-sum_len),to-from ); //length of first node
			start->CharArraylist=new char[start->len+1]; //Declare size of first node
			start->CharArraylist[start->len]='\0';
			
			int j=0;
			while(j<start->len){
				start->CharArraylist[j]=tmp->CharArraylist[i-sum_len];
				
				if(i==to-1) //Special case
				{
					uni.ans.head=start;
					uni.ans.tail=start;
					uni.ans.tail->next=nullptr;
					
					//Add to References List
    				refList.addRefNode2(uni.ans.head,1);
    				refList.addRefNode2(uni.ans.tail,1);
					return uni.ans;
				}
				++j;
				++i;
			}
			
			uni.ans.head=start;
			uni.ans.tail=start;
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
		else if(i>from)
		{
			start->CharArraylist[i-sum_len]=tmp->CharArraylist[i-sum_len];
			if(i==to-1)
			{
				//control the tail
				uni.ans.tail->next=start;
				uni.ans.tail=start;
				break;
			}
		}	
		if(i-sum_len==tmp->len-1 && i>from)
		{	
			//control the tail
			uni.ans.tail->next=start;
			uni.ans.tail=start;
			
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
	}
	
	uni.ans.tail->next=nullptr;
	//Add to References List
    refList.addRefNode2(uni.ans.head,1);
    refList.addRefNode2(uni.ans.tail,1);
	
	return uni.ans;
}

ConcatStringList ConcatStringList::reverse() const{
	
	//Declare answer and deep copy the old object
	union S
    {
        ConcatStringList ans;
        S()
        {
            ans = ConcatStringList();
        }
        ~S()
        {

        }
    } uni;
	uni.ans.list_len=list_len; //copy length
	
	CharALNode *travel=head; //Travel node
	while(travel!=tail->next){

		//Deep copy data from the travel
		CharALNode *new_node=new CharALNode; //deep copy node
		new_node->len=travel->len;
		new_node->CharArraylist=new char[new_node->len+1];
		new_node->CharArraylist[new_node->len]='\0';
		for(int i=0;i<new_node->len/2;i++) new_node->CharArraylist[i]=travel->CharArraylist[new_node->len-i-1];
		for(int i=0;i<new_node->len/2;i++) new_node->CharArraylist[new_node->len-i-1]=travel->CharArraylist[i];
		if(new_node->len % 2==1) new_node->CharArraylist[new_node->len/2]=travel->CharArraylist[new_node->len/2];
		
		if(uni.ans.head==nullptr) uni.ans.head=uni.ans.tail=new_node;
		else
		{
			uni.ans.tail->next=new_node;
			uni.ans.tail=new_node;
		}
		travel=travel->next;
	}
	
	//Reverse Node
	CharALNode *curr=uni.ans.head;
	CharALNode *TAIL=curr;
	CharALNode *pre=nullptr;
	CharALNode *next=nullptr;
	while(curr && curr!=uni.ans.tail->next)
	{
		
		next=curr->next;//Store next node to move
		
		curr->next=pre;
		pre=curr;
		curr=next;

	}
	uni.ans.head=pre;
	uni.ans.tail=TAIL;
	uni.ans.tail->next=nullptr;
	
	//Add to References List
    refList.addRefNode2(uni.ans.head,1);
    refList.addRefNode2(uni.ans.tail,1);
    
	return uni.ans;
}

ConcatStringList::~ConcatStringList(){
	
	//update reference list
	refList.addRefNode2(head,-1);
	refList.addRefNode2(tail,-1);
	
	//add to delete string list
	CharDelNode *del_curr=new CharDelNode;
	del_curr->Phead=refList.find_curr(head);
	del_curr->Ptail=refList.find_curr(tail);
	delStrList.addDelNode(del_curr); 
	
	CharDelNode *run=delStrList.delHead;
	CharDelNode *pre=nullptr;
	CharDelNode *next=nullptr;
	while(run && run!=delStrList.delTail->next)
	{
		next=run->next;
		if(run->Phead->num_ref + run->Ptail->num_ref==0)
		{
			if(run->Phead->word!=nullptr && run->Ptail->word!=nullptr)
			{
				
				CharALNode *curr=run->Phead->word;
				CharALNode *next_curr=nullptr;
				
				while(curr && curr!=run->Ptail->word->next)
				{
					next_curr=curr->next;
					////////delete CharALNode///////
					delete[] curr->CharArraylist;
					delete curr;
					////////delete CharALNode///////
					curr=next_curr;
				}
				run->Phead->word=nullptr;
				run->Ptail->word=nullptr;
			}
			delStrList.deleteDelNode(pre, run);
			run=next;
			continue;
		}
		pre=run;
		run=next;
	}
	//check to delete all in references list
	if(refList.refHead->num_ref==0)
	{
		CharRefNode *current=refList.refHead;
		CharRefNode *after=nullptr;
		while(current && current!=refList.refTail->next)
		{
			after=current->next;
			delete current;
			current=after;
		}
		refList.refHead=nullptr;
		refList.refTail=nullptr;
		refList.ref_list_len=0;
	}
}
///////////////////////REFERENCES-LIST CLASS/////////////////////
ConcatStringList::ReferencesList::ReferencesList(){
	refHead=nullptr;
	refTail=nullptr;
	ref_list_len=0;
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

void ConcatStringList::DeleteStringList::deleteDelNode(CharDelNode *pre, CharDelNode *curr){

	if(curr==nullptr) return; //Cannot find the node to delete
	
	--del_list_len;
	if(curr==delHead) //Delete at index 0
	{
		delHead=delHead->next;
		if(del_list_len==0) delTail=delHead;
	}
	else 
	{
		pre->next=curr->next;
		if(curr==delTail) delTail=pre;
	}
	delete curr;
	curr=nullptr;
	if(delTail) delTail->next=nullptr;
	
	return;
}

void ConcatStringList::DeleteStringList::addDelNode(CharDelNode *del_curr){
	
	if(delHead==nullptr) delHead=delTail=del_curr;
	else
	{
		delTail->next=del_curr;
		delTail=del_curr;
	}
	delTail->next=nullptr;
	++del_list_len;
	
	return;
}

int ConcatStringList::DeleteStringList::size() const{
	return del_list_len;
}

std::string ConcatStringList::DeleteStringList::totalRefCountsString() const{
	
	CharDelNode *curr=delHead;
	string ans="";
	if(curr==nullptr) return "TotalRefCounts[]";
	while(curr && curr!=delTail->next){
		
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
        cout << msg;
        //abort();
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
    //_CrtMemState s1, s2, s3;
    vector<ConcatStringList*> CSLVector(100, nullptr);
    //_CrtMemCheckpoint(&s1);
    for (int i = 1; i <= 100; i++)
    {
        cout << "Testcase #" << i << ": ";
        fstream inp(dir + "test" + to_string(i) + ".txt", ios::in);
        fstream out(dir2 + "test" + to_string(i) + ".txt", ios::in);
        string line;
        bool check=true;
        while (getline(inp, line))
        {
            string res_line = "";
            string s = "";
            if (line == "refCountsString")
            {
                getline(out, res_line);
                s = ConcatStringList::refList.refCountsString();
            }
            else if (line == "totalRefCountsString")
            {
                getline(out, res_line);
                s = ConcatStringList::delStrList.totalRefCountsString();
            }
            else if (line == "CheckMemoryLeaks")
            {
                break;
            }
            else
            {
                string key, variable, instruction;
                int space_index = line.find(' ');
                key = line.substr(0, space_index);
                if (key == "toString")
                {
                    getline(out, res_line);
                    variable = line.substr(space_index + 1);
                    int index = stoi(variable);
                    //myAssert((index >= 0 && index < 100), "Index is out of bound!");
                    if (CSLVector[index] != nullptr)
                    {
                        s = CSLVector[index]->toString();
                    }
                }
                else if (key == "length")
                {
                    getline(out, res_line);
                    variable = line.substr(space_index + 1);
                    if (variable == "refList")
                    {
                        s = to_string(ConcatStringList::refList.size());
                    }
                    else if (variable == "delStrList")
                    {
                        s = to_string(ConcatStringList::delStrList.size());
                    }
                    else
                    {
                        int index = stoi(variable);
                        //myAssert((index >= 0 && index < 100), "Index is out of bound!");
                        if (CSLVector[index] != nullptr)
                        {
                            s = to_string(CSLVector[index]->length());
                        }
                    }
                }
                else if (key == "refCountAt")
                {
                    getline(out, res_line);
                    variable = line.substr(space_index + 1);
                    int idx = stoi(variable);
                    try
                    {
                        s = to_string(ConcatStringList::refList.refCountAt(idx));
                    }
                    catch (exception& e)
                    {
                        s = string(e.what());
                    }
                }
                else if (key == "get")
                {
                    getline(out, res_line);
                    int space_index2 = line.find(' ', space_index + 1);
                    variable = line.substr(space_index + 1, space_index2 - space_index - 1);
                    instruction = line.substr(space_index2 + 1);
                    int index = stoi(variable);
                    int idx = stoi(instruction);
                    //myAssert((index >= 0 && index < 100), "Index is out of bound!");
                    if (CSLVector[index] != nullptr)
                    {
                        try
                        {
                            s += CSLVector[index]->get(idx);
                        }
                        catch (exception& e)
                        {
                            s = string(e.what());
                        }
                    }
                }
                else if (key == "indexOf")
                {
                    getline(out, res_line);
                    int space_index2 = line.find(' ', space_index + 1);
                    variable = line.substr(space_index + 1, space_index2 - space_index - 1);
                    instruction = line.substr(space_index2 + 1);
                    int index = stoi(variable);
                    myAssert((index >= 0 && index < 100), "Index is out of bound!");
                    if (CSLVector[index] != nullptr)
                    {
                        s = to_string(CSLVector[index]->indexOf(instruction[0]));
                    }
                }
                else if (key == "subString")
                {
                    getline(out, res_line);
                    int space_index2 = line.find(' ', space_index + 1);
                    int space_index3 = line.find(' ', space_index2 + 1);
                    int space_index4 = line.find(' ', space_index3 + 1);
                    variable = line.substr(space_index + 1, space_index2 - space_index - 1);
                    instruction = line.substr(space_index2 + 1, space_index3 - space_index2 - 1);
                    string from = line.substr(space_index3 + 1, space_index4 - space_index3 - 1);
                    string to = line.substr(space_index4 + 1);
                    int index1 = stoi(variable);
                    int index2 = stoi(instruction);
//                    myAssert((index1 >= 0 && index1 < 100), "Index is out of bound!");
//                    myAssert((index2 >= 0 && index2 < 100), "Index is out of bound!");
//                    myAssert(CSLVector[index1] == nullptr, "Cannot overwrite the object!");
                    if (CSLVector[index2] != nullptr)
                    {
                        try
                        {
                            CSLVector[index1] = new ConcatStringList(CSLVector[index2]->subString(stoi(from), stoi(to)));
                            s = (CSLVector[index1] == nullptr ? "Failed to allocate memory" : "Success");
                        }
                        catch (exception& e)
                        {
                            s = string(e.what());
                        }
                    }
                }
                else if (key == "reverse")
                {
                    getline(out, res_line);
                    int space_index2 = line.find(' ', space_index + 1);
                    variable = line.substr(space_index + 1, space_index2 - space_index - 1);
                    instruction = line.substr(space_index2 + 1);
                    int index1 = stoi(variable);
                    int index2 = stoi(instruction);
//                    myAssert((index1 >= 0 && index1 < 100), "Index is out of bound!");
//                    myAssert((index2 >= 0 && index2 < 100), "Index is out of bound!");
//                    myAssert(CSLVector[index1] == nullptr, "Cannot overwrite the object!");
                    if (CSLVector[index2] != nullptr)
                    {
                        CSLVector[index1] = new ConcatStringList(CSLVector[index2]->reverse());
                        s = (CSLVector[index1] == nullptr ? "Failed to allocate memory" : "Success");
                    }
                }
                else if (key == "single_concat")
                {
                    getline(out, res_line);
                    string safe_object;
                    int space_index2 = line.find(' ', space_index + 1);
                    int space_index3 = line.find(' ', space_index2 + 1);
                    variable = line.substr(space_index + 1, space_index2 - space_index - 1);
                    instruction = line.substr(space_index2 + 1, space_index3 - space_index2 - 1);
                    safe_object = line.substr(space_index3 + 1);
                    myAssert(instruction != safe_object, "An object cannot appear twice in function concat() !");
                    int index1 = stoi(variable);
                    int index2 = stoi(instruction);
                    int index3 = stoi(safe_object);
//                    myAssert((index1 >= 0 && index1 < 100), "Index is out of bound!");
//                    myAssert((index2 >= 0 && index2 < 100), "Index is out of bound!");
//                    myAssert((index3 >= 0 && index3 < 100), "Index is out of bound!");
//                    myAssert((CSLVector[index2] != nullptr) || (CSLVector[index3] != nullptr), "Object is not initialize!");
//                    myAssert((variable != safe_object) || (variable != instruction), "Memory will be leaked!");
//                    myAssert(CSLVector[index1] == nullptr, "Cannot overwrite the object!");
                    CSLVector[index1] = new ConcatStringList(CSLVector[index2]->concat(*CSLVector[index3]));
                    s = (CSLVector[index1] == nullptr ? "Failed to allocate memory" : "Success");
                }
                else if (key == "init")
                {
                    getline(out, res_line);
                    int space_index2 = line.find(' ', space_index + 1);
                    variable = line.substr(space_index + 1, space_index2 - space_index - 1);
                    instruction = line.substr(space_index2 + 1);
                    int index1 = stoi(variable);
                    //myAssert((index1 >= 0 && index1 < 100), "Index is out of bound!");
                    //myAssert(CSLVector[index1] == nullptr, "Cannot overwrite the object!");
                    if (instruction == "\"empty_string\"")
                    {
                        CSLVector[index1] = new ConcatStringList("");
                    }
                    else
                    {
                        CSLVector[index1] = new ConcatStringList(instruction.c_str());
                    }
                    s = (CSLVector[index1] == nullptr ? "Failed to allocate memory!" : "Success");
                }
                else if (key == "delete")
                {
                    variable = line.substr(space_index + 1);
                    int index1 = stoi(variable);
                    delete CSLVector[index1];
                    CSLVector[index1] = nullptr;
                }
                else
                {
                    cout << "Invalid instruction: " + line;
                    break;
                }
            }
            //myAssert(s == res_line, "Wrong answer! Expected " + res_line + ", got " + s);
            if(s != res_line)
			{
				check=false;
            	cout<<"Wrong answer!\n";
            	break;
			}
        }
        if(check) cout << "Correct!\n";
    }
    _CrtMemCheckpoint(&s2);
    if (_CrtMemDifference(&s3, &s1, &s2))
    {
        _CrtMemDumpStatistics(&s3);
    }
	system("pause");
}
