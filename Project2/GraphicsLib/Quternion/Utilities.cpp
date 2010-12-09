//-----------------------------------------------------------------------
//  Best viewed with tabs every 4 columns
//-----------------------------------------------------------------------
//  File:           utilities.cpp
//  Description:    Some utility math functions
//  Programmer:     Dave Mount
//  For:            CMSC 427 - Fall 2010
//-----------------------------------------------------------------------

#include "Utilities.h"
#include "Vector3d.h"					// for geometric constants

using namespace std;					// make std:: accessible

// ---------------------------------------------------------------  
// Clamps val to between min and max
// ---------------------------------------------------------------

double clamp(double val, double min, double max)
{
	if(max < GEOM_INF && val > max) val = max;
	else if(val < min) val = min;
	return val;
}

//----------------------------------------------------------------------
//  checkGLerror - OpenGL error handler
//----------------------------------------------------------------------

void checkGLerror(const string& checkPoint)
{
    GLenum errCode = glGetError();
	if (errCode == GL_NO_ERROR)  return;

    cerr << "OpenGL error detected: At checkpoint " << checkPoint << endl;
    while (errCode != GL_NO_ERROR) {
        cerr << "    ";
        switch (errCode) {
            case GL_INVALID_ENUM:
                cerr << "Invalid enumerated type as argument." << endl;
                break;
            case GL_INVALID_VALUE:
                cerr << "Argument out of range." << endl;
                break;
            case GL_INVALID_OPERATION:
                cerr << "Invalid operation for current state." << endl;
                break;
            case GL_STACK_OVERFLOW:
                cerr << "Stack overflow." << endl;
                break;
            case GL_STACK_UNDERFLOW:
                cerr << "Stack unverflow." << endl;
                break;
            case GL_OUT_OF_MEMORY:
                cerr << "Out of memory." << endl;
                break;
            default:
                cerr << "Unknown error code: " << errCode << endl;
                break;
        }
        errCode = glGetError();
    }
    cerr.flush();                       // make sure that output appears
}

//----------------------------------------------------------------------
//  error - called if an error occurs
//----------------------------------------------------------------------

void error(const string& msg, bool fatal)
{
    if (fatal) {
        cerr << "Error: " << msg << endl;
        exit(1);
    }
    else  cerr << "Warning: " << msg << endl;
}

//----------------------------------------------------------------------
//  version control
//----------------------------------------------------------------------

int version;

int getVersion() { return version; }

void setVersion(int v) { version = v; }

//----------------------------------------------------------------------
//  get millisecond time counts
//----------------------------------------------------------------------

int getMilliCount()
{
	// Something like GetTickCount but portable
	// It rolls over every ~ 12.1 days (0x100000/24/60/60)
	// Use GetMilliSpan to correct for rollover
	timeb tb;
	ftime( &tb );
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}

int getMilliSpan(int nTimeStart)
{
	int nSpan = getMilliCount() - nTimeStart;
	if ( nSpan < 0 )
		nSpan += 0x100000 * 1000;
	return nSpan;
}

//-----------------------------------------------------------------------
//	Get elapsed time
//
//	Due to possibly low clock resolution, we average many time steps to
//	obtain an estimate of the number of seconds per idle events. We
//	maintain a vector of 100 recent calls. The first 100 calls fill this
//	array. Once filled, we take the difference between the current time
//	and the time 99 events earlier, and average them.
//-----------------------------------------------------------------------
double getTimeStep()
{
	const int MANY = 100;				// number of values to average
	const int MILSEC_PER_SEC = 1000;

	static int mtime[MANY];				// start times
	static int prev = 0;				// previous event index
	static int curr = 0;				// current event index
	static int initializing = true;		// true during first MANY calls
	double averageTime;

	if (initializing) {					// initialization phase
		mtime[curr] = getMilliCount();	// save current time
		if (curr == 0) {
			averageTime = 0;			// very first call
		}
		else {							// else average from 0..curr 
			averageTime = double(mtime[curr] - mtime[0]) / double(MILSEC_PER_SEC * curr);
		}
		curr++;
		if (curr == MANY) {				// end of initialization
			initializing = false;
			prev = 1;					// starting config for remaining phases
			curr = 0;
		}
	}
	else {								// after initialization
		mtime[curr] = getMilliCount();	// save current time
		averageTime = double(mtime[curr] - mtime[prev]) / double(MILSEC_PER_SEC * (MANY-1));
		curr = prev;					// advance pointers
		prev = (prev + 1) % MANY;
	}
	return averageTime;
}
