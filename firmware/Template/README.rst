========
Template
========

Template is the empty project generated with the command::

    sapphiremake.py --create Template

Files
-----
app.c
    This is where your application code goes.  Some code is provided to execute your code along with the rest of the operating system, so you don't need touch that part of the code or even worry about what it is doing.  Let's look at what is provided.  Starting at the top:

    .. code-block:: c

        #include "sapphire.h"

        #include "app.h"

    sapphire.h is a wrapper around all of the header files for the libraries provided by the operating system.  It is provided here so you can directly call into useful libraries (io, keyvalue, etc.) without need additional #define statements.  app.h is just the header file for app.c.

    .. code-block:: c

        PT_THREAD( app_thread( pt_t *pt, void *state ) )
        {
        PT_BEGIN( pt );

            //executable application code goes here

        PT_END( pt );
        }

    This section defines your application thread.  PT_THREAD(), PT_BEGIN() and PT_END() are aready set up for you so do not need to modify them.  As the comment indicates, all you need to do in this section is put your executable application code between PT_BEGIN() and PT_END().  Generally this will be some initialization code, followed by a while(1) loop around some code you want to repeat.  There are a few requirements to adhere to in your application code:

        #. You must use wait statements to force the application thread to yield. See examples in other projects in this repo.
        #. Do not expect a variable decalred in your thread to be preserved after using a wait statement.  If you need a variable to persist, declare it as static.  Again, see examples in other projects in this repo.
        #. You cannot use a switch() statement.  This is a non-obvious restriction that comes from using protothreads.

    Final section of app.c:

    .. code-block:: c

        void app_v_init( void ){

        thread_t_create( app_thread,
                         PSTR("app"),
                         0,
                         0 );
        }

    This section starts the application thread, and does not need to be modified.  app_v_init() is called by main.c to start your application thread.

app.h
    Provides the app_v_init() prototype to be called by main.c.  This file does not generally need to be modified.
buildnumber.txt
    Used by the build system, and does not need to be modified.
main.c
    The entry point of the firmware code, which does not need to be modified.  main.c calls into app.c using app_v_init() to start the application code.
settings.json
    Contains project information, including Name, Firmware ID, Version, and build settings.
