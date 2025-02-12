"""
****************************************************************************
*                                                                          
* Aluno: Jonatas Cleyton Fonseca Coelho                                                      
* Matricula: 20241045050120                                                          
*                                                                          
* Avaliacao 04: Trabalho Final                                              
* 04.505.23-2024.2 - Prof. Daniel Ferreira                                  
*                                                                          
* Compilador: gcc version 13.3.0 (Ubuntu 13.3.0-6ubuntu2~24.04)                    
*                                                                           
****************************************************************************/
"""

import pandas as pd
import matplotlib.pyplot as plt
from tkinter import Tk, filedialog

def plot_histogram():

    root = Tk()
    root.withdraw()  
    

    filepath = filedialog.askopenfilename(
        title="Selecione o arquivo de histograma",
        filetypes=[("CSV Files", "*.csv"), ("All Files", "*.*")]
    )
    
    if not filepath: 
        print("Nenhum arquivo selecionado!")
        return
    
    try:

        df = pd.read_csv(filepath)
        

        plt.figure(figsize=(12, 6))
        plt.bar(df['Intensidade'], df['Normalizado'], width=1.0, color='blue')
        

        plt.title(f"Histograma - {filepath.split('/')[-1]}")
        plt.xlabel("Intensidade do Pixel")
        plt.ylabel("Frequência Normalizada")
        plt.xlim(0, 255)
        plt.grid(axis='y', alpha=0.5)
        
        plt.show()
        
    except Exception as e:
        print(f"Erro ao processar arquivo: {str(e)}")

if __name__ == "__main__":
    plot_histogram()
    plt.close('all')  