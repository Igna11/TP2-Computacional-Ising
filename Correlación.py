#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Jun 30 13:48:31 2018

@author: batman
"""
import pyprind
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
#%%        
# Tamaño de la red LxL
L=20
# Nro. de pasos para el cálculo de Monte Carlo
nMC=10000
# Nro. de pasos para correlación
nCorr = 7000
#Vectores para la correlación
x = np.arange(L/2)
Tcorr = 2.1
Corr = np.zeros(len(x))
#BarMC = pyprind.ProgBar(nMC, width=50)
#BarnCorr = pyprind.ProgBar(nCorr, width=50)
S = Inicial(L)

for i in range (nMC):
    S = MC2D(L,S,1/Tcorr)
#    BarMC.update()

Sii = np.zeros(nCorr)
SIJ = np.zeros((len(x),nCorr))  
for t in range (nCorr):
    S=MC2D(L, S, 1/Tcorr)
    Sii[t] = S[0,0]
    for l in range(len(x)):
        SIJ[l,t] = S[0,l]
#    BarnCorr.update()
    
#%%
Corr1 = np.zeros(len(x))
Corr2 = np.zeros(len(x))

Sij = np.sum(SIJ,axis=1)

for i in range (len(x)):
    for j in range (nCorr):
        Prod = Sii[:]*SIJ[:,:]

Corr1 = np.sum(Prod,axis=1)
Corr2 = sum(Sii)*Sij
Corr = Corr1/(nCorr) - Corr2/((nCorr)**2)
#%%
figura3 = plt.figure(figsize=(8,7))
plt.ylim(-0.2,2)
sp =  plt.subplot(111);
#plt.setp(sp.get_xticklabels(), fontsize=10)
sp.plot(x, CorrT15, linestyle = ':', marker='o', color='mediumturquoise', 
        markeredgecolor='None', label='1.5')
sp.plot(x, CorrT2, linestyle = ':', marker='o', color='pink', 
        markeredgecolor='None', label='2')
sp.plot(x, CorrT226, linestyle = ':', marker='o', color='k', 
        markeredgecolor='None', label='2.26')
sp.plot(x, CorrT23, linestyle = ':', marker='o', color='g', 
        markeredgecolor='None', label='2.3')
sp.plot(x, CorrT25, linestyle = ':', marker='o', color='firebrick', 
        markeredgecolor='None', label='2.5')
sp.plot(x, CorrT3, linestyle = ':', marker='o', color='darkviolet', 
        markeredgecolor='None', label='3')
sp.plot(x, CorrT35, linestyle = ':', marker='o', color='y', 
        markeredgecolor='None', label='3.5')
sp.plot(x, CorrT4, linestyle = ':', marker='o', color='gray', 
        markeredgecolor='None', label='4')
sp.set_xlim([0, 5])
plt.ylabel("Correlación", fontsize=18); 
plt.xlabel("Distancia entre spines", fontsize=18);   plt.axis('tight');
plt.legend(loc='upper right', frameon=False, fontsize='x-large')
sp.spines['right'].set_visible(False)
sp.spines['top'].set_visible(False)

#%%
C = np.array([CorrT15, CorrT2, CorrT21, CorrT226, CorrT23, CorrT25, CorrT3, 
              CorrT35, CorrT4])
m = np.zeros(len(x))
c = np.zeros(len(x))
l = []
for i in range (len(C)):
    for j in range (len(x)):
        c[j] = abs(C[i,j])
        m[j] = -x[j]/np.log(c[j])
        prom = sum(m)/len(x)
    l.append(prom)