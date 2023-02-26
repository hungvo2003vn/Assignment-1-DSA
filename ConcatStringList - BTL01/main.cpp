#include "ConcatStringList.h"

void tc1()
{
	cout<<"-----------------TEST 1st--------------------\n";
    ConcatStringList s1("Hello,_world");
    // test length
    cout << "s1's length: " << s1.length() << endl;
    // test get
    cout << "char at index 2: " << s1.get(2) << endl;
    try
    {
        cout << "char at index 22: " << s1.get(22) << endl;
    }
    catch (out_of_range& ofr)
    {
        cout << "Exception out_of_range: " << ofr.what() << endl;
    }
    // test indexOf
    cout << "in s1, index of 'o': " << s1.indexOf('o') << endl;
    cout << "in s1, index of 'a': " << s1.indexOf('a') << endl;
    // test toString
    cout << "s1 toString: " << s1.toString() << endl;
}

void tc2()
{
	cout<<"-----------------TEST 2nd--------------------\n";
    ConcatStringList s1("Hello,");
    ConcatStringList s2("_this_is");
    ConcatStringList s3("_an_assignment");

    // s3->s2->s1
    // test concat
    ConcatStringList s4 = s1.concat(s2);
    cout << "s4: " << s4.toString() << endl;

    //// test subString
    ConcatStringList s6 = s4.subString(3,14);
    cout << "s6: " << s6.toString() <<"."<< endl;

    //// test reverse
    ConcatStringList s7 = s4.reverse();
    cout << "s7: " << s7.toString() << endl;
}

