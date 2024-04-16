#include "MMALIB_fft1dBatched_i32fc_c32fc_o32fc_idat.h"

static fft1d_testParams_t testParams[] = {
#if ((TEST_CASE == 27) || (TEST_CATEGORY == 1000))
    {
        RANDOM, // test pattern
        NULL,   // staticIn0
        NULL,   // staticIn1
        256,    // numChannels
        32,     // numPoints
        27,     // test ID
    },
#endif

#if ((TEST_CASE == 48) || (TEST_CATEGORY == 1000))
    {
        RANDOM, // test pattern
        NULL,   // staticIn0
        NULL,   // staticIn1
        64,     // numChannels
        64,     // numPoints
        48,     // test ID
    },
#endif

#if ((TEST_CASE == 55) || (TEST_CATEGORY == 1000))
    {
        RANDOM, // test pattern
        NULL,   // staticIn0
        NULL,   // staticIn1
        64,     // numChannels
        128,    // numPoints
        55,     // test ID
    },
#endif

};

/*
 *  Sends the test parameter structure and number of tests
 */
void fft1d_getTestParams (fft1d_testParams_t **params, int32_t *numTests)
{
   *params   = testParams;
   *numTests = sizeof (testParams) / sizeof (fft1d_testParams_t);
}
