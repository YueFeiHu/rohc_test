#ifndef _TESTAPP_H
#define _TESTAPP_H

// packageType
#define UDP 		1
#define LITE 		2
#define IP 		3
#define UNCOMP 		4

// debugType
#define NODEBUG		0
#define INPUT		1
#define COMP		2
#define DECOMP		4
#define FEEDBACK	8

/*
 * Linked list with information about orginal packet
 * and generated packets
 */
typedef struct generatedPackage{
	int size;
	int type;
	unsigned char * package;
	struct generatedPackage *nxt;
}packageList;




/* Fl�det i Main-funktionen
 * 1. Parse:a inparametrarna
 * 2. Skapa en paketstr�m beroende p� inparameter
 * 3. Skriv ev ut paketet om r�tt debugniv�
 * 4. Compressa ett paket
 * 5. Skriv ev ut comppaketet om r�tt debugniv�
 * 6. Decompressa paketet
 * 7. Skriv ev ut decomppaketet om r�tt debugniv�
 * 8. Compare package, print err if found
 *(9.) Hantera ev feedback och redirecta, print if debug
 * 10. GoTo 3:
 * 11. End
 */
 // int main(argc c, argv v[]);


/*
 * Skapar en serie paket av typen "packageType"
 * nr_Packages anger hur m�nga paket som skapas.
 * packageType avg�r vilken typ av paket som skapas (IP,UDP etc)
 *
 * Returnerar en pekare till paketstr�mmen
 */
packageList *generatePackage(int packageType, int nr_Packages);

/*
 * J�mf�r paket "orgPackage" med paket "finalPackage"
 * om paketen �r lika returneras true annars false
 */
int comparePackage(unsigned char *orgPackage, int orgSize, unsigned char *finalPackage, int finalSize);

/*
 * Anropas fr�n dekompressorn och skriver ut ev debuginfo
 * och skickar datan till kompressorn. Detta �r n�r feedback
 * kommer in till dekomp som denna anropas
 *
 */
void feedbackRedir(unsigned char *ibuf, int feedbacksize);

/*
 * Anropas av dekompressorn n�r feedback ska piggybackas p�
 * kompressorn, detta f�r att se vad som piggybackas
 * Anropas n�r feedback ska skickas
 */
void feedbackRedir_piggy(unsigned char *ibuf, int feedbacksize);


/*
 * Skriver ut ett pakets inneh�ll beroende p� vilken
 * debugniv� som programmet exekveras i.
 * debugLevel �r den debugniv� som programmet k�rs i.
 * packageToPrint �r det paket som ska skrivas ut.
 *
 */
void printDebugMsg(int debugLevel, unsigned char *packageToPrint, int debugType, int size);

/*
 * Kommer nog inte att anv�ndas...
 *
 *
 */
int writeToFile(int file, unsigned char *packageToWrite);

/* (M) Sequance test
 */
void sequence_test(char * filename, int rohc_mode);

/* (M) Sequence test of compressor and decompressor
 */

void sequence_test_comp_and_decomp(char * filename);
/* (M) Sequence test for the decompressor
 */
void sequence_test_decompressor_only(char * filename);

/* (M) Read a serie of files
 */
packageList * read_sequence(char * filename_begin, char * filename_end);

/* (M) Allocate memory and read a file. write the size in "size".
 */
unsigned char * read_file(char * filename, int * size);

/* (M) Count packages in a packageList
 */
int package_list_size(packageList *);

/* (M) Duplicate memory
 */
void * memdup(void *, int size);

#endif
