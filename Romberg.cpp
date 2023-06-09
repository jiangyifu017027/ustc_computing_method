#include<iostream>
#include<vector>
#include<cmath>
#include<fstream>
#include<sstream>

using namespace std;

double Mtime = 0.0;
double errortime = 0.0;

double fx(double t) {
    return sin(t) / (sqrt(t) + 1.0);
}

double fy(double t) {
    return log(t + 1.0) / (t + 1.0);
}

//rombergv_x即v_x
double rombergv_x(double a, double b, double e, int M) {
    double result = 0.0;
    vector<vector<double>> R(M + 1, vector<double>(M + 1, 0.0));
    int n = 1;
    double h = b - a;
    R[1][1] = h / 2.0 * ((fx(a)) + (fx(b)));
    result = R[1][1];
    for (int k = 2; k <= M; ++k) {
        double temp = 0.0;
        for (int i = 1; i <= pow(2, k - 2); ++i) {
            temp += fx(a + (2.0 * i - 1.0) * (h / pow(2, k - 1)));
        }
        R[k][1] = (R[k - 1][1] + (h / pow(2, k - 2)) * temp) / 2.0;
        for (int j = 2; j <= k; ++j) {
            R[k][j] = R[k][j - 1] + (R[k][j - 1] - R[k - 1][j - 1]) / (pow(4, j - 1) - 1.0);
        }
        if (fabs(R[k][k] - R[k - 1][k - 1]) < e) {
            result = R[k][k];
            break;
        }
    }
    return result;
}

double rombergv_y(double a, double b, double e, int M) {
    double result = 0.0;
    vector<vector<double>> R(M + 1, vector<double>(M + 1, 0.0));
    int n = 1;
    double h = b - a;
    R[1][1] = h / 2.0 * ((fy(a)) + (fy(b)));
    result = R[1][1];
    for (int k = 2; k <= M; ++k) {
        double temp = 0.0;
        for (int i = 1; i <= pow(2, k - 2); ++i) {
            temp += fy(a + (2.0 * i - 1.0) * (h / pow(2, k - 1)));
        }
        R[k][1] = (R[k - 1][1] + (h / pow(2, k - 2)) * temp) / 2.0;
        for (int j = 2; j <= k; ++j) {
            R[k][j] = R[k][j - 1] + (R[k][j - 1] - R[k - 1][j - 1]) / (pow(4, j - 1) - 1.0);
        }
        if (fabs(R[k][k] - R[k - 1][k - 1]) < e) {
            result = R[k][k];
            break;
        }
    }
    return result;
}

//rombergx即x(t),y(t)
double rombergx(double a, double b, double e, int M) {
    double result = 0.0;
    vector<vector<double>> R(M + 1, vector<double>(M + 1, 0.0));
    int n = 1;
    double h = b - a;
    R[1][1] = h / 2.0 * (rombergv_x(0.0, a, e, M) + rombergv_x(0.0, b, e, M));
    result = R[1][1];
    for (int k = 2; k <= M; ++k) {
        double temp = 0.0;
        for (int i = 1; i <= pow(2, k - 2); ++i) {
            temp += rombergv_x(0.0, a + (2 * i - 1.0) * (h / pow(2, k - 1)), e, M);
        }
        R[k][1] = (R[k - 1][1] + (h / pow(2, k - 2)) * temp) / 2.0;
        for (int j = 2; j <= k; ++j) {
            R[k][j] = R[k][j - 1] + (R[k][j - 1] - R[k - 1][j - 1]) / (pow(4, j - 1) - 1.0);
        }
        if (fabs(R[k][k] - R[k - 1][k - 1]) < e) {
            Mtime += M;
            errortime += k;
            result = R[k][k];
            break;
        }
    }
    return result;
}

double rombergy(double a, double b, double e, int M) {
    double result = 0.0;
    vector<vector<double>> R(M + 1, vector<double>(M + 1, 0.0));
    int n = 1;
    double h = b - a;
    R[1][1] = h / 2.0 * (rombergv_y(0.0, a, e, M) + rombergv_y(0.0, b, e, M));
    result = R[1][1];
    for (int k = 2; k <= M; ++k) {
        double temp = 0.0;
        for (int i = 1; i <= pow(2, k - 2); ++i) {
            temp += rombergv_y(0.0, a + (2 * i - 1.0) * (h / pow(2, k - 1)), e, M);
        }
        R[k][1] = (R[k - 1][1] + (h / pow(2, k - 2)) * temp) / 2.0;
        for (int j = 2; j <= k; ++j) {
            R[k][j] = R[k][j - 1] + (R[k][j - 1] - R[k - 1][j - 1]) / (pow(4, j - 1) - 1.0);
        }
        if (fabs(R[k][k] - R[k - 1][k - 1]) < e) {
            Mtime += M;
            errortime += k;
            result = R[k][k];
            break;
        }
    }
    return result;
}

int main() {
    vector<double> t;
    double temp = 0.1;
    t.push_back(temp);
    while (temp < 9.9) {
        temp += 0.1;
        t.push_back(temp);
    }
    double e = 1e-6;
    int M = 20;
    vector<vector<double>> poi;
    for (int i = 1; i <= t.size(); ++i) {
        vector<double> tmp(2, 0.0);
        tmp[0] = rombergx(0.0, t[i - 1], e, M);
        tmp[1] = rombergy(0.0, t[i - 1], e, M);
        poi.push_back(tmp);
    }
    std::cout << "x(t), y(t)为:" << endl;
    for (int i = 0; i < t.size(); ++i) {
        std::cout << poi[i][0] << "  " << poi[i][1] << endl;
    }
    std::cout << endl;
    ofstream data;
    data.open("C:\\ustc_computing_method\\romberg.txt");
    for (int i = 0; i < poi.size(); ++i) {
        data << poi[i][0] << "  " << poi[i][1] << endl;
    }
    data.close();
    std::cout << "当M=20时,比例:" << errortime / Mtime << endl;
    return 0;
}