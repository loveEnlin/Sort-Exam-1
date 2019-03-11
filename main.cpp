#include "main.hpp"

long long Element::cmp_count{0};
long long Element::set_count{0};
std::ifstream Element::ifs(data_file,std::ifstream::in|std::ifstream::binary);
std::vector<Element> Element::data;
char Element::data_length{0};
int Element::times{0};

bool Element::operator<=(const Element& another) const{
	++cmp_count;
	return value<=another.value;
}

bool Element::operator>=(const Element& another) const{
	++cmp_count;
	return value>=another.value;
}

bool Element::operator<(const Element& another) const{
	++cmp_count;
	return value<another.value;
}

bool Element::operator>(const Element& another) const{
	++cmp_count;
	return value>another.value;
}

char Element::operator=(const Element& another){
	++set_count;
	value=another.value;
	return value;
}

char Element::operator=(const char& another){
	++set_count;
	value=another;
	return value;
}

char operator=(char& another,Element& one){
	++set_count;
	another=one.value;
	return another
}

void Element::init(){
	cmp_count=0;
	set_count=0;
	data.clear();
	data_length=0;
}

void Element::swap(Element& first,Element& second){
	Element third=first;
	first=second;
	second=third;
}

bool Element::is_sorted(){
	std::vector<Element>::const_iterator i{data.begin()+1};
	while(i != data.end()){
		if(*i<*(i-1)){
			return false;
		}
		++i;
	}
	return true;
}

bool Element::input(){
	init();
	++times;
	ifs.get(data_length);
	std::cout<<"Times="<<times<<",Data Length="<<static_cast<int>(data_length)<<",Data Size="<<(1<<static_cast<long long>(data_length))<<std::endl;
	if(data_length==0) return false;//If data_length==0 means no data left
	for(int i{1<<static_cast<long long>(data_length)};i>0;--i){
		char x;
		ifs.get(x);
		Element tmp=x;
		data.push_back(tmp);//Get the number from data_file and push into the vector of Elements
	}
	return true;
}

void Element::output(){
	std::ofstream ofs("../log/"+sort_name+"_"+log_file, std::ofstream::out|std::ofstream::app);
	ofs<<'|'<<sort_name<<'|'<<times<<'|'<<"2<sup>"<<static_cast<int>(data_length)<<"</sup>"<<'|'<<cmp_count<<'|'<<set_count<<'|'<<std::endl;
	ofs.close();
}

Element::Element(const char& another){
	value=another;
}

int main(){
	while(Element::input()){
		Element::sort_method();
		if(!(Element::is_sorted())) std::cout<<"Isn't sorted at Times "<<Element::times<<std::endl<<std::endl;
		Element::output();
	}
	return 0;
}