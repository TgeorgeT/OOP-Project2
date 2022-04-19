#include <iostream>
#include <list>
#include <map>
#include <string>

class MyException : public std::exception {
public:
    const char *what() const throw() {
        return "Exceptie\n";
    }
};

class EmptyList : public std::exception {
public:
    const char *what() const throw() {
        return "List is empty";
    }
};

class UnavailablePointer : public std::exception {
public:
    const char *what() const throw() {
        return "Element can't be erased";
    }
};

class OutOfRange : public std::exception {
public:
    const char *what() const throw() {
        return "Index out of range";
    }
};

class WrongInput : public std::exception {
public:
    const char *what() const throw() {
        return "Wrong input";
    }
};


class Nod {
    int info;
    Nod *next;
public:
    Nod(int info = 0, Nod *next = nullptr) {
        this->info = info;
        this->next = next;
    }

    Nod(const Nod &a) {
        info = a.info;
        next = a.next;
    }

    int get_info() const {
        return info;
    }

    Nod *get_next() {
        return next;
    }

    void set_next(Nod *n) {
        next = n;
    }

    Nod &operator=(const Nod &);

    friend std::ostream &operator<<(std::ostream &, const Nod &);

    friend std::istream &operator>>(std::istream &, Nod &);

    virtual ~Nod() = default;
};

Nod &Nod::operator=(const Nod &a) {
    if (this == &a)
        return *this;
    this->info = a.info;
    this->next = a.next;
    return *this;
}

std::ostream &operator<<(std::ostream &out, const Nod &a) {
    out << a.info;
    return out;
}

std::istream &operator>>(std::istream &in, Nod &a) {
    in >> a.info;
    return in;
}

class Nod_dublu : public Nod {
    Nod *prev;
public:
    Nod_dublu(int info = 0) : Nod(info) {
        this->prev = nullptr;
    }

    Nod_dublu(const Nod_dublu &n) : Nod(n) {
        this->prev = n.prev;
    }

    Nod_dublu(const Nod &n) : Nod(n) {
        this->prev = nullptr;
    }


    friend std::ostream &operator<<(std::ostream &, const Nod_dublu &);

    friend std::istream &operator>>(std::istream &, Nod_dublu &);

    Nod_dublu &operator=(const Nod_dublu &);

    Nod *get_prev() {
        return prev;
    }

    void set_prev(Nod *p) {
        prev = p;
    }
};

Nod_dublu &Nod_dublu::operator=(const Nod_dublu &a) {
    if (this == &a)
        return *this;
    this->Nod::operator=(a);
    this->prev = a.prev;
    return *this;
}

std::ostream &operator<<(std::ostream &out, const Nod_dublu &a) {
    out << dynamic_cast<const Nod &>(a);
    return out;
}

std::istream &operator>>(std::istream &in, Nod_dublu &a) {
    in >> dynamic_cast<Nod &>(a);
    return in;
}

class LDI {
    static int cnt;
    Nod_dublu *start, *final;
    int n, id;
protected:
    void set_start(Nod_dublu *n) {
        start = n;
    }

    void set_final(Nod_dublu *n) {
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
        final->set_prev(dynamic_cast<Nod *>(start));
        start->set_next(dynamic_cast<Nod *>(final));
        start->set_prev(nullptr);
    }

    LDI(const LDI &l) {
        cnt++;
        id = cnt;
        n = 0;
        start = final = new Nod_dublu(-1);
        for (Nod_dublu *aux = l.start; aux != l.final; aux = dynamic_cast<Nod_dublu *>(aux->get_next()))
            this->push_back(aux->get_info());
    }

    virtual ~LDI() {
        Nod_dublu *aux = start;
        while (aux != nullptr) {
            Nod_dublu *aux1 = aux;
            aux = dynamic_cast<Nod_dublu *>(aux1->get_next());
            delete aux1;
        }
    }

    Nod_dublu *begin() {
        return start;
    }

    Nod_dublu *end() {
        return final;
    }

    bool empty() {
        return n == 0;
    }

    int size() {
        return n;
    }

    virtual void insert(Nod *it, int val);

    void insert(int poz, int val);

    virtual void erase(Nod *it);

    void erase(int poz);

    void push_back(int val) {
        this->insert(final, val);
    }

    void push_front(int val) {
        this->insert(start, val);
    }

    virtual void pop_back() {
        this->erase(final->get_prev());
    }

    void pop_front() {
        this->erase(start);
    }

