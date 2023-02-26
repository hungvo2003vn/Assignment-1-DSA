#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h> // This library is only available in MSVC++ 
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

class CharALNode
{
private:
    string s;
    CharALNode* next;
    int numOfRef;
    friend class ConcatStringList;
public:
    CharALNode(const char* s = "", int numOfRef = 0) : s(string(s)), next(nullptr), numOfRef(numOfRef) {}
    ~CharALNode()
    {

    }
};

class ConcatStringList {
public:
    class ReferencesList; // forward declaration
    class DeleteStringList; // forward declaration
public:
    static ReferencesList refList;
    static DeleteStringList delStrList;
protected:
    CharALNode* head, * tail;
    bool isSameNode;
    int len;
public:
    ConcatStringList();
    ConcatStringList(const char* s);
    int length() const;
    char get(int index) const;
    int indexOf(char c) const;
    std::string toString() const;
    ConcatStringList concat(const ConcatStringList& otherS) const;
    ConcatStringList subString(int from, int to) const;
    ConcatStringList reverse() const;
    bool isEmptyList() { return this->head == nullptr; }
    ~ConcatStringList();

public:
    class ReferencesList {
    public:
        class RNode;
    protected:
        RNode* head, * tail;
        int len;
        friend class ConcatStringList;
        friend class DeleteStringList;
    public:
        ReferencesList()
        {
            head = nullptr;
            tail = nullptr;
            len = 0;
        }
        ~ReferencesList()
        {
            while (this->head != nullptr)
            {
                RNode* q = this->head;
                head = head->next;
                if (this->head == nullptr)
                {
                    this->tail = nullptr;
                }
                q->next = nullptr;
                delete q;
                q = nullptr;
                len--;
            }
        }
    public:
        void add(CharALNode* h);
        int size() const;
        int refCountAt(int index) const;
        std::string refCountsString() const;
        void swap(RNode* a, RNode* b)
        {
            CharALNode* ptr = a->p;
            a->p = b->p;
            b->p = ptr;
            int num = a->numOfRef;
            a->numOfRef = b->numOfRef;
            b->numOfRef = num;
        }
        void sort();
    public:
        class RNode
        {
        private:
            CharALNode* p;
            RNode* next;
            int numOfRef;
            friend class ReferencesList;
            friend class ConcatStringList;
        public:
            RNode() : p(nullptr), next(nullptr), numOfRef(0) {}
            RNode(CharALNode* p) : p(p), next(nullptr), numOfRef(0) {}
            ~RNode()
            {

            }
        };
    };

    class DeleteStringList {
    public:
        class DNode;
    protected:
        DNode* head, * tail;
        int len;
        friend class ConcatStringList;
    public:
        DeleteStringList() : head(nullptr), tail(nullptr), len(0) {}
        ~DeleteStringList()
        {
            while (head)
            {
                DNode* p = head;
                head = head->next;
                if (!head)
                {
                    tail = nullptr;
                }
                delete p;
            }
        }
    public:
        void addLast(CharALNode* h, CharALNode* t, bool isSameNode, int numHead, int numTail);
        int size() const;
        std::string totalRefCountsString() const;
    public:
        class DNode
        {
        private:
            CharALNode* head, * tail;
            bool isSameNode;
            int numHeadRef, numTailRef;
            DNode* next;
            friend class DeleteStringList;
            friend class ConcatStringList;
        public:
            DNode(CharALNode* head = nullptr, CharALNode* tail = nullptr, bool isSameNode = true, int numHead = 0, int numTail = 0)
            {
                this->head = head;
                this->tail = tail;
                this->isSameNode = isSameNode;
                this->next = nullptr;
                this->numHeadRef = numHead;
                this->numTailRef = numTail;
            }
            ~DNode()
            {

            }
        };
    };
};

ConcatStringList::ReferencesList ConcatStringList::refList = ConcatStringList::ReferencesList();
ConcatStringList::DeleteStringList ConcatStringList::delStrList = ConcatStringList::DeleteStringList();

ConcatStringList::ConcatStringList()
{
    this->head = this->tail = nullptr;
    this->len = 0;
    this->isSameNode = false;
}

