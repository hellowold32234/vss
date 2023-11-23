#define __debug__
#define __timer__
#include "linear_gkr/zk_verifier.h"
#include "linear_gkr/zk_prover.h"
#include "linear_gkr/prime_field.h"
#include <iostream>
#include <cassert>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <stdio.h>
#include <string.h>
zk_verifier v;
zk_prover p;



int main(int argc, char** argv)
{
	//std::cout << "hello world" << std::endl;
	int n, t;
	if(argc != 6)
	{
		printf("usage: ./main circuit_path meta_data_path log_path log_#of_verifiers log_#of_degree\n");
		return 0;
	}
	sscanf(argv[4], "%d", &n);
	sscanf(argv[5], "%d", &t);
	prime_field::init();
	p.total_time = 0;
	p.log_num_degree = v.log_num_degree = t;
	p.log_num_verifier = v.log_num_verifier = n;
	v.get_prover(&p);
	//std::cout << "come in" << std::endl;
	
	v.read_circuit(argv[1], argv[2]);
	//std::cout << "after readfile" << std::endl;
	p.get_circuit(v.C);
	bool result = v.verify(argv[3]);
	printf("%s\n", result ? "Pass" : "Fail");
	int i=64;
	printf("S 	S_Time    	Our_Time 	Size 	 Our_Size\n");
	//for(int j=0;j<p.log_num_degree;j++){
	//printf("Please enter a number:");
	//scanf("%d", &i); 
	//int j=1<<i;
	v.broadcast(i);
	//i=i<<1;
	//}
	p.delete_self();
	v.delete_self();
	return 0;
}
