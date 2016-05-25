#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <thread>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <curl/curl.h>

using namespace std;

/**
 * Obtém a URL correta a partir de um ID.
 */
static char* get_URL(int urlID) {
  char* result = "";

  switch (urlID) {
    case 1:
      result = "https://apitestes.info.ufrn.br/unidades-services/services/consulta/unidade/de";
      break;
    case 2:
      result = "https://apitestes.info.ufrn.br/unidades-services/services/consulta/unidade/pa";
      break;
    case 3:
      result = "https://apitestes.info.ufrn.br/unidades-services/services/consulta/unidade/ta";
      break;
    case 4:
      result = "https://apitestes.info.ufrn.br/unidades-services/services/consulta/unidade/me";
      break;
    case 5:
      result = "https://apitestes.info.ufrn.br/unidades-services/services/consulta/unidade/to";
      break;
    case 6:
      result = "https://apitestes.info.ufrn.br/servidor-services/services/consulta/servidor/lotacao/ct";
      break;
    case 7:
      result = "https://apitestes.info.ufrn.br/concursos-services/services/consulta/concurso";
      break;
    case 8:
      result = "https://apitestes.info.ufrn.br/biblioteca-services/services/consulta/biblioteca/materiais";
      break;
    case 9:
      result = "https://apitestes.info.ufrn.br/telefone-services/services/consulta/telefone/ccet";
      break;
    default:
      result = "https://apitestes.info.ufrn.br/unidades-services/services/consulta/unidade/ce";
      break;
  }

  return result;
}

/**
 * Obtém o texto retornado na requisição HTTP GET e salva-o em um arquivo.
 */
void get_data(string filename, int urlID) {
  CURL *curl;
  CURLcode res;
  FILE *hd_src;
  string path = "/tmp/" + filename + ".txt";

  hd_src = fopen(path.c_str(), "w+");

  curl = curl_easy_init();

  if (curl) {
    struct curl_slist *chunk = NULL;
    chunk = curl_slist_append(chunk, "Authorization: Bearer 6e7ab608-e759-420c-a99f-a4cd2c4b7da2");
    
    curl_easy_setopt(curl, CURLOPT_URL, get_URL(urlID));
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, hd_src);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

    curl_easy_cleanup(curl);

    fclose(hd_src);
  }

  return;
}

/**
 * Recupera o texto salvo em um arquivo. (Texto retornado na requisição HTTP GET)
 */
char* get_text(string filename) {
  FILE *hd_src;
  string path = "/tmp/" + filename + ".txt";
  int character;
  char characterAux[1000000];
  int i = 0;

  hd_src = fopen(path.c_str(), "r");

  while (1) {
    character = fgetc(hd_src);
    
    if (feof(hd_src)) { 
       break ;
    }
    
    characterAux[i++] = character;
  }

  fclose(hd_src);
  remove(path.c_str());

  return characterAux;
}

/**
 * Função de execução de uma Thread.
 */
void start_thread(int client_sockfd) {
  char vector_ch[4];
  char answer_ch[1000000];
  int urlID;
  string data;
  //printf("Client %d\n", client_sockfd);

  read(client_sockfd, vector_ch, sizeof(vector_ch));
  read(client_sockfd, &urlID, sizeof(urlID));

  string filename(vector_ch);

  get_data(filename, urlID);
  data = get_text(filename);
  strcpy(answer_ch, data.c_str());
  //printf("Text %s\n", answer_ch);
  write(client_sockfd, answer_ch, sizeof(answer_ch));
  //printf( "Caracter vindo do cliente = %c %c %c %c\n",vector_ch[0],vector_ch[1],vector_ch[2],vector_ch[3]);
  //printf( "Int vindo do cliente = %d\n",urlID);
  close(client_sockfd);
  
  //printf("Data result: ");
  //printf(data.c_str());
}

/**
 * Função de exemplo de execução.
 */
int main(void) {
  int server_sockfd, client_sockfd, urlID;
  size_t server_len;
  socklen_t client_len;
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;
  //string text1;
  //string text2;

  unlink("server_socket");  // remocao de socket antigo
  server_sockfd = socket(AF_INET, SOCK_STREAM, 0);  // cria um novo socket

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = 8081;

  server_len = sizeof(server_address);
  bind(server_sockfd, (struct sockaddr *) &server_address, server_len);
  listen(server_sockfd, 100);
   
  while (1) {
    //char vector_ch[4];
    //char answer_ch[1000000];

    printf("Servidor esperando ...\n");
    client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_address, &client_len);
    //printf("Client %d\n", client_sockfd);

    //read(client_sockfd, vector_ch, sizeof(vector_ch));
    //read(client_sockfd, &urlID, sizeof(urlID));

    //string name(vector_ch);
    thread(start_thread, client_sockfd).detach();
    
    //strcpy(answer_ch, text1.c_str());
    //write(client_sockfd, answer_ch, sizeof(answer_ch));
    //printf( "Caracter vindo do cliente = %c %c %c %c\n",vector_ch[0],vector_ch[1],vector_ch[2],vector_ch[3]);
    //printf( "Int vindo do cliente = %d\n",urlID);
    //close(client_sockfd);
  }

  /*thread threadA (start_thread, "test1", 7, ref(text1));
  thread threadB (start_thread, "test2", 8, ref(text2));
 
  threadA.join();
  threadB.join();

  printf("\n\nTexto da thread 1:\n%s\n", text1.c_str());

  printf("\n\nTexto da thread 2:\n%s\n", text2.c_str());*/

  return 0;
}
