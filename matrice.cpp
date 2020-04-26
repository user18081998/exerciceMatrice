#ifndef MATRICE_CPP
#define MATRICE_CPP

#include "matrice.h"
using namespace std;

// ############################ MATRICE SKELETON ############################ 
// getters
unsigned int MatriceSkeleton::getLignes() const {return n_lignes;}
unsigned int MatriceSkeleton::getColonnes() const {return n_colonnes;}


// ############################ MATRICE MAP ############################ 
// constructeurs
template<class T>
MatriceMap<T>::MatriceMap(const unsigned int i,const unsigned int j,const T& x){
    if(i<=0 || j<=0){
        n_lignes=0;
        n_colonnes=0;
    }
    n_lignes=i;
    n_colonnes=j;
    for(int h=1;h<=n_lignes;h++)
        for(int k=1;k<=n_colonnes;k++)
            mat[Position(h,k)]=x;
}
template<class T>
MatriceMap<T>::MatriceMap(){
    n_lignes=0;
    n_colonnes=0;
}
// destructeur
template<class T> MatriceMap<T>::~MatriceMap(){}
// getters
template<class T> map<Position,T> MatriceMap<T>::getMat()const{return mat;}
// setters
template<class T> void MatriceMap<T>::setMat(const map<Position,T>& m){mat=m; return;}
// surcharge operateur =
template<class T> MatriceMap<T>& MatriceMap<T>::operator=(const MatriceMap<T>& other){
    n_lignes = other.getLignes();
    n_colonnes = other.getColonnes();
    mat=other.getMat();
    return *this;
}
//surcharger operateur +
template<class T> MatriceMap<T> operator+(const MatriceMap<T>& m1, const MatriceMap<T>& m2){
    MatriceMap<T> resultat(m1.getLignes(),m1.getColonnes());
    try{
        if(!(m1.getLignes()==m2.getLignes() && m1.getLignes()==m2.getColonnes()))
            throw "Matrices incompatibles";
        for(int i=1;i<=resultat.getLignes();i++)
            for(int j=1;j<=resultat.getColonnes();j++)
                resultat.mat[Position(i,j)]=m1.getMat()[Position(i,j)]+m2.getMat()[Position(i,j)];
    } catch(const char* m){
    cerr << m <<endl;
    }
    return resultat;
}
template<class T> MatriceMap<T> operator+(const MatriceMap<T>& m, const T& scal){
    return m+MatriceMap<T>(m.getLignes(),m.getColonnes(),scal);
}
template<class T> MatriceMap<T> operator+(const T& scal,const MatriceMap<T>& m){
    return m+MatriceMap<T>(m.getLignes(),m.getColonnes(),scal);
}
// surcharge operateur <<
template<class T> ostream& operator<<(ostream& out, const MatriceMap<T>& M){
    out<<"["<<endl;
    for(int i=1;i<=M.getLignes();i++){
        out<<" [";
        for(int j=1;j<=M.getColonnes();j++) out<<M.getMat()[Position(i,j)]<<", ";
        out<<"],"<<endl;
    }
    out<<"]"<<endl;
    return out;
}

// ############################ CLASS CASE ############################ 
template<class S> Case<S>::Case(const Position& k,const S& v){
    key=k;
    value=v;
}
template<class S> Case<S>::~Case(){}
template<class S> S Case<S>::getValue() const {return value;}
template<class S> void Case<S>::setValue(const S& val){value=val; return;}
template<class S> Position Case<S>::getKey() const {return key;}
template<class S> bool operator<(const Case<S>& c1, const Case<S>& c2){
    if(c1.getKey().first<c2.getKey().first)
        return true;
    else if(c1.getKey().first>c2.getKey().first)
        return false;
    else if(c1.getKey().second<=c2.getKey().second)
        return true;
    else 
        return false;
}

