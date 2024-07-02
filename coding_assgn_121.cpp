#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

double findDensity(double P, double t){ // t is temp in degC
    double Vo,B,A1,A2;
    Vo=(1+(18.1597*pow(10,-3)*t))/(0.9998+(18.2249*pow(10,-3)*t)-(7.9222*pow(10,-6)*pow(t,2))-(55.4485*pow(10,-9)*pow(t,3))+(149.7562*pow(10,-12)*pow(t,4))-(393.2952*pow(10,-15)*pow(t,5)));
    B=19654.32+(147.037*t)-(2.2155*pow(t,2))+(1.0478*pow(10,-2)*pow(t,3))-(2.2789*pow(10,-5)*pow(t,4));         
    A1=3.2891-(2.391*pow(10,-3)*t)+(2.8446*pow(10,-4)*pow(t,2))-(2.82*pow(10,-6)*pow(t,3))+(8.477*pow(10,-9)*pow(t,4));
    A2=(6.245*pow(10,-5))-(3.913*pow(10,-6)*t)+(3.499*pow(10,-8)*pow(t,2))-(7.942*pow(10,-10)*pow(t,3))+(3.299*pow(10,-12)*pow(t,4));

    double rho,inverseRho;              // rho in cc/g
    inverseRho= Vo-((Vo*P)/(B+(A1*P)+(A2*P*P)));
    rho=1.00000/inverseRho;

    return rho;
} 

double findFugacity(double P, double T){    //T in Kelvin
    double Tc=647.096,Pc=220.64;    // Critical values for H20
    double a1=-7.8595178,a2=1.8440825,a3=-11.786649,a4=22.680741,a5=-15.9618719,a6=1.8012250;   //from table A1

    double temp=(Tc/T)*((a1*(1-(T/Tc)))+(a2*pow((1-(T/Tc)),1.5))+(a3*pow((1-(T/Tc)),3))+(a4*pow((1-(T/Tc)),3.5))+(a5*pow((1-(T/Tc)),4))+(a6*pow((1-(T/Tc)),7.5)));

    double Ps=Pc*exp(temp);

    double rho=findDensity(P,T-273.15),R=83.14;
    double fo=Ps*exp((18.0152*(P-Ps))/(rho*R*T));

    return fo;
}

double f(double x, double a, double b, double c, double d) {
    return a*x*x*x + b*x*x + c*x + d;
}
double df(double x, double a, double b, double c) {
    return 3*a*x*x + 2*b*x + c;
}

double newtonRaphson(double x0, double a, double b, double c, double d, double tolerance, int maxIterations) {
    double x = x0;
    for (int i = 0; i < maxIterations; i++) {
        double fx = f(x, a, b, c, d);
        double dfx = df(x, a, b, c);
        double xNew = x - fx / dfx;
        if (fabs(xNew - x) < tolerance) 
            return xNew;
        x = xNew;
    }
    return x; 
}

//_______________________________________________________________________________________________________//
int main(){
  ifstream infile;
  infile.open("input.txt");
  
  double T;
  infile >> T;

  double P;
  infile >> P;

  double M;
  infile >> M;

  double t = T - 273.15; 

  // double t=100,P=150,M=4;
  // cin>>P>>t>>M;
  // cout<<"input temp in celcius: "<<t<<endl<<"input pressure in bar: "<<P<<endl<<"input molality of co2 in mol/kg of co2: "<<M<<endl;
  // double T=t+273.15;
  double rho=findDensity(P,t);
  double fowater=findFugacity(P,T);
  cout<<"density of water: "<<rho<<endl<<"fugacity of pure water: "<<fowater<<endl;

  double Pc=73.8,Tc=304.0000;    //Critical values for CO2
  double R=83.14;
  double wi=0.224;      // CO2 eccentric factor which is const for species 

  // Calculation of A and B 
  double mi=0.37464+(1.54226*wi)-(0.26992*wi*wi);
  double ai=((0.457236*((R*R*Tc*Tc)/Pc)))*(pow(1+(mi*(1-(pow((T/Tc),0.5)))),2));
  double bi=(0.077796*((R*Tc)/Pc));

//   cout<<ai<<"  "<<bi<<endl;

  double A=(ai*P)/(R*R*T*T);
  double B=(bi*P)/(R*T);

//   cout<<A<<"  "<<B<<endl;

  // Equation of Z from gen form of PR EOS
  // Z3 − (1 − B)Z2 + (A − 2B − 3B2)Z − (AB−B2 − B3) = 
  double a1=1.000,a2=-(1-B),a3=A-(2*B)-(3*B*B),a4=-((A*B)-(B*B)-(B*B*B));

 double x0=0;
 double tol=1e-6;
 double maxIter=1000;
 double Z = newtonRaphson(x0, a1, a2, a3, a4, tol, maxIter);
 cout<<"compressibility factor(Z): "<<Z<<endl;
 
  double del1=1+sqrt(2),del2=1-sqrt(2);


  double phi;
  // bi=b (from eq 18) -> bi/b=1
  // a=sigma(j=1 to N) yi*yj*aij
  // Above 2 lines ->  (2*sigma(j=1 to N) yi*yj*aij)/a - bi/b = 2-1 = 1  --> no need to write this part in eqn since 1 is multiplied
  phi=exp((Z-1)-(log(abs(Z-B)))-((A/(B*(del2-del1)))*(log((Z+(del2*B))/(Z+(del1*B))))));

  cout<<"fugacity coefficient of co2(phi): "<<phi<<endl;

  //Calculation of hi
  double neta=-0.114535,Mw=18.01528,tau=-5.279063,beta=6.187967;
  double delB=tau+(beta*(pow(1000.00000/T,0.5)));
  double hi=exp(((1-neta)*log(fowater))+(neta*(log((R*T*rho)/(Mw))))+(2*rho*delB)); 
  cout<<"delta B: "<<delB<<endl;
  
  cout<<"henry const for dissolved co2(h): "<<hi<<endl;

  //Calculation of gammai
  double lambda=(-0.0652869)+(1.6790636*0.0001*T)+(40.838951/T)+((-3.9266518*0.01*P)/T)+((2.1157167*0.01*P)/(630.000000-T))+(6.5486487*0.000001*T*log(P));
  double epsilon=(-1.144624*0.01)+(2.8274958*0.00001*T)+((1.3980876*0.01*P)/T)+((-1.4349005*0.01*P)/(630.000000-T));
  double gammai=exp((2*M*lambda)+(2*M*M*epsilon));
  cout<<"Activity coeff of dissoved co2(gamma): "<<gammai<<endl;

  //Calculation of Kco2 and Kh2o
  double Kco2=(hi*gammai)/(P*phi);

  double Koh2o=pow(10,((-2.209)+(3.097*pow(10,-2)*t)-(1.098*pow(10,-4)*t*t)+(2.048*pow(10,-7)*t*t*t)));
  double Kh2o=(Koh2o/(fowater*P))*exp(((P-1)*18.18)/(R*T));
cout<<"Kco2: "<<Kco2<<endl<<"Kh2o: "<<Kh2o<<endl;
  //Calculation of yi and xi
  double yh2o=(1-(1/Kco2))/((1/Kh2o)-(1/Kco2));
  double yi=1.0000/(1+yh2o);

  double xi=yi/Kco2;

  ofstream outfile("output.txt");
  outfile << "mole fraction- " << xi;

  cout<<100*xi<<endl;
}
