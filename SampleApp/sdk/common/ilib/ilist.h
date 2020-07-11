/*---------------------------------------------------------------------------*/
/* ilist.h                                                                   */
/* copyright (c) innovaphone 2016 - 2017                                     */
/*                                                                           */
/*---------------------------------------------------------------------------*/

namespace istd {
    template <class T> class listElement;

    template <class T> class list {
        friend class listElement<T>;
        T * head;
        T * tail;
    public:
        list() {
            head = 0;
            tail = 0;
        }
        virtual ~list() {
            while (head) head->remove();
        }

        const T * front() const { return head; }
        T * front() { return head; }

        bool empty() { return head == NULL; }

        const T * back() const { return tail; }
        T * back() { return tail; }

        void push_front(T * e) {
            e->_list = this;
            if (head) head->prev = e;
            else tail = e;
            e->next = head;
            e->prev = 0;
            head = e;
        }

        void push_back(T * e) {
            e->_list = this;
            if (tail) tail->next = e;
            else head = e;
            e->prev = tail;
            e->next = 0;
            tail = e;
        }

        T * pop_front() {
            T * e = head;
            if (e) {
                head = e->next;
                if (head) head->prev = 0;
                else tail = 0;
                e->_list = 0;
                e->next = 0;
                e->prev = 0;
            }
            return e;
        }

        T * pop_back() {
            T * e = tail;
            if (e) {
                tail = e->prev;
                if (tail) tail->next = 0;
                else head = 0;
                e->_list = 0;
                e->next = 0;
                e->prev = 0;
            }
            return e;
        }

        void insertBefore(T * e, T * before) {
            e->_list = this;
            e->next = before;
            if (before) {
                e->prev = before->prev;
                before->prev = e;
            }
            else {
                e->prev = tail;
                tail = e;
            }
            if (e->prev) e->prev->next = e;
            else head = e;
        }

        void insertBehind(T * e, T * behind) {
            e->_list = this;
            e->prev = behind;
            if (behind) {
                e->next = behind->next;
                behind->next = e;
            }
            else {
                e->next = head;
                head = e;
            }
            if (e->next) e->next->prev = e;
            else tail = e;
        }

        void swap(T * a, T * b)
        {
            a->swap(b);
        }

        void sort(T * start = NULL, T * end = NULL)
        {
            if (start == NULL)
                start = head;
            if (end == NULL)
                end = tail;

            quickSort(start, end);
        }

    private:
        list(const list &) { };

        class list & operator= (const class list &) { return *this; };
        
        // Note: this quicksort implementaion is based on the solution found at GeeksForGeeks (http://www.geeksforgeeks.org/quicksort-for-linked-list/)
        void quickSort(T * start, T * end)
        {
            if (end != NULL && start != end && end->next != start) {
                T * pivot = start->prev;
                for (T * i = start; i != end; i = i->next)
                {
                    if (i->compare(end) <= 0)
                    {
                        pivot = (pivot == NULL) ? start : pivot->next;
                        if (pivot != i)
                            pivot->swap(i);
                    }
                }
                pivot = (pivot == NULL) ? start : pivot->next;
                pivot->swap(end);

                quickSort(start, pivot->prev);
                quickSort(pivot->next, end);
            }
        }
    };

    template <class T> class listElement {
        friend class list<T>;
        class list<T> * _list;
        T * prev;
        T * next;

    public:
        listElement() {
            _list = 0;
            prev = 0;
            next = 0;
        }

        virtual ~listElement() {
            remove();
        }

        const T * goNext() const { return next; }
        T * goNext() { return next; }

        const T * goPrev() const { return prev; }
        T * goPrev() { return prev; }

        void remove() {
            if (_list) {
                if (prev) prev->next = next;
                else _list->head = next;
                if (next) next->prev = prev;
                else _list->tail = prev;
                _list = 0;
                next = 0;
                prev = 0;
            }
        }

        const list<T> * getList() const { return _list; }
        list<T> * getList() { return _list; }
        virtual int compare(T * e) { ASSERT(false, "listElement::compare() not implemented. You need to implement it in your derived class in order to call it or istd::ilist::sort()"); return 0; }
        virtual void swap(T * with) { ASSERT(false, "listElement::swap() not implemented. You need to implement it in your derived class in order to call it or istd::ilist::sort()"); }

    private:
        listElement(const listElement &) { };
        class listElement & operator= (const class listElement &) { return *this; };
    };
}
