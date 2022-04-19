#include <iostream>
#include <list>
#include <map>


class MyException : public std::exception {
public:
    const char* what() const throw() {
        return "Exceptie\n";
    }
};

class EmptyList : public std::exception {
public:
    const char* what() const throw() {
        return "List is empty";
    }
};

class UnavailablePointer : public std::exception {
public:
    const char* what() const throw() {
        return "Element can't be erased";
    }
};

class OutOfRange : public std::exception {
public:
    const char* what() const throw() {
        return "Index out of range";
    }
};


class Nod {
    int info;
    Nod* next;
public:
    Nod(int info = 0, Nod* next = nullptr) {
        this->info = info;
        this->next = next;
    }

    Nod(const Nod& a) {
        info = a.info;
        next = a.next;
    }

    int get_info() const {
        return info;
    }

    Nod* get_next() {
        return next;
    }

    void set_next(Nod* n) {
        next = n;
    }

    Nod& operator=(const Nod&);

    friend std::ostream& operator<<(std::ostream&, const Nod&);

    friend std::istream& operator>>(std::istream&, Nod&);

    virtual ~Nod() = default;
};

Nod& Nod::operator=(const Nod& a) {
    if (this == &a)
        return *this;
    this->info = a.info;
    this->next = a.next;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Nod& a) {
    out << a.info;
    return out;
}

std::istream& operator>>(std::istream& in, Nod& a) {
    in >> a.info;
    return in;
}

class Nod_dublu : public Nod {
    Nod* prev;
public:
    Nod_dublu(int info = 0) : Nod(info) {
        this->prev = nullptr;
    }

    Nod_dublu(const Nod_dublu& n) : Nod(n) {
        this->prev = n.prev;
    }

    Nod_dublu(const Nod& n) : Nod(n) {
        this->prev = nullptr;
    }


    friend std::ostream& operator<<(std::ostream&, const Nod_dublu&);

    friend std::istream& operator>>(std::istream&, Nod_dublu&);

    Nod_dublu& operator=(const Nod_dublu&);

    Nod* get_prev() {
        return prev;
    }

    void set_prev(Nod* p) {
        prev = p;
    }
};

Nod_dublu& Nod_dublu::operator=(const Nod_dublu& a) {
    if (this == &a)
        return *this;
    this->Nod::operator=(a);
    this->prev = a.prev;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Nod_dublu& a) {
    out << dynamic_cast<const Nod&>(a);
    return out;
}

std::istream& operator>>(std::istream& in, Nod_dublu& a) {
    in >> dynamic_cast<Nod&>(a);
    return in;
}

class LDI {
    static int cnt;
    Nod_dublu* start, * final;
    int n, id;
protected:
    void set_start(Nod_dublu* n) {
        start = n;
    }

    void set_final(Nod_dublu* n) {
        final = n;
    }

    void set_size(int val) {
        n = val;
    }

public:
    LDI() {
        cnt++;
        start = final = new Nod_dublu(-1);
        n = 0;
        id = cnt;
    }

    LDI(int v) {
        n = 1;
        cnt++;
        id = cnt;
        start = new Nod_dublu(v);
        final = new Nod_dublu(-1);
        final->set_next(nullptr);
        final->set_prev(dynamic_cast<Nod*>(start));
        start->set_next(dynamic_cast<Nod*>(final));
        start->set_prev(nullptr);
    }

    LDI(const LDI& l) {
        cnt++;
        id = cnt;
        n = 0;
        start = final = new Nod_dublu(-1);
        for (Nod_dublu* aux = l.start; aux != l.final; aux = dynamic_cast<Nod_dublu*>(aux->get_next()))
            this->push_back(aux->get_info());
    }

    virtual ~LDI() {
        Nod_dublu* aux = start;
        while (aux != nullptr) {
            Nod_dublu* aux1 = aux;
            aux = dynamic_cast<Nod_dublu*>(aux1->get_next());
            delete aux1;
        }
    }

