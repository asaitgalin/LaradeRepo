#include<iostream>
#include<set>
#include<deque>

int main()
{
	//freopen("C:\\temp\\in.txt", "r", stdin);
	std::multiset<int> set;
	std::deque<std::multiset<int>::iterator> deq;
	int k, num;
	std::cin >> k;
	for(size_t i=0; i < k-1; ++i)
	{
		std::cin >> num;
		deq.push_back(set.insert(num));
	}
	std::cin >> num;
	while(num != -1)
	{
		deq.push_back(set.insert(num));
		std::cout << (*set.rbegin()) << std::endl;
		set.erase(deq.front());
		deq.pop_front();
		std::cin >> num;
	}
	
	return 0;
}