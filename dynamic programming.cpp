#include<iostream>
#include<fstream>
using namespace std;
double chazhi(double x);
double chazhi6(double x);
double chazhi2(double x);
double chazhi3(double x);
double chazhi4(double x);
double chazhi5(double x);
void njs(int m);
void dr();
void ckll();
void sc(double m);
void dtgh(double m);
double Q[3924];
double bzl=0;
double a[56], b[56], a1[56], b1[56], a2[56], b2[56], a3[56], b3[56], a4[56], b4[56], a5[56], b5[56], q1[3924], fd2[36], qs2[36], p2[36], e2[36], qsl[36], h1[3925],hsl[36];
struct dafa
{
	double preh;
	double max;
};
struct dafa result[3925][601];
void dr()
{
	fstream f1;
	f1.open("F:\\水电站调度\\入库流量.txt");
	for (int i = 0; i < 3924; i++)
	{
		f1 >> Q[i];
		
	}
	f1.close();
	fstream f2;
	f2.open("F:\\水电站调度\\库容曲线.txt");
	for (int i = 0; i < 56; i++)
	{
		f2 >> a[i] >> b[i];
	}
	f2.close();
	fstream f3;
	f3.open("F:\\水电站调度\\出力系数.txt");
	for (int i = 0; i < 6; i++)
	{
		f3 >> a1[i] >> b1[i];
	}
	f3.close();
	fstream f4;
	f4.open("F:\\水电站调度\\损失.txt");
	for (int i = 0; i < 15; i++)
	{
		f4 >> a2[i] >> b2[i];
	}
	f4.close();
	fstream f5;
	f5.open("F:\\水电站调度\\下游水位.txt");
	for (int i = 0; i < 30; i++)
	{
		f5 >> a3[i] >> b3[i];
	}
	f5.close();
	fstream f6;
	f6.open("F:\\水电站调度\\泄流能力.txt");
	for (int i = 0; i < 12; i++)
	{
		f6 >> a4[i] >> b4[i];
	}
	f6.close();
	fstream f7;
	f7.open("F:\\水电站调度\\最大出力.txt");
	for (int i = 0; i < 18; i++)
	{
		f7 >> a5[i] >> b5[i];
	}
	f7.close();
	fstream f8;
	f8.open("F:\\水电站调度\\出库流量.txt");
	for (int i = 0; i < 3924; i++)
	{
		f8 >> q1[i] ;
	}
	f8.close();
	fstream f9;
	f9.open("F:\\水电站调度\\水位.txt");
	for (int i = 0; i < 3924; i++)
	{
		f9 >> h1[i];
	}
	f9.close();
}
double fd[3924][601], xx[3924][601], qs[3924][601], p[3924][601], h[3925][601], sw[3925],ck[3924];
void main()
{
	for (int i = 0; i <=600; i++)
		result[0][i].max = 0;
	sw[0] = sw[3924] = 171.7;
	dr();
	dtgh(171.7);
	sc(171.7);
	ckll();
	njs(34);
	system("pause");
}
void njs(int m)
{
	double bzl2=0;
	int i;
	for (i = m*36; i <=m*36+35; i++)
	{
		if ((chazhi2((h1[i] + h1[i + 1]) / 2 - chazhi4(q1[i])) * q1[i] * ((h1[i] + h1[i + 1]) / 2 - chazhi4(q1[i])))>(chazhi6((h1[i] + h1[i + 1]) / 2 - chazhi4(q1[i])) * 32 * 1000))
		{
			fd2[i % 36] = (chazhi6((h1[i] + h1[i + 1]) / 2 - chazhi4(q1[i])) * 1000 * 32) / ((chazhi2((h1[i] + h1[i + 1]) / 2 - chazhi4(q1[i]))*(h1[i] + h1[i + 1]) / 2 - chazhi4(q1[i])));
			qs2[i % 36] = q1[i] - fd2[i % 36];
			p2[i % 36] = chazhi6((h1[i] + h1[i + 1]) / 2 - chazhi4(q1[i])) * 32;
			hsl[i % 36] = fd2[i % 36] / q1[i];
			if (p2[i % 36] > (4990 * 1000))  bzl2 = bzl2 + 1 / 36;
		}
		else
		{
			fd2[i % 36] = q1[i];
			qs2[i % 36] = 0;
			p2[i % 36] = (chazhi2((h1[i] + h1[i + 1]) / 2 - chazhi4(q1[i]))*q1[i] * ((h1[i] + h1[i + 1]) / 2 - chazhi4(q1[i])))/1000;
			hsl[i % 36] = 1;
			if (p2[i % 36] > (4990 * 1000))  bzl2 = bzl2 + 1 / 36;
		}
		e2[i % 36] = p2[i % 36] * 3600 * 24 * 10;
	}
	ofstream f2("F:\\水电站调度\\结果.txt", ios::trunc);
	for (int i = 0; i < 36; i++)
	{
		f2 << h1[m * 36 + i] << "," << Q[m * 36 + i] << "," << q1[m * 36 + i] << "," << fd2[i] << "," << qs2[i] << "," << p2[i] << "," << e2[i] << "," << hsl[i] << endl;
	}
}
void ckll()
{
	ofstream f3("F:\\水电站调度\\出库流量.txt", ios::trunc);
	for (int i = 1; i <= 3924; i++)
		ck[3924 - i] = (Q[3924 - i] * 3600 * 24 * 10 - (chazhi(sw[i]) - chazhi(sw[i+1])) * 100000000) / (3600 * 24 * 10);
	for (int i = 0; i < 3924; i++)
		f3 << ck[i] << endl;
}
void sc(double m)
{
	ofstream f2("F:\\水电站调度\\水位.txt", ios::trunc);
	int n;
	double q;
	f2 << m << endl;
	n = (int)(result[3924][int((m - 145) * 20)].preh*20);
	for (int i = 1; i <= 3924; i++)
	{
		n = (int)(result[3924 - i][(n - 2900)].preh * 20);
		q = n / 20.0;
		sw[3924 - i] = q;
	    f2 << q << endl;
	}	
}
void dtgh(double m)
{
	for (int j = 0; j < 3924; j++)
	{
		if (j % 36 == 0)//年初
		{
			for (int i = 0; i <= 600; i++)
			{
				double max1 = 0;
				h[j + 1][i] = 145 + i*0.05;
				for (int z = 0; z <= 600; z++)
				{
					h[j][z] = m;
					xx[j][i] = (Q[j]*3600*24*10 - (chazhi(h[j + 1][i]) - chazhi(h[j][z]))*100000000)/(3600*24*10);//
					if (xx[j][i] > chazhi5((h[j + 1][i] + h[j][z]) / 2)||xx[j][i]<0||xx[j][i]<5000)
						p[j][i] = -100000000000;
					else if (chazhi2(((h[j + 1][i] + h[j][z]) / 2) - chazhi4(xx[j][i]))*xx[j][i] * ((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][z])) > (((chazhi6((h[j + 1][i] + h[j][z])/2 - chazhi4(xx[j][i])))) * 32)*1000)
					{
						fd[j][i] = (chazhi6(((h[j + 1][i] + h[j][z])/2 - chazhi4(xx[j][i]))*1000*32) / (chazhi2((h[j + 1][i] + h[j][z])/2 - chazhi4(xx[j][i])))*((h[j + 1][i] + h[j][z])/2 - chazhi4(xx[j][i])));
						qs[j][i] = xx[j][i] - fd[j][i];
						p[j][i] = chazhi6((h[j + 1][i] + h[j][z])/2 - chazhi4(xx[j][i])) * 32;
					}
					else
					{
						fd[j][i] = xx[j][i];
						qs[j][i] = 0;
						p[j][i] = (chazhi2((h[j + 1][i] + h[j][z])/2 - chazhi4(xx[j][i]))*xx[j][i] * ((h[j + 1][i] + h[j][z])/2 - chazhi4(xx[j][i])))/1000;
					}
					if (p[j][i]<4700)
						p[j][i] = -10000000000000;
					if ((result[j][z].max+p[j][i]) > max1)
					{
						max1 = p[j][i] + result[j][z].max;
						result[j + 1][i].max = result[j][z].max + p[j][i];
						result[j + 1][i].preh = 145 + z*0.05;
					}
				}
			}
		}
		else if (j % 36 == 15)//汛期初
		{
			for (int i = 0; i <= 600; i++)
			{
				double max1 = 0;
				h[j + 1][i] = 145;
				for (int z = 0; z <= 600; z++)
				{
					h[j][z] = 145 + z * 0.05;
					xx[j][i] = (Q[j] * 3600 * 24 * 10 - (chazhi(h[j + 1][i]) - chazhi(h[j][z])) * 100000000) / (3600 * 24 * 10);
					if (xx[j][i] > chazhi5((h[j + 1][i] + h[j][z]) / 2) || xx[j][i]<0 || xx[j][i]<5000)
						p[j][i] = -100000000000;
					else if (chazhi2(((h[j + 1][i] + h[j][z]) / 2) - chazhi4(xx[j][i]))*xx[j][i] * ((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][z])) > (((chazhi6((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])))) * 32) * 1000)
					{
						fd[j][i] = (chazhi6(((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])) * 1000 * 32) / (chazhi2((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])))*((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])));
						qs[j][i] = xx[j][i] - fd[j][i];
						p[j][i] = chazhi6((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])) * 32;
					}
					else
					{
						fd[j][i] = xx[j][i];
						qs[j][i] = 0;
						p[j][i] = (chazhi2((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i]))*xx[j][i] * ((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i]))) / 1000;
					}
					if (p[j][i]<4700)
						p[j][i] = -10000000000000;
					if ((result[j][z].max + p[j][i]) > max1)
					{
						max1 = p[j][i] + result[j][z].max;
						result[j + 1][i].max = result[j][z].max + p[j][i];
						result[j + 1][i].preh = 145 + z*0.05;
					}
				}
			}
		}
		else if (j % 36 >= 16 && j % 36 <= 24)//汛期
		{
			for (int i = 0; i <= 600; i++)
			{
				double max1 = 0;
				h[j + 1][i] = 145;
				for (int z = 0; z <= 600; z++)
				{
					h[j][z] = 145;
					xx[j][i] = (Q[j] * 3600 * 24 * 10 - (chazhi(h[j + 1][i]) - chazhi(h[j][z])) * 100000000) / (3600 * 24 * 10);
					if (xx[j][i] > chazhi5((h[j + 1][i] + h[j][z]) / 2) || xx[j][i]<0 || xx[j][i]<5000)
						p[j][i] = -100000000000;
					else if (chazhi2(((h[j + 1][i] + h[j][z]) / 2) - chazhi4(xx[j][i]))*xx[j][i] * ((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][z])) > (((chazhi6((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])))) * 32) * 1000)
					{
						fd[j][i] = (chazhi6(((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])) * 1000 * 32) / (chazhi2((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])))*((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])));
						qs[j][i] = xx[j][i] - fd[j][i];
						p[j][i] = chazhi6((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])) * 32;
					}
					else
					{
						fd[j][i] = xx[j][i];
						qs[j][i] = 0;
						p[j][i] = (chazhi2((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i]))*xx[j][i] * ((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i]))) / 1000;
					}
					if (p[j][i]<4700)
						p[j][i] = -10000000000000;
					if ((result[j][z].max + p[j][i]) > max1)
					{
						max1 = p[j][i] + result[j][z].max;
						result[j + 1][i].max = result[j][z].max + p[j][i];
						result[j + 1][i].preh = 145 + z*0.05;
					}
				}
			}
		}
		else if (j % 36 == 25)//汛期末
		{
			for (int i = 0; i <= 600; i++)
			{
				double max1 = 0;
				h[j + 1][i] = 145 + i*0.05;
				for (int z = 0; z <= 600; z++)
				{
					h[j][z] = 145;
					xx[j][i] = (Q[j] * 3600 * 24 * 10 - (chazhi(h[j + 1][i]) - chazhi(h[j][z])) * 100000000) / (3600 * 24 * 10);
					if (xx[j][i] > chazhi5((h[j + 1][i] + h[j][z]) / 2) || xx[j][i]<0 || xx[j][i]<5000)
						p[j][i] = -100000000000;
					else if (chazhi2(((h[j + 1][i] + h[j][z]) / 2) - chazhi4(xx[j][i]))*xx[j][i] * ((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][z])) > (((chazhi6((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])))) * 32) * 1000)
					{
						fd[j][i] = (chazhi6(((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])) * 1000 * 32) / (chazhi2((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])))*((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])));
						qs[j][i] = xx[j][i] - fd[j][i];
						p[j][i] = chazhi6((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])) * 32;
					}
					else
					{
						fd[j][i] = xx[j][i];
						qs[j][i] = 0;
						p[j][i] = (chazhi2((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i]))*xx[j][i] * ((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i]))) / 1000;
					}
					if (p[j][i]<4700)
						p[j][i] = -10000000000000;
					if ((result[j][z].max + p[j][i]) > max1)
					{
						max1 = p[j][i] + result[j][z].max;
						result[j + 1][i].max = result[j][z].max + p[j][i];
						result[j + 1][i].preh = 145 + z*0.05;
					}
				}
			}
		}
		else if (j % 36 == 35)//年末
		{
			for (int i = 0; i <= 600; i++)
			{
				double max1 = 0;
				h[j + 1][i] = m;
				for (int z = 0; z <= 600; z++)
				{
					h[j][z] = 145 + z*0.05;
					xx[j][i] = (Q[j] * 3600 * 24 * 10 - (chazhi(h[j + 1][i]) - chazhi(h[j][z])) * 100000000) / (3600 * 24 * 10);
					if (xx[j][i] > chazhi5((h[j + 1][i] + h[j][z]) / 2) || xx[j][i]<0 || xx[j][i]<5000)
						p[j][i] = -100000000000;
					else if (chazhi2(((h[j + 1][i] + h[j][z]) / 2) - chazhi4(xx[j][i]))*xx[j][i] * ((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][z])) > (((chazhi6((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])))) * 32) * 1000)
					{
						fd[j][i] = (chazhi6(((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])) * 1000 * 32) / (chazhi2((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])))*((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])));
						qs[j][i] = xx[j][i] - fd[j][i];
						p[j][i] = chazhi6((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])) * 32;
					}
					else
					{
						fd[j][i] = xx[j][i];
						qs[j][i] = 0;
						p[j][i] = (chazhi2((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i]))*xx[j][i] * ((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i]))) / 1000;
					}
					if (p[j][i]<4700)
						p[j][i] = -10000000000000;
					if ((result[j][z].max + p[j][i]) > max1)
					{
						max1 = p[j][i] + result[j][z].max;
						result[j + 1][i].max = result[j][z].max + p[j][i];
						result[j + 1][i].preh = 145 + z*0.05;
					}
				}
			}
		}
		else//正常时期
		{
			for (int i = 0; i <= 600; i++)
			{
				double max1 = 0;
				h[j + 1][i] = 145 + i*0.05;
				for (int z = 0; z <= 600; z++)
				{
					h[j][z] = 145 + z*0.05;
					xx[j][i] = (Q[j] * 3600 * 24 * 10 - (chazhi(h[j + 1][i]) - chazhi(h[j][z])) * 100000000) / (3600 * 24 * 10);
					if (xx[j][i] > chazhi5((h[j + 1][i] + h[j][z]) / 2) || xx[j][i]<0 || xx[j][i]<5000)
						p[j][i] = -100000000000;
					else if (chazhi2(((h[j + 1][i] + h[j][z]) / 2) - chazhi4(xx[j][i]))*xx[j][i] * ((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][z])) > (((chazhi6((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])))) * 32) * 1000)
					{
						fd[j][i] = (chazhi6(((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])) * 1000 * 32) / (chazhi2((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])))*((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])));
						qs[j][i] = xx[j][i] - fd[j][i];
						p[j][i] = chazhi6((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i])) * 32;
					}
					else
					{
						fd[j][i] = xx[j][i];
						qs[j][i] = 0;
						p[j][i] = (chazhi2((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i]))*xx[j][i] * ((h[j + 1][i] + h[j][z]) / 2 - chazhi4(xx[j][i]))) / 1000;
					}
					if (p[j][i]<4700)
						p[j][i] = -10000000000000;
					if ((result[j][z].max + p[j][i]) > max1)
					{
						max1 = p[j][i] + result[j][z].max;
						result[j + 1][i].max = result[j][z].max + p[j][i];
						result[j + 1][i].preh = 145 + z*0.05;
					}
				}
			}
		}
	}
	int p = (int)((m - 145) * 20);
	cout << result[3923][p].max << endl;
}
double chazhi(double x)//库容曲线
{
	double y;
	if (x<a[0])
		y = (b[0] - b[1])*(x - a[0]) / (a[0] - a[1]) + b[0];
	else if (x>a[55])
		y = (b[55] - b[54])*(x - a[55]) / (a[55] - a[54]) + b[55];
	else
	{
		for (int i = 0; x>a[i]; i++)
		{
			y = (b[i + 1] - b[i]) / (a[i + 1] - a[i])*(x - a[i]) + b[i];
		}

	}
	return y;
}//
double chazhi2(double x)//出力系数
{
	double y;
	if (x<a1[0])
		y = (b1[0] - b1[1])*(x - a1[0]) / (a1[0] - a1[1]) + b1[0];
	else if (x>a1[55])
		y = (b1[5] - b1[4])*(x - a1[5]) / (a1[5] - a1[4]) + b1[5];
	else
	{
		for (int i = 0; x>a1[i]; i++)
		{
			y = (b1[i + 1] - b1[i]) / (a1[i + 1] - a1[i])*(x - a1[i]) + b1[i];
		}

	}
	return y;
}
double chazhi3(double x)//水头损失
{
	double y;	
	if (x<a2[0])
		y = (b2[0] - b2[1])*(x - a2[0]) / (a2[0] - a2[1]) + b[0];
	else if (x>a2[14])
		y = (b2[14] - b2[13])*(x - a2[14]) / (a2[14] - a2[13]) + b2[14];
	else
	{
		for (int i = 0; x>a2[i]; i++)
		{
			y = (b2[i + 1] - b2[i]) / (a2[i + 1] - a2[i])*(x - a2[i]) + b2[i];
		}

	}
	return y;
}
double chazhi4(double x)//下游水位
{
	double y;
	if (x<a3[0])
		y = (b3[0] - b3[1])*(x - a3[0]) / (a3[0] - a3[1]) + b3[0];
	else if (x>a3[29])
		y = (b3[29] - b3[28])*(x - a3[29]) / (a3[29] - a3[28]) + b3[29];
	else
	{
		for (int i = 0; x>=a3[i]; i++)
		{
			y = (b3[i + 1] - b3[i]) / (a3[i + 1] - a3[i])*(x - a3[i]) + b3[i];
		}
	}
	return y;
}
double chazhi5(double x)//泄流能力
{
	double y;
	if (x<a4[0])
		y = (b4[0] - b4[1])*(x - a4[0]) / (a4[0] - a4[1]) + b4[0];
	else if (x>a4[11])
		y = (b4[11] - b4[10])*(x - a4[11]) / (a4[11] - a4[10]) + b4[11];
	else
	{
		for (int i = 0; x>a4[i]; i++)
		{
			y = (b4[i + 1] - b4[i]) / (a4[i + 1] - a4[i])*(x - a4[i]) + b4[i];
		}

	}
	return y;
}
double chazhi6(double x)//最大出力
{
	double y;
	if (x<a5[0])
		y = (b5[0] - b5[1])*(x - a5[0]) / (a5[0] - a5[1]) + b5[0];
	else if (x>a5[17])
		y = (b5[17] - b5[16])*(x - a5[17]) / (a5[17] - a5[16]) + b5[17];
	else
	{
		for (int i = 0; x>a5[i]; i++)
		{
			y = (b5[i + 1] - b5[i]) / (a5[i + 1] - a5[i])*(x - a5[i]) + b5[i];
		}

	}
	return y;
}