    friend std::ostream &operator<<(std::ostream &out, const LDI &l);

    static int get_cnt() {
        return cnt;
    }

    virtual void print(std::ostream &out) {
        if (this->n == 0)
            return;
        for (Nod_dublu *it = this->start; it != this->final; it = dynamic_cast<Nod_dublu *>(it->get_next())) {
            out << *it << " ";
        }
    }

    friend std::istream &operator>>(std::istream &in, LDI &l);

    LDI &operator=(const LDI &);

    void insertion_sort();
};

void LDI::insertion_sort() {
    for (Nod_dublu *it1 = dynamic_cast<Nod_dublu *>(start->get_next());
         dynamic_cast<Nod_dublu *>(it1) != final; it1 = dynamic_cast<Nod_dublu *>(it1->get_next())) {
        Nod_dublu *it2;
        for (it2 = it1; it2->get_prev() != nullptr && it2->get_prev()->get_info() >
                                                      it1->get_info(); it2 = dynamic_cast<Nod_dublu *>(it2->get_prev())) {
            int a = 1;
        }
        if (it1 != it2) {
            int val = it1->get_info();
            Nod_dublu *aux = dynamic_cast<Nod_dublu *>(it1->get_prev());
            erase(it1);
            insert(it2, val);
            it1 = aux;
        }
    }
}

std::istream &operator>>(std::istream &in, LDI &l) {
    int a;
    std::cin >> a;
    l.push_back(a);
    return in;
}

LDI &LDI::operator=(const LDI &l) {
    if (this == &l)
        return *this;
    this->~LDI();
    n = 0;
    start = final = new Nod_dublu(-1);
    for (Nod_dublu *aux = l.start; aux != l.final; aux = dynamic_cast<Nod_dublu *>(aux->get_next()))
        this->push_back(aux->get_info());
    return *this;
}

std::ostream &operator<<(std::ostream &out, const LDI &l) {
    if (l.n == 0)
        return out;
    for (Nod_dublu *it = l.start; it != l.final; it = dynamic_cast<Nod_dublu *>(it->get_next())) {
        out << *it << " ";
    }
    return out;
}

void LDI::insert(int poz, int val) {
    try {
        if (poz < 0 || poz >= n + 1)
            throw OutOfRange();
        Nod *aux = dynamic_cast<Nod *>(start);
        for (int i = 1; i <= poz; i++)
            aux = aux->get_next();
        insert(aux, val);
    }
    catch (OutOfRange &e) {
        std::cout << e.what() << "\n";
    }
}

void LDI::erase(int poz) {
    try {
        if (poz < 0 || poz >= n)
            throw OutOfRange();
        if (n == 0)
            throw (EmptyList());
        Nod *aux = dynamic_cast<Nod *>(start);
        for (int i = 1; i <= poz; i++)
            aux = aux->get_next();
        erase(aux);
    }
    catch (EmptyList &e) {
        e.what();
    }
    catch (OutOfRange &e) {
        std::cout << e.what() << "\n";
    }
}

void LDI::erase(Nod *it) {
    try {
        if (empty())
            throw EmptyList();
        Nod_dublu *it1 = dynamic_cast<Nod_dublu *>(it);
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
        dynamic_cast<Nod_dublu *>(it1->get_next())->set_prev(it1->get_prev());
        delete it1;
    }
    catch (EmptyList &e) {
        std::cout << e.what() << '\n';
    }
    catch (UnavailablePointer &e) {
        std::cout << e.what() << "\n";
    }
}

void LDI::insert(Nod *it, int val) {
    Nod_dublu *it1 = dynamic_cast<Nod_dublu *>(it);
    if (it1 == start) {
        this->n++;
        Nod_dublu *n = new Nod_dublu(val);
        start->set_prev(dynamic_cast<Nod *>(n));
        n->set_prev(nullptr);
        n->set_next(dynamic_cast<Nod *>(start));
        start = n;
        return;
    }
    this->n++;
    Nod_dublu *n = new Nod_dublu(val);
    it1->get_prev()->set_next(dynamic_cast<Nod *>(n));
    n->set_prev(it1->get_prev());
    it1->set_prev(dynamic_cast<Nod *>(n));
    n->set_next(dynamic_cast<Nod *>(it1));
}


class LSI : public LDI {
public:
    LSI() : LDI() {};

    LSI(int val) : LDI(val) {};

    LSI(const LSI &l) : LDI(l) {};

