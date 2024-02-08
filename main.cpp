#include <iostream>
#include <math.h>
#include <conio.h>
#include <graphics.h>
using namespace std;
struct pozitie
{
    int lin, col;
};

struct jucator
{
    pozitie pion;
    int nrPereti;
    int color;
};

struct game
{
    int tabla[19][19];
    jucator p1, p2;
    pozitie dimensiune;
    int spatiere;
    int lat;
};
game g; //starea jocului

enum directie
{
    sus, jos, stanga, dreapta,
};
directie tasta_to_dir(char c)
{
    switch (c)
    {
    case 'w':
        return sus;
    case 'a':
        return stanga;
    case 'd':
        return dreapta;
    case 's':
        return jos;
    }
}
bool mutare_corecta(jucator p, char tasta, pozitie &mutare)
{
    bool care_pion=0; //0 player 1; 1 player 2
    directie dir = tasta_to_dir(tasta);
    pozitie d[8]= {{-2, 0}, {2, 0}, {0, -2}, {0, 2},{-2,-2},{2,-2},{2,2},{-2,2} };
    mutare = {p.pion.lin+d[dir].lin, p.pion.col+d[dir].col};
    pozitie obstacol = {(p.pion.lin + mutare.lin)/2, (p.pion.col + mutare.col)/2};
    int pion_1,pion_2;

    switch (g.tabla[mutare.lin][mutare.col])
    {
    case 1:
        return (g.tabla[obstacol.lin][obstacol.col] != 5);
        break;
    case 3:
    case 4:
        if (g.tabla[obstacol.lin][obstacol.col] != 5)
            mutare = {mutare.lin+d[dir].lin, mutare.col+d[dir].col};
        return (g.tabla[mutare.lin][mutare.col]==1);
        break;
    default:
        return false;
    }
}
void draw_tabla(game g, int n)
{
    int i,j,r,cnt=0,cntj;
    r=((getmaxx()+1)-(g.dimensiune.col+1)*g.spatiere)/g.dimensiune.col;
    setfillstyle(SOLID_FILL, WHITE);
    for(i=10; cnt<9; i=i+r+10)
    {
        cntj=0;
        for(j=10; cntj<9; j=j+r+10)
        {
            bar(i,j,i+r,j+r);
            cntj++;
        }
        cnt++;
    }
}
void draw_pion(game g, int nr_juc, int care_pion)
{
    int x, y;
    int nr_col = g.dimensiune.col;
    int spatiere = g.spatiere;
    jucator p;
    if (nr_juc==0)
        p=g.p1;
    else
        p=g.p2;
    int lat = ((getmaxx()+1)-(nr_col+1)*spatiere)/nr_col;

    x = (p.pion.col/2+1)*spatiere+(p.pion.col/2)*lat + lat/2;

    y = (p.pion.lin/2+1)*spatiere+(p.pion.lin/2)*lat + lat/2;

    int r=lat/2*0.8;

    if (nr_juc == care_pion)
    {
        setfillstyle(SOLID_FILL, COLOR(255, 255, 0));
        bar(x - lat/2, y - lat/2, x + lat/2, y + lat/2);
    }
    setcolor(p.color);
    setfillstyle(SOLID_FILL,p.color);
    fillellipse(x,y,r, r);
}
const int di[]= {-1, 0, 1, 0},
                dj[]= { 0, 1, 0,-1};

int A[101][101], n, m, istart, jstart;

