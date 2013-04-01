
#include "sapphire.h"

#include "app.h"


// define pin to use as a digital input
#define IO_PIN_DIGITAL_IN   IO_PIN_GPIO2


/* Key-Value Start */

// define a key-value pair for the digital input
#define KV_ID_DIGITAL_IN    1

// create a variable to bind to the value of the key-value pair
static bool digital_in = FALSE;

// Configure key-value meta data.
// This publishes a read-only key called "digital_in" to the network.  The
// value of this key is bound to the local boolean digital_in.
KV_SECTION_META kv_meta_t app_kv[] = {
    { KV_GROUP_APP_BASE, KV_ID_DIGITAL_IN, SAPPHIRE_TYPE_BOOL, 0, &digital_in, 0,  "digital_in" }
};

/* Key-Value End */


PT_THREAD( app_thread( pt_t *pt, void *state ) )
{
PT_BEGIN( pt );

    // declare a timer
    static uint32_t timer;

    // conifure pin as input with internal pull-up resistor
    io_v_set_mode(IO_PIN_DIGITAL_IN, IO_MODE_INPUT_PULLUP );

    // loop forever
    while(1){

        // read from pin
        bool new_digital_in = io_b_digital_read(IO_PIN_DIGITAL_IN);

        // check to see if input changed
        if(digital_in != new_digital_in){

            // store the new digital input value
            digital_in = new_digital_in;

            // notify all network listeners of the digital_in value change
            kv_i8_notify(KV_GROUP_APP_BASE, KV_ID_DIGITAL_IN);

        }

        //wait 20 ms
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

