#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#define MAX 20
typedef struct ders{
	char *kod;
	char *ad;
	int kontenjan,alan;
	int kredi;
	int* ogrenci;
	int ogrencisayisi;
	struct ders* next;
}DERS;
typedef struct ogrenci_listesi{
	int num,ders_sayisi,kredi,kalan;
	char *ad,*soy;
	struct ogrenci_listesi* next;
	struct ogrenci_listesi* prev;
	
}OGRENCI;
typedef struct{
	int ID;
	int ogrNo;
	char dersNo[20];
	char tarih[20];
	char drum[20];
}DURUM;
//structlar^

void ders_ekle(DERS **,DERS *);
void ders_yaz(DERS *);
void ders_dosyayaKaydet(DERS *head,OGRENCI *Ohead);
void ders_ozelkaydet(DERS *drs,OGRENCI *head);
void dersOkuYaz(DERS **);
void yeni_ders_ekle(DERS **head);
void ders_sil(DERS **,DURUM *,int);
void yeni_ogrenci_ekle(OGRENCI **head);
void ogrenciderskayit(DURUM *,int );
void ogrenci_dosyayaKaydet(OGRENCI *head);
void ogrenci_sil(OGRENCI **,DURUM *,int);
void ogrenciOkuYaz(OGRENCI **head);
void ogrenci_ekle(OGRENCI **,OGRENCI *);
void ogrenci_yaz(OGRENCI *);
void yeni_derseOgrenciekle(DERS *,OGRENCI *,DURUM *,int *);
void dosyadanderseOgrenciekle(DERS *,OGRENCI *,DURUM *,int *);
void derseOgrenciekle(DERS *,OGRENCI *,DURUM *,int *);
void dersOgrencisil(DERS *,DURUM* ,int *);
void ogrenci_ozelkaydet(DERS *,OGRENCI *,DURUM *,int );
void ders_ozelyaz(DERS *,OGRENCI *,DURUM *,int );
DERS *dersolustur();
OGRENCI *ogrenciolustur();
DERS *dersbul(DERS *head,char *drsnum);
OGRENCI *ogrencibul(OGRENCI *head,int ogrnum);

int main(){
	DERS *Dhead=NULL;
	OGRENCI *Ohead=NULL;
	DURUM *durumlar;
	durumlar=(DURUM*)malloc(20*sizeof(DURUM));
	int nd=0,i=1,j=0,mn,mn2,num;
	dersOkuYaz(&Dhead);
	ogrenciOkuYaz(&Ohead);
	dosyadanderseOgrenciekle(Dhead,Ohead,durumlar,&nd);	
	while(mn!=0){
	printf("\nMENU\n");
	printf("1-Ders islemleri icin:");
	printf("\n2-Ogrenci ekleme silme islmeleri icin:");
	printf("\n3-Ogrenci islemleri icin:");
	printf("\n4-Ogrenci veya mevcut dersleri gormek icin:");
	printf("\n0-cikis icin\n");
	scanf("%d",&mn);
		if(mn==1){
			printf("1-ders eklemek icin :");
			printf("\n2-ders silmek icin :");
			printf("\n3-ders yazdýrmak icin :\n");
			scanf("%d",&mn2);
			if(mn2==1){
				yeni_ders_ekle(&Dhead);
			}
			else if(mn2==2){
				ders_sil(&Dhead,durumlar,nd);
			}
			else if(mn2==3){
				ders_ozelyaz(Dhead,Ohead,durumlar,nd);
			}
			else{
				printf("\nHatali giris!!\nMenuye yonlendiriliyorsunuz...\n");
			}	
		}
		else if(mn==2){
			printf("1-Ogrenci eklemek icin :");
			printf("\n2-Ogrenci silmek icin :\n");
			scanf("%d",&mn2);
			if(mn2==1){
				yeni_ogrenci_ekle(&Ohead);
			}
			else if(mn2==2){
				ogrenci_sil(&Ohead,durumlar,nd);
			}
			else{
				printf("\nHatali giris!!\nMenuye yonlendiriliyorsunuz...\n");
			}		
		}
		else if(mn==3){
			printf("1-Derse ogrenci eklemek icin :");
			printf("\n2-Derse ogrenci silmek icin :");
			printf("\n3-Ogrenci icin ders programi gostermek icin :\n");
			scanf("%d",&mn2);
			if(mn2==1){
				yeni_derseOgrenciekle(Dhead,Ohead,durumlar,&nd);
			}
			else if(mn2==2){
				dersOgrencisil(Dhead,durumlar,&nd);
			}
			else if(mn2==3){
				ogrenci_ozelkaydet(Dhead,Ohead,durumlar,nd);
			}
			else{
				printf("\nHatali giris!!\nMenuye yonlendiriliyorsunuz...\n");
			}
			
			ogrenciderskayit(durumlar,nd);
		}
		else if(mn==4){
			printf("1-Dersleri gormek icin:\n");
			printf("2-Ogrencileri gormek icin:\n");
			scanf("%d",&mn2);
			if(mn2==1){
				ders_yaz(Dhead);
			}
			if(mn2==2){
				ogrenci_yaz(Ohead);
			}
		}
		else if(mn!=0){
			printf("\nHatali giris!!!!\nTekrar giriniz...\n");
		}
		ders_dosyayaKaydet(Dhead,Ohead);	
		ogrenci_dosyayaKaydet(Ohead);
		ogrenciderskayit(durumlar,nd);
	}
	
}
DERS *dersolustur(){
	DERS *tmp;
	tmp=(DERS*)malloc(sizeof(DERS));
	tmp->ad=(char*)malloc(20*sizeof(char));
	tmp->kod=(char*)malloc(20*sizeof(char));
	tmp->ogrenci=(int*)malloc(sizeof(int));
	tmp->alan=0;
	tmp->ogrencisayisi=0;
	tmp->next=NULL;
}