void tc3() {
	cout<<"-----------------TEST 3rd--------------------\n";
    ConcatStringList * s1 = new ConcatStringList("Hello");
    ConcatStringList * s2 = new ConcatStringList("_world");
    ConcatStringList * s3 = new ConcatStringList(s1->concat(*s2));
    ConcatStringList * s4 = new ConcatStringList(s3->reverse());
    
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    
	cout << "---After deleting s4---" << endl;
    delete s4;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    
    cout << "---After deleting s1---" << endl;
    delete s1;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    cout << "---After deleting s3---" << endl;
    delete s3;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    cout << "---After deleting s2---" << endl;
    delete s2;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    
}
void tc4() {
	cout<<"-----------------TEST 4th--------------------\n";
    ConcatStringList* s1 = new ConcatStringList("Hello");                            // SPECIAL TEST CASE
    cout << "refSize:" << ConcatStringList::refList.size() << endl; //1
    ConcatStringList* s2 = new ConcatStringList("_world");
    cout << "refSize:" << ConcatStringList::refList.size() << endl; // 2
    ConcatStringList* s3 = new ConcatStringList("LOL");
    cout << "refSize:" << ConcatStringList::refList.size() << endl; // 3
    ConcatStringList* s4 = new ConcatStringList("HOHO");
    cout << "refSize:" << ConcatStringList::refList.size() << endl; // 4
    ConcatStringList* s5 = new ConcatStringList(s1->concat(*s2));
    cout << "refSize:" << ConcatStringList::refList.size() << endl; // 4
    ConcatStringList* s6 = new ConcatStringList(s5->reverse());
    cout << "refSize:" << ConcatStringList::refList.size() << endl; // 6
    ConcatStringList* s7 = new ConcatStringList(s6->concat(*s3));
    cout << "refSize:" << ConcatStringList::refList.size() << endl; // 6
    ConcatStringList* s8 = new ConcatStringList(s7->subString(1, 14));
    cout << "refSize:" << ConcatStringList::refList.size() << endl; // 8
    ConcatStringList* s9 = new ConcatStringList(s8->concat(*s4));
    cout << "refSize:" << ConcatStringList::refList.size() << endl;  // 8
    cout << endl;
    cout << "--------SPECIAL--------" << endl;
    cout << "s1: " << s1->toString() << endl;
    cout << "s2: " << s2->toString() << endl;
    cout << "s3: " << s3->toString() << endl;
    cout << "s4: " << s4->toString() << endl;
    cout << "s5: " << s5->toString() << endl;
    cout << "s6: " << s6->toString() << endl;
    cout << "s7: " << s7->toString() << endl;
    cout << "s8: " << s8->toString() << endl;
    cout << "s9: " << s9->toString() << endl;
    cout << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << "size of DelStrList: " << ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s1;
    cout << "--------After deleting s1--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << "size of DelStrList: " << ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s2;
    cout << "--------After deleting s2--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << "size of DelStrList: " << ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s4;
    cout << "--------After deleting s4--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << "size of DelStrList: " << ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s5;
    cout << "--------After deleting s5--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << "size of DelStrList: " << ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s6;
    cout << "--------After deleting s6--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << "size of DelStrList: " << ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s3;
    cout << "--------After deleting s3--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << "size of DelStrList: " << ConcatStringList::delStrList.size() << endl;
    delete s7;
    cout << "--------After deleting s7--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << "size of DelStrList: " << ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s9;
    cout << "--------After deleting s9--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << "size of DelStrList: " << ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s8;
    cout << "--------After deleting s8--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << "size of DelStrList: " << ConcatStringList::delStrList.size() << endl;
    cout << endl;
}
void tc5() {
	cout<<"-----------------TEST 5th--------------------\n";
    ConcatStringList* s1 = new ConcatStringList(" mot ");
    ConcatStringList* s2 = new ConcatStringList(" hai ");
    ConcatStringList* s3 = new ConcatStringList(" ba ");
    ConcatStringList* s4 = new ConcatStringList(" bon ");
    ConcatStringList* s5 = new ConcatStringList(" nam ");
    ConcatStringList* s6 = new ConcatStringList((s1->concat(*s2)).reverse());
    ConcatStringList* s7 = new ConcatStringList((s3->concat(*s4)).subString(0, 7)); 
    ConcatStringList* s8 = new ConcatStringList(s7->concat(s5->reverse()));
    ConcatStringList* s9 = new ConcatStringList(s6->concat(s8->subString(0, s8->length())));
    cout << "s1: " << s1->toString() << endl;
    cout << "s2: " << s2->toString() << endl;
    cout << "s3: " << s3->toString() << endl;
    cout << "s4: " << s4->toString() << endl;
    cout << "s5: " << s5->toString() << endl;
    cout << "s6: " << s6->toString() << endl;
    cout << "s7: " << s7->toString() << endl;
    cout << "s8: " << s8->toString() << endl;
    cout << "s9: " << s9->toString() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << "size of DelStrList: " << ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s1;
    cout << "--------After deleting s1--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << "size of DelStrList: " << ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s2;
    cout << "--------After deleting s2--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << "size of DelStrList: " << ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s4;
    cout << "--------After deleting s4--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << "size of DelStrList: " << ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s5;
    cout << "--------After deleting s5--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << "size of DelStrList: " << ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s6;
    cout << "--------After deleting s6--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << "size of DelStrList: " << ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s3;
    cout << "--------After deleting s3--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << "size of DelStrList: " << ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s7;
    cout << "--------After deleting s7--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << "size of DelStrList: " << ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s9;
    cout << "--------After deleting s9--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout << "size of DelStrList: " << ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s8;
    cout << "--------After deleting s8--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[]
    cout << "size of refList: " << ConcatStringList::refList.size() << endl;
    cout << "size of DelStrList: " << ConcatStringList::delStrList.size() << endl;
    cout << endl;
}
void tc6()
{
	cout<<"-----------------TEST 6th--------------------\n";
    ConcatStringList s1("Qp04");
    ConcatStringList s2("m");
    ConcatStringList s21 = s2.concat(s1);
    cout << "s11: " << s21.toString() << endl;
    ConcatStringList s32 = s21.subString(0, 5);
    cout << "s32: " << s32.toString() <<"."<< endl;
}
void tc7() {
	cout<<"-----------------TEST 7th--------------------\n";
    ConcatStringList* s0 = new ConcatStringList("XYZ");
    cout << "s0: " << s0->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size()<<endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    ConcatStringList* s1 = new ConcatStringList("ABC");
    cout << "s1: " << s1->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    ConcatStringList* s2 = new ConcatStringList("DEF");
    cout << "s2: " << s2->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    ConcatStringList* s3 = new ConcatStringList("GHI");
    cout << "s3: " << s3->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    ConcatStringList* s4 = new ConcatStringList(s1->concat(*s2));
    cout << "s4: " << s4->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    ConcatStringList* s5 = new ConcatStringList(s4->reverse().concat(*s3));
    cout << "s5: " << s5->toString() << endl;
    cout << "length of s5: " << s5->length() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    ConcatStringList* s6 = new ConcatStringList(s5->reverse().reverse());
    cout << "s6: " << s6->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    ConcatStringList* s7 = new ConcatStringList(s5->subString(1,8));
    cout << "s7: " << s7->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    ConcatStringList* s8 = new ConcatStringList(s5->subString(1, 8).subString(1,5).subString(2,3));
    cout << "s8: " << s8->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    ConcatStringList* s9 = new ConcatStringList(s6->concat(s5->reverse().subString(4,5)).reverse());
    cout << "s9: " << s9->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 	
    cout << endl;
    ConcatStringList* s10 = new ConcatStringList(s0->reverse().concat((s0->reverse().concat(s0->reverse()).reverse())));
    cout << "s10: " << s10->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
 	cout<<endl;
 	
    cout << "---After deleting s0---" << endl;
    delete s0;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    cout << "---After deleting s1---" << endl;
    delete s1;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    cout << "---After deleting s3---" << endl;
    delete s3;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    cout << "---After deleting s2---" << endl;
    delete s2;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    cout << "---After deleting s4---" << endl;
    delete s4;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    cout << "---After deleting s5---" << endl;
    delete s5;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    cout << "---After deleting s6---" << endl;
    delete s6;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    cout << "---After deleting s7---" << endl;
    delete s7;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    cout << "---After deleting s8---" << endl;
    delete s8;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    cout << "---After deleting s9---" << endl;
    delete s9;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    cout << "---After deleting s10---" << endl;
    delete s10;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
}
void tc8() {
	cout<<"-----------------TEST 8th--------------------\n";
    ConcatStringList s1("Hello,");
    ConcatStringList s2("_this_is");
    ConcatStringList s3("_an_assignment_");
    ConcatStringList s4 = ConcatStringList(s1.concat(s2).concat(s3));
    ConcatStringList s5 = ConcatStringList(s4.subString(0,s4.length()).concat(s4));
    cout << s5.toString() << endl;
    cout << s5.length() << endl;
    ConcatStringList s6 = ConcatStringList(s5.subString(6, s5.length() - s3.length()));
    ConcatStringList s7 = ConcatStringList(s5.subString(6, s5.length() - s3.length()+1).reverse());
    cout << s6.toString() << endl;
    cout << s6.length() << endl;
    cout << s7.toString() << endl;
    cout << s7.length() << endl;
    for (int i = 0; i < s6.length(); i++) {
        cout << s6.get(i);
    }
    cout << endl;
    for (int i = 0; i < s7.length(); i++) {
        cout << s7.get(i);
    }
    cout << endl;
    for (int i = 0; i < s5.length(); i++) {
        cout << s5.get(i);
    }
    cout << endl;
    for (int i = 0; i < s7.length(); i++) {
        cout << s7.indexOf(s7.get(i))<<" ";
    }
}
int main()
{
    tc1();
    tc2();
    tc3();
    tc4();
    tc5();
    tc6();
    tc7();
    tc8();
    return 0;
}
