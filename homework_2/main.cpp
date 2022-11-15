#include <iostream>

using namespace std;

struct Matrix {
    int m_;
    int n_;
    double **a_;

    Matrix(int m, int n) : m_{m}, n_{n} {
        a_ = new double*[m_];
        for (int i = 0; i < m_; ++i) {
            a_[i] = new double[n_];
            for (int j = 0; j < n_; ++j) {
                a_[i][j] = 0;
            }
        }
    } 

    void SetElem(int i, int j, double val) {
        a_[i][j] = val;
    }

    double GetElem(int i, int j) {
        return a_[i][j];
    }

    void Print() {
        for (int i = 0; i < m_; ++i) {
            for (int j = 0; j < n_; ++j) {
                cout << a_[i][j] << " ";
            }
            cout << "\n";
        }
    }

    Matrix GetRow(int i) {
        Matrix matr = Matrix(1, n_);
        for (int j = 0; j < n_; ++j) {
            matr.SetElem(i, j, this->GetElem(i, j));
        }
        return matr;
    }

    Matrix GetColumn(int j) {
        Matrix matr = Matrix(m_, 1);
        for (int i = 0; i < m_; ++i) {
            matr.SetElem(i, j, this->GetElem(i, j));
        }
        return matr;
    }

    Matrix operator+(const double val) {
        Matrix matr = Matrix(m_, n_);
        for (int i = 0; i < m_; ++i) {
            for (int j = 0; j < n_; ++j) {
                matr.SetElem(i, j, this->GetElem(i, j) + val);
            }
        }
        return matr;
    }

    Matrix operator-(const double val) {
        Matrix matr = Matrix(m_, n_);
        for (int i = 0; i < m_; ++i) {
            for (int j = 0; j < n_; ++j) {
                matr.SetElem(i, j, this->GetElem(i, j) - val);
            }
        }
        return matr;
    }

    Matrix operator*(const double val) {
        Matrix matr = Matrix(m_, n_);
        for (int i = 0; i < m_; ++i) {
            for (int j = 0; j < n_; ++j) {
                matr.SetElem(i, j, this->GetElem(i, j) * val);
            }
        }
        return matr;
    }

    Matrix operator/(const double val) {
        Matrix matr = Matrix(m_, n_);
        for (int i = 0; i < m_; ++i) {
            for (int j = 0; j < n_; ++j) {
                matr.SetElem(i, j, this->GetElem(i, j) / val);
            }
        }
        return matr;
    }

    Matrix &operator+=(const double val) {
        for (int i = 0; i < m_; ++i) {
            for (int j = 0; j < n_; ++j) {
                this->SetElem(i, j, this->GetElem(i, j) + val);
            }
        }
        return *this;
    }

    Matrix &operator-=(const double val) {
        for (int i = 0; i < m_; ++i) {
            for (int j = 0; j < n_; ++j) {
                this->SetElem(i, j, this->GetElem(i, j) - val);
            }
        }
        return *this;
    }

    Matrix &operator*=(const double val) {
        for (int i = 0; i < m_; ++i) {
            for (int j = 0; j < n_; ++j) {
                this->SetElem(i, j, this->GetElem(i, j) * val);
            }
        }
        return *this;
    }

    Matrix &operator/=(const double val) {
        for (int i = 0; i < m_; ++i) {
            for (int j = 0; j < n_; ++j) {
                this->SetElem(i, j, this->GetElem(i, j) / val);
            }
        }
        return *this;
    }

    Matrix(const Matrix &matr) {
        m_ = matr.m_;
        n_ = matr.n_;
        a_ = new double*[m_];
        for (int i = 0; i < m_; ++i) {
            a_[i] = new double[n_];
            for (int j = 0; j < n_; ++j) {
                a_[i][j] = 0;
            }
        };
    }

    Matrix &operator=(const Matrix &matr) {
        if (n_ > 0) {
            for (int i = 0; i < m_; ++i) {
                delete [] a_[i];
            }
        }

        if (m_ > 0) {
            delete [] a_;
        }

        m_ = matr.m_;
        n_ = matr.n_;
        a_ = new double*[m_];
        for (int i = 0; i < m_; ++i) {
            a_[i] = new double[n_];
            for (int j = 0; j < n_; ++j) {
                a_[i][j] = 0;
            }
        }

        return *this;
    }

    ~Matrix() {
        if (n_ > 0) {
            for (int i = 0; i < m_; ++i) {
                delete [] a_[i];
            }
        }

        if (m_ > 0) {
            delete [] a_;
        }
    } 

    Matrix GetDiagonal() {
        int count;
        if (m_ < n_) {
            count = m_;
        } else {
            count = n_;
        }
        Matrix matr = Matrix(1, count);
        for (int i = 0; i < m_; ++i) {
            for (int j = 0; j < n_; ++j) {
                if (i == j) {
                    matr.SetElem(0, j, this->GetElem(i, j));
                }
            }
        }
        return matr;
    }
};

int main() {
    int m, n;
    m = 5;
    n = 3;

    double a[m][n];

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = rand() % 10;
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    Matrix matr = Matrix(m, n);
    cout << matr.m_ << " " << matr.n_ << "\n";
    cout << "\n";

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            matr.SetElem(i, j, a[i][j]);
        }
    }
    matr.Print();
    cout << "\n";

    Matrix row = matr.GetRow(0);
    row.Print();
    cout << "\n";

    Matrix column = matr.GetColumn(0);
    column.Print();
    cout << "\n";

    matr.SetElem(0, 0, 0);
    matr.Print();
    cout << "\n";

    row.Print();
    cout << "\n";

    column.Print();
    cout << "\n";

    Matrix matr_2 = matr + 1;
    cout << matr_2.m_ << "\n";
    matr_2.Print();
    cout << "\n";

    matr.Print();
    cout << "\n";

    Matrix diag = matr.GetDiagonal();
    diag.Print();
    cout << "\n";

    matr.Print();
    matr *= 2;
    cout << "\n";
    matr.Print();

    return 0;
}
