#include<bits/stdc++.h>
using namespace std;
float error(float predicted, float expected) {
    return static_cast<float>( abs(predicted*predicted - expected*expected) );
}
float loss(float predicted, float expected) {
    return 1/exp(-1*error(predicted, expected));
}
int main() {
    srand(time(NULL));
    float expected = ceilf(static_cast<float>( ((double)rand() / RAND_MAX))*100)/100;
    float predicted = ceilf(static_cast<float>( ((double)rand() / RAND_MAX))*100)/100;
    while(predicted >= expected) {
        predicted = ceilf(static_cast<float>( ((double)rand() / RAND_MAX))*100)/100;
    }
    for(float _pred=predicted; _pred<=expected+(expected-predicted);) {
        cout<<"Loss for "<<_pred<<" : "<<loss(_pred, expected)<<endl;
        _pred = ceilf((_pred + 0.01)*100)/100;
    }
    return 0;
}