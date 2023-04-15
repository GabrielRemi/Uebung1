/***********************************************************************
 *
 * kompilieren  mit
 *
 *   gcc -Wall -pedantic skeleton.c -o skeleton -lm
 *
 *   Linker-Option "-lm", weil Mathematik-Bibliotheken verwendet werden
 *
 * aufrufen mit
 *   ./skeleton
 *
 ***********************************************************************/

#include <stdlib.h>  /* Definition vieler Grundfunktionen, u.a. auch die Speicherverwaltung */
#include <stdio.h>   /* Definition von Input-/Output-Funktionen */
#include <math.h>    /* elementare Funktionen, exp, sin, cos Wurzel etc.. */

#define NELEM 128  /* Präprozessor-Definition; NELEM wird im folgenden beim Kompilieren mit dem Wert 128 ersetzt,
                      NELEM ist die Länge der Arrays weiter unten */


/***********************************************************************
 * Beispiel-Funktion daxpy, die macht
 * y <- a * x + y, element-weise über N Elemente
 *
 * a und die pointer x, y, sowie die Anzahl der Elemente N werden nicht 
 * verändert, daher sind sie mit Schlüsselwort const deklariert
 *
 * Verändert wird nur der Inhalt des Speicherbereichs, auf den y zeigt
 ***********************************************************************/
void daxpy (double const a, double * const x, double * const y, unsigned int const N )
{
  for ( unsigned int i = 0; i < N; i++ )
  {
    y[i] = a * x[i] + y[i]; 
    /*
     * das ist das gleiche, wie
       y[i] += a * x[i];
     *
     */
  }

  return; /* kein weiterer Rückgabewert, da daxpy als void deklariert ist;
             return kann auch ganz weggelassen werden in diesem Fall */

}  /* end of daxpy */


/***********************************************************************
 * MAIN PROGRAM
 ***********************************************************************/
int main(int argc, char **argv) 
{

  unsigned int const n = NELEM; /* Präprozessor-Makro NELEM wird als 128 ersetzt */

  double * x = NULL, * y = NULL;  /* pointer-to-double, initialisiert als NULL-pointer */

  double a = 2.0;

  /* Speicher für y reservieren 
   *  expliziter Cast (double*) des von malloc zurückgelieferten Pointers vom Typ void* nach double* 
   *
   * Speichergröße = Anzahl der Elemente (=n) x Größe pro Element (=sizeof(double) )
   */
  y = (double*) malloc ( n * sizeof ( double ) );

  /* Prüfe, ob ungleich NULL, d.h. ob Fehler vorliegt */
  if ( y == NULL ) 
  {
    /* Fehlermeldung wird nach stderr geschrieben
     *
     * benutzen die Präprozessor-Makros __FILE__ und __LINE__, diese geben dann den vollen Dateinamen und die
     * aktuelle Zeilennummer aus, wenn die Fehlermeldung geschrieben wird; vereinfacht das Auffinden bei größeren
     * Projekten
     */
    fprintf ( stderr, "[skeleton] Fehler von malloc %s %d\n", __FILE__, __LINE__ );

    /* verlasse Programm mit Rückgabewert 1 and das Betriebssystem (OS);
     * auf OS-Ebene können wir dann den Fehler feststellen durch Prüfen des
     * Rückgabewertes */
    exit (1);
  }

  /* Speicher für x anlegen 
   *
   * etwas anders, als bei y, mit demselben Resultat
   * NELEM ist eine Konstante zur Kompilierzeit, mit ihr können wir also direkt ein
   * array deklarieren; double xarray[n] */
  double xarray[NELEM];

  /* Jetzt x auf die Startadresse von xarray setzen */
  x = xarray;

  /* das ist das gleiche wie 
   * x = &( array[0] );
   *  also x = Speicheradresse v on Array-Element array[0]
   */

  /* wir setzen Werte in y ein;
   * wir benutzen cos und sin, daher benötigen wir beim Linken -lm 
   */
  for ( unsigned int i = 0; i < n; i++ )
  {
    y[i] = cos ( 1. / ( i+1.) ); /* Achtung; auf der rechten Seite wird Variable i implizit von unsigned int nach double umgewandelt, dem Typ von y[i] */
  }

  /* wir setzen Werte in x ein; 
   *
   * hier machen wir etwas Gymnastik mit Speicheradress-Arithmetik;
   * das macht aber im Effekt das gleiche, wie bei y
   */
  for ( unsigned int i = 0; i < n; i++ )
  {
    /* x+i ist die Adresse von x[i] = xarray[i]; egal, welcher Pointer-Typ x ist, das Rechnung von 
     * x+1, x+2, ... ist immer richtig, die Schrittweite (wieviele Bytes zwischen x+0 und x+1 etc.)
     * macht der Kompiler selbst 
     */
    *(x + i ) = sin ( 1. / ( i+1.) );
    /* *ptr referenziert den Wert an der Speicheradresse, auf die Pointer ptr zeigt */
  }

  /***********************************************************************
   * wir rufen die Funktion auf
   ***********************************************************************/
  daxpy ( a, x, y, n );

  /***********************************************************************
   * wir geben in eine Datei aus
   ***********************************************************************/

  FILE *fp = NULL;

  fp = fopen ( "skeleton.tab", "w" ); /* öffne skeleton.tab für _w_rite ("w") */

  for ( unsigned int i = 0; i < n; i++ )
  {
    fprintf ( fp, "%6u %25.16e %25.16e\n", i, x[i], *(y+i) );
  }

  fclose ( fp );  /* Datei schliessen */

  /***********************************************************************
   * Aufräumen, d.h. den mit malloc reservierten Speicher freigeben
   ***********************************************************************/
  free ( y );  /* y müssen wir von Hand freigeben; y ist auf dem Heap angelegt und wird
                  nicht automatisch bereinigt, sondern wir entscheiden */

  /* Achtung; KEIN free(x); denn x war NICHT mit malloc reserviert worden; x ist auf dem Stack und
   * wird automatisch bereinigt  */


  return ( 0 );  /* Rückkehr zur Ebene, von der Das Programm aufgerufen wurde */
}

