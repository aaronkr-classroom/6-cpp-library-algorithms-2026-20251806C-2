//palindrome.cpp
#include<iostream>
#include<string>
#include<algorithm> //equal() 두 문자열이 같으면 true qksghks

using namespace std;

bool is_palindrome(const string& s) {
	return equal(s.begin(), s.end(), s.rbegin());
}

int main(void) {
	string s;
	while (cin >> s) {
		if (is_palindrome(s))
			cout << s << "은/는 회문입니다!~~" << endl;
		else
			cout << s << "은/는 회문이 아닙니다.ㅠㅠ" << endl;
	}
	return 0;
}