    Nod_dublu* begin() {
        return start;
    }

    Nod_dublu* end() {
        return final;
    }

    bool empty() {
        return n == 0;
    }

    int size() {
        return n;
    }

    virtual void insert(Nod* it, int val);

    void insert(int poz, int val);

    virtual void erase(Nod* it);

    void erase(int poz);

    void push_back(int val) {
        this->insert(final, val);
    }

    void push_front(int val) {
        this->insert(start, val);
    }

    void pop_back() {
        this->erase(final->get_prev());
    }

    void pop_front() {
        this->erase(start);
    }

    friend std::ostream& operator<<(std::ostream& out, const LDI& l);

    static int get_cnt() {
        return cnt;
    }

    virtual void print(std::ostream& out) {
        if (this->n == 0)
            return;
        for (Nod_dublu* it = this->start; it != this->final; it = dynamic_cast<Nod_dublu*>(it->get_next())) {
            out << *it << " ";
        }
    }

    friend std::istream& operator>>(std::istream& in, LDI& l);

    LDI& operator=(const LDI&);

    void insertion_sort();
};

void LDI::insertion_sort() {
    for (Nod_dublu* it1 = dynamic_cast<Nod_dublu*>(start->get_next());
         dynamic_cast<Nod_dublu*>(it1) != final; it1 = dynamic_cast<Nod_dublu*>(it1->get_next())) {
        Nod_dublu* it2;
        for (it2 = it1; it2->get_prev() != nullptr && it2->get_prev()->get_info() >
                                                      it1->get_info(); it2 = dynamic_cast<Nod_dublu*>(it2->get_prev())) {
            int a = 1;
        }
        if (it1 != it2) {
            int val = it1->get_info();
            Nod_dublu* aux = dynamic_cast<Nod_dublu*>(it1->get_prev());
            erase(it1);
            insert(it2, val);
            it1 = aux;
        }
    }
}

std::istream& operator>>(std::istream& in, LDI& l) {
    int a;
    std::cin >> a;
    l.push_back(a);
    return in;
}

LDI& LDI::operator=(const LDI& l) {
    if (this == &l)
        return *this;
    this->~LDI();
    n = 0;
    start = final = new Nod_dublu(-1);
    for (Nod_dublu* aux = l.start; aux != l.final; aux = dynamic_cast<Nod_dublu*>(aux->get_next()))
        this->push_back(aux->get_info());
    return *this;
}

std::ostream& operator<<(std::ostream& out, const LDI& l) {
    if (l.n == 0)
        return out;
    for (Nod_dublu* it = l.start; it != l.final; it = dynamic_cast<Nod_dublu*>(it->get_next())) {
        out << *it << " ";
    }
    return out;
}

void LDI::insert(int poz, int val) {
    try {
        if (poz < 0 || poz >= n + 1)
            throw OutOfRange();
        Nod* aux = dynamic_cast<Nod*>(start);
        for (int i = 1; i <= poz; i++)
            aux = aux->get_next();
        insert(aux, val);
    }
    catch (OutOfRange& e) {
        std::cout << e.what() << "\n";
    }
}

void LDI::erase(int poz) {
    try {
        if (poz < 0 || poz >= n)
            throw OutOfRange();
        Nod* aux = dynamic_cast<Nod*>(start);
        for (int i = 1; i <= poz; i++)
            aux = aux->get_next();
        erase(aux);
    }
    catch (OutOfRange& e) {
        std::cout << e.what() << "\n";
    }
}

