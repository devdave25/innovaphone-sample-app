/*---------------------------------------------------------------------------*/
/* time.h                                                                    */
/* copyright (c) innovaphone 2016                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#define EPOCH_YEAR		1970
#define MAX_TRANSITS	(2 * (2037 - EPOCH_YEAR + 1))

typedef struct _timezone_info_t {
    struct {
        dword   utc;
        long    off;
    }   transits[MAX_TRANSITS];
    int numTransits;
    long tzStdOff;
    long tzDstOff;

    // Default-CTOR to initialize all fields (important, because the c-lib function depending on initialized
    // fields - greetings from Valgrind)
    _timezone_info_t()
    {
        memset(this, 0, sizeof(_timezone_info_t));
    }
} timezone_info_t;

typedef struct _time_tm_t {
    int tmSec;			/* Seconds.	[0-60] (1 leap second) */
    int tmMin;			/* Minutes.	[0-59] */
    int tmHour;		    /* Hours.	[0-23] */
    int tmMDay;		    /* Day.		[1-31] */
    int tmMon;			/* Month.	[0-11] */
    int tmYear;		    /* Year	- 1900.  */
    int tmWDay;		    /* Day of week.	[0-6] */
    int tmYDay;		    /* Days in year.[0-365]	*/
    int tmIsDst;		/* DST.		[-1/0/1] */

    // Default-CTOR to initialize all fields (important, because the c-lib function depending on initialized
    // fields - greetings from Valgrind)
    _time_tm_t()
    {
        memset(this, 0, sizeof(_time_tm_t));
    }
} time_tm_t;

class ITime {
public:
    static bool ParseTimeZoneString(const char * tz, timezone_info_t & tiOut, int * errPos = NULL);

    static long64 TimeStampMilliseconds();
    static long64 TimeStampMilliseconds(timezone_info_t & ti);
    static long64 UTCTimeToLocalTime(long64 timeMsUtc, timezone_info_t & ti);

    static long64 GetMonotonicTime();
    static size_t GetTimeStamp(char * buf, unsigned sz);
    static void GetTimeStruct(long64 timeMs, time_tm_t * t);
    static void GetTimeStruct(long64 timeMs, time_tm_t * t, timezone_info_t & ti);

    static long64 TimeStructToMilliseconds(time_tm_t * ts);
    static bool NormalizeTimeStruct(time_tm_t * ts);

    static size_t FormatTimeStampISO(char * buf, unsigned length, long64 timeMs);
    static size_t FormatTimeStampRFC1123(char * buf, unsigned length, long64 timeMs);
    static size_t FormatTimeStamp(char * buf, unsigned length, const char * formatStr, long64 timeMs);
    static size_t FormatTimeStamp(char * buf, unsigned length, const char * formatStr, long64 timeMs, timezone_info_t & ti);

    static long64 RemoveTime(long64 timeStamp) {
        return (timeStamp / 86400000 * 86400000);
    }

    static bool IsLeapYear(int year) {
        return (year % 4) == 0 && (year % 100 != 0 || year % 400 == 0);
    }

    static int GetDaysOfMonth(int month, int forYear) {
        // Make sure that month is not out of range...
        while (month > 11) {
            month -= 12;
            ++forYear;
        }
        int monthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        return month == 1 && IsLeapYear(forYear) ? 29 : monthDays[month];
    }
};
