#include <stdio.h>
#include <windows.h>
#include <conio.h>

char key[255],ch;
char note[255];
float freq[255];
char save[600];
int k;

float sound (char note) {
	for (int i=0;i<32;i++) {
		if (key[i]==note) return freq[i];
	}
}

void printpiano() {
	printf("\t\t\tWelcome to mini piano program\n");
	printf("\t\tThe notes will be similar to a melodica (pianica) notes\n");
	printf("\t ____________________________________________________________________________________________\n");
	printf("\t|  |  | |  | |  |  |   |  | |  |  |   |  | |  | |  |  |   |  | |  |  |   |  | |  | |  |  |   |\n");
	printf("\t|  |z | |x | |c |  |   |v | |b |  |   |n | |m | |, |  |   |. | |/ |  |   |' | |; | |l |  |   |\n");
	printf("\t|  |__| |__| |__|  |   |__| |__|  |   |__| |__| |__|  |   |__| |__|  |   |__| |__| |__|  |   |\n");
	printf("\t|   |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |   |\n");
	printf("\t| r | t  | y  | u  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | a  | s  | d  | f  | g  | h  | j |\n");
	printf("\t|___|____|____|____|____|____|____|____|____|____|____|____|____|____|____|____|____|____|___|\n");
}

void playpiano() {
	printf("Press \"-\" to stop\n");
	while (1) {
		char ch;
		if (kbhit()) {
			ch=getch();
			if (ch=='-') break;
			Beep(sound(ch),600);
		}
	}
}

void playsavepiano() {
	while (1) {
		if (kbhit()) {
			ch=getch();
			if (ch=='-') break;
			Beep(sound(ch),600);
			save[k]=ch;
			k++;
		}
	}
}

void playsongs (int n) {
	printf("Press any key to stop\n");
	char stop;
	for (int j=0;j<n;j++) {
		Beep(sound(note[j]),500);
		if (kbhit()) {
			stop=getch();
			break;
		}
	}
}

int main() {
	printpiano();
	int num_keys,i,n=0;
	char name[255];
	FILE *fp=fopen("digitalpiano.txt","r");
	for (i=0;i<32;i++) {
    	fscanf(fp,"%c %f\n",&key[i],&freq[i]);
	}
	fclose(fp);
	for (;;) {
		printf("\nWhat do you want to do?\n");
		printf("1. Play piano and save it to file\n");
		printf("2. Play piano only\n");
		printf("3. Play song snippets from our file\n");
		printf("4. Play song from your saved file\n");
		int choice;
		scanf("%d",&choice);
		getchar();
		if (choice==1) {
			char name[255];
			printf("Enter your song name (it will be your file name, and will automatically be saved in txt format): ");
			scanf("%[^\n]",&name);
			strcat(name,".txt");
			printf("Press \"-\" to stop\n");
			k=0;
			playsavepiano();
			FILE *saved=fopen(name,"w");
			for (i=0;i<k;i++) {
				fprintf(saved,"%c ",save[i]);
			}
			fclose(saved);
		}
		else if (choice==2) {
			playpiano();
		}
		else if (choice==3) {
			printf("\nWhich song snippets do you wanna hear?\n");
			printf("1. Memories\n");
			printf("2. Beautiful in White\n");
			printf("3. On My Way\n");
			printf("4. You Raise Me Up\n");
			printf("5. Shape of You\n");
			int choose;
			scanf("%d",&choose);
			n=0;
			if (choose==1) {
				FILE *song=fopen("memories.txt","r");
				while (!feof(song)) {
					fscanf(song,"%c",&note[n]);
					n++;
				}
				playsongs(n);
				fclose(song);
			}
			else if (choose==2) {
				FILE *song=fopen("beautifulinwhite.txt","r");
				while (!feof(song)) {
					fscanf(song,"%c",&note[n]);
					n++;
				}
				playsongs(n);
				fclose(song);
			}
			else if (choose==3) {
				FILE *song=fopen("onmyway.txt","r");
				while (!feof(song)) {
					fscanf(song,"%c",&note[n]);
					n++;
				}
				playsongs(n);
				fclose(song);
			}
			else if (choose==4) {
				FILE *song=fopen("youraisemeup.txt","r");
				while (!feof(song)) {
					fscanf(song,"%c",&note[n]);
					n++;
				}
				playsongs(n);
				fclose(song);
			}
			else {
				FILE *song=fopen("shapeofyou.txt","r");
				while (!feof(song)) {
					fscanf(song,"%c",&note[n]);
					n++;
				}
				playsongs(n);
				fclose(song);
			}
		}
		else if (choice==4) {
			n=0;
			char filename[255];
			printf("Enter your file name with the file format : ");
			scanf("%[^\n]",&filename);
			FILE *savedsong=fopen(filename,"r");
			while (!feof(savedsong)) {
				fscanf(savedsong,"%c",&note[n]);
				n++;
			}
			playsongs(n);
			fclose(savedsong);
		}
	}
	return 0;
}
