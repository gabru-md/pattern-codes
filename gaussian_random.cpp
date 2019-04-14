#include<bits/stdc++.h>
using namespace std;
class gaussian_random
{
private:
    float mu;
    float sigma;
    float pi;
public:
    gaussian_random(float, float);
    float generate(float);
};

gaussian_random::gaussian_random(float mu, float sigma){
    this->mu = mu;
    this->sigma = sigma;
    this->pi = 3.14;
}

float gaussian_random::generate(float x) {
    float _res;
    float _sup = -( (static_cast<float>(x) - this->mu) * (static_cast<float>(x) - this->mu) ) / (2 * this->sigma * this->sigma);
    float _frac = 1/sqrt(2 * this->pi * this->sigma * this->sigma);

    return static_cast<float>(_frac*exp(_sup));
}

int main() {
    float mu, sigma;
    int n;
    cout<<"Enter 'mu' and 'sigma':\n";
    cin>>mu>>sigma;
    cout<<"Enter the number of points to be generated(odd):\n";
    cin>>n;
    n = n/2;

    gaussian_random * Gauss = new gaussian_random(mu, sigma);
    vector<float> _res;
    for(int i=-n;i<=n;i++) {
        _res.push_back(Gauss->generate(i));
    }

    cout<<"Generated Random numbers are:\n";
    for(int i=0;i<_res.size();i++) {
        cout<<"("<<i-n<<", "<<_res[i]<<")\n";
    }
    cout<<endl;
    return 0;
}