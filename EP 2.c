/***************************************************************/
/**                                                           **/
/**  Natham Sanchez Pez                             13680470  **/
/**   Exercício-Programa 02                                   **/
/**   Professor: Guilherme Mota                               **/
/**   Turma: 01                                               **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>

/*Declaração das funções*/
double quadrado (double n1);

double raiz_quadrada (double x);

double dist (double r1x, double r1y, double r2x, double r2y);

double forca_resultante (double massa_primeiro_planeta, double massa_segundo_planeta, double distancia);

double forca (char componente, int numero_planeta,double r0x, double r0y, double massa_0,double r1x, double r1y, double massa_1,double r2x, double r2y, double massa_2);

void atualize (double *rx, double *ry, double *vx, double *vy, double ax, double ay, double dt);

double aceleracao (char componente, int numero_planeta, double r0x, double r0y, double massa_0,double r1x, double r1y, double massa_1,double r2x, double r2y, double massa_2);

/*Código principal*/
int main()
{
    double r0x, r0y, r1x, r1y, r2x, r2y;
    double v0x, v0y, v1x, v1y, v2x, v2y;
    double massa_0, massa_1, massa_2;
    double acel_0x, acel_0y, acel_1x, acel_1y, acel_2x, acel_2y;
    int tempo_total, delta_tempo;
    int k, contador;

    scanf("%lf %lf %lf %lf %lf\n", &r0x, &r0y, &v0x, &v0y, &massa_0);
    scanf("%lf %lf %lf %lf %lf\n", &r1x, &r1y, &v1x, &v1y, &massa_1);
    scanf("%lf %lf %lf %lf %lf\n", &r2x, &r2y, &v2x, &v2y, &massa_2);

    scanf("%d", &tempo_total);
    scanf("%d", &delta_tempo);

    k = tempo_total / delta_tempo;
    for (contador = 0 ; contador <= k; contador ++)
    {
        printf ("%.5g %.5g %.5g %.5g %.5g %.5g\n", r0x, r0y, r1x, r1y, r2x, r2y);

        acel_0x = aceleracao ('x', 0, r0x, r0y, massa_0, r1x, r1y, massa_1, r2x, r2y, massa_2);
        acel_0y = aceleracao ('y', 0, r0x, r0y, massa_0, r1x, r1y, massa_1, r2x, r2y, massa_2);
        acel_1x = aceleracao ('x', 1, r0x, r0y, massa_0, r1x, r1y, massa_1, r2x, r2y, massa_2);
        acel_1y = aceleracao ('y', 1, r0x, r0y, massa_0, r1x, r1y, massa_1, r2x, r2y, massa_2);
        acel_2x = aceleracao ('x', 2, r0x, r0y, massa_0, r1x, r1y, massa_1, r2x, r2y, massa_2);
        acel_2y = aceleracao ('y', 2, r0x, r0y, massa_0, r1x, r1y, massa_1, r2x, r2y, massa_2);

        /*Atualizar os valores que serão usados nos cálculos*/
        atualize (&r0x, &r0y, &v0x, &v0y, acel_0x, acel_0y, delta_tempo);
        atualize (&r1x, &r1y, &v1x, &v1y, acel_1x, acel_1y, delta_tempo);
        atualize (&r2x, &r2y, &v2x, &v2y, acel_2x, acel_2y, delta_tempo);
    }
    return 0;
}
/*Calcular o quadrado de dois numeros*/
double quadrado (double n1)
{
    return n1 * n1;
}
/*Calcular a raiz quadrada de um numero*/
double raiz_quadrada (double x)
{
    double epsilon, erro;
    double raiz, raiz_anterior;
    epsilon = 0.00001;
    erro = epsilon;
    raiz_anterior = x;

    while (erro >= epsilon || erro <= -epsilon)
    {
        raiz = ((raiz_anterior + (x / raiz_anterior))) / 2;
        erro = raiz - raiz_anterior;
        raiz_anterior = raiz;
    }
    return raiz;
}
/*Calcular a distancia entre dois corpos*/
double dist (double r1x, double r1y, double r2x, double r2y)
{
    double delta_x = r1x - r2x;
    double delta_y = r1y - r2y;

    double distancia = raiz_quadrada(quadrado (delta_x) + quadrado (delta_y));

    return distancia;
}
/*Calcular a força total que atua sobre um dos corpos*/
double forca_resultante (double massa_primeiro_planeta, double massa_segundo_planeta, double distancia)
{
    double G = 6.67e-11;
    double forca = (G * massa_primeiro_planeta * massa_segundo_planeta) / quadrado(distancia);

    return forca;
}
/*Calcula a componente de uma força nas direções x e y*/
double forca (char componente, int numero_planeta,double r0x, double r0y, double massa_0,double r1x, double r1y, double massa_1,double r2x, double r2y, double massa_2)
{
    double parcial_1;
    double parcial_2;
    double total;

    if (componente == 'x' && numero_planeta == 0)
    {
        parcial_1 = ((r1x - r0x) / dist (r1x, r1y, r0x, r0y)) * forca_resultante (massa_1, massa_0, dist (r1x, r1y, r0x, r0y));
        parcial_2 = ((r2x - r0x) / dist (r2x, r2y, r0x, r0y)) * forca_resultante (massa_2, massa_0, dist (r2x, r2y, r0x, r0y));
        total = parcial_1 + parcial_2;

    }
    else if (componente == 'x' && numero_planeta == 1)
    {
        parcial_1 = ((r0x - r1x) / dist (r0x, r0y, r1x, r1y)) * forca_resultante (massa_0, massa_1, dist (r0x, r0y, r1x, r1y));
        parcial_2 = ((r2x - r1x) / dist (r2x, r2y, r1x, r1y)) * forca_resultante (massa_2, massa_1, dist (r2x, r2y, r1x, r1y));
        total = parcial_1 + parcial_2;

    }
    else if (componente == 'x' && numero_planeta == 2)
    {
        parcial_1 = ((r0x - r2x) / dist (r0x, r0y, r2x, r2y)) * forca_resultante (massa_0, massa_2, dist (r0x, r0y, r2x, r2y));
        parcial_2 = ((r1x - r2x) / dist (r1x, r1y, r2x, r2y)) * forca_resultante (massa_1, massa_2, dist (r1x, r1y, r2x, r2y));
        total = parcial_1 + parcial_2;

    }
    else if (componente == 'y' && numero_planeta == 0)
    {
        parcial_1 = ((r1y - r0y) / dist (r1x, r1y, r0x, r0y)) * forca_resultante (massa_1, massa_0, dist (r1x, r1y, r0x, r0y));
        parcial_2 = ((r2y - r0y) / dist (r2x, r2y, r0x, r0y)) * forca_resultante (massa_2, massa_0, dist (r2x, r2y, r0x, r0y));
        total = parcial_1 + parcial_2;

    }
    else if (componente == 'y' && numero_planeta == 1)
    {
        parcial_1 = ((r0y - r1y) / dist (r0x, r0y, r1x, r1y)) * forca_resultante (massa_0, massa_1, dist (r0x, r0y, r1x, r1y));
        parcial_2 = ((r2y - r1y) / dist (r2x, r2y, r1x, r1y)) * forca_resultante (massa_2, massa_1, dist (r2x, r2y, r1x, r1y));
        total = parcial_1 + parcial_2;

    }
    else
    {
        parcial_1 = ((r0y - r2y) / dist (r0x, r0y, r2x, r2y)) * forca_resultante (massa_0, massa_2, dist (r0x, r0y, r2x, r2y));
        parcial_2 = ((r1y - r2y) / dist (r1x, r1y, r2x, r2y)) * forca_resultante (massa_1, massa_2, dist (r1x, r1y, r2x, r2y));
        total = parcial_1 + parcial_2;

    }
    return total;
}
/*Calcula as componentes da aceleração dos corpos estudados*/
double aceleracao (char componente, int numero_planeta, double r0x, double r0y, double massa_0,double r1x, double r1y, double massa_1,double r2x, double r2y, double massa_2)
{
    double aceleracao;
    if (numero_planeta == 0)
    {
        aceleracao = (1/ massa_0) * forca (componente, 0, r0x, r0y, massa_0, r1x, r1y, massa_1, r2x, r2y, massa_2);
    }
    else if (numero_planeta == 1)
    {
        aceleracao = (1/ massa_1) * forca (componente, 1, r0x, r0y, massa_0, r1x, r1y, massa_1, r2x, r2y, massa_2);
    }
    else 
    {
        aceleracao = (1/ massa_2) * forca (componente, 2, r0x, r0y, massa_0, r1x, r1y, massa_1, r2x, r2y, massa_2);
    }
    return aceleracao;
}
/*Atualiza os valores das váriaveis armazenados na memoria do computador*/
void atualize(double *rx, double *ry, double *vx, double *vy, double ax, double ay, double dt)
{

    *vx = *vx + ax * dt;
    *vy = *vy + ay * dt;
    *rx = *rx + *vx * dt;
    *ry = *ry + *vy * dt;
}