    ~LSI() {

    }

    void insert(Nod *, int);

    void erase(Nod *);

    void pop_back() {
        LDI::erase(size() - 1);
    }
};


void LSI::erase(Nod *it) {
    try {
        if (empty())
            throw EmptyList();
        Nod_dublu *it1 = dynamic_cast<Nod_dublu *>(it);
        if (it1 == end())
            throw UnavailablePointer();
        if (size() == 1) {
            delete begin();
            set_start(end());
            set_size(0);
            return;
        }
        if (it1 == begin()) {
            set_start(dynamic_cast<Nod_dublu *>(begin()->get_next()));
            delete it1;
            return;
        }
        set_size(size() - 1);
        Nod_dublu *aux;
        for (aux = begin();
             dynamic_cast<Nod_dublu *>(aux->get_next()) != it1; aux = dynamic_cast<Nod_dublu *>(aux->get_next())) {
            int a = 1;
        }
        aux->set_next(it1->get_next());
        delete it1;
    }
    catch (EmptyList &e) {
        std::cout << e.what() << '\n';

    }
    catch (UnavailablePointer &e) {
        std::cout << e.what() << "\n";
    }
}

void LSI::insert(Nod *it, int val) {

    Nod_dublu *it1 = dynamic_cast<Nod_dublu *>(it);
    this->set_size(size() + 1);
    if (it1 == begin()) {
        Nod_dublu *n = new Nod_dublu(val);
        n->set_next(dynamic_cast<Nod *>(begin()));
        set_start(n);
        return;
    }
    Nod_dublu *aux;
    for (aux = begin();
         dynamic_cast<Nod_dublu *>(aux->get_next()) != it1; aux = dynamic_cast<Nod_dublu *>(aux->get_next()));
    Nod_dublu *nou = new Nod_dublu(val);
    aux->set_next(dynamic_cast<Nod *>(nou));
    nou->set_next(dynamic_cast<Nod *>(it1));

}


inline void rtrim(std::string &s) {
    s.erase(s.find_last_not_of(' ') + 1);
}

inline void ltrim(std::string &s) {
    s.erase(0, s.find_first_not_of(' '));
}

inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

int isnum(std::string a) {
    for (int i = 0; i < a.length(); i++)
        if (!(a[i] >= '0' && a[i] <= '9'))
            return 0;
    return 1;
}

int LDI::cnt;


void addList(std::map<int, LDI *> &m) {
    while (1) {
        std::cout << "\n#########################################\n\n";
        std::cout << "Press b to go back, 1 for doubly linked list or 2 for singly linked list:\n";
        std::string ans;
        std::getline(std::cin, ans);
        trim(ans);
        try {
            if ((!isnum(ans) || (ans != "1" && ans != "2")) && ans != "b")
                throw (WrongInput());
            if (ans == "b")
                return;
            std::cout << "Input an integer:";
            std::string number;
            std::getline(std::cin, number);
            trim(number);
            try {
                if (!isnum(number))
                    throw (WrongInput());
                LDI *l;
                if (ans == "2")
                    l = dynamic_cast<LDI *>(new LSI(std::stoi(number)));
                else
                    l = new LDI(std::stoi(number));
                m[l->get_cnt()] = l;
                return;
            }
            catch (WrongInput &e) {
                std::cout << "Please input an integer";
            }
        }
        catch (WrongInput &e) {
            std::cout << "Please press b to go back, 1 for doubly linked list or 2 for singly linked list:\n";
        }
    }
}