OGRENCI *ogrenciolustur(){
	OGRENCI *tmp;
	tmp=(OGRENCI*)malloc(sizeof(OGRENCI));
	tmp->ad=(char*)malloc(20*sizeof(char));
	tmp->soy=(char*)malloc(20*sizeof(char));
	tmp->ders_sayisi=0;
	tmp->next=NULL;
	tmp->prev=NULL;
}

void ders_ekle(DERS **head,DERS *yeni){
	DERS *tmp,*hl;
	int i;
	if(*head==NULL){
		*head=yeni;	
	}
	else{
		tmp=*head;
		if(strcmp((yeni->kod),(tmp->kod))==0){
			printf("HATA!Ayni degere sahip ders bulunmakta.\n");
			free(yeni);
			return;
		}
		if(strcmp((yeni->kod),(tmp->kod))==-1){
			hl=*head;
			*head=yeni;
			yeni->next=hl; 
		}
		else{
			while(tmp->next != NULL && strcmp((yeni->kod),(tmp->next->kod))==1){
				tmp=tmp->next;
			}
			if(tmp->next != NULL){
				if(strcmp((yeni->kod),(tmp->next->kod))==0){
					printf("HATA!Ayni degere sahip ders bulunmakta.\n");
					free(yeni);
					return;
				}
				hl=tmp->next;
				tmp->next=yeni;
				yeni->next=hl;
			}
			else{
				tmp->next=yeni;
			}
		}
	}

}
void yeni_ders_ekle(DERS **head){
	DERS *yeni=dersolustur();
	printf("\nders kodu:");
	fflush(stdin);
	gets(yeni->kod);
	printf("ders adi:");
	fflush(stdin);
	gets(yeni->ad);
	printf("kontenjan:");
	scanf("%d",&yeni->kontenjan);
	printf("kredi:");
	scanf("%d",&yeni->kredi);
	ders_ekle(head,yeni);

}

