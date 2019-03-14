#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <algorithm>

using namespace std;

template <class T>
class Multime {
private:
    int capacitate;
    int dimensiune;
    T *v;

public:

    void sortare() {
        for (int i = 0; i < dimensiune - 1; ++i) {
            for (int j = i + 1; j < dimensiune; ++j) {
                if (v[i] > v[j]) {
                    T aux = v[i];
                    v[i] = v[j];
                    v[j] = aux;
                }
            }
        }
    }

    void add(T x) {
        if (!exist(x)) {
            v[dimensiune] = x;
            dimensiune ++;
            if (dimensiune == capacitate) {
                T *copyV = new T[dimensiune];
                for (int i = 0; i < dimensiune; ++i) {
                    copyV[i] = v[i];
                }
                delete[] v;
                capacitate = 2 * capacitate;
                v = new T[capacitate];
                for (int i = 0; i < dimensiune; ++i) {
                    v[i] = copyV[i];
                }
                delete[] copyV;
            }
        }
    }
    bool exist(T x) const {
        for (int i = 0; i < dimensiune; ++i) {
            if (v[i] == x) return true;
        }
        return false;
    }
    int getDim() const { return dimensiune;}
    Multime() {
        capacitate = 5;
        dimensiune = 0;
        v = new T[capacitate];
    }
    Multime(int n, T *a) {
        capacitate = 5;
        dimensiune = 0;
        v = new T[capacitate];
        for (int i = 0; i < n; ++i) {
            add(a[i]);
        }
    }

    ~Multime() {
        delete[] v;
    }

    Multime &operator =(const Multime &m) {
        if (this == &m) return (*this);
        delete[] v;
        this->capacitate = m.capacitate;
        this->dimensiune = m.dimensiune;
        v = new T[capacitate];
        for (int i = 0; i < dimensiune; ++i) {
            v[i] = m[i];
        }
        return (*this);
    }

    T &operator [] (int pos) const {
        return v[pos];
    }
    template<class Y>
    friend Multime<Y> transformareInMultime(int, Y*);
    friend ostream &operator <<(ostream &out, const Multime &m) {
        out << "{";
        for (int i = 0; i < m.dimensiune - 1; ++i) {
            out << m[i] << ", ";
        }
        if (m.dimensiune != 0) {
            out << m[m.dimensiune - 1];
        }
        out << "}";
        return out;
    }
    friend istream &operator >>(istream &in, Multime &m) {
        int n;
        in >> n;
        for (int i = 0; i < n; ++i) {
            T x;
            in >> x;
            m.add(x);
        }
        return in;
    }

    friend Multime operator +(const Multime &m1, const Multime &m2) {
        Multime m3;
        for (int i = 0; i < m1.dimensiune; ++i) {
            m3.add(m1[i]);
        }
        for (int i = 0; i < m2.dimensiune; ++i) {
            m3.add(m2[i]);
        }
        return m3;
    }

    Multime(const Multime &m) {
        this->dimensiune = m.getDim();
        this->capacitate = m.capacitate;
        v = new T[capacitate];
        for (int i = 0; i < m.getDim(); ++i) {
            v[i] = m[i];
        }
    }
    friend Multime operator *(const Multime &m1, const Multime &m2) {
        Multime m3;
        for (int i = 0; i < m1.dimensiune; ++i) {
            if (m2.exist(m1[i])) {
                m3.add(m1[i]);
            }
        }
        return m3;
    }

    friend Multime operator -(const Multime &m1, const Multime &m2) {
        Multime m3;
        for (int i = 0; i < m1.dimensiune; ++i) {
            if ( !m2.exist(m1.v[i]) ) { m3.add(m1[i]);}
        }
        return m3;
    }
    friend bool operator ==(Multime &m1, Multime &m2) {
        if (m1.getDim() != m2.getDim()) return false;
        for (int i = 0; i < m1.getDim(); ++i) {
            bool amGasit = false;
            for (int j = 0; j < m2.getDim(); ++j) {
                if (m1[i] == m2[j]) { amGasit = true;}
            }
            if (!amGasit) { return amGasit;}
        }
        return true;
    }
    friend bool operator !=(Multime &m1, Multime &m2) {
        return (!(m1 == m2));
    }

