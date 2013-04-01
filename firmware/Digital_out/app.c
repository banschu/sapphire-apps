
#include "sapphire.h"

#include "app.h"


// define pin to use as a digital output
#define IO_PIN_DIGITAL_OUT  IO_PIN_GPIO7


/* Key-Value Start */

// define a key-value pair for the digital output
#define KV_ID_DIGITAL_OUT   1

// create a variable to bind to the value of the key-value pair
static bool digital_out = FALSE;

// Configure key-value meta data.
// This publishes a key called "digital_out" to the network.  The value of
// this key is bound to the local boolean digital_out.
KV_SECTION_META kv_meta_t app_kv[] = {
    { KV_GROUP_APP_BASE, KV_ID_DIGITAL_OUT, SAPPHIRE_TYPE_BOOL, 0, &digital_out, 0,  "digital_out" }
};

/* Key-Value End */


PT_THREAD( app_thread( pt_t *pt, void *state ) )
{
PT_BEGIN( pt );

    // declare a timer
    static uint32_t timer;

    // configure pin as output
    io_v_set_mode(IO_PIN_DIGITAL_OUT, IO_MODE_OUTPUT);

    // loop forever
    while(1){

        // output the value of digital_out
        io_v_digital_write(IO_PIN_DIGITAL_OUT, digital_out);

        // wait 20 ms
        timer = 20;
        TMR_WAIT(pt, timer);

    }

PT_END( pt );
}


// boilerplate initialiation
void app_v_init( void ){

    thread_t_create( app_thread,
                     PSTR("app"),
                     0,
                     0 );
}

