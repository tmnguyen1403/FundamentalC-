/*
* Pre-travel to count the length of linked list
* To know where to stop
* two pointers, fast travel
* when the fast pointer is at the end, we know the slow pointer is in the middle
* since we only take n/2 time to travel to middle
* and take another n/2 time for the slow to travel to the end
1 2 
slow = 1
fast = null
then slow need to move up 1
1 2 2 1
t = 1
slow = 1
fast = 2
t = 2
slow = 2
fast = 1
fast = null
if (fast == null) at the second step, meaning we have 2*t element
 then slow need to move up one step
if (frst == null) at the first step, meaning we have 2*t - 1 element
 then slow can stay at where it is

We know then travel step by step to the end
*/
#include <iostream>
 struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(nullptr) {}
      ~ListNode() {
        // std::cout << "Destroying node with val: " << val << "\n";
        // std::cout << "Destroying node with address: " << this << "\n";
      
        if (next != nullptr)
            delete next;
        next = nullptr;
       // std::cout << "Destroyed node with address: " << this << "\n";
      }
};

class Solution {
public:
    bool isPalindrome(ListNode* head) const {
        if (head == nullptr || head->next == nullptr)
            return true;
        //dummy head technique might be easier for this 
        auto slow = head;
        auto fast = head->next->next;
        //Relink here to cover the case with only 2 nodes that cause the loop never be accessed
        ListNode* next_pos = slow->next;
        ListNode* prev = nullptr;
        slow->next = prev;
        prev = slow;
        auto mid_left = slow;
        auto mid_right = next_pos;
        while (fast != nullptr)
        {
            //relink while traversing the linkedlist
            //This is important to remember, messing up the order can cause the whole thing to fail through
            slow = next_pos;
            next_pos = slow->next;
            slow->next = prev;
            prev = slow; 

            fast = fast->next;
            if (fast != nullptr) {
                fast = fast->next;
                mid_left = slow;
                mid_right = next_pos;
            } else {
                mid_left = slow->next;
                mid_right = next_pos;
            }
        }
        
        bool palindrome = true; //Since we want to relink the linked list, we don't want to return early, so using this variable to store the result
        prev = mid_right;
        while (mid_left != nullptr && mid_right != nullptr) {
            if (mid_left->val != mid_right->val)
                palindrome = false;
            //relink the left nodes while traversing
            next_pos = mid_left->next;
            mid_left->next = prev;
            prev = mid_left;
            mid_left = next_pos;
            mid_right = mid_right->next;
        }
        return palindrome;
    }
    bool operator()(ListNode *head) const {return isPalindrome(head);}
};

template <typename FunctionT>
void test(ListNode* input, bool expect, const FunctionT& f, std::string_view message)
{
    std::cout << message << std::endl;
    auto result = f(input);
    std::cout << "expect: " << expect << std::endl;
    std::cout << "result: " << result << std::endl;
    assert(result == expect && "Result is not equal to expect");
}

int main()
{
    Solution so; 
    {
        ListNode head{1};
        test(&head, true, so, "Test 1 - Expect true");
    }

    {
        ListNode head{1};
        head.next = new ListNode(1);
        test(&head, true, so, "Test 2 - Expect true");
    }

    {
        ListNode head{1};
        head.next = new ListNode(2);
        test(&head, false, so, "Test 3 - Expect false");
    }

    {
        ListNode head{1};
        head.next = new ListNode(2);
        head.next->next = new ListNode(1);

        test(&head, true, so, "\nTest 3 - Expect true\n");
    }

    {
        ListNode head{1};
        head.next = new ListNode(0);
        head.next->next = new ListNode(0);

        test(&head, false, so, "\nTest 3.1 - Expect false\n");
    }

    {
        ListNode head{1};
        head.next = new ListNode(2);
        head.next->next = new ListNode(2);
        head.next->next->next = new ListNode(1);

        test(&head, true, so, "\nTest 4 - Expect true\n");
        head.next->next->next->val = 10;
        test(&head, false, so, "\nTest 5 - Expect true\n");

    }
    return 0;
}
