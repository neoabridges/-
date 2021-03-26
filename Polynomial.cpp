#include<iostream>
using namespace std;
struct Monomial
{
    int coe = 0, exp = 0;
    bool operator <(Monomial mono)
    {
        return exp < mono.exp;
    }
    bool operator >(Monomial mono)
    {
        return exp > mono.exp;
    }
    bool eq(Monomial mono)
    {
        return exp == mono.exp;
    }
    Monomial operator +(Monomial mono)
    {
        Monomial new_mono;
        new_mono.exp = mono.exp;
        new_mono.coe = coe + mono.coe;
        return new_mono;
    }
    Monomial operator -(Monomial mono)
    {
        Monomial new_mono;
        new_mono.exp = mono.exp;
        new_mono.coe = coe - mono.coe;
        return new_mono;
    }
    Monomial operator *(Monomial mono)
    {
        Monomial new_mono;
        new_mono.exp = mono.exp + exp;
        new_mono.coe = coe * mono.coe;
        return new_mono;
    }
};
struct Node
{
    Monomial mono;
    void copy(Node* node)
    {
        this->mono = node->mono;
    }
    Node* next = NULL;
};
struct Polynomial 
{
    Node* head = NULL;
};

Node* InitNode(const char* str_head, const char* str_tail);
Polynomial InitPolynomial(const char *);
void PrintPolynomial(const Polynomial &);
Polynomial Add(const Polynomial &, const Polynomial &);
Polynomial Minus(const Polynomial &, const Polynomial &);
Polynomial Multiply(const Polynomial &, const Polynomial &);
Polynomial Power(const Polynomial &, int);
void InsertNode(Polynomial &, Node* node);
//  above are declarations

#include "test.hpp"

int main()
{
    test();
    return 0;
}

Polynomial Power(const Polynomial & Poly, int n)
{
    Polynomial NewPoly = Poly;
    while(n > 1){
        NewPoly = Multiply(NewPoly, Poly);
        n -= 1;
    }
    return NewPoly;
}

Polynomial Multiply(const Polynomial & Poly1, const Polynomial & Poly2)
{
    Polynomial NewPoly;
    for(Node* head1 = Poly1.head; head1; head1 = head1->next){
        for (Node* head2 = Poly2.head; head2; head2 = head2->next){
            Node* new_node = new Node;
            new_node->mono = head1->mono * head2->mono;
            InsertNode(NewPoly, new_node);
        }
    }
    return NewPoly;
}
Polynomial Minus(const Polynomial & Poly1, const Polynomial &Poly2)
{
    Polynomial NewPoly;
    Node* head2 = Poly2.head;
    Node* head1 = Poly1.head;
    while(head1){        
        Node* new_node = new Node;
        new_node->mono.coe = head1->mono.coe;
        new_node->mono.exp = head1->mono.exp;
        InsertNode(NewPoly, new_node);
        head1 = head1->next;
    }
    while(head2){
        Node* new_node = new Node;
        new_node->mono.coe = - head2->mono.coe;
        new_node->mono.exp = head2->mono.exp;
        InsertNode(NewPoly, new_node);
        head2 = head2->next;
    }
    return NewPoly;
}
Polynomial Add(const Polynomial & Poly1, const Polynomial & Poly2)
{
    Polynomial NewPoly;
    Node* head1 = Poly1.head;
    Node* head2 = Poly2.head;
    while(head1){
        Node* node = new Node;
        node->copy(head1);
        InsertNode(NewPoly, node);
        head1 = head1->next;
    }
    while(head2){
        Node* node = new Node;
        node->copy(head2);
        InsertNode(NewPoly, node);
        head2 = head2->next;
    }
    return NewPoly;
}

Polynomial InitPolynomial(const char* str)
{
    Polynomial Poly;
    const char* str_tail = str;
    while(*str){
        str_tail++;
        while(*str_tail != '+' && *str_tail != '-' && *str_tail){
            str_tail++;
        }
        str_tail--;
        InsertNode(Poly, InitNode(str, str_tail));
        str = ++str_tail;
    }
    return Poly;
}
void PrintPolynomial(const Polynomial & Poly)
{
    Node* head = Poly.head;
    while (head){
        if (head->mono.coe > 0){
            cout << '+' << head->mono.coe << "x^" << head->mono.exp;
        }
        else{
            cout << head->mono.coe << "x^" << head->mono.exp;
        }
        head = head->next;
    }
    cout << '\n';
}
Node* InitNode(const char* str_head, const char* str_tail)
{
    Node* new_node = new Node;
    Monomial mono;
    char sign = *str_head; //   get the sign
    mono.coe = *(++str_head) - '0';
    while (*(str_head + 1) != 'x'){
        str_head++;
        mono.coe = mono.coe * 10 + *str_head - '0';
    }
    str_head += 3;
    mono.exp = *str_head - '0';
    while(str_head != str_tail){
        str_head++;
        mono.exp = mono.exp * 10 + *str_head - '0';
    }
    if (sign == '-'){
        mono.coe *= -1;
    }
    new_node->mono = mono;
    return new_node;
}
void InsertNode(Polynomial & Poly, Node* node)
{
    if (node->mono.coe == 0){
        return;
    }
    if (! Poly.head){
        Poly.head = node;
    }
    else if (node->mono > Poly.head->mono){
        node->next = Poly.head;
        Poly.head = node;
    }
    else if (node->mono.eq(Poly.head->mono)){
        Poly.head->mono = node->mono + Poly.head->mono;
        if(Poly.head->mono.coe == 0){
            Poly.head = Poly.head->next;
        }
    }
    else{
        Node* head = Poly.head;
        bool has_inserted = false;
        while (head->next){
            if (node->mono < head->next->mono){
                head = head->next;
            }
            else if (node->mono.eq(head->next->mono)){
                head->next->mono = node->mono + head->next->mono;
                if (head->next->mono.coe == 0){
                    head->next = head->next->next;
                }
                has_inserted = true;
                break;
            }
            else{
                node->next = head->next;
                head->next = node;
                has_inserted = true;
                break;
            }
        }
        if (! has_inserted){
            head->next = node;
        }
    }
}