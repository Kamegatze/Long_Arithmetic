#include <iostream>
#include <string>
#include <math.h>
#include <vector>

const long digit = 20;

using namespace std;

vector<short> MultiplicationKarazuba(vector<short> a, vector<short> b);
short ConvertionFromSimbolToNumber(char a);
char ConvertionFromNumberToSimbol(short a);
vector<short> Addtion(vector<short> a, vector<short> b);
vector<short> ConvertFromMassSimbolToMassValue(string a);
string ConvertFromMassValueToMassSimbol(vector<short>a);
vector<short> Subtruction(vector<short> a, vector<short> b);
vector<short> Multiplication(vector<short> a, vector<short> b);
int Digits(int x);
string ConvertVectorToString(vector<char>a);
vector<short> ReverseVector(vector<short> a);
vector<short> TruncationOfZeros(vector<short> a);



int main()
{
    vector<short>a{ 1, 2, 3, 7 };
    vector<short>b{ 1, 2, 3, 4 };
    vector<short> res = MultiplicationKarazuba(a, b);
    for (auto i = 0; i < size(res); i++)
        cout << res.at(i) << " ";
}
vector<short> Multiplication(vector<short> a, vector<short> b)
{
    a = ReverseVector(a);
    b = ReverseVector(b);
    vector<short> MassA(size(a) + 1);
    vector<short> MassB(size(b) + 1);
    for (auto i = 0; i < size(a); i++)
        MassA.at(i) = a.at(i);
    for (auto i = 0; i < size(b); i++)
        MassB.at(i) = b.at(i);
    vector<short>MassC(size(a)*2);
    char carry = 0;
    if (size(a) > size(b))
    {
        for (auto i = 0; i < size(a); i++)
        {
            for (auto j = 0; j < size(MassA); j++)
            {
                MassC[i + j] += MassA[i] * MassB[j] + carry;
                carry = MassC[i + j] / 10;
                MassC[i + j] = MassC[i + j] % 10;
            }
        }
    }
    else
    {
        for (auto i = 0; i < size(b); i++)
        {
            MassC.at(i + 1) += carry;
            carry = 0;
            for (auto j = 0; j < size(b) + 1; j++)
            {
                MassC[i + j] += MassA[i] * MassB[j] + carry;
                carry = MassC[i + j] / 10;
                MassC[i + j] = MassC[i + j] % 10;
            }
        }
    }
    return TruncationOfZeros(ReverseVector(MassC));
  
}
vector<short> Subtruction(vector<short> a, vector<short> b)
{
    auto carry = 0;
    a = ReverseVector(a);
    b = ReverseVector(b);
    if (size(a) >= size(b))
    {
        if (a[size(a) - 1] < b[size(b) - 1] && size(a) == size(b))
        {
            vector<short>MassC(1, 0);
            return MassC;
        }

        for (auto i = 0; i < size(b); i++)
        {
            if (a[i] < b[i])
            {
                a[i] = (a[i] + 10) - b[i] - carry;
                carry = 1;
            }
            else
            {
                a[i] = a[i] - b[i] - carry;
                carry = 0;
            }
        }
        for (auto i = 0; i < size(a); i++)
        {
            if (a[i] < 0)
            {
                for (auto i = 0; i < size(a); i++)
                {
                    a[i] = 0;
                }
            }
        }
        return TruncationOfZeros(ReverseVector(a));
    }
    else
    {
        a = { 0 };
        return TruncationOfZeros(ReverseVector(a));
    }
}
vector<short> Addtion(vector<short> a, vector<short> b)
{
    char carry = 0;
    vector<short>MassC(size(a) * size(b), 0);
    vector<short> MassA(size(a) + 1);
    vector<short> MassB(size(b) + 1);
    if (size(b) > size(a))
    {
        vector<short> c = b;
        a = ReverseVector(b);
        b = ReverseVector(c);
        auto iter = a.begin();
        for (auto i = 0; i < size(a); i++)
        {
            MassA.at(i) = *iter;
            iter++;
        }
        iter = b.begin();
        for (auto i = 0; i < size(b); i++)
        {
            MassA.at(i) = *iter;
            iter++;
        }
    }
    else if (size(b) < size(a))
    {
        a = ReverseVector(a);
        b = ReverseVector(b);
        auto iter = a.begin();
        for (auto i = 0; i < size(a); i++)
        {
            MassA.at(i) = *iter;
            iter++;
        }
        iter = b.begin();
        for (auto i = 0; i < size(b); i++)
        {
            MassA.at(i) = *iter;
            iter++;
        }
    }
    else
    {
        a = ReverseVector(a);
        b = ReverseVector(b);
        auto iter = a.begin();
        for (auto i = 0; i < size(a); i++)
        {
            MassA.at(i) = *iter;
            iter++;
        }
        iter = b.begin();
        for (auto i = 0; i < size(b); i++)
        {
            MassB.at(i) = *iter;
            iter++;
        }
    }
    for (int i = 0; i < size(a) + 1; ++i)
    {
        MassC.at(i) = MassA.at(i) + MassB.at(i) + carry;
        carry = MassC.at(i) / 10;
        MassC.at(i) = MassC.at(i) % 10;
    }
    
    return TruncationOfZeros(ReverseVector(MassC));
}
vector<short> ConvertFromMassSimbolToMassValue(string a)
{
    vector<short>mass(size(a) + 1, 0);
    for (int i = 0; i < size(a); i++)
    {
        mass[i] = ConvertionFromSimbolToNumber(a[i]);
    }
    short temp = 0;
    for (int i = 0, j = size(a)-1; i < size(a) / 2; i++, j--)
    {
        temp = mass[i];
        mass[i] = mass[j];
        mass[j] = temp;
    }
    return mass;
}
string ConvertFromMassValueToMassSimbol(vector<short>a)
{
    vector<char>mass(a.size() + 1, 0);
    for (int i = 0; i < a.size(); i++)
    {
        mass[i] = ConvertionFromNumberToSimbol(a[i]);
    }
    char temp;
    for (int i = 0, j = a.size() - 1; i < a.size() / 2; i++, j--)
    {
        temp = mass[i];
        mass[i] = mass[j];
        mass[j] = temp;
    }
    mass[a.size()] = '\0';
    string res = ConvertVectorToString(mass);
    return res;
}
vector<short> MultiplicationKarazuba(vector<short> a, vector<short> b)
{
    vector<short>MassC(size(a)*size(b), 0);
    int n = min(size(a), size(b));
    int nHalf = floor(n / 2);
    vector<short>MassA1(nHalf);
    auto iter = a.begin();
    for (auto i = 0; i < nHalf; i++)
    {
        MassA1.at(i) = *iter;
        iter++;
    }
    vector<short>MassA0(nHalf);
    iter = a.end() - 1;
    for(auto i = nHalf - 1; i >= 0; i--)
    {
        MassA0.at(i) = *iter;
        iter--;
    }
    vector<short>MassB1(nHalf);
    iter =b.begin();
    for (auto i = 0; i < nHalf; i++)
    {
        MassB1.at(i) = *iter;
        iter++;
    }
    vector<short>MassB0(nHalf);
    iter = b.end() - 1;
    for (auto i = nHalf - 1; i >= 0; i--)
    {
        MassB0.at(i) = *iter;
        iter--;
    }
    vector<short> Y = Multiplication(MassA0, MassA1);
    vector<short> Z = Multiplication(MassB0, MassB1);
    vector<short> X = Multiplication(Addtion(MassA0, MassA1), Addtion(MassB0, MassB1));
    vector<short> X1 = Subtruction(Subtruction(X, Z),Y);
    vector<short> N(n + 1);
    N.at(0) = 1;
    vector<short> Nhalf(nHalf + 1);
    Nhalf.at(0) = 1;
    vector<short> res = Addtion(Addtion(Multiplication(Y, N), Multiplication(X1, Nhalf)), Z);
    return res;
    /*
    if (a < 10 || b < 10)
    {
        return a * b;
    }
    int m = min(Digits(a), Digits(b));
    m = floor(m / 2);
    int a0 = a / pow(10, m);
    int a1 = a % (int)pow(10, m);
    int b0 = b / pow(10, m);
    int b1 = b % (int)pow(10, m);
    int z0 = MultiplicationKarazuba(a0, b0);
    int z1 = MultiplicationKarazuba(a0 + a1, b0 + b1);
    int z2 = MultiplicationKarazuba(a1, b1);
    return z0*pow(10, m*2) + (z1 - z0 - z2) * pow(10, m) + z2;*/
}
int Digits(int x)
{
    int i = 1;
    while ((x = x / 10) > 0)
    {
        i++;
    }
    return i;
}
short ConvertionFromSimbolToNumber(char a)
{
    if (a == '0')
        return 0;
    else if (a == '1')
        return 1;
    else if (a == '2')
        return 2;
    else if (a == '3')
        return 3;
    else if (a == '4')
        return 4;
    else if (a == '5')
        return 5;
    else if (a == '6')
        return 6;
    else if (a == '7')
        return 7;
    else if (a == '8')
        return 8;
    else if (a == '9')
        return 9;
}
char ConvertionFromNumberToSimbol(short a)
{
    if (a == 0)
        return '0';
    else if (a == 1)
        return '1';
    else if (a == 2)
        return '2';
    else if (a == 3)
        return '3';
    else if (a == 4)
        return '4';
    else if (a == 5)
        return '5';
    else if (a == 6)
        return '6';
    else if (a == 7)
        return '7';
    else if (a == 8)
        return '8';
    else if (a == 9)
        return '9';
}
string ConvertVectorToString(vector<char>a)
{
    char* res = new char[a.size()];
    memset(res, 0, sizeof(char) * a.size());
    for (auto i = 0; i < a.size(); i++)
    {
        res[i] = a[i];
    }
    return res;
}
vector<short> ReverseVector(vector<short> a)
{
    short temp = 0;
    for (int i = 0, j = size(a) - 1; i < size(a) / 2; i++, j--)
    {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
    return a;
}
vector<short> TruncationOfZeros(vector<short> a)
{
    auto flag = 0;
    for (auto i = 0; i < size(a); i++)
    {
        if (a.at(i) == 0)
        {
            flag++;
        }
        else
        {
            break;
        }
    }
    vector<short> mass(size(a) - flag);
    for (auto i = 0; i < size(mass); i++)
    {
        mass.at(i) = a.at(flag);
        flag++;
    }
    return mass;
}