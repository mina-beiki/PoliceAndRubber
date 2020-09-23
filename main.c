#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


//NOTE : !!!!!!!!!!!!!system cls va clear hichkodoom baraye compiler man kar nmikard. pas man mohito ba fasele dar har marhale
//chap mikonam vali dar soorati ke compiler kar kone o bkhaim bzarim bayad line haye 87 o 88 va 279 o 280 , har do
// sleep(500); va system("cls");   bashan .!!!!!!!!!!!!!!!!
int t = 1, n, m, x[1000][1000], rob_move = 0, pol_move = 0, yrob, xrob;

int see_robber(int irob, int jrob, int ipol, int jpol) {
    int dist;
    dist = sqrt(pow(irob - ipol, 2) + pow(jrob - jpol, 2));
    if (dist <= (2 * sqrt(2)))
        return 1; //police dozd ro mibine2
    else
        return 0;//nemibine
}
int main() {
    int ps, i, j, xpol, ypol, sumtedadpolice = 0, psno[10000];
    srand(time(NULL));
    printf("Size of environment?\n-For example :3 4-\n");
    scanf("%d %d", &m, &n);
    int x[m][n];
    //meghdare avalie araye 2bodi ro sefr mizarim
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            x[i][j] = 0;
        }
    }
    printf("Number of police stations ?\n");
    scanf("%d", &ps); //ps stands for police station
    int s[ps]; //s stands for station
    for (i = 0; i < ps; i++) {
        int temp;
        printf("Number of police in station %d ?", i + 1);
        scanf("%d", &temp);
        s[i] = temp;
        sumtedadpolice += temp;
    }
    //zakhrie kardane shomare kalantari baraye har police :
    int counter = 0;
    for (i = 0; i < ps; i++) {
        for (j = 0; j < s[i]; j++) {
            psno[counter] = i + 1;
            counter++;
        }
    } //robbers first place :
    xrob = rand() % n;
    yrob = rand() % m;
    x[yrob][xrob] = 1;//dozd ro too on khoone mizarim
    int k = 0;
    //police first place :
    for (i = 0; i < ps; i++) {//baraye har kalantari
        for (j = 0; j < s[i]; j++) {//tedade police ha dar har kalantari
            xpol = rand() % n;
            ypol = rand() % m;
            if (x[ypol][xpol] == 0)  //agar oon khoone khali bashe
                x[ypol][xpol] = 3;// har ja police hast oon khune meghdares 3 hast .
            else {
                while (k != 1) { //agar khali nabood mire soraghe khune hayi dge va engahd in karo anjam mide ta khune khali peida she
                    xpol = rand() % n;
                    ypol = rand() % m;
                    if (x[ypol][xpol] == 0) {
                        x[ypol][xpol] = 3;
                        k = 1;
                    }//if
                }//while
            }//else
        }
    }
    int pol_x[1000], pol_y[1000]; //arayeyi ke x o y police ha baraye har police tosh zakhire mishe .
    //FIRST TIME PRINT:
    counter = 0; //shemordane tedade police haye kol
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (x[i][j] == 0) {
                printf("0   ");//yani hichkas to on khoone nist
            } else if (x[i][j] == 1) {
                printf("T   ");// yani dozd to oon khoonast
            } else if (x[i][j] == 3) {//yani police to oon khoonast
                pol_y[counter] = i;
                pol_x[counter] = j;
                printf("D%d  ", psno[counter]);
                counter++;
            }
        }
        printf("\n");
    }


    int endplaying = 0;
    while (endplaying != 1) {
        //ROBBER MOVES  :
        int xrob2, yrob2;
        while (k != 1) {
            xrob2 = xrob + ((rand() % 3) - 1);
            yrob2 = yrob + ((rand() % 3) - 1);
            //baraye inke az safhe biroon nazane :
            if (yrob2 > (m - 1)) { //m-1 chon x o y ha az 0 shoro mishan
                while (yrob2 > (m - 1)) {
                    yrob2 -= 1;
                }
            }
            if (xrob2 > (n - 1)) {
                while (xrob2 > (n - 1)) {
                    xrob2 -= 1;
                }
            }
            if (xrob2 < 0 || yrob2 < 0) {
                while (xrob2 < 0) {
                    xrob2++;
                }
                while (yrob2 < 0) {
                    yrob2++;
                }
            }
            if (x[yrob2][xrob2] == 0) { //agar oon khuneye jadid khali bood , agar na sare jash mimone .
                x[yrob][xrob] = 0; //jaye ghabli ro khali kone
                x[yrob2][xrob2] = 1; // jaye jadid ro dozd bezare
                yrob = yrob2;
                xrob = xrob2;
                rob_move++;
                t++;
                k = 1;
            }
        }
        //POLICE MOVE:
        char etela[sumtedadpolice + 1];
        k = 0;counter = 0;
        int a;
        for (i = 0; i < ps; i++) {
            for (j = 0; j < s[i]; j++) {
                a = see_robber(xrob, yrob, pol_x[counter], pol_y[counter]);
                if (a == 1)
                    etela[i] = 'y'; //yani kalantarie shomare x etela daran az mahale dozd
                else
                    etela[i] = 'n';
                counter++;
            }
        }
        counter = -1; //chon avalin bar ezafe mishe va mishe 0
        for (i = 0; i < ps; i++) {
            for (j = 0; j < s[i]; j++) {
                counter++;
                if (etela[i] == 'y') { //agar oon kalantari az mahale dozd etela dashte bashe
                    //be dozd nazdik beshe :
                    int yghabli = pol_y[counter];
                    int xghabli = pol_x[counter];
                    if (xrob > pol_x[counter]) {
                        if (yrob > pol_y[counter]) {
                            x[pol_y[counter]][pol_x[counter]] = 0;
                            pol_y[counter] += 1;
                            pol_x[counter] += 1;
                        } else if (yrob == pol_y[counter]) {
                            x[pol_y[counter]][pol_x[counter]] = 0;
                            pol_x[counter] += 1;
                        } else if (yrob < pol_y[counter]) {
                            x[pol_y[counter]][pol_x[counter]] = 0;
                            pol_x[counter] += 1;
                            pol_y[counter] -= 1;
                        }
                    } else if (xrob < pol_x[counter]) {
                        if (yrob > pol_y[counter]) {
                            x[pol_y[counter]][pol_x[counter]] = 0;
                            pol_x[counter] -= 1;
                            pol_y[counter] += 1;
                        } else if (yrob < pol_y[counter]) {
                            x[pol_y[counter]][pol_x[counter]] = 0;
                            pol_x[counter] -= 1;
                            pol_y[counter] -= 1;
                        } else if (yrob == pol_y[counter]) {
                            x[pol_y[counter]][pol_x[counter]] = 0;
                            pol_x[counter] -= 1;
                        }
                    } else if (xrob == pol_x[counter]) {
                        if (yrob > pol_y[counter]) {
                            x[pol_y[counter]][pol_x[counter]] = 0;
                            pol_y[counter] += 1;
                        } else if (yrob < pol_y[counter]) {
                            x[pol_y[counter]][pol_x[counter]] = 0;
                            pol_y[counter] -= 1;
                        }
                    }
                    if (x[pol_y[counter]][pol_x[counter]] != 3) { //agar police onja nabood be on khune bere
                        x[pol_y[counter]][pol_x[counter]] = 3;
                        pol_move++;
                    } else { //age police to oon khune bood sare jash bmone
                        pol_y[counter]=yghabli ;
                        pol_x[counter]=xghabli ;
                    }

                    //baraye inke az safhe biroon nazane :
                    if (pol_y[counter] > (m - 1))
                        while (pol_y[counter] > (m - 1)) {
                            pol_y[counter] -= 1;
                        }
                    if (pol_x[counter] > (n - 1))
                        while (pol_y[counter] > (n - 1)) {
                            pol_y[counter] -= 1;
                        }
                    if (pol_x[counter] < 0 || pol_y[counter] < 0) {
                        while (pol_x[counter] < 0) {
                            pol_x[counter]++;
                        }
                        while (pol_y[counter] < 0) {
                            pol_y[counter]++;
                        }
                    }
                    if (pol_y[counter] == yrob && pol_x[counter] == xrob) {
                        int counter2 = 0;
                        printf("\n\n\n");
                        for (i = 0; i < m; i++) {
                            for (j = 0; j < n; j++) {
                                if (x[i][j] == 0) {
                                    printf("0   ");//yani hichkas to on khoone nist
                                } else if (x[i][j] == 1) {
                                    printf("T   ");// yani dozd to oon khoonast
                                } else if (x[i][j] == 3) {
                                    printf("D%d  ", psno[counter2]);//yani police to oon khoonast
                                    counter2++;
                                }
                            }
                            printf("\n");
                        }
                        printf("\nMisson Completed !\nTotal Time=%d\n", t);
                        printf("Total Movements Of Police=%d\nTotal Movements Of Robber=%d\n", pol_move, rob_move);
                        return 0;
                    }
                } else { //agar jaye dozd ro nmidone be toore random harkat mikone :
                    k = 0;
                    while (k != 1) {
                        xpol = rand() % n;
                        ypol = rand() % m;
                        if (x[ypol][xpol] != 3) {
                            x[pol_y[counter]][pol_x[counter]] = 0;
                            x[ypol][xpol] = 3;
                            pol_y[counter] = ypol;
                            pol_x[counter] = xpol;
                            pol_move++;
                            k = 1;
                        }//if
                    }//while
                    if (pol_y[counter] == yrob && pol_x[counter] == xrob) {
                        int counter2 = 0;
                        printf("\n\n\n");
                        for (i = 0; i < m; i++) {
                            for (j = 0; j < n; j++) {
                                if (x[i][j] == 0) {
                                    printf("0   ");//yani hichkas to on khoone nist
                                } else if (x[i][j] == 1) {
                                    printf("T   ");// yani dozd to oon khoonast
                                } else if (x[i][j] == 3) {
                                    printf("D%d  ", psno[counter2]);//yani police to oon khoonast
                                    counter2++;
                                }
                            }
                            printf("\n");
                        }
                        printf("\nMisson Completed !\nTotal Time=%d\n", t);
                        printf("Total Movements Of Police=%d\nTotal Movements Of Robber=%d\n", pol_move, rob_move);
                        return 0;
                    }
                }//else etela
            }//for2
        }//for1
        counter = 0;
        printf("\n\n\n");
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                if (x[i][j] == 0) {
                    printf("0   ");//yani hichkas to on khoone nist
                } else if (x[i][j] == 1) {
                    printf("T   ");// yani dozd to oon khoonast
                } else if (x[i][j] == 3) {
                    printf("D%d  ", psno[counter]);//yani police to oon khoonast
                    counter++;
                }
            }
            printf("\n");
        }


    }//while end playing
}
