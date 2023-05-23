#include<iostream>

bool is_DIN(){
	return false;
}

int main(){
	if(!is_DIN()){
		std::cout<<"false\n";
	}
	else{
		std::cout<<"true\n";
	}
	return 0;
}
