#include<bits/stdc++.h>
#include<random>
using namespace std;

// PD Parameters

#define a 3
#define b 6
#define c 1
#define d 5

// Belief Parameters

float epsilon[] = {7,5}; 

float mu01 = 0.4;
float mu02 = 0.6;
float mu11 = 0.25;
float mu12 = 0.75;
float sigma01 = 0.8;
float sigma02 = 0.7;
float sigma11 = 0.2;
float sigma12 = 0.3;

float mub1 = 0.7;
float mub2 = 0.6;
float sb1 = 0.5;
float sb2 = 0.5;


// Graph Variables

const int size = 108;
int n, score[size];
bool e[size][size], strategy[size], religion[size];
float qc[size], qd[size];

// Strategy : 0 - Cooperate and 1 - Defect
// Religion : 0 - Islam and 1 - Hindu

// Graph Input

void graph_input(){

	cin>>n;
	for(int i=0; i<n; i++){
		cin >> religion[i];
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin >> e[i][j];
			//cout<<e[i][j]<<" ";
		}
		//cout<<endl;
	}
}

void set_parameters(){
	
	default_random_engine generator(time(0));
        normal_distribution<float> distribution01(mu01,sigma01);
	normal_distribution<float> distribution02(mu02,sigma02);
	normal_distribution<float> distribution11(mu11,sigma11);
        normal_distribution<float> distribution12(mu12,sigma12);

	normal_distribution<float> b1(mub1,sb1);
        normal_distribution<float> b2(mub2,sb2);

	
	/*
	float M01 = mu01 + 3*sigma01;
	float m01 = mu01 - 3*sigma01;
	float M02 = mu02 + 3*sigma02;
        float m02 = mu02 - 3*sigma02;
	float M11 = mu11 + 3*sigma11;
        float m11 = mu11 - 3*sigma11;
	float M12 = mu12 + 3*sigma12;
        float m12 = mu12 - 3*sigma12;

	cout<<M01<<" "<<m01<<" "<<M02<<" "<<m02<<" "<<M11<<" "<<m11<<" "<<M12<<" "<<m12<<"\n";
	for(int i=0; i<n; i++){
		if(religion[i] == 0){
			qc[i] = (distribution01(generator) - m01)/(M01 - m01);
			qd[i] = (distribution02(generator) - m02)/(M02 - m02);
		}
		else{
                        qc[i] = (distribution11(generator) - m11)/(M11 - m11);
                        qd[i] = (distribution12(generator) - m12)/(M12 - m12);
                }
	} 
	for(int i=0; i<n; i++){
		cin>>qc[i];
	}
	for(int i=0; i<n; i++){
                cin>>qd[i];
        }
	*/
	for(int i=0; i<n; i++){
                if(religion[i] == 0){
                        qc[i] = distribution01(generator);
			while(qc[i] < 0 || qc[i] >1){
				qc[i] = distribution01(generator);
			}
                        qd[i] = distribution02(generator);
                        while(qd[i] < 0 || qd[i] >1){
                                qd[i] = distribution02(generator);
                        }
			/*
			qc[i] = 0.5;
			qd[i] = 0.5;
			*/
                }
                else{
			qc[i] = distribution11(generator);
                        while(qc[i] < 0 || qc[i] >1){
                                qc[i] = distribution11(generator);
                        }
                        qd[i] = distribution12(generator);
                        while(qd[i] < 0 || qd[i] >1){
                                qd[i] = distribution12(generator);
                        }
			/*
			qc[i] = 0.25;
			qd[i] = 0.75;
			*/
                }
        }
	for(int i=0; i<n; i++){
                score[i] = 0;
                //cin >> strategy[i];
                //strategy[i] = rand() %2;
		if(religion[i] == 0){
			float vb1 = b1(generator);
			while(vb1 < 0 || vb1 >1)
				vb1 = b1(generator);
			float sc = vb1 * (d + epsilon[0] * (1 - 2*qc[i])) + (1 - vb1) * (c + epsilon[0] * (1 - 2*qc[i]));
			float sd = vb1 * (b + epsilon[0] * (1 - 2*qd[i])) + (1 - vb1) * (a + epsilon[0] * (1 - 2*qd[i]));
			if(sc > sd)
				strategy[i] = 0;
			else
				strategy[i] = 1;
		}
		else{
			float vb2 = b2(generator);
                        while(vb2 < 0 || vb2 >1)
                                vb2 = b2(generator);
                        float sc = vb2 * (d + epsilon[1] * (1 - 2*qc[i])) + (1 - vb2) * (c + epsilon[1] * (1 - 2*qc[i]));
                        float sd = vb2 * (b + epsilon[1] * (1 - 2*qd[i])) + (1 - vb2) * (a + epsilon[1] * (1 - 2*qd[i]));
                        if(sc > sd)
                                strategy[i] = 0;
                        else
                                strategy[i] = 1;
		}
        }
	/*
	for(int i=0; i<n; i++)
		cout<<qc[i]<<" ";
	cout<<endl;
	for(int i=0; i<n; i++)
		cout<<qd[i]<<" ";
	cout<<endl;
	cout<<"**********\n";
	for(int i=0; i<n; i++)
		cout<<strategy[i]<<" ";
	cout<<endl; 
	*/
}

// Estimate pay-off for player 'p' 

float payOff(int p){
	
	float s = 0;
	for(int i=0; i<n; i++){
		if(e[i][p]){
			if(religion[i] != religion[p]){
				switch(strategy[p]){
					case 0: if(strategy[i] == 0){
							s += d + epsilon[religion[p]] * (1 - 2*qc[p]);
						}
						else{
							s += c + epsilon[religion[p]] * (1 - 2*qc[p]);
						}
						break;
					case 1: if(strategy[i] == 0){
                                                        s += b + epsilon[religion[p]] * (1 - 2*qd[p]);
                                                }
                                                else{
                                                        s += a + epsilon[religion[p]] * (1 - 2*qd[p]);     
                                                }
                                                break;	
				}
			}
		}
	}	
	return s;
}

// Update the strategy of the pth player using their same religion neighbours.

void updateStrategy(int p){

	float maxScore = (float) INT_MIN;
	int player = p;
	for(int i=0; i<n; i++){
                if(e[i][p]){
                        if(religion[i] == religion[p]){
				if(score[i] > maxScore){
					player = i;
					maxScore = score[i];
				}
                        }
                }
        }
	strategy[p] = strategy[player];
	return ;

}

static int s[10];

void play(int t){
	set_parameters();
	while(t--){
		for(int i=0; i<n; i++){
			score[i] = payOff(i);
		}
		for(int i=0; i<n; i++){
			updateStrategy(i);
		}
	}
	/*
	for(int i=0; i<n; i++)
		cout<<strategy[i]<<" ";

	cout<<endl;
	*/

	// The following code is specific to UP-data for estimation of D-D links count.
	
	int k=0;
	for(int i=0; i<n; i +=10){
		int r=0;
		for(int j=i; j<i+10 && j<n; j++){
			for(int k=0; k<n; k++){
				if(e[k][j] && strategy[k] && strategy[j])
					r++;
				//cout<<e[k][j]<<strategy[k]<<strategy[j]<<endl;
			}
		}
		s[k] +=r;
		cout<<s[k]<<" ";
		k++;
	}
	cout<<endl;
					
}

int main(){
	//srand (time(NULL));
	graph_input();
	int i=0;
	for(int i=0; i<9; i++)
		s[i] = 0;
	while(i<1000){
		play(10000);	
		i++;
	}
	for(int i=0; i<9; i++)
		cout<<s[i]/1000<<" ";
	cout<<endl;
	return 0;
}
