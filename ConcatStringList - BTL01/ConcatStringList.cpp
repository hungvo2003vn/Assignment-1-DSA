#include "ConcatStringList.h"

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
	ConcatStringList *ans=new ConcatStringList;
	ans->head=head;
	ans->tail=tail;
	
	ans->tail->next=otherS.head;
	ans->tail=otherS.tail;
	
	ans->list_len=list_len+otherS.list_len;
	
	//Add to References List
    refList.addRefNode2(ans->head,1);
    refList.addRefNode2(ans->tail,1);
	return *ans;
}

ConcatStringList ConcatStringList::subString(int from, int to) const{
	if((from<0 || from>=list_len)||(to<0 || to>list_len))
		throw out_of_range("Index of string is invalid");
	else if(from>=to) 
		throw logic_error("Invalid range");
	//else
	int sum_len=0;
	ConcatStringList *ans= new ConcatStringList;
	ans->list_len=to-from;
	
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
					ans->head=start;
					ans->tail=start;
					ans->tail->next=nullptr;
					
					//Add to References List
    				refList.addRefNode2(ans->head,1);
    				refList.addRefNode2(ans->tail,1);
					return *ans;
				}
				++j;
				++i;
			}
			
			ans->head=start;
			ans->tail=start;
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
				ans->tail->next=start;
				ans->tail=start;
				break;
			}
		}	
		if(i-sum_len==tmp->len-1 && i>from)
		{	
			//control the tail
			ans->tail->next=start;
			ans->tail=start;
			
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
	
	ans->tail->next=nullptr;
	//Add to References List
    refList.addRefNode2(ans->head,1);
    refList.addRefNode2(ans->tail,1);
	
	return *ans;
}

ConcatStringList ConcatStringList::reverse() const{
	
	//Declare answer and deep copy the old object
	ConcatStringList *ans=new ConcatStringList;
	ans->list_len=list_len; //copy length
	
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
		
		if(ans->head==nullptr) ans->head=ans->tail=new_node;
		else
		{
			ans->tail->next=new_node;
			ans->tail=new_node;
		}
		travel=travel->next;
	}
	
	//Reverse Node
	CharALNode *curr=ans->head;
	CharALNode *TAIL=curr;
	CharALNode *pre=nullptr;
	CharALNode *next=nullptr;
	while(curr && curr!=ans->tail->next)
	{
		
		next=curr->next;//Store next node to move
		
		curr->next=pre;
		pre=curr;
		curr=next;

	}
	ans->head=pre;
	ans->tail=TAIL;
	ans->tail->next=nullptr;
	
	//Add to References List
    refList.addRefNode2(ans->head,1);
    refList.addRefNode2(ans->tail,1);
    
	return *ans;
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



