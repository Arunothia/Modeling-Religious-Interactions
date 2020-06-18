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

float mu01 = 0.1;
float mu02 = 0.5;
float mu11 = 0.25;
float mu12 = 0.75;
float sigma01 = 0.2;
float sigma02 = 0.2;
float sigma11 = 0.2;
float sigma12 = 0.3;

float mub1 = 0.8;
float mub2 = 0.6;
float sb1 = 0.5;
float sb2 = 0.5;


// Graph Variables

const int size = 286500;
int n, score[size];
bool strategy[size], religion[size];
int e[500][573];
float qc[size], qd[size];

// Strategy : 0 - Cooperate and 1 - Defect
// Religion : 0 - Sikh and 1 - Hindu

// Graph Input

void graph_input(){
	n = size;
	int row = 500;
	int col = 573;

	// When we model Sikh-Hindu using their population ratio in punjab

/*
	for(int i=0; i<size; i++){
		int v = rand()%100;
		if(v<35)
			religion[i] = 1;
		else
			religion[i] = 0;
		//cout<<religion[i]<<" ";
	}
*/
	//cout<<endl;

	// When we take everyone in the population to be of same religion



	for(int i=0; i<size; i++){
                religion[i] = 1;
        }


	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
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
                }
        }
	for(int i=0; i<n; i++){
                score[i] = 0;
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
	int neighbour[8];
	neighbour[0] = p-1;
	neighbour[1] = p-500;
	neighbour[2] = p-499;
	neighbour[3] = p-501;
	neighbour[4] = p+500;
	neighbour[5] = p+499;
	neighbour[6] = p+501;
	neighbour[7] = p+1;

	for(int k=0; k<8; k++){
		int i = neighbour[k];
		if(i<0 || i>=size)
                        continue;
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
	return s;
}

// Update the strategy of the pth player using their same religion neighbours.

void updateStrategy(int p){

	float maxScore = (float) INT_MIN;
	int player = p;
	
	int neighbour[8];
        neighbour[0] = p-1;
        neighbour[1] = p-500;
        neighbour[2] = p-499;
        neighbour[3] = p-501;
        neighbour[4] = p+500;
        neighbour[5] = p+499;
        neighbour[6] = p+501;
	neighbour[7] = p+1;
	
	for(int k=0; k<8; k++){
                int i = neighbour[k];
		if(i<0 || i>=size)
			continue;
                if(religion[i] == religion[p]){
			if(score[i] > maxScore){
				player = i;
				maxScore = score[i];
			}
                }
        }
	strategy[p] = strategy[player];
	return ;

}

int play(int t){
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
	
	int r=0;
	for(int i=0; i<n; i++){
		int neighbour[8];
        	neighbour[0] = i-1;
        	neighbour[1] = i-500;
        	neighbour[2] = i-499;
        	neighbour[3] = i-501;
        	neighbour[4] = i+500;
        	neighbour[5] = i+499;
        	neighbour[6] = i+501;
		neighbour[7] = i+1;

		
		for(int k=0; k<8; k++){
			int j = neighbour[k];
			if(j<0 || j>=size)
                        	continue;
			if(strategy[i] && strategy[j])
				r++;
		}
		//cout<<r<<" ";
	}
	//cout<<endl;
	return r;
					
}

int main(){
	srand (time(NULL));
	graph_input();
	int i=0;
	int sum=0;
	while(i<100){
		sum += play(100);	
		i++;
	}
	
	cout<<sum/100<<endl;
	return 0;
}