ConcatStringList::ConcatStringList(const char* s)
{
    this->head = this->tail = new CharALNode(s, 1);
    this->len = (int)head->s.length();
    isSameNode = true;
    refList.add(this->head);
    refList.add(this->tail);
}

ConcatStringList ConcatStringList::concat(const ConcatStringList& otherS) const
{
    union S
    {
        ConcatStringList newList;
        S()
        {
            newList = ConcatStringList();
        }
        ~S()
        {

        }
    } str;
    this->tail->next = otherS.head;
    str.newList = *this;
    str.newList.tail = otherS.tail;
    str.newList.isSameNode = (str.newList.head == str.newList.tail ? true : false);
    str.newList.len = this->len + otherS.len;
    str.newList.head->numOfRef = 1;
    str.newList.tail->numOfRef = 1;
    refList.add(str.newList.head);
    refList.add(str.newList.tail);
    return str.newList;
}

int ConcatStringList::length() const
{
    return this->len;
}

char ConcatStringList::get(int index) const
{
    if (index >= this->length() || index < 0)
    {
        throw out_of_range("Index of string is invalid!");
    }
    CharALNode* p = head;
    while (index >= (int)p->s.length())
    {
        index -= (int)p->s.length();
        p = p->next;
    }
    return p->s[index];
}

int ConcatStringList::indexOf(char c) const
{
    CharALNode* p = head;
    int index = 0;
    int sum_length = 0;
    while (p != nullptr)
    {
        for (int i = 0; i < (int)p->s.length(); i++)
        {
            if (p->s[i] == c)
            {
                index = sum_length + i;
                return index;
            }
        }
        sum_length += (int)p->s.length();
        p = p->next;
    }
    return -1;
}

string ConcatStringList::toString() const
{
    string ans = "";
    CharALNode* p = head;
    while (p != tail)
    {
        ans += p->s;
        p = p->next;
    }
    ans += p->s;
    return ans;
}

ConcatStringList ConcatStringList::subString(int from, int to) const
{
    if (from >= to)
    {
        throw logic_error("Invalid range");
    }
    if (from < 0 || from >= this->length() || to < 0 || to >= this->length() + 1)
    {
        throw out_of_range("Index of string is invalid");
    }
    int length_string = to - from;
    CharALNode* p = head;
    while (from >= (int)p->s.length())
    {
        from -= (int)p->s.length();
        p = p->next;
    }
    string s = "";
    while (from < min(length_string, (int)p->s.length()))
    {
        s += get(from);
        from++;
    }
    union S
    {
        ConcatStringList newList;
        S()
        {
            newList = ConcatStringList();
        }
        ~S()
        {

        }
    } str;
    str.newList.head = str.newList.tail = new CharALNode(s.c_str());
    CharALNode* tmp = nullptr;
    p = p->next;
    if (p != nullptr)
    {
        while (from + (int)p->s.length() < length_string)
        {
            s = p->s;
            tmp = new CharALNode(s.c_str());
            str.newList.tail->next = tmp;
            str.newList.tail = tmp;
            from += (int)p->s.length();
            p = p->next;
        }
        s = "";
        while (from < to)
        {
            s += get(from);
            from++;
        }
        if (s != "")
        {
            tmp = new CharALNode(s.c_str());
            str.newList.tail->next = tmp;
            str.newList.tail = tmp;
        }
    }
    str.newList.len = length_string;
    str.newList.isSameNode = (str.newList.head == str.newList.tail ? true : false);
    str.newList.head->numOfRef = 1;
    str.newList.tail->numOfRef = 1;
    refList.add(str.newList.head);
    refList.add(str.newList.tail);
    return str.newList;
}

ConcatStringList ConcatStringList::reverse() const
{
    union S
    {
        ConcatStringList newList;
        S()
        {
            newList = ConcatStringList();
        }
        ~S()
        {

        }
    } str;
    CharALNode* p = head;
    while (p != nullptr)
    {
        string s = p->s;
        int i = 0, j = (int)s.length() - 1;
        while (i < j)
        {
            char c = s[i];
            s[i] = s[j];
            s[j] = c;
            i++;
            j--;
        }
        CharALNode* tmp = new CharALNode(s.c_str());
        if (str.newList.head == nullptr)
        {
            str.newList.head = str.newList.tail = tmp;
        }
        else
        {
            tmp->next = str.newList.head;
            str.newList.head = tmp;
        }
        p = p->next;
    }
    str.newList.len = this->length();
    str.newList.isSameNode = (str.newList.head == str.newList.tail ? true : false);
    str.newList.head->numOfRef = 1;
    str.newList.tail->numOfRef = 1;
    refList.add(str.newList.head);
    refList.add(str.newList.tail);
    return str.newList;
}

