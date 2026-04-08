#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// URL에서 사용할 수 있는 문자 판별
bool not_url_char(char c)
{
    static const string url_ch = "~;/?:@=&$-_.+!*'(),";

    return !(isalnum(c) ||
        find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
}

// URL의 끝 찾기
string::const_iterator url_end(string::const_iterator b,
    string::const_iterator e)
{
    return find_if(b, e, not_url_char);
}

// URL의 시작 찾기
string::const_iterator url_beg(string::const_iterator b,
    string::const_iterator e)
{
    static const string sep = "://";

    typedef string::const_iterator iter;
    iter i = b;

    while ((i = search(i, e, sep.begin(), sep.end())) != e) {
        // protocol의 시작 찾기
        if (i != b && i + sep.size() != e) {
            iter beg = i;

            // :// 앞쪽으로 이동하며 protocol 검사
            while (beg != b && isalpha(beg[-1]))
                --beg;

            // protocol이 비어있지 않으면 유효
            if (beg != i)
                return beg;
        }

        // 다음 위치로 이동
        if (i != e)
            i += sep.size();
    }
    return e;
}

// URL 추출 함수
vector<string> find_urls(const string& s)
{
    vector<string> ret;
    typedef string::const_iterator iter;
    iter b = s.begin(), e = s.end();

    while (b != e) {
        b = url_beg(b, e);
        if (b != e) {
            iter after = url_end(b, e);
            ret.push_back(string(b, after));
            b = after;
        }
    }
    return ret;
}

// 테스트용 main
int main()
{
    string text = "Visit https://example.com or http://google.com for info.";

    vector<string> urls = find_urls(text);

    for (const auto& url : urls) {
        cout << url << endl;
    }

    return 0;
}