// ############################ MATRICE SET ############################ 
// constructeurs
template<class T>
MatriceSet<T>::MatriceSet(const unsigned int i,const unsigned int j, const T& x){
    if(i<=0 || j<=0){
        n_lignes=0;
        n_colonnes=0;
    }
    else{
        n_lignes=i;
        n_colonnes=j;
        for(int h=1;h<=n_lignes;h++)
            for(int k=1;k<=n_colonnes;k++)
                mat.insert(Case<T>(Position(h,k),x));
    }
}
template<class T> MatriceSet<T>::MatriceSet(){
    n_lignes=0;
    n_colonnes=0;
}
// destructeur
template<class T> MatriceSet<T>::~MatriceSet(){}
//constructeur de copie
template<class T> MatriceSet<T>& MatriceSet<T>::operator=(const MatriceSet<T>& other){
    n_lignes=other.getLignes();
    n_colonnes=other.getColonnes();
    mat=other.getMat();
    return *this;
}
//surcharge operateur []
template<class T> T MatriceSet<T>::operator[](const Position& pos) const {
    for(Case<T> element : mat){
        if(element.getKey()==pos)
            return element.getValue();
    }
    T v=0;
    return v;
}
//surcharge operateur +
template<class S> MatriceSet<S> operator+(const MatriceSet<S>& m1,const MatriceSet<S>& m2){
    MatriceSet<S> resultat(m1.getLignes(),m1.getColonnes());
    try{
        if(!(m1.getLignes()==m2.getLignes() && m1.getLignes()==m2.getColonnes()))
            throw "Matrices incompatibles";
        for(int i=1;i<=m1.getLignes();i++)
            for(int j=1;j<=m2.getColonnes();j++)
                resultat.mat.insert(Case<S>(Position(i,j),m1[Position(i,j)]+m2[Position(i,j)]));
    } catch(const char* m){
    cerr << m <<endl;
    }
    return resultat;
}
template<class S> MatriceSet<S> operator+(const MatriceSet<S>& m,const S& s){
    return MatriceSet<S>(m.getLignes(),m.getColonnes(),s)+m;
}
template<class S> MatriceSet<S> operator+(const S&s, const MatriceSet<S>m){
    return MatriceSet<S>(m.getLignes(),m.getColonnes(),s)+m;
}
//getters
template<class T> set<Case<T> > MatriceSet<T>::getMat() const {return mat;}
// surcharge ostream
template<class S> ostream& operator<<(ostream& out,const MatriceSet<S>& M){
    out<<"["<<endl;
    for(int i=1;i<=M.getLignes();i++){
        out<<" [";
        for(int j=1;j<=M.getColonnes();j++) 
            out<<M[Position(i,j)]<<", ";
        out<<"],"<<endl;
    }
    out<<"]"<<endl;
    return out;
}

// ############################ MATRICE DYNAMIQUE ############################ 
//constructeurs
template<class S>
MatriceDynamique<S>::MatriceDynamique(const unsigned int i,const unsigned int j,const S& x) {
    if(i<=0 || j<=0){
        n_lignes=0;
        n_colonnes=0;
        mat=nullptr;
    }
    mat=new S[i*j]; n_lignes=i; n_colonnes=j;
    for(int c=0;c<i*j;c++)
        mat[c]=x;
}
template<class S>
MatriceDynamique<S>::MatriceDynamique(){
    mat=nullptr;
    n_lignes=0;
    n_colonnes=0;
}
//destructeur
template<class S> 
MatriceDynamique<S>::~MatriceDynamique(){ delete[] mat;}
//getters
template<class S> S* MatriceDynamique<S>::getMat() const {return mat;}
// setters
template<class S> void MatriceDynamique<S>::setLignes(const unsigned int& i){n_lignes=i;}
template<class S> void MatriceDynamique<S>::setColones(const unsigned int& j){n_colonnes=j;}
template<class S> void MatriceDynamique<S>::setMat(const S* Mat) {mat=Mat;};
//surcharger operateur =
template<class S> 
MatriceDynamique<S>& MatriceDynamique<S>::operator=(const MatriceDynamique<S>& other){
    n_lignes=other.getLignes();
    n_colonnes=other.getColonnes();
    mat= new S[n_colonnes*n_lignes];
    for(int i=0;i<n_lignes*n_colonnes;i++)
        mat[i]=other.getMat()[i];
    return *this;
}
//surcharger operateur +
template<class S>
MatriceDynamique<S> operator+(const MatriceDynamique<S>& m1,const MatriceDynamique<S>& m2){
    MatriceDynamique<S> resultat(m1.getLignes(),m1.getColonnes(),0);
    try{
        if(!(m1.getLignes()==m2.getLignes() && m1.getLignes()==m2.getColonnes()))
            throw "Matrices incompatibles";
        for(int i=0;i<m1.getLignes()*m1.getColonnes();i++)
            resultat.mat[i]=m1.getMat()[i]+m2.getMat()[i];
        
    } catch(const char* m){
    cerr << m <<endl;
    }
    return resultat;
}
template<class S>
MatriceDynamique<S> operator+(const MatriceDynamique<S>& m,const S& scal){
    return MatriceDynamique<S>(m.getLignes(),m.getColonnes(),scal)+m;
}
template<class S>
MatriceDynamique<S> operator+(const S& scal,const MatriceDynamique<S>& m){return m+scal;}
// surcharger operateur <<
template<class S>
ostream& operator<<(ostream& out,const MatriceDynamique<S>& M){
    out<<"["<<endl;
    for(int i=0;i<M.getLignes();i++){
        out<<" [";
        for(int j=0;j<M.getColonnes();j++) 
            out<<M.getMat()[i+j]<<", ";
        out<<"],"<<endl;
    }
    out<<"]"<<endl;
    return out;
}


#endif