int ConcatStringList::ReferencesList::size() const
{
    return this->len;
}

ConcatStringList::~ConcatStringList()
{
    ReferencesList::RNode* p = refList.head, * q = refList.head;
    int s1 = 0, s2 = 0;
    while (p != nullptr)
    {
        if (p->p == this->head)
        {
            p->numOfRef -= (p->numOfRef == 0 ? 0 : 1);
            s1 = p->numOfRef;
            break;
        }
        p = p->next;
    }
    while (q != nullptr)
    {
        if (q->p == this->tail)
        {
            q->numOfRef -= (q->numOfRef == 0 ? 0 : 1);
            s2 = q->numOfRef;
            break;
        }
        q = q->next;
    }
    delStrList.addLast(this->head, this->tail, this->isSameNode, (this->isSameNode == true ? s2 : s1), s2);
    refList.sort();
    DeleteStringList::DNode* q1 = delStrList.head;
    ReferencesList::RNode* pHead = refList.head;
    while (pHead != nullptr)
    {
        if (pHead->numOfRef == 0)
        {
            while (q1 != nullptr)
            {
                if (q1->head == pHead->p)
                {
                    q1->numHeadRef = 0;
                }
                if (q1->tail == pHead->p)
                {
                    q1->numTailRef = 0;
                }
                q1 = q1->next;
            }
        }
        pHead = pHead->next;
    }
    ReferencesList::RNode* pHead1 = refList.head;
    while (pHead1 != nullptr)
    {
        if (pHead1->numOfRef == 0)
        {
            if (pHead1 == refList.head)
            {
                DeleteStringList::DNode* d1 = delStrList.head, * d2 = nullptr;
                while (d1 != nullptr)
                {
                    while (d1->head != nullptr)
                    {
                        CharALNode* c1 = d1->head;
                        ReferencesList::RNode* pHead2 = refList.head;
                        while (pHead2 != nullptr)
                        {
                            if (pHead2->p == c1)
                            {
                                break;
                            }
                            pHead2 = pHead2->next;
                        }
                        d1->head = d1->head->next;
                        if (d1->head == nullptr)
                        {
                            d1->tail = nullptr;
                        }
                        d2 = delStrList.head;
                        while (d2 != nullptr)
                        {
                            CharALNode* c2 = d2->head, * pre_c2 = nullptr;
                            while (c2 != nullptr)
                            {
                                if (c2 == c1)
                                {
                                    break;
                                }
                                pre_c2 = c2;
                                c2 = c2->next;
                            }
                            if (c2 != nullptr)
                            {
                                if (pre_c2 == nullptr)
                                {
                                    d2->head = d2->head->next;
                                    if (d2->head == nullptr)
                                    {
                                        d2->tail = nullptr;
                                    }
                                    c1->next = nullptr;
                                }
                                else
                                {
                                    pre_c2->next = c2->next;
                                    c1->next = nullptr;
                                }
                            }
                            d2 = d2->next;
                        }
                        delete c1;
                        c1 = nullptr;
                        if (pHead2 != nullptr)
                        {
                            pHead2->p = nullptr;
                        }
                    }
                    d1 = d1->next;
                }
                while (delStrList.head != nullptr)
                {
                    DeleteStringList::DNode* dptr = delStrList.head;
                    delStrList.head = delStrList.head->next;
                    if (delStrList.head == nullptr)
                    {
                        delStrList.tail = nullptr;
                    }
                    dptr->next = nullptr;
                    delete dptr;
                    dptr = nullptr;
                    delStrList.len--;
                }
                refList.~ReferencesList();
                break;
            }
        }
        pHead1 = pHead1->next;
    }
}

