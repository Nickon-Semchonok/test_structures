#include <iostream>
#include "queue.h"
#include "array.h"

int main() {
    std::cout << "=== Test Task 1: Queue ===" << std::endl;
    Queue<int> q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    std::cout << "Dequeued element: " << q.dequeue() << std::endl; 
    std::cout << "Front element: " << q.front() << std::endl;     

    std::cout << "\n=== Test Task 2: DoublyLinkedList Operators & Clone ===" << std::endl;
    DoublyLinkedList<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);

    DoublyLinkedList<int> list2;
    list2.push_back(2);
    list2.push_back(3);
    list2.push_back(4);

    DNode<int>* cloned = list1.clone();
    std::cout << "Cloned list1: ";
    list1.printList(cloned);

    DNode<int>* sumList = list1 + list2;
    std::cout << "list1 + list2: ";
    list1.printList(sumList);

    DNode<int>* commonList = list1 * list2;
    std::cout << "list1 * list2 (common): ";
    list1.printList(commonList);

    auto freeListNodes = [](DNode<int>* head) {
        while (head != nullptr) {
            DNode<int>* next = head->next;
            delete head;
            head = next;
        }
        };
    freeListNodes(cloned);
    freeListNodes(sumList);
    freeListNodes(commonList);

    std::cout << "\n=== Test Task 3: Array Container ===" << std::endl;
    Array<int> arr;
    arr.SetSize(3, 2); 

    arr.SetAt(0, 100);
    arr.SetAt(1, 200);
    arr.SetAt(2, 300);

    std::cout << "Array Size (GetSize): " << arr.GetSize() << std::endl;
    std::cout << "Upper Bound (GetUpperBound): " << arr.GetUpperBound() << std::endl;
    std::cout << "Element at index 1 (GetAt): " << arr.GetAt(1) << std::endl;

    arr.Add(400);
    std::cout << "After Add(400) Size: " << arr.GetSize() << std::endl;
    std::cout << "Element at index 3 using operator[]: " << arr[3] << std::endl;

    arr.InsertAt(1, 150);
    std::cout << "After InsertAt(1, 150), element at index 1: " << arr[1] << std::endl;

    arr.RemoveAt(2);
    std::cout << "After RemoveAt(2), element at index 2: " << arr[2] << std::endl;

    std::cout << "\nAll tests completed successfully!" << std::endl;
    return 0;
}