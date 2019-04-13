#include<bits/stdc++.h>
using namespace std;
int main() {
    int n_features, n_samples, n_classes;
    cout<<"Enter number of features: ";
    cin>>n_features;
    cout<<"Enter number of samples: ";
    cin>>n_samples;
    cout<<"Enter number of classes: ";
    cin>>n_classes;

    map<string, vector<string> > features;
    vector<pair<string, string> > predict;

    for(unsigned int i=0;i<n_features;i++) {
        string feature;
        vector<string> vec;
        cout<<"Enter feature "<<i+1<<":\n";
        cin>>feature;
        cout<<"For feature '"<<feature<<"' enter the "<<n_samples<<" values:\n";
        for(unsigned int i=0;i<n_samples;i++) {
            string feature_val;
            cin>>feature_val;
            vec.push_back(feature_val);
        }

        features.insert(
            make_pair(feature, vec)
        );

        predict.push_back(
            make_pair(feature, "")
        );
    }
    
    vector<string> result;

    vector<string> classes;
    cout<<"Enter the "<<n_classes<<" classes:\n";
    for(unsigned int i=0;i<n_classes;i++) {
        string _class;
        cin>>_class;
        classes.push_back(_class);
    }

    cout<<"Target value for "<<n_samples<<" samples:\n";
    for(unsigned int i=0;i<n_samples;i++) {
        string res;
        cin>>res;
        result.push_back(res);
    }


    map<string, float> probs;
    for(map<string, vector<string> >::const_iterator ptr = features.begin();
        ptr != features.end(); ptr++) {
            set<string> s;
            for(unsigned int i=0;i<ptr->second.size();i++) {
                s.insert(ptr->second[i]);
            }

            for(unsigned int i=0; i<n_classes;i++){
                int tot_count = 0;
                vector<pair<string, float> > t_vec;
                for(set<string>::const_iterator it = s.begin(); it!=s.end();it++) {
                    string prob = classes[i] + "/"  + ptr->first + "=" + *it;
                    int _count = 0;
                    for(unsigned int j=0;j<ptr->second.size();j++) {
                        if(result[j] == classes[i]) {
                            if(ptr->second[j] == *it)
                                _count++;
                        }
                    }
                    tot_count += _count;
                    t_vec.push_back(make_pair(prob, _count+1));
                }
                for(unsigned int tt=0;tt<t_vec.size();tt++) {
                    probs.insert(
                        make_pair(t_vec[tt].first, static_cast<float>(t_vec[tt].second/(tot_count+1)))
                    );
                }
            }
            
    }


    // cout<<"\n\nProbabilities are: \n\n";
    // for(map<string, float >::const_iterator ptr = probs.begin();
    //     ptr != probs.end(); ptr++) {
    //         cout<<ptr->first<<" : "<<ptr->second<<endl;
    // }

    cout<<"\nEnter Prediction Values: \n";

    for(unsigned int i=0;i<predict.size();i++) {
        string state;
        cout<<"State of feature '"<<predict[i].first<<"' : ";
        cin>>state;
        predict[i].second = state;
    }

    vector<pair<string, float> > res_prob;

    for(unsigned int i=0;i<n_classes;i++) {
        vector<float> _tvec;
        for(unsigned int j=0;j<predict.size();j++){
            string prob = classes[i] + "/"  + predict[j].first + "=" + predict[j].second;
            map<string, float>::const_iterator got = probs.find(prob);
            if(got == probs.end()) {
                cout<<"error\n";
            }else {
                _tvec.push_back(got->second);
            }
        }
        float _res = 1.0;
        for(unsigned int k=0;k<_tvec.size();k++) {
            _res *= _tvec[k];
        }
        res_prob.push_back(
            make_pair(classes[i], _res)
        );
    }

    cout<<"\n\n------------------Final Predictions------------------\n\n";
    for(unsigned int i=0;i<res_prob.size();i++) {
        cout<<res_prob[i].first<<" : "<<res_prob[i].second<<endl;
    }
    cout<<"\n\n-----------------------------------------------------\n\n";

    return 0;
}