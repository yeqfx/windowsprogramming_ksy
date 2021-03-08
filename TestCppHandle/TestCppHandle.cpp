// TestCppHandle.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>

using namespace std;

typedef unsigned int HANDLE;

struct HandleData
{
    HANDLE h;
    char* p_string;
};

class HandleManager
{
private:
    unsigned int m_max_count, m_gen_value;
    HandleData* mp_data;

public:
    HandleManager(unsigned int a_max_count = 50)
    {
        m_gen_value = 1;
        m_max_count = a_max_count;
        mp_data = new HandleData[m_max_count];
        memset(mp_data, 0, sizeof(HandleData) * m_max_count);
        cout << "핸들 관리자가 생성되었습니다!" << endl;
    }

    ~HandleManager()
    {
        HandleData* p = mp_data;

        for (unsigned int i = 0; i < m_max_count; i++) {
            if (p->h) delete[] p->p_string;
            p++;
        }
        delete[] mp_data;
        cout << "핸들 관리자가 관리하던 문자열을 모두 제거했습니다!" << endl;
    }

    HANDLE InsertString(const char* ap_string)
    {
        HandleData* p = mp_data;
        unsigned int i;

        for (i = 0; i < m_max_count; i++) {
            if (p->h == 0) break;
            p++;
        }

        if (i < m_max_count) {
            p->h = m_gen_value++;
            int len = strlen(ap_string) + 1;
            p->p_string = new char[len];
            memcpy(p->p_string, ap_string, len);
            cout << p->p_string << " : 문자열 추가!!" << endl;
            return p->h;
        }

        cout << "더 이상 문자열을 추가할 수 없습니다!!" << endl;
        return 0xFFFFFFFF;
    }

    void PrintString(HANDLE ah_string)
    {
        HandleData* p = mp_data;

        for (unsigned int i = 0; i < m_max_count; i++) {
            if (p->h == ah_string) {
                cout << p->p_string << endl;
                return;
            }
            p++;
        }
        cout << "유효하지 않은 핸들값을 사용했습니다!" << endl;
    }

    void DeleteString(HANDLE ah_string)
    {
        HandleData* p = mp_data;

        for (unsigned int i = 0; i < m_max_count; i++) {
            if (p->h == ah_string) {
                cout << p->p_string << " : 삭제!!" << endl;
                delete[] p->p_string;
                p->h = 0;
                return;
            }
            p++;
        }
        cout << "유효하지 않은 핸들값을 사용했습니다!!" << endl;
    }
};

int main()
{
    HandleManager str_list;

    HANDLE h_str = str_list.InsertString("Hello World!!");
    cout << "문자열 생성 후 h_str의 핸들값 : " << h_str << endl;
    str_list.PrintString(h_str);
    str_list.DeleteString(h_str);
    cout << "문자열 삭제 후 h_str의 핸들값 : " << h_str << " : 핸들값은 남아 있으나 핸들 관리자가 갖고 있는 핸들값은 없어서 유효하지 않다." << endl;
    str_list.PrintString(h_str);

    /*char* p = new char[32];

    strcpy_s(p, 32, "Hello World!!");
    cout << p << endl;

    delete[] p;*/
    return 0;
}
