#include <stdio.h>//for printf, etc
#include <unistd.h>//for fork
#include <stdlib.h>
#include <string.h>//for strlen
#include <sys/types.h>//waitpid fonksiyonu
#include <sys/wait.h>//waitpid fonksiyonu

int main()
{
	char komut[80];
	char* komutlar[10];
	char yol[100000];
	int pidler[5];
	int sayac = 0;
	getcwd(yol, sizeof(yol));//dosya yolunu dondurur
	while(1){
		printf("\x1b[31m" "sau:" "\x1b[0m" "\x1b[32m" "%s > " "\x1b[0m", yol);//prompt kısmı
		fgets(komut, sizeof(komut), stdin);//girilen string ifadeyi cekme
		komut[strlen(komut) - 1] = '\0';//string ifadenin sonundaki bosluk karakterini silme
		komutlar[0]=strtok(komut," ");
		for(int i = 1; i < 10; i++){
			komutlar[i]=strtok(NULL," ");
		}
		if(strcmp(komutlar[0],"exit") == 0){ //terminali kapatma
			printf("exit\n");
			exit(0);
		}
		else if(strcmp(komutlar[0],"cd") == 0){ //dosyalar arasinda gezinme
			chdir(komutlar[1]);
			getcwd(yol, sizeof(yol));
		}
		else if(strcmp(komutlar[0],"showpid")==0){ //son 5 pid'i ekrana yazdirma
			for(int i=0;i<5;i++){
				printf("%d\n",pidler[i]);
			}
		}
		else{ //dosya calistirma
			int pid = fork();
			if(pid==0){
				execvp(komutlar[0],komutlar);
				fprintf(stderr, "Hata.\n");
				return 1;
			}
			else if(pid<0){
				fprintf(stderr, "Hata.\n");
				return 1;
			}
			else{
				waitpid(pid,NULL,0);
			}
			pidler[sayac] = pid;
			sayac++;
			if(sayac>=6){
				sayac=0;
			}
		}
	}
}
