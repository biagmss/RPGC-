class Stack {
    public:
        Stack();
        ~Stack();
        bool Empty();
        void Push(int x);
        void Pop(int &x);
        int Size();
        void Clear();
        void Top(int &x);
    private:
        struct StackNode {
            int Entry;
            StackNode *NextNode;
        };
        typedef StackNode *StackPointer;
        StackPointer top;
};