void ders_yaz(DERS *head){
	int i;
	DERS *tmp=head;
	while(tmp!=NULL){
		printf("%s ",tmp->kod);
		printf("%s ",tmp->ad);
		printf("%d ",tmp->kontenjan);
		printf("%d\n",tmp->kredi);
		tmp=tmp->next;
	}
}
void ders_dosyayaKaydet(DERS *head,OGRENCI *Ohead){
	DERS *tmp=head;
	int i;
	FILE *fp;
	fp = fopen("dersler.txt","w");
	while(tmp!=NULL){
		ders_ozelkaydet(tmp,Ohead);
		fprintf(fp,"%s %s %d %d\n",tmp->kod,tmp->ad,tmp->kontenjan,tmp->kredi);
		tmp=tmp->next;
	}
	fclose(fp);
}
void ders_ozelkaydet(DERS *drs,OGRENCI *head){
	OGRENCI *ogr;
	FILE *fo;
	char txtname[]=".txt";
	char nm[20];
	int i;
	strcpy(nm,drs->kod);
	strcat(nm,txtname);
	fo = fopen(nm,"w");
	for(i=0;i< drs->alan;i++){
		ogr=ogrencibul(head,drs->ogrenci[i]);
		fprintf(fo,"%d %s %s %d\n",ogr->num,ogr->ad,ogr->soy,ogr->kredi);
	}
	fclose(fo);
}
void ogrenci_ozelkaydet(DERS *Dhead,OGRENCI *Ohead,DURUM *durumlar,int nd){	
	FILE *fn;
	OGRENCI *ogr;
	DERS *drs;
	char txtname[]="_DERSPROGRAMI.txt";
	char nm[20];
	int i,Ogrnum;
	printf("\nOgrenci numarasi girin:");
	scanf("%d",&Ogrnum);
	ogr = ogrencibul(Ohead,Ogrnum);
	itoa(Ogrnum,nm,10);
	strcat(nm,txtname);
	printf("\n%d numarali ogrencinin ders listesi:\n",Ogrnum);
	fn = fopen(nm,"w");
	for(i=0;i<nd;i++){
		if(durumlar[i].ogrNo==Ogrnum){
			drs = dersbul(Dhead,durumlar[i].dersNo); 
			fprintf(fn,"%s %s %d %d\n",drs->kod,drs->ad,drs->kontenjan,drs->kredi);
			printf("%s %s %d %d\n",drs->kod,drs->ad,drs->kontenjan,drs->kredi);
		}
		
	}
	fclose(fn);
}
void ders_ozelyaz(DERS *Dhead,OGRENCI *Ohead,DURUM *durumlar,int nd){	
	OGRENCI *ogr;
	DERS *drs;
	int i;
	char dersnum[20];
	printf("\nDers kodunu girin:");
	scanf("%s",dersnum);
	drs = dersbul(Dhead,dersnum);
	printf("%s kodlu dersin listesi:\n",dersnum);
	for(i=0;i<nd;i++){
		if(strcmp(durumlar[i].dersNo,dersnum)==0){
			ogr = ogrencibul(Ohead,durumlar[i].ogrNo); 
			printf("%d %s %s %d\n",ogr->num,ogr->ad,ogr->soy,ogr->kredi);
		}
		
	}
}
void ogrenci_dosyayaKaydet(OGRENCI *head){
	OGRENCI *tmp=head;
	int i;
	FILE *fp;
	fp = fopen("ogrenciler.txt","w");
	while(tmp!=NULL){
		fprintf(fp,"%d %s %s %d\n",tmp->num,tmp->ad,tmp->soy,tmp->kredi);
		tmp=tmp->next;
	}
	fclose(fp);
}
void ogrenciderskayit(DURUM *durumlar,int nd){
	int i;
	FILE *fp;
	fp = fopen("ÖðrenciDersKayýt.txt","w");
	for(i=0;i<nd;i++){
		fprintf(fp,"%d %d %s %s %s\n",durumlar[i].ID,durumlar[i].ogrNo,durumlar[i].dersNo,durumlar[i].drum,durumlar[i].tarih);
	}
	fclose(fp);
}


void ogrenci_ekle(OGRENCI **head,OGRENCI *yeni){
	OGRENCI *tmp,*hl;
	int i;
	if(*head==NULL){
		*head=yeni;	
	}
	else{
		tmp=*head;
		if((yeni->num)==(tmp->num)){
			printf("HATA!Ayni degere sahip ogrencý bulunmakta.\n");
			free(yeni);
			return;
		}
		if((yeni->num)<(tmp->num)){
			hl=*head;
			*head=yeni;
			yeni->next=hl;
			hl->prev=yeni;
		}
		else{
			while(tmp->next != NULL && (yeni->num)>(tmp->next->num)){
				tmp=tmp->next;
			}
			if(tmp->next != NULL){
				if((yeni->num)==(tmp->next->num)){
					printf("HATA!Ayni degere sahip ogrencý bulunmakta.\n");
					free(yeni);
					return;
				}
				hl=tmp->next;
				tmp->next=yeni;
				yeni->next=hl;
				hl->prev=yeni;
			}
			else{
				tmp->next=yeni;
				yeni->prev=tmp;
			}	
		}
	}

}
void yeni_ogrenci_ekle(OGRENCI **head){
	OGRENCI *yeni=ogrenciolustur();
	printf("ogrenci adi:");
	fflush(stdin);
	gets(yeni->ad);
	printf("ogrenci soyadi:");
	fflush(stdin);
	gets(yeni->soy);
	printf("ogrenci numarasi:");
	scanf("%d",&yeni->num);
	printf("ogrenci kredisi:");
	scanf("%d",&yeni->kredi);
	yeni->kalan=yeni->kredi;
	ogrenci_ekle(head,yeni);
}

