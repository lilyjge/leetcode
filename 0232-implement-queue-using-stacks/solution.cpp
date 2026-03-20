class MyQueue {
public:
    stack<int> s;
    int top;
    MyQueue() {

    }
    
    void push(int x) {
        if (s.empty()) 
            top = x;
        s.push(x);
    }
    
    int pop() {
        stack<int> t;
        while(s.size() > 1) {
            t.push(s.top());
            s.pop();
        }
        int res = s.top();
        s.pop();
        if (!t.empty())
            top = t.top();
        while(!t.empty()) {
            s.push(t.top());
            t.pop();
        }
        return res;
    }
    
    int peek() {
        return top;
    }
    
    bool empty() {
        return s.empty();   
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