void modificare(std::map<int, LDI *> &m, int id) {
    LDI *l = m[id];
    while (1) {
        std::cout << "\n#########################################\n\n";
        std::cout << "Your List:\n" << *l << "\n\n";
        std::cout << "Pick an option:\n";
        std::cout << "0. Go back\n";
        std::cout << "1. Push back a number\n";
        std::cout << "2. Push front a number\n";
        std::cout << "3. Pop back\n";
        std::cout << "4. Pop front\n";
        std::cout << "5. Erase the element at the n-th position\n";
        std::cout << "6. Add the element at the n-th position\n";
        std::cout << "7. Sort doubly linked list\n";
        std::string ans;
        getline(std::cin, ans);
        int option = -1;
        try {
            option = stoi(ans);
            if (option > 7)
                throw WrongInput();
        }
        catch (const WrongInput &e) {
            std::cout << "Please type a number from 0 to 4\n";
            continue;
        }
        if (option == 0) {
            return;
        }
        if (option == 1) {
            while (1) {
                std::cout << "\n#########################################\n\n";
                std::cout << "Type b to go back or type a number:\n";
                std::string number;
                int nr;
                getline(std::cin, number);
                trim(number);
                if (number == "b")
                    break;
                try {
                    if (isnum(number) == 0)
                        throw (WrongInput());
                    nr = stoi(number);
                    l->push_back(nr);
                    break;
                }
                catch (const WrongInput &e) {
                    e.what();
                }
            }
        } else if (option == 2) {
            while (1) {
                std::cout << "\n#########################################\n\n";
                std::cout << "Type b to go back or type a number:\n";
                std::string number;
                int nr;
                getline(std::cin, number);
                trim(number);
                if (number == "b")
                    break;
                try {
                    if (isnum(number) == 0)
                        throw (WrongInput());
                    nr = stoi(number);
                    l->push_front(nr);
                    break;
                }
                catch (const WrongInput &e) {
                    e.what();
                }
            }

        } else if (option == 3) {
            l->pop_back();
        } else if (option == 4) {
            l->pop_front();
        } else if (option == 5) {
            while (1) {
                std::cout << "\n#########################################\n\n";
                std::cout << "Type b to go back or type a position:\n";
                std::string number;
                int nr;
                getline(std::cin, number);
                trim(number);
                if (number == "b")
                    break;
                try {
                    if (isnum(number) == 0)
                        throw WrongInput();
                    nr = stoi(number);
                    l->erase(nr);
                    break;
                }
                catch (WrongInput &e) {
                    e.what();
                }
            }
        } else if (option == 6) {
            while (1) {
                std::cout << "\n#########################################\n\n";
                std::cout << "Type b to go back or type a position:\n";
                std::string number;
                int poz;
                getline(std::cin, number);
                trim(number);
                if (number == "b")
                    break;
                try {
                    if (isnum(number) == 0)
                        throw WrongInput();
                    poz = stoi(number);
                    while (1) {
                        std::cout << "\n#########################################\n\n";
                        std::cout << "Type b to go back or type a number:\n";
                        std::string number1;
                        int nb;
                        getline(std::cin, number1);
                        trim(number1);
                        if (number1 == "b")
                            break;
                        try {
                            if (isnum(number1) == 0)
                                throw WrongInput();
                            nb = stoi(number1);
                            l->insert(poz,nb);
                            break;
                        }
                        catch (WrongInput &e) {
                            e.what();
                        }
                    }
                    break;
                }
                catch (WrongInput &e) {
                    e.what();
                }
            }
        }
        else{
            try{
            if(dynamic_cast<LSI *>(l)!= nullptr)
                throw std::exception();
            l->insertion_sort();
            }
            catch(std::exception &e){
                std::cout<<"List is not doubly linked\n";
            }
        }
    }
}


void operation(std::map<int, LDI *> &m) {
    while (1) {
        std::cout << "\n#########################################\n\n";
        std::cout << "Press b to go back or pick an id:\n";
        std::string ans;
        std::getline(std::cin, ans);
        trim(ans);

        try {
            if (ans == "b")
                return;
            if (!isnum(ans) || (isnum(ans) && m.find(std::stoi(ans)) == m.end()))
                throw (WrongInput());
            int id = std::stoi(ans);
            modificare(m, id);
        }
        catch (WrongInput &e) {
            std::cout << "Please press b to go back or pick a valid id\n";
        }
    }
}


int main() {
    std::map<int, LDI *> m;
    while (1) {
        std::cout << "Your lists:\n";
        for (auto it = m.begin(); it != m.end(); ++it) {
            if (dynamic_cast<LSI *>(it->second) != nullptr)
                std::cout << "Singly linked list";
            else
                std::cout << "Doubly linked list";
            std::cout << "\nID: " << it->first << "\n" << *(it->second) << "\n\n";
        }
        std::cout << "\nPick an option:\n1. Create a new list\n2. Perform an operation on a list\n";
        std::string ans;
        std::getline(std::cin, ans);
        trim(ans);
        try {
            if (!isnum(ans) || (ans != "1" && ans != "2"))
                throw (WrongInput());
            if (ans == "1") {
                addList(m);
            } else {
                operation(m);
            }
        }
        catch (WrongInput &e) {
            std::cout << "Please pick a number between 1 and 2\n";
        }
        std::cout << "\n#########################################\n\n";
    }
    return 0;
}
