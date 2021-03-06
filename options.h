#ifndef OPTIONS_H
#define OPTIONS_H

#include <vector>

namespace options
{
    /* value set by ‘--verbose’. */
    extern bool verbose;

    /* value set by '--phone' */
    extern char *phone_number;

    /* value set by '--config' */
    extern char *config;

    /* value set by '--profile' */
    extern char *profile;

    /* value set by '--exec' */
    extern char *exec;

    /* flag to indicate if user wants to execute something */
    extern bool do_exec;

    /* value set by '--enable-msg-id' */
    extern bool msg_id;

    /* value set by '--disable-colors' */
    extern bool no_colors;

    /* value set by '--alert' */
    extern bool alert;

    #ifdef USE_JSON
    /* value set by '--json' */
    extern bool json;
    #endif

    /* all non option arguments */
    extern std::vector<char*> argv;

    /* counter of all non option arguments */
    extern int argc;

} // options


#endif