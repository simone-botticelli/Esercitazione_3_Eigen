#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;

//palu_2x2 solves the linear system Ax=b for 2 by 2 matrices using PALU decomposition
void palu_2x2(const Matrix2d& A, const Vector2d& b, Vector2d& x){
	x = A.lu().solve(b);
}

//qr_2x2 solves the linear system Ax=b for 2 by 2 matrices using QR decomposition
void qr_2x2(const Matrix2d& A, const Vector2d& b, Vector2d& x){
	x = A.householderQr().solve(b);
}

void relative_err(const Vector2d& solution, const Vector2d& x, double& rel_err){
	rel_err = (x - solution).norm() / solution.norm();
}


int main()
{
	// Inizializzo due vector in cui inserire i sistemi da risolvere
    std::vector<Matrix2d> matrices(3);
    std::vector<Vector2d> vectors(3);
    
    matrices[0] << 5.547001962252291e-01, -3.770900990025203e-02,
    		8.320502943378437e-01, -9.992887623566787e-01;
	vectors[0] << -5.169911863249772e-01, 1.672384680188350e-01;

    matrices[1] << 5.547001962252291e-01, -5.540607316466765e-01,
     8.320502943378437e-01, -8.324762492991313e-01;
    vectors[1] << -6.394645785530173e-04, 4.259549612877223e-04;

    matrices[2] << 5.547001962252291e-01, -5.547001955851905e-01,
     8.320502943378437e-01, -8.320502947645361e-01;
    vectors[2] << -6.400391328043042e-10, 4.266924591433963e-10;
	
	Vector2d solution;
	solution << -1.0e+0, -1.0e+00;
	
	double rel_err;
	Vector2d x;
	
	cout << std::scientific;
	
	for (int i = 0; i < 3; i++){
		palu_2x2(matrices[i], vectors[i], x);
		relative_err(solution, x, rel_err);
		cout << "Solving problem " << i+1 << endl;
		cout << endl;
		cout << "PALU decomposition yields solution x" << endl;
		cout << x << endl;
		cout << "with relative error = " << rel_err << endl;
		cout << endl;
		qr_2x2(matrices[i], vectors[i], x);
		relative_err(solution, x, rel_err);
		cout << "QR decomposition yields solution x" << endl;
		cout << x << endl;
		cout << "with relative error =" << rel_err << endl;
		cout << endl;
	}
	
    return 0;
}
