#include <iostream>
#include <list>

using namespace std;

struct product{
	int id;
	int value;
	int rank;
	float sales;
	product(int id, int value, int rank, float sales) : id(id), value(value), rank(rank), sales(sales) {}
};

void impute(list<product> &myList, int k){
	list<int> valuesToAverage1;
	list<int> valuesToAverage2;
	for (list<product>::iterator iterator = myList.begin(), end = myList.end(); iterator != end; ++iterator) {
			int count = 0;
		    if(iterator->sales < 0){		//missing sales value detected
		    	cout<<"missing sales value detected"<<endl;
		    	for(float i = 1; i <= k; i++){		//find k-nearest neighbors upwards (sales > missing value)
		    		list<product>::iterator currIterator = iterator;
		    		if(iterator->rank > 1){		//prevents going out of bounds
		    			--iterator;
		    		}
		    		if(currIterator != iterator){
						valuesToAverage1.push_front(iterator->sales);
						count++;
		    		}
		    	}
		    	for(int i = 0; i < count; i++){		//return to the entry with the missing data point
		    		++iterator;
		    	}
		    	if(count < k){
		    		int temp = k;
		    		k = count;
		    		if(k == 0){
		    			++iterator;
		    			int temp = iterator->sales;
		    			--iterator;
		    			iterator->sales = temp;
		    			break;
		    		}
		    	}
		    	count = 0;
		    	for(float i = 1; i <= k; i++){		//find k-nearest neighbors DOWNWARDS (sales < missing value)
		    		list<product>::iterator currIterator = iterator;
		    		if(iterator == end){		//prevents going out of bounds
//		    			cout<<"END OF LIST"<<endl;
		    		}else{
		    			++iterator;
		    		}
		    		if(iterator != end && iterator->sales < 0){		//skip other missing values for now
		    			++iterator;
		    		}
		    		if(currIterator != iterator){
		    			if(iterator != end){
		    				valuesToAverage2.push_back(iterator->sales);
		    			}
						count++;
		    		}
		    	}
		    	for(int i = 0; i < count; i++){		//return to the entry with the missing data point
		    		--iterator;
		    	}
		    	while(valuesToAverage1.size() > valuesToAverage2.size()){		//if the list sizes differ, we must use the minimum number of nearest neighbors to prevent skew
		    		valuesToAverage1.pop_front();
		    	}
		    	valuesToAverage1.merge(valuesToAverage2);
		    	float newAve = 0;
		    	int newCount = 0;
		    	while(!valuesToAverage1.empty()){
		    		newAve = newAve + valuesToAverage1.front();
		    		valuesToAverage1.pop_front();
		    		newCount++;
		    	}
		    	if(newCount == 0){		//missing value has no nearest neighbor on the lower end
		    		--iterator;
		    		newAve = iterator->sales;
		    		++iterator;
		    		iterator->sales = newAve;
		    	}else{
		    	newAve = newAve / newCount;
		    	iterator->sales = newAve;
		    	}
		    	cout<<"Imputed sales number: "<<iterator->sales<<endl;
		    }
		}
}

int main(){
	int k = 3;
	list<product> myList;

	product *zero = new product(1435, 2, 1, 1500);
	product *one = new product(53451, 2, 2, 1250);
	product *two = new product(6256,3,3,1000);
	product *three = new product(355,4,4,-1);
	product *four = new product(879,5,5,500);
	product *five = new product(2311,5,6,250);
	product *six = new product(3424, 2, 7, 1);
	myList.push_back(*zero);
	myList.push_back(*one);
	myList.push_back(*two);
	myList.push_back(*three);
	myList.push_back(*four);
	myList.push_back(*five);
	myList.push_back(*six);

	cout<<"List of products' sales values BEFORE imputation: (negative values represent missing figures)"<<endl;
	for (list<product>::iterator iterator = myList.begin(), end = myList.end(); iterator != end; ++iterator) {
		cout<<iterator->sales<<endl;
	}
	cout<<endl;

	impute(myList, k);

	cout<<"\nList of products' sales values AFTER imputation: "<<endl;
	for (list<product>::iterator iterator = myList.begin(), end = myList.end(); iterator != end; ++iterator) {
		cout<<iterator->sales<<endl;
	}
	cout<<endl;
}