    friend bool operator <(Multime &m1, Multime &m2) {
        if (m1.dimensiune != m2.dimensiune) return (m1.dimensiune < m2.dimensiune);
        Multime copyM1 = m1;
        Multime copyM2 = m2;
        m1.sortare();
        m2.sortare();

        for (int i = 0; i < m1.dimensiune; ++i) {
            if (m1[i] < m2[i]) {
                m1 = copyM1;
                m2 = copyM2;
                return true;
            } else if (m1[i] > m2[i]) {
                m1 = copyM1;
                m2 = copyM2;
                return false;
            }
        }
        m1 = copyM1;
        m2 = copyM2;
        return false;
    }

    friend bool operator <=(Multime &m1, Multime &m2) {
        bool este = (m1 < m2 || m1 == m2);
        return este;
    }

    friend bool operator >(Multime &m1, Multime &m2) {
        bool este = (m1 <= m2);
        return !este;
    }

    friend bool operator >=(Multime &m1, Multime &m2) {
        bool este = (m1 > m2 || m1 == m2);
        return este;
    }


};

template <class Y>
Multime<Y> transformareInMultime(int n, Y *a) {
    Multime<Y> m(n, a);
    return m;
}

template <class T>
class Pereche {
private:
    T x, y;
public:
    Pereche() {}
    Pereche(T x, T y) {
        this->x = x;
        this->y = y;
    }
    T getX() const{ return x;}
    T getY() const{ return y;}
    void setX(T x) { this->x = x;}
    void setY(T y) { this->y = y;}
    T &operator[] (int pos) {
        if (pos != 0 && pos != 1) throw ("Indice invalid in clasa Pereche!");
        if (pos == 0) { return x;}
        return y; // pos == 1
    }

    Pereche(const Pereche &per) {
        this->x = per.x;
        this->y = per.y;
    }

    friend istream &operator >>(istream &in, Pereche &per) {
        in >> per.x;
        in >> per.y;
        return in;
    }
    friend ostream &operator <<(ostream &out, const Pereche &per) {
        out << "<" << per.x << ", " << per.y << ">";
        return out;
    }

    Pereche &operator =(const Pereche &per) {
        if (this == &per) return (*this);
        this->x = per.getX();
        this->y = per.getY();
        return (*this);
    }

    friend bool operator ==(Pereche &p1, Pereche &p2) {
        if (p1[0] != p2[0] || p1[1] != p2[1]) return false;
        return true;
    }
    friend bool operator !=(Pereche &p1, Pereche &p2) {
        return (!(p1 == p2));
    }
    friend bool operator <(Pereche &p1, Pereche &p2) {
        if (p1[0] < p2[0] || (p1[0] == p2[0] && p1[1] < p2[1])) return true;
        return false;
    }
    friend bool operator <=(Pereche &p1, Pereche &p2) {
        return (p1 < p2 || p1 == p2);
    }

    friend bool operator >(Pereche &p1, Pereche &p2) {
        return !(p1 <= p2);
    }
    friend bool operator >=(Pereche &p1, Pereche &p2) {
        return !(p1 < p2);
    }

};


template <class T>
class MultimePerechi {
private:
    int dimensiune;
    int capacitate;
    Pereche<T> *p;
public:
    MultimePerechi() {
        dimensiune = 0;
        capacitate = 5;
        p = new Pereche<T>[capacitate];
    }
    ~MultimePerechi() {
        delete[] p;
    }

    MultimePerechi(const MultimePerechi &mp) {
            this->capacitate = mp.capacitate;
            this->dimensiune = mp.dimensiune;
            p = new Pereche<T>[capacitate];
            for (int i = 0; i < this->dimensiune; ++i) {
                p[i] = mp[i];
            }
    }

    int getDim() const { return dimensiune;}

    friend class Pereche<T>;

