#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "main.h"
#include "config.h"
#include "options.h"



int main (int argc, char **argv) {
  while (1) {
      static struct option long_options[] =
        {
          /* These options don’t set a flag.
             We distinguish them by their indices. */
          {"verbose", no_argument,       0, 'v'},
          {"phone", required_argument,  0,  'u'},
          {"config",  required_argument,  0,  'c'},
          {"profile", optional_argument,  0,  'p'},
          {"exec",  required_argument,  0,  'e'},
          {"enable-msg-id", no_argument,  0,  'N'},
          {"disable-colors", no_argument, 0,  'C'},
          {"alert", no_argument,  0,  'A'},
          {"help", no_argument, 0,  'h'},
          //{"daemonize", no_argument,  0,  'd'},
          #ifdef USE_JSON
          {"json",     no_argument,       0, 'j'},
          #endif

          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

      opterr = 0; // disable getopt error message
      int c = getopt_long (argc, argv, ":hACNvr:p:c:u:e:;",    // all short flags together
                           long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1) {
        break;
      }

      switch (c)
        {
        case 0:
          /* If this option set a flag, do nothing else now. */
          if (long_options[option_index].flag != 0)
            break;
          printf ("option %s", long_options[option_index].name);
          if (optarg)
            printf (" with arg %s", optarg);
          printf ("\n");
          break;

        case 'h':
          help();
          break;

        case 'A':
          options::alert = true;
          break;

        case 'C':
          options::no_colors = true;
          break;

        case 'N':
          options::msg_id = true;
          break;
        case 'p':
          if (optarg != NULL) {
            options::profile = optarg;
          } else {
            options::profile = "default";
          }
          break;
        case 'c':
          options::config = optarg;
          break;
        case 'u':
          options::phone_number = optarg;
          break;
        case'e':
          options::do_exec = true;
          options::exec = optarg;
          break;
        case 'v':
          options::verbose = true;
          puts("running in verbose mode");
          break;

        #ifdef USE_JSON
        case 'j':
          options::json = true;
          break;
        #endif

        // error handling sectin
        case '?': // invalid option
          printf("%s: invalid option -- '%c'\n", PACKAGE_NAME, optopt);
          help();
          break;
        case ':':   // missing option argument
          printf("%s: missing argument -- '%c'\n", PACKAGE_NAME, optopt);
          help();
          break;

        // should not happen at all
        default:
          printf("%s: error in execution: unable to process char %c\n", PACKAGE_NAME);
          printf("Please open a issue at: %s\n", PACKAGE_BUGREPORT);
          abort ();
        }
  }

  /* save any remaining command line arguments (not options). */
  if (optind < argc) {
      while (optind < argc) {
        char *arg = argv[optind++];
        options::argc++;
        options::argv.push_back(arg);
      }
  }
  exit (0);
}



static void help() {    // prints help message to terminal
  printf ("Usage: %s [options]\n", PACKAGE_NAME);
  
  printf ("  -u, --phone                    specify username (for registration)\n");
  printf ("  -v, --verbose                      set to verbose mode\n");
  printf ("  -N, --enable-msg-id            message num mode\n");
  printf ("  -c, --config                    config file name\n");
  printf ("  -p, --profile                  use specified profile\n");
  printf ("  -C, --disable-colors           disabled colored output\n");
  printf ("  -A, --alert                    enable bell notifications\n");
  printf ("  -e, --exec                     execute a single command and exit\n");  //TODO: think about executing all non flag arguments
  #ifdef USE_JSON
  printf ("  -j, --json                     prints answers and values in json format\n");
  #endif

  //  further info
  puts("\n");
  printf("please report bugs at: %s", PACKAGE_BUGREPORT);


  exit (0);
}