void LDI::erase(Nod* it) {
    Nod_dublu* it1 = dynamic_cast<Nod_dublu*>(it);
    try {
        if (empty())
            throw EmptyList();
        if (it1 == final)
            throw UnavailablePointer();
        if (n == 1) {
            delete start;
            start = final;
            n = 0;
            return;
        }
        n--;
        it1->get_prev()->set_next(it1->get_next());
        dynamic_cast<Nod_dublu*>(it1->get_next())->set_prev(it1->get_prev());
        delete it1;
    }
    catch (EmptyList& e) {
        std::cout << e.what() << '\n';
    }
    catch (UnavailablePointer& e) {
        std::cout << e.what() << "\n";
    }
}

void LDI::insert(Nod* it, int val) {
    Nod_dublu* it1 = dynamic_cast<Nod_dublu*>(it);
    if (it1 == start) {
        this->n++;
        Nod_dublu* n = new Nod_dublu(val);
        start->set_prev(dynamic_cast<Nod*>(n));
        n->set_prev(nullptr);
        n->set_next(dynamic_cast<Nod*>(start));
        start = n;
        return;
    }
    this->n++;
    Nod_dublu* n = new Nod_dublu(val);
    it1->get_prev()->set_next(dynamic_cast<Nod*>(n));
    n->set_prev(it1->get_prev());
    it1->set_prev(dynamic_cast<Nod*>(n));
    n->set_next(dynamic_cast<Nod*>(it1));
}


int LDI::cnt;

class LSI : public LDI {
public:
    LSI() : LDI() {};

    LSI(int val) : LDI(val) {};

    LSI(const LSI& l) : LDI(l) {};

    ~LSI() {

    }

    void insert(Nod*, int);

    void erase(Nod*);
};


void LSI::erase(Nod* it) {
    Nod_dublu* it1 = dynamic_cast<Nod_dublu*>(it);
    try {
        if (empty())
            throw EmptyList();
        if (it1 == end())
            throw UnavailablePointer();
        if (size() == 1) {
            delete begin();
            set_start(end());
            set_size(0);
            return;
        }
        if (it1 == begin()) {
            set_start(dynamic_cast<Nod_dublu*>(begin()->get_next()));
            delete it1;
            return;
        }
        set_size(size() - 1);
        Nod_dublu* aux;
        for (aux = begin(); dynamic_cast<Nod_dublu*>(aux->get_next()) != it1; aux = dynamic_cast<Nod_dublu*>(aux->get_next())) {
            int a = 1;
        }
        aux->set_next(it1->get_next());
        delete it1;
    }
    catch (EmptyList& e) {
        std::cout << e.what() << '\n';
    }
    catch (UnavailablePointer& e) {
        std::cout << e.what() << "\n";
    }
}

void LSI::insert(Nod* it, int val) {

    Nod_dublu* it1 = dynamic_cast<Nod_dublu*>(it);
    this->set_size(size() + 1);
    if (it1 == begin()) {
        Nod_dublu* n = new Nod_dublu(val);
        n->set_next(dynamic_cast<Nod*>(begin()));
        set_start(n);
        return;
    }
    Nod_dublu* aux;
    for (aux = begin(); dynamic_cast<Nod_dublu*>(aux->get_next()) != it1; aux = dynamic_cast<Nod_dublu*>(aux->get_next()));
    Nod_dublu* nou = new Nod_dublu(val);
    aux->set_next(dynamic_cast<Nod*>(nou));
    nou->set_next(dynamic_cast<Nod*>(it1));

}

int main() {
    /*LDI l(3);
    l.push_back(1);
    l.push_front(1000);
    l.push_front(1001);
    LDI cl(l);
    LDI cl1(2);
    cl1 = cl = l;
    cl1.insertion_sort();
    cl1.insert(2, 10000);
    cl1.insertion_sort();
    cl1.push_back(-1);
    cl1.insertion_sort();
    std::cout << cl1 << "\n" << l;*/

    LSI l(3);
    LDI& l1 = l;
    l1.insert(l1.begin(), 4);
    l1.insert(0, 15);
    l1.push_back(6);
    l1.erase(3);
    l1.pop_front();
    std::cout << l;
    return 0;
}
