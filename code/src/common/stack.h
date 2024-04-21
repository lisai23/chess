#ifndef STACK_H
#define STACK_K

template<typename T>
struct node
{
    node<T> *prev = nullptr;
    T data;
    node<T> *next = nullptr;
};


template<typename T>
class stack
{
public:
    stack(/* args */);
    ~stack();

    void push(T data);
    T pop();
    T top();
    bool isEmpty();

private:
    node<T> *m_head = nullptr;
    node<T> *m_currentNode = nullptr;
};

template<typename T>
stack<T>::stack(/* args */)
{
    m_head = new node<T>;
    m_head->next = m_head;
    m_head->prev = m_head;

    m_currentNode = m_head;
}

template<typename T>
stack<T>::~stack(/* args */)
{
    for (m_currentNode = m_head->next; m_currentNode != m_head; m_currentNode = m_currentNode->next)
    {
        if (nullptr != m_currentNode)
        {
            delete m_currentNode;
        }
    }
    delete m_head;
    m_currentNode = nullptr;
    m_head = nullptr;
}

template<typename T>
void stack<T>::push(T data)
{
    node<T> *p_node = new node<T>;
    p_node->data = data;
    p_node->next = m_head;
    p_node->prev = m_currentNode;
    
    m_currentNode->next = p_node;/*为什么这里的m_currentNode不为空也会段错误？？？*/
    m_head->prev = p_node;

    m_currentNode = p_node;
}

template<typename T>
T stack<T>::pop()
{
    node<T> *tmp = m_currentNode;
    m_currentNode = m_currentNode->prev;
    m_currentNode->next = m_head;
    m_head->prev = m_currentNode;

    tmp->next = nullptr;
    tmp->prev = nullptr;
    
    T data = tmp->data;
    delete tmp;

    return data;
}

template<typename T>
T stack<T>::top()
{
    return m_currentNode->data;
}

template<typename T>
bool stack<T>::isEmpty()
{
    return m_currentNode == m_head;
}


#endif //STACK_K