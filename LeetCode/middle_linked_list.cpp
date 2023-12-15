#include <iostream>
 struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(nullptr) {}
      ~ListNode() {
        std::cout << "Destroying node with val: " << val << "\n";
        std::cout << "Destroying node with address: " << this << "\n";
      
        if (next != nullptr)
            delete next;
        next = nullptr;
        std::cout << "Destroyed node with address: " << this << "\n";
      }
};

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
        auto slow = head;
        auto fast = head->next->next;
        /*
        If fast is null at the while loop condition, it means that we have 2n numbers in the list.
        So, slow pointer will be at the nth number, and we want to return (n+1)th number instead
        Otherwise, we will return the nth number in the while loop when we fast pointer at the end of the list
        */
        while (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
            if (fast == nullptr)
                return slow;
            else
                fast = fast->next;
        }
        return slow->next;
    }
};

int main()
{
    {
        //Input: 1,2,3,4,5
        //Result [3]
    }

    {
        //Input: 1,2,3,4,5,6
        //Result [4]
    }
}