void Fill(int i,int j,int v)
{
    if(i >= 1 && i <= 17 && j >= 1 && j <= 17 && A[i][j] == 0)
    {
        A[i][j] = v;
        for(int k = 0 ; k < 4 ; k ++)
            Fill(i + di[k], j + dj[k], v);
    }
}
bool algoritm_umplere_pion1(game &g)
{
    for (int i=1; i<=17; i++)
        for (int j=1; j<=17; j++)
            if (g.tabla[i][j]==1 || g.tabla[i][j]==3 || g.tabla[i][j]==4)
                A[i][j]=0;
            else
                A[i][j]=g.tabla[i][j];

    istart=g.p1.pion.lin;
    jstart=g.p1.pion.col;

    Fill(istart+1, jstart, 9);
    Fill(istart-1, jstart, 9);
    Fill(istart, jstart+1, 9);
    Fill(istart, jstart-1, 9);
    int a=1,b=1,c=1,d=1;
    for(int i =1 ; i <= 17 ; i ++)
        if (A[1][i]!=9 )
            a=0;
    for(int i =1 ; i <= 17 ; i ++)
        if(A[i][1]!=9)
            b=0;
    for(int i =1 ; i <= 17 ; i ++)
        if(A[17][i]!=9)
            c=0;
    for(int i =1 ; i <= 17 ; i ++)
        if(A[i][17]!=9)
            d=0;
    if (a+b+c+d>=3)
        return true;
    return false;
}
bool algoritm_umplere_pion2(game &g)
{
    for (int i=1; i<=17; i++)
        for (int j=1; j<=17; j++)
            if (g.tabla[i][j]==1 || g.tabla[i][j]==3 || g.tabla[i][j]==4)
                A[i][j]=0;
            else
                A[i][j]=g.tabla[i][j];
    n=g.p2.pion.lin;
    m=g.p2.pion.col;
    Fill(n+1, m, 9);
    Fill(n-1, m, 9);
    Fill(n, m+1, 9);
    Fill(n, m-1, 9);
    int a=1,b=1,c=1,d=1;
    for(int i =1 ; i <= 17 ; i ++)
        if (A[1][i]!=9 )
            a=0;
    for(int i =1 ; i <= 17 ; i ++)
        if(A[i][1]!=9)
            b=0;
    for(int i =1 ; i <= 17 ; i ++)
        if(A[17][i]!=9)
            c=0;
    for(int i =1 ; i <= 17 ; i ++)
        if(A[i][17]!=9)
            d=0;
    if (a+b+c+d>=3)
        return true;
    return false;
}
void afisare_consola(game g)
{
    int i,j;
    for (i=0; i<=18; i++)
    {
        for (j=0; j<=18; j++)
            cout<<g.tabla[i][j]<<" ";
        cout<<endl;
    }
}
bool punere_perete(game &g,int &care_pion)
{
    int lat = ((getmaxx()+1)-(g.dimensiune.col+1)*g.spatiere)/g.dimensiune.col;
    int sp=g.spatiere;
    int m=sp; //margine
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        int x=mousex();
        int y=mousey();
        //garduri verticale
        for (int k=0; k<=9; k++)
            if (x>=m+(k+1)*lat+k*sp && x<=m+(k+1)*lat+(k+1)*sp)
                for (int i=0; i<=9; i++)
                    if (y>=m+i*lat+i*sp && y<=m+(i+1)*lat+i*sp)
                        if(g.tabla[2*i+1][2*k+2]!=5 && g.tabla[2*i+2][2*k+2]!=5 && g.tabla[2*i+3][2*k+2]!=5 && g.tabla[2*i+1][2*k+2]!=2 && g.tabla[2*i+2][2*k+2]!=2 && g.tabla[2*i+3][2*k+2]!=2)
                        {
                            if (!care_pion)
                            {
                                if (g.p1.nrPereti<1 )
                                    break;
                                else
                                {
                                    setfillstyle(SOLID_FILL,g.p1.color);
                                    g.p1.nrPereti--;
                                }
                            }
                            else
                            {
                                if (g.p2.nrPereti<1 )
                                    break;
                                else
                                {
                                    setfillstyle(SOLID_FILL,g.p2.color);
                                    g.p2.nrPereti--;
                                }
                            }
                            g.tabla[2*i+1][2*k+2]=5;
                            g.tabla[2*i+2][2*k+2]=5;
                            g.tabla[2*i+3][2*k+2]=5;
                            if(!algoritm_umplere_pion1(g) || !algoritm_umplere_pion2(g))
                            {
                                g.tabla[2*i+1][2*k+2]=0;
                                g.tabla[2*i+2][2*k+2]=0;
                                g.tabla[2*i+3][2*k+2]=0;
                            }
                            else
                            {
                                bar(m+(k+1)*lat+k*sp, m+i*lat+i*sp, m+(k+1)*lat+(k+1)*sp, m+(i+2)*lat+(i+1)*sp);
                                cout<<"Numar pereti ramasi jucator rosu "<<g.p1.nrPereti<<endl;
                                cout<<"Numar pereti ramasi jucator albastru "<<g.p2.nrPereti<<endl;
                                return true;
                            }
                        }
        //garduri orizontale
        for (int i=0; i<=9; i++)
            if (y>=m+(i+1)*lat+i*sp && y<=m+(i+1)*lat+(i+1)*sp)
                for (int j=0; j<=9; j++)
                    if (x>=m+j*lat+j*sp && x<=m+(j+1)*lat+j*sp)
                        if (g.tabla[2*i+2][2*j+1]!=5 && g.tabla[2*i+2][2*j+2]!=5 && g.tabla[2*i+2][2*j+3]!=5 && g.tabla[2*i+2][2*j+1]!=2 &&g.tabla[2*i+2][2*j+2]!=2&& g.tabla[2*i+2][2*j+3]!=2)
                        {
                            if (!care_pion)
                            {
                                if (g.p1.nrPereti<=0)
                                    break;
                                else
                                {
                                    setfillstyle(SOLID_FILL,g.p1.color);
                                    g.p1.nrPereti--;
                                }
                            }
                            else
                            {
                                if (g.p2.nrPereti<=0 )
                                    break;
                                else
                                {
                                    setfillstyle(SOLID_FILL,g.p2.color);
                                    g.p2.nrPereti--;
                                }
                            }
                            g.tabla[2*i+2][2*j+1]=5;
                            g.tabla[2*i+2][2*j+2]=5;
                            g.tabla[2*i+2][2*j+3]=5;
                            if(!algoritm_umplere_pion1(g) || !algoritm_umplere_pion2(g))
                            {
                                g.tabla[2*i+2][2*j+1]=0;
                                g.tabla[2*i+2][2*j+2]=0;
                                g.tabla[2*i+2][2*j+3]=0;
                            }
                            else
                            {
                                bar(m+j*lat+j*sp, m+(i+1)*lat+i*sp,m+(j+2)*lat+(j+1)*sp, m+(i+1)*lat+(i+1)*sp);
                                cout<<"Numar pereti ramasi jucator rosu "<<g.p1.nrPereti<<endl;
                                cout<<"Numar pereti ramasi jucator albastru "<<g.p2.nrPereti<<endl;
                                return true;
                            }
                        }


    }
    return false;
}

