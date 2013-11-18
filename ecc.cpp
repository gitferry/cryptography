#include <iostream>
using namespace std;


int p;
int a;
int flag = 0;

//明文
int m_x = 0;
int m_y = 0;

//密钥
int c1_x = 0;
int c1_y = 0;
int c2_x = 0;
int c2_y = 0;
int ky_x = 0;
int ky_y = 0;

int extend_gcd(int numer, int denom, int p)
{
    while(numer < 0)
    {
        numer += p;
    }
    while (denom < 0) {
        denom += p;
    }
	for(int i = 1; ;i++)
	{
		if(denom * i % p == numer)
			return i;
	}
}
void cal_c1(int k, int x1, int y1, int &x3, int &y3)
{
    if (k == 2)
    {
    	int numer = (3 * x1 * x1 + a) % p;
    	int denom = 2 * y1 % p;
		int lamda  = extend_gcd(numer, denom, p);
		x3 = (lamda * lamda - 2 * x1) % p;
		y3 = (lamda * (x1 - x3) - y1) % p;
        if(x3 < 0)
            x3 += p;
        if(y3 < 0)
            y3 += p;
		return;
    }
    else if(k > 2)
    {
        
    	int x2 = 0;
    	int y2 = 0;
    	cal_c1(k - 1, x1, y1, x2, y2);
        if(flag == 1)
            return;
        if(x1 == x2 && y1 + y2 == p)
        {
            flag = 1;
        }
        
    	int lamda;
        if(x1 != x2)
            lamda = extend_gcd((y2 - y1), (x2 - x1), p);
        else
            lamda = extend_gcd((3 * x1 * x1 + a) % p, 2 * y1 % p, p);
    	x3 = (lamda * lamda - x1 - x2) % p;
    	y3 = (lamda * (x1 - x3) - y1) % p;
        if(x3 < 0)
            x3 += p;
        if(y3 < 0)
            y3 += p;
        if(flag == 1)
        {
            c1_x = x3;
            c1_y = y3;
        }
    	return;
    }
}

void cal_ky(int k, int x1, int y1, int &x3, int &y3)
{
    if (k == 2)
    {
    	int numer = (3 * x1 * x1 + a) % p;
    	int denom = 2 * y1 % p;
		int lamda  = extend_gcd(numer, denom, p);
		x3 = (lamda * lamda - 2 * x1) % p;
		y3 = (lamda * (x1 - x3) - y1) % p;
        if(x3 < 0)
            x3 += p;
        if(y3 < 0)
            y3 += p;
		return;
    }
    else if(k > 2)
    {
        
    	int x2 = 0;
    	int y2 = 0;
    	cal_ky(k - 1, x1, y1, x2, y2);
        if(flag == 1)
            return;
        if(x1 == x2 && y1 + y2 == p)
        {
            flag = 1;
        }
        
    	int lamda;
        if(x1 != x2)
            lamda = extend_gcd((y2 - y1), (x2 - x1), p);
        else
            lamda = extend_gcd((3 * x1 * x1 + a) % p, 2 * y1 % p, p);
    	x3 = (lamda * lamda - x1 - x2) % p;
    	y3 = (lamda * (x1 - x3) - y1) % p;
        if(x3 < 0)
            x3 += p;
        if(y3 < 0)
            y3 += p;
        if(flag == 1)
        {
            ky_x = x3;
            ky_y = y3;
        }
    	return;
    }
}

void cal_c2(int x1, int y1, int x2, int y2, int &x3, int &y3)
{
    int lamda;
    if(x1 != x2)
        lamda = extend_gcd((y2 - y1), (x2 - x1), p);
    else
        lamda = extend_gcd((3 * x1 * x1 + a) % p, 2 * y1 % p, p);
    x3 = (lamda * lamda - x1 - x2) % p;
    y3 = (lamda * (x1 - x3) - y1) % p;
    if(x3 < 0)
        x3 += p;
    if(y3 < 0)
        y3 += p;

    c2_x = x3;
    c2_y = y3;
    return;
}
int main()
{
	int x3 = 0;
	int y3 = 0;
	int k = 13;
	int x1 = 10;
	int y1 = 5;
    
    
    //公钥y
    int y_x = 17;
    int y_y = 21;
    
    //明文
    m_x = 11;
    m_y = 1;
    
    flag = 0;
    p = 23;
    a = 13;
    
    //计算c1
	cal_c1(k, x1, y1, x3, y3);
    
    flag = 0;
    x3 = 0;
    y3 = 0;
    
    //计算ky
    cal_ky(k, y_x, y_y, x3, y3);
    
    //计算c2
    cal_c2(m_x, m_y, ky_x, ky_y, x3, y3);
	cout << "密文：" << "((" << c1_x << ", " << c1_y << "), (" << c2_x << ", " << c2_y << "))" << endl;
    return 0;
}
