#include <iostream>
#include <string_view>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
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

/*
If we use two pointers method, one move with speed 1, one move with speed 2
Then eventually, if there is a cycle the fast pointer will reach the slow pointer, otherwise there is no cycle

*/
class Solution {
public:
    bool hasCycle(ListNode *head) const {
        if (head == nullptr)
            return false;
        ListNode* slowPointer = head->next;
        ListNode* fastPointer = nullptr;
        if (slowPointer != nullptr)
            fastPointer = slowPointer->next;

        while (slowPointer != fastPointer) {
            if (slowPointer == nullptr || fastPointer == nullptr)
                return false;
            slowPointer = slowPointer->next;
            fastPointer = fastPointer->next;
            if (fastPointer != nullptr)
                fastPointer = fastPointer->next;
        }
        return slowPointer != nullptr && slowPointer == fastPointer;
    }

    bool operator()(ListNode *head) const {
        return hasCycle(head);
    }
};

template <typename InT, typename ResultT, typename FunctionT>
void test(const InT& input, const ResultT& expect, const FunctionT& f, std::string_view message) {
    std::cout << "******" << message << "******" << std::endl;
    auto result = f(input);

    std::cout << "Expect: " << expect << std::endl;
    std::cout << "Result: " << result << std::endl;
    assert(expect == result && "Expect is not equal result");
}

int main() {
    Solution so;
    //ListNode head{10};
    {
        ListNode head{10};
        std::cout << "address of head: " << &head << std::endl;

        head.next = new ListNode(20);
        head.next->next = new ListNode(30);
        head.next->next->next = &head;
        test(&head, true, so, "Test 1 with cycle");
        //decycle so that resource can be freed properly
        head.next->next->next = nullptr;
    }
    std::cout << "Not calling freed yet\n";
    {
        ListNode head{5};
        head.next = new ListNode(20);
        head.next->next = new ListNode(30);
        test(&head, false, so, "Test 2 with cycle");
    }
    return 0;
}