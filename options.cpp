#include "options.h"
#include "config.h"

// this file is needed for extern configuration

namespace options
{
    /* value set by ‘--verbose’. */
     bool verbose;

    /* value set by '--phone' */
     char *phone_number;

    /* value set by '--config' */
     char *config;

    /* value set by '--profile' */
     char *profile;

    /* value set by '--exec' */
     char *exec;

    /* flag to indicate if user wants to execute something */
     bool do_exec;

    /* value set by '--enable-msg-id' */
     bool msg_id;

    /* value set by '--disable-colors' */
     bool no_colors;

    /* value set by '--alert' */
     bool alert;

    #ifdef USE_JSON
    /* value set by '--json' */
     bool json;
    #endif

    /* all non option arguments */
     std::vector<char*> argv;

    /* counter of all non option arguments */
     int argc;

} // options