int main()
{
    cout<<" QUORIDOR - Regulament "<<endl;
    cout<<endl<<"Prezentare - un platou de joc 9 x 9 , 20 de bariere si 2 pioni. "<<endl;
    cout<<"Scopul jocului: De a ajunge primul pe linia opusa liniei de plecare  "<<endl;
    cout<<"La inceputul jocului fiecare jucator are cate 10 bariere.  "<<endl;
    cout<<"Jucatorul rosu incepe.  "<<endl;
    cout<<endl<<"Derularea unei partide: "<<endl;
    cout<<"Pe rand, fiecare jucator alege intre a-si misca pionul sau a-si aseza una dintre bariere. Daca un jucator isi termina barierele este obligat sa-si deplaseze pionul."<<endl;
    cout<<endl<<"Deplasarea pionilor: Pionii se deplaseaza orizontal, vertical, inainte sau inapoi cu o casuta, dar barierele trebuie ocolite.  "<<endl;
    cout<<endl<<"Asezarea barierelor: O bariera trebuie asezata exact intre doua casute. Asezarea barierei are ca scop crearea propriului drum sau de a incetini avansarea adversarului, dar este interzis de a-i bloca toate caile de acces la linia de sosire; trebuie lasata intotdeauna o cale de iesire.  "<<endl;
    cout<<endl<<"Fata in fata: Cand doi pioni se afla fata în fata pe doua casute alaturate neseparate de o bariera, jucatorul care trebuie să mute, poate sari peste pionul adversarului, asezandu-se in spatele acestuia, Daca, în spatele pionului care trebuie sarit, se afla o bariera, jucatorul poate alege casuta din stanga sau dreapta acestui pion.  "<<endl;
    cout<<endl<<"Incheierea partidei: Primul jucator care ajunge cu pionul intr-una dintre cele 9 casute de pe linia de sosire (opusa celei de plecare), castiga."<<endl;
    cout<<endl<<"ATENTIE!"<<endl;
    cout<<endl<<"PENTRU DEPLASAREA PIONILOR SE FOLOSESC URMATORELE TASTE: "<<endl;
    cout<<endl<<"w - sus          d - dreapta         s - jos         a - stanga  "<<endl;
    cout<<endl<<"Daca, in spatele pionului care trebuie sarit, se afla o bariera, jucatorul poate alege casuta din stanga sau dreapta acestui pion.  "<<endl;
    cout<<endl<<"q - stanga sus    z - stanga jos    c  - dreapta jos    e - dreapta sus"<<endl;
    cout<<endl<<"PENTRU AMPLASAREA BARIERELOR SE DA CLICK PE ZONA UNDE SE DORESTE AMPLASAREA SI SE APASA TASTA  p "<<endl;
    cout<<endl<<"               START"<<endl;
    cout<<endl;
    int i,j;
    for (i=0; i<=18; i++)
        for (j=0; j<=18; j++)
            g.tabla[i][j]=0;
    for (i=0; i<=18; i++)
    {
        g.tabla[0][i]=2;
        g.tabla[i][0]=2;
        g.tabla[i][18]=2;
        g.tabla[18][i]=2;
    }
    for (i=1; i<18; i=i+2)
    {
        for (j=1; j<18; j=j+2)
            g.tabla[i][j]=1;
    }
    g.p1.pion.lin=17; //linia pion1
    g.p1.pion.col=9; //coloana pion1
    g.p2.pion.lin=1; //linia pion2
    g.p2.pion.col=9; //coloana pion2
    g.p1.nrPereti=10; //nr de pereti pion1
    g.p2.nrPereti=10; //nr de pereti pion2
    g.p1.color=COLOR(255,0,0);//culoare pion1 rosu
    g.p2.color=COLOR(0,0,255);//culoare pion2 albastru
    g.spatiere=10;
    g.dimensiune.col=9;
    g.tabla[g.p1.pion.lin][g.p1.pion.col]=3;
    g.tabla[g.p2.pion.lin][g.p2.pion.col]=4;
    int care_pion; //0 player 1; 1 player 2*/
    care_pion=0;
    initwindow(600,600,"Quoridor");
    draw_tabla(g,600);
    draw_pion(g,1, care_pion);
    draw_pion(g,0, care_pion);
    jucator p;
    directie dir;
    int var; //char c;
    g.p1.color=COLOR(255,0,0);//culoare pion1 rosu
    g.p2.color=COLOR(0,0,255);//culoare pion2 albastru
    while (!(g.p1.pion.lin==1 || g.p2.pion.lin==17))//nu a castigat
    {
inceput:
        char c;
        if (care_pion==0) //alegem player-ul curent
        {
            p=g.p1;
            cout<<"Jucatorul rosu joaca"<<endl;
        }
        else
        {
            p=g.p2;
            cout<<"Jucatorul albastru joaca"<<endl;
        }

        pozitie mutare;
        int mutare_valida;
        do
        {
            pozitie d[8]= {{-2, 0}, {2, 0}, {0, -2}, {0, 2},{-2,-2},{2,-2},{2,2},{-2,2} };
            c = getch(); //preluam caracter de la tastatura
            if (c=='p')
                if(punere_perete(g,care_pion))
                {
                    punere_perete(g,care_pion);
                    care_pion = !care_pion;
                draw_tabla(g,600);
                draw_pion(g,1, care_pion);
                draw_pion(g,0, care_pion);
                cout<<endl;
                goto inceput;
                }
            if (c=='q')
            {
                mutare = {p.pion.lin+d[4].lin, p.pion.col+d[4].col};
                goto start;
            }
            if (c=='z')
            {
                mutare = {p.pion.lin+d[5].lin, p.pion.col+d[5].col};
                goto start;
            }
            if (c=='c')
            {
                mutare = {p.pion.lin+d[6].lin, p.pion.col+d[6].col};
                goto start;
            }
            if (c=='e')
            {
                mutare = {p.pion.lin+d[7].lin, p.pion.col+d[7].col};
                goto start;
            }
            mutare_valida=0;
            if (strchr("wasdp", c)) //este tasta permisa
                mutare_valida = mutare_corecta(p, c, mutare);



        }
        while (!mutare_valida ||c=='p');
start:
        g.tabla[p.pion.lin][p.pion.col]=1; //pozitie veche eliberata pe tabla
        p.pion = mutare;
        if (care_pion==1)   //actualizare pozitie pion din joc
            g.p2.pion=p.pion;
        else
            g.p1.pion=p.pion;
        if (care_pion==0) //pozitie noua ocupata pe tabla
            g.tabla[p.pion.lin][p.pion.col]=3;
        else
            g.tabla[p.pion.lin][p.pion.col]=4;
        care_pion = !care_pion;
        draw_tabla(g,600);
        draw_pion(g,1, care_pion);
        draw_pion(g,0, care_pion);
        cout<<endl;
    }
    char mesaj[51];
    if (!care_pion)
        strcpy(mesaj, "Player albastru a castigat!");
    else
        strcpy(mesaj, "Player rosu a castigat!");
    setbkcolor(BLACK);
    setcolor(WHITE);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    settextstyle(COMPLEX_FONT, HORIZ_DIR, 0);
    setusercharsize(1, 1, 1, 1);
    outtextxy((getmaxx()+1)/2, (getmaxx()+1)/2, mesaj);
    getch();
    closegraph();
    return 0;
}
