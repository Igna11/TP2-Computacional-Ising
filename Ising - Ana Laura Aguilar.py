#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jun 26 15:36:56 2018

@author: batman
"""

#import pyprind
import numpy as np
from matplotlib import pyplot as plt
#%%
def Inicial(L):   
    # Genera un estado inicial aleatorio
    S = 2*np.random.randint(2, size=(L,L))-1
    return S

def EnergiaPV(S,i,j):    
    # Obtiene el tamaño de la red
    L = S.shape[0];
    # Calcula la energía de interacción a primeros vecinos
    Epv = -S[i,j]*(S[i+1-(i==L-1)*L,j] + S[i-1+(i==0)*L,j] + 
                    S[i,j+1-(j==L-1)*L] + S[i,j-1+(j==0)*L]);
    return Epv
    
def MC2D(L, S, beta):
    for a in range (L):
        for b in range (L):               
            #Genera una posición al azar
            (i,j) = np.random.randint(L,size=2);        
            #Calcula las energias con y sin cambio de spin
            dE = -2 * EnergiaPV(S,i,j)        
            #Genera un numero al azar entre 0 y 1
            dado = np.random.rand();        
            #Calcula la probabilidad del método Metrópolis y evalúa el cambio
            prob = np.exp(-beta * dE); 
            if dE<0:
                S[i,j] = -S[i,j];
            elif (prob > dado):
                #Acepta el cambio
                S[i,j] = -S[i,j];
    return  S

def Energia(S):    
    Etotal=0;
    L = S.shape[0];
    # B=0
    for i in range(L-1):
        for j in range(L-1):
            Etotal += EnergiaPV(S,i,j);     
    return Etotal
    
def Magnet(S):
    # Calcula la magnetización como la suma de todos los espines
    M = np.sum(S)
    return M
#%%
# Tamaño de la red LxL
L=32
# Nro. de pasos para el cálculo de Monte Carlo
nMC=150
#Longitud del vector de temperatura
nT=90
# Divide por nro. de muestras y del sistema para tener valores intensivos
n1, n2  = 1.0/(nMC*L*L), 1.0/(nMC*nMC*L*L) 

T = np.linspace(1.53, 3.28, nT); 
E,M,C,X, = np.zeros(nT), np.zeros(nT), np.zeros(nT), np.zeros(nT)

#BarMC = pyprind.ProgBar(nT, width=40)
    
for p in range(nT):
    E2 = M2 = E3 = M3 = C1= 0
    S = Inicial(L)
    b=1.0/T[p]; b2=b**2;       

    for i in range(nMC):
        MC2D(L, S, b)           
        Ene = Energia(S)     
        Mag = Magnet(S)        

        E2 = E2 + Ene
        M2 = M2 + Mag
        M3 = M3 + Mag**2
        E3 = E3 + Ene**2

    E[p] = n1*E2
    M[p] = n1*M2
    C[p] = (n1*E3 - n2*E2*E2)*b2
    X[p] = (n1*M3 - n2*M2*M2)*b
    #BarMC.update()

#%%
figura1 = plt.figure(figsize=(8, 7)); 
plt.subplots_adjust(hspace=0.1);    

sp3 =  figura1.add_subplot(2, 1, 1 );
plt.setp(sp3.set_xticklabels([]))
plt.scatter(T, E, marker='o', color='#007052', edgecolor='#007052')
plt.axvline(x=2.26,linestyle='--', linewidth=2, color='#686868', label="Tc") 
plt.ylabel("Energía", fontsize=14);         plt.axis('tight');
sp3.spines['right'].set_visible(False)
sp3.spines['top'].set_visible(False)
plt.legend(loc='upper left', frameon=False)

sp4 =  figura1.add_subplot(2, 1, 2);
plt.setp(sp4.get_xticklabels(), fontsize=10)
plt.scatter(T, abs(M), marker='o', color='#860c0c')
plt.axvline(x=2.26,linestyle='--', linewidth=2, color='#686868', label="Tc")
plt.xlabel("Temperatura(T)", fontsize=14); 
plt.ylabel("Magnetización", fontsize=14);   plt.axis('tight');
sp4.spines['right'].set_visible(False)
sp4.spines['top'].set_visible(False)

figura2 = plt.figure(figsize=(8, 7)); 
plt.subplots_adjust(hspace=0.1);

sp5 =  figura2.add_subplot(2, 1, 1 );
plt.setp(sp5.set_xticklabels([]))
plt.scatter(T, C, marker='o', color='#e29700') 
plt.axvline(x=2.26,linestyle='--', linewidth=2, color='#686868', label="Tc") 
plt.ylabel("Calor Específico", fontsize=14);   plt.axis('tight'); 
sp5.spines['right'].set_visible(False)
sp5.spines['top'].set_visible(False)  
plt.legend(loc='upper right', frameon=False)

sp6 =  figura2.add_subplot(2, 1, 2);
plt.scatter(T, X, marker='o', color='#4993dd')
plt.axvline(x=2.26,linestyle='--', linewidth=2, color='#686868', label="Tc")
plt.xlabel("Temperatura(T)", fontsize=14); 
plt.ylabel("Susceptibilidad", fontsize=14);   plt.axis('tight');
sp6.spines['right'].set_visible(False)
sp6.spines['top'].set_visible(False)



#%% A PARTIR DE ACÁ NO!!
#Longitud del vector de temperatura
nT=90
# Nro. de pasos para llegar al equilibrio
nEq = 10500
# Divide por nro. de muestras y del sistema para tener valores intensivos
m = 1.0/(L**2) 
#%%
L=32
It = np.linspace(0, nEq, nEq)
Eeq, Meq = np.zeros(nEq), np.zeros(nEq)
Teq = 1
B = 1/Teq
S = Inicial(L)
#BarEq = pyprind.ProgBar(nEq, width=40)
for i in range(nEq):
    MC2D(L, S, B)
    Eneq = Energia(S)
    Mageq = Magnet(S)
    Eeq[i] = Eneq*m
    Meq[i] = Mageq*m
#    BarEq.update()
#%% 
figuraEq = plt.figure(figsize=(8, 7));
plt.subplots_adjust(hspace=0.001);    

sp1 =  plt.subplot(2, 1, 2 );
plt.plot(It, Eeq, linestyle = '-', color='r')
plt.setp(sp1.get_xticklabels(), fontsize=10)
plt.xlabel("Iteraciones", fontsize=14);
plt.ylabel("Energía", fontsize=14);         plt.axis('tight');
sp1.spines['right'].set_visible(False)
sp1.spines['top'].set_visible(False)

sp2 =  plt.subplot(2, 1, 1 , sharex=sp1)
axbox = sp2.get_position()
plt.setp(sp2.get_xticklabels(), visible=False);
plt.plot(It, abs(Meq), linestyle = '-', color='b')
#plt.axvline(x=400,linestyle='--', label="400") 
plt.ylabel("Magnetización por sitio", fontsize=14);   plt.axis('normal');
sp2.spines['right'].set_visible(False)
sp2.spines['top'].set_visible(False)
#plt.legend(loc = 3)