void ogrenci_yaz(OGRENCI *head){
	int i;
	OGRENCI *tmp=head;
	while(tmp!=NULL){
		printf("%s ",tmp->ad);
		printf("%s ",tmp->soy);
		printf("%d ",tmp->num);
		printf("%d\n",tmp->kredi);
		tmp=tmp->next;
	}
}
void dersOkuYaz(DERS **head){
	DERS *yeni=dersolustur();
	char file_name[20];
	FILE *fp;
	fp = fopen("dersler.txt", "r");
	if(fp==NULL){
		printf("Dosya yok");
	}
	while(fscanf(fp,"%s %s %d %d",yeni->kod,yeni->ad,&yeni->kontenjan,&yeni->kredi)!=EOF){
		yeni->ogrencisayisi=0;
		yeni->alan=0;
		ders_ekle(head,yeni);
		yeni=dersolustur();
	}
	free(yeni);	
}
void ogrenciOkuYaz(OGRENCI **head){
	OGRENCI *yeni=ogrenciolustur();
	char file_name[20];
	FILE *fp;
	fp = fopen("ogrenciler.txt", "r");
	if(fp==NULL){
		printf("Dosya yok");
		return;
	}
	while(fscanf(fp,"%d %s %s %d",&yeni->num,yeni->ad,yeni->soy,&yeni->kredi)!=EOF){
		yeni->kalan=yeni->kredi;
		ogrenci_ekle(head,yeni);
		yeni=ogrenciolustur();
	}
	free(yeni);	
}
void ders_sil(DERS **head,DURUM *durumlar,int n){
	DERS *tmp=*head,*hl;
	char hedef[20];
	int i;
	printf("silmek istediginiz dersin kodunu giriniz: ");
	scanf("%s",hedef);
	if(strcmp(hedef,(tmp->kod))==0){
		*head=tmp->next;
		free(tmp);
	}
	else{
		while(tmp->next != NULL && strcmp(hedef,(tmp->next->kod))!=0){
			tmp=tmp->next;
		}
		if(tmp->next != NULL){
			hl=tmp->next->next;
			free(tmp->next);
			tmp->next=hl;
		}
		else{
			printf("SILINECEK DEGER BULUNAMADI!!");
			return;
		}
	}
	for(i=0;i<n;i++){
		if(strcmp(durumlar[i].dersNo,hedef)==0){
			strcpy(durumlar[i].drum,"SILINDI");
		}
	}
}
void ogrenci_sil(OGRENCI **head,DURUM *durumlar,int n){
	OGRENCI *tmp=*head,*hl;
	int hedef;
	int i;
	printf("silmek istediginiz ogrencinin numarasini giriniz: ");
	scanf("%d",&hedef);
	if(hedef==tmp->num){
		*head=tmp->next;
		free(tmp);
	}
	else{
		while(tmp->next != NULL && hedef!=tmp->next->num){
			tmp=tmp->next;
		}
		if(tmp->next != NULL){
			hl=tmp->next->next;
			free(tmp->next);
			tmp->next=hl;
		}
		else{
			printf("SILINECEK DEGER BULUNAMADI!!");
			return;
		}
	}
	for(i=0;i<n;i++){
		if(durumlar[i].ogrNo==hedef){
			strcpy(durumlar[i].drum,"SILINDI");
		}
	}
}
void yeni_derseOgrenciekle(DERS *Dhead,OGRENCI *Ohead,DURUM *durumlar,int *nd){
	OGRENCI *ogr;
	DERS *drs;
	char dersnum[20];
	int ogrnum;
	printf("ogrenci numarasi:");
	scanf("%d",&ogrnum);
	ogr=ogrencibul(Ohead,ogrnum);
	printf("ogrenci hangi derse eklenecek:");
	scanf("%s",dersnum);
	drs = dersbul(Dhead,dersnum);
	if(ogr==0 ||drs==0){
		printf("Islem HATALI!!\n");
		return;
	}
	derseOgrenciekle(drs,ogr,durumlar,nd);
}
void dosyadanderseOgrenciekle(DERS *Dhead,OGRENCI *Ohead,DURUM *durumlar,int *nd){
	OGRENCI *ogr;
	DERS *drs;
	char file_name[20];
	char kod[20],durum[20],tarih[20];
	int num,id;
	FILE *fp;
	fp = fopen("ÖðrenciDersKayýt.txt", "r");
	if(fp==NULL){
		printf("Dosya yok");
		return;
	}
	while(fscanf(fp,"%d %d %s %s %s",&id,&num,kod,durum,tarih)!=EOF){
		if(strcmp(durum,"KAYIT_OLDU")==0){
			drs = dersbul(Dhead,kod);
			ogr=ogrencibul(Ohead,num);
			if(drs==0||ogr==0){
				printf("\nDosyadan okumada hata olustu!!!!\n");
				return;
			}
			derseOgrenciekle(drs,ogr,durumlar,nd);
		}
	}
	fclose(fp);
}
void derseOgrenciekle(DERS *drs,OGRENCI *ogr,DURUM *durumlar,int *nd){
	char gun[20], ay[20], yil[20];
    time_t t = time(NULL);
    struct tm *ptm = localtime(&t);
	int i,j,k,tmp,min,*dizi,n,dn=*nd;
	char dersnum[20];
	strcpy(dersnum,drs->kod);
	int ogrnum=ogr->num;
	ogr->kalan-=drs->kredi;
	n=drs->alan;
	drs->alan++;
	if(ogr->kalan<0 || drs->alan > drs->kontenjan || ogr->ders_sayisi>MAX){
		if(ogr->kalan<0){
			printf("\nogrenci bu dersi alamaz. Kredi yetersiz!!");	
		}
		else if(drs->alan > drs->kontenjan){
			printf("\nkontenjan dolu!!");
		}
		else{
			printf("\nmaximum ders sayisi asildi!!\n");
		}
		ogr->kalan+=drs->kredi;
		drs->alan--;
		return;
	}
	drs->ogrenci[n]=ogrnum;
	dizi=drs->ogrenci;
	ogr->ders_sayisi++;
	for(i=0;i<n;i++){	
		min=dizi[i];
		for(j=i+1;j<=n;j++){
			if(dizi[j]<min){
				min=dizi[j];
				k=j;
			}
		}
		tmp=dizi[i];
		dizi[i]=dizi[k];
		dizi[k]=tmp;
	}
	durumlar[dn].ID=dn;
	durumlar[dn].ogrNo=ogrnum;
	strcpy(durumlar[dn].dersNo,dersnum);
	strcpy(durumlar[dn].drum,"KAYIT_OLDU\0");
	
    itoa(ptm->tm_mday,gun,10);
	itoa(ptm->tm_mon + 1,ay,10);           
    itoa(ptm->tm_year + 1900,yil,10);     
    
    
    strcat(gun,".\0");
    strcat(gun,ay);
    strcat(gun,".\0");
    strcat(gun,yil);
    strcpy(durumlar[dn].tarih,gun);
	(*nd)+=1;
	return;
}
void dersOgrencisil(DERS *head,DURUM* durumlar,int *nd){
	DERS *drs;
	int i,j,num;
	char kod[20];
	printf("Ogrenci numarasini girin : ");
	scanf("%d",&num);
	printf("Ders kodunu girin : ");
	scanf("%s",kod);
	for(i=0;i<*nd;i++){
		if(durumlar[i].ogrNo==num && strcmp(durumlar[i].dersNo,kod)==0){
			strcpy(durumlar[i].drum,"SILINDI");
		}
	}
	drs= dersbul(head,kod);
	i=0;
	while(i<drs->alan && drs->ogrenci[i]!=num){
		i++;
	}
	drs->ogrenci[i]=0;
	if(i<drs->alan){
		for(j=i;j<drs->alan-1;i++){
			drs->ogrenci[j]=drs->ogrenci[j+1];
		}
		(drs->alan)--;
	}
	else{
		printf("Silinecek deger bulunamadi!!\n");
	}
}
DERS *dersbul(DERS *head,char *drsnum){
	DERS *tmp=head;
	while(tmp!=NULL && strcmp(tmp->kod,drsnum)!=0){
		tmp=tmp->next;
	}
	if(tmp!=NULL){
		return tmp;
	}
	else{
		printf("\nHATA!! DERS BULUNAMADI!!\n");
		return 0;
	}
}
OGRENCI *ogrencibul(OGRENCI *head,int ogrnum){
	OGRENCI *tmp=head;
	while(tmp!=NULL && tmp->num!=ogrnum){
		tmp=tmp->next;
	}
	if(tmp!=NULL){
		return tmp;
	}
	else{
		printf("\nHATA!! OGRENCI BULUNAMADI!!\n");
		return 0;
	}
}
