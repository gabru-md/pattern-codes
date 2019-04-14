#include<bits/stdc++.h>
using namespace std;
class Point
{
private:
    int val;
    float x;
    float y;
    float distance;
public:
    Point(int val, float x, float y) {
        this->val = val;
        this->x = x;
        this->y = y;
    }
    float getDistance() {
        return this->distance;
    }
    int getVal() {
        return this->val;
    }
    float getX() {
        return this->x;
    }
    float getY() {
        return this->y;
    }
    void calcDistance(Point *p) {
        this->distance = sqrt(
            (p->getX() - this->x ) * (p->getX() - this->x )
            +
            (p->getY() - this->y) *  (p->getY() - this->y)
        );
    }
};

bool compare(Point * p1, Point * p2) {
    return p1->getDistance() < p2->getDistance();
}

int main() {
    int n_samples, k, n_classes;
    cout<<"Enter number of samples: ";
    cin>>n_samples;
    cout<<"Enter number of classes: ";
    cin>>n_classes;
    cout<<"Enter k value: ";
    cin>>k;

    vector<Point *> _pVec;

    for(int i=0;i<n_samples;i++) {
        float x,y;
        int val;
        cout<<"Enter 'x', 'y' and 'val' for point "<< i+1<< ": \n";
        cin>>x>>y>>val;
        Point * _p = new Point(static_cast<int>(val), static_cast<float>(x), static_cast<float>(y));
        _pVec.push_back(_p);
    }
    cout<<"\nEnter the point to be predicted:\n";
    float _x,_y;
    int _val = -1;
    cin>>_x>>_y;
    Point * _predict = new Point(static_cast<int>(_val), static_cast<float>(_x), static_cast<float>(_y));
    for(int i=0;i<n_samples;i++) {
        _pVec[i]->calcDistance(_predict);
    }

    sort(_pVec.begin(), _pVec.end(), compare);

    // for(int i=0;i<n_samples;i++) {
    //     cout<<_pVec[i]->getDistance()<<" ";
    // }

    vector<int> _fRes(n_classes, 0);
    for(int i=0;i<k;i++) {
        _fRes[_pVec[i]->getVal()]++;
    }
    int _m_s = INT_MIN;
    int _res = -1;
    for(int i=0;i<n_classes;i++) {
        if(_fRes[i] > _m_s) {
            _m_s = _fRes[i];
            _res = i;
        }
    }

    cout<<"Resulting Prediction is:\n Point belongs to Class "<<_res<<"\n";
    return 0;
}