#ifndef MATRICE_H
#define MATRICE_H

#include<iostream>
#include<map>
#include<set>
using namespace std;

class MatriceSkeleton{
    protected :
    unsigned int n_lignes;
    unsigned int n_colonnes;
    public :
    unsigned int getLignes() const;
    unsigned int getColonnes() const;
};

typedef pair<unsigned int,unsigned int> Position;

template<class T> class MatriceMap : private MatriceSkeleton{
    map<Position,T> mat;

    public :

    MatriceMap(const unsigned int i,const unsigned int j,const T& x=0);
    MatriceMap();
    ~MatriceMap();

    map<Position,T> getMat() const;
    void setMat(const map<Position,T>& mat);

    MatriceMap<T>& operator=(const MatriceMap<T>& other);

    template<class U>
    friend MatriceMap<U> operator+(const MatriceMap<U>& m1, const MatriceMap<U>& m2);
    template<class U>
    friend MatriceMap<U> operator+(const MatriceMap<U>& m, const U& scal);
    template<class U>
    friend MatriceMap<U> operator+(const U& scal,const MatriceMap<U>& m);

    template<class U>
    friend ostream& operator<<(ostream& out, const MatriceMap<U>& M);
};

template<class T> class Case{
    Position key;
    T value;
    public :
    Case(const Position& k,const T& v);
    ~Case();
    T getValue() const ;
    void setValue(const T& val);
    Position getKey() const ;
    template<class S> 
    friend bool operator<(const Case<S>& c1, const Case<S>& c2);
};
template<class T> class MatriceSet : private MatriceSkeleton{
    set<Case<T> > mat;

    public :

    MatriceSet(const unsigned int i,const unsigned int j,const T& x=0);
    MatriceSet();
    ~MatriceSet();

    MatriceSet<T>& operator=(const MatriceSet<T>& other);
    T operator[](const Position& pos) const ;
    template<class S>
    friend MatriceSet<S> operator+(const MatriceSet<S>& m1,const MatriceSet<S>& m2);
    template<class S>
    friend MatriceSet<S> operator+(const MatriceSet<S>& m,const S& scal);
    template<class S>
    friend MatriceSet operator+(const S& scal,const MatriceSet<S>& m);

    template<class S>
    friend ostream& operator<<(ostream& out,const MatriceSet<S>& M);

    set<Case<T> > getMat() const;

};

template<class Scalaire> class MatriceDynamique : private MatriceSkeleton{
    Scalaire* mat;

    public:
    
    MatriceDynamique(const unsigned int i,const unsigned int j,const Scalaire& x=0);
    MatriceDynamique();
    ~MatriceDynamique();
    
    MatriceDynamique<Scalaire>& operator=(const MatriceDynamique<Scalaire>& other);
    
    template<class S>
    friend MatriceDynamique<S> operator+(const MatriceDynamique<S>& m1,const MatriceDynamique<S>& m2);
    template<class S> 
    friend MatriceDynamique<S> operator+(const MatriceDynamique<S>& m,const S& scal);
    template<class S> 
    friend MatriceDynamique<S> operator+(const S& scal,const MatriceDynamique<S>& m);

    template<class S>
    friend ostream& operator<<(ostream& out,const MatriceDynamique<S>& M);

    Scalaire* getMat() const;

    void setLignes(const unsigned int& i);
    void setColones(const unsigned int& j);
    void setMat(const Scalaire* Mat);

};

#endif