    bool exist(Pereche<T> pCurent) {
        for (int i = 0; i < dimensiune; ++i) {
            if (p[i][0] == pCurent[0] && p[i][1] == pCurent[1]) { return true;}
        }
        return false;
    }
    void add(Pereche<T> per) {
        if (!exist(per)) {
            p[dimensiune] = per;
            dimensiune ++;
            if (dimensiune == capacitate) {
                Pereche<T> *copyPer = new Pereche<T>[dimensiune];
                for (int i = 0; i < dimensiune; ++i) {
                    copyPer[i] = p[i];
                }
                delete[]p;
                capacitate = 2 * capacitate;
                p = new Pereche<T>[capacitate];
                for (int i = 0; i < dimensiune; ++i) {
                    p[i] = copyPer[i];
                }
                delete[]copyPer;
            }
        }
    }

    Pereche<T> &operator [](int index) const{
        return p[index];
    }

    MultimePerechi &operator =(const MultimePerechi &mp) {
        if (&mp == this) return *this;
        this->capacitate = mp.capacitate;
        this->dimensiune = mp.dimensiune;
        delete[] p;
        p = new Pereche<T>[capacitate];
        for (int i = 0; i < dimensiune; ++i) {
            p[i] = mp[i];

        }
        return (*this);
    }

    friend ostream &operator <<(ostream &out, const MultimePerechi &mp) {
        out << "{";
        for (int i = 0; i < mp.getDim() - 1; ++i) {
            out << "(" << mp[i][0] << ", " << mp[i][1] << "), ";
        }
        if (mp.getDim() != 0) {
            out << "(" << mp[mp.getDim() - 1][0] << ", " << mp[mp.getDim() - 1][1] << ")}";
        } else {
            out << "}";
        }
        return out;
    }

    friend istream &operator >>(istream &in, MultimePerechi &mp) {
        int n;
        in >> n;
        for (int i = 0; i < n; ++i) {
            Pereche<T> per;
            in >> per;
            mp.add(per);
        }

        return in;
    }

    void sortare() {
        for (int i = 0; i < dimensiune; ++i) {
            for (int j = i + 1; j < dimensiune; ++j) {
                if (p[i] > p[j]) {
                    Pereche<T> aux;
                    aux = p[i];
                    p[i] = p[j];
                    p[j] = aux;
                }
            }
        }
    }

    friend bool operator <(MultimePerechi &m1, MultimePerechi &m2) {
        if (m1.dimensiune != m2.dimensiune) return (m1.dimensiune < m2.dimensiune);
        MultimePerechi copyM1 = m1;
        MultimePerechi copyM2 = m2;
        copyM1.sortare();
        copyM2.sortare();
        for (int i = 0; i < m1.dimensiune; ++i) {
            if (copyM1[i] < copyM2[i]) return true;
            if (copyM1[i] > copyM2[i]) return false;
        }
        return false;
    }
    friend bool operator ==(MultimePerechi &m1, MultimePerechi &m2) {
        if (m1.dimensiune != m2.dimensiune) return false;
        MultimePerechi<T> cm1 = m1;
        MultimePerechi<T> cm2 = m2;
        cm1.sortare();
        cm2.sortare();
        for (int i = 0; i < m1.dimensiune; ++i) {
            if (cm1[i] != cm2[i]) return false;
        }
        return true;
    }
    friend bool operator <=(MultimePerechi &m1, MultimePerechi &m2) {
        return (m1 == m2 || m1 < m2);
    }
    friend  bool operator >(MultimePerechi &m1, MultimePerechi &m2) {
        return (!(m1 <= m2));
    }
    friend bool operator >=(MultimePerechi &m1, MultimePerechi &m2) {
        return (!(m1 < m2));
    }
    friend bool operator !=(MultimePerechi &m1, MultimePerechi &m2) {
        return (!(m1 == m2));
    }

};

template <class T>
MultimePerechi<T> produsCartezian(const Multime<T> &m1, const Multime<T> &m2) {
    MultimePerechi<T> mp;
    for (int i = 0; i < m1.getDim(); ++i) {
        for (int j = 0; j < m2.getDim(); ++j) {
            Pereche<T> p;
            p.setX(m1[i]);
            p.setY(m2[j]);
            mp.add(p);
        }
    }
    return mp;
}

bool cmp(Pereche<int> p1, Pereche<int> p2) {
    return (p1 < p2);
}