void ConcatStringList::ReferencesList::add(CharALNode* h)
{
    RNode* tmp = nullptr;
    bool inc_len = true;
    if (head == nullptr)
    {
        head = tail = new RNode(h);
        head->numOfRef = tail->numOfRef = h->numOfRef;
    }
    else
    {
        RNode* p = head;
        while (p != nullptr)
        {
            if (p->p == h)
            {
                inc_len = false;
                break;
            }
            p = p->next;
        }
        if (p == nullptr)
        {
            tmp = new RNode(h);
            tmp->next = this->head;
            this->head = tmp;
            this->head->numOfRef = tmp->numOfRef;
        }
        else
        {
            p->numOfRef += h->numOfRef;
        }
    }
    len += (inc_len == true ? 1 : 0);
    sort();
}

void ConcatStringList::ReferencesList::sort()
{
    if (head == nullptr)
    {
        return;
    }
    RNode* ptr1 = nullptr;
    int i = 0;
    do
    {
        ptr1 = head;
        while (ptr1->next != nullptr)
        {
            if (ptr1->numOfRef > ptr1->next->numOfRef)
            {
                swap(ptr1, ptr1->next);
            }
            ptr1 = ptr1->next;
        }
        i++;
    } while (i < this->size());
    if (tail->numOfRef == 0)
    {
        return;
    }
    while (head != nullptr)
    {
        if (head->numOfRef != 0)
        {
            break;
        }
        RNode* tmp = head;
        head = head->next;
        tmp->next = nullptr;
        this->tail->next = tmp;
        this->tail = tmp;
    }
}

int ConcatStringList::ReferencesList::refCountAt(int index) const
{
    if (index < 0)
    {
        throw out_of_range("Index of references list is invalid!");
    }
    else
    {
        int i = 0;
        RNode* p = head;
        while (p != nullptr)
        {
            if (i == index)
            {
                break;
            }
            i++;
            p = p->next;
        }
        if (p == nullptr)
        {
            throw out_of_range("Index of references list is invalid!");
        }
        return p->numOfRef;
    }
}

std::string ConcatStringList::ReferencesList::refCountsString() const
{
    string s = "RefCounts[";
    RNode* p = head;
    while (p != nullptr)
    {
        s += to_string(p->numOfRef);
        s += (p->next == nullptr ? "" : ",");
        p = p->next;
    }
    s += "]";
    return s;
}

void ConcatStringList::DeleteStringList::addLast(CharALNode* h, CharALNode* t, bool isSameNode, int numHead, int numTail)
{
    DNode* tmp = new DNode(h, t, isSameNode, numHead, numTail);
    if (head == nullptr)
    {
        head = tail = tmp;
    }
    else
    {
        DNode* temp = head;
        while (temp != nullptr)
        {
            if (tmp->numHeadRef == 0)
            {
                if (tmp->head == temp->head)
                {
                    temp->numHeadRef = 0;
                    temp->numTailRef = (temp->isSameNode == true ? 0 : temp->numTailRef);
                }
            }
            if (tmp->numTailRef == 0)
            {
                if (tmp->tail == temp->tail)
                {
                    temp->numHeadRef = (temp->isSameNode == true ? 0 : temp->numHeadRef);
                    temp->numTailRef = 0;
                }
            }
            temp = temp->next;
        }
        this->tail->next = tmp;
        this->tail = tmp;
    }
    int real_length = 0;
    DNode* x = this->head;
    while (x != nullptr)
    {
        if (x->numHeadRef + x->numTailRef != 0)
        {
            real_length++;
        }
        x = x->next;
    }
    this->len = real_length;
}

int ConcatStringList::DeleteStringList::size() const
{
    return this->len;
}

std::string ConcatStringList::DeleteStringList::totalRefCountsString() const
{
    string s = "TotalRefCounts[";
    DNode* p = head;
    int sumRef = 0;
    while (p != nullptr)
    {
        sumRef = (p->isSameNode == true ? p->numHeadRef : p->numHeadRef + p->numTailRef);
        if (sumRef != 0)
        {
            s += (to_string(sumRef) + ",");
        }
        p = p->next;
    }
    s += "]";
    for (int i = 0; i < (int)s.length(); i++)
    {
        if (s[i] == ',' && s[i + 1] == ']')
        {
            s.erase(s.begin() + i);
            i--;
        }
    }
    return s;
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
    string key, variable, instruction;
    do
    {
        cin >> key;
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
            _CrtDumpMemoryLeaks();
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

