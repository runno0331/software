int main()
{
        double t,x,v,dt,tmax;
        double k1[2],k2[2],k3[2],k4[2];

        x=1.0;                  //位置の初期値
        v=0.0;                  //速度の初期値
        dt=0.01;                //刻み幅
        tmax=500.0;             //繰り返し最大回数

        for(t=0;t<tmax;t+=dt) {
                k1[0]=dt*f1(t,x,v);
                k1[1]=dt*f2(t,x,v);

                k2[0]=dt*f1(t+dt/2.0,x+k1[0]/2.0,v+k1[1]/2.0);
                k2[1]=dt*f2(t+dt/2.0,x+k1[0]/2.0,v+k1[1]/2.0);

                k3[0]=dt*f1(t+dt/2.0,x+k2[0]/2.0,v+k2[1]/2.0);
                k3[1]=dt*f2(t+dt/2.0,x+k2[0]/2.0,v+k2[1]/2.0);

                k4[0]=dt*f1(t+dt,x+k3[0],v+k3[1]);
                k4[1]=dt*f2(t+dt,x+k3[0],v+k3[1]);

                x=x+(k1[0]+2.0*k2[0]+2.0*k3[0]+k4[0])/6.0;
                v=v+(k1[1]+2.0*k2[1]+2.0*k3[1]+k4[1])/6.0;

                fprintf(output,"%f %f %f\n",t,x,v);
        }

        fclose(output);

        return 0;
}

//xなら0,yなら1
double dxdt(int a, int i)
{
    (a == 0)? return stars[i].vx:return stars[i].vy;
}

double dvdt(int i, int j,int a)
{
        return ax += (stars[j].x-stars[i].x)*stars[j].m*cond.G/pow(pow(stars[i].x-stars[j].x,2)+pow(stars[i].y-stars[j].y,2),1.5);
}