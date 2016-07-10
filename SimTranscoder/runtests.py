# coding: utf8

import os
import re
import sys

def mean(L):
    return sum(L)/len(L)
    

def verify(mode):
    if mode not in ['heap', 'circular']:
        print '\nOpcao "%s" nao aceita, apenas "heap" ou "circular"\n\n'%(mode,)
        exit()

def run_test(mode):
    number_tests = 10
    

    instancias = [10**1, 10**2, 10**3, 10**4, 10**5, 10**6, 10**7,] 
    inserts_search = re.compile(r'inserções:(\d*)')
    removes_search = re.compile(r'removeu:(\d*)')
    remove_moves_search = re.compile(r'remover:(\d*)')
    insert_moves_search = re.compile(r'inserir:(\d*)')
    overload_search = re.compile(r'sobrecarga:(\d*)')
    time_search = re.compile(r'time:\s(.+)\ss')

    path = os.path.dirname(__file__)

    for instancia in instancias:
        executable = 'transcoder_%s.exe'%(mode,)
        inputfile = 'Dado\\instancia.' + str(instancia)
        outputfile = 'Test\\instancia.' + str(instancia) + '.%s.test'%(mode,)
        for i in range(0,number_tests):
            outputmarker = ' >> ' if i > 0 else ' > '
            cmd = 'ptime ' + executable + ' < ' + inputfile + outputmarker + outputfile
            print(cmd)
            a = os.system(cmd)
        
        result_file = open(outputfile, 'a+')
        file_content = ''.join(result_file.readlines())
        inserts_results = [int(item) for item in inserts_search.findall(file_content)]
        removes_results = [int(item) for item in removes_search.findall(file_content)]
        remove_moves_results = [int(item) for item in remove_moves_search.findall(file_content)]
        insert_moves_results = [int(item) for item in insert_moves_search.findall(file_content)]
        overload_results = [int(item) for item in overload_search.findall(file_content)]
        time_results = [float(item) for item in time_search.findall(file_content)]
        result_file.write('-----------------------------------------------------------------------------------------------------------------------------')
        result_file.write('\nMÉDIAS:\n')
        result_file.write('insercoes, remocoes, movs insercoes, movs remocoes, sobrecargas, tempo, \n')

        medias = (mean(inserts_results), mean(removes_results), mean(remove_moves_results), mean(insert_moves_results), mean(overload_results), mean(time_results)) 

        print medias
        result_file.write("%d, %d, %d, %d, %d, %fs\n"%medias)
        result_file.close()

def compile_code(mode):
    cmd = 'mingw32-make transcoder_%s'%(mode,)
    print cmd
    os.system(cmd)

if __name__ == '__main__':
    mode = sys.argv[1]
    verify(mode)
    compile_code(mode)
    run_test(mode)
