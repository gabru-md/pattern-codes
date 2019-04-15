#include<bits/stdc++.h>
using namespace std;
vector<string> _vectorize(string sample) {
    vector<string> _vStr;
    string _s = "";
    for(int i=0;i<sample.size();i++) {
        if(sample[i] == ' ') {
            _vStr.push_back(_s);
            _s = "";
        }
        else {
            _s.push_back(sample[i]);
        }
    }
    _vStr.push_back(_s);
    return _vStr;
}
int main() {
    vector<pair<vector<string> , string> > _sample;
    set<string> vocab;
    int n_samples, n_classes;
    set<string> _classes;


    n_samples = 5;
    n_classes = 2;


    float min_prob = static_cast<float>(INT_MAX);

    map<string, int> _count;

    for(unsigned int i=0;i<n_samples;i++) {
        string sample, target;
        cout<<"Enter sample "<<i+1<<" : ";
        getline(cin, sample);
        cout<<"Enter the target: ";
        getline(cin, target);

        vector<string> _sVec = _vectorize(sample);
        _sample.push_back(
            make_pair(
                _sVec,
                target
            )
        );
        for(unsigned int j=0;j<_sVec.size();j++) {
            vocab.insert(_sVec[j]);
            map<string, int>::iterator it = _count.find(_sVec[j]);
            if(it != _count.end()) {
                it->second = it->second + 1;
            }else {
                _count.insert(
                    make_pair(
                        _sVec[j],
                        1
                    )
                );
            }
        }
        _classes.insert(target);
    }

    assert(_classes.size() == n_classes);
    assert(_sample.size() == n_samples);

    map<string, float> probs;
    vector<pair<string, vector<string> > > _map;

    for(set<string>::const_iterator it=_classes.begin(); it!=_classes.end();it++) {
        string _cl = *it;
        vector<string> _vStr;
        for(unsigned int i=0;i<_sample.size();i++) {
            if(_sample[i].second == _cl) {
                for(unsigned int j=0;j<_sample[i].first.size();j++) {
                    _vStr.push_back(_sample[i].first[j]);
                }
            }
        }
        _map.push_back(
            make_pair(
                _cl,
                _vStr
            )
        );
    }

    
    for(unsigned int i=0;i<_map.size();i++) {
        //cout<<"Class '"<<_map[i].first<<"' :\n";
        for(set<string>::const_iterator it = vocab.begin(); it!=vocab.end();it++) {
            string _probStr = _map[i].first + "/" + *it;
            map<string, int>::iterator mIt = _count.find(*it);
            float tot_count = static_cast<float>(mIt->second);
            float giv_count = static_cast<float>(count(_map[i].second.begin(), _map[i].second.end(), *it));
            float __prob = (giv_count + 1)/(tot_count + 1);
            probs.insert(
                make_pair(
                    _probStr,
                    __prob
                )
            );
            if(min_prob > __prob) {
                min_prob = __prob;
            }
        }
    }

    string _predict_str;
    cout<<"\nEnter the string to predict:";
    getline(cin, _predict_str);
    vector<string> _preVec = _vectorize(_predict_str);
    float _res = 1.0;
    vector<pair<string, float> > _resVec;
    for(set<string>::const_iterator it = _classes.begin(); it!=_classes.end();it++) {
        _res = 1.0;
        for(unsigned int i=0;i<_preVec.size();i++) {
            string __probStr = *it + "/" + _preVec[i];
            map<string, float>::const_iterator mIt = probs.find(__probStr);
            if(mIt != probs.end()) {
                _res *= mIt->second;
            }else {
                _res *= min_prob;
            }
        }
        _resVec.push_back(
            make_pair(
                *it,
                _res
            )
        );
    }
    cout<<"\nResults:\n";
    for(unsigned int i=0;i<_resVec.size();i++) {
        cout<<_resVec[i].first<<" : "<<_resVec[i].second<<endl;
    }

    return 0;
}