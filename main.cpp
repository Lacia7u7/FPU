#include <bits/stdc++.h>
using namespace std;

union IEEE_754_helper {
    float f;
    struct {
        unsigned int mantissa : 23; // +127
        unsigned int exponent : 8;
        bool sign : 1;
    } IEEE_F;
};

void intToBinary(unsigned int n, int start, int end, string &res) {
    int i = end+1;
    while(n && (i-- >= start)) {
        if(n&1) res[i] = '1';
        else res[i] = '0';
        n>>=1;
    }
}

unsigned int binaryToInt(string &bin, int start, int end) {
    unsigned int res = 0, baseNum = 1;
    for(int i=end; i>=start; i--, baseNum<<=1) {
        if(bin[i] == '1') res += baseNum;
    }
    return res;
}

string codify(float f) {
    string res;
    res.resize(32);
    IEEE_754_helper helpF;
    helpF.f = f;
    res[0] = helpF.IEEE_F.sign + '0';
    intToBinary(helpF.IEEE_F.exponent, 1, 8, res);
    intToBinary(helpF.IEEE_F.mantissa, 9, 31, res);
    return res;
}

float decode(string fs) {
    bool sign = fs[0] - '0';
    int exponent, mantissa;
    exponent = binaryToInt(fs, 1, 8) - 127;
    if(exponent == -127) return 0.0;
    mantissa = binaryToInt(fs, 9, 31);
    float fmantissa = mantissa;
    while(mantissa) {
        fmantissa /= 10, mantissa /= 10;
    }
    float fres = 1+fmantissa;
    while(exponent > 0) {
        fres *= 2, exponent--;
    }
    while(exponent < 0) { 
        fres /= 2, exponent++;
    }
    if(sign) fres = -fres;
    return fres;
}

float substraction(string f1, string f2) {
    return decode(f1)-decode(f2);
}

float division(string f1, string f2) {
    float df1 = decode(f1), df2 = decode(f2);
    if(df2 == 0.0) return NAN;
    if(df1 == 0.0) return 0.0;
    return (df1/df2);
}

float addition(string n1,string n2){
    return decode(n1)+ decode(n2);
}
float multiplication(string n1, string n2){
    return decode(n1)* decode(n2);
}
float sqrt(string n1){
    float i;
    for(i=0.01;i*i<decode(n1);i=i+0.01);
    return(printf("%.2f", i));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //cout<<substraction(codify(0.5), codify(1))<<'\n';
    cout<<division(codify(0), codify(2))<<'\n';
    return 0;
}
