#define INCL_NOPMAPI
#define INCL_DOS
#include <os2.h>
#include <string.h>



/* the real Dos32Open() has been renamed (by the *.def file) to
 * _Dos32Open():
 */
APIRET APIENTRY  _DOS32OPEN(PSZ    pszFileName,
                         PHFILE pHf,
                         PULONG pulAction,
                         ULONG  cbFile,
                         ULONG  ulAttribute,
                         ULONG  fsOpenFlags,
                         ULONG  fsOpenMode,
                         PEAOP2 peaop2);



/* write a string to stderr (file handle #2) */
static void msg(char *s)
{
    ULONG bw;
    DosWrite(2, s, strlen(s), &bw);
}




/* Our replacement Dos32Open() function.
 * Look for,  and turn off, OPEN_FLAGS_WRITE_THROUGH
 * and OPEN_FLAGS_NO_CACHE.  The latter was never seen being
 * used by pmmerge, but what the heck...
 */
APIRET APIENTRY _Export DOS32OPEN(PSZ    pszFileName,
                         PHFILE pHf,
                         PULONG pulAction,
                         ULONG  cbFile,
                         ULONG  ulAttribute,
                         ULONG  fsOpenFlags,
                         ULONG  fsOpenMode,
                         PEAOP2 peaop2)
{
    if( fsOpenMode & OPEN_FLAGS_WRITE_THROUGH ){
        fsOpenMode &= ~OPEN_FLAGS_WRITE_THROUGH;
        msg("OPEN_FLAGS_WRITE_THROUGH off for '");
        msg(pszFileName);
        msg("'\r\n");
    }
    if( fsOpenMode & OPEN_FLAGS_NO_CACHE){
        fsOpenMode &= ~OPEN_FLAGS_NO_CACHE;
        msg("OPEN_FLAGS_NO_CACHE off for'");
        msg(pszFileName);
        msg("'\r\n");
    }
    return _DOS32OPEN(pszFileName,
                    pHf,
                    pulAction,
                    cbFile,
                    ulAttribute,
                    fsOpenFlags,
                    fsOpenMode,
                    peaop2);
}

