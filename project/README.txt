A compilação do cliente: ./cliente 127.0.0.1 22000 Fulano
A compilação do servidor:  ./servidor 9990 BATEPAPO 

Obs.: algumas vezes a conexão não é estabelecida provavelmente pela existencia da função
que mostra o IP do cliente (localizado no arquivo do servidor, no while 1 da main). Talvez seja
necessário executar o servidor e o cliente de novo pra garantir o funcionamento.

Obs.: tentei deixar a apresentação do código mais bonita com outro strcat, porém o programa
todo bugava então preferi pelo funcionamento.