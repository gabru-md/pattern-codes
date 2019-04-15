#include<iostream>
using namespace std;
class m_prob
{
private:
    float pi;
    float m;
    float n;
    float t;
public:
    m_prob(float m, float pi);
    float calculate(float n, float t);
    float _calc() {
        return (this->n + this->m*this->pi)/(this->t + this->m);
    }

};

m_prob::m_prob(float m, float pi) {
    this->m = m;
    this->pi = pi;
}

float m_prob::calculate(float m, float t) {
    this->n = n;
    this->t = t;

    return this->_calc();
        
}

int main() {
    float m, pi, n, t;
    cout<<"Enter 'm', 'pi', 'n', 't':\n";
    cin>>m>>pi>>n>>t;
    m_prob * prob = new m_prob(m, pi);
    cout<<prob->calculate(n, t)<<"\n";
    return 0;
}