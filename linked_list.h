namespace LLST {
    template < typename T >
    class linked_list {
        struct node {
            T value;
            node * next;
            node * previous;
        };
        node * _end;
    public:
        class iterator {
            node * element;
        public:
            // Default constructor
            explicit iterator(const node * el) {
                element = new node;
                element->value = el->value;
                element->next = el->next;
                element->previous = el->previous;
            }
            // Copy constructor
            iterator & operator=(const iterator & other) {
                element->value = other.element->value;
                element->next = other.element->next;
                element->previous = other.element->previous;
                return *this;
            }

            bool operator==(const iterator & other) const {
                return (element->next == other.element->next
                        && element->previous == other.element->previous);
            }
            bool operator!=(const iterator & other) const {
                return !(other == *this);
            }
            T & operator*() { return this->element->value; } // Get element reference
            T * operator->() { return &this->element->value; } // Get element pointer

            iterator & operator++() {
                iterator & copy = *this;
                element = element->next;
                return copy;
            }
            iterator operator++(int) {
                element = element->next;
                return *this;
            }
            iterator & operator--() {
                iterator & copy = *this;
                element = element->previous;
                return copy;
            }
            iterator operator--(int) {
                element = element->previous;
                return *this;
            }

            friend linked_list;
        };

        class const_iterator {
            const node * element;
        public:
            const_iterator(const node * el) {
                auto elem = new node;
                elem->value = el->value;
                elem->next = el->next;
                elem->previous = el->previous;
                element = elem;
            }
            const_iterator & operator=(const const_iterator & other) {
                auto elp = new node;
                elp->value = other.element->value;
                elp->next = other.element->next;
                elp->previous = other.element->previous;
                this->element = elp;
                return *this;
            }

            bool operator!=(const const_iterator & other) const {
                return !(*this == other);
            }
            bool operator==(const const_iterator & other) const {
                return (element->next == other.element->next
                        && element->previous == other.element->previous);
            }
            const T & operator*() const { return this->element->value; }; // Get element reference
            const T * operator->() const { return &this->element->value; }; // Get element pointer

            const_iterator & operator++() {
                const_iterator &copy = *this;
                element = element->next;
                return copy;
            }
            const_iterator operator++(int) {
                element = element->next;
                return *this;
            }
            const_iterator & operator--() {
                const_iterator &copy = *this;
                element = element->previous;
                return copy;
            }
            const_iterator operator--(int) {
                element = element->previous;
                return *this;
            }

            friend linked_list;
        };

        // Create an empty list
        linked_list() {
            _end = new node;
            _end->next = _end;
            _end->previous = _end;
        }
        // Create a new list with elements from another list
        linked_list(const linked_list & other) {
            _end = new node;
            _end->value = 0;
            _end->next = _end;
            _end->previous = _end;
            for (auto it : other) {
                push_back(it); // ?
            }
        }
        // Move constructor
        linked_list(linked_list && other) {
            _end = other._end;
        }

        // Destructor
        ~linked_list() {
            auto current = _end->next;
            while (current != _end) {
                current = current->next;
                delete current->previous;
            }
            delete _end;
        }

        // 
        linked_list & operator=(const linked_list & other) {
            this->clear();
            for (auto it : other) {
                push_back(it);
            }
            return *this;
        }
        linked_list & operator=(linked_list && other) {
            _end = other._end;
            return *this;
        }

        iterator begin() { return iterator(_end->next);}
        const_iterator begin() const { return const_iterator(_end->next); }
        const_iterator cbegin() const { return const_iterator(_end->next); }

        iterator end() { return iterator(_end); }
        const_iterator end() const { return const_iterator(_end); }
        const_iterator cend() const { return const_iterator(_end); }

        // Size of list
        int size() const {
            int size = 0;
            for (auto it : *this) {
                ++size;
            }
            return size;
        }
        // "true" if the list is empty, "false" otherwise
        bool empty() const { return _end->next == _end; }

        // Reference to the first element
        T & front() { return _end->next->value; }
        // Reference to the first element
        const T & front() const { return _end->next->value; }

        // Reference to the last element
        T & back() { return _end->previous->value; }
        // Reference to the last element
        const T & back() const { return _end->previous->value; }

        // Modificators

        // Delete [index] element
        iterator erase(iterator index) {
            auto ret_node = index.element->next;
            index.element->previous->next = index.element->next;
            index.element->next->previous = index.element->previous;
            delete index.element;
            return *(new iterator(ret_node));
        }
        // Delete [begin, end] elements
        iterator erase(iterator begin, iterator end) {
            auto ret_node = end.element->next;
            begin.element->previous->next = end.element->next;
            end.element->next->previous = begin.element->previous;
            auto current = begin;
            while (current != end) {
                current++;
                delete current.element->previous;
            }
            delete end.element;
            return *(new iterator(ret_node));
        }
        // Delete all occurrences of (value)
        int remove(const T & value) {
            auto current = begin();
            int count = 0;
            while (current != end()) {
                if (*current == value) {
                    current = erase(current);
                    ++count;
                }
                else {
                    ++current;
                }
            }
            return count;
        }
        // Clears the list
        void clear() {
            auto it = begin();
            while (it != end()) {
                it = erase(it);
            }
        }

        // Delete the last element
        void pop_back() {
            auto elm = _end->previous;
            elm->previous->next = _end;
            _end->previous = elm->previous;
            delete elm;
        }
        // Delete the first element
        void pop_front() {
            auto elm = _end->next;
            elm->next->previous = _end;
            _end->next = elm->next;
            delete elm;
        }
        // Add (value) to the end of the list
        void push_back(const T & value) {
            auto new_element = new node;
            new_element->value = value;
            new_element->next = _end;
            new_element->previous = _end->previous;
            _end->previous->next = new_element;
            _end->previous = new_element;
        }
        // Add (value) to the begin of the list
        void push_front(const T & value) {
            auto new_element = new node;
            new_element->value = value;
            new_element->previous = _end;
            new_element->next = _end->next;
            _end->next->previous = new_element;
            _end->next = new_element;
        }
        // Add (value) to the element before [before]
        iterator insert(iterator before, const T & value) {
            auto new_element = new node;
            new_element->value = value;
            new_element->next = before.element;
            new_element->previous = before.element->previous;
            before.element->previous->next = new_element;
            before.element->previous = new_element;
            return *(new iterator(new_element));
        }

        // Internal operators

        // Concat of lists
        linked_list & operator+=(const linked_list & other) {
            for (auto it : other) {
                this->push_back(it);
            }
            return *this;
        }

        // External operators
        friend bool operator!=(const linked_list & left, const linked_list & right) {
            auto it1 = left.begin();
            auto it2 = right.begin();
            while (it1 != left.end() && it2 != right.end()) {
                if (*it1 != *it2) {
                    return true;
                }
                it1++;
                it2++;
            }
            return (left.size() != right.size());
        }
        friend bool operator==(const linked_list & left, const linked_list & right) {
            auto it1 = left.begin();
            auto it2 = right.begin();
            while (it1 != left.end() && it2 != right.end()) {
                if (*it1 != *it2) {
                    return false;
                }
                it1++;
                it2++;
            }
            return (left.size() == right.size());
        }
    };
}