int main() {

    //////////////// MULTIMI //////////////////

    int n = 11;
    int v[] = {2, 1, 4, 2, 4, 3, 6, 5, 8, 9, -24};
    Multime<int> m1;
    m1 = transformareInMultime(n, v);
    m1.add(3);
    //cout << m1;

    int m = 5;
    int w[] = {2, 4, 6, 5, -6};
    Multime<int> m2(m, w);
    Multime<int> m3;
    /*cin >> m3;
    Multime<int> m4 = m1 + m3;
    Multime<int> m5 = m1 * m3;
    Multime<int> m6 = m1 - m3;
    cout << m1 << "\n" << m2 << "\n" << m3 << "\n" << m4 << "\n" << m5 << "\n" << m6;*/

    //////////////////////////////////////////


    ///////////////// PERECHI ////////////////

    Pereche<int> p1;
    p1[0] = 2;
    p1[1] = 43;
    Pereche<int> p2(4, 5);
    Pereche<int> p3 = p1;
    Pereche<int> p4;
    p4 = p1;
    //cout << p1 << " " << p2 << " " << p3 << " " << p4;

    /////////////////////////////////////////

    /////////// MULTIMI DE PERECHI //////////

    MultimePerechi<int> mp;

    mp = produsCartezian(m1, m2);
    mp.add(p1);
    mp.add(p2);

    //cout << mp << "\n";

    MultimePerechi<int> mp2;
    mp2 = mp;
    p1[0] = 100;
    p1[1] = 200;
    //mp2.add(p1);
    //cout << (mp2 != mp) << "\n";
    //cout << mp << "\n" << mp2 << "\n";

    //cout << mp2;
    /////////////////////////////////////////

    /////////SORTARE////////////////////////

    MultimePerechi<int> *mpArray = new MultimePerechi<int>[11];
    mpArray[10] = produsCartezian(m1, m2);
    for (int i = 0; i < 10; ++i) {
        Pereche<int> per(i, i + 1);
        mpArray[i].add(per);
        per[0] = -6;
        per[1] = 3 * i;
        mpArray[i].add(per);
        if (i == 3) {
            per[0] = -73;
            per[1] = 5;
            mpArray[i].add(per);
        } else if (i == 7) {
            per[0] = 9;
            per[1] = -5;
            mpArray[i].add(per);
        }
    }
    /*
    for (int i = 0; i < 11; ++i) {
        cout << mpArray[i] << "\n";
    }
    cout << "\n" << "\n";
    sort(mpArray, mpArray + 11, cmp);
    for (int i = 0; i < 11; ++i) {
        cout << mpArray[i] << "\n";
    }
    delete[] mpArray;*/

    Multime<int> *mult = new Multime<int>[11];
    mult[10] = transformareInMultime(11, v);

    for (int i = 0; i < 10; ++i) {
        mult[i].add(2 * i + 3);
        if (i == 3) {
            mult[i].add(4);
        }
        if (i == 7) {
            mult[i].add(6);
        }
    }

    /*sort(mult, mult + 11);
    for (int i = 0; i < 11; ++i) {
        cout << mult[i] << "\n";
    }*/


    Pereche<float> *perArray = new Pereche<float>[10];
    for (int i = 0; i < 10; ++i) {
        perArray[i][0] = (float) i - 1;
        perArray[i][1] = (float) i + 1;
        if (i == 3) {
            perArray[i][0] = 200.6;
            perArray[i][1] = 300.3;
        }
        if (i == 7) {
            perArray[i][1] = 200.9;
            perArray[i][0] = 300.0;
        }
    }
    //sort(perArray, perArray + 10);

    /*for (int i = 0; i < 10; ++i) {
        for (int j = i + 1; j < 10; ++j) {
            if (perArray[i] > perArray[j]) {
                Pereche<float> aux = perArray[i];
                perArray[i] = perArray[j];
                perArray[j] = aux;
            }
        }
    }
    for (int i = 0; i < 10; ++i) {
        cout << perArray[i] << "\n";
    }
    delete[] perArray;*/

    MultimePerechi<int> *multimePerechiTest = new MultimePerechi<int>[10];
    for (int i = 0; i < 10; ++i) {
        multimePerechiTest[i] = produsCartezian(mult[i], mult[i + 1]);
    }
    sort(mult, mult + 10);

    for (int i = 0; i < 11; ++i) {
        cout << mult[i] << "\n";
    }

    return 0;
}
