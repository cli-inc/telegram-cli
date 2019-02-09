#ifndef OPTIONS_H
#define OPTIONS_H

#include <vector>

namespace options
{
    /* value set by ‘--verbose’. */
    static bool verbose;

    /* value set by '--phone' */
    static char *phone_number;

    /* value set by '--config' */
    static char *config;

    /* value set by '--profile' */
    static char *profile;

    /* value set by '--exec' */
    static char *exec;

    /* flag to indicate if user wants to execute something */
    static bool do_exec;

    /* value set by '--enable-msg-id' */
    static bool msg_id;

    /* value set by '--disable-colors' */
    static bool no_colors;

    /* value set by '--alert' */
    static bool alert;

    #ifdef USE_JSON
    /* value set by '--json' */
    static bool json;
    #endif

    /* all non option arguments */
    static std::vector<char*> argv;

    /* counter of all non option arguments */
    static int argc;

} // options


#endif