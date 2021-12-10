#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

char komut[80];
char* komutlar[10];
char yol[100000];
int pidler[5];
int sayac = 0;

void prompt(){//prompt yazar
	printf("\x1b[31m" "%s: " "\x1b[0m" "\x1b[32m" "sau > " "\x1b[0m", yol);
};

void kullanici_girisi(){//kullanicinin girdigi string ifadelerle ilgilenir
	fgets(komut, sizeof(komut), stdin);//girilen string ifadeyi cekme
	komut[strlen(komut) - 1] = '\0';//string ifadenin sonundaki bosluk karakterini silme
	komutlar[0]=strtok(komut," ");
	for(int i = 1; i < 10; i++){
		komutlar[i]=strtok(NULL," ");
	}
};

void sonlandir(){//kabugu sonlandirir
	printf("exit\n");
	exit(0);
};

void gezinme(){//klasorler arasinda gezinme saglar
	chdir(komutlar[1]);
	getcwd(yol, sizeof(yol));
};

void pidleri_yazdir(){//en son olusan 5 pid'i ekrana yazdirir
	for(int i=0;i<5;i++){
		printf("%d\n",pidler[i]);
	}
};

int main()
{
	getcwd(yol, sizeof(yol));//dosya yolunu dondurur
	while(1){
		prompt();
		kullanici_girisi();
		if(strcmp(komutlar[0],"exit") == 0){
			sonlandir();
		}
		else if(strcmp(komutlar[0],"cd") == 0){
			gezinme();
		}
		else if(strcmp(komutlar[0],"showpid")==0){
			pidleri_yazdir();
		}
		else{
			int pid = fork();
			if(pid==0){
				execvp(komutlar[0],komutlar);
				fprintf(stderr, "Hata: Komut icra edilemiyor.\n");
				return 1;
			}
			else if(pid<0){
				fprintf(stderr, "Hata: Komut icra edilemiyor.\n");
				return 1;
			}
			else{
				waitpid(pid,NULL,0);
			}
			pidler[sayac] = pid;
			sayac++;
			if(sayac>=5){ //son 5 process id'si yazilacagi icin 5'ten sonra sayaci sifirla.
				sayac=0;
			}
		